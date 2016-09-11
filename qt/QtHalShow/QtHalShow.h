#ifndef QTHALSHOW_H
#define QTHALSHOW_H

#include <QtGui>
#include <QSettings>
#include <QCoreApplication>
#include <QAction>
#include <QMenu>

#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>

#include "HAL_Accessp.h"

#include "ui_halshow.h"


class QtHalShow : public QDialog , private Ui_QtHalShowDlg
{
    Q_OBJECT

public:
     QtHalShow(QWidget* parent = 0);
    ~ QtHalShow();

private:
    HAL_Access *_hal;
    
    QTimer *timer;
    void startTimer();
    
    int comp_id;
    QString prefix;
    
    QStringList tab1List;
    QStringList tab2List;
    QStringList headerList;
    
    //QAction *actionKeep;
    QAction *actionRemove;
    QAction *actionWatch;
    
    QModelIndex modelIndex;  // last context menu modelindex item in tableWatch
    QTreeWidgetItem *selectionItem;
    QString lastTableItemText;
    QString lastTreeItemText;
    QStringList watchingList;
    
    void addGroups(QTreeWidgetItem*, QStringList& , QStringList&, QStringList&, int);
    void addSubGroups(QTreeWidgetItem*, QString& name, QStringList&, QStringList&);
    void addGroupChildren(QTreeWidgetItem*, QString&, QStringList&, bool subgroup);
    void showList(QStringList&);
    void watchList(QStringList&);
    
    void fillTree();
    int createPins();

    bool bShowTab;
    bool bWatchTab;

    void reject();
    
private slots:
    virtual void onGo();
    virtual void onCurrentTabChanged(int);

    virtual void onItemClicked(QTreeWidgetItem*, int);
    virtual void onShowItemClicked(QTreeWidgetItem*, bool watch);

    virtual void onItemDoubleClicked(QTreeWidgetItem*);
    
    virtual void onContextTree(const QPoint&);
    virtual void onContextTableWatch(const QPoint&);
    //virtual void onContextTableShow(const QPoint&);
    
    virtual void onActionRemove();
    virtual void onActionWatchTree();
    //virtual void onActionWatchTable();
    
    virtual void eventsLoop();
};


#endif
