#include "QtAxis.h"
#include <QIODevice>
#include <QByteArray>

///////////////  persistence in MDI command history, files position etc /////////////////


void QtAxis::readSettings()
{
QString str, str2;
int i, lines;

    settings->beginGroup("WINDOW");
    restoreGeometry(settings->value("mainWindowGeometry").toByteArray());
    restoreState(settings->value("mainWindowState").toByteArray());
    settings->endGroup();

    settings->beginGroup("MDI");
    lines = settings->value("Lines", 0).toInt();

    for (i = 0; i < lines; ++i)
        listMDITemp.append(settings->value(str.sprintf("Line%02d", i), "").toString());
    settings->endGroup();

    settings->beginGroup("RECENT_FILES");
    lines = settings->value("Files", 0).toInt();
    for (i = 0; i < lines; ++i)
        listRecentFiles.append(settings->value(str.sprintf("Line%02d", i), "").toString());
    settings->endGroup();
    listRecentFiles.removeDuplicates();

    settings->beginGroup("LAST_FILE");
    lastFile = settings->value("LastFile", "").toString();
    settings->endGroup();

    settings->beginGroup("SLIDERS");
    jogSpeed = settings->value("JogSlider", 0).toInt();
    feedOverride = settings->value("FeedSlider", 0).toInt();
    currentVelocity = settings->value("VelocitySlider", 0).toInt();
    settings->endGroup();

    settings->beginGroup("GREMLIN");
    gremlin_width = settings->value("GremlinWidth", 0).toInt();
    gremlin_height = settings->value("GremlinHeight", 0).toInt();
    gremlin_Xoffset = settings->value("GremlinXoffset", 0).toInt();
    gremlin_Yoffset = settings->value("GremlinYoffset", 0).toInt();
//    bGremlin = settings->value("BGremlin", true).toBool();
//    actionGremlin->setChecked(bGremlin);
    settings->endGroup();

//    qDebug() << "Settings read\n" << listMDITemp[0] << "\n" << listRecentFiles[0] << "\n" << lastFile  << "\n" << jogSpeed << "\n" << feedOverride << "\n" << currentVelocity 
//    << "\n" << gremlin_width << "\n" << gremlin_height << "\n" << bGremlin;
}

void QtAxis::writeSettings()
{
QString str, str2;
int i, lines;

    settings->beginGroup("WINDOW");
    settings->setValue("mainWindowGeometry", saveGeometry());
    settings->setValue("mainWindowState", saveState());
    settings->endGroup();

    settings->beginGroup("MDI");
    settings->setValue("Lines", lines = listMDITemp.count());
    for (i = 0; i < lines; ++i)
        settings->setValue(str.sprintf("Line%02d", i), listMDITemp.at(i));
    settings->endGroup();

    listRecentFiles.removeDuplicates();
    settings->beginGroup("RECENT_FILES");
    settings->setValue("Files", lines = listRecentFiles.count());
    for (i = 0; i < lines; ++i)
        settings->setValue(str.sprintf("Line%02d", i), listRecentFiles.at(i));
    settings->endGroup();

    settings->beginGroup("LAST_FILE");
    if(openFile.length())
        settings->setValue("LastFile", openFile);
    settings->endGroup();

    settings->beginGroup("SLIDERS");
    settings->setValue("JogSlider", slideJog->value());
    settings->setValue("FeedSlider", slideFeed->value());
    settings->setValue("VelocitySlider", slideVelocity->value());
    settings->endGroup();

    settings->beginGroup("GREMLIN");
    settings->setValue("GremlinWidth", gremlin_width);
    settings->setValue("GremlinHeight", gremlin_height);
    settings->setValue("GremlinXoffset", gremlin_Xoffset);
    settings->setValue("GremlinYoffset", gremlin_Yoffset);
//    settings->setValue("BGremlin", bGremlin);
    settings->endGroup();

//    qDebug() << "Settings read\n" << listMDITemp[0] << "\n" << listRecentFiles[0] << "\n" << lastFile  << "\n" << jogSpeed << "\n" << feedOverride << "\n" << currentVelocity 
//    << "\n" << gremlin_width << "\n" << gremlin_height << "\n" << bGremlin;

}


//////////////////////////////////////////////////////////////////////

void QtAxis::onOpenFile()
{
QString filename;

    if(!bRun)
        {
//        if(openFile.length())
//            querySave();

        filename = QFileDialog::getOpenFileName(this, tr("Open GCode"), _hal->_nml->programPrefix, tr("GCode Files (*.ngc *.nc);; All files (*.*)"));
        if(openInBrowser(filename) == 0)
            {
//            connect((QTextDocument*)te_Code->document(), SIGNAL(modificationChanged(bool)), this, SLOT(onGCodeModificationChanged(bool)));
//            pb_Edit->setText("Edit G Code");
            }
        }
}

void QtAxis::onReloadFile()
{
    if(!bRun)
        {
//        querySave();
        if(openInBrowser(openFile) == 0)
            {
//            connect((QTextDocument*)te_Code->document(), SIGNAL(modificationChanged(bool)), this, SLOT(onGCodeModificationChanged(bool)));
//            // update the edit window to reflect new file now loaded
//            pb_Edit->setText("Edit G Code");
            }
        }
}

// TODO look at xemc and axis re file opens


int QtAxis::openInBrowser(QString& filename)
{
QFile file(filename);
QString str;
char buff[LINELEN];

    if(!allHomed())
        {
        statusbar->showMessage("Cannot do operation until homed", 10000);
        return -1;
        }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
        bLoadChanged = true;  // flag that tells onGCodeChanged() that it only changed because we loaded a file
        str = "Loading file " + filename;
        statusbar->showMessage(str);
        
        te_Code->setReadOnly(false);
        te_Code->clear();
        QTextStream in(&file);
        while (!in.atEnd()) 
            te_Code->appendPlainText(in.readLine());
        file.close();
        te_Code->setReadOnly(true);
        str = "QtCNC :- " +  filename;
        setWindowTitle(str);
        listRecentFiles.append(openFile = filename);
        bLoadChanged = false;
        
        openFile = filename;
        QStrncpy(buff, filename, filename.length());
        _hal->_nml->sendMdi();   // forces interp sync by switching modes
        _hal->_nml->sendAuto();
        _hal->_nml->sendSynch(); // sends INIT to interpreter
        // this not only opens program but writes its name
        _hal->_nml->sendProgramOpen(buff);
//        _hal->_nml->sendManual();
        te_Code->highlightLine(1);
//        pb_Edit->setText("Edit G Code");
        return 0;
        }
    else
        {
        str = "Error (re)loading file " + filename ;
        statusbar->showMessage(str, 10000);
        return -1;
        }

}



////////////////////////////////////////////////////////////////////////

/*
void QtAxis::onOpenFile()
{
QString filename;

    if(!bRun)
        {
        filename = QFileDialog::getOpenFileName(this, tr("Open GCode"), _hal->_nml->programPrefix, tr("GCode Files (*.ngc *.nc);; All files (*.*)"));
        if(filename.length())
            openInBrowser(filename);
        }
}


int QtAxis::openInBrowser(QString& filename)
{
QString filename;

    if(!bRun)
        {
        if(openFile.length())
            querySave();

        filename = QFileDialog::getOpenFileName(this, tr("Open GCode"), _hal->_nml->programPrefix, tr("GCode Files (*.ngc *.nc);; All files (*.*)"));
        if(openInBrowser(filename) == 0)
            {
            connect((QTextDocument*)te_Code->document(), SIGNAL(modificationChanged(bool)), this, SLOT(onGCodeModificationChanged(bool)));
            pb_Edit->setText("Edit G Code");
            }
        }

//    REPLACE WITH NORMAL FILE OPEN

QFile file(filename);
QString str, str2;
char buff[LINELEN];

    if(!allHomed())
        {
        te_Messages->append("Cannot do operation until homed");
        return -1;
        }

    if (file.open(QFile::ReadOnly | QFile::Text))
        {
        fileSize = file.size();
        str = "Loading file " + filename;
        statusbar->showMessage(str);
        te_Code->clear();

        QTextStream ts(&file);

        while( (!ts.atEnd()) && (ts.pos() < CHUNK_SIZE) )
            {
            str = ts.readLine();
            if(str.length())
                {
                str = str + "\n";
                te_Code->appendNewPlainText(str);
                }
            }

        filePos = ts.pos();
        if(file.size() > MAX_SIZE)
            bBigFile = true;

        if(fileSize >= filePos)
             bMoreBig = true;
        else
             bMoreBig = false;

        file.close();

        str = "QtCNC :- " +  filename;
        setWindowTitle(str);
        listRecentFiles.append(openFile = filename);
        bLoadChanged = false;

        openFile = filename;
        QStrncpy(buff, filename, filename.length());
        _hal->_nml->sendMdi();   // forces interp sync by switching modes
        _hal->_nml->sendAuto();
        _hal->_nml->sendSynch(); // sends INIT to interpreter
        // this not only opens program but writes its name
        _hal->_nml->sendProgramOpen(buff);

        te_Code->highlightLine(1);

        return 0;
        }
    else
        {
        str = "Error loading file " + filename ;
        statusbar->showMessage(str);
        return -1;
        }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// called when further chunks of a large file are added to the text edit widget

int QtAxis::reOpenInBrowser()
{

        
    if(!bRun)
        {
        querySave();
        if(openInBrowser(openFile) == 0)
            {
            connect((QTextDocument*)te_Code->document(), SIGNAL(modificationChanged(bool)), this, SLOT(onGCodeModificationChanged(bool)));
            // update the edit window to reflect new file now loaded
            pb_Edit->setText("Edit G Code");
            }
        }
//    REPLACE WITH NORMAL FILE REOPEN
QString str, str2;
QFile file(openFile);

    if (file.open(QFile::ReadOnly | QFile::Text))
        {
        if(file.size() != fileSize)
            {
            qDebug() << "Error - file size has changed since last load - " << openFile;
            return -1;
            }
        QTextStream ts(&file);
        ts.seek(filePos);

        while( (!ts.atEnd()) && (ts.pos() < (filePos + ADD_SIZE) ) )
            {
            str = ts.readLine();
            if(str.length())
                {
                str = str + "\n";
                te_Code->appendNewPlainText(str);
                }
            }

        filePos = ts.pos();
        if(fileSize > filePos)
            bMoreBig = true;
        else
            bMoreBig = false;

        file.close();
        return 0;
        }
    else
        {
        str = "Error reOpening file " + openFile;
        statusbar->showMessage(str, 10000);
        return -1;
        }

}
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void QtAxis::onLoadLast()
{
    if(lastFile.length())
        openInBrowser(lastFile);

}


void QtAxis::onRecentFiles()
{
    listRecentFiles.removeDuplicates();
    RecentFilesDialog *dlg = new RecentFilesDialog(this, listRecentFiles);

    dlg->exec();

    if(dlg->result())
        openInBrowser(dlg->selection);

    listRecentFiles.removeDuplicates();
}

/*
void QtAxis::querySave()
{
//    if(bModified)
//        {
//        if( QMessageBox::question ( this, "QtCNC:  Save changes?", "The G Code file has changed\nDo you want to save it?", 
//                                    QMessageBox::Ok , QMessageBox::No ) == QMessageBox::Ok)
//        onSaveAs();
//        }  
}  
*/
