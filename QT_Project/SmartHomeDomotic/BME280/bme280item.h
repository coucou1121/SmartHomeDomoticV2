#ifndef BME280ITEM_H
#define BME280ITEM_H

#include <QObject>
#include <QDebug>
#include <QDialog>
#include <QStateMachine>

#include <globalestaticvalue.h>
#include <globalstyle.h>

#include <QTimer>
#include <QThread>
#include <TimerThread.h>

#include <BME280/bme280.h>
#include <DataManager/dataFrame.h>

class BME280Item : public QThread
{
     Q_OBJECT

public:
    explicit BME280Item(quint8 deviceI2CAdress,
                        QObject *bme280Display = nullptr,
                        QObject *roomDataPlot = nullptr,
                        QObject *homeViewer = nullptr);

    void readSavedData();

    bool onReadingData() const;

    bool deviceIsReady() const;

    void setReadData(bool readData);

    DataFrame *dataFrame() const;

    void setOnReadingData(bool onReadingData);

    void setStartToReadOnData(bool startToReadOnData);

    bool startToReadOnData() const;

protected:

    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();

private:
    quint8 _deviceI2CAdress;
    quint8 _fd;
    BME280 *_bme280;
    sbme280_dev _bme280Device;
    psbme280_dev _pbme280Device;
    bool _deviceIsReady;
    bool _onReadingData;
    bool _startToReadOnData;

    quint16 _sleepingDelay;
    qint64 _timeInMilisecond;
    qint64 _memotimeInMilisecond;


    QObject *_bme280Display;
    QObject *_roomDataPlot;
    QObject *_homeViewer;

    DataFrame *_dataFrame;

    double _temperature;
    double _humidity;
    double _pressure;

    GlobalEnumerate::E_StateMachine _stateMachine;

    void _initDevice();
    void _insertTextAtHomePage(QString textToInsert);
    void _checkStateOfDevice();
    void _initRegisterDevice();
    bool _checkRegisterConfiguration();
    void _readDataI2C();

    void _waitDelay(quint64 delayInSeconde);
    void _waitDelayMili(quint64 delayInMiliSeconde);
    void _waitDelayMicro(quint64 delayInMicroSeconde);
    void _goToNextState();

public slots:

signals:
    void jumpToNextState();
};

#endif // BME280ITEM_H
