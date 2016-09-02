#include "QtAxis.h"

//////////////////////////////////////////////////////////////////////////////

void QtAxis::onAxis(bool on)
{
    if(on  && !bJogging && !bRun)
        {
        for(int i = 0; i < MAX_AXES; i++)
           {
            if( (buttonArray[i])->isChecked())
                {
                currentAxis = axisArray[i];
                currentAxisIndex = i;
                break;
                }
            }
        // set flag to force button re-write
        bHomeStateChanged = true;
        }

    if(bJogging)
        te_Messages->append("Cannot change axis whilst jogging");
}

//////////////////////////////////////////////////////////////////////////////////

void QtAxis::onHome()
{
QString str;

    if(bHomeAll)
        {
        if( (pbHome->text()) == "Home All" )
            {
            _hal->_nml->sendHomeAll();

            for(int x = 0; x < numAxes; x++)
                axisHomedArray[x] = true;
            }
        else
            {
            _hal->_nml->sendUnhome(-1);

            for(int x = 0; x < numAxes; x++)
               axisHomedArray[x] = false;
            }
        }
    else
        {
        if( (pbHome->text()).contains("Un-Home") )
            {
            _hal->_nml->sendUnhome(currentAxisIndex);
            axisHomedArray[currentAxisIndex] = false;
            }
        else
            {
            _hal->_nml->sendHome(currentAxisIndex);
            axisHomedArray[currentAxisIndex] = true;
            }
        }
    bHomeStateChanged = true;
    statusbar->showMessage("");
}


void QtAxis::onUnReHome()
{
QString str;

    if((pbUnReHome->text()).contains("Un-Home"))
        {
        _hal->_nml->sendUnhome(currentAxisIndex);
        axisHomedArray[currentAxisIndex] = false;
        }
    else
        {
        _hal->_nml->sendHome(currentAxisIndex);
        axisHomedArray[currentAxisIndex] = true;
        }
    bHomeStateChanged = true;
}



///////////////////////////////////////////////////////////////////////////////////

void QtAxis::onTouchOff()
{
   
QString str, str2;
float value;
int coordinateSystem;

    if(bJogging || bRun)
        {
        te_Messages->append("Cannot touch off whilst jogging or in Auto mode");
        return;
        }

    touchOffDialog *dlg = new touchOffDialog(this, coordList, currentAxis);

    dlg->exec();

    if(dlg->result())
        {
        value = dlg->value;
        str = dlg->cbText;
        coordinateSystem = dlg->index + 1;
        str.sprintf("G10 L20 P%d %c%08.03f", coordinateSystem, currentAxis, value);
        str2 = str + " " + dlg->cbText;
        statusbar->showMessage(str2);

        _hal->_nml->sendMdi();

        QStrncpy(lastCommand, str, str.length());
        if((lastCommand)[0] != 0)
            _hal->_nml->sendMdiCmd(lastCommand);

        _hal->_nml->sendManual();
        }

}


void QtAxis::onJogSliderChanged(int value)
{
QString str;
    jogSpeed = value;
    str.sprintf("Jog Speed:  %d", value);
    lbJog->setText(str);
}

// value received is 0 - 120% - needs converting to 0 - 1.2 range
void QtAxis::onFeedSliderChanged(int value)
{
QString str;
    feedOverride = value;
    str.sprintf("Feed Override:  %d", value);
    str += " %";
    lbFeed->setText(str);
    _hal->_nml->sendFeedOverride(feedOverride / 100);
}

void QtAxis::onVelocitySliderChanged(int value)
{
QString str;

    currentVelocity = value;
    str.sprintf("Max Velocity:  %d mm/min", value);
    lbVelocity->setText(str);
    _hal->_nml->sendMaxVelocity(currentVelocity / 60);
}


//////////////////////////////////////////////////////////////////////////////////////////////

void QtAxis::onJogMinus(int axis)
{
    if(!bRun)
        {
        _hal->_nml->sendManual();
        bJogging = true;
        _hal->_nml->axisJogging = axis;
        _hal->_nml->sendJogCont(axis, -jogSpeed);
        }
}

void QtAxis::onJogPlus(int axis)
{

    if(!bRun)
        {
        _hal->_nml->sendManual();
        bJogging = true;
        _hal->_nml->axisJogging = axis;
        _hal->_nml->sendJogCont(axis, jogSpeed);
        }
}

void QtAxis::onJogOff(int axis)
{
    bJogging = false;
    _hal->_nml->sendJogStop(axis);
}

////////////////////////////////////////////////////////////////



void QtAxis::onTabViewChanged(int index)
{
Q_UNUSED(index)

    switch(index)
        {
        case 0: // Messages
                bDRO = false;
                bGCode = false;
                break;
        case 1: // DRO
                bDRO = true;
                bGCode = false;
                break;
        case 2: // GCode
                bDRO = false;
                bGCode = true;
        default:
                break;
        }
}

void QtAxis::onTabControlChanged(int index)
{
    switch(index)
        {
        case 0: bManual = true;
                bMDI = false;
                if(started && ! bRun)
                    _hal->_nml->sendManual();
                break;
        case 1: bManual = false;
                bMDI = true;
                if(started && ! bRun)
                    {
                    //_hal->_nml->sendMdi(); done at every command anyway
                    list_MDI->clear();
                    for (int i = 0; i < listMDITemp.size(); ++i)
                        list_MDI->addItem(listMDITemp.at(i));
                    le_MDI->setFocus(Qt::OtherFocusReason);
                    }
                break;
        default:
                break;
        }
}




///////////////////////////////////////////////////////////////////////

void QtAxis::onToggleEstop()
{
    if(bEstop)
        {
        _hal->_nml->sendEstopReset();
        estopOff();
        }
    else
        {
        _hal->_nml->sendEstop();
        estopOn();
        }
}

void QtAxis::onToggleMachine()
{

    if(bMachine)
        {
        _hal->_nml->sendMachineOff();
        machineOff();
        }
    else
        {
        _hal->_nml->sendMachineOn();
        machineOn();
        if(!started)
            {
            started = true;
            tabControl->setCurrentIndex(0);
            }
        }
}

void QtAxis::estopOff()
{
    actionToggleEstop->setChecked(bEstop = false);
    actionToggleMachineOn->setEnabled(true);
}

void QtAxis::estopOn()
{
    actionToggleEstop->setChecked(bEstop = true);
    actionToggleMachineOn->setEnabled(false);
    machineOff();
}

void QtAxis::machineOn()
{
    actionToggleMachineOn->setChecked(bMachine = true);
    tabManual->setEnabled(true);
    onAxis(true);
}

void QtAxis::machineOff()
{
    _hal->_nml->sendMachineOff();
    actionToggleMachineOn->setChecked(bMachine = false);
    tabManual->setEnabled(false);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// only called directly from context menu in code editor
void QtAxis::onRunFromContext(int line /* = 1*/)
{
    bDirect = true;
    onRunFrom(line);

}

void QtAxis::onRunProgram(int line /* = 1 */)
{
    if(!bRun && !bPause) // if not running or paused
        {
        // set mode to AUTO
        _hal->_nml->sendAuto();
        startLine = oldStartLine = line;
        actionRunProgram->setChecked(bRun = true);
        runEnable(false);
        _hal->_nml->sendProgramRun(startLine);
        }
}

void QtAxis::onRunFrom(int line)
{
    if(bRun) return;

    onRunProgram(line);
    qDebug() << "Run From line " << line;
}

/*
void QtAxis::onRunProgram()
{
    bDirect = false;
    onRunFrom(1);
}

// check if direct command from te_Code first to override the current line number

void QtAxis::onRunFrom(int line )
{
    if(!openFile.length())
        {
        te_Messages->append("Error - no file open - cannot execute Run command");
        actionRunProgram->setChecked(bRun = false);
        runEnable(false);
        return;
        }
    // if Run-From activated whilst Running and in Pause - change index
    if(bDirect)
        {
        if(bRun && bPause)
            {
            actionPauseProgram->setChecked(bPause = false);
            listIndex = line;
            bDirect = false;
            return;
            }
        bDirect = false;
        }
    // if run button toggled off - treat as Stop
    if( bRun && !actionRunProgram->isChecked() )
        {
        bRun = false;
        stopProgram();
        return;
        }
    // shouldn't go here - but just in case
    if(bRun) return;

    // if not running or paused- ie normal start
    if(!bRun && !bPause)
        {
        actionRunProgram->setChecked(bRun = true);
        _hal->_nml->sendMdi();
        runEnable(false);
//        refreshTimer->stop();
//        refreshTimer->start(100);
        }
    listIndex = line;
}

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void QtAxis::pauseProgram()
{
    if(!bPause && bRun) // if not already paused and running
        actionPauseProgram->setChecked(bPause = true);
    else if(bPause && bRun)
        actionPauseProgram->setChecked(bPause = false);
    else  // the button itself is checkable even if the action does not fit into above 2
          // so stop it checking unless desired
        actionPauseProgram->setChecked(bPause = false);
}

void QtAxis::stepProgram()
{
    if(bPause && bRun)  // can only step from paused program
        actionStep->setChecked(bStep = true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//  Even though we are using MDI commands, this will still abort everything

void QtAxis::stopProgram()
{
    bRun = false;
    actionPauseProgram->setChecked(bPause = false);
    actionRunProgram->setChecked(bRun = false);
    runEnable(true);
    _hal->_nml->sendAbort();
    _hal->_nml->sendManual();

    refreshTimer->stop();
    refreshTimer->start(500);

    // highlight first line to show stopped
    te_Code->highlightLine(1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// enables and disables all the relevant buttons when running program

void QtAxis::runEnable(bool onoff)
{
    //axesGroupBox->setEnabled(onoff);
    horizontalLayout_5->setEnabled(onoff);
    pbHome->setEnabled(onoff);
    pbUnReHome->setEnabled(onoff);
    pbTouch->setEnabled(onoff);
    pbJogXMinus->setEnabled(onoff);
    pbJogXPlus->setEnabled(onoff);
    tabMDI->setEnabled(onoff);
    statusbar->showMessage("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void QtAxis::onAboutQtAxis()
{
    QMessageBox::about (this, "About QtAxis",
                        "               QtAxis\n"
                        "            LinuxCNC GUI\n"
                        "          (c) ArcEye 2012 - 2015\n\n"
                        "An alternative front end to MachineKit\n"
                        "     written entirely in Qt5 C++\n");
}

void QtAxis::onAboutQt()
{
    QMessageBox::aboutQt(this, "QtAxis - About Qt");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void QtAxis::onGremlin()
{
    gremlinDlg *dlg = new gremlinDlg(this, gremlin_width, gremlin_height, gremlin_Xoffset, gremlin_Yoffset);

    dlg->exec();

    if(dlg->result())
        {
        gremlin_width = dlg->width;
        gremlin_height = dlg->height;
        gremlin_Xoffset = dlg->xoffset;
        gremlin_Yoffset = dlg->yoffset;           
           
        if(!bGremlinRunning)
            setupGremlin();
        else
           statusbar->showMessage("Gremlin size changes will take effect at next start up", 3000);
        }
}

void QtAxis::onClearMessages()
{
    te_Messages->clear();
}


