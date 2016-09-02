#ifndef _NML_ACCESS_H_
#define _NML_ACCESS_H_

#include "LCNC_Headers.h"

#define MDI_MAX 64



#define CLOSE(a,b,eps) ((a)-(b) < +(eps) && (a)-(b) > -(eps))
#define LINEAR_CLOSENESS 0.0001
#define ANGULAR_CLOSENESS 0.0001
#define INCH_PER_MM (1.0/25.4)
#define CM_PER_MM 0.1
#define GRAD_PER_DEG (100.0/90.0)
#define RAD_PER_DEG TO_RAD	


#define RETRY_TIME 10.0		// seconds to wait for subsystems to come up
#define RETRY_INTERVAL 1.0	// seconds between wait tries for a subsystem
#define EMC_COMMAND_DELAY   0.1	// how long to sleep between checks
//#define EMC_COMMAND_TIMEOUT 1.0 // how long to wait until timeout


class NML_Access: public QObject
{
    Q_OBJECT
public:

    NML_Access();


/////  User interface commands  //////////////////////////////
    
    int getNumAxes();
    QString getCoordinates();
    bool isHomeAll();
    
    int sendMachineOn();
    int sendMachineOff();
    int sendEstop();
    int sendEstopReset();
    int sendManual();
    int sendAuto();
    int sendMdi();
    int sendMdiCmd(char*);
    int sendMdiCommand(int );
    int sendTeleop();
    int sendJoint();
    int sendMistOn();
    int sendMistOff();
    int sendFloodOn();
    int sendFloodOff();
    int sendLubeOn();
    int sendLubeOff();
 
    int sendSynch();
    int sendProgramRun(int line);
    int getCurrentLine();
    int getMotionLine();
    int getReadLine();
    int sendProgramPause();
    int sendSetOptionalStop(bool);
    int sendSetBlockDelete(bool);
    int sendProgramResume();
    int sendProgramStep();
    
    int sendSpindleForward();
    int sendSpindleReverse();
    int sendSpindleOff();
    int sendSpindleIncrease();
    int sendSpindleDecrease();
    int sendSpindleConstant();

    int sendBrakeEngage();
    int sendBrakeRelease();
 
    int sendHome(int);
    int sendHomeAll();
    int sendUnhome(int );

    int sendAbort();
    int sendJogStop(int);
    int sendJogCont(int, double );
    int sendJogInc(int , double , double);
    int sendFeedOverride(double );
    int sendMaxVelocity(double );
    int sendSpindleOverride(double );
    
    int sendToolSetOffset(int toolno, double zoffset, double diameter);
    int sendOverrideLimits();
    int sendTaskPlanInit();
    int sendProgramOpen(char *program);
//    int sendProgramRun(int line);
//    int sendProgramPause();
//    int sendProgramResume();
//    int sendProgramStep();
    int sendLoadToolTable(const char *file);    
 
    int getMode(); // 0 = manual 1 = mdi 2 = auto -1 = error
    void setMode(int mode); // 0 = manual 1 = mdi 2 = auto
    
    bool isEstopOn();
    bool isMachineOn();
    
    bool isJointMode();
    bool isMist();
    bool isFlood();
    bool isLube();

    QString getProgramName();
    bool isProgramPaused();
    bool isProgramRunning();
    bool isProgramIdle();
    bool isProgramOptionalStopOn();
    bool isProgramBlockDeleteOn();
    
    unsigned int getToolNumber();
    float getToolOffsetX();
    float getToolOffsetY();
    float getToolOffsetZ();        
    float getToolOffsetA();
    float getToolOffsetB();
    float getToolOffsetC();
    float getToolOffsetU();                
    float getToolOffsetV();
    float getToolOffsetW();
    
    unsigned int getSelectedJoint();
    float getFeedOverride();
    float getSpindleOverride();    
    float getMaxVelocity();

    bool isSpindleOn();
    bool isSpindleBrakeOn();
    bool isSpindleForward();
    bool isSpindleReverse();
    
    float getCommandedPosition(int);    // will return 9999.9999 if error
    float getActualPosition(int);       // will return 9999.9999 if error
    float getRelativePosition(int);     // will return 9999.9999 if error
    
    QString getActiveGCodes();
    QString getActiveMCodes();
    QString getActiveSettings();
    
    bool isHomed(int joint);
    bool isOnSoftMinLimit(int);
    bool isOnSoftMaxLimit(int);
    bool isOnHardMinLimit(int);
    bool isOnHardMaxLimit(int);
    bool isFaulted(int);
 
    
    // the NML channels to the EMC task
    RCS_CMD_CHANNEL *emcCommandBuffer;
    RCS_STAT_CHANNEL *emcStatusBuffer;
    EMC_STAT *emcStatus;
   // EMC_TASK_STAT *emcTaskStatus;  // use emcStatus->task.????
    
    // the NML channel for errors
    NML *emcErrorBuffer;

    int emcCommandSerialNumber;

    void printError(const char *error);
    
    char *mdi_commands[MDI_MAX];
    int num_mdi_commands;
    int have_home_all;
    int num_axes;
    double maxFeedOverride;
    double maxMaxVelocity;
    double minSpindleOverride;
    double maxSpindleOverride;

    EMC_TASK_MODE_ENUM halui_old_mode;
    int halui_sent_mdi;
    
    // default value for timeout, 0 means wait forever
    // use same timeout value as in tkemc & mini
    double receiveTimeout;
    double doneTimeout;
    

    
///////////////  Private NML functions   //////////////////////////////////////////////

    // programStartLine is the saved valued of the line that
    // sendProgramRun(int line) sent
    int programStartLine;
    int programStartLineLast;
    int tryNml();

    int emcTaskNmlGet();
    int emcErrorNmlGet();
    int updateStatus();
    int updateError();
    
    int emcCommandWaitReceived(int );
    int emcCommandWaitDone(int );
    
    
    int iniLoad(const char*);
    void cleanUp();
    
    // string for ini file version num
    QString version_string;

    // interpreter parameter file name, from ini file
    QString PARAMETER_FILE;

    // help file name, from ini file
    QString HELP_FILE;

    QString ui_file;
    QString hal_file;
    
    // the program path prefix
    QString programPrefix;

    // the program name currently displayed
    QString programFile;

    // the program last loaded by the controller
    QString lastProgramFile;

    QString active_g_codes;
    QString active_m_codes;
    QString active_settings;
    
    QString error_string;
    
    QString coordinates;
    int coords;
    int posDisplay;

    int axisJogging;

    // current jog speed setting
    int jogSpeed;
    int maxJogSpeed;
    int jogSpeedChange;

    // current jog increment setting, non-positive means continuous
    double jogIncrement;

    // the size of the smallest increment to jog, = 1/INPUT_SCALE
    double stepIncrement;

    // polarities for axis jogging, from ini file
    int jogPol[3];

    int oldFeedOverride;
    int feedOverride;   
    int feedOverrideChange;
    // timer delays until dec/inc appears
    int feedOverrideDelayCount;
    void QStrncpy(char* str, QString& qstr, int num);
};

#endif
