#ifndef QT_POPIMAGE_H
#define QT_POPIMAGE_H

#include <QtWidgets>
#include <QtGui>
#include <QSettings>
#include <QCoreApplication>

class QtPopImage : public QWidget
{
Q_OBJECT

public:
    explicit QtPopImage(int argc = 0, char **argv = NULL, QWidget *parent = 0);
    ~QtPopImage();

private:
    int delay;

private slots:
    virtual void onTimer();

};



#endif
