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

class DataAnalyser : public QThread
{

    Q_OBJECT

public:
    DataAnalyser(quint16 nbDataFramToTempSave,
                 QObject *statisticValueViewer,
                 QObject *statisticViewer);

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

    void setSaveTempFile(bool saveTempFile);

    void setSaveFile(bool saveFile);

    void setDataFrame(DataFrame *dataFrame);

    void setItdataFrameEnd(const QVector<DataFrame>::iterator &itdataFrameEnd);

    void setNbOfSavedDataInBuffer(const quint16 &nbOfSavedDataInBuffer);

    void setResetTempFile(bool resetTempFile);

    bool saveFinished() const;

    void setDateTime(const QDateTime &dateTime);

    bool saveTempFileFinished() const;

    bool saveFileFinished() const;

protected:

    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();

private:
    QVector<DataFrame> *_buffer;
    QVector<DataFrame>::iterator _itdataFrameEnd;
    quint16 _nbOfSavedDataInBuffer;
    QList<DataFrame> _bufferTempData;

    QFile _fileTempData;

    quint16 _nbDataFramToTempSave;

    bool _saveTempFile;
    bool _saveTempFileFinished;
    bool _saveFile;
    bool _saveFileFinished;
    bool _resetTempFile;
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

    quint16 _waitDelayInMili;

    //time zone for saved file
    QDateTime _dateTime;

//    quint8 _hourToUpdate;
//    quint8 _dayToUpdate;

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

    QObject *_qobjectStastisticValueViewer;
    QObject *_statisticViewer;

    void _updateDataForTheHour(quint8 minuteToUpdate);
    void _updateDataForTheDay(QDateTime *dateToUpdate);
    void _updateDataForTheMonth(QDateTime *dateToUpdate);
    void _createDirectory(QDateTime *dateTimeToCheck);
    void _deleteHourDirectory(QDateTime *dateTimeToDelete);

public slots:
    // replot
    void ReceivedreplotWithSavedData(int year, int month, int day);

};

#endif // DATAANALYSER_H
