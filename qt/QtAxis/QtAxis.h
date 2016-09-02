
#ifndef QTCNC_H
#define QTCNC_H

#include <QtGui>
#include <QSettings>
#include <QCoreApplication>
#include <QtDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "HAL_Access.h"
#include "ui_axis.h"
#include "touch-off_dlg.h"
#include "recent_files_dialog.h"
#include "code_editor.h"
#include "gremlindlg.h"

#define MAX_AXES 9

class QtAxis  : public QMainWindow , private Ui_QtAxis
{
    Q_OBJECT
public:

    QtAxis(int argc, char** argv);
    void closeEvent(QCloseEvent * event);  // redefine inherited function from QWidget to control exit

    void setupExtra();
    void setupGremlin();

    void startTimer(int);
    void makeConnections();

private:

    HAL_Access *_hal;

    QString prefixName;
    QString iniFile;

    WId id;
    QWidget* container;

    int gremlin_width;
    int gremlin_height;
    int gremlin_Xoffset;
    int gremlin_Yoffset;
    QProcess *gremlinProcess;
    
//    bool bGremlin;
    bool bGremlinRunning;

    //bool bStopOnError;

    bool bEstop;
    bool bMachine;
    bool bRun;
    bool bPause;
    bool bStep;
    bool bDirect;
    bool started;
    bool bLoadChanged;
    bool bBigFile;
    bool bMoreBig;
    qint64 filePos;
    qint64 fileSize;

    bool bHomeAll;
    bool bHomeStateChanged;
    
    bool bDRO;
    bool bGCode;
    bool bManual;
    bool bMDI;

    void QStrncpy(char* str, QString& qstr, int num);
    bool allHomed();

    QString axesList;
    int numAxes;
    char currentAxis;
    int currentAxisIndex;

    int jogSpeed;
    int maxJogSpeed;
    bool bJogging;

    double currentVelocity;
    double maxVelocity;

    double feedOverride;
    double maxFeedOverride;

    int startLine;
    int oldStartLine;
    int currentLine;
    int oldCurrentLine;

    int spare;

    int chunkIndex;
    int listIndex;

    QRadioButton *buttonArray[MAX_AXES];
    QLabel *axisLabelArray[MAX_AXES];
    QLabel *axisG54Array[MAX_AXES];
    QLabel *axisG53Array[MAX_AXES];
    char axisArray[MAX_AXES];
    bool axisHomedArray[MAX_AXES];

    QStringList pinNameListAbs;
    QStringList signalNameListAbs;

    QStringList pinNameListRel;
    QStringList signalNameListRel;

    QStringList coordList;

    QTimer *droTimer;
    QTimer *refreshTimer;


    
    QString openFile;
    QString lastFile;
    QStringList listStrings;


    QStringList listMDITemp;
    QStringList listRecentFiles;

    // _nml->sendMdiCmd(char*) is very picky
    // it will accept a const string or a real char array
    // but not QString.data()
    char lastCommand[80];

    QSettings *settings;
    void readSettings();
    void writeSettings();

    int openInBrowser(QString& filename);
    int saveInBrowser(QString& filename);
//    void querySave();

    // Action funcs
    void estopOff();
    void estopOn();
    void machineOn();
    void machineOff();

    void runEnable(bool onoff);

private:

    
//    void runInBackground();
//    int reOpenInBrowser();

    void checkErrors();


    void setupPins();
    
private slots:
    virtual void onCloseDown();
    virtual void onExitPressed();

    virtual void onRunFromContext(int line = 1);
    
    virtual void onRunProgram(int line = 1);
    virtual void onRunFrom(int line = 1);
    virtual void pauseProgram();
    virtual void stepProgram();
    virtual void stopProgram();

    virtual void onToggleEstop();
    virtual void onToggleMachine();

    virtual void onAxis(bool);
    virtual void onHome();
    virtual void onUnReHome();

    virtual void onTouchOff();

    virtual void onJogXPlus(){ onJogPlus(0); }
    virtual void onJogXMinus(){ onJogMinus(0); }
    virtual void onJogXOff(){ onJogOff(0); }
    virtual void onJogYPlus(){ onJogPlus(1); }
    virtual void onJogYMinus(){ onJogMinus(1); }
    virtual void onJogYOff(){ onJogOff(1); }
    virtual void onJogZPlus(){ onJogPlus(2); }
    virtual void onJogZMinus(){ onJogMinus(2); }
    virtual void onJogZOff(){ onJogOff(2); }

    virtual void onJogMinus(int);
    virtual void onJogPlus(int );
    virtual void onJogOff(int );

    virtual void onJogSliderChanged(int);
    virtual void onFeedSliderChanged(int);
    virtual void onVelocitySliderChanged(int);

    virtual void onTabViewChanged(int);
    virtual void onTabControlChanged(int);

    virtual void updateDRO();
    virtual void refresh();

    virtual void onMDICommand(QString& str);
    virtual void onReturnMDICommand();
    virtual void onSelectFromMDIList(QListWidgetItem*);
    virtual void onMdiClear();
    virtual void onMdiCopy();
    virtual void onMdiPaste();

    virtual void onAboutQtAxis();
    virtual void onAboutQt();

    virtual void onOpenFile();
    virtual void onReloadFile();
    virtual void onRecentFiles();
    virtual void onLoadLast();

    virtual void onGremlin();

    virtual void onClearMessages();
    //virtual void onStopOnError();


};




#endif
