#include "setting.h"

Setting::Setting(QObject *parent,
                 QObject *homeViewer,
                 QObject *tankViewer,
                 QObject *settingViewer,
                 QObject *statisticViewer,
                 DataAnalyser *dataAnalyser,
                 BME280Item *bme280,
                 ADS1115Item *ads1115_1,
                 ADS1115Item *ads1115_2,
                 DataManager *dataManager):
    QObject(parent),
    _tankObjectNameArray(GlobaleStaticValue::initTankObjectName()),
    _homeViewObject(GlobaleStaticValue::initHomeViewObject()),
    _settingFileName(GlobaleStaticValue::settingFile),
    _setting(new QSettings (GlobaleStaticValue::settingFile, QSettings::IniFormat)),
    _Tank1(new Tank(GlobalEnumerate::TANK1, this->_tankObjectNameArray[GlobalEnumerate::TANK1])),
    _Tank2(new Tank(GlobalEnumerate::TANK2, this->_tankObjectNameArray[GlobalEnumerate::TANK2])),
    _Tank3(new Tank(GlobalEnumerate::TANK3, this->_tankObjectNameArray[GlobalEnumerate::TANK3])),
    _Tank4(new Tank(GlobalEnumerate::TANK4, this->_tankObjectNameArray[GlobalEnumerate::TANK4])),
    _Tank5(new Tank(GlobalEnumerate::TANK5, this->_tankObjectNameArray[GlobalEnumerate::TANK5])),
    _Tank6(new Tank(GlobalEnumerate::TANK6, this->_tankObjectNameArray[GlobalEnumerate::TANK6])),
    _tankIsVisible(true),
    _homeViewer(homeViewer),
    _tankViewer(tankViewer),
    _settingViewer(settingViewer),
    _statisticViewer(statisticViewer),
    _dataAnalyser(dataAnalyser),
    _dataManager(dataManager),
    _bme280(bme280),
    _ads1115_1(ads1115_1),
    _ads1115_2(ads1115_2),
    _graphicReccordTime(24)
{

    qmlRegisterType<Setting>("io.qt.Setting", 1, 0, "Setting");

    //set personnal path for the setting.ini file
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope, SAVED_PATH_FILE);

    //load parameter from this init file
    this->_loadSettings();

    //set the object parameters from the init file
    this->_initSetting();

    //save the parameter from the init file
    this->_saveSettings();

    //init graphic range
//    this->receivedGraphReccordTimesChanged(this->_graphicReccordTime);
}

void Setting::receivedTankIsVisible(const int objectID, const bool isVisible)
{
    bool isReadyToTerminate = false;

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setIsVisible(isVisible);
        this->_ads1115_1->setChan0_used(isVisible);
        if(isVisible)
        {
            this->_ads1115_1->setAskToRun(true);
            if(!this->_ads1115_1->isRunning())
            {
                this->_ads1115_1->start();
            }
        }
        else
        {
           this->_ads1115_1->setAskToRun(false);
           this->_ads1115_1->terminate();
        }
        qDebug() << Q_FUNC_INFO << "ADS1115 is runnung: " << this->_ads1115_1->isRunning();

        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setIsVisible(isVisible);
        this->_ads1115_1->setChan1_used(isVisible);
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

    QMetaObject::invokeMethod(this->_homeViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );

    QMetaObject::invokeMethod(this->_statisticViewer, "setupTraceIsSelected",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    this->_saveSettings();
}

void Setting::receivedTankTitleChanged(const int objectID, const QString titleText)
{
    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setTitle(titleText);
        this->_initHomeViewObject(GlobalEnumerate::HOMETANK1, this->_Tank1->title());
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setTitle(titleText);
        this->_initHomeViewObject(GlobalEnumerate::HOMETANK2, this->_Tank2->title());
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setTitle(titleText);
        this->_initHomeViewObject(GlobalEnumerate::HOMETANK3, this->_Tank3->title());
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setTitle(titleText);
        this->_initHomeViewObject(GlobalEnumerate::HOMETANK4, this->_Tank4->title());
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setTitle(titleText);
        this->_initHomeViewObject(GlobalEnumerate::HOMETANK5, this->_Tank5->title());
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setTitle(titleText);
        this->_initHomeViewObject(GlobalEnumerate::HOMETANK6, this->_Tank6->title());
        break;
    }


    QMetaObject::invokeMethod(this->_homeViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_statisticViewer, "setTankTraceTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    this->_saveSettings();
}

void Setting::receivedTankVolumeMaxChanged(const QString objectName, const int volumeMax)
{

    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
    {
        this->_Tank1->setVolumeMax(volumeMax);
//        this->_ads1115_1->setTankChan0VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan0VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK2 :
    {
        this->_Tank2->setVolumeMax(volumeMax);
//        this->_ads1115_1->setTankChan1VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan1VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK3 :
    {
        this->_Tank3->setVolumeMax(volumeMax);
//        this->_ads1115_1->setTankChan2VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan2VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK4 :
    {
        this->_Tank4->setVolumeMax(volumeMax);
//        this->_ads1115_1->setTankChan3VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan3VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK5 :
    {
        this->_Tank5->setVolumeMax(volumeMax);
//        this->_ads1115_2->setTankChan0VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan0VolumeMax(volumeMax);
        break;
    }
    case GlobalEnumerate::TANK6 :
    {
        this->_Tank6->setVolumeMax(volumeMax);
//        this->_ads1115_2->setTankChan1VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan1VolumeMax(volumeMax);
        break;
    }
    }

    this->_saveSettings();
}

void Setting::receivedVolumePIDChanged(const int PIDValue)
{
    qDebug() << Q_FUNC_INFO << "value: " << PIDValue;

//    this->_ads1115_1->setPIDVolumeCoef(PIDValue);
    this->_dataAnalyser->setPIDVolumeCoef(PIDValue);

    this->_saveSettings();
}

void Setting::receivedSmoothPlotValueChanged(const int SmoothPlotValue)
{
    qDebug() << Q_FUNC_INFO << "value: " << SmoothPlotValue;
    this->_ads1115_1->setSmoothPlot(SmoothPlotValue);

    this->_saveSettings();
}

void Setting::receivedVolumeATMChanged()
{
     qDebug() << Q_FUNC_INFO;
    this->_saveSettings();
}

void Setting::receivedWarningLowLevelFromTank(const QString objectName, const bool isActive)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    if(isActive)
    {
        QMetaObject::invokeMethod(this->_homeViewer, "setTankColor",
                                  Q_ARG(QVariant, objectID),
                                  Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX)
                                  );
    }
    else
    {
        QMetaObject::invokeMethod(this->_homeViewer, "setTankColor",
                                  Q_ARG(QVariant, objectID),
                                  Q_ARG(QVariant, DEVICE_COLOR_READY_HEX)
                                  );

    }
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

    this->_saveSettings();
}

void Setting::receivedTankLiquideFillupChanged(const QString objectName, const int liquideFillup)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
    {
        this->_Tank1->setLiquideFillup(liquideFillup);
//        this->_ads1115_1->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        this->_dataAnalyser->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK2 :
    {
        this->_Tank2->setLiquideFillup(liquideFillup);
//        this->_ads1115_1->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        this->_dataAnalyser->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK3 :
    {
        this->_Tank3->setLiquideFillup(liquideFillup);
//        this->_ads1115_1->setTankChan2LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        this->_dataAnalyser->setTankChan2LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK4 :
    {
        this->_Tank4->setLiquideFillup(liquideFillup);
//        this->_ads1115_1->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        this->_dataAnalyser->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK5 :
    {
        this->_Tank5->setLiquideFillup(liquideFillup);
//        this->_ads1115_2->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        this->_dataAnalyser->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    case GlobalEnumerate::TANK6 :
    {
        this->_Tank6->setLiquideFillup(liquideFillup);
//        this->_ads1115_2->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        this->_dataAnalyser->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)liquideFillup);
        break;
    }
    }

    this->_saveSettings();
}

void Setting::receivedTankHeightMaxLevelChanged(const QString objectName, const int heightVMax)
{
    int objectID = this->_tankObjectNameArray.key(objectName);

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
        this->_Tank1->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK2 :
        this->_Tank2->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK3 :
        this->_Tank3->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK4 :
        this->_Tank4->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK5 :
        this->_Tank5->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    case GlobalEnumerate::TANK6 :
        this->_Tank6->setVolumeMaxHeightInMilimeter(heightVMax);
        break;
    }

    this->_saveSettings();
}

void Setting::receivedTankOffsetPressureChanged(const int objectID, const int offsetPressureValue)
{
    qDebug() << Q_FUNC_INFO << "ID: " << objectID << ", value: " << offsetPressureValue;

    switch (objectID)
    {
    case GlobalEnumerate::TANK1 :
//        this->_ads1115_1->setOffsetPressurChan0(offsetPressureValue);
        this->_dataAnalyser->setOffsetPressurChan0(offsetPressureValue);
        break;
    case GlobalEnumerate::TANK2 :
//        this->_ads1115_1->setOffsetPressurChan1(offsetPressureValue);
        this->_dataAnalyser->setOffsetPressurChan1(offsetPressureValue);
        break;
    case GlobalEnumerate::TANK3 :
//        this->_ads1115_1->setOffsetPressurChan2(offsetPressureValue);
        this->_dataAnalyser->setOffsetPressurChan2(offsetPressureValue);
        break;
    case GlobalEnumerate::TANK4 :
//        this->_ads1115_1->setOffsetPressurChan3(offsetPressureValue);
        this->_dataAnalyser->setOffsetPressurChan3(offsetPressureValue);
        break;
    case GlobalEnumerate::TANK5 :
//        this->_ads1115_2->setOffsetPressurChan0(offsetPressureValue);
        this->_dataAnalyser->setOffsetPressurChan4(offsetPressureValue);
        break;
    case GlobalEnumerate::TANK6 :
//        this->_ads1115_2->setOffsetPressurChan1(offsetPressureValue);
        this->_dataAnalyser->setOffsetPressurChan5(offsetPressureValue);
        break;
    }

    this->_saveSettings();
}

void Setting::receivedTankActualVolumeChanged(const int objectID, const int volumeActual)
{
//    qDebug() << Q_FUNC_INFO << "ID: " << objectID << "volume: " << volumeActual;

    QString str = QString::number(volumeActual) + " " + GlobaleStaticValue::ADS1115_Liter;

    QMetaObject::invokeMethod(this->_tankViewer, "setTankVolumeActual",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, volumeActual)
                              );
    QMetaObject::invokeMethod(this->_homeViewer, "setTankVolumeActual",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, str)
                              );
}

void Setting::receivedGraphReccordTimesChanged(const int reccordTime)
{
    quint64 refreshTime = 0;
    quint64 graphicRange = 0;
    this->_graphicReccordTime = reccordTime;

    if(reccordTime <= 0)
    {
        graphicRange = 100;
        refreshTime = graphicRange*1000/NB_OF_PIXELS_IN_PLOT;
    }
    else
    {
        graphicRange = reccordTime*3600;
        refreshTime = graphicRange*1000/NB_OF_PIXELS_IN_PLOT;
    }

    qDebug() << Q_FUNC_INFO  << "reccordTime" << reccordTime
             << "graphicRange" << graphicRange << ", refreshTime"
             << refreshTime << "_graphicReccordTime" << this->_graphicReccordTime;
//    this->_dataManager->setSleepingDelay(refreshTime);

    this->_dataAnalyser->setDisplayPlotTime(reccordTime);

    QMetaObject::invokeMethod(this->_statisticViewer, "setGraphicRange",
                              Q_ARG(QVariant, graphicRange)
                              );
    this->_saveSettings();
}

void Setting::receivedOnCalibrationMode(const bool onCalibration)
{
    qDebug() << Q_FUNC_INFO << onCalibration;
    this->_ads1115_1->setOnCalibration(onCalibration);

    QMetaObject::invokeMethod(this->_statisticViewer, "setOnClaibration",
                              Q_ARG(QVariant, onCalibration)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setOnClaibration",
                              Q_ARG(QVariant, onCalibration)
                              );
}

void Setting::_initSetting()
{
//    this->initTankObjectName(this->_Tank1->objectID(),this->_Tank1->objectName());
//    this->initTankObjectName(this->_Tank2->objectID(),this->_Tank2->objectName());
//    this->initTankObjectName(this->_Tank3->objectID(),this->_Tank3->objectName());
//    this->initTankObjectName(this->_Tank4->objectID(),this->_Tank4->objectName());
//    this->initTankObjectName(this->_Tank5->objectID(),this->_Tank5->objectName());
//    this->initTankObjectName(this->_Tank6->objectID(),this->_Tank6->objectName());

    this->_initTankIsVisible(this->_Tank1->objectID(), this->_Tank1->isVisible());
    this->_initTankIsVisible(this->_Tank2->objectID(), this->_Tank2->isVisible());
    this->_initTankIsVisible(this->_Tank3->objectID(), this->_Tank3->isVisible());
    this->_initTankIsVisible(this->_Tank4->objectID(), this->_Tank4->isVisible());
    this->_initTankIsVisible(this->_Tank5->objectID(), this->_Tank5->isVisible());
    this->_initTankIsVisible(this->_Tank6->objectID(), this->_Tank6->isVisible());

    this->_initTankTitleText(this->_Tank1->objectID(),this->_Tank1->title());
    this->_initTankTitleText(this->_Tank2->objectID(),this->_Tank2->title());
    this->_initTankTitleText(this->_Tank3->objectID(),this->_Tank3->title());
    this->_initTankTitleText(this->_Tank4->objectID(),this->_Tank4->title());
    this->_initTankTitleText(this->_Tank5->objectID(),this->_Tank5->title());
    this->_initTankTitleText(this->_Tank6->objectID(),this->_Tank6->title());

//    this->_initTankOffsetPressure(this->_Tank1->objectID(),this->_ads1115_1->offsetPressurChan0());
//    this->_initTankOffsetPressure(this->_Tank2->objectID(),this->_ads1115_1->offsetPressurChan1());
//    this->_initTankOffsetPressure(this->_Tank3->objectID(),this->_ads1115_1->offsetPressurChan2());
//    this->_initTankOffsetPressure(this->_Tank4->objectID(),this->_ads1115_1->offsetPressurChan3());
//    this->_initTankOffsetPressure(this->_Tank5->objectID(),this->_ads1115_2->offsetPressurChan0());
//    this->_initTankOffsetPressure(this->_Tank6->objectID(),this->_ads1115_2->offsetPressurChan1());

    this->_initTankOffsetPressure(this->_Tank1->objectID(),this->_dataAnalyser->offsetPressurChan0());
    this->_initTankOffsetPressure(this->_Tank2->objectID(),this->_dataAnalyser->offsetPressurChan1());
    this->_initTankOffsetPressure(this->_Tank3->objectID(),this->_dataAnalyser->offsetPressurChan2());
    this->_initTankOffsetPressure(this->_Tank4->objectID(),this->_dataAnalyser->offsetPressurChan3());
    this->_initTankOffsetPressure(this->_Tank5->objectID(),this->_dataAnalyser->offsetPressurChan0());
    this->_initTankOffsetPressure(this->_Tank6->objectID(),this->_dataAnalyser->offsetPressurChan1());

    this->_initHomeViewObject(GlobalEnumerate::HOMEBME280, _homeViewObject[GlobalEnumerate::HOMEBME280]);
    this->_initHomeViewObject(GlobalEnumerate::HOMETANK1, this->_Tank1->title());
    this->_initHomeViewObject(GlobalEnumerate::HOMETANK2, this->_Tank2->title());
    this->_initHomeViewObject(GlobalEnumerate::HOMETANK3, this->_Tank3->title());
    this->_initHomeViewObject(GlobalEnumerate::HOMETANK4, this->_Tank4->title());
    this->_initHomeViewObject(GlobalEnumerate::HOMETANK5, this->_Tank5->title());
    this->_initHomeViewObject(GlobalEnumerate::HOMETANK6, this->_Tank6->title());
    this->_initHomeViewObject(GlobalEnumerate::HOMESENSOR1, _homeViewObject[GlobalEnumerate::HOMESENSOR1]);
    this->_initHomeViewObject(GlobalEnumerate::HOMESENSOR2, _homeViewObject[GlobalEnumerate::HOMESENSOR2]);
    this->_initHomeViewObject(GlobalEnumerate::HOMESENSOR3, _homeViewObject[GlobalEnumerate::HOMESENSOR3]);
    this->_initHomeViewObject(GlobalEnumerate::HOMESENSOR4, _homeViewObject[GlobalEnumerate::HOMESENSOR4]);
    this->_initHomeViewObject(GlobalEnumerate::HOMESENSOR5, _homeViewObject[GlobalEnumerate::HOMESENSOR5]);
    this->_initHomeViewObject(GlobalEnumerate::HOMESENSOR6, _homeViewObject[GlobalEnumerate::HOMESENSOR6]);
    this->_initHomeViewObject(GlobalEnumerate::HOMEAD1115_1, _homeViewObject[GlobalEnumerate::HOMEAD1115_1]);
    this->_initHomeViewObject(GlobalEnumerate::HOMEAD1115_2, _homeViewObject[GlobalEnumerate::HOMEAD1115_2]);
    this->_initHomeViewObject(GlobalEnumerate::HOMEAMCP23017_1, _homeViewObject[GlobalEnumerate::HOMEAMCP23017_1]);
    this->_initHomeViewObject(GlobalEnumerate::HOMEAMCP23017_2, _homeViewObject[GlobalEnumerate::HOMEAMCP23017_2]);
    this->_initHomeViewObject(GlobalEnumerate::HOMEAMCP23017_3, _homeViewObject[GlobalEnumerate::HOMEAMCP23017_3]);
    this->_initHomeViewObject(GlobalEnumerate::HOMEAMCP23017_4, _homeViewObject[GlobalEnumerate::HOMEAMCP23017_4]);

    this->_initTankVolumeMax(this->_Tank1->objectID(),this->_Tank1->volumeMax());
    this->_initTankVolumeMax(this->_Tank2->objectID(),this->_Tank2->volumeMax());
    this->_initTankVolumeMax(this->_Tank3->objectID(),this->_Tank3->volumeMax());
    this->_initTankVolumeMax(this->_Tank4->objectID(),this->_Tank4->volumeMax());
    this->_initTankVolumeMax(this->_Tank5->objectID(),this->_Tank5->volumeMax());
    this->_initTankVolumeMax(this->_Tank6->objectID(),this->_Tank6->volumeMax());

    this->_initTankLiquideInside(this->_Tank1->objectID(),this->_Tank1->LiquideFillup());
    this->_initTankLiquideInside(this->_Tank2->objectID(),this->_Tank2->LiquideFillup());
    this->_initTankLiquideInside(this->_Tank3->objectID(),this->_Tank3->LiquideFillup());
    this->_initTankLiquideInside(this->_Tank4->objectID(),this->_Tank4->LiquideFillup());
    this->_initTankLiquideInside(this->_Tank5->objectID(),this->_Tank5->LiquideFillup());
    this->_initTankLiquideInside(this->_Tank6->objectID(),this->_Tank6->LiquideFillup());

    this->_initHeightVMaxValue(this->_Tank1->objectID(),this->_Tank1->volumeMaxHeightInMilimeter());
    this->_initHeightVMaxValue(this->_Tank2->objectID(),this->_Tank2->volumeMaxHeightInMilimeter());
    this->_initHeightVMaxValue(this->_Tank3->objectID(),this->_Tank3->volumeMaxHeightInMilimeter());
    this->_initHeightVMaxValue(this->_Tank4->objectID(),this->_Tank4->volumeMaxHeightInMilimeter());
    this->_initHeightVMaxValue(this->_Tank5->objectID(),this->_Tank5->volumeMaxHeightInMilimeter());
    this->_initHeightVMaxValue(this->_Tank6->objectID(),this->_Tank6->volumeMaxHeightInMilimeter());

    this->_initTankWarningLowLevel(this->_Tank1->objectID(),this->_Tank1->lowLevelValue());
    this->_initTankWarningLowLevel(this->_Tank2->objectID(),this->_Tank2->lowLevelValue());
    this->_initTankWarningLowLevel(this->_Tank3->objectID(),this->_Tank3->lowLevelValue());
    this->_initTankWarningLowLevel(this->_Tank4->objectID(),this->_Tank4->lowLevelValue());
    this->_initTankWarningLowLevel(this->_Tank5->objectID(),this->_Tank5->lowLevelValue());
    this->_initTankWarningLowLevel(this->_Tank6->objectID(),this->_Tank6->lowLevelValue());

    //init ADS1115 for volume calculation
//    this->_ads1115_1->setTankIDchan0(this->_Tank1->objectID());
//    this->_ads1115_1->setTankIDchan1(this->_Tank2->objectID());
//    this->_ads1115_1->setTankIDchan2(this->_Tank3->objectID());
//    this->_ads1115_1->setTankIDchan3(this->_Tank4->objectID());
//    this->_ads1115_2->setTankIDchan0(this->_Tank5->objectID());
//    this->_ads1115_2->setTankIDchan1(this->_Tank6->objectID());

    //init tank ID for volume calculation
    this->_dataAnalyser->setTankIDchan0(this->_Tank1->objectID());
    this->_dataAnalyser->setTankIDchan1(this->_Tank2->objectID());
    this->_dataAnalyser->setTankIDchan2(this->_Tank3->objectID());
    this->_dataAnalyser->setTankIDchan3(this->_Tank4->objectID());
    this->_dataAnalyser->setTankIDchan4(this->_Tank5->objectID());
    this->_dataAnalyser->setTankIDchan5(this->_Tank6->objectID());

    //init PID
    QMetaObject::invokeMethod(this->_settingViewer, "setVolumePIDCoef",
                              Q_ARG(QVariant, this->_dataAnalyser->PIDVolumeCoef())
                              );

    //init smooth plot
    QMetaObject::invokeMethod(this->_settingViewer, "setSmootPlotValue",
                              Q_ARG(QVariant, this->_ads1115_1->smoothPlot())
                              );
    //init trace in plot
    //reccord time
//    QMetaObject::invokeMethod(this->_settingViewer, "setGraphicReccordTime",
//                              Q_ARG(QVariant, this->_graphicReccordTime)
//                              );

    //init ATM value in settingViewer
        QMetaObject::invokeMethod(this->_settingViewer, "setATMValue",
                                  Q_ARG(QVariant, QString::number(this->_dataAnalyser->ATMMin(),'f', 2)),
                                  Q_ARG(QVariant, QString::number(this->_dataAnalyser->ATMAvg(),'f', 2)),
                                  Q_ARG(QVariant, QString::number(this->_dataAnalyser->ATMMax(),'f', 2))
                                  );

    //nbTraceInPlot
    this->_nbTrace = this->_calculNbTraceInPlot();

    QMetaObject::invokeMethod(this->_statisticViewer, "setTankTraceNomberInGraph",
                              Q_ARG(QVariant, this->_nbTrace)
                              );

    this->_initTankColorInHomePage(this->_Tank1->objectID());
    this->_initTankColorInHomePage(this->_Tank2->objectID());
    this->_initTankColorInHomePage(this->_Tank3->objectID());
    this->_initTankColorInHomePage(this->_Tank4->objectID());
    this->_initTankColorInHomePage(this->_Tank5->objectID());
    this->_initTankColorInHomePage(this->_Tank6->objectID());

    //init IO of all MCP23017 UI object
//    this->_initMCP23017();


    this->_dataManager->startReading();
}

void Setting::_initMCP23017()
{
    qDebug() << Q_FUNC_INFO;

    //init titleText of MCP23017
    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017TitleName",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_20),
                              Q_ARG(QVariant, GlobaleStaticValue::MCP23017_1Title)
                              );
    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017TitleName",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_21),
                              Q_ARG(QVariant, GlobaleStaticValue::MCP23017_2Title)
                              );
    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017TitleName",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_22),
                              Q_ARG(QVariant, GlobaleStaticValue::MCP23017_3Title)
                              );
    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017TitleName",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_23),
                              Q_ARG(QVariant, GlobaleStaticValue::MCP23017_4Title)
                              );

    //regIODIR
    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017RegIODIR",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_20),
                              Q_ARG(QVariant, 0x0000),
                              Q_ARG(QVariant, "0x0000")
                              );

    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017RegIODIR",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_21),
                              Q_ARG(QVariant, 0xFF00),
                              Q_ARG(QVariant, "0xFF00")
                              );

    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017RegIODIR",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_22),
                              Q_ARG(QVariant, 0x00FF),
                              Q_ARG(QVariant, "0x00FF")
                              );

    QMetaObject::invokeMethod(this->_settingViewer, "setMCP23017RegIODIR",
                              Q_ARG(QVariant, MCP23017_ADDRESS_DEFAULT_23),
                              Q_ARG(QVariant, 0xFFFF),
                              Q_ARG(QVariant, "0xFFFF")
                              );

}

//void Setting::initTankObjectName(int objectID, QString objectName)
//{
//    QMetaObject::invokeMethod(this->_tankViewer, "setTankObjectName",
//                              Q_ARG(QVariant, objectID),
//                              Q_ARG(QVariant, objectName)
//                              );

//}

void Setting::_initTankColorInHomePage(int objectID)
{
    QMetaObject::invokeMethod(this->_homeViewer, "setTankColor",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, DEVICE_COLOR_READY_HEX)
                              );
}

void Setting::_initTankTitleText(int objectID, QString titleText)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_homeViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_tankViewer, "setTankTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );

    QMetaObject::invokeMethod(this->_statisticViewer, "setTankTraceTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, titleText)
                              );
}

void Setting::_initHomeViewObject(int objectID, QString obbjectName)
{
    QMetaObject::invokeMethod(this->_homeViewer, "setAllTitleText",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, obbjectName)
                              );
}

void Setting::_initTankIsVisible(int objectID, bool isVisible)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    QMetaObject::invokeMethod(this->_tankViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );

    QMetaObject::invokeMethod(this->_homeViewer, "setTankIsVisible",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
    QMetaObject::invokeMethod(this->_statisticViewer, "setupTraceIsSelected",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, isVisible)
                              );
}

void Setting::_initTankVolumeMax(int objectID, int volumeMax)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankVolumeMax",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, volumeMax)
                              );
    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
//        this->_ads1115_1->setTankChan0VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan0VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK2:
//        this->_ads1115_1->setTankChan1VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan1VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK3:
//        this->_ads1115_1->setTankChan2VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan2VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK4:
//        this->_ads1115_1->setTankChan3VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan3VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK5:
//        this->_ads1115_2->setTankChan0VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan4VolumeMax(volumeMax);
        break;
    case GlobalEnumerate::TANK6:
//        this->_ads1115_2->setTankChan1VolumeMax(volumeMax);
        this->_dataAnalyser->setTankChan5VolumeMax(volumeMax);
        break;
    default:
        break;
    }
}

void Setting::_initTankWarningLowLevel(int objectID, int warningLowLevel)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setWarningLowLevel",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, warningLowLevel)
                              );
}

void Setting::_initTankLiquideInside(int objectID, int tankLiquideInside)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setTankLiquideInside",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, tankLiquideInside)
                              );

    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
//        this->_ads1115_1->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        this->_dataAnalyser->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK2:
//        this->_ads1115_1->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        this->_dataAnalyser->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK3:
//        this->_ads1115_1->setTankChan2LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        this->_dataAnalyser->setTankChan2LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK4:
//        this->_ads1115_1->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        this->_dataAnalyser->setTankChan3LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK5:
//        this->_ads1115_2->setTankChan0LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        this->_dataAnalyser->setTankChan4LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    case GlobalEnumerate::TANK6:
//        this->_ads1115_2->setTankChan1LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        this->_dataAnalyser->setTankChan5LiquideInside((GlobalEnumerate::E_TankLiquidInside)tankLiquideInside);
        break;
    default:
        break;
    }
}

void Setting::_initHeightVMaxValue(int objectID, int HeightVMaxValue)
{
    QMetaObject::invokeMethod(this->_tankViewer, "setHeightVMaxValue",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, HeightVMaxValue)
                              );

    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
//        this->_ads1115_1->setTankChan0VolumeMaxHeightInMilimeter(HeightVMaxValue);
        this->_dataAnalyser->setTankChan0VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK2:
//        this->_ads1115_1->setTankChan1VolumeMaxHeightInMilimeter(HeightVMaxValue);
        this->_dataAnalyser->setTankChan1VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK3:
//        this->_ads1115_1->setTankChan2VolumeMaxHeightInMilimeter(HeightVMaxValue);
        this->_dataAnalyser->setTankChan2VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK4:
//        this->_ads1115_1->setTankChan3VolumeMaxHeightInMilimeter(HeightVMaxValue);
        this->_dataAnalyser->setTankChan3VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK5:
//        this->_ads1115_2->setTankChan0VolumeMaxHeightInMilimeter(HeightVMaxValue);
        this->_dataAnalyser->setTankChan0VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    case GlobalEnumerate::TANK6:
//        this->_ads1115_2->setTankChan1VolumeMaxHeightInMilimeter(HeightVMaxValue);
        this->_dataAnalyser->setTankChan1VolumeMaxHeightInMilimeter(HeightVMaxValue);
        break;
    default:
        break;
    }
}

void Setting::_initTankOffsetPressure(int objectID, int OffsetPressure)
{
    QMetaObject::invokeMethod(this->_settingViewer, "setOffsetPressure",
                              Q_ARG(QVariant, objectID),
                              Q_ARG(QVariant, OffsetPressure)
                              );
}

quint8 Setting::_calculNbTraceInPlot()
{
    return(this->_Tank1->isVisible()+
           this->_Tank2->isVisible()+
           this->_Tank3->isVisible()+
           this->_Tank4->isVisible()+
           this->_Tank5->isVisible()+
           this->_Tank6->isVisible()
           );
}

void Setting::_saveSettings()
{
    //save application setting values
    QString groupeNameSetting = GlobaleStaticValue::saveGroupeNameApplicationSettingTxt;
    this->_setting->beginGroup(groupeNameSetting);
    //Grafic reccord time set on setting page
    this->_setting->setValue(GlobaleStaticValue::GraphicReccordTime, this->_graphicReccordTime);
    //ADS1115, 0v value in puls for the 4-10ma to 0-5v converter chanel 0
    this->_setting->setValue(GlobaleStaticValue::ADS115_0V_Chan0_ValueInPlus, this->_setting->value(GlobaleStaticValue::ADS115_0V_Chan0_ValueInPlus, 0).toInt());
    //ADS1115, 0v value in puls for the 4-10ma to 0-5v converter chanel 1
    this->_setting->setValue(GlobaleStaticValue::ADS115_0V_Chan1_ValueInPlus, this->_setting->value(GlobaleStaticValue::ADS115_0V_Chan1_ValueInPlus, 0).toInt());
    //ADS1115, 5v value in puls for the 4-10ma to 0-5v converter chanel 0
    this->_setting->setValue(GlobaleStaticValue::ADS115_5V_Chan0_ValueInPlus, this->_setting->value(GlobaleStaticValue::ADS115_5V_Chan0_ValueInPlus, 26000).toInt());
    //ADS1115, 5v value in puls for the 4-10ma to 0-5v converter chanel 1
    this->_setting->setValue(GlobaleStaticValue::ADS115_5V_Chan1_ValueInPlus, this->_setting->value(GlobaleStaticValue::ADS115_5V_Chan1_ValueInPlus, 26000).toInt());
    //ADS1115, tank volume PID coef
    this->_setting->setValue(GlobaleStaticValue::Volume_PID_coef, this->_dataAnalyser->PIDVolumeCoef());
    //ATM coef
    this->_setting->setValue(GlobaleStaticValue::saveATMMinTxt, this->_dataAnalyser->ATMMin());
    this->_setting->setValue(GlobaleStaticValue::saveATMAvgTxt, this->_dataAnalyser->ATMAvg());
    this->_setting->setValue(GlobaleStaticValue::saveATMMaxTxt, this->_dataAnalyser->ATMMax());

    //ADS1115, set smooth plot
    this->_setting->setValue(GlobaleStaticValue::smoothPlotTxt, this->_ads1115_1->smoothPlot());

    //path for saved data folder
    this->_setting->setValue(GlobaleStaticValue::saveDataMainTxt, this->_dataManager->directoryDatafileName());

    //path for setting file
    this->_setting->setValue(GlobaleStaticValue::settingFileTxt, this->_setting->value(GlobaleStaticValue::settingFile, GlobaleStaticValue::settingFile).toString());
    this->_setting->endGroup();

    //save all value for tank1
    this->_saveTankSetting(this->_Tank1);

    //save all value for tank2
    this->_saveTankSetting(this->_Tank2);

    //save all value for tank3
    this->_saveTankSetting(this->_Tank3);

    //save all value for tank4
    this->_saveTankSetting(this->_Tank4);

    //save all value for tank5
    this->_saveTankSetting(this->_Tank5);

    //save all value for tank6
    this->_saveTankSetting(this->_Tank6);

}

void Setting::_saveTankSetting(Tank *tank)
{
    QString groupeName = tank->objectName();
    int objectID = this->_tankObjectNameArray.key(groupeName);

    //save all value for tank
    this->_setting->beginGroup(groupeName);
    this->_setting->setValue(GlobaleStaticValue::saveIDTxt, tank->objectID());
    this->_setting->setValue(GlobaleStaticValue::saveObjectNameTxt, tank->objectName());
    this->_setting->setValue(GlobaleStaticValue::saveTitleTxt, tank->title());
    this->_setting->setValue(GlobaleStaticValue::saveVisibleTxt, tank->isVisible());
    this->_setting->setValue(GlobaleStaticValue::saveLiquideInsideTxt, tank->LiquideFillup());
    this->_setting->setValue(GlobaleStaticValue::saveVolumeMaxTxt, tank->volumeMax());
    this->_setting->setValue(GlobaleStaticValue::saveLowLevelWarningTxt, tank->lowLevelValue());
    this->_setting->setValue(GlobaleStaticValue::saveHeightVMaxValueTxt, tank->volumeMaxHeightInMilimeter());

    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
        this->_setting->setValue(GlobaleStaticValue::saveOffsetPressureTxt, this->_dataAnalyser->offsetPressurChan0());
        break;
    case GlobalEnumerate::TANK2:
        this->_setting->setValue(GlobaleStaticValue::saveOffsetPressureTxt, this->_dataAnalyser->offsetPressurChan1());
        break;
    case GlobalEnumerate::TANK3:
        this->_setting->setValue(GlobaleStaticValue::saveOffsetPressureTxt, this->_dataAnalyser->offsetPressurChan2());
        break;
    case GlobalEnumerate::TANK4:
        this->_setting->setValue(GlobaleStaticValue::saveOffsetPressureTxt, this->_dataAnalyser->offsetPressurChan3());
        break;
    case GlobalEnumerate::TANK5:
        this->_setting->setValue(GlobaleStaticValue::saveOffsetPressureTxt, this->_dataAnalyser->offsetPressurChan4());
        break;
    case GlobalEnumerate::TANK6:
        this->_setting->setValue(GlobaleStaticValue::saveOffsetPressureTxt, this->_dataAnalyser->offsetPressurChan5());
        break;
    default:
        break;
    }

    this->_setting->endGroup();
}

void Setting::_loadSettings()
{
    //load application setting values
    QString groupeNameSetting = GlobaleStaticValue::saveGroupeNameApplicationSettingTxt;
    QString Graphic_Reccord_Time = groupeNameSetting + "/" + GlobaleStaticValue::GraphicReccordTime;
    QString ADS115_0V_Chan0_ValueInPlus = groupeNameSetting + "/" + GlobaleStaticValue::ADS115_0V_Chan0_ValueInPlus;
    QString ADS115_0V_Chan1_ValueInPlus = groupeNameSetting + "/" + GlobaleStaticValue::ADS115_0V_Chan1_ValueInPlus;
    QString ADS115_5V_Chan0_ValueInPlus = groupeNameSetting + "/" + GlobaleStaticValue::ADS115_5V_Chan0_ValueInPlus;
    QString ADS115_5V_Chan1_ValueInPlus = groupeNameSetting + "/" + GlobaleStaticValue::ADS115_5V_Chan1_ValueInPlus;
    QString Volume_PID_coef = groupeNameSetting + "/" + GlobaleStaticValue::Volume_PID_coef;
    QString directoryDatafileName = groupeNameSetting + "/" + GlobaleStaticValue::saveDataMainTxt;
    QString tempFileName = groupeNameSetting + "/" + GlobaleStaticValue::saveTempFileTxt;
    QString settingFileName = groupeNameSetting + "/" + GlobaleStaticValue::saveTempFileTxt;
    QString ATMMin = groupeNameSetting + "/" + GlobaleStaticValue::saveATMMinTxt;
    QString ATMAvg = groupeNameSetting + "/" + GlobaleStaticValue::saveATMAvgTxt;
    QString ATMMax = groupeNameSetting + "/" + GlobaleStaticValue::saveATMMaxTxt;
    QString smootPlot = groupeNameSetting + "/" + GlobaleStaticValue::smoothPlotTxt;

    //load graphic range
    this->_graphicReccordTime = (this->_setting->value(Graphic_Reccord_Time, 24).toInt());
    this->_dataAnalyser->setOffsetChan0InPuls(this->_setting->value(ADS115_0V_Chan0_ValueInPlus, 0).toInt());
    this->_dataAnalyser->setOffsetChan1InPuls(this->_setting->value(ADS115_0V_Chan1_ValueInPlus, 0).toInt());
//    this->_dataAnalyser->setOffsetChan2InPuls(this->_setting->value(ADS115_0V_Chan2_ValueInPlus, 0).toInt());
//    this->_dataAnalyser->setOffsetChan3InPuls(this->_setting->value(ADS115_0V_Chan3_ValueInPlus, 0).toInt());
//    this->_dataAnalyser->setOffsetChan4InPuls(this->_setting->value(ADS115_0V_Chan4_ValueInPlus, 0).toInt());
//    this->_dataAnalyser->setOffsetChan5InPuls(this->_setting->value(ADS115_0V_Chan5_ValueInPlus, 0).toInt());
    this->_dataAnalyser->setPIDVolumeCoef(this->_setting->value(Volume_PID_coef,1).toInt());
    this->_dataAnalyser->setChan0HighMaxValueInPuls(this->_setting->value(ADS115_5V_Chan0_ValueInPlus, 26000).toInt());
    this->_dataAnalyser->setChan1HighMaxValueInPuls(this->_setting->value(ADS115_5V_Chan1_ValueInPlus, 26000).toInt());
//    this->_dataAnalyser->setChan2HighMaxValueInPuls(this->_setting->value(ADS115_5V_Chan1_ValueInPlus, 26000).toInt());
//    this->_dataAnalyser->setChan3HighMaxValueInPuls(this->_setting->value(ADS115_5V_Chan1_ValueInPlus, 26000).toInt());
//    this->_dataAnalyser->setChan4HighMaxValueInPuls(this->_setting->value(ADS115_5V_Chan1_ValueInPlus, 26000).toInt());
//    this->_dataAnalyser->setChan5HighMaxValueInPuls(this->_setting->value(ADS115_5V_Chan1_ValueInPlus, 26000).toInt());

    this->_dataAnalyser->setATMMin(this->_setting->value(ATMMin,2000).toDouble());
    this->_dataAnalyser->setATMAvg(this->_setting->value(ATMAvg,0).toDouble());
    this->_dataAnalyser->setATMMax(this->_setting->value(ATMMax,0).toDouble());

    //set smooth plot value
    this->_ads1115_1->setSmoothPlot(this->_setting->value(smootPlot,32).toInt());

    //path for saved data folder
    this->_dataManager->setDirectoryDatafileName(this->_setting->value(directoryDatafileName, GlobaleStaticValue::saveDataMain).toString());

    //path for setting file
    this->_settingFileName = this->_setting->value(settingFileName, GlobaleStaticValue::settingFile).toString();

    //load tanks values
    _loadTankSetting(this->_Tank1);
    _loadTankSetting(this->_Tank2);
    _loadTankSetting(this->_Tank3);
    _loadTankSetting(this->_Tank4);
    _loadTankSetting(this->_Tank5);
    _loadTankSetting(this->_Tank6);

    //set used channel on ADS1115
    this->_ads1115_1->setChan0_used(this->_Tank1->isVisible());
    this->_ads1115_1->setChan1_used(this->_Tank2->isVisible());

}

void Setting::_loadTankSetting(Tank *tank)
{
    int objectID = 0;

    QString groupeName = tank->objectName();
    QString groupeNameID = groupeName + "/" + GlobaleStaticValue::saveIDTxt;
    QString groupeNameObjectName = groupeName + "/" + GlobaleStaticValue::saveObjectNameTxt;
    QString groupeNameTitle = groupeName + "/" +GlobaleStaticValue::saveTitleTxt;
    QString groupeNameVisible = groupeName + "/" + GlobaleStaticValue::saveVisibleTxt;
    QString groupeNameLiquideInside = groupeName + "/" + GlobaleStaticValue::saveLiquideInsideTxt;
    QString groupeNameVolumeMax = groupeName + "/" + GlobaleStaticValue::saveVolumeMaxTxt;
    QString groupeNameLowLevelWarning = groupeName + "/" + GlobaleStaticValue::saveLowLevelWarningTxt;
    QString groupeNameHeighVMaxValue = groupeName + "/" + GlobaleStaticValue::saveHeightVMaxValueTxt;
    QString groupeNamesetOffsetPressure = groupeName + "/" + GlobaleStaticValue::saveOffsetPressureTxt;

    tank->setObjectName(this->_setting->value(groupeNameObjectName, tank->objectName()).toString());
    tank->setTitle(this->_setting->value(groupeNameTitle, tank->objectID()).toString());
    tank->setIsVisible(this->_setting->value(groupeNameVisible, tank->isVisible()).toBool());
    tank->setLiquideFillup(this->_setting->value(groupeNameLiquideInside, GlobalEnumerate::E_TankLiquidInside::WATER).toInt());
    tank->setVolumeMax(this->_setting->value(groupeNameVolumeMax, 1500).toInt());
    tank->setLowLevelValue(this->_setting->value(groupeNameLowLevelWarning, 500).toInt());
    tank->setVolumeMaxHeightInMilimeter(this->_setting->value(groupeNameHeighVMaxValue, 1500).toInt());

    objectID = this->_setting->value(groupeNameID, 0).toInt();

    switch (objectID)
    {
    case GlobalEnumerate::TANK1:
//        this->_ads1115_1->setOffsetPressurChan0(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        this->_dataAnalyser->setOffsetPressurChan0(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        break;
    case GlobalEnumerate::TANK2:
//        this->_ads1115_1->setOffsetPressurChan1(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        this->_dataAnalyser->setOffsetPressurChan1(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        break;
    case GlobalEnumerate::TANK3:
//        this->_ads1115_1->setOffsetPressurChan2(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        this->_dataAnalyser->setOffsetPressurChan2(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        break;
    case GlobalEnumerate::TANK4:
//        this->_ads1115_1->setOffsetPressurChan3(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        this->_dataAnalyser->setOffsetPressurChan3(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        break;
    case GlobalEnumerate::TANK5:
//        this->_ads1115_2->setOffsetPressurChan0(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        this->_dataAnalyser->setOffsetPressurChan4(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        break;
    case GlobalEnumerate::TANK6:
//        this->_ads1115_2->setOffsetPressurChan1(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        this->_dataAnalyser->setOffsetPressurChan5(this->_setting->value(groupeNamesetOffsetPressure, 0).toInt());
        break;
    default:
        break;
    }




}
