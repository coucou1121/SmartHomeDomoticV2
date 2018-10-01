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
#include <globalenumerate.h>
#include <globalestaticvalue.h>

#define SAVED_PATH_FILE "."
#define FILE_NAME "settings.ini"

class Setting : public QObject
{

    Q_OBJECT

public:
    explicit Setting(QObject *parent = nullptr, QObject *tankViewer = nullptr, QObject *settingViewer = nullptr);

public slots:
    void receivedTankIsVisible(const int objectID, const bool isVisible);
    void receivedTankTitleChanged(const int objectID, const QString titleText);
    void receivedTankVolumeMaxChanged(const QString objectName, const int volumeMax);
    void receivedTankWarningLowLevelChanged(const QString objectName, const int lowLevel);
    void receivedTankLiquideFillupChanged(const QString objectName, const int liquideFillup);
    void receivedTankHeightMaxLevelChanged(const QString objectName, const int heightVMax);
private:

    //key value for tank object name possible
    QMap<int, QString> _tankObjectNameArray;

    QSettings *_setting;

    Tank *_Tank1;
    Tank *_Tank2;
    Tank *_Tank3;
    Tank *_Tank4;
    Tank *_Tank5;
    Tank *_Tank6;


    bool _tankIsVisible;

    QObject *_tankViewer;
    QObject *_settingViewer;

    void initSetting();

    void initTankObjectName(int objectID, QString objectName);
    void initTankTitleText(int objectID, QString isVisible);
    void initTankIsVisible(int objectID, bool isVisible);
    void initTankVolumeMax(int objectID, int volumeMax);
    void initTankWarningLowLevel(int objectID, int warningLowLevel);
    void initTankLiquideInside(int objectID, int tankLiquideInside);
    void initHeightVMaxValue(int objectID, int HeightVMaxValue);

    void saveSettings();
    void saveTankSetting(Tank *tank);
    void loadSettings();
    void loadTankSetting(Tank *tank);
};

#endif // SETTING_H
