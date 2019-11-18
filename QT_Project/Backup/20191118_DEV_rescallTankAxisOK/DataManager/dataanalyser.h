#ifndef DATAANALYSER_H
#define DATAANALYSER_

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QTime>

#include <QDebug>
#include <QDir>
#include <QFile>

#include <QDateTime>
#include <globalestaticvalue.h>
#include <customplotitem.h>

class DataAnalyser : public QThread
{

    Q_OBJECT

public:
    DataAnalyser(QObject *statisticValueViewer,
                 QObject *statisticViewer,
                 QObject *settingViewer,
                 QObject *homeViewer = nullptr,
                 QObject *bme280Display = nullptr,
                 QObject *roomDataPlot = nullptr,
                 QObject *tanksDataPlot=nullptr);

    /**
      * \fn  static void msleep(unsigned long msecs)
      * \brief waiting delay
      * \param[in] msleep is the time in miliseconds
      * \return void : nothing
      */
    static void msleep(unsigned long msecs);

    void saveDataFile();

    void setBuffer(QVector<DataFrame> *buffer);

    void saveTempData(DataFrame *dataFrame);

    void savePlotData(DataFrame *dataFrame);

    void setSaveTempFile(bool saveTempFile);

    void setSaveFile(bool saveFile);

    void setDataFrame(DataFrame *dataFrame);

    //    void setItdataFrameEnd(const QVector<DataFrame>::iterator &itdataFrameEnd);

    void setNbOfSavedDataInBuffer(const quint16 &nbOfSavedDataInBuffer);

    void setResetTempFile(bool resetTempFile);

    bool saveFinished() const;

    void setDateTime(const QDateTime &dateTime);

    bool saveTempFileFinished() const;

    bool saveFileFinished() const;

    void setItdataFrameToRead(const QVector<DataFrame>::iterator &itdataFrameToRead);

    void setItdataFrameOnWriting(const QVector<DataFrame>::iterator &itdataFrameOnWriting);

    bool updateDataFrameForDataManager() const;
    void setUpdateDataFrameForDataManager(bool updateDataFrameForDataManager);

    bool saveFile() const;

    bool saveTempDataFrame() const;
    void setSaveTempDataFrame(bool saveTempDataFrame);

    void setTankIDchan0(const quint8 &tankIDchan0);

    void setTankIDchan1(const quint8 &tankIDchan1);

    void setTankIDchan2(const quint8 &tankIDchan2);

    void setTankIDchan3(const quint8 &tankIDchan3);

    qint16 offsetPressurChan0() const;
    void setOffsetPressurChan0(const qint16 &offsetPressurChan0);

    qint16 offsetPressurChan1() const;
    void setOffsetPressurChan1(const qint16 &offsetPressurChan1);

    qint16 offsetPressurChan2() const;
    void setOffsetPressurChan2(const qint16 &offsetPressurChan2);

    qint16 offsetPressurChan3() const;
    void setOffsetPressurChan3(const qint16 &offsetPressurChan3);

    qint16 offsetPressurChan4() const;
    void setOffsetPressurChan4(const qint16 &offsetPressurChan4);

    qint16 offsetPressurChan5() const;
    void setOffsetPressurChan5(const qint16 &offsetPressurChan5);




    void setDisplayPlotTime(const qint8 &displayPlotTime);

    void setTankChan0VolumeMax(const quint16 &tankChan0VolumeMax);

    void setTankChan1VolumeMax(const quint16 &tankChan1VolumeMax);

    void setTankChan2VolumeMax(const quint16 &tankChan2VolumeMax);

    void setTankChan3VolumeMax(const quint16 &tankChan3VolumeMax);

    void setTankChan4VolumeMax(const quint16 &tankChan4VolumeMax);

    void setTankChan5VolumeMax(const quint16 &tankChan5VolumeMax);

    void setTankChan0VolumeMaxHeightInMilimeter(const quint16 &tankChan0VolumeMaxHeightInMilimeter);

    void setTankChan1VolumeMaxHeightInMilimeter(const quint16 &tankChan1VolumeMaxHeightInMilimeter);

    void setTankChan2VolumeMaxHeightInMilimeter(const quint16 &tankChan2VolumeMaxHeightInMilimeter);

    void setTankChan3VolumeMaxHeightInMilimeter(const quint16 &tankChan3VolumeMaxHeightInMilimeter);

    void setOffsetChan0InPuls(const quint64 &offsetChan0InPuls);

    void setOffsetChan1InPuls(const quint64 &offsetChan1InPuls);

    void setOffsetChan2InPuls(const quint64 &offsetChan2InPuls);

    void setOffsetChan3InPuls(const quint64 &offsetChan3InPuls);

    void setOffsetChan4InPuls(const quint64 &offsetChan4InPuls);

    void setOffsetChan5InPuls(const quint64 &offsetChan5InPuls);

    void setChan0HighMaxValueInPuls(const quint64 &chan0HighMaxValueInPuls);

    void setChan1HighMaxValueInPuls(const quint64 &chan1HighMaxValueInPuls);

    void setChan2HighMaxValueInPuls(const quint64 &chan2HighMaxValueInPuls);

    void setChan3HighMaxValueInPuls(const quint64 &chan3HighMaxValueInPuls);

    void setChan4HighMaxValueInPuls(const quint64 &chan4HighMaxValueInPuls);

    void setChan5HighMaxValueInPuls(const quint64 &chan5HighMaxValueInPuls);

    void setTankChan0LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan0LiquideInside);

    void setTankChan1LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan1LiquideInside);

    void setTankChan2LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan2LiquideInside);

    void setTankChan3LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan3LiquideInside);

    void setTankChan4LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan4LiquideInside);

    void setTankChan5LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan5LiquideInside);

    void setTankIDchan4(const quint8 &tankIDchan4);

    void setTankIDchan5(const quint8 &tankIDchan5);

    qint16 PIDVolumeCoef() const;
    void setPIDVolumeCoef(const qint16 &PIDVolumeCoef);

    double ATMMin() const;
    void setATMMin(double ATMMin);


    double ATMMax() const;
    void setATMMax(double ATMMax);

    double ATMAvg() const;
    void setATMAvg(double ATMAvg);

protected:

    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();

private:
    QVector<DataFrame> *_buffer;
    QVector<DataFrame>::iterator _itdataFrameToRead;
    QVector<DataFrame>::iterator _itdataFrameOnWriting;
    //    quint16 _nbOfSavedDataInBuffer;
    QList<DataFrame> _bufferTempData;
    quint16 _sleepingDelay;
    qint64 _timeInMilisecond;
    qint64 _memotimeInMilisecond;

    QFile _fileTempData;
    QFile _filePlotsDataWriteOnly;
    QFile _filePlotsDataReadOnly;

    QStringList _listeOfData;

    //    quint16 _nbDataFramToTempSave;

    bool _saveTempDataFrame;
    bool _saveTempFile;
    bool _saveTempFileFinished;
    bool _saveFile;
    bool _saveFileFinished;
    bool _resetTempFile;
    bool _updateDataFrameFromDataManager;
    bool _updateDayData;
    bool _updateMonthData;
    //    bool _hourChanged;
    //    bool _dayChanged;
    //    bool _monthChanged;
    bool _saveFinished;

    DataFrame *_dataFrame;

    QString _directoryDataMain;
    QString _directoryFileNameYear;
    QString _directoryFileNameMonth;
    QString _directoryFileNameDay;
    QString _directoryFileNameHour;
    QString _directoryFileNameMinute;

    //    quint16 _waitDelayInMili;

    //time zone for saved file
    QDateTime _dateTime;

    //diplay time in plot
    qint8 _displayPlotTime;

    //    quint8 _hourToUpdate;
    //    quint8 _dayToUpdate;
    QObject *_bme280Display;
    QObject *_roomDataPlot;
    QObject *_tanksDataPlot;
    QObject *_settingViewer;
    QObject *_homeViewer;


    qint16 _PIDVolumeCoef;

    //    double _BME280_temperature;
    //    double _BME280_humidity;
    //    double _BME280_pressure;
    //    qint16 _ADS115_1_chan0;
    //    qint16 _ADS115_1_chan1;
    //    qint16 _ADS115_1_chan2;
    //    qint16 _ADS115_1_chan3;
    //    qint16 _ADS115_2_chan0;
    //    qint16 _ADS115_2_chan1;
    //    qint16 _ADS115_2_chan2;
    //    qint16 _ADS115_2_chan3;
    double _ATMMin;
    double _ATMAvg;
    double _ATMMax;

    double _tempMin;
    double _tempMax;
    double _humMin;
    double _humMax;
    double _pressMin;
    double _pressMax;
    qint16 _consoChan0;
    qint16 _consoChan1;
    qint16 _consoChan2;
    qint16 _consoChan3;

    double _chan0VolumeInLiter;
    double _chan1VolumeInLiter;
    double _chan2VolumeInLiter;
    double _chan3VolumeInLiter;
    double _chan4VolumeInLiter;
    double _chan5VolumeInLiter;

    QObject *_qobjectStastisticValueViewer;
    QObject *_statisticViewer;

    quint64 _offsetChan0InPuls;
    quint64 _offsetChan1InPuls;
    quint64 _offsetChan2InPuls;
    quint64 _offsetChan3InPuls;
    quint64 _offsetChan4InPuls;
    quint64 _offsetChan5InPuls;

    quint64 _chan0HighMaxValueInPuls;
    quint64 _chan1HighMaxValueInPuls;
    quint64 _chan2HighMaxValueInPuls;
    quint64 _chan3HighMaxValueInPuls;
    quint64 _chan4HighMaxValueInPuls;
    quint64 _chan5HighMaxValueInPuls;

    quint8 _tankIDchan0;
    quint8 _tankIDchan1;
    quint8 _tankIDchan2;
    quint8 _tankIDchan3;
    quint8 _tankIDchan4;
    quint8 _tankIDchan5;

    quint16 _tankChan0VolumeMax;
    quint16 _tankChan1VolumeMax;
    quint16 _tankChan2VolumeMax;
    quint16 _tankChan3VolumeMax;
    quint16 _tankChan4VolumeMax;
    quint16 _tankChan5VolumeMax;

    quint16 _tankChan0VolumeMaxHeightInMilimeter;
    quint16 _tankChan1VolumeMaxHeightInMilimeter;
    quint16 _tankChan2VolumeMaxHeightInMilimeter;
    quint16 _tankChan3VolumeMaxHeightInMilimeter;
    quint16 _tankChan4VolumeMaxHeightInMilimeter;
    quint16 _tankChan5VolumeMaxHeightInMilimeter;

    GlobalEnumerate::E_TankLiquidInside _tankChan0LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan1LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan2LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan3LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan4LiquideInside;
    GlobalEnumerate::E_TankLiquidInside _tankChan5LiquideInside;

    qint16 _offsetPressurChan0;
    qint16 _offsetPressurChan1;
    qint16 _offsetPressurChan2;
    qint16 _offsetPressurChan3;
    qint16 _offsetPressurChan4;
    qint16 _offsetPressurChan5;    

    void _waitDelay(quint64 delaySeconde);
    void _waitDelayMili(quint64 delayInMiliSeconde);
    void _waitDelayMicro(quint64 delayInMicroSeconde);

    void _updateDataForTheHour(quint8 minuteToUpdate);
    void _updateDataForTheDay(QDateTime *dateToUpdate);
    void _updateDataForTheMonth(QDateTime *dateToUpdate);
    void _createDirectory(QDateTime *dateTimeToCheck);
    void _deleteHourDirectory(QDateTime *dateTimeToDelete);

    double _convertToVolumeInLiter(quint8 channelNumber,
                                    double valueIn,
                                    quint16 tankolumeMax,
                                    quint16 tankVolumeMMaxHeightInMilimeter,
                                    GlobalEnumerate::E_TankLiquidInside liquide);

    double _offsetVolumePressure(double deltaPressure,
                                 quint16 tankolumeMax,
                                 quint16 tankVolumeMMaxHeightInMilimeter,
                                 GlobalEnumerate::E_TankLiquidInside liquide);

    void _insertTextAtHomePage(QString textToInsert);

public slots:
    // replot
    void ReceivedreplotWithSavedData(int year, int month, int day);

signals:
    void sendTankActualVolumeChanged(int objectID, int actualVolume);

};

#endif // DATAANALYSER_H
