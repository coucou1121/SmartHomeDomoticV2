#ifndef GLOBALESTATICVALUE_H
#define GLOBALESTATICVALUE_H

#include <QMap>
#include <QFileDevice>

#include <globalenumerate.h>
#include <DataManager/dataFrame.h>

#define SAVED_PATH_FILE "."
//#define DATA_PATH_FILE "./HomrDomotic/Data"
#define FILE_NAME_SETTING "./HomrDomotic/Setting/settings.ini"


class GlobaleStaticValue
{
public:
    GlobaleStaticValue();

    //Welcome static text
    static QString welcomeText;

    //warning static text
    static QString errorCounterTxt;

    //sensor read interval time in miliseconde
    static quint16 delaiToReadValue;

    //Saved static String
    static QString saveGroupeNameApplicationSettingTxt;
    static QString GraphicReccordTime;
    static QString ADS115_0V_Chan0_ValueInPlus;
    static QString ADS115_0V_Chan1_ValueInPlus;
    static QString ADS115_5V_Chan0_ValueInPlus;
    static QString ADS115_5V_Chan1_ValueInPlus;
    static QString Volume_PID_coef;
    static QString saveIDTxt;
    static QString saveObjectNameTxt;
    static QString saveTitleTxt;
    static QString saveVisibleTxt;
    static QString saveLiquideInsideTxt;
    static QString saveVolumeMaxTxt;
    static QString saveLowLevelWarningTxt;
    static QString saveHeightVMaxValueTxt;
    static QString saveOffsetPressureTxt;

    //saved static date-time format
    static QString saveTimeFormatMinuteTXT;
    static QString saveTimeFormatHourTXT;
    static QString saveTimeFormatDayTXT;
    static QString saveTimeFormatMonthTXT;

    //saved static saved folder
    static QString saveDataMainTxt;
    static QString saveDataMain;

    //saved static temp file
    static QString saveTempFileTxt;
    static QString saveTempFile;

    //setting file
    static QString settingFileTxt;
    static QString settingFile;

    //log file
    static QString logFileTxt;
    static QString logFile;

    //Permission of all files
    static QFileDevice::Permissions filePermissions;

    //saved static plot data file
    static QString savePlotDataFileReadOnly;
    static QString savePlotDataFileWriteOnly;

    //Machine States static text
    static QString stateNotFounded;
    static QString stateFounded;
    static QString stateOnProgramming;
    static QString stateCheckProgramming;
    static QString stateProgrammingSuccessful;
    static QString stateInit;
    static QString stateOnReading;
    static QString stateReady;

    //ADS1115 static text
    static QString ADS1115_1Title;
    static QString ADS1115_2Title;
    static QString ADS1115_Chan0;
    static QString ADS1115_Chan1;
    static QString ADS1115_Chan2;
    static QString ADS1115_Chan3;
    static QString ADS1115_Liter;
    static QString ADS1115_Volt;

    //BME 280 static text
    static QString bme280Title;
    static QString bme280Temperature;
    static QString bme280Humidity;
    static QString bme280Pressure;
    static QString bme280DegCelcuis;
    static QString bme280PerCent;
    static QString bme280Milibar;

    //pressure capteur values
    static quint16 pressureCapteurCoef;
    static quint16 pressureCapteurHeightMaxWater;

    //density kg/m^3
    static double densityWater;
    static double densityOil;
    static double densityOilECO;

    //pressure coeficient ADS1115
    static double pressureCoefWater;
    static double pressureCoefOil;

    //static array

    //tanks TXT object name
    static QString ObjectNameTank1;
    static QString ObjectNameTank2;
    static QString ObjectNameTank3;
    static QString ObjectNameTank4;
    static QString ObjectNameTank5;
    static QString ObjectNameTank6;

    //TankObjectName
    /**
      * \struct  TankObjectName
      * \brief Array for all tank object name possible
      *
      * Linked the E_TankObjectName to the objectName
      * Use the objectName as groupe for saving the data
    */
    static QMap<int, QString> TankObjectName;

    //HomeViewObject
    /**
      * \struct  HomeViewObject
      * \brief Array for all home view object
      *
      * Linked the E_TankObjectName to the objectName
      * Use the objectName as groupe for saving the data
    */
    static QMap<int, QString> HomeViewObject;

    // init array for external use

    // initTankObjectName
    /**
      * \func  initTankObjectName
      * \brief init the array for all tank object name possible
      *
      * static function to init the array for all tank object name possible
    */
    static QMap<int, QString> initTankObjectName();

    //TankObjectName
    /**
      * \func  initErrorPossible
      * \brief init the array for all possible error on application
      *
      * static function to init the array for all tank object name possible
    */
    static QMap<int, QString> initErrorPossible();

    // initHomeViewObject
    /**
      * \func  initHomeViewObject
      * \brief init the array for all home view object
      *
      * static function to init the array for all tank object name possible
    */
    static QMap<int, QString> initHomeViewObject();
};

#endif // GLOBALESTATICVALUE_H
