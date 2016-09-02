#include "QtAxis.h"

//////////////////////////////////////////////////////////////////////
// Go pushbutton linked to this

void QtAxis::onReturnMDICommand()
{
QString str;
// copy to list
    str = le_MDI->text();
    if(str.length())
        {
        list_MDI->insertItem(list_MDI->count(), str); 
        listMDITemp.append(str);
        // this should scroll to last entry but doesn't   
        list_MDI->setCurrentRow(list_MDI->count(), QItemSelectionModel::ClearAndSelect);              
        list_MDI->scrollToItem ( list_MDI->item(list_MDI->count()), QAbstractItemView::EnsureVisible );  
        onMDICommand(str);
        }
    
}

///////////////////////////////////////////////////////////////////////
// execute single MDI command
// used per line by runInBackground()

void QtAxis::onMDICommand(QString& str)
{
char lastCommand[80];
QString cstr;

    QStrncpy(lastCommand, str, str.length());
    if((lastCommand)[0] != 0)
        {
        if(!bRun) // want the run loop as fast as pos
            {
            cstr.sprintf("Running MDI Command = %s",lastCommand);
            statusbar->showMessage(cstr);
            _hal->_nml->sendMdi();
            }        
        _hal->_nml->sendMdiCmd(lastCommand);
        }
}

///////////////////////////////////////////////////////////////////////

void QtAxis::onSelectFromMDIList(QListWidgetItem* item)
{
    le_MDI->setText(item->text() );
    le_MDI->setFocus(Qt::OtherFocusReason);
}

///////////////////////////////////////////////////////////////////////

void QtAxis::onMdiClear()
{
    if( QMessageBox::question(this, "Clear MDI History", "This will clear the MDI History list\nContinue?", QMessageBox::Ok) == QMessageBox::Ok )
        {
        list_MDI->clear();
        listMDITemp.clear();
        }
}

//////////////////////////////////////////////////////////////////////


static bool toggle;

void QtAxis::onMdiCopy()
{
QString str;

    if(!toggle)
        {
        if( QMessageBox::question(this, "Copy MDI List Entries", 
                                    "Hold down [Shift] key\nHighlight a contiguous group of entries\nThen press [Copy] again", 
                                    QMessageBox::Ok) == QMessageBox::Ok )
            {
            list_MDI->setSelectionMode(QAbstractItemView::ContiguousSelection);
            toggle = true;
            }
        }
    else
        {
        listStrings.clear();
        QList<QListWidgetItem *> l = list_MDI->selectedItems();
        for(int x = 0; x < l.count(); x++)
            listStrings.append((l[x])->text() );

        QApplication::clipboard()->setText(listStrings.join("\n"));
        
        list_MDI->setSelectionMode(QAbstractItemView::SingleSelection);
        toggle = false;
        }
}

//////////////////////////////////////////////////////////////////////////

void QtAxis::onMdiPaste()
{
QString str;
    // this will insert in list_MDI after current row
    // otherwise can be pasted anywhere as normal
    str = (QApplication::clipboard())->text();
    list_MDI->insertItems(list_MDI->currentRow(), str.split("\n"));
    listMDITemp.append(str.split("\n"));
    
}

/////////////////////////////////////////////////////////////////////////
