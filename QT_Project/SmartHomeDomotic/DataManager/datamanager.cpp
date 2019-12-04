#include "datamanager.h"

DataManager::DataManager(QString name,
                         //                         quint32 nbFrameReadForEverySavedFile,
                         QObject *stastisticViewer,
                         QObject *bme280Display,
                         //                         QObject *statisticValueViewer,
                         DataAnalyser *dataAnalyserObject):
    _stastisticViewer(stastisticViewer),
    _bme280Display(bme280Display),
    //    _delay(GlobaleStaticValue::delaiToReadValue),
    _sleepingDelay(500),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0),
    _askForStartReading(false),
    _askForStopReading(false),
    _ADS1115_1(nullptr),
    _ADS1115_2(nullptr),
    _BME280(nullptr),
    _buffer1(86400),
    //    _buffer2(1000),
    //    _nbFrameReadForEverySavedFile(nbFrameReadForEverySavedFile),
    _dateTime(QDateTime::currentDateTime()),
    _dataAnalyerObject(dataAnalyserObject),
    _time_format(GlobaleStaticValue::saveTimeFormatMinuteTXT),
    _directoryDatafileName(GlobaleStaticValue::saveDataMain)
{

    //    this->_itdataFrameToWrite = GlobaleStaticValue::buffer1.begin();
    //    this->_itdataFrameBuffer2 = GlobaleStaticValue::buffer2.begin();
    this->_dataAnalyerObject->setBuffer(&this->_buffer1);
    this->_itdataFrameToWrite = this->_buffer1.begin();
    //    this->_itdataFrameBuffer2 = this->_buffer2.begin();
    this->setObjectName(name);

    moveToThread(this);

    //    this->_dataFrameBuffer1.clear();
    //    this->_dataFrameBuffer2.clear();

}

void DataManager::msleep(qint64 msecs)
{
    QThread::msleep(msecs);
}

void DataManager::startReading()
{
    this->_askForStartReading = true;
}

void DataManager::stopReading()
{
    this->_askForStopReading = true;
}

ADS1115Item *DataManager::ADS1115_1() const
{
    return _ADS1115_1;
}

void DataManager::setADS1115_1(ADS1115Item *ADS1115_1)
{
    _ADS1115_1 = ADS1115_1;
}

ADS1115Item *DataManager::ADS1115_2() const
{
    return _ADS1115_2;
}

void DataManager::setADS1115_2(ADS1115Item *ADS1115_2)
{
    _ADS1115_2 = ADS1115_2;
}

BME280Item *DataManager::BME280() const
{
    return _BME280;
}

void DataManager::setBME280(BME280Item *BME280)
{
    _BME280 = BME280;
}

void DataManager::run()
{
//    static quint64 cpt = 0;
    static bool inReadingProcess = false;
    static bool firstTimeStart = true;
    bool ADS1115_1isReady = false;
    bool ADS1115_2isReady = false;
    bool BME280isReady = false;
    quint16 dataFrameState = 0;
    //    static bool useTheBuffer2 = false;
    qint8 nextMinuteToSave = this->_dateTime.time().minute() + 1;
    static qint8 memoSecond = 0;
    qint64 sleepingDelay = 61;

    qDebug() << Q_FUNC_INFO << this->objectName() << "started";



    this->_dataAnalyerObject->setItdataFrameToRead(this->_itdataFrameToWrite);
    this->_dataAnalyerObject->setItdataFrameOnWriting(this->_itdataFrameToWrite);
    this->_dataAnalyerObject->start();

    while(true)
    {
        this->_memotimeInMilisecond = QDateTime::currentMSecsSinceEpoch();

//        sleepingDelay = this->_sleepingDelay;

        dataFrameState = 0;
        //Check all hardware are ready
        if(_askForStartReading && !inReadingProcess)
        {
            qDebug() << Q_FUNC_INFO << this->objectName() << "ask thread to start reading";

            //check the BME280, ADS1115_1 and ADS1115_2 are ready
            do
            {
                BME280isReady = this->_BME280->deviceIsReady();
                ADS1115_1isReady = this->_ADS1115_1->deviceIsReady();
                ADS1115_2isReady = this->_ADS1115_2 != nullptr ? this->_ADS1115_2->deviceIsReady() : true;
                this->msleep(1);
            }
            while(!BME280isReady || !ADS1115_1isReady || !ADS1115_2isReady);

            inReadingProcess = true;
            _askForStartReading = false;

            //           this->msleep(10000);

        }

        if(_askForStopReading)
        {
            qDebug() << this->objectName() << "thread stop reading";
            _askForStopReading = false;
            inReadingProcess = false;
        }

        if(inReadingProcess)
        {
            this->_dateTime = QDateTime::currentDateTime();

            //wait minits change to start reccording
            if(firstTimeStart)
            {
                //                while(this->_dateTime.time().minute() != nextMinuteToSave)
                //                {
                //                    this->msleep(10);
                //                    this->_dateTime = QDateTime::currentDateTime();
                //                }

                //                //set date and time to the dataframe
                //                this->_dateTime = QDateTime::currentDateTime();

//                timeInMilisecond = QDateTime::currentMSecsSinceEpoch();//- QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
                //                nextMinuteToSave = this->_dateTime.time().minute();
                firstTimeStart = false;
            }

//            qDebug() << Q_FUNC_INFO << this->objectName() << "live reading start ";


            //reccord date and time when the data is reading
            this->_itdataFrameToWrite->setDateTime(this->_dateTime);

            //wait until BME280 sensor ready to read value
            while(this->_BME280->dataFrame()->dataFrameState() != 7)
            {
                this->msleep(1);
            }

            //Copy the data from BME280 object
            this->_itdataFrameToWrite->setBME280_temperature(this->_BME280->dataFrame()->BME280_temperature());
            this->_itdataFrameToWrite->setBME280_humidity(this->_BME280->dataFrame()->BME280_humidity());
            this->_itdataFrameToWrite->setBME280_pressure(this->_BME280->dataFrame()->BME280_pressure());
            this->_itdataFrameToWrite->setDataFrameState(this->_BME280->dataFrame()->dataFrameState());

            dataFrameState += this->_itdataFrameToWrite->dataFrameState();
            //            qDebug() << Q_FUNC_INFO << "BME280 state: " << this->_itdataFrameToWrite->dataFrameState()
            //                                    << "Pressure : " << this->_itdataFrameToWrite->BME280_pressure();

            //wait until ADS1115_1 sensor ready to read value
            while(this->_ADS1115_1->dataFrame()->dataFrameState() != 24)
            {
                this->msleep(1);
            }


            //Copy the data from ADS1115_1 object
            this->_itdataFrameToWrite->setADS115_1_chan0(this->_ADS1115_1->dataFrame()->ADS115_1_chan0());
            this->_itdataFrameToWrite->setADS115_1_chan1(this->_ADS1115_1->dataFrame()->ADS115_1_chan1());
            this->_itdataFrameToWrite->setADS115_1_chan2(this->_ADS1115_1->dataFrame()->ADS115_1_chan2());
            this->_itdataFrameToWrite->setADS115_1_chan3(this->_ADS1115_1->dataFrame()->ADS115_1_chan3());
            this->_itdataFrameToWrite->setDataFrameState(this->_ADS1115_1->dataFrame()->dataFrameState());

            dataFrameState += this->_itdataFrameToWrite->dataFrameState();

            //display value of BME280 on the sidebar
            //            QMetaObject::invokeMethod(this->_bme280Display, "updateValue",
            //                                      Q_ARG(QVariant, QString::number(this->_itdataFrameToWrite->BME280_temperature(),'f', 2)),
            //                                      Q_ARG(QVariant, QString::number(this->_itdataFrameToWrite->BME280_humidity(),'f', 2)),
            //                                      Q_ARG(QVariant, QString::number(this->_itdataFrameToWrite->BME280_pressure(),'f', 1))
            //                                      );

            //do the same if _ads1115_2 existe
            if(this->_ADS1115_2 != nullptr)
            {
                //                this->_ADS1115_2->setOnReadingSavedData(true);
                //this->_ADS1115_2->setDataFrame(this->_itdataFrameToWrite);
            }

            //            qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");

            //            qDebug() << Q_FUNC_INFO <<
            //                        "DataTemp temp 2: " << this->_itdataFrameToWrite->BME280_temperature() <<
            //                        ", hum " << this->_itdataFrameToWrite->BME280_humidity() <<
            //                        ", press : " << this->_itdataFrameToWrite->BME280_pressure() <<
            //                        ", chan 0: " << this->_itdataFrameToWrite->ADS115_1_chan0() <<
            //                        ", chan 1: " << this->_itdataFrameToWrite->ADS115_1_chan1() <<
            //                        ", chan 2: " << this->_itdataFrameToWrite->ADS115_1_chan2() <<
            //                        ", chan 3: " << this->_itdataFrameToWrite->ADS115_1_chan3() <<
            //                        ", state : " << this->_itdataFrameToWrite->dataFrameState();

            this->_itdataFrameToWrite->setDataFrameState(dataFrameState);

//            //saveplot data in file, to recal in case of app restarted every second
//            if (memoSecond != this->_dateTime.time().second())
//            {
//              this->_dataAnalyerObject->savePlotData(this->_itdataFrameToWrite);
//              memoSecond = this->_dateTime.time().second();
//            }


            //add in temp file if it's the same minute
            if(this->_dateTime.time().minute() == nextMinuteToSave - 1)
            {
                while(!this->_dataAnalyerObject->saveTempFileFinished())
                {
                    this->msleep(1);
                }
                this->_dataAnalyerObject->setUpdateDataFrameForDataManager(true);
                this->_dataAnalyerObject->setDataFrame(this->_itdataFrameToWrite);
                this->_dataAnalyerObject->setSaveTempDataFrame(true);
                this->_dataAnalyerObject->setUpdateDataFrameForDataManager(false);
            }
            else
            {
                nextMinuteToSave = this->_dateTime.time().minute() + 1;

                //this->_dataAnalyerObject->setDateTime(this->_dateTime.addSecs(-60));

                this->_dataAnalyerObject->setSaveFile(true);

                this->_dataAnalyerObject->setItdataFrameToRead(this->_itdataFrameToWrite);

                this->_itdataFrameToWrite = this->_itdataFrameToWrite ==
                        this->_buffer1.end() ? this->_buffer1.begin() : this->_itdataFrameToWrite + 1;

                this->_dataAnalyerObject->setItdataFrameOnWriting(this->_itdataFrameToWrite);

                while(this->_dataAnalyerObject->saveFile() &&
                      !this->_dataAnalyerObject->saveFileFinished())
                {
                    this->msleep(1);
                }

                //                this->_dataAnalyerObject->setSaveTempFile(true);
//                cpt = 0;
            }
        }


        //live data saving in temp file
        //        while((memotimeInMilisecond+this->_delay) > timeInMilisecond)
        //            //        while((memotimeInMilisecond+1000) > timeInMilisecond)
        //        {
        //            //            qDebug() << Q_FUNC_INFO <<
        //            //                        "DataTemp temp 3: " << this->_itdataFrameToWrite->BME280_temperature() <<
        //            //                        ", hum " << this->_itdataFrameToWrite->BME280_humidity() <<
        //            //                        ", press : " << this->_itdataFrameToWrite->BME280_pressure() <<
        //            //                        ", chan 0: " << this->_itdataFrameToWrite->ADS115_1_chan0() <<
        //            //                        ", chan 1: " << this->_itdataFrameToWrite->ADS115_1_chan1() <<
        //            //                        ", chan 2: " << this->_itdataFrameToWrite->ADS115_1_chan2() <<
        //            //                        ", chan 3: " << this->_itdataFrameToWrite->ADS115_1_chan3() <<
        //            //                        ", state : " << this->_itdataFrameToWrite->dataFrameState();

        //            if(this->_dateTime.time().minute() == nextMinuteToSave)
        //            {
        //                this->_dateTime = QDateTime::currentDateTime();
        //                this->_dataAnalyerObject->setDateTime(this->_dateTime);

        //                this->_dataAnalyerObject->setDataFrame(this->_itdataFrameToWrite);
        //                this->_dataAnalyerObject->setSaveTempFile(true);
        //                do
        //                {
        //                    //                readingFinished = this->_dataAnalyerObject->saveFinished();
        //                    this->msleep(1);
        //                }
        //                while(!this->_dataAnalyerObject->saveTempFileFinished());
        //                //                this->_itdataFrameToWrite++;
        //                cpt++;
        //            }


        //            this->msleep(5000);
        //            timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        //        }


//        this->msleep(this->_waitingDelay-(timeInMilisecond - memotimeInMilisecond));

        this->_timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        sleepingDelay = (this->_timeInMilisecond - this->_memotimeInMilisecond) > this->_sleepingDelay ?
                    0 : this->_sleepingDelay - (this->_timeInMilisecond - this->_memotimeInMilisecond);

//        qDebug() << Q_FUNC_INFO << this->objectName() << "Time to read data : "
//                 << timeInMilisecond - memotimeInMilisecond << "[ms]";

        this->_waitDelayMili(sleepingDelay);



    }
}

void DataManager::setSleepingDelay(const qint64 &sleepingDelay)
{
    _sleepingDelay = sleepingDelay;
}

void DataManager::_waitDelayMili(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

QString DataManager::directoryDatafileName() const
{
    return _directoryDatafileName;
}

void DataManager::setDirectoryDatafileName(const QString &directoryDatafileName)
{
    _directoryDatafileName = directoryDatafileName;
}

void DataManager::ReceivedreplotWithSavedData(int year, int month, int day)
{
    qDebug() << "replotWithSavedData";
    QDateTime dateTimeToAnalyse =  QDateTime::currentDateTime();
    QDate dateToAnalyse;
    dateToAnalyse.setDate(year,month,day);
    dateTimeToAnalyse.setDate(dateToAnalyse);

    //    QString directoryfileName = this->_saveDataFileMainName;
    QString fileName = "";

    if(month != 0)
    {
        this->_directoryDatafileName += dateTimeToAnalyse.toString("yyyy") + "/";
        fileName += dateTimeToAnalyse.toString("yyyy-MM");
    }

    if(day != 0)
    {
        this->_directoryDatafileName += dateTimeToAnalyse.toString("MM") + "/";
        fileName = dateTimeToAnalyse.toString("yyyy-MM-dd");
    }

    QFile fileToAnalyse(this->_directoryDatafileName +  "/" + fileName + ".csv");

    QTextStream streamAnalyse(&fileToAnalyse);

    QStringList listeOfData;

//    qint8 lineNumber = 0;
    double tempMin = 200;
    double tempMax = 0;
    double humMin = 200;
    double humMax = 0 ;
    double pressMin = 2000;
    double pressMax = 0;
    qint16 consoChan0 = 0;
    qint16 consoChan1 = 0;
    qint16 consoChan2 = 0;
    qint16 consoChan3 = 0;
    qint16 consoTotal = 0;

    double memoTempMin = 200;
    double memoTempMax = 0;
    double memoHumMin = 200;
    double memoHumMax = 0 ;
    double memoPressMin = 2000;
    double memoPressMax = 0;
    qint16 memoConsoTotal = 0;
//    qint16 memoConsoTotalDayBefore = 0;

    if (fileToAnalyse.open(QFile::ReadOnly))
    {
        while (!streamAnalyse.atEnd())
        {
            QString s=fileToAnalyse.readLine(); // reads line from file
            listeOfData.append(s.split(",")); // appends first column to list, ',' is separator
            //            qDebug() << "_updateDataForTheDay" << listeOfData.count() << listeOfData[1];

            //Analyse the data
//            lineNumber = listeOfData[0].toInt();

            tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
            tempMax = listeOfData[2].toDouble() > tempMax ? listeOfData[2].toDouble() :  tempMax;

            humMin = listeOfData[3].toDouble() < humMin ? listeOfData[3].toDouble() :  humMin;
            humMax = listeOfData[4].toDouble() > humMax ? listeOfData[4].toDouble() :  humMax;

            pressMin = listeOfData[5].toDouble() < pressMin ? listeOfData[5].toDouble() :  pressMin;
            pressMax = listeOfData[6].toDouble() > pressMax ? listeOfData[6].toDouble() :  pressMax;

            consoChan0 = listeOfData[7].toInt() > consoChan0 ? listeOfData[7].toInt() :  consoChan0;
            consoChan1 = listeOfData[8].toInt() > consoChan1 ? listeOfData[8].toInt() :  consoChan1;
            consoChan2 = listeOfData[9].toInt() > consoChan2 ? listeOfData[9].toInt() :  consoChan2;
            consoChan3 = listeOfData[10].toInt() > consoChan3 ? listeOfData[10].toInt() :  consoChan3;

            consoTotal = consoChan0 + consoChan1 + consoChan2 + consoChan3;
            listeOfData.clear();

            memoTempMin = tempMin < memoTempMin ? tempMin :  memoTempMin;
            memoTempMax = tempMax > memoTempMin ? tempMax :  memoTempMin;
            memoHumMin = humMin < memoHumMin ? humMin :  memoHumMin;
            memoHumMax = humMax > memoHumMax ? humMax :  memoHumMax;
            memoPressMin = pressMin < memoPressMin ? pressMin :  memoPressMin;
            memoPressMax = pressMax > memoPressMax ? pressMax :  memoPressMax;
            memoConsoTotal += consoTotal;

        }
    }
    else
    {
        qDebug() << "cannot open fileToAnalyse" ;
    }
    fileToAnalyse.close();

    QMetaObject::invokeMethod(this->_stastisticViewer, "setStatisticValues",
                              Q_ARG(QVariant, QString::number(memoTempMin,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoTempMax,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoHumMin,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoHumMax,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoPressMin,'f', 1)),
                              Q_ARG(QVariant, QString::number(memoPressMax,'f', 1)),
                              Q_ARG(QVariant, QString::number(memoConsoTotal,'f', 0))
                              );


    //    //update screen values for today
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMinDayText", QString::number(memoTempMin, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMaxDayText", QString::number(memoTempMax, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMinDayText", QString::number(memoHumMin, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMaxDayText", QString::number(memoHumMax, 'f', 2));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMinDayText", QString::number(memoPressMin, 'f', 1));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMaxDayText", QString::number(memoPressMax, 'f', 1));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoDayText", QString::number(memoConsoTotal, 'f', 0));
    //    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoDayBeforeText", QString::number(memoConsoTotalDayBefore, 'f', 0));
}
