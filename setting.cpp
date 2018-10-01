#include "setting.h"

Setting::Setting(QObject *parent, QObject *tankViewer, QObject *settingViewer):
    QObject(parent),
    _tankObjectNameArray(GlobaleStaticValue::initTankObjectName()),
    _setting(new QSettings (FILE_NAME, QSettings::IniFormat)),
    _Tank1(new Tank(GlobalEnumerate::TANK1, this->_tankObjectNameArray[GlobalEnumerate::TANK1])),
    _Tank2(new Tank(GlobalEnumerate::TANK2, this->_tankObjectNameArray[GlobalEnumerate::TANK2])),
    _Tank3(new Tank(GlobalEnumerate::TANK3, this->_tankObjectNameArray[GlobalEnumerate::TANK3])),
    _Tank4(new Tank(GlobalEnumerate::TANK4, this->_tankObjectNameArray[GlobalEnumerate::TANK4])),
    _Tank5(new Tank(GlobalEnumerate::TANK5, this->_tankObjectNameArray[GlobalEnumerate::TANK5])),
    _Tank6(new Tank(GlobalEnumerate::TANK6, this->_tankObjectNameArray[GlobalEnumerate::TANK6])),
    _tankIsVisible(true),
    _tankViewer(tankViewer),
    _settingViewer(settingViewer)
{

    qmlRegisterType<Setting>("io.qt.Setting", 1, 0, "Setting");

    //set personnal path for the setting.ini file
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, SAVED_PATH_FILE);

    //load parameter from this init file
    this->loadSettings();

    //set the object parameters from the init file
    this->initSetting();

    //save the parameter from the init file
    this->saveSettings();

}

void Setting::receivedTankIsVisible(const int objectID, const bool isVisible)
{
    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setIsVisible(isVisible);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setIsVisible(isVisible);
        break;
    }

    QMetaObject::invokeMethod(this->_tankViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    this->saveSettings();
}

void Setting::receivedTankTitleChanged(const int objectID, const QString titleText)
{
    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setTitle(titleText);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setTitle(titleText);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setTitle(titleText);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setTitle(titleText);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setTitle(titleText);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setTitle(titleText);
        break;
    }

    QMetaObject::invokeMethod(this->_tankViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );
    this->saveSettings();
}

void Setting::receivedTankVolumeMaxChanged(const QString objectName, const int volumeMax)
{

    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setVolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setVolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setVolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setVolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setVolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setVolumeMax(volumeMax);
        break;
    }

    this->saveSettings();
}

void Setting::receivedTankWarningLowLevelChanged(const QString objectName, const int lowLevel)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setLowLevelValue(lowLevel);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setLowLevelValue(lowLevel);
        break;
    }

    this->saveSettings();
}

void Setting::receivedTankLiquideFillupChanged(const QString objectName, const int liquideFillup)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setLiquideFillup(liquideFillup);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setLiquideFillup(liquideFillup);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setLiquideFillup(liquideFillup);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setLiquideFillup(liquideFillup);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setLiquideFillup(liquideFillup);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setLiquideFillup(liquideFillup);
        break;
    }

    this->saveSettings();
}

void Setting::receivedTankHeightMaxLevelChanged(const QString objectName, const int heightVMax)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setHeightVMaxValue(heightVMax);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setHeightVMaxValue(heightVMax);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setHeightVMaxValue(heightVMax);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setHeightVMaxValue(heightVMax);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setHeightVMaxValue(heightVMax);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setHeightVMaxValue(heightVMax);
        break;
    }

    this->saveSettings();
}

void Setting::initSetting()
{

    this->initTankObjectName(this->_Tank1->objectID(),this->_Tank1->objectName());
    this->initTankObjectName(this->_Tank2->objectID(),this->_Tank2->objectName());
    this->initTankObjectName(this->_Tank3->objectID(),this->_Tank3->objectName());
    this->initTankObjectName(this->_Tank4->objectID(),this->_Tank4->objectName());
    this->initTankObjectName(this->_Tank5->objectID(),this->_Tank5->objectName());
    this->initTankObjectName(this->_Tank6->objectID(),this->_Tank6->objectName());

    this->initTankTitleText(this->_Tank1->objectID(),this->_Tank1->title());
    this->initTankTitleText(this->_Tank2->objectID(),this->_Tank2->title());
    this->initTankTitleText(this->_Tank3->objectID(),this->_Tank3->title());
    this->initTankTitleText(this->_Tank4->objectID(),this->_Tank4->title());
    this->initTankTitleText(this->_Tank5->objectID(),this->_Tank5->title());
    this->initTankTitleText(this->_Tank6->objectID(),this->_Tank6->title());

    this->initTankVolumeMax(this->_Tank1->objectID(),this->_Tank1->volumeMax());
    this->initTankVolumeMax(this->_Tank2->objectID(),this->_Tank2->volumeMax());
    this->initTankVolumeMax(this->_Tank3->objectID(),this->_Tank3->volumeMax());
    this->initTankVolumeMax(this->_Tank4->objectID(),this->_Tank4->volumeMax());
    this->initTankVolumeMax(this->_Tank5->objectID(),this->_Tank5->volumeMax());
    this->initTankVolumeMax(this->_Tank6->objectID(),this->_Tank6->volumeMax());

    this->initTankWarningLowLevel(this->_Tank1->objectID(),this->_Tank1->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank2->objectID(),this->_Tank2->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank3->objectID(),this->_Tank3->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank4->objectID(),this->_Tank4->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank5->objectID(),this->_Tank5->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank6->objectID(),this->_Tank6->lowLevelValue());

    this->initTankWarningLowLevel(this->_Tank1->objectID(),this->_Tank1->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank2->objectID(),this->_Tank2->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank3->objectID(),this->_Tank3->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank4->objectID(),this->_Tank4->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank5->objectID(),this->_Tank5->lowLevelValue());
    this->initTankWarningLowLevel(this->_Tank6->objectID(),this->_Tank6->lowLevelValue());

    this->initTankLiquideInside(this->_Tank1->objectID(),this->_Tank1->LiquideFillup());
    this->initTankLiquideInside(this->_Tank2->objectID(),this->_Tank2->LiquideFillup());
    this->initTankLiquideInside(this->_Tank3->objectID(),this->_Tank3->LiquideFillup());
    this->initTankLiquideInside(this->_Tank4->objectID(),this->_Tank4->LiquideFillup());
    this->initTankLiquideInside(this->_Tank5->objectID(),this->_Tank5->LiquideFillup());
    this->initTankLiquideInside(this->_Tank6->objectID(),this->_Tank6->LiquideFillup());

    this->initHeightVMaxValue(this->_Tank1->objectID(),this->_Tank1->heightVMaxValue());
    this->initHeightVMaxValue(this->_Tank2->objectID(),this->_Tank2->heightVMaxValue());
    this->initHeightVMaxValue(this->_Tank3->objectID(),this->_Tank3->heightVMaxValue());
    this->initHeightVMaxValue(this->_Tank4->objectID(),this->_Tank4->heightVMaxValue());
    this->initHeightVMaxValue(this->_Tank5->objectID(),this->_Tank5->heightVMaxValue());
    this->initHeightVMaxValue(this->_Tank6->objectID(),this->_Tank6->heightVMaxValue());

}

void Setting::initTankObjectName(int objectID, QString objectName)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankObjectName",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, objectName)
                              );
}

void Setting::initTankTitleText(int objectID, QString titleText)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );
}

void Setting::initTankIsVisible(int objectID, bool isVisible)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    QMetaObject::invokeMethod(this->_tankViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );

}

void Setting::initTankVolumeMax(int objectID, int volumeMax)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankVolumeMax",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, volumeMax)
                              );
}

void Setting::initTankWarningLowLevel(int objectID, int warningLowLevel)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setWarningLowLevel",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, warningLowLevel)
                              );
}

void Setting::initTankLiquideInside(int objectID, int tankLiquideInside)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankLiquideInside",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, tankLiquideInside)
                              );
}

void Setting::initHeightVMaxValue(int objectID, int HeightVMaxValue)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setHeightVMaxValue",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, HeightVMaxValue)
                              );
}

void Setting::saveSettings()
{

    //save all value for tank1
    this->saveTankSetting(this->_Tank1);

    //save all value for tank2
    this->saveTankSetting(this->_Tank2);

    //save all value for tank3
    this->saveTankSetting(this->_Tank3);

    //save all value for tank4
    this->saveTankSetting(this->_Tank4);

    //save all value for tank5
    this->saveTankSetting(this->_Tank5);

    //save all value for tank6
    this->saveTankSetting(this->_Tank6);

}

void Setting::saveTankSetting(Tank *tank)
{
    QString groupeName = tank->objectName();

    //save all value for tank
    this->_setting->beginGroup(groupeName);
    this->_setting->setValue(GlobaleStaticValue::saveIDTxt, tank->objectID());
    this->_setting->setValue(GlobaleStaticValue::saveObjectNameTxt, tank->objectName());
    this->_setting->setValue(GlobaleStaticValue::saveTitleTxt, tank->title());
    this->_setting->setValue(GlobaleStaticValue::saveVisibleTxt, tank->isVisible());
    this->_setting->setValue(GlobaleStaticValue::saveLiquideInsideTxt, tank->LiquideFillup());
    this->_setting->setValue(GlobaleStaticValue::saveVolumeMaxTxt, tank->volumeMax());
    this->_setting->setValue(GlobaleStaticValue::saveLowLevelWarningTxt, tank->lowLevelValue());
    this->_setting->setValue(GlobaleStaticValue::saveHeightVMaxValueTxt, tank->heightVMaxValue());
    this->_setting->endGroup();
}

void Setting::loadSettings()
{

    loadTankSetting(this->_Tank1);
    loadTankSetting(this->_Tank2);
    loadTankSetting(this->_Tank3);
    loadTankSetting(this->_Tank4);
    loadTankSetting(this->_Tank5);
    loadTankSetting(this->_Tank6);
}

void Setting::loadTankSetting(Tank *tank)
{
    QString groupeName = tank->objectName();
    QString groupeNameID = groupeName + "/" + GlobaleStaticValue::saveIDTxt;
    QString groupeNameObjectName = groupeName + "/" + GlobaleStaticValue::saveObjectNameTxt;
    QString groupeNameTitle = groupeName + "/" +GlobaleStaticValue::saveTitleTxt;
    QString groupeNameVisible = groupeName + "/" + GlobaleStaticValue::saveVisibleTxt;
    QString groupeNameLiquideInside = groupeName + "/" + GlobaleStaticValue::saveLiquideInsideTxt;
    QString groupeNameVolumeMax = groupeName + "/" + GlobaleStaticValue::saveVolumeMaxTxt;
    QString groupeNameLowLevelWarning = groupeName + "/" + GlobaleStaticValue::saveLowLevelWarningTxt;
    QString groupeNameHeighVMaxValue = groupeName + "/" + GlobaleStaticValue::saveHeightVMaxValueTxt;

    tank->setObjectName(this->_setting->value(groupeNameObjectName, tank->objectName()).toString());
    tank->setTitle(this->_setting->value(groupeNameTitle, tank->objectID()).toString());
    tank->setIsVisible(this->_setting->value(groupeNameVisible, true).toBool());
    tank->setLiquideFillup(this->_setting->value(groupeNameLiquideInside, GlobalEnumerate::E_TankLiquidInside::WATER).toInt());
    tank->setVolumeMax(this->_setting->value(groupeNameVolumeMax, 5000).toInt());
    tank->setLowLevelValue(this->_setting->value(groupeNameLowLevelWarning, 500).toInt());
    tank->setHeightVMaxValue(this->_setting->value(groupeNameHeighVMaxValue, 1500).toInt());
}
