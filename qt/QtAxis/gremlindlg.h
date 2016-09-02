
#ifndef GREMLIN_DLG_H
#define GREMLIN_DLG_H

#include <QtGui>
#include <QSettings>
#include <QCoreApplication>


#include "ui_gremlinDlg.h"


class gremlinDlg  : public QDialog , private Ui_gremlinDlg
{
    Q_OBJECT
public:

    gremlinDlg(QWidget* parent, int w, int h, int x, int y);
    int width;
    int height;
    int xoffset;
    int yoffset;
private:

private slots:
    virtual void onAccept();
};


#endif
