#ifndef QTSHOWERROR_H
#define QTSHOWERROR_H

#include <QWidget>
#include <QtGui>
#include <QSettings>
#include <QCoreApplication>
#include <QtDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>

#include <unistd.h>
#include <sys/types.h>

#include "ui_show_error.h"

class QtShowError : public QDialog , private Ui_QtShowError
{
    Q_OBJECT

public:
    explicit QtShowError(int argc = 0, char **argv = NULL, QWidget *parent = 0);
    ~QtShowError(){}

private:
    void load(QString& filename, QTextBrowser *browser);
};

#endif // QTSHOWERROR_H
