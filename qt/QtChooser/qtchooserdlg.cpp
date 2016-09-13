/***************************************************************************************************************
Requires modified   configure.ac
                    linuxcnc.in
                    makeQt script
All available in qtchooser branch
********************************************************************************************************************/

#include "qtchooserdlg.h"

#include <QtDebug>
#include <QtWidgets/QFileSystemModel>
#include <QProcessEnvironment>

qtChooserDlg::qtChooserDlg()
{
QString str;
QStringList list, pathList;
QDir *dir;
QFileInfoList filesList[3];
QTreeWidgetItem *header[3];

    setupUi(this);

    QCoreApplication::setOrganizationName("MGWare");
    QCoreApplication::setOrganizationDomain("mgware.co.uk");
    QCoreApplication::setApplicationName("qtchooser");

    homeDir = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    mkHome = QProcessEnvironment::systemEnvironment().value("EMC2_HOME", "");

    str = homeDir + "/.config/MGWare/qtchooser/qtchooser.ini";
    settings = new QSettings(str, QSettings::IniFormat, this);

    // just get the item text for now
    getLastSelected();
    // make sure the saved file still exists
    dir = new QDir();
    if(lastFile.length())
        {
        if(dir->exists(lastFile))
            {
            list = lastFile.split("/");
            if(!list.isEmpty())
                {
                int sz = list.size();
                if(sz >= 2)
                    {
                    selectionName = list.at(sz -1);
                    selectionParentName = list.at(sz -2);
                    if(sz >= 3)
                        selectionGParentName = list.at(sz -3);
                    }
                else
                    selectionName = list.last();
                }
            }
        else
            selectionName = lastFile = "";
        }
    selectionItem = NULL;

    treeConfigs->setColumnCount(1);
    treeConfigs->setHeaderLabel("Machinekit - .INI file chooser");

        // if it is a RIP, this will find it
    if(mkHome.length())
        pathList.append(mkHome + "/configs");
        // std install examples
    pathList.append("/usr/share/linuxcnc/examples/sample-configs");
        // ~/machinekit
    pathList.append(homeDir + "machinekit/configs");

    for(int x = 0; x < pathList.size(); x++)
        {
        if(dir->exists(pathList[x]))
            {
            dir->setPath(pathList[x]);
            if((! (dir->path()).isEmpty()) && ((dir->path()) != ".") )
                {
                filesList[x] = dir->entryInfoList();
                header[x] = new QTreeWidgetItem();
                header[x]->setText(0,dir->path());
                treeConfigs->insertTopLevelItem(0, header[x]);
                addParents( header[x], filesList[x]);
                }
            }
        }

        // now restore the tree state
    readSettings();

    connect(treeConfigs , SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),    this, SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)));
    connect(treeConfigs , SIGNAL(itemClicked(QTreeWidgetItem*,int)),    this, SLOT(onItemClicked(QTreeWidgetItem*,int)));
    connect(this , SIGNAL(finished(int)),    this, SLOT(onFinished(int)));

    if(selectionItem != NULL)
        {
        treeConfigs->setCurrentItem(selectionItem);
            // manually select it and show README
        onItemClicked(selectionItem, 0);
        }

}


////////////////////////////////////////////////////////////////////////////////////////////

void qtChooserDlg::addParents(QTreeWidgetItem* header, QFileInfoList& list2)
{
QStringList list;
QTreeWidgetItem *ret = NULL;
QString str;
    foreach(QFileInfo fileInfo, list2)
        {
        if( fileInfo.isDir() && ( (fileInfo.fileName() != ".") && (fileInfo.fileName() != "..") ) )
            {
            list = (fileInfo.fileName()).split("/");
            if(!list.isEmpty())
                str = list.last();
            else
                str = fileInfo.fileName();
            QTreeWidgetItem* item = new QTreeWidgetItem(header);
            item->setText(0, str);
            item->setIcon(0,*(new QIcon("../images/folder.png")));
            ret = addChildren(item,fileInfo.filePath());
            if(ret != NULL)
                selectionItem = ret;
            header->addChild(item);
            }
        }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QTreeWidgetItem* qtChooserDlg::addChildren(QTreeWidgetItem* item, QString filePath)
{
QString str;
QStringList list;
QDir* rootDir = new QDir(filePath);
QFileInfoList filesList = rootDir->entryInfoList();
QTreeWidgetItem *ret, *ptr = NULL;

    foreach(QFileInfo fileInfo, filesList)
        {
        if(fileInfo.isFile() && (fileInfo.fileName()).contains(".ini"))
            {
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setText(0,fileInfo.fileName());
            item->addChild(child);
            // make sure we have right config by trying to checking 2 sections of path back from name
            if(selectionGParentName.length())
                {
                if((fileInfo.fileName() == selectionName) && (item->text(0) == selectionParentName) && ( ((item->parent())->text(0)).contains(selectionGParentName)) )
                    ptr = child;
                }
            else
                {
                if((fileInfo.fileName() == selectionName) && (item->text(0) == selectionParentName))
                    ptr = child;
                }
            }

        if( fileInfo.isDir() && ( (fileInfo.fileName() != ".") && (fileInfo.fileName() != "..") ) )
            {
            list = (fileInfo.fileName()).split("/");
            if(!list.isEmpty())
                str = list.last();
            else
                str = fileInfo.fileName();
            QTreeWidgetItem* child = new QTreeWidgetItem();
            child->setIcon(0,*(new QIcon("../images/folder.png")));
            child->setText(0, str);
            item->addChild(child);
                // if a dir recurse until a file
            ret = addChildren(child, fileInfo.filePath());
            if(ret != NULL)
                ptr = ret;
            }
        }
    return ptr;
}


////////////////////////////////////////////////////////////////////////////////////////////

void qtChooserDlg::onItemClicked(QTreeWidgetItem* item, int col)
{
Q_UNUSED(col)

QString str;

    if((item->text(0)).contains(".ini") )
        {
        selection = str = getFullPath(item);
        pathLabel->setText(selection);
        str = (str.left(str.lastIndexOf("/")));
        str += "/README";
        QFile file(str);
        if(file.exists())
            {
            if (file.open(QFile::ReadOnly | QFile::Text))
                {
                tbReadme->clear();
                QTextStream ts(&file);
                while( !ts.atEnd())
                    {
                    str = ts.readLine();
                    tbReadme->append(str);
                    }
                }
            }
        else
            tbReadme->clear();
        }

}

////////////////////////////////////////////////////////////////////////

QString qtChooserDlg::getFullPath(QTreeWidgetItem* item)
{
QString str, str2;
QTreeWidgetItem *p, *c;

    str2 = "/" + item->text(0).toLatin1();
    str = "";
    c = item;
    while((p = c->parent()) != NULL)
        {
        str = "/" + p->text(0).toLatin1() + str;
        c = p;
        }
    str.remove(0, 1);
    str2 = str + str2;

    return str2;

}

////////////////////////////////////////////////////////////////////////////////////////////

void qtChooserDlg::onItemDoubleClicked(QTreeWidgetItem* item, int col)
{
Q_UNUSED(item)
Q_UNUSED(col)

    if( (item->text(0)).contains(".ini") )
        accept();
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// Altered linuxcnc.in file, sets qtchooser as $PICKCONFIG and
// INIFILE=$(< ~/.qtchooser) ie reads the file to get path
//
void qtChooserDlg::onFinished(int code)
{
QString str;
    if(code == QDialog::Accepted)
        {
        str = "echo '" + selection + "' > ~/.qtchooser";
        system(str.toLatin1());
        }
    if(code == QDialog::Rejected)
        {
        str = "echo \"ESCAPE\" > ~/.qtchooser";
        system(str.toLatin1());
        }
    writeSettings();
}

////////////////////////////////////////////////////////////////////////////////////////////

void qtChooserDlg::readSettings()
{

    settings->beginGroup("WINDOW");
    restoreGeometry(settings->value("dialogGeometry").toByteArray());
    settings->endGroup();

    //LAST_FILE is done before tree creation to match names

    settings->beginGroup("TREE");
    QVariantList states = settings->value("states").toList();
    settings->endGroup();

    QTreeWidgetItemIterator it(treeConfigs);
    while (*it && !states.isEmpty())
        {
        (*it)->setExpanded(states.takeFirst().toBool());
        ++it;
        }


}


void qtChooserDlg::writeSettings()
{
    settings->beginGroup("WINDOW");
    settings->setValue("dialogGeometry", saveGeometry());
    settings->endGroup();

    settings->beginGroup("LAST_FILE");
    settings->setValue("LastFile", selection);
    settings->endGroup();

    QVariantList states;
    QTreeWidgetItemIterator it(treeConfigs);
    while (*it)
        {
        states += (*it)->isExpanded();
        ++it;
        }
    settings->beginGroup("TREE");
    settings->setValue("states", states);
    settings->endGroup();
}

////////////////////////////////////////////////////////////////////////////////////////////

void qtChooserDlg::getLastSelected()
{
    settings->beginGroup("LAST_FILE");
    lastFile = settings->value("LastFile", "").toString();
    settings->endGroup();

}

////////////////////////////////////////////////////////////////////////////////////////////
