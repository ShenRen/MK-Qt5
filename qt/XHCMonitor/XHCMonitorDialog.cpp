#include "XHCMonitorDialog.h"

#include <QtDebug>



XHCMonitorDialog::XHCMonitorDialog(QWidget *parent, int argc, char **argv)
:QDialog(parent)
{
QString str;
int r;
QStringList lst;

    iniFile = argv[1];
    if( (argc < 2) || (!iniFile.contains(".ini") ) )
        {
        qDebug() << "\nXHCMonitor ERROR:-  Syntax is XHCMonitor /path/to/inifile";
        qDebug() << "XHC-HB04 pendant will not be loaded\nQuitting............\n";
        exit(1);
        }
    prefix = "xhc-monitor";

    // build the dialog from ui
    setupUi(this);

    textEdit->setText("Checking for presence of pendant.............");

    lst << "Owner" << "Type" << "Dir" << "Value" << "Name" << "Net Dir" << "Signal";
    resultsTable->setHorizontalHeaderLabels(lst);

    QObject::connect(pb_Hide, SIGNAL(clicked()), this, SLOT(onHide()));
    QObject::connect(pb_ShowXHCPins, SIGNAL(clicked()), this, SLOT(onShowXHCPins()));
    QObject::connect(pb_ShowUtilPins, SIGNAL(clicked()), this, SLOT(onShowUtilPins()));
    QObject::connect(pb_ShowHaluiPins, SIGNAL(clicked()), this, SLOT(onShowHaluiPins()));
    QObject::connect(pb_Monitor, SIGNAL(clicked()), this, SLOT(onMonitor()));
    
    bFirstRun = true;
    bHidden = false;

// rt stuff
    _hal = new HAL_Access(argc, argv, prefix , false);

    if((r = createPins()))
        _hal->cleanUp();
    else
        _hal->engage();

    // read the ini file
    getSettings();

    // start the pendant
    str.sprintf("halcmd loadusr -W xhc-hb04 -I xhc-hb04-layout%d.cfg -H", layout);
    system( str.toLatin1().constData() );
    system("halcmd loadrt xhc_hb04_util names=pendant_util");
    str = "halcmd addf pendant_util " + threadname;
    system( str.toLatin1().constData() );

    connectPins();

    startTimer();
}

XHCMonitorDialog::~XHCMonitorDialog()
{
    hal_exit(comp_id);
}

void XHCMonitorDialog::onHide()
{
    hide(); 
    bHidden = true;
}

void XHCMonitorDialog::showList(QStringList& list)
{
int y, x;
QStringList rowList, lst;
QTableWidgetItem *newItem;

    resultsTable->clearContents();
        // this is the best way (undocumented) to remove the rows and leave headers
    resultsTable->model()->removeRows(0, resultsTable->rowCount());

    for(x = 0; x < list.size(); x++)
        {
	rowList = (list[x]).split(",");
	resultsTable->insertRow(x);
	for(y = 0; y < rowList.size() && y < 7; y++)
	    {
	    newItem = new QTableWidgetItem();
	    newItem->setText(rowList[y]);
	    resultsTable->setItem(x,y, newItem);
	    }
	}
    // make table fir the widget
    resultsTable->horizontalHeader()->setStretchLastSection(true);
    // make columns fit the contents
    resultsTable->setVisible(false);
    resultsTable->resizeColumnsToContents();
    resultsTable->setVisible(true);

}

void XHCMonitorDialog::onShowXHCPins()
{
QStringList list;
QString name = "xhc-hb04";

    _hal->getPinInfo(name, list, true);
    showList(list);
}

void XHCMonitorDialog::onShowUtilPins()
{
QStringList list;
QString name = "pendant_util";

    _hal->getPinInfo(name, list, true);
    showList(list);
}

void XHCMonitorDialog::onShowHaluiPins()
{
QStringList list;
QString name = "halui";

    _hal->getPinInfo(name, list, true);
    showList(list);
}

void XHCMonitorDialog::onMonitor()
{
    textEdit->setText("Checking for presence of pendant.............");
    bFirstRun = true;
}

void XHCMonitorDialog::getSettings()
{
QString str2;
QStringList list;
int x;

QSettings settings(iniFile, QSettings::IniFormat);

    settings.beginGroup("XHC_HB04_CONFIG");
        // specify layout = n for xhc-hb04-layout{n}.cfg files
    layout = settings.value("layout", 2 ).toInt();
    
        // normally 1 or true, but can be 0 for testing
    bRequirePendant = settings.value("require_pendant", 1).toBool();
    
        // lowpass settings:
        // coef: slows rate of change of output,  range: 0 < coef < 1
    str2 = settings.value("coefs", "0 0 0 0").toString();
    list = str2.split(" ");
    for(x = 0; x < list.size() && x < 4 ; x++)
        coefs[x] = (list.at(x)).toInt();
    
        // scale plus or minus, rotaries may require larger scale factor 
    str2 = settings.value("scales", "1 1 1 1").toString();
    list = str2.split(" ");
    for(x = 0; x < list.size() && x < 4 ; x++)
        scales[x] = (list.at(x)).toInt();
    
        // coords: specify 4 letters
        // coords: switch labels are xyza but any unique 4 letters
        // from the set {xyxabcuvw) can be used (if the coord exists)
    str2 = settings.value("coords", "x y z a").toString();
    list = str2.split(" ");
    for(x = 0; x < list.size() && x < 4 ; x++)
        coords[x] = (list.at(x)).data()->toLatin1();
    coordsNum = x;
        // jogmode normal(default) or vnormal or plus-minus
    jogmode = settings.value("jogmode", "normal").toString();
    
        // sequence 1 mm, 2 inch
    sequence = settings.value("sequence", 1 ).toInt();
        // this may not exist, default to usual name
    threadname = settings.value("threadname", "servo-thread").toString();
    settings.endGroup();

    settings.beginGroup("XHC_HB04_BUTTONS");
    go_to_zero = settings.value("goto-zero", "halui.mdi-command-00").toString();
    start_pause = settings.value("start-pause", "std_start_pause").toString();
    rewind = settings.value("rewind", "halui.program.step").toString();
    probe_z = settings.value("probe-z", "motion.probe-input").toString();
    macro_3 = settings.value("macro-3", "halui.mdi-command-03").toString();
    half = settings.value("half", "halui.spindle.stop").toString();
    zero = settings.value("zero", "").toString();
    safe_z = settings.value("safe-z", "halui.mdi-command-10").toString();
    home = settings.value("home", "halui.home-all").toString();
    macro_1 = settings.value("macro-1", "halui.mdi-command-01").toString();
    macro_2 = settings.value("macro-2", "halui.mdi-command-02").toString();
    spindle = settings.value("spindle", "halui.spindle.start").toString();
    step = settings.value("step", "xhc-hb04.stepsize-up").toString();
    mode = settings.value("mode", "").toString();
    macro_6 = settings.value("macro-6", "halui.mdi-command-06").toString();
    macro_7 = settings.value("macro-7", "halui.mdi-command-07").toString();
    stop = settings.value("stop", "halui.program.stop").toString();
    reset = settings.value("reset", "halui.estop.activate").toString();
    settings.endGroup();

/*
    // DEBUG print
    qDebug() << "bRequirePendant is " << bRequirePendant;
    qDebug() << "iniFile is " << iniFile;
    qDebug() << "Layout is " << layout;
    qDebug() << "threadname is " << threadname;
    qDebug() << "coordsNum is " << coordsNum;
    for(x=0; x < 4; x++)
	    qDebug() << coefs[x];
    for(x=0; x < 4; x++)
        qDebug() << scales[x];
    for(x=0; x < 4 ; x++)
        qDebug() << coords[x];
*/
}

int XHCMonitorDialog::createPins()
{
    // none here yet
    return 0;
}


// NB. cannot use direction arrows here, sh does not like them in a command
int XHCMonitorDialog::connectPins()
{
QStringList cmdList;
// the preset coord allocations used by xhc-hb04
// these can be netted to other axes later
char acoords[] = {'x','y','z','a'};
QString str;
int x;

    cmdList.append("halcmd net xhc-jog-scale xhc-hb04.jog.scale");
    cmdList.append("halcmd net xhc-jog-counts xhc-hb04.jog.counts");
    cmdList.append("halcmd net xhc-jog-counts-neg xhc-hb04.jog.counts-neg");

    for(x = 0; x < coordsNum; x++)
        {
        
        str.sprintf("halcmd setp pendant_util.coef%d %d", x, coefs[x]);
        cmdList.append(str);
  
        str.sprintf("halcmd setp pendant_util.scale%d %d", x, scales[x]);
        cmdList.append(str);

        str.sprintf("halcmd net xhc-pos-%c halui.axis.%d.pos-feedback xhc-hb04.%c.pos-absolute", coords[x], x, acoords[x] );
        cmdList.append(str);

        str.sprintf("halcmd net xhc-pos-rel-%c halui.axis.%d.pos-relative xhc-hb04.%c.pos-relative", coords[x], x, acoords[x]);
        cmdList.append(str);
        str.sprintf("halcmd net xhc-jog-scale axis.%d.jog-scale", x);
        cmdList.append(str);
        str.sprintf("halcmd net xhc-jog-counts pendant_util.in%d", x);
        cmdList.append(str);
        str.sprintf("halcmd net xhc-jog-counts-%c-filtered pendant_util.out%d axis.%d.jog-counts", coords[x], x , x);
        cmdList.append(str);
    
        if(jogmode == "normal" || jogmode == "vnormal")
            {
            str.sprintf("halcmd net xhc-jog-%c xhc-hb04.jog.enable-%c axis.%d.jog-enable", coords[x], acoords[x], x);
            cmdList.append(str);
            }
        if(jogmode == "plus-minus")
            {
            // connect halui plus,minus pins
            str.sprintf("halcmd net xhc-jog-plus-%c xhc-hb04.jog.plus-%c halui.jog.%d.plus", coords[x], acoords[x], x);
            cmdList.append(str);
            str.sprintf("halcmd net xhc-jog-minus-%c xhc-hb04.jog.minus-%c halui.jog.%d.minus", coords[x], acoords[x], x);
            cmdList.append(str);
            }
        if(jogmode == "vnormal")
            {
            str.sprintf("halcmd setp axis.%d.jog-vel-mode 1", x);
            cmdList.append(str);
            }
        }

    if(jogmode == "normal" || jogmode == "vnormal")
        cmdList.append("halcmd net xhc-jog-speed halui.max-velocity.value");
        // not used: xhc-hb04.jog.velocity
        // not used: xhc-hb04.jog.max-velocity
    if(jogmode == "plus-minus")
        {
        // Note: the xhc-hb04 driver manages xhc-hb04.jog.velocity");
        cmdList.append("halcmd net xhc-jog-max-velocity halui.max-velocity.value");
        cmdList.append("halcmd net xhc-jog-max-velocity xhc-hb04.jog.max-velocity");
        cmdList.append("halcmd net xhc-jog-speed xhc-hb04.jog.velocity");
        cmdList.append("halcmd net xhc-jog-speed halui.jog-speed");
        }

    cmdList.append("halcmd setp halui.feed-override.scale 0.01");
    cmdList.append("halcmd net xhc-jog-counts halui.feed-override.counts");

    cmdList.append("halcmd setp halui.spindle-override.scale 0.01");
    cmdList.append("halcmd net xhc-jog-counts halui.spindle-override.counts");

    cmdList.append("halcmd net xhc-jog-feed halui.feed-override.count-enable xhc-hb04.jog.enable-feed-override");
    cmdList.append("halcmd net xhc-jog-feed2 halui.feed-override.value xhc-hb04.feed-override");

    cmdList.append("halcmd net xhc-jog-spindle halui.spindle-override.count-enable");
    cmdList.append("halcmd net xhc-jog-spindle xhc-hb04.jog.enable-spindle-override");
    cmdList.append("halcmd net xhc-jog-spindle2  halui.spindle-override.value xhc-hb04.spindle-override");
    cmdList.append("halcmd net xhc-spindle-rps motion.spindle-speed-cmd-rps xhc-hb04.spindle-rps");

    // connect pendant_util
    cmdList.append("halcmd net xhc-is-idle halui.program.is-idle pendant_util.is-idle");
    cmdList.append("halcmd net xhc-is-paused halui.program.is-paused pendant_util.is-paused");
    cmdList.append("halcmd net xhc-is-running halui.program.is-running pendant_util.is-running");
    cmdList.append("halcmd net xhc-program-resume pendant_util.resume halui.program.resume");
    cmdList.append("halcmd net xhc-program-pause pendant_util.pause halui.program.pause");
    cmdList.append("halcmd net xhc-program-run pendant_util.run halui.program.run");

    // connect buttons
    str = "halcmd net xhc-go-to-zero  xhc-hb04.button-goto-zero " + go_to_zero;
    cmdList.append(str);

    if(start_pause != "std_start_pause") // only connect if not the standard setting
        {
        str = "halcmd net xhc-start-or-pause xhc-hb04.button-start-pause " + start_pause;
        cmdList.append(str);
        }
    else // std setting
        cmdList.append("halcmd net xhc-start-or-pause xhc-hb04.button-start-pause pendant_util.start-or-pause");

    str = "halcmd net xhc-rewind xhc-hb04.button-rewind " + rewind;
    cmdList.append(str);
    str = "halcmd net xhc-probe-z xhc-hb04.button-probe-z  " +  probe_z;
    cmdList.append(str);
    str = "halcmd net xhc-macro-3 xhc-hb04.button-macro-3 " + macro_3;
    cmdList.append(str);
    str = "halcmd net xhc-button-half xhc-hb04.button-half  " + half;
    cmdList.append(str);
    if(zero != "")
        {
        str = "halcmd net xhc-zero xhc-hb04.button-zero " + zero;
        cmdList.append(str);
        }
    str = "halcmd net xhc-safe-z xhc-hb04.button-safe-z " +  safe_z;
    cmdList.append(str);
    str = "halcmd net xhc-home xhc-hb04.button-home " +  home;
    cmdList.append(str);
    str = "halcmd net xhc-macro-1 xhc-hb04.button-macro-1 " + macro_1;
    cmdList.append(str);
    str = "halcmd net xhc-macro-2 xhc-hb04.button-macro-2 " + macro_2;
    cmdList.append(str);
    str = "halcmd net xhc-macro-6 xhc-hb04.button-macro-6 " + macro_6;
    cmdList.append(str);
    str = "halcmd net xhc-macro-7 xhc-hb04.button-macro-7 " + macro_7;
    cmdList.append(str);
    str = "halcmd net xhc-spindle xhc-hb04.button-spindle " + spindle;
    cmdList.append(str);
    str = "halcmd net xhc-step xhc-hb04.button-step " + step;
    cmdList.append(str);
    if(mode != "")
        {
        str = "halcmd net xhc-mode xhc-hb04.button-mode " + mode;
        cmdList.append(str);
        }
    str = "halcmd net xhc-stop xhc-hb04.button-stop " + stop;
    cmdList.append(str);
    str = "halcmd net xhc-reset xhc-hb04.button-reset " + reset;
    cmdList.append(str);

    for( x = 0; x < cmdList.size(); x++)
        system( (cmdList.at(x)).toLatin1().constData() );

    return 0;
}

void XHCMonitorDialog::startTimer()
{   
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(eventsLoop()));
    timer->start(1000);
}


void XHCMonitorDialog::eventsLoop()
{
QString str, str1, str2, str3;
bool connected = false;

    str = "xhc-hb04.connected";

    if((_hal->getPValue(str, str1) == 0) )
        {
        connected = str1.toInt();
        if(bRequirePendant)
            str = "Pendant is required, ";
        else
            str = "Pendant is NOT required, ";
        if(connected)
            str += "xhc-hb04 is connected";
        else
            str += "xhc-hb04 is NOT connected";
        }
        // write str on first run
    if(bFirstRun)
        {
        textEdit->append(str);
        bFirstRun = false;
        bConnected = connected;
        }
        // thereafter only if state changes
    else
        {
        if((connected != bConnected))
            {
            bConnected = connected;
    	    textEdit->append(str);
            // force show if it has been hidden
            show();
            bHidden = false;
            }
        }
}


