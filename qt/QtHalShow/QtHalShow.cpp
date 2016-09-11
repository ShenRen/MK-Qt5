#include "QtHalShow.h"

#include <QtDebug>
#include <QColor>
#include <QMessageBox>


QtHalShow::QtHalShow(QWidget *parent)
:QDialog(parent)
{
QString str;
int r;
QStringList lst;

    prefix = "halshow";

    // build the dialog from ui
    setupUi(this);
    
    QObject::connect(treeHal, SIGNAL( itemClicked(QTreeWidgetItem*, int)), this, SLOT(onItemClicked(QTreeWidgetItem*, int)));
    QObject::connect(treeHal, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onContextTree(const QPoint&)));
    QObject::connect(tableWatch, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onContextTableWatch(const QPoint&)));
    
    tabWidget->setCurrentIndex(0);
    onCurrentTabChanged(0);
        
    treeHal->setColumnCount(1);
    treeHal->setHeaderLabel("HAL Configuration");

    actionRemove = new QAction(this);
    actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
    actionRemove->setText("Remove");

    actionWatch = new QAction(this);
    actionWatch->setObjectName(QString::fromUtf8("actionWatch"));
    actionWatch->setText("Watch");
    
// rt stuff 
    
    _hal = new HAL_Access(); // passive version of lib, we do our own connection
    
    comp_id = hal_init("halshow");
    
    if(comp_id < 0) 
        exit(-1);
        
    if((r = createPins())) 
        hal_exit(comp_id);    
    else
        {
        hal_ready(comp_id);
        qDebug() << "Component registered and ready" << "comp_ID " << comp_id;
        }

    fillTree();

}


QtHalShow::~QtHalShow()
{
    hal_exit(comp_id);
    qDebug() << "Cleaned Up";
}

void QtHalShow::reject()
{
// prevent exit using Alt F4 or window buttons
}

/////////////////////////////////////////////////////////////////////////////////////////
// stub to create pins - unused at present

int QtHalShow::createPins()
{
    // none here yet
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
// when tableWatch tab visible, timer runs to update values of contents

void QtHalShow::startTimer()
{   
    QTimer::singleShot(500, this, SLOT(eventsLoop()));
}



///////////////////////////////////////////////////////////////////////////////////////////////////
// routines to walk the pin names and create a treeview

void QtHalShow::fillTree()
{
QString str, str1;
QStringList list[6], groupList[6], subgroupList[6];
QTreeWidgetItem *header[6];
int x = 0, y = 0;

    headerList << "Components" << "Pins" << "Parameters" << "Signals" << "Functions" << "Threads";
    
    // get all the raw info for each header type
    _hal->getAllComponentNames(list[x++]);
    _hal->getAllPinNames(list[x++]);
    _hal->getAllParamNames(list[x++]);
    _hal->getAllSignals(list[x++], true);
    _hal->getAllFuncNames(list[x++]);
    _hal->getAllThreadNames(list[x]);

    // set the top level headers and store the items
    for(x = 0; x < headerList.size(); x++)
        {
        header[x] = new QTreeWidgetItem();
        header[x]->setText(0,headerList[x]);
        treeHal->addTopLevelItem(header[x]);
        }

    // split off the first part of each name into list eg. axis
    for(x = 0; x < headerList.size(); x++)
        {
        for(y = 0; y < list[x].size() ; y++)
            {
            str = (list[x])[y];
            int z = str.indexOf(".");
            str = str.left(z);
            groupList[x].append(str);
            }
        groupList[x].removeDuplicates();
        }
    // split off the first two parts of each name into list eg. axis.0
    for(x = 0; x < headerList.size(); x++)
        {
        for(y = 0; y < list[x].size() ; y++)
            {
            str = (list[x])[y];
            int z = str.indexOf(".");
            z = str.indexOf(".", z+1);
            str = str.left(z);
            subgroupList[x].append(str);
            }
        subgroupList[x].removeDuplicates();
        }

    for(x = 0; x < headerList.size(); x++)
        addGroups( header[x], groupList[x], subgroupList[x], list[x], x);


}

// Insert the group name
// For components, signals, functions and threads, they have a single name - the group
// Therefore we do not need to go down to subgroups as we do for pins and params

void QtHalShow::addGroups(QTreeWidgetItem* header, QStringList& groupList, QStringList& subgroupList, QStringList& pinList, int group)
{

    for( int i = 0; i < groupList.size(); i++)
        {
        QTreeWidgetItem* item = new QTreeWidgetItem(header);
        item->setText(0, groupList[i]);
        header->addChild(item);
        if( group && (group < 3) ) // only for pins and params
            addSubGroups(item, groupList[i], subgroupList, pinList);
        }
}

void QtHalShow::addSubGroups(QTreeWidgetItem* group, QString& name, QStringList& subgroupList, QStringList& pinList)
{
QString str;

    for( int i = 0; i < subgroupList.size(); i++)
        {
        if( subgroupList[i] == name )
            continue;
        str = subgroupList[i];
        int z = str.indexOf(".");
        str = str.left(z);
 
        if( str == name )
            {
            QTreeWidgetItem* item = new QTreeWidgetItem(group);
            item->setText(0, subgroupList[i]);
            group->addChild(item);
            addGroupChildren(item, subgroupList[i], pinList, true);  // use the group.subgroup to match against
            }
        else
            addGroupChildren(group, subgroupList[i], pinList, false); // just use the group to match against
        }
}


void QtHalShow::addGroupChildren(QTreeWidgetItem* group, QString& name, QStringList& pinList, bool subgroup)
{
QString str;

    for( int i = 0; i < pinList.size(); i++)
        {
        if( pinList[i] == name )
            continue;
        str = pinList[i];
        int z = str.indexOf(".");
        if(subgroup)
            z = str.indexOf(".", z+1); // new
        str = str.left(z);
        if( str == name )
            {
            QTreeWidgetItem* item = new QTreeWidgetItem(group);
            item->setText(0, pinList[i]);
            group->addChild(item);
            }
        }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// routines to display in the tableShow and tableWatch

void QtHalShow::showList(QStringList& list)
{
int y, x;
QStringList rowList, lst;
QString str;
QTableWidgetItem *newItem;
QColor red("#FF0000"), green("#008000"), blue("#0000FF"), purple("#800080"), fuscia("#FF00FF");
QColor maroon("#800000"), aqua("#00FFFF"), olive("#808000"), teal("#008080"), orange("#FF8C00");
QRegExp re("\\d*");  // a digit (\d), zero or more times

    tableShow->clearContents();
        // this is the best way (undocumented) to remove the rows and leave headers
    tableShow->model()->removeRows(0, tableShow->rowCount());

    //col = QColorDialog::getColor( colour = Qt::green, this);
    for(x = 0; x < list.size(); x++)
        {
        rowList = (list[x]).split(",");
        tableShow->insertRow(x);
        for(y = 0; y < rowList.size() && y < 7; y++)
            {
            newItem = new QTableWidgetItem();
            newItem->setText(rowList[y]);
            tableShow->setItem(x,y, newItem);
            if( (rowList[y].contains("Thread Users")) || (rowList[y].contains("No Users")) )
                newItem->setForeground(red);
            else if( rowList[y].contains("TRUE") || rowList[y] == "YES" || rowList[y] == "ready")
                newItem->setForeground(green);
            else if( rowList[y].contains("FALSE") || rowList[y] == "NO" || rowList[y] == "initializing")
                newItem->setForeground(red);
            else if( rowList[y] == "IN" || rowList[y] == "RO" || rowList[y] == "INST")
                newItem->setForeground(purple);
            else if( rowList[y] == "OUT" || rowList[y] == "RW" || rowList[y].contains("RT") )
                newItem->setForeground(blue);
            else if( rowList[y] == "I/O" )
                newItem->setForeground(fuscia);
            else if( rowList[y].contains("bit" ))
                newItem->setForeground(teal);
            else if( rowList[y].contains("s32" ))
                newItem->setForeground(aqua);
            else if( rowList[y].contains("u32" ))
                newItem->setForeground(olive);
            else if( rowList[y].contains("float" ))
                newItem->setForeground(maroon);
            else 
                {
                str = rowList[y];
                str = str.simplified();
                str = str.remove("-"); str = str.remove("+"); str = str.remove(".");
                if( re.exactMatch(str))
                    newItem->setForeground(orange);
                }
            }
        }
    // make table fir the widget
    tableShow->horizontalHeader()->setStretchLastSection(true);
    // make columns fit the contents
    tableShow->setVisible(false);
    tableShow->resizeColumnsToContents();
    tableShow->setVisible(true);

}

void QtHalShow::watchList(QStringList& list)
{
int y, x;
QStringList rowList, lst;
QString str;
QTableWidgetItem *newItem;
QColor red("#FF0000"), green("#008000"), orange("#FF8C00");
QRegExp re("\\d*");  // a digit (\d), zero or more times

    tableWatch->clearContents();
        // this is the best way (undocumented) to remove the rows and leave headers
    tableWatch->model()->removeRows(0, tableWatch->rowCount());
    
    watchingList.append(list);

    //col = QColorDialog::getColor( colour = Qt::green, this);
    for(x = 0; x < watchingList.size(); x++)
        {
        rowList = (watchingList[x]).split(",");
        tableWatch->insertRow(x);
        for(y = 0; y < rowList.size() && y < 2; y++)
            {
            newItem = new QTableWidgetItem();
            newItem->setText(rowList[y]);
            tableWatch->setItem(x,y, newItem);
            if( rowList[y].contains("TRUE") || rowList[y] == "YES" || rowList[y] == "ready")
                newItem->setForeground(green);
            else if( rowList[y].contains("FALSE") || rowList[y] == "NO" || rowList[y] == "initializing")
                newItem->setForeground(red);
            else 
                {
                str = rowList[y];
                str = str.simplified();
                str = str.remove("-"); str = str.remove("+"); str = str.remove(".");
                if( re.exactMatch(str))
                    newItem->setForeground(orange);
                }
            }
        }
    // make table fir the widget
    tableWatch->horizontalHeader()->setStretchLastSection(true);
    // make columns fit the contents
    tableWatch->setVisible(false);
    tableWatch->resizeColumnsToContents();
    tableWatch->setVisible(true);

}



////////////////////////////////////////////////////////////////////////////////////////
// triggers for items clicked in treeHal and Go button for executing HAL commands

void QtHalShow::onGo()
{
QString str, str1;
    // execute hal commands here
    str1 = le_Command->text();
    str = str1.left(str1.indexOf(" "));
    system(str1.toLatin1().constData());
}

void QtHalShow::onItemDoubleClicked(QTreeWidgetItem* item)
{
Q_UNUSED(item)

//    if( (item->text(0)).contains(".ini") )
//        accept();
}

// TODO context menu for add to watch, plus one for delete from watch

void QtHalShow::onItemClicked(QTreeWidgetItem* item, int col)
{
    Q_UNUSED(col)  // will always be 0
    
    if(bShowTab)
        onShowItemClicked(item, false);

}

//////////////////////////////////////////////////////////////////////////////////////////////
// Get the full details for the item / family clicked upon and pass to table

void QtHalShow::onShowItemClicked(QTreeWidgetItem* item, bool watch)
{ 
QStringList list, headerList;
QString name, header;
QTreeWidgetItem *parent;

    if((parent = item->parent()) == NULL)
        header = item->text(0);
    else
        {
        while(parent->parent() != NULL)
            parent = parent->parent();
        header = parent->text(0);
        }
    name = item->text(0);
    
    if((header == "Components" || header == "Functions" || header == "Threads") && watch)
        {
        QMessageBox::information(this, tr("QtHalShow"),
                               tr("The values of Components, Functions and Threads\n"
                                  "are unchanged in the life of a machinekit instance.\n\n"
                                  "Choose a Pin, Parm or Signal to watch.") );
        return;
        }
    
    if(header == "Components")
        {
        _hal->getCompInfo(name, list, true);
        if(list.size())
            {
            headerList.clear();
            headerList << "Name" << "ID" << "Type" << "PID" << "State";
            tableShow->setColumnCount(5);
            tableShow->setHorizontalHeaderLabels(headerList);
            }
        }
    else if(header == "Pins")
        {
        if(watch)
            _hal->getPinInfo(name, list, true, true);
        else
            _hal->getPinInfo(name, list, true);
        
        if(list.size())
            {
            headerList.clear();
            if(watch)
                {
                headerList << "Name" << "Value";
                tableWatch->setColumnCount(2);
                tableWatch->setHorizontalHeaderLabels(headerList);
                }
            else
                {
                headerList << "Owner" << "Name" << "Type" << "Dir" << "Value" << "Net Dir" << "Signal"; // << "";
                tableShow->setColumnCount(7);
                tableShow->setHorizontalHeaderLabels(headerList);
                }
            }
        }
    else if(header == "Parameters")
        {
        if(watch)
            _hal->getParamInfo(name, list, true, true);
        else
            _hal->getParamInfo(name, list, true);
        if(list.size())
            {
            headerList.clear();
            if(watch)
                {
                headerList << "Name" << "Value";
                tableWatch->setColumnCount(2);
                tableWatch->setHorizontalHeaderLabels(headerList);
                }
            else
                {
                headerList << "Owner" << "Name" << "Type" << "Dir" << "Value"; // << "" << "" << "";
                tableShow->setColumnCount(5);
                tableShow->setHorizontalHeaderLabels(headerList);
                }
            }
        }
    else if(header == "Signals")
        {
        if(watch)
            _hal->getSigInfo(name, list, true, true);
        else
            _hal->getSigInfo(name, list, true);
        if(list.size())
            {
            headerList.clear();
            if(watch)
                {
                headerList << "Name" << "Value";
                tableWatch->setColumnCount(2);
                tableWatch->setHorizontalHeaderLabels(headerList);
                }
            else
                {
                headerList << "Name" << "Type" << "Value" << "Dir" << "Pin(s)" << "" << "" << "";
                tableShow->setColumnCount(8);
                tableShow->setHorizontalHeaderLabels(headerList);
                }
            }
        }
    else if(header == "Functions")
        {
        _hal->getFunctInfo(name, list, true);
        if(list.size())
            {
            headerList.clear();
            headerList << "Owner" << "Name" << "CodeAddr" << "Arg" << "FP" << "Users";
            tableShow->setColumnCount(6);
            tableShow->setHorizontalHeaderLabels(headerList);
            }
        }
    else if(header == "Threads")
        {
        _hal->getThreadInfo(name, list, true);
        if(list.size())
            {
            headerList.clear();
            headerList << "Name (+Users)" << "Period" << "FP" << "Time" << "Max-Time";
            tableShow->setColumnCount(5);
            tableShow->setHorizontalHeaderLabels(headerList);
            }
        }

    if(list.size())
        {
        if(watch)
            watchList(list);
        else
            showList(list);
        }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// switching from tableShow to table Watch

void QtHalShow::onCurrentTabChanged(int tab)
{
QStringList headerList;

    //qDebug() << "Tab changed to " << tab ;
    switch(tab)
        {
        case 0: // show tab with default pin headers
            tableShow->setColumnCount(8);
            headerList << "Owner" << "Name" << "Type" << "Dir" << "Value" << "Net Dir" << "Signal" << "";
            tableShow->setHorizontalHeaderLabels(headerList);
            tableShow->horizontalHeader()->setStretchLastSection(true);
            // make columns fit the contents
            tableShow->setVisible(false);
            tableShow->resizeColumnsToContents();
            tableShow->setVisible(true);
            bShowTab = true;
            bWatchTab = false;
            //if(timer != NULL)
              //  timer->stop();
            break;
        case 1: // watch tab
            tableWatch->setColumnCount(2);
            headerList << "Name" << "Value" << "Data Type" << "" << "" << "" << "";
            tableWatch->setHorizontalHeaderLabels(headerList);
            tableWatch->horizontalHeader()->setStretchLastSection(true);
            // make columns fit the contents
            tableWatch->setVisible(false);
            tableWatch->resizeColumnsToContents();
            tableWatch->setVisible(true);
            bShowTab = false;
            bWatchTab = true;
            startTimer();
            break;
        default:
            qDebug() << "Error";
            break;
        }
}

////////////////////////////////////////////////////////////////////////////////
// context menus

void QtHalShow::onContextTree(const QPoint& pos)
{
    selectionItem = treeHal->itemAt( pos );
    
    QMenu *menu = new QMenu(this);
    menu->addAction(actionWatch);
    connect(actionWatch, SIGNAL(triggered()), this, SLOT(onActionWatchTree()));
    menu->popup(treeHal->mapToGlobal(pos) );
}

void QtHalShow::onContextTableWatch(const QPoint& pos)
{
    modelIndex = tableWatch->indexAt(pos);

    QMenu *menu = new QMenu(this);
    menu->addAction(actionRemove);
    connect(actionRemove, SIGNAL(triggered()), this, SLOT(onActionRemove()));
    menu->popup(tableWatch->viewport()->mapToGlobal(pos));
}

//////////////////////////////////////////////////////////////////////////////////
// actions from context menus

void QtHalShow::onActionWatchTree()
{
    if(lastTreeItemText != selectionItem->text(0))
        {
        lastTreeItemText = selectionItem->text(0);
        //qDebug() << "onActionWatchTree()" << "Text " << lastTreeItemText;
        tabWidget->setCurrentIndex(1);
        onShowItemClicked(selectionItem, true);
        disconnect(actionWatch, SIGNAL(triggered()), this, SLOT(onActionWatchTree()));
        }
}


void QtHalShow::onActionRemove()
{
int row, col;
QTableWidgetItem *item;
QStringList blank;
    row = modelIndex.row();
    col = 1; // name only, no matter where in the row is clicked
    
    item = tableWatch->item(row, col);
        
    lastTableItemText = item->text();
    //qDebug() << "onActionRemove()" << "Row " << modelIndex.row() << "Column " << modelIndex.column();
    watchingList.removeAt(row);
    watchList(blank);
    disconnect(actionRemove, SIGNAL(triggered()), this, SLOT(onActionRemove()));
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// called when tableWatch tab is visible to update the content values

void QtHalShow::eventsLoop()
{
int x;
bool changed = false;
QStringList rowList, lst, blank;
QString type, value;
    // get the data for each entry in watchingList
    for( x = 0; x < watchingList.size(); x++)
        {
        rowList = (watchingList[x]).split(",");
        type = rowList[2];
        //qDebug() << "type = " << type;
        if(type == "pin")
            _hal->getPinInfo(rowList[0], lst, true, true);
        else if(type == "param")
            _hal->getParamInfo(rowList[0], lst, true, true);
        else
            _hal->getSigInfo(rowList[0], lst, true, true);
        }
    // any of it changed?
    for( x = 0; x < lst.size(); x++)
        {
        //qDebug() << lst[x];
        if(watchingList[x] != lst[x]) 
            {
            changed = true;
            break;
            }
        }
    // if so replace the contents and force a redraw of the table
    if(changed)
        {
        watchingList.clear();
        watchingList = lst;
        watchList(blank);
        }
    // use a oneshot timer, set once finished, so no danger of overrun
    startTimer();

}