#ifndef GLOBALENUMATEDANDEXTERN_H
#define GLOBALENUMATEDANDEXTERN_H

//*

/**
  * \file globalEnumatedAndExtern.h
  * \author Sébastien Blessemaille
  * \version 1.0
  * \date 17 septembre 2017
  * \brief All enumarate and externe variables
  */

#include <QObject>
#include <QString>
#include <QMap>
#include <QMetaType>
#include <QQmlEngine>

class GlobalEnumatedAndExtern : public QObject
{

    Q_OBJECT

private:

public:
    //    /**
    //      * \fn GlobalEnumatedAndExtern();
    //      * \brief constructor for GlobalEnumatedAndExtern
    //      */
    //    GlobalEnumatedAndExtern();



    //    //application main state possible
    //    /**
    //      * \struct  eMainStateApplication
    //      * \brief structure of the main application states
    //      *
    //      * Is for the main state graph
    //      */
    //    typedef enum
    //    {
    //        mainStateInit = 0,  /*!< initialisation status */
    //        mainStateStop,      /*!< stop status */
    //        mainStateReady,     /*!< ready status */
    //        mainStateSet,       /*!< set status */
    //        mainStateTrig,      /*!< trig status */
    //        mainStateRoll,      /*!< roll status */
    //        mainStateDebug      /*!< debug status */
    //    }eMainStateApplication;

    //    //application trig state possible
    //    /**
    //      * \struct  eTrigState
    //      * \brief structure of the trigger states
    //      *
    //      * Is for the trigger state graph
    //      */
    //    typedef enum
    //    {
    //        trigNotReady = 0,   /*!< not ready status*/
    //        trigReady,          /*!< ready status*/
    //        trigRunTrig,        /*!< run trig status*/
    //        trigTrigged,        /*!< trigged status*/
    //    }eTrigState;

    //    //application Roll state possible
    //    /**
    //      * \struct  eRollState
    //      * \brief structure of the roll states
    //      *
    //      * Is for the roll state graph
    //      */
    //    typedef enum
    //    {
    //        rollNotReady = 0,   /*!< not ready status*/
    //        rollReady,          /*!< ready status*/
    //        rollRollOn,         /*!< roll on status*/
    //        rollPaused,         /*!< paused status*/
    //    }eRollState;

    //    //display state possible
    //    /**
    //      * \struct  eMainStateDisplay
    //      * \brief structure of the display status possible
    //      *
    //      * Is for the status display
    //      */
    //    typedef enum
    //    {
    //        init = 0,   /*!< Init display*/
    //        stopped,    /*!< Stopped display*/
    //        ready,      /*!< Ready display*/
    //        runTrig,    /*!< Run trig display*/
    //        trigged,    /*!< Trigged display*/
    //        rollOn,     /*!< Roll on display*/
    //        paused      /*!< Paused display*/
    //    }eMainStateDisplay;

    //    QString BPMenuHomeTxt;
    //    QString BPMenuSetTxt;
    //    QString BPMenuTrigTxt;
    //    QString BPMenuRollTxt;
    //    QString BPMenuDebugTxt;

    //    //startStop button state possible
    //    /**
    //      * \struct  eBPStartStopState
    //      * \brief structure of the main button state
    //      *
    //      * Is for the text display in on the main push button
    //      */
    //    typedef enum
    //    {
    //        stop,   /*!< Stop display*/
    //        start,  /*!< Start display*/
    //        hold    /*!< Hold display*/
    //    }eBPStartStopState;

    //    QString BPStartStopStateStartTxt;
    //    QString BPStartStopStateStopTxt;
    //    QString BPStartStopStateHoldTxt;

    //    //Error Possible
    //    // from the Highest priority is at the top after noError
    //    /**
    //      * \struct  eError
    //      * \brief structure of all error possible
    //      *
    //      * The Highest priority message will be displaying and it's at the top after noError
    //      */
    //    typedef enum
    //    {
    //        noError = 0,                    /*!< no Error */
    //        errorFTDIDeviceNotFound,        /*!< FTDI Error */
    //        errorSamplingFrequencyToHigh,   /*!< Sampling frequency is to High */
    //        errorNoSelectedTrace,           /*!< No traces are selected */
    //        errorNoSelectedTriggerTrace,    /*!< No trigger traces are selected */
    //        errorWrongEquation              /*!< Incorrect configuration of equation */
    //    }eError;


    //    static QMap<int, QString> initErrorPossible();

    //    //trace range
    //    /**
    //      * \struct  eRangeValue
    //      * \brief structure of all voltage range possible
    //      *
    //      * This is the possible range for the signal
    //      */
    //    typedef enum
    //    {
    //        range0_24 = 0,  /*!< range 0 to 24Vdc */
    //        range0_30,      /*!< range 0 to 40Vdc */
    //        range15_15      /*!< range -15Vdc to 15Vdc */
    //    }eRangeValue;

    //    QString range0_24Txt;
    //    QString range0_30Txt;
    //    QString range15_15Txt;

    //    //edge type
    //    /**
    //      * \struct  eEdge
    //      * \brief structure of all possible edge possible
    //      *
    //      * Can be selected in trigger setting window
    //      */
    //    typedef enum
    //    {
    //        noEdge = 0,     /*!< no edge */
    //        fallingEdge,    /*!< falling edge */
    //        risingEdge      /*!< rising edge */
    //    }eEdge;

    //    //Equation operator possible
    //    /**
    //      * \struct  eLogicOperator
    //      * \brief structure of all logical operator possible
    //      *
    //      * Can be selected in trigger function window
    //      */
    //    typedef enum
    //    {
    //        opNone = 0,     /*!< no operator */
    //        opAnd,          /*!< logical operator AND */
    //        opOr,           /*!< logical operator OR */
    //        opAndNot,       /*!< logical operator AND NOT */
    //        opOrNot         /*!< logical operator OR NOT */
    //    }eLogicOperator;

    //    QString opNoneTxt;
    //    QString opOrTxt;
    //    QString opAndTxt;
    //    QString opNotOrTxt;
    //    QString opNoTAnd;

    //    //button in setting windows
    //    /**
    //      * \struct  eTracePossible
    //      * \brief structure of all trace possible
    //      *
    //      * Can be selected in channels setting window
    //      */
    //    typedef enum
    //    {
    //        btNone = 0,     /*!< no trace */
    //        btDI1,          /*!< trace DI1 */
    //        btDI2,          /*!< trace DI2 */
    //        btDI3,          /*!< trace DI3 */
    //        btDI4,          /*!< trace DI4 */
    //        btDI5,          /*!< trace DI5 */
    //        btDI6,          /*!< trace DI6 */
    //        btDI7,          /*!< trace DI7 */
    //        btDI8,          /*!< trace DI8 */
    //        btDI9,          /*!< trace DI9 */
    //        btDI10,         /*!< trace DI10 */
    //        btDI11,         /*!< trace DI11 */
    //        btDI12,         /*!< trace DI12 */
    //        btDI13,         /*!< trace DI13 */
    //        btDI14,         /*!< trace DI14 */
    //        btDI15,         /*!< trace DI15 */
    //        btDI16,         /*!< trace DI16 */
    //        btAI1,          /*!< trace AI1 */
    //        btAI2,          /*!< trace AI2 */
    //        btAI3,          /*!< trace AI3 */
    //        btAI4,          /*!< trace AI4 */
    //        functionResult  /*!< trigger trace TR1*/
    //    }eTracePossible;

    //    //periode possible for saved time
    //    /**
    //      * \struct  ePeriodePossible
    //      * \brief structure of all periode possible
    //      *
    //      * Can be selected in Time scale factor window
    //      */
    //    typedef enum
    //    {
    //        periode0_5_microsec = 0,    /*!< 0,5 microseconds */
    //        periode1_microsec,          /*!< 1 microseconds */
    //        periode50_microsec,         /*!< 50 microseconds */
    //        periode100_microsec,        /*!< 100 microseconds */
    //        periode1_ms,                /*!< 1 miliseconds */
    //        periode5_ms,                /*!< 5 miliseconds */
    //        periode10_ms,               /*!< 10 miliseconds */
    //        periode50_ms,               /*!< 50 miliseconds */
    //        periode100_ms,              /*!< 100 miliseconds */
    //        periode500_ms,              /*!< 500 miliseconds */
    //        periode1_s,                 /*!< 1 second */
    //        periode5_s,                 /*!< 5 second */
    //        periode10_s                 /*!< 10 second */
    //    }ePeriodePossible;

    //    //FTDI state possible
    //    /**
    //      * \struct  eFTDIStatePossible
    //      * \brief structure of all FTDI state possible
    //      *
    //      * Use to display the status as message and check the FTDI status
    //      */
    //    typedef enum
    //    {
    //        FTDInotConnected = 0,           /*!< FTDI not conneted */
    //        FTDIDeviceFound,                /*!< FTDI not found */
    //        FTDIopened,                     /*!< FTDI not opened */
    //        FTDIUSBparameterSetted,         /*!< FTDI USB parameter setting was failed */
    //        FTDIBaudRateSetted,             /*!< FTDI baudrate parameter setting was failed */
    //        FTDIDataCaracteristiqueSetted,  /*!< FTDI data characteristic setting was failed */
    //        FTDIFlowControlSetted,          /*!< FTDI flow control setting was failed */
    //        FTDITxRxBufferFree,             /*!< FTDI Rx and Tx buffer cleaned was failed */
    //        FTDIready                       /*!< FTDI ready to use */
    //    }eFTDIStatePossible;

    //    /**
    //      * \struct  eFTDIReturnCharacter
    //      * \brief structure of return character possible from the PIC
    //      *
    //      * Use to converte the character to string for displaying
    //      */
    //    typedef enum
    //    {
    //        endOfTransmission = 0x04,   /*!< 0x04 end of tranmsission */
    //        transmissionEnquiry = 0x05, /*!< 0x05 start of tranmsission */
    //        positiveAcknoledge = 0x06,  /*!< 0x06 acknoledgement */
    //        negativeAcknoledge = 0x15   /*!< 0x015 none acknoledgement */
    //    }eFTDIReturnCharacter;

    //    //all static variables
    //    static QMap<int, QString> TriggerTracePossible;
    //    static QMap<int, QString> FTDIReturnCharPossible;
    //    static QMap<int, QString> FTDIStatePossible;

    //    //init array for external use
    //    static QMap<int, QString> initTriggerTracePossible();
    //    static QMap<int, QString> initFTDIReturnCharPossibleTxt();
    //    static QMap<int, QString> initFTDIStatePossibleTXT();


    //    static QMap<int, double> initPeridePossible();
    //    static QMap<int, QString> initPeridePossibleTxt();

    //    static QMap<int, QString> initMainStateDisplayPossibleTxt();

    //****************************************************************************
    // new declaration


    //liquide insiade the tank
    /**
      * \struct  E_TankLiquidInside
      * \brief structure of the main button state
      *
      * Is use to set the color of the tank level and the liquide density
      */

//    typedef enum
//    {
//        WATER = 0,  /*!< water inside tank*/
//        OIL,        /*!< oil inside tank*/
//        ECO_OIL      /*!< ecoOil inside tank*/
//    }E_TankLiquidInside;

//    Q_ENUM(E_TankLiquidInside)



    //tank object for linking to custom name
    /**
         * \struct  E_TankObjectName
         * \brief structure of all tank possible
         *
         * Use to manage the link between the custom name and the object
         */
    typedef enum
    {
        TANK1 = 1,     /*!< tank on the 1 row 1 column */
        TANK2,         /*!< tank on the 1 row 2 column */
        TANK3,         /*!< tank on the 1 row 3 column */
        TANK4,         /*!< tank on the 2 row 1 column */
        TANK5,         /*!< tank on the 2 row 2 column */
        TANK6          /*!< tank on the 2 row 3 column */
    }E_TankObjectName;

    Q_ENUM(E_TankObjectName)

//    //init array for external use
//    static QMap<int, QString> initTankObjectName();
//    /**
//      * \fn init();
//      * \brief create link bettween C++ and QML
//      */
//    static void initClass();
};

#endif // GLOBALENUMATEDANDEXTERN_H
