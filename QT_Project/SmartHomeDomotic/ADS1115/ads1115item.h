#ifndef ADS1115ITEM_H
#define ADS1115ITEM_H

#define VALUE_IN_VOLTS 0

#include <QObject>
#include <QDebug>
#include <QDialog>
#include <QStateMachine>

#include <globalestaticvalue.h>
#include <globalstyle.h>

#include <QTimer>
#include <QThread>
#include <TimerThread.h>
//#include <globalestaticvalue.h>

#include <ADS1115/ads1115.h>
#include <DataManager/dataFrame.h>

class ADS1115Item : public QThread
{
    Q_OBJECT

public:
    explicit ADS1115Item(QString deviceName,
                         quint8 deviceI2CAdress,
                         QObject *ADS1115Display = nullptr,
                         QObject *roomDataPlot = nullptr,
                         timerthread *I2CThread = nullptr,
                         QObject *homeViewer = nullptr);

    adsRate_t ads_rate() const;
    void setAds_rate(const adsRate_t &ads_rate);

    bool deviceIsReady() const;

    void setTankChan0VolumeMax(const quint16 &tankChan0VolumeMax);

    void setTankChan1VolumeMax(const quint16 &tankChan1VolumeMax);

    void setTankChan2VolumeMax(const quint16 &tankChan2VolumeMax);

    void setTankChan3VolumeMax(const quint16 &tankChan3VolumeMax);

    void setTankChan0LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan0LiquideInside);

    void setTankChan1LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan1LiquideInside);

    void setTankChan2LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan2LiquideInside);

    void setTankChan3LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan3LiquideInside);

    void setTankIDchan0(const quint8 &tankIDchan0);

    void setTankIDchan1(const quint8 &tankIDchan1);

    void setTankIDchan2(const quint8 &tankIDchan2);

    void setTankIDchan3(const quint8 &tankIDchan3);

    void setTankChan0VolumeMaxHeightInMilimeter(const quint16 &tankChan0VolumeMaxHeightInMilimeter);

    void setTankChan1VolumeMaxHeightInMilimeter(const quint16 &tankChan1VolumeMaxHeightInMilimeter);

    void setTankChan2VolumeMaxHeightInMilimeter(const quint16 &tankChan2VolumeMaxHeightInMilimeter);

    void setTankChan3VolumeMaxHeightInMilimeter(const quint16 &tankChan3VolumeMaxHeightInMilimeter);

    bool onReadingData() const;

    void readSavedData();

    DataFrame *dataFrame() const;

    void setStartToReadOnData(bool startToReadOnData);

    bool startToReadOnData() const;

    void setOnCalibration(bool onCalibration);

    void setHighMaxValueInPuls(const quint64 &highMaxValueInPuls);

protected:

    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();

private:

    QObject *_tanksDataPlot;
    QObject *_homeViewer;
    timerthread *_I2CThread;
    QString _deviceName;
    quint8 _deviceI2CAdress;
    quint8 _fd;
    ADS1115 *_ads1115;

    DataFrame *_dataFrame;

    adsRate_t _ads_rate;
    bool _deviceIsReady;
    bool _onReadingData;
    bool _startToReadOnData;
    bool _onCalibration;

    quint64 _highMaxValueInPuls;

    quint8 _tankIDchan0;
    quint8 _tankIDchan1;
    quint8 _tankIDchan2;
    quint8 _tankIDchan3;

    quint16 _tankChan0VolumeMax;
    quint16 _tankChan1VolumeMax;
    quint16 _tankChan2VolumeMax;
    quint16 _tankChan3VolumeMax;

    quint16 _tankChan0VolumeMaxHeightInMilimeter;
    quint16 _tankChan1VolumeMaxHeightInMilimeter;
    quint16 _tankChan2VolumeMaxHeightInMilimeter;
    quint16 _tankChan3VolumeMaxHeightInMilimeter;

    GlobalEnumerate::E_TankLiquidInside _tankChan0LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan1LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan2LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan3LiquideInside;

    QList<quint16> _filterListeChan0;
    QList<quint16> _filterListeChan1;
    QList<quint16> _filterListeChan2;
    QList<quint16> _filterListeChan3;

#if VALUE_IN_VOLTS
    double _chan0;
    double _chan1;
    double _chan2;
    double _chan3;
#else
    qint16 _chan0;
    qint16 _chan1;
    qint16 _chan2;
    qint16 _chan3;
#endif
    GlobalEnumerate::E_StateMachine _stateMachine;

    void _initDevice();

    void _insertTextAtHomePage(QString textToInsert);
    void _checkStateOfDevice();
    void _initConfigDevice();
    bool _checkRegisterConfiguration();
    void _readDataI2C(DataFrame *dataFrame = nullptr);
    quint16 _convertToVolumeInLiter(qint16 valueIn,
                                    quint16 tankolumeMax,
                                    quint16 tankVolumeMMaxHeightInMilimeter,
                                    GlobalEnumerate::E_TankLiquidInside liquide);

    void _continueReadingAllValue();
    void _waitDelay(quint64 delaySeconde);
    void _waitDelayMili(quint64 delayInMiliSeconde);
    void _waitDelayMicro(quint64 delayInMicroSeconde);
    void _goToNextState();

    quint16 _meanList(QList<quint16> &listToMean);

public slots:

signals:
    void sendTankActualVolumeChanged(int objectID, int actualVolume);
};

#endif // ADS1115ITEM_H
