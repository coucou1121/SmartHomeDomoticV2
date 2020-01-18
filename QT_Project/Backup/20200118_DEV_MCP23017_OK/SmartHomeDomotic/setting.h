#ifndef SETTING_H
#define SETTING_H


#include <QObject>
#include <QDebug>

#include <QDialog>
#include <QtCore>
#include <QSettings>

#include <QMetaType>
#include <QQmlEngine>

#include <tank.h>
#include <ADS1115/ads1115item.h>
#include <BME280/bme280item.h>
#include <DataManager/datamanager.h>
#include <customplotitem.h>
#include <globalenumerate.h>
#include <globalestaticvalue.h>
#include <MCP23017/mcp2317item.h>

class Setting : public QObject
{

    Q_OBJECT

public:
    explicit Setting(QObject *parent = nullptr,
                     QObject *homeViewer = nullptr,
                     QObject *tankViewer = nullptr,
                     QObject *settingViewer = nullptr,
                     QObject *statisticViewer = nullptr,
                     DataAnalyser *dataAnalyser = nullptr,
                     BME280Item *bme280 = nullptr,
                     ADS1115Item *ads1115_1 = nullptr,
                     ADS1115Item *ads1115_2 = nullptr,
                     MCP2317item *mcp23017_1 = nullptr,
                     MCP2317item *mcp23017_2 = nullptr,
                     MCP2317item *mcp23017_3 = nullptr,
                     MCP2317item *mcp23017_4 = nullptr,
                     DataManager *dataManager = nullptr);

public slots:
    void receivedTankIsVisible(const int objectID, const bool isVisible);
    void receivedTankTitleChanged(const int objectID, const QString titleText);
    void receivedTankVolumeMaxChanged(const QString objectName, const int volumeMax);
    void receivedVolumePIDChanged(const int PIDValue);
    void receivedSmoothPlotValueChanged(const int SmoothPlotValue);
    void receivedVolumeATMChanged();
    void receivedWarningLowLevelFromTank(const QString objectName, const bool isActive);
    void receivedTankWarningLowLevelChanged(const QString objectName, const int lowLevel);
    void receivedTankLiquideFillupChanged(const QString objectName, const int liquideFillup);
    void receivedTankHeightMaxLevelChanged(const QString objectName, const int heightVMax);
    void receivedTankOffsetPressureChanged(const int objectID, const int offsetPressureValue);

    void receivedTankActualVolumeChanged(const int objectID, const int volumeActual);
    void receivedGraphReccordTimesChanged(const int reccordTime);
    void receivedOnCalibrationMode(const bool onCalibration);

    void ReceivedIODIRregChanged(const int deviceID, const int regIODIRvalue);
    void ReceivedGPIOregChanged(const int deviceID, const int regGPIOvalue);

private:

    //key value for tank object name possible
    QMap<int, QString> _tankObjectNameArray;

    //key value for home viewer object
    QMap<int, QString> _homeViewObject;

    QString _settingFileName;
    QSettings *_setting;

    Tank *_Tank1;
    Tank *_Tank2;
    Tank *_Tank3;
    Tank *_Tank4;
    Tank *_Tank5;
    Tank *_Tank6;


    bool _tankIsVisible;

    quint8 _nbTrace;
    quint8 _graphicReccordTime;

    QObject *_homeViewer;
    QObject *_tankViewer;
    QObject *_settingViewer;
    QObject *_statisticViewer;
    DataAnalyser *_dataAnalyser;

    DataManager *_dataManager;

    BME280Item *_bme280;
    ADS1115Item *_ads1115_1;
    ADS1115Item *_ads1115_2;

    MCP2317item *_mcp23017_1;
    MCP2317item *_mcp23017_2;
    MCP2317item *_mcp23017_3;
    MCP2317item *_mcp23017_4;

    void _initSetting();
    void _initMCP23017();

//    void initTankObjectName(int objectID, QString objectName);
    void _initTankColorInHomePage(int objectID);
    void _initTankTitleText(int objectID, QString isVisible);
    void _initHomeViewObject(int objectID, QString obbjectName);
    void _initTankIsVisible(int objectID, bool isVisible);
    void _initTankVolumeMax(int objectID, int volumeMax);
    void _initTankWarningLowLevel(int objectID, int warningLowLevel);
    void _initTankLiquideInside(int objectID, int tankLiquideInside);
    void _initHeightVMaxValue(int objectID, int HeightVMaxValue);
    void _initTankOffsetPressure(int objectID, int OffsetPressure);

    quint8 _calculNbTraceInPlot();
    void _saveSettings();
    void _saveTankSetting(Tank *tank);
    void _loadSettings();
    void _loadTankSetting(Tank *tank);
};

#endif // SETTING_H
