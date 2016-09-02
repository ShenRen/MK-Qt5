
#ifndef CHOOSER_H
#define CHOOSER_H

#include <QtGui>
#include <QSettings>
#include <QCoreApplication>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>


#include "ui_chooser.h"


class qtChooserDlg  : public QDialog , private Ui_ChooserDlg
{
    Q_OBJECT
public:
    qtChooserDlg();

private:

    QSettings *settings;
    QString selection;
    QString lastFile;
    QString selectionGParentName;
    QString selectionParentName;
    QString selectionName;
    QString homeDir;
    QString mkHome;

    QTreeWidgetItem *selectionItem;

    void writeSettings();
    void readSettings();
    void getLastSelected();

    QTreeWidgetItem* addChildren(QTreeWidgetItem* ,QString );
    void addParents(QTreeWidgetItem*, QFileInfoList& );
    QString getFullPath(QTreeWidgetItem* item);

private slots:

   virtual void onItemClicked(QTreeWidgetItem* item, int col);
   virtual void onItemDoubleClicked(QTreeWidgetItem* item, int col);
   virtual void onFinished(int code);
};


#endif
