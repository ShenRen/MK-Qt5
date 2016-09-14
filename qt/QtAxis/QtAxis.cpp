// QtAxis 

/***********************************************************************
 * TODO
 * 
 * Fix pause etc
 * Make QtAxis top window?
 * 
 * 
***********************************************************************/
#include "QtAxis.h"
#include <QShortcut>
#include <X11/Xlib.h>

QtAxis::QtAxis(int argc, char** argv)
{
QString str, str2;

    started = false;
    bJogging = false;
    
    // build the main window from ui
    setupUi(this);
    qDebug() << argv[1] << argv[2];

    // series of arrays and lists used for addressing data and widgets in an efficient manner.
    QList<QRadioButton*> rbList;
    rbList << rbX << rbY << rbZ << rbU << rbV << rbW << rbA << rbB << rbC ;
    QList<QLabel*> labelList;
    labelList << labelX << labelY << labelZ << labelU << labelV << labelW << labelA << labelB << labelC ;
    QList<QLabel*> labelG54List;
    labelG54List << lbXG54 << lbYG54 <<lbZG54 <<lbUG54 <<lbVG54 <<lbWG54 <<lbAG54 <<lbBG54 <<lbCG54;
    QList<QLabel*> labelG53List;
    labelG53List << lbXG53 << lbYG53 <<lbZG53 <<lbUG53 <<lbVG53 <<lbWG53 <<lbAG53 <<lbBG53 <<lbCG53;

    char axes[] = {'X','Y','Z','U','V','W','A','B','C'};
    bool homed[] = {false, false, false, false, false, false, false, false, false};
    for(int x = 0; x < MAX_AXES; x++)
        {
        buttonArray[x] = rbList.at(x);
        axisArray[x] = axes[x];
        axisHomedArray[x] = homed[x];
        axisG54Array[x] = labelG54List.at(x);
        axisG53Array[x] = labelG53List.at(x);
        }
    // cannot use XPos etc because now reserved names!!  Arghh took ages to find this out
    pinNameListAbs  << "XAbsPin" << "YAbsPin" << "ZAbsPin" << "UAbsPin" << "VAbsPin" << "WAbsPin" << "AAbsPin" << "BAbsPin" << "CAbsPin";
    pinNameListRel  << "XRelPin" << "YRelPin" << "ZRelPin" << "URelPin" << "VRelPin" << "WRelPin" << "ARelPin" << "BRelPin" << "CRelPin";
    signalNameListAbs  << "XposAbs" << "YposAbs" << "ZposAbs" << "UposAbs" << "VposAbs" << "WposAbs" << "AposAbs" << "BposAbs" << "CposAbs";
    signalNameListRel  << "XposRel" << "YposRel" << "ZposRel" << "UposRel" << "VposRel" << "WposRel" << "AposRel" << "BposRel" << "CposRel";

    coordList << "G54" << "G55" << "G56" << "G57" << "G58" << "G59" << "G59.1" << "G59.2" << "G59.3";

    currentAxis = axisArray[currentAxisIndex = 0]; //X
    buttonArray[0]->setChecked(true);

    bEstop = true;
    bMachine = false;
    bRun = false;
    bPause = false;
    bStep = false;
    bDirect = false;
    bHomeAll = false;
    
    bDRO = false;
    bGCode = false;
    bManual = true;
    bMDI = false;

    gremlin_width = 0;
    gremlin_height = 0;
    gremlin_Xoffset = 0;
    gremlin_Yoffset = 0;
    
//    bGremlin = true;
    bGremlinRunning = false;

    filePos = 0L;
    fileSize = 0L;
    chunkIndex = 0;
    listIndex = 1;

    startLine = oldStartLine = 1;
    currentLine = oldCurrentLine = 0;

    // set true to fill in text first time round
    // will be set false on first iteration of refresh loop
    bHomeStateChanged = true;

    jogSpeed = 300;  // default
    
    currentVelocity = 10.0;
    maxVelocity = 10.0;

    feedOverride = 1.0;
    maxFeedOverride = 1.2;

    axesList.clear();
    numAxes = 0;

    id = 0;

    prefixName = "qtMDI";
    iniFile = argv[2];

    actionToggleEstop->setChecked(true);
    actionToggleMachineOn->setEnabled(false);
    tabManual->setEnabled(false);

    prefixName = "QtAxis";
    iniFile = argv[2];

    _hal = new HAL_Access(argc, argv, prefixName, true);

    setupPins();

    _hal->engage();

    // ensure we start in estop and manual mode
    _hal->_nml->sendEstop();
    _hal->_nml->sendManual();
    
    setupExtra();

    startTimer(250);
    
    // override the default behavior of gremlin_view by making this window top
    setWindowFlags(Qt::WindowStaysOnTopHint);
    

}

//////////////////////////////////////////////////////////////////////////////////
//
// closeEvent() traps the system event and forces closure through onCloseDown()
// any code needs to be in onCloseDown() because other exit methods go straight there.
void QtAxis::closeEvent(QCloseEvent * event )
{
    Q_UNUSED(event);

    onCloseDown();
    
    event->accept();
}

void QtAxis::onCloseDown()
{

    refreshTimer->stop();

    _hal->_nml->cleanUp();

    writeSettings();
    
    gremlinProcess->close();  
    //above cleaner than terminate(); which gives warning
}

void QtAxis::onExitPressed()
{
    onCloseDown();
    
    qApp->exit();
}



//////////////////////////////////////////////////////////////////////////////////

// These are not standard pins, but are created in local arrays for ease of indexing

void QtAxis::setupPins()
{
QString pin = "inposition";
QString motion_inpos = "motion.in-position";
QString signame = "InPosSig";
QStringList pinList;
QString str, str2;
int i = 0;

    numAxes = 0;

    axesList = _hal->_nml->getCoordinates();

    for(int x = 0; x < MAX_AXES; x++)
        {
        if(axesList.contains(axisArray[x]))
           numAxes++;  // update it to number of coordinates
        }

    // create pins for absolute and relative positions
    for(i = 0; i < numAxes; i++)
        _hal->createFloatPin(pinNameListAbs[i], true);

    for(i = 0; i < numAxes; i++)
        _hal->createFloatPin(pinNameListRel[i], true);

    // now for in-position pin
    _hal->createBitPin(pin, true);

    //  Now link the absolute pins to signals XposAbs, YposAbs, ZposAbs etc
    for(int x = 0; x < numAxes; x++)
        {
        _hal->createSignal(signalNameListAbs[x], HAL_FLOAT);
        str.sprintf("halui.axis.%d.pos-feedback", x);
        if(_hal->linkPin2Signal(str, signalNameListAbs[x]))
            {
            str2 = "linkPin2Signal() failed " + str + " " +  signalNameListAbs[x];
            te_Messages->append(str2);
            qDebug() << str2;
            }
        else
        // if that succeeds, link signal to our absolute position pins
            {
            str =  prefixName + "." + pinNameListAbs[x];
            if(_hal->linkPin2Signal(str, signalNameListAbs[x]) != 0)
                {
                str2 = "linkPin2Signal() failed " + str + " "  + signalNameListAbs[x];
                te_Messages->append(str2);
                qDebug() << str2;
                }
            }
        }

    for(int x = 0; x < numAxes; x++)
        {
        //  Now create the signals XposRel etc
        _hal->createSignal(signalNameListRel[x], HAL_FLOAT);
        // link signals to halui pins
        str.sprintf("halui.axis.%d.pos-relative", x);
        if(_hal->linkPin2Signal(str, signalNameListRel[x]) != 0)
            {
            str2 = "linkPin2Signal() failed " + str + " " + signalNameListRel[x];
            te_Messages->append(str2);
            qDebug() << str2;
            }
        else
        // if that succeeds, link signal to our relative position pins
            {
            str =  prefixName + "." + pinNameListRel[x];
            if(_hal->linkPin2Signal(str, signalNameListRel[x]) != 0)
                {
                str2 = "linkPin2Signal() failed " + str + " "  + signalNameListRel[x];
                te_Messages->append(str2);
                qDebug() << str2;
                }
            }
        }
    // another way to create sig and link all in one
    pinList << prefixName + "." + pin << motion_inpos;
    _hal->netSignalPin(signame, pinList);

}

///////////////////////////////////////////////////////////////////////////////////



void QtAxis::setupExtra()
{
QString str;

    te_Code->setReadOnly(true);
    te_Code->setLineWrapMode(QPlainTextEdit::NoWrap);
    te_Code->setCenterOnScroll(true);

    // get data extracted from INI file
    bHomeAll = _hal->_nml->isHomeAll();
    axesList = _hal->_nml->getCoordinates();

    // this will get the entry, but it could be misleading
    numAxes = _hal->_nml->getNumAxes();

    // if a homing sequence was detected in the .ini file
    // offer opportunity to home all or do it individually
    // If not detected pbHome button does all homing
    // and pbUnReHome is disabled
    if(bHomeAll)
        {
        pbHome->setText("Home All");
        pbUnReHome->setEnabled(true);
        }
    else
        {
        pbUnReHome->setText("");
        pbUnReHome->setEnabled(false);
        }

    for(int x = 0; x < MAX_AXES; x++)
        {
        if(!axesList.contains(axisArray[x]))
            (buttonArray[x])->setEnabled(false);
        }

    QCoreApplication::setOrganizationName("MGWare");
    QCoreApplication::setOrganizationDomain("mgware.co.uk");
    QCoreApplication::setApplicationName("QtAxis");

    // qt does not understand ~/ so path must be absolute or it will create ~/ on PWD
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;

    str = homedir;
    str += "/.config/MGWare/QtAxis/QtAxis.ini";
    settings = new QSettings(str, QSettings::IniFormat, this);

    makeConnections();

    readSettings();

    // set up sliders from ini file values with fallback defaults
    if(!jogSpeed)
        jogSpeed = _hal->_nml->jogSpeed;
    maxJogSpeed = _hal->_nml->maxJogSpeed; // returns value already * 60 + 0.5
    slideJog->setRange(0, maxJogSpeed);
    slideJog->setSliderPosition(jogSpeed);
    onJogSliderChanged(jogSpeed);

    _hal->_nml->maxFeedOverride > 1 ? maxFeedOverride = (_hal->_nml->maxFeedOverride * 100) : maxFeedOverride = 120;

    slideFeed->setRange(0, maxFeedOverride);
    if(!feedOverride)
        feedOverride = 100;
    slideFeed->setSliderPosition(feedOverride);
    onFeedSliderChanged(feedOverride);

    maxVelocity =  (_hal->_nml->maxMaxVelocity * 60 + 0.5);
    slideVelocity->setRange(0, maxVelocity);
    if(!currentVelocity)
        currentVelocity = 600;
    slideVelocity->setSliderPosition(currentVelocity);
    onVelocitySliderChanged(currentVelocity);
    
    setupGremlin();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////


void QtAxis::makeConnections()
{
    connect(actionToggleEstop, SIGNAL(triggered()), this, SLOT(onToggleEstop()));
    connect(actionToggleMachineOn, SIGNAL(triggered()), this, SLOT(onToggleMachine()));
    connect(actionHome, SIGNAL(triggered()), this, SLOT(onHome()));

    connect(actionOpen, SIGNAL(triggered()), this, SLOT(onOpenFile()));
    connect(actionReload, SIGNAL(triggered()), this, SLOT(onReloadFile()));
    connect(actionRecentFiles, SIGNAL(triggered()), this, SLOT(onRecentFiles()));
    connect(actionLoadLast, SIGNAL(triggered()), this, SLOT(onLoadLast()));

    // actionRun is menu item
    connect(actionRun, SIGNAL(triggered()), this, SLOT(onRunProgram()));
    connect(actionRunProgram, SIGNAL(triggered()), this, SLOT(onRunProgram()));
    connect(te_Code, SIGNAL(runFromSelected(int)), this, SLOT(onRunFromContext(int)));
    connect(actionPauseProgram, SIGNAL(triggered()), this, SLOT(pauseProgram()));
    connect(actionStopProgram, SIGNAL(triggered()), this, SLOT(stopProgram()));
    connect(actionStep, SIGNAL(triggered()), this, SLOT(stepProgram()));

    connect(actionAboutQt, SIGNAL(triggered()), this, SLOT(onAboutQt()));
    connect(actionAboutQtAxis, SIGNAL(triggered()), this, SLOT(onAboutQtAxis()));

    connect(actionExit, SIGNAL(triggered()), this, SLOT(onExitPressed()));

    connect(actionGremlin, SIGNAL(triggered()), this, SLOT(onGremlin()));
//    connect(actionStopOnError, SIGNAL(triggered()), this, SLOT(onStopOnError()) );
    connect(pbClear, SIGNAL(clicked()), this, SLOT(onClearMessages()));

    connect(pbJogXPlus, SIGNAL(pressed()), this, SLOT(onJogXPlus()));
    connect(pbJogXPlus, SIGNAL(released()), this, SLOT(onJogXOff()));
    connect(pbJogXMinus, SIGNAL(pressed()), this, SLOT(onJogXMinus()));
    connect(pbJogXMinus, SIGNAL(released()), this, SLOT(onJogXOff()));

    connect(pbJogYPlus, SIGNAL(pressed()), this, SLOT(onJogYPlus()));
    connect(pbJogYPlus, SIGNAL(released()), this, SLOT(onJogYOff()));
    connect(pbJogYMinus, SIGNAL(pressed()), this, SLOT(onJogYMinus()));
    connect(pbJogYMinus, SIGNAL(released()), this, SLOT(onJogYOff()));

    connect(pbJogZPlus, SIGNAL(pressed()), this, SLOT(onJogZPlus()));
    connect(pbJogZPlus, SIGNAL(released()), this, SLOT(onJogZOff()));
    connect(pbJogZMinus, SIGNAL(pressed()), this, SLOT(onJogZMinus()));
    connect(pbJogZMinus, SIGNAL(released()), this, SLOT(onJogZOff()));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// Launch a modified gremlin_view
// Gets the inifile name from env var $INIFILE, exported from linucnc script
// Allows setting an offset within the screen to allow repeatable placement

void QtAxis::setupGremlin()
{
QString str1, str2, str3, str4, program = "gremlin_view";
QStringList arguments;

    if(!bGremlinRunning)
        {  
        // 0 is valid value for offsets, just means no move
        if(gremlin_width == 0 ) 
            gremlin_width = 400;
        if(gremlin_height == 0 ) 
            gremlin_height = 300;
            
        str1.sprintf("-W %d", gremlin_width);
        str2.sprintf("-H %d", gremlin_height);
        str3.sprintf("-X %d", gremlin_Xoffset);
        str4.sprintf("-Y %d", gremlin_Yoffset);
        arguments << str1 << str2 << str3 << str4;
        // use Qprocess rather than fork, because process can be 
        // closed on exit.  Don't need any data from it, so no
        // signal/slot connections set up
        gremlinProcess = new QProcess(this);
        gremlinProcess->start(program, arguments);
        }
}

////////////////////////////  Refresh loop //////////////////////////////////////

void QtAxis::startTimer(int period)
{
    refreshTimer = new QTimer(this);
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    refreshTimer->start(period);
}

///////////////////////  this loop redraws the DRO values  ///////////////////////////////

void QtAxis::updateDRO()
{
QString str;
float pos;
int x, y;

    for(x = 0; x < numAxes; x++)
        {
        pos = _hal->getFloatPinValue(x);
        str.sprintf("%08.03f", pos);
        (axisG53Array[x])->setText(str);
        }
    // we are indexing the _hal internal array of pins so need to preserve the index
    // into next call
    y = x + numAxes;
    for(int z = 0; x < y; x++, z++)
        {
        pos = _hal->getFloatPinValue(x);
        str.sprintf("%08.03f", pos);
        (axisG54Array[z])->setText(str);
        }


}

///////////// this loop refreshes all info and redraws as required  /////////////////////////

void QtAxis::refresh()
{
static int idle_count = 0;
int current,  motion, count = 0;
QString state_str, str, str2, str3;

    QApplication::setActiveWindow(this);
    
    if(bRun)
        {
        if(bGCode)
            {
            motion = _hal->_nml->getMotionLine();
            current = _hal->_nml->getCurrentLine();
            count = te_Code->getLineCount();

            if (current > 0)
                {
                if ( (motion > 0) && (motion < current) )
                    // active line is the motion line, which lags
                    currentLine = motion;
                else
                    currentLine = current;
                }
            else
                // no active line at all
                currentLine = 0;

            if (currentLine != oldCurrentLine)
                {
                te_Code->highlightLine(currentLine);
                oldCurrentLine = currentLine;
                }
            // The currentline calculations is flawed, never reported properly
            // This prevents sitting at end of file which has stopped
            if(_hal->_nml->emcStatus->task.interpState == EMC_TASK_INTERP_IDLE)
                idle_count++;
            if(  (_hal->_nml->emcStatus->task.interpState == EMC_TASK_INTERP_IDLE) && (idle_count >= (count - (currentLine - 2) ) ) )
                {
                stopProgram();
                idle_count = 0;
                }
            }
        // only visible in DRO tab
        if(bDRO)
            updateDRO();
        checkErrors();
        }
    else
        {
        // only visible in DRO tab
        if(bDRO)
            updateDRO();
        
        checkErrors();
        // Only visible in MDI tab
        if(bMDI)
            {
            // update active codes, if displayed
            lb_activeGCodes->setText(_hal->_nml->getActiveGCodes());
            lb_activeMCodes->setText(_hal->_nml->getActiveMCodes());
            lb_feedSpeed->setText(_hal->_nml->getActiveSettings());
            }
        // Update button text and logic if home state changed
        if(bHomeStateChanged && !bRun) // button is disabled when running
            {
            if(axisHomedArray[currentAxisIndex])
                {
                if(bHomeAll)
                    {
                    str = "Un-Home All";
                    pbHome->setText(str);
                    str.sprintf("Un-Home %c", axisArray[currentAxisIndex]);
                    pbUnReHome->setText(str);
                    }
                else
                    {
                    str.sprintf("Un-Home %c", axisArray[currentAxisIndex]);
                    pbHome->setText(str);
                    }
                }
            else
                {
                if(bHomeAll)
                    {
                    str = "Home All";
                    pbHome->setText(str);
                    str.sprintf("Home %c", axisArray[currentAxisIndex]);
                    pbUnReHome->setText(str);
                    }
                else
                    {
                    str.sprintf("Home %c", axisArray[currentAxisIndex]);
                    pbHome->setText(str);
                    }
                }
            bHomeStateChanged = false;
            }
        }

}

////////////////////////////////////////////////////////////////////////


void QtAxis::checkErrors()
{
    // read the EMC status
    if (0 != _hal->_nml->updateStatus())
        _hal->_nml->error_string = "Bad Status";

    // read the EMC errors
    if (0 != _hal->_nml->updateError())
        _hal->_nml->error_string = "Bad Status";

    // print any result stored by updateError() in error_string
    if (_hal->_nml->error_string.length())
        {
        te_Messages->append(_hal->_nml->error_string);
        _hal->_nml->error_string = "";
        }
}

////////////////////////////////////////////////////////////////////////

bool QtAxis::allHomed()
{
    for(int x = 0; x < numAxes; x++)
        {
        if(!axisHomedArray[x])
            return false;
        }
    return true;
}


////////////////////////////////////////////////////////////////
//
// helper to save problems translating QStrings to char*
// which NML and HAL functions require
//

void QtAxis::QStrncpy(char* str, QString& qstr, int num)
{
int x;

    for(x = 0; x < num; x++)
        {
        str[x] = (char)qstr.at(x).toLatin1();
        }
    str[x] = 0;  // terminating '\0'

}
