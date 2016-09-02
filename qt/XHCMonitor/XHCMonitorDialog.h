#ifndef XHC_MONITOR_H
#define XHC_MONITOR_H

#include <QtGui>
#include <QSettings>
#include <QCoreApplication>


#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>

#include "HAL_Access.h"

#include "ui_XHCMonitorDialog.h"

struct __comp_state
    {
    hal_bit_t *homed;
    hal_bit_t *machineon;
    hal_bit_t *finished;
    };


class XHCMonitorDialog : public QDialog , private Ui_XHCMonitorDialog
{
    Q_OBJECT

public:
    XHCMonitorDialog(QWidget* parent = 0, int argc = 0, char **argv = NULL);
    ~XHCMonitorDialog();
    
private:
    HAL_Access *_hal;

    QTimer *timer;
    int comp_id;
    int progress;
    QString prefix;

    struct __comp_state *inst;
    
    void getSettings();
    int createPins();
    int connectPins();
    void startTimer();
    bool bFirstRun;
    bool bRequirePendant;
    bool bConnected;
    bool bHidden;
    
    // settings
    QString iniFile;
    int layout;
    int sequence;
    int coordsNum;
    QString jogmode;
    QString threadname;
    int coefs[4];
    int scales[4];
    char coords[4];
    // button settings
    QString go_to_zero;
    QString start_pause;
    QString rewind;
    QString probe_z;
    QString macro_3;
    QString half;
    QString zero;
    QString safe_z;
    QString home;
    QString macro_1;
    QString macro_2;
    QString spindle;
    QString step;
    QString mode;
    QString macro_6;
    QString macro_7;
    QString stop;
    QString reset;

    void showList(QStringList& list);

// in hal_info.cpp
//    void QStrncpy(char* , QString& , int );
//    const char* data_type(int type);
//    const char* pin_data_dir(int dir);
//    const char* param_data_dir(int dir);
//    const char* data_arrow1(int dir);
//    char* data_value(int type, void *valptr);
//    int get_common(hal_type_t type, void *d_ptr, QString& value);
//    int getPValue(QString& name, QString& value);
//    void getPinInfo(QString& name, QStringList& list);

private slots:
    virtual void onHide();
    virtual void onShowXHCPins();
    virtual void onShowUtilPins();
    virtual void onShowHaluiPins();
    virtual void onMonitor();
    virtual void eventsLoop();
};


#endif
