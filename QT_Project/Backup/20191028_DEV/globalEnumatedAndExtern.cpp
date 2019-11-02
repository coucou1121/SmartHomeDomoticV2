#include "globalEnumatedAndExtern.h"

//GlobalEnumatedAndExtern::GlobalEnumatedAndExtern()
//{

//}



//QMap<int, QString> GlobalEnumatedAndExtern::initErrorPossible()
//{
//    QMap<int, QString> ret;
//    ret.insert(noError, "No error");
//    ret.insert(errorFTDIDeviceNotFound, "FTDI Device\nNot Found\n-> Run in emulation\nor\n-> Fix FTDI device");
//    ret.insert(errorSamplingFrequencyToHigh, "Periode too low \n or \n baudrate too high");
//    ret.insert(errorNoSelectedTrace, "No channels \n selected");
//    ret.insert(errorNoSelectedTriggerTrace, "No trigger channels \n selected");
//    ret.insert(errorWrongEquation, "Wrong Equation in \n Trigger Function\n menu");
//    return ret;
//}

//QMap<int, QString> GlobalEnumatedAndExtern::initTriggerTracePossible()
//{

//    QMap<int, QString> ret;
//    ret.insert(btNone, "none");
//    ret.insert(btDI1, "DI 1");
//    ret.insert(btDI2, "DI 2");
//    ret.insert(btDI3, "DI 3");
//    ret.insert(btDI4, "DI 4");
//    ret.insert(btDI5, "DI 5");
//    ret.insert(btDI6, "DI 6");
//    ret.insert(btDI7, "DI 7");
//    ret.insert(btDI8, "DI 8");
//    ret.insert(btDI9, "DI 9");
//    ret.insert(btDI10, "DI 10");
//    ret.insert(btDI11, "DI 11");
//    ret.insert(btDI12, "DI 12");
//    ret.insert(btDI13, "DI 13");
//    ret.insert(btDI14, "DI 14");
//    ret.insert(btDI15, "DI 15");
//    ret.insert(btDI16, "DI 16");
//    ret.insert(btAI1, "AI 1");
//    ret.insert(btAI2, "AI 2");
//    ret.insert(btAI3, "AI 3");
//    ret.insert(btAI4, "AI 4");
//    ret.insert(functionResult, "TR 1");
//    return ret;
//}

//QMap<int, QString> GlobalEnumatedAndExtern::initFTDIStatePossibleTXT()
//{
//    QMap<int, QString> ret;
//    ret.insert(FTDInotConnected, "FTDI not connected");
//    ret.insert(FTDIDeviceFound, "FTDI found");
//    ret.insert(FTDIopened, "FTDI opened");
//    ret.insert(FTDIUSBparameterSetted, "FTDI USB parameter setted");
//    ret.insert(FTDIBaudRateSetted, "FTDI baudrate setted");
//    ret.insert(FTDIDataCaracteristiqueSetted, "FTDI data characteristic setted");
//    ret.insert(FTDIFlowControlSetted, "FTDI flow control setted");
//    ret.insert(FTDITxRxBufferFree, "FTDI TxRx buffer cleaned");
//    ret.insert(FTDIready, "FTDI ready to use");
//    return ret;
//}

//QMap<int, QString> GlobalEnumatedAndExtern::initFTDIReturnCharPossibleTxt()
//{
//    QMap<int, QString> ret;
//    ret.insert(endOfTransmission, "transmission Stop");
//    ret.insert(transmissionEnquiry, "transmission Stard");
//    ret.insert(positiveAcknoledge, "ACK");
//    ret.insert(negativeAcknoledge, "nACK");
//    return ret;
//}

//QMap<int, double> GlobalEnumatedAndExtern::initPeridePossible()
//{
//    // all time are in millisecondes
//    QMap<int, double> ret;
//    ret.insert(periode0_5_microsec, 0.0005);
//    ret.insert(periode1_microsec, 0.001);
//    ret.insert(periode50_microsec, 0.05);
//    ret.insert(periode100_microsec, 0.1);
//    ret.insert(periode1_ms, 1);
//    ret.insert(periode5_ms, 5);
//    ret.insert(periode10_ms, 10);
//    ret.insert(periode50_ms, 50);
//    ret.insert(periode100_ms, 100);
//    ret.insert(periode500_ms, 500);
//    ret.insert(periode1_s, 1000);
//    ret.insert(periode5_s, 5000);
//    ret.insert(periode10_s, 10000);
//    return ret;
//}

//QMap<int, QString> GlobalEnumatedAndExtern::initPeridePossibleTxt()
//{
//    QMap<int, QString> ret;
//    ret.insert(periode0_5_microsec, "0.5 μs max resolution");
//    ret.insert(periode1_microsec, "1 μs");
//    ret.insert(periode50_microsec, "50 μs");
//    ret.insert(periode100_microsec, "100 μs");
//    ret.insert(periode1_ms, "1 ms");
//    ret.insert(periode5_ms, "5 ms");
//    ret.insert(periode10_ms, "10 ms");
//    ret.insert(periode50_ms, "50 ms");
//    ret.insert(periode100_ms, "100 ms");
//    ret.insert(periode500_ms, "500 ms");
//    ret.insert(periode1_s, "1 s");
//    ret.insert(periode5_s, "5 s");
//    ret.insert(periode10_s, "10 s");
//    return ret;
//}

//QMap<int, QString> GlobalEnumatedAndExtern::initMainStateDisplayPossibleTxt()
//{
//    QMap<int, QString> ret;
//    ret.insert(init, "Init");
//    ret.insert(stopped, "Stopped");
//    ret.insert(ready, "Ready");
//    ret.insert(runTrig, "Run Trig");
//    ret.insert(trigged, "Trigged");
//    ret.insert(rollOn, "Roll on");
//    ret.insert(paused, "Paused");
//    return ret;
//}


////initialise the Key - Value for combobx
//extern QMap<int, QString> TriggerTracePossible = GlobalEnumatedAndExtern::initTriggerTracePossible();

////externe variable
// QString BPMenuHomeTxt = "Home";
// QString BPMenuSetTxt = "Set";
// QString BPMenuTrigTxt = "Trig";
// QString BPMenuRollTxt = "Roll";
// QString BPMenuDebugTxt = "Debug";

// QString BPStartStopStateStartTxt = "Start";
// QString BPStartStopStateStopTxt = "Stop";
// QString BPStartStopStateHoldTxt = "Hold";

// QString range0_24Txt = "0-24";
// QString range0_30Txt = "0-30";
// QString range15_15Txt = QString::fromUtf8("\u00B1 15");

// qint8 minRange0 = 0;
// qint8 maxRange0_24 = 24;
// qint8 maxRange0_30 = 30;
// qint8 minRange_15_15 = -15;
// qint8 maxRange_15_15 = 15;

// QString opNoneTxt = "none";
// QString opOrTxt = "OR";
// QString opAndTxt = "AND";
// QString opNotOrTxt = "OR NOT";
// QString opNoTAndTxt = "AND NOT";

// QString speedSettingTitle = "data divider";



//void GlobalEnumatedAndExtern::initClass()
//{
//    //liquide tank enum class
//    qRegisterMetaType<GlobalEnumatedAndExtern::E_TankLiquidInside>("E_TankLiquidInside");
//    qmlRegisterType<GlobalEnumatedAndExtern>("io.qt.GlobalEnumatedAndExtern", 1, 0, "E_TankLiquidInside");

//    //Tank name and object
//    //liquide tank enum class
//    qRegisterMetaType<GlobalEnumatedAndExtern::E_TankObjectName>("E_TankObjectName");
//    qmlRegisterType<GlobalEnumatedAndExtern>("io.qt.GlobalEnumatedAndExtern", 1, 0, "E_TankObjectName");
//}
