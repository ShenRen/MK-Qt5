#ifndef _HAL_ACCESS_H_
#define _HAL_ACCESS_H_

#include "LCNC_Headers.h"

#include "NML_Access.h"


//#ifndef EMC_INIFILE
//#define EMC_INIFILE DEFAULT_EMC_INIFILE
//#endif

// These are used as the basic data units for any pins created
// via the functions in this class
typedef struct {
  hal_bit_t *pin;
} bit_data_t;

typedef struct {
  hal_s32_t *pin;
} s32_data_t;

typedef struct {
  hal_float_t *pin;
} float_data_t;

#define ARRAY_SIZE 50   // default max number of pins in an array
#define NAME_LEN 30     // default max len of new pin



class HAL_Access : public QObject
{

    Q_OBJECT
public:

    HAL_Access(int argc, char **argv, QString& compname, bool inifile);

    void engage();
    void disEngage();
    int reEngage(QString& compname);    

    char* getIniFileName();
    int getID();
    void cleanUp();

    int comp_id;
    int done;
    // name of component in pin name
    char prefix[80];
    
    NML_Access *_nml;

////////////  Local pins and params commands  
 //////////////////////////////////////////////////////////// 

// These create and get / set values of local pins, ie those belonging to the component created when
// _hal = new HAL_Access(argc, argv, "hal-test"); is called
// in this instance the component name is hal-test and this prefixes all pin names

// Pins
    char lname[80];
    char l2name[80];
    
    int createBitPin(QString&, bool);
    int createS32Pin(QString&, bool);
    int createFloatPin(QString&, bool); 

    bool getBitPinValue(QString&); // by name
    bool getBitPinValue(int); // overloaded, by index

    void setBitPinValue(QString&, bool); // by name
    void setBitPinValue(int, bool); // overloaded, by index    

    signed int getS32PinValue(QString&); // by name
    signed int getS32PinValue(int); // overloaded, by index

    void setS32PinValue(QString&, signed int); // by name
    void setS32PinValue(int, signed int); // overloaded, by index    ////////////  Local component variables and data   /////////////////////////////////

    float getFloatPinValue(QString&); // by name
    float getFloatPinValue(int); // overloaded, by index

    void setFloatPinValue(QString&, float); // by name
    void setFloatPinValue(int, float); // overloaded, by index   
// Params
    int createBitParam(QString& name, bool rw);
    int createS32Param(QString& name, bool rw);
    int createFloatParam(QString& name, bool rw);
     
    bool getBitParamValue(QString&); // by name
    bool getBitParamValue(int); // overloaded, by index

    void setBitParamValue(QString&, bool); // by name
    void setBitParamValue(int, bool); // overloaded, by index    

    signed int getS32ParamValue(QString&); // by name
    signed int getS32ParamValue(int); // overloaded, by index

    void setS32ParamValue(QString&, signed int); // by name
    void setS32ParamValue(int, signed int); // overloaded, by index    
    
    float getFloatParamValue(QString&); // by name
    float getFloatParamValue(int); // overloaded, by index

    void setFloatParamValue(QString&, float); // by name
    void setFloatParamValue(int, float); // overloaded, by index        
    // Used when creating pins
    // arrays of data* with arrays of names to match the index
    //   *(bit_data[bit_index])->pin = lvalue assigns

// Access arrays    
    bit_data_t* bit_data[ARRAY_SIZE];
    s32_data_t* s32_data[ARRAY_SIZE];
    float_data_t* float_data[ARRAY_SIZE];
    
    hal_bit_t* bit_param_data[ARRAY_SIZE];
    hal_s32_t* s32_param_data[ARRAY_SIZE];
    hal_float_t* float_param_data[ARRAY_SIZE];
    
    //     if(strcmp((char*)float_name[y], name) == 0) finds name
    
    char bit_name [ARRAY_SIZE][NAME_LEN];
    char s32_name [ARRAY_SIZE][NAME_LEN];
    char float_name [ARRAY_SIZE][NAME_LEN];

    char bit_param_name [ARRAY_SIZE][NAME_LEN];
    char s32_param_name [ARRAY_SIZE][NAME_LEN];    
    char float_param_name [ARRAY_SIZE][NAME_LEN];
    
    int bit_index;      // index to the relevant array, left at last entry so size is known
    int s32_index;
    int float_index;  

    int bit_param_index;
    int s32_param_index;
    int float_param_index;
 
/////////////////////////////////////////////////////////////////////////////////////

//  These work on the locally indexed pins and params created for this comp_id
//  Just use to zero initially then set values with main functions above

    void zeroAllBitPin();
    void zeroAllS32Pin();
    void zeroAllFloatPin();
    
    void zeroAllBitParam();
    void zeroAllS32Param();
    void zeroAllFloatParam();
 
 
////////////////////////////////////////////////////////////////////////////////

// these are specific hal calls rather that setP()

    int setBitParam(QString& name, int value);
    int setFloatParam(QString& name, double value);
    int setS32Param(QString& name, signed long value);

// general set pin or param    
    int setPValue(QString& name, QString& value);
    int getPValue(QString& name, QString& value);  
    
    int setSignalValue(QString& name, QString& value);
    int getSignalValue(QString& name, QString& value);

/////////////  HAL pin / signal / param commands  //////////////////////////////////
     
//    int startThreads(void);
//    int stopThreads(void);
    
    int createSignal(QString& name, hal_type_t type);
    int deleteSignal(QString& name);
    int linkPin2Signal(QString& pin, QString& sig);
    int unlinkPin2Signal(QString& name);
    
    int netSignalPin(QString& signal,  QStringList& pins);  
    
    int addFunc2Thread(QString& func, QString& thread);
    int removeFunc2Thread(QString& func, QString& thread);

    int setLockOn(QString& command);
    int setLockOff(QString& command);

//////////////  Hal Info functions  ////////////////////////////////////////////////////////////

    void getAllComponentNames(QStringList& list);
    void getAllParamNames(QStringList& list);
    void getAllFuncNames(QStringList& list);
    void getAllThreadNames(QStringList& list);            
    void getAllPinNames(QStringList&);
    void getAllPinAliases(QStringList& list);
    void getAllSignals(QStringList& list);

    void getMemoryStatus(QStringList& list);
    void getLockStatus(QStringList& list);
    void getCompInfo(char **patterns, QStringList& list,  bool csv);
    void getPinInfo(char **patterns, QStringList& list, bool csv);
    void getSigInfo( char **patterns, QStringList& list, bool csv);
    void getParamInfo(char **patterns, QStringList& list, bool csv);
    void getFunctInfo(char **patterns, QStringList& list, bool csv);
    void getThreadInfo(char **patterns, QStringList& list);
    
// helper functions

    int tmatch(int req_type, int type);
    int match(char **patterns, char *value); 
    const char *pin_data_dir(int dir);
    const char *data_type2(int type);
    const char *data_arrow2(int dir);
    int count_list(int list_root);
    const char* data_type(int type);
    const char* param_data_dir(int dir);
    const char* data_arrow1(int dir);
    char * data_value(int type, void *valptr);
    char * data_value2(int type, void *valptr);
    int checkNet(QString& signal, hal_sig_t *sig, QStringList& pins) ;

//  convert QString to char* in lname mostly
    void QStrncpy(char* str, QString& qstr, int num);
 
};



#endif
