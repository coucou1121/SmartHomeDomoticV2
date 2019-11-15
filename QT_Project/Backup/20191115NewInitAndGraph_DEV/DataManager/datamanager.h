#ifndef DATAMANAGER_H
#define DATAMANAGER_H

/**
  * \file datamanager.h
  * \author Sébastien Blessemaille
  * \version 1.0
  * \date 21 november 2018
  * \brief thread to create the tick to read the data from
  * BME 280, ADS1115_1, ADS1115_2
  */

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTime>

#include <DataManager/dataFrame.h>
#include <DataManager/dataanalyser.h>

#include <BME280/bme280item.h>
#include <ADS1115/ads1115item.h>

class DataManager :  public QThread
{
    Q_OBJECT

public:

    /**
      * \fn explicit DataManager(QString name, quint32 nbFrameReadEveryCycle, quint16 delay, QObject *parent = 0)
      * \brief constructor for DataManager
      * \param[in] name is the name of the object
      * \param[in] nbFrameReadForEverySavedFile is the amont of reading data saved per file
      * \param[in] delay is the cycle time delay in miliseconds
      */
    explicit DataManager(QString name,
//                         quint32 nbFrameReadForEverySavedFile,
                         QObject *stastisticViewer,
                         QObject *bme280Display,                         
//                         QObject *statisticValueViewer,
                         DataAnalyser *dataAnalyserObject = nullptr);
    /**
      * \fn  static void msleep(qint64 msecs)
      * \brief waiting delay
      * \param[in] msleep is the time in miliseconds
      * \return void : nothing
      */
    static void msleep(qint64 msecs);

    //start real time reading
    /**
      * \fn  startReading()
      * \brief start reading operation
      * \return void : nothing
     */
    void startReading();

    /**
      * \fn  setItConsumerAdress(const QVector<DataFrame>::iterator &itConsumerAdress)
      * \brief stop reading operation
      * \return void : nothing
      */
    void stopReading();

    /**
      * \fn  ADS1115Item *ADS1115_1() const
      * \brief Getter of the ADS1115_1
      * \return ADS1115_1 : ADS1115_1 object pointer
      */
    ADS1115Item *ADS1115_1() const;

    /**
      * \fn void setADS1115_1(ADS1115 *ADS1115_1)
      * \brief Getter for ADS1115_1 attribute
      * \return void : nothing
      */
    void setADS1115_1(ADS1115Item *ADS1115_1);

    /**
      * \fn  ADS1115Item *ADS1115_2() const
      * \brief Getter of the ADS1115_1
      * \return ADS1115_2 : ADS1115_2 object pointer
      */
    ADS1115Item *ADS1115_2() const;

    /**
      * \fn void setADS1115_2(ADS1115 *ADS1115_2)
      * \brief Getter for ADS1115_2 attribute
      * \return void : nothing
      */
    void setADS1115_2(ADS1115Item *ADS1115_2);

    /**
      * \fn  BME280Item *BME280() const
      * \brief Getter of the BME280
      * \return BME280 : BME280 object pointer
      */
    BME280Item *BME280() const;

    /**
      * \fn setBME280(BME280 *BME280)
      * \brief Getter for BME280 attribute
      * \return void : nothing
      */
    void setBME280(BME280Item *BME280);

    void setDirectoryDatafileName(const QString &directoryDatafileName);

    QString directoryDatafileName() const;

    void setSleepingDelay(const qint64 &sleepingDelay);


protected:

    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();

private:
    QObject *_stastisticViewer;
    QObject *_bme280Display;

    qint64 _sleepingDelay;
    qint64 _timeInMilisecond;
    qint64 _memotimeInMilisecond;
    bool _askForStartReading;
    bool _askForStopReading;

    //ADS1115
    ADS1115Item *_ADS1115_1;
    ADS1115Item *_ADS1115_2;

    //BME280
    BME280Item *_BME280;

    //actif wait delay
    void _waitDelay(int delayInSeconde);
    void _waitDelayMili(quint64 delayInMiliSeconde);

    //temporary buffer 1 for new Datas
    QVector<DataFrame> _buffer1;
    QVector<DataFrame>::iterator _itdataFrameToWrite;

    //temporary buffer 2 for new Datas
//    QVector<DataFrame> _buffer2;
//    QVector<DataFrame>::iterator _itdataFrameBuffer2;

    //number of frame reading every cycle
//    quint32 _nbFrameReadForEverySavedFile;

    //time zone for saved file
    QDateTime _dateTime;

    //create the saveing and analysis
    DataAnalyser *_dataAnalyerObject;

    //Time formatting
    QString _time_format;

    //save data file directory
    QString _directoryDatafileName;

public slots:
    // replot
    void ReceivedreplotWithSavedData(int year, int month, int day);

signals:
    void dataFrameWasSent(int itProducerAdress);
};

#endif // DATAMANAGER_H
