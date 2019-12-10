#include "globalenumerate.h"

GlobalEnumerate::GlobalEnumerate()
{

}

void GlobalEnumerate::initCppToQmlClass()
{

    //Style of the plot
    qRegisterMetaType<GlobalEnumerate::E_PlotStyle>("E_PlotStyle");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_PlotStyle");

    //liquide tank enum class
    qRegisterMetaType<GlobalEnumerate::E_TankLiquidInside>("E_TankLiquidInside");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_TankLiquidInside");

    //Tank name and object
    qRegisterMetaType<GlobalEnumerate::E_TankObjectName>("E_TankObjectName");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_TankObjectName");

    //All home page object
    qRegisterMetaType<GlobalEnumerate::E_HomePageObject>("E_HomePageObject");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_HomePageObject");

    //error message possible
    qRegisterMetaType<GlobalEnumerate::E_ErrorMesseage>("E_ErrorMessage");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_ErrorMessage");

    //Mode of the application
    qRegisterMetaType<GlobalEnumerate::E_StateMachine>("E_StateMachine");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_StateMachine");

    //MCP23017 ID
    qRegisterMetaType<GlobalEnumerate::E_StateMachine>("E_MCP23017ObjectID");
    qmlRegisterType<GlobalEnumerate>("io.qt.GlobalEnumerate", 1, 0, "E_MCP23017ObjectID");

}
