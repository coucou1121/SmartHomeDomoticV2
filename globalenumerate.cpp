#include "globalenumerate.h"

GlobalEnumerate::GlobalEnumerate()
{

}

void GlobalEnumerate::initClass()
{

    //liquide tank enum class
    qRegisterMetaType<GlobalEnumerate::E_TankLiquidInside>("E_TankLiquidInside");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_TankLiquidInside");

    //Tank name and object
    qRegisterMetaType<GlobalEnumerate::E_TankObjectName>("E_TankObjectName");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_TankObjectName");

    //error message possible
    qRegisterMetaType<GlobalEnumerate::E_ErrorMesseage>("E_ErrorMessage");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_ErrorMessage");

}
