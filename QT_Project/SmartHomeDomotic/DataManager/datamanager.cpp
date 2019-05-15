#include "datamanager.h"

DataManager::DataManager(QObject *stastisticViewer,
                         QObject *bme280Display,
                         QString name,
                         quint32 nbFrameReadForEverySavedFile,
                         quint16 delayInMili,
                         QObject *statisticValueViewer,
                         DataAnalyser *dataAnalyserObject):
    _stastisticViewer(stastisticViewer),
    _bme280Display(bme280Display),
    _delay(GlobaleStaticValue::delaiToReadValue),
    _askForStartReading(false),
    _askForStopReading(false),
    _ADS1115_1(nullptr),
    _ADS1115_2(nullptr),
    _BME280(nullptr),
    _buffer1(nbFrameReadForEverySavedFile),
    _buffer2(nbFrameReadForEverySavedFile),
    _nbFrameReadForEverySavedFile(nbFrameReadForEverySavedFile),
    _dateTime(QDateTime::currentDateTime()),
    _dataAnalyerObject(dataAnalyserObject),
    _time_format(GlobaleStaticValue::saveTimeFormatMinuteTXT),
    _directoryDatafileName(GlobaleStaticValue::saveDataMain)
{

    //    this->_itdataFrameBuffer1 = GlobaleStaticValue::buffer1.begin();
    //    this->_itdataFrameBuffer2 = GlobaleStaticValue::buffer2.begin();
    this->_dataAnalyerObject->setBuffer(&this->_buffer1);
    this->_itdataFrameBuffer1 = this->_buffer1.begin();
    //    this->_itdataFrameBuffer2 = this->_buffer2.begin();
    this->setObjectName(name);

    moveToThread(this);

    //    this->_dataFrameBuffer1.clear();
    //    this->_dataFrameBuffer2.clear();

}

void DataManager::msleep(unsigned long msecs)
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
    static quint64 cpt = 0;
    static bool inReadingProcess = false;
    static bool firstTimeStart = true;
    bool ADS1115_1isReady = false;
    bool ADS1115_2isReady = false;
    bool BME280isReady = false;
    bool readingFinished = false;
    bool ADS1115_2isOnReading = false;
    bool BME280isOnReading = false;
    static bool useTheBuffer2 = false;
    static quint8 memoHour = this->_dateTime.time().hour();
    qint8 memoMinute = this->_dateTime.time().minute() + 1;
    QTime memoTime;
    quint8 bufferCnt = 1;
    qint64 timeInMilisecond = 0;
    qint64 memotimeInMilisecond = 0;
    qDebug() << this->objectName() << "started";



    this->_dataAnalyerObject->start();

    while(true)
    {

        if(_askForStartReading && !inReadingProcess)
        {
            qDebug() << this->objectName() << "ask thread to start reading";

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
            this->_dataAnalyerObject->setDateTime(this->_dateTime);

            if(firstTimeStart)
            {
                do
                {
                    this->_dateTime = QDateTime::currentDateTime();
                    this->msleep(10);
                }
                while(this->_dateTime.time().minute() != memoMinute);

                this->_dateTime = QDateTime::currentDateTime();
                this->_dataAnalyerObject->setDateTime(this->_dateTime);

                timeInMilisecond = QDateTime::currentMSecsSinceEpoch();//- QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
                memoMinute = this->_dateTime.time().minute();
                firstTimeStart = false;
            }
            memotimeInMilisecond = timeInMilisecond;

            //get current date and time
            //            this->_dateTime = QDateTime::currentDateTime();

            //ask to read one data
            this->_BME280->setStartToReadOnData(true);
            this->_ADS1115_1->setStartToReadOnData(true);

            //wait they finished
            while(this->_BME280->onReadingData() ||
                  this->_BME280->startToReadOnData() ||
                  this->_ADS1115_1->onReadingData() ||
                  this->_ADS1115_1->startToReadOnData())
            {
                this->msleep(10);
            }

            //copy the data from BME280 and ADS1115 object
            this->_itdataFrameBuffer1->setBME280_temperature(this->_BME280->dataFrame()->BME280_temperature());
            this->_itdataFrameBuffer1->setBME280_humidity(this->_BME280->dataFrame()->BME280_humidity());
            this->_itdataFrameBuffer1->setBME280_pressure(this->_BME280->dataFrame()->BME280_pressure());
            this->_itdataFrameBuffer1->setADS115_1_chan0(this->_ADS1115_1->dataFrame()->ADS115_1_chan0());
            this->_itdataFrameBuffer1->setADS115_1_chan1(this->_ADS1115_1->dataFrame()->ADS115_1_chan1());
            this->_itdataFrameBuffer1->setADS115_1_chan2(this->_ADS1115_1->dataFrame()->ADS115_1_chan2());
            this->_itdataFrameBuffer1->setADS115_1_chan3(this->_ADS1115_1->dataFrame()->ADS115_1_chan3());

            //display value of BME280 on the sidebar
            QMetaObject::invokeMethod(this->_bme280Display, "updateValue",
                                      Q_ARG(QVariant, QString::number(this->_itdataFrameBuffer1->BME280_temperature(),'f', 2)),
                                      Q_ARG(QVariant, QString::number(this->_itdataFrameBuffer1->BME280_humidity(),'f', 2)),
                                      Q_ARG(QVariant, QString::number(this->_itdataFrameBuffer1->BME280_pressure(),'f', 1))
                                      );

            //do the same if _ads1115_2 existe
            if(this->_ADS1115_2 != nullptr)
            {
                //                this->_ADS1115_2->setOnReadingSavedData(true);
                //this->_ADS1115_2->setDataFrame(this->_itdataFrameBuffer1);
            }

//            qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss");

            //            qDebug() << Q_FUNC_INFO <<
            //                        "DataTemp temp: " << this->_itdataFrameBuffer1->BME280_temperature() <<
            //                        ", hum " << this->_itdataFrameBuffer1->BME280_humidity() <<
            //                        ", press : " << this->_itdataFrameBuffer1->BME280_pressure() <<
            //                        ", chan 0: " << this->_itdataFrameBuffer1->ADS115_1_chan0() <<
            //                        ", chan 1: " << this->_itdataFrameBuffer1->ADS115_1_chan1() <<
            //                        ", chan 2: " << this->_itdataFrameBuffer1->ADS115_1_chan2() <<
            //                        ", chan 3: " << this->_itdataFrameBuffer1->ADS115_1_chan3() ;

            if(this->_dateTime.time().minute() == memoMinute)
            {
                this->_dataAnalyerObject->setDataFrame(this->_itdataFrameBuffer1);
                this->_dataAnalyerObject->setSaveTempFile(true);
                do
                {
                    //                readingFinished = this->_dataAnalyerObject->saveFinished();
                    this->msleep(1);
                }
                while(!this->_dataAnalyerObject->saveTempFileFinished());
                //                this->_itdataFrameBuffer1++;
                cpt++;
            }
            else
            {
                if(!useTheBuffer2)
                {
                    this->_itdataFrameBuffer1 = _buffer2.begin();
                    useTheBuffer2 = true;
                    this->_dataAnalyerObject->setBuffer(&this->_buffer1);
                }
                else
                {
                    this->_itdataFrameBuffer1 = _buffer1.begin();
                    useTheBuffer2 = false;
                    this->_dataAnalyerObject->setBuffer(&this->_buffer2);
                }
                //                this->_dataAnalyerObject->setItdataFrameEnd(this->_itdataFrameBuffer1);
                //                this->_dataAnalyerObject->setNbOfSavedDataInBuffer(cpt);

                //                this->_dataAnalyerObject->setDateTime(this->_dateTime);
                //               this->_dataAnalyerObject->setDateTime(memoDateTime);
                memoMinute = this->_dateTime.time().minute();
                //                memoTime = this->_dateTime.time();
                //                memoTime.setHMS(memoTime.hour(),memoMinute-1,memoTime.second());
                //                this->_dateTime.setTime(memoTime);
                this->_dataAnalyerObject->setDateTime(this->_dateTime.addSecs(-60));

                this->_dataAnalyerObject->setSaveFile(true);

                do
                {
                    this->msleep(10);
                }
                while(!this->_dataAnalyerObject->saveFileFinished());
                //          this->_dataAnalyerObject->saveFile(_dateTime.toString(this->_time_format), cpt);

                this->_dataAnalyerObject->setSaveTempFile(true);
                cpt = 0;
            }
        }

        timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();

        while((memotimeInMilisecond+this->_delay) > timeInMilisecond)
        {
            this->msleep(10);
            timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        }
        //        this->msleep(_delay-100);
    }
}

void DataManager::setDelay(const quint16 &delay)
{
    _delay = delay;
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

    qint8 lineNumber = 0;
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
    qint16 memoConsoTotalDayBefore = 0;

    if (fileToAnalyse.open(QFile::ReadOnly))
    {
        while (!streamAnalyse.atEnd())
        {
            QString s=fileToAnalyse.readLine(); // reads line from file
            listeOfData.append(s.split(",")); // appends first column to list, ',' is separator
            //            qDebug() << "_updateDataForTheDay" << listeOfData.count() << listeOfData[1];

            //Analyse the data
            lineNumber = listeOfData[0].toInt();

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
