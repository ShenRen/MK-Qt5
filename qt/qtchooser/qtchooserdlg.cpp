/***************************************************************************************************************
Requires modified   configure.ac
                    linuxcnc.in
                    makeQt script
All available in qtchooser branch
********************************************************************************************************************/

#include "qtchooserdlg.h"

#include <QtDebug>
#include <QtWidgets/QFileSystemModel>


qtChooserDlg::qtChooserDlg()
{
QString str;
QStringList list;

    // build the dialog from ui
    setupUi(this);

//////////////////////////////////////////////////////////////////////////////////////

    QCoreApplication::setOrganizationName("MGWare");
    QCoreApplication::setOrganizationDomain("mgware.co.uk");
    QCoreApplication::setApplicationName("qtchooser");

    // qt does not understand ~/ so path must be absolute or it will create ~/ on PWD
    struct passwd *pw = getpwuid(getuid());
    homeDir = pw->pw_dir;
    str = homeDir;
    str += "/.config/MGWare/qtchooser/qtchooser.ini";
    settings = new QSettings(str, QSettings::IniFormat, this);

    // just get the item text for now
    getLastSelected();
    // make sure the saved file still exists
    QDir *dir0 = new QDir();
    if(lastFile.length())
        {
        if(dir0->exists(lastFile))
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

///////////////////////////////////////////////////////////////////////////////////////

    treeConfigs->setColumnCount(1);
    treeConfigs->setHeaderLabel("Machinekit - .INI file chooser");
    // always have user configs first
    // search for configs in default locations

    QString path1 = "/usr/src/machinekit/configs";
    QString path2 = "/usr/share/linuxcnc/examples/sample-configs";
    QString path3 = homeDir + "/src/machinekit/sample-configs";
    QString path4 = homeDir + "/machinekit/configs";
    // This allows user defined extra path to search for configs in ini
    getExtraPath();
    QString path5 = extraPath;
//    qDebug() << "extraPath = " << extraPath;
    QDir* dir1 = new QDir();

    if(dir1->exists(path1))
        {
        dir1->setPath(path1);
        }
    else if(dir1->exists(path2) )
        {
        dir1->setPath(path2);
        }
    else
        {
        if(dir1->exists(path3))
            {
            dir1->setPath(path3);
            }
        }

    if((! (dir1->path()).isEmpty()) && ((dir1->path()) != ".") )
        {
        QFileInfoList filesList1 = dir1->entryInfoList();
        QTreeWidgetItem* header1 = new QTreeWidgetItem();
        header1->setText(0,dir1->path());
        treeConfigs->insertTopLevelItem(0, header1);
        addParents( header1, filesList1);    
        }
    
    QDir* dir2 = new QDir(path4);
    if((! (dir2->path()).isEmpty()) && ((dir2->path()) != ".") )
        {        
        QFileInfoList filesList2 = dir2->entryInfoList();    
        QTreeWidgetItem* header2 = new QTreeWidgetItem();
        header2->setText(0,dir2->path());
        treeConfigs->insertTopLevelItem(0, header2);
        addParents( header2, filesList2);
        }
//    qDebug() << "path5 = " << path5;        
    if(path5.length() && dir0->exists(path5))
        {
        QDir* dir3 = new QDir(path5);
        QTreeWidgetItem* header3 = new QTreeWidgetItem();
        header3->setText(0,dir3->path());
        treeConfigs->insertTopLevelItem(0, header3);
        QFileInfoList filesList3 = dir3->entryInfoList();
        addParents( header3, filesList3);
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
            item->setIcon(0,*(new QIcon("folder.png")));
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
            child->setIcon(0,*(new QIcon("folder.png")));
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

void qtChooserDlg::getExtraPath()
{
    settings->beginGroup("EXTRA_PATH");
    extraPath = settings->value("ExtraPath", "").toString();
    settings->endGroup();

}

////////////////////////////////////////////////////////////////////////////////////////////
