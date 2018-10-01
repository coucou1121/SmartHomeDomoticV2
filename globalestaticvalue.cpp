#include "globalestaticvalue.h"

GlobaleStaticValue::GlobaleStaticValue()
{

}

//warning static text
QString GlobaleStaticValue::errorCounterTxt = "nb of active error";

//text value for the saved file
QString GlobaleStaticValue::saveIDTxt = "ID";
QString GlobaleStaticValue::saveObjectNameTxt = "ObjectName";
QString GlobaleStaticValue::saveTitleTxt = "Title";
QString GlobaleStaticValue::saveVisibleTxt = "Visible";
QString GlobaleStaticValue::saveLiquideInsideTxt = "LiquideInside";
QString GlobaleStaticValue::saveVolumeMaxTxt = "VolumeMax";
QString GlobaleStaticValue::saveLowLevelWarningTxt = "LowLevelWarning";
QString GlobaleStaticValue::saveHeightVMaxValueTxt = "HeightVMax";


static QString titleTank1 = "Tank_1";
static QString titleTank2 = "Tank_2";
static QString titleTank3 = "Tank_3";
static QString titleTank4 = "Tank_4";
static QString titleTank5 = "Tank_5";
static QString titleTank6 = "Tank_6";


static QString errNoError = "no error";
static QString errLowLevelReached = "low level reached";


QMap<int, QString> GlobaleStaticValue::initTankObjectName()
{
    QMap<int, QString> ret;
    ret.insert(GlobalEnumerate::TANK1, titleTank1);
    ret.insert(GlobalEnumerate::TANK2, titleTank2);
    ret.insert(GlobalEnumerate::TANK3, titleTank3);
    ret.insert(GlobalEnumerate::TANK4, titleTank4);
    ret.insert(GlobalEnumerate::TANK5, titleTank5);
    ret.insert(GlobalEnumerate::TANK6, titleTank6);
    return ret;
}

QMap<int, QString> GlobaleStaticValue::initErrorPossible()
{
    QMap<int, QString> ret;
    ret.insert(GlobalEnumerate::ERR_NO_ERROR, errNoError);
    ret.insert(GlobalEnumerate::ERR_LOW_LEVEL_REACHED, errLowLevelReached);
    return ret;
}
