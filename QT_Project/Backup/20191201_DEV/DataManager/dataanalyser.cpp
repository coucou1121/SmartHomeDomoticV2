#include "dataanalyser.h"

DataAnalyser::DataAnalyser(QObject *statisticValueViewer,
                           QObject *statisticViewer,
                           QObject *settingViewer, QObject *homeViewer,
                           QObject *bme280Display,
                           QObject *roomDataPlot,
                           QObject *tanksDataPlot):
    _sleepingDelay(200),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0),
    _fileTempData(GlobaleStaticValue::saveTempFile),
    _filePlotsDataWriteOnly(GlobaleStaticValue::savePlotDataFileWriteOnly),
    _filePlotsDataReadOnly(GlobaleStaticValue::savePlotDataFileReadOnly),
    //    _nbDataFramToTempSave(nbDataFramToTempSave),
    _saveTempDataFrame(false),
    _saveTempFile(false),
    _saveTempFileFinished(true),
    _saveFile(false),
    _saveFileFinished(true),
    _resetTempFile(true),
    _updateDataFrameFromDataManager(true),
    _updateDayData(false),
    _updateMonthData(false),
    _ATMMinSet(false),
    _ATMMaxSet(false),
    _ATMAvgSet(false),
    //   _hourChanged(false),
    //   _dayChanged(false),
    //   _monthChanged(false),
    _saveFinished(true),
    _dataFrame(nullptr),
    _directoryDataMain(GlobaleStaticValue::saveDataMain),
    _directoryFileNameYear(""),
    _directoryFileNameMonth(""),
    _directoryFileNameDay(""),
    _directoryFileNameHour(""),
    _directoryFileNameMinute(""),
    //    _nbOfSavedDataInBuffer(nbDataFramToTempSave),
    //    _waitDelayInMili(500),
    _dateTime(QDateTime::currentDateTime()),
    _displayPlotTime(24),
    _bme280Display(bme280Display),
    _roomDataPlot(roomDataPlot),
    _tanksDataPlot(tanksDataPlot),
    _settingViewer(settingViewer),
    _homeViewer(homeViewer),
    _PIDVolumeCoef(1),
    //    _hourToUpdate(00),
    //    _dayToUpdate(25),
    //    _BME280_temperature(0),
    //    _BME280_humidity(0),
    //    _BME280_pressure(0),
    //    _ADS115_1_chan0(0),
    //    _ADS115_1_chan1(0),
    //    _ADS115_1_chan2(0),
    //    _ADS115_1_chan3(0),
    //    _ADS115_2_chan0(0),
    //     ADS115_2_chan1(0),
    //    _ADS115_2_chan2(0),
    //    _ADS115_2_chan3(0),
    _ATMMin(2000),
    _ATMAvg(0),
    _ATMMax(0),
    _tempMin(200),
    _tempMax(0),
    _humMin(110),
    _humMax(0),
    _pressMin(2000),
    _pressMax(0),
    _consoChan0(0),
    _consoChan1(0),
    _consoChan2(0),
    _consoChan3(0),
    _chan0VolumeInLiter(0),
    _chan1VolumeInLiter(0),
    _chan2VolumeInLiter(0),
    _chan3VolumeInLiter(0),
    _chan4VolumeInLiter(0),
    _chan5VolumeInLiter(0),
    _qobjectStastisticValueViewer(statisticValueViewer),
    _statisticViewer(statisticViewer),
    _offsetChan0InPuls(0),
    _offsetChan1InPuls(0),
    _offsetChan2InPuls(0),
    _offsetChan3InPuls(0),
    _offsetChan4InPuls(0),
    _offsetChan5InPuls(0),
    _chan0HighMaxValueInPuls(26000),
    _chan1HighMaxValueInPuls(26000),
    _chan2HighMaxValueInPuls(26000),
    _chan3HighMaxValueInPuls(26000),
    _chan4HighMaxValueInPuls(26000),
    _chan5HighMaxValueInPuls(26000),
    _tankIDchan0(0),
    _tankIDchan1(0),
    _tankIDchan2(0),
    _tankIDchan3(0),
    _tankIDchan4(0),
    _tankIDchan5(0),
    _tankChan0VolumeMax(0),
    _tankChan1VolumeMax(0),
    _tankChan2VolumeMax(0),
    _tankChan3VolumeMax(0),
    _tankChan4VolumeMax(0),
    _tankChan5VolumeMax(0),
    _tankChan0VolumeMaxHeightInMilimeter(0),
    _tankChan1VolumeMaxHeightInMilimeter(0),
    _tankChan2VolumeMaxHeightInMilimeter(0),
    _tankChan3VolumeMaxHeightInMilimeter(0),
    _tankChan4VolumeMaxHeightInMilimeter(0),
    _tankChan5VolumeMaxHeightInMilimeter(0),
    _tankChan0LiquideInside(GlobalEnumerate::WATER),
    _tankChan1LiquideInside(GlobalEnumerate::WATER),
    _tankChan2LiquideInside(GlobalEnumerate::WATER),
    _tankChan3LiquideInside(GlobalEnumerate::WATER),
    _tankChan4LiquideInside(GlobalEnumerate::WATER),
    _tankChan5LiquideInside(GlobalEnumerate::WATER),
    _offsetPressurChan0(0),
    _offsetPressurChan1(0),
    _offsetPressurChan2(0),
    _offsetPressurChan3(0),
    _offsetPressurChan4(0),
    _offsetPressurChan5(0)
{
    moveToThread(this);
    this->_createDirectory(&_dateTime);
}

void DataAnalyser::msleep(unsigned long msecs)
{
    QThread::msleep(msecs);
}

void DataAnalyser::saveDataFile()
{
    static qint8 memoHour = this->_dateTime.time().hour();
    static qint8 memoDay = this->_dateTime.date().day();

    quint8 hourNow = QDateTime::currentDateTime().time().hour();
    quint8 dayNow = QDateTime::currentDateTime().date().day();

    this->_createDirectory(&_dateTime);

    QString fileNameMinute = this->_dateTime.toString(GlobaleStaticValue::saveTimeFormatMinuteTXT);

    QFile::copy(GlobaleStaticValue::saveTempFile, this->_directoryFileNameHour + "/" + fileNameMinute + ".csv");

    //reset file fileTempData
    //    while(!this->_fileTempData.isWritable())
    //    {
    //        this->msleep(10);
    //    }

    if (this->_fileTempData.open(QFile::WriteOnly|QFile::Truncate))
    {
    }

    this->_fileTempData.close();
    this->_bufferTempData.clear();


    QMetaObject::invokeMethod(this->_settingViewer, "setATMValue",
                              Q_ARG(QVariant, QString::number(this->_ATMMin,'f', 2)),
                              Q_ARG(QVariant, QString::number(this->_ATMAvg,'f', 2)),
                              Q_ARG(QVariant, QString::number(this->_ATMMax,'f', 2))
                              );

    this->_updateDataForTheHour(this->_dateTime.time().minute());

    //check if hour changed, then update the day Data
    if(memoHour != hourNow)
    {
        this->_updateDayData = true;
        memoHour = hourNow;
    }

    //check if day changed, then update the month Data
    if(memoDay != dayNow)
    {
        this->_updateMonthData = true;
        memoDay = dayNow;
    }

}

void DataAnalyser::setBuffer(QVector<DataFrame> *buffer)
{
    _buffer = buffer;
}

void DataAnalyser::saveTempData(DataFrame *dataFrame)
{
    this->_dateTime = dataFrame->dateTime();

    //    static int i = 0;

    //    this->_bufferTempData.append(*dataFrame);
    //    bool checkDataFrameNotEmpty = false;
    //    checkDataFrameNotEmpty =        dataFrame->BME280_temperature() +
    //            dataFrame->BME280_humidity() + dataFrame->BME280_pressure() +
    //            dataFrame->ADS115_1_chan0() +  dataFrame->ADS115_1_chan1() +
    //            dataFrame->ADS115_1_chan2() + dataFrame->ADS115_1_chan3();


    QTextStream stream(&this->_fileTempData);

    this->_ATMMin = dataFrame->BME280_pressure() < this->_ATMMin ? dataFrame->BME280_pressure() : this->_ATMMin;
    this->_ATMMax = dataFrame->BME280_pressure() > this->_ATMMax ? dataFrame->BME280_pressure() : this->_ATMMax;
    this->_ATMAvg = ((this->_ATMMin + this ->_ATMMax)/2);

    //    if((this->_bufferTempData.count()>0) && (this->_bufferTempData.count() < this->_nbDataFramToTempSave))
    //    {
    //        if(!(this->_bufferTempData.count() % 1))
    //        {

    //           qDebug() << "save Temp ";
    //    qDebug() << Q_FUNC_INFO << this->_dateTime.toString(GlobaleStaticValue::saveTimeFormatMinuteTXT);

    //    do
    //    {
    //        this->msleep(10);
    //    }
    //    while(!this->_fileTempData.isWritable());
    if (dataFrame->dataFrameState()==31 && this->_fileTempData.open(QFile::WriteOnly|QFile::Append))

        //    if (checkDataFrameNotEmpty && this->_fileTempData.open(QFile::WriteOnly|QFile::Append))
    {
        //                for(int j = i; j<this->_bufferTempData.size(); j++)
        //                {
        stream << this->_dateTime.time().second() << ", "
               << dataFrame->BME280_temperature() << ", "
               << dataFrame->BME280_humidity() << ", "
               << dataFrame->BME280_pressure() << ", "
               << this->_chan0VolumeInLiter + this->_offsetPressurChan0 <<  ", "
               << this->_chan1VolumeInLiter + this->_offsetPressurChan1 << ", "
               << this->_chan2VolumeInLiter + this->_offsetPressurChan2 << ", "
               << this->_chan3VolumeInLiter + this->_offsetPressurChan3 << ", "
               << this->_chan4VolumeInLiter + this->_offsetPressurChan3 << ", "
               << this->_chan5VolumeInLiter + this->_offsetPressurChan3 << endl;
        //                    i=j;
        //                }
        //            }
        this->_fileTempData.close();

        if(this->_fileTempData.permissions() != GlobaleStaticValue::filePermissions)
        {
            this->_fileTempData.setPermissions(GlobaleStaticValue::filePermissions);
        }
        //        i++;
        //        i = i > 59 ? 0 : i;
    }


    //    }
    //    else
    //    {
    //        i = 0;

    //        if (this->_fileTempData.open(QFile::WriteOnly|QFile::Truncate))
    //        {
    //        }

    //        this->_fileTempData.close();
    //        this->_bufferTempData.clear();
    //    }

    //        qDebug() << Q_FUNC_INFO << ", checkDataFrameNotEmpty : " << checkDataFrameNotEmpty <<
    //                    "dataTempCount : " << this->_bufferTempData.count() <<
    //                    "DataTemp temp: " << dataFrame->BME280_temperature() <<
    //                    ", hum " << dataFrame->BME280_humidity() <<
    //                    ", press : " << dataFrame->BME280_pressure() <<
    //                    ", chan 0: " << dataFrame->ADS115_1_chan0() <<
    //                    ", chan 1: " << dataFrame->ADS115_1_chan1() <<
    //                    ", chan 2: " << dataFrame->ADS115_1_chan2() <<
    //                        ", chan 3: " << dataFrame->ADS115_1_chan3() ;
}

void DataAnalyser::savePlotData(DataFrame *dataFrame)
{

    //    qDebug() << Q_FUNC_INFO << "dataframe state: " << dataFrame->dataFrameState();
    static bool iniWrtieFileDone = false;
    bool copyOk = false;
    bool setPermissionOK = false;
    //    static quint64 listSize = 0;
    QString str="";

    QTextStream streamRead(&this->_filePlotsDataReadOnly);
    QTextStream streamWrite(&this->_filePlotsDataWriteOnly);
    QTextStream streamToList(&str);

    if(!iniWrtieFileDone)
    {
        if (_filePlotsDataReadOnly.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            this->_listeOfData.clear();

            while (!_filePlotsDataReadOnly.atEnd())
            {
                this->_listeOfData.append(_filePlotsDataReadOnly.readLine());
            }
        }

        this->_filePlotsDataReadOnly.close();
        //        listSize = this->_listeOfData.size();
        iniWrtieFileDone = true;
    }


    if (dataFrame->dataFrameState() == 31 && this->_filePlotsDataReadOnly.open(QFile::WriteOnly|QFile::Append))
    {
        streamRead << this->_dateTime.toMSecsSinceEpoch() << ", " <<  dataFrame->BME280_temperature() << ", " << dataFrame->BME280_humidity() << ", "
                   << dataFrame->BME280_pressure() << ", "
                   << this->_chan0VolumeInLiter + this->_offsetPressurChan0 <<  ", "
                   << this->_chan1VolumeInLiter + this->_offsetPressurChan1 <<  ", "
                   << this->_chan2VolumeInLiter + this->_offsetPressurChan2 <<  ", "
                   << this->_chan3VolumeInLiter + this->_offsetPressurChan3 <<  ", "
                   << this->_chan4VolumeInLiter + this->_offsetPressurChan4 <<  ", "
                   << this->_chan5VolumeInLiter + this->_offsetPressurChan5 << endl;

        streamToList << this->_dateTime.toMSecsSinceEpoch() << ", " <<  dataFrame->BME280_temperature() << ", " << dataFrame->BME280_humidity() << ", "
                     << dataFrame->BME280_pressure() << ", "
                     << this->_chan0VolumeInLiter + this->_offsetPressurChan0 <<  ", "
                     << this->_chan1VolumeInLiter + this->_offsetPressurChan1 <<  ", "
                     << this->_chan2VolumeInLiter + this->_offsetPressurChan2 <<  ", "
                     << this->_chan3VolumeInLiter + this->_offsetPressurChan3 <<  ", "
                     << this->_chan4VolumeInLiter + this->_offsetPressurChan4 <<  ", "
                     << this->_chan5VolumeInLiter + this->_offsetPressurChan5 << endl;

        //        listSize++;
        this->_listeOfData.append(str);
        this->_filePlotsDataReadOnly.close();
    }

//    qDebug() << Q_FUNC_INFO << ", :liste size:" << this->_listeOfData.size();

    if(this->_listeOfData.size() > NB_OF_SECONDE_IN_PLOT)
    {
        ///remove the oldest minuts
        while(this->_listeOfData.size() > (NB_OF_SECONDE_IN_PLOT - 60))
        {
            this->_listeOfData.removeFirst();
        }

        //copy buffer to write only
        if (this->_filePlotsDataWriteOnly.open(QFile::WriteOnly | QFile::Truncate))
        {
            for (int i = 0; i < this->_listeOfData.size(); ++i)
            {
                streamWrite << this->_listeOfData.at(i);
            }
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "error opening _filePlotsDataWriteOnly file\n";
        }
        this->_filePlotsDataWriteOnly.close();





        QFile::remove(GlobaleStaticValue::savePlotDataFileReadOnly);
        copyOk = QFile::copy(GlobaleStaticValue::savePlotDataFileWriteOnly, GlobaleStaticValue::savePlotDataFileReadOnly);
        qDebug() << Q_FUNC_INFO << "copyOk :" << copyOk;
    }

    //    QFileDevice::Permissions filePermission = QFileDevice::ReadOwner |
    //            // QFileDevice::ReadGroup |
    //            QFileDevice::WriteOwner |
    //            // QFileDevice::WriteGroup |
    //            QFileDevice::ExeOwner;
    if(this->_filePlotsDataWriteOnly.exists() &&
            this->_filePlotsDataReadOnly.permissions() != GlobaleStaticValue::filePermissions)
    {
        setPermissionOK =  this->_filePlotsDataReadOnly.setPermissions(GlobaleStaticValue::filePermissions);
        qDebug() << Q_FUNC_INFO << "setPermissionOK: " << setPermissionOK;
        qDebug() << "GlobaleStaticValue::filePermissions permission :\t" << GlobaleStaticValue::filePermissions;
        qDebug() << "_filePlotsDataReadOnly permission :\t\t" << _filePlotsDataReadOnly.permissions();
    }

    if(this->_filePlotsDataWriteOnly.exists() &&
            this->_filePlotsDataWriteOnly.permissions() != GlobaleStaticValue::filePermissions)
    {
        setPermissionOK = this->_filePlotsDataWriteOnly.setPermissions(GlobaleStaticValue::filePermissions);
        qDebug() << Q_FUNC_INFO << "setPermissionOK: " << setPermissionOK;
        qDebug() << "GlobaleStaticValue::filePermissions permission :\t" << GlobaleStaticValue::filePermissions;
        qDebug() << "_filePlotsDataWriteOnly permission : \t\t" << _filePlotsDataWriteOnly.permissions();
    }
}

void DataAnalyser::run()
{
    //    qDebug() << Q_FUNC_INFO;

    qint64 sleepingDelay = 0;
    static qint8 cpt = this->_displayPlotTime;
    static double memoStartPressure = 0;
    double offsetLiquidePressure = 0;
    static qint8 memoSecond = 0;

    while(this->_dataFrame == nullptr)
    {
        this->_waitDelayMili(1);
    }

    while(!this->_ATMAvgSet && !this->_ATMMaxSet && !this->_ATMMinSet)
    {
        this->_waitDelayMili(1);
    }

//    memoStartPressure = this->_dataFrame->BME280_pressure();
    memoStartPressure = this->_ATMAvg;

    while(true)
    {
        this->_memotimeInMilisecond = QDateTime::currentMSecsSinceEpoch();

        this->_saveFinished = false;

        //offset volum because of ATM
        //convert puls in liter
        if(this->_dataFrame->ADS115_1_chan0() > 0)
        {

            offsetLiquidePressure = this->_offsetVolumePressure((this->_ATMAvg - memoStartPressure),
                                                                this->_tankChan0VolumeMax,
                                                                this->_tankChan0VolumeMaxHeightInMilimeter,
                                                                this->_tankChan0LiquideInside );

            this->_chan0VolumeInLiter = this->_convertToVolumeInLiter(0,
                                                                      this->_dataFrame->ADS115_1_chan0(),
                                                                      this->_tankChan0VolumeMax,
                                                                      this->_tankChan0VolumeMaxHeightInMilimeter,
                                                                      this->_tankChan0LiquideInside);
//            this->_chan0VolumeInLiter -= offsetLiquidePressure;

        }
        else
        {
            this->_chan0VolumeInLiter = 0;
        }

        if(this->_dataFrame->ADS115_1_chan1() > 0)
        {
            offsetLiquidePressure = this->_offsetVolumePressure((this->_ATMAvg - memoStartPressure),
                                                                this->_tankChan1VolumeMax,
                                                                this->_tankChan1VolumeMaxHeightInMilimeter,
                                                                this->_tankChan1LiquideInside );

            this->_chan1VolumeInLiter = this->_convertToVolumeInLiter(1,
                                                                      this->_dataFrame->ADS115_1_chan1(),
                                                                      this->_tankChan1VolumeMax,
                                                                      this->_tankChan1VolumeMaxHeightInMilimeter,
                                                                      this->_tankChan1LiquideInside);
//            this->_chan1VolumeInLiter -= offsetLiquidePressure;

            //            qDebug() << Q_FUNC_INFO << "offsetLiquidePressure: " << offsetLiquidePressure
            //                     << "_chan0VolumeInLiter : " << this->_chan1VolumeInLiter;

        }
        else
        {
            this->_chan1VolumeInLiter = 0;
        }

        //saveplot data every second in file, to recall in case of app restarted for fill up the plot
        if (memoSecond != this->_dataFrame->dateTime().time().second())
        {
            this->savePlotData(this->_dataFrame);
            memoSecond = this->_dataFrame->dateTime().time().second();

            sendTankActualVolumeChanged(this->_tankIDchan0, (this->_chan0VolumeInLiter + this->_offsetPressurChan0));
            sendTankActualVolumeChanged(this->_tankIDchan1, (this->_chan1VolumeInLiter + this->_offsetPressurChan1));


//            qDebug() << Q_FUNC_INFO << "ATMAvg" << this->_ATMAvg << "memoStartPressure: " << memoStartPressure << "offsetLiquidePressure: " << offsetLiquidePressure
//                     << ", PIDVolumeCoef(): " << 1+((double)this->_PIDVolumeCoef/100) << "_chan0VolumeInLiter : " << this->_chan0VolumeInLiter;

        }

        //Save temp data to tempFile
        if(this->_saveTempDataFrame)
        {
            cpt--;
            while(this->_updateDataFrameFromDataManager)
            {
                this->msleep(1);
            }
            this->_saveTempFileFinished = false;
            saveTempData(this->_dataFrame);
            this->_saveTempFileFinished = true;
            this->_saveTempDataFrame = false;


            if(cpt < 0)
            {
                //                sendTankActualVolumeChanged(this->_tankIDchan0, (this->_dataFrame->ADS115_1_chan0() + this->_offsetPressurChan0));
                //                sendTankActualVolumeChanged(this->_tankIDchan1, (this->_dataFrame->ADS115_1_chan1() + this->_offsetPressurChan1));

                //                qDebug() << Q_FUNC_INFO << cpt;

                QMetaObject::invokeMethod(this->_roomDataPlot, "addYValue",
                                          Q_ARG(QVariant, QString::number(this->_dataFrame->BME280_temperature(),'f', 2)),
                                          Q_ARG(QVariant, QString::number(this->_dataFrame->BME280_humidity(),'f', 2)),
                                          Q_ARG(QVariant, QString::number(this->_dataFrame->BME280_pressure(),'f', 2)),
                                          Q_ARG(QVariant, 0),
                                          Q_ARG(QVariant, 0),
                                          Q_ARG(QVariant, 0)
                                          );

                //                QMetaObject::invokeMethod(this->_tanksDataPlot, "addYValue",
                //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan0()),
                //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan1()),
                //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan2()),
                //                                          Q_ARG(QVariant, this->_dataFrame->ADS115_1_chan3()),
                //                                          Q_ARG(QVariant, 0),
                //                                          Q_ARG(QVariant, 0)
                //                                          );

                QMetaObject::invokeMethod(this->_tanksDataPlot, "addYValue",
                                          Q_ARG(QVariant, this->_chan0VolumeInLiter + this->_offsetPressurChan0),
                                          Q_ARG(QVariant, this->_chan1VolumeInLiter + this->_offsetPressurChan1),
                                          Q_ARG(QVariant, this->_chan2VolumeInLiter + this->_offsetPressurChan2),
                                          Q_ARG(QVariant, this->_chan3VolumeInLiter + this->_offsetPressurChan3),
                                          Q_ARG(QVariant, this->_chan4VolumeInLiter + this->_offsetPressurChan4),
                                          Q_ARG(QVariant, this->_chan5VolumeInLiter + this->_offsetPressurChan5)
                                          );
                cpt = this->_displayPlotTime;
            }

            QMetaObject::invokeMethod(this->_bme280Display, "updateValue",
                                      Q_ARG(QVariant, QString::number(this->_dataFrame->BME280_temperature(),'f', 2)),
                                      Q_ARG(QVariant, QString::number(this->_dataFrame->BME280_humidity(),'f', 2)),
                                      Q_ARG(QVariant, QString::number(this->_dataFrame->BME280_pressure(),'f', 2))
                                      );

        }

        //Copy tempFile to a minute file
        if(this->_saveFile)
        {
            this->_saveFileFinished = false;
            //            this->_dateTime = this->_itdataFrameToRead->dateTime();
            //            this->_dateTime.addSecs(-60);
            saveDataFile();
            this->_saveFileFinished = true;
            //            this->_itdataFrameToRead = this->_itdataFrameOnWriting;
            this->_saveFile = false;
        }


        if(this->_updateDayData)
        {
            this->_updateDayData = false;
            _updateDataForTheDay(&this->_dateTime);
        }

        if(this->_updateMonthData)
        {
            this->_updateMonthData = false;
            _updateDataForTheMonth(&this->_dateTime);
        }

        this->_saveFinished = true;

        if(this->_resetTempFile)
        {
            this->_resetTempFile = false;
            if (this->_fileTempData.open(QFile::WriteOnly|QFile::Truncate))
            {
            }

            this->_fileTempData.close();
            this->_bufferTempData.clear();
        }

        this->_timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        sleepingDelay = (this->_timeInMilisecond - this->_memotimeInMilisecond) > this->_sleepingDelay ?
                    0 : this->_sleepingDelay - (this->_timeInMilisecond - this->_memotimeInMilisecond);

        //        qDebug() << Q_FUNC_INFO << this->objectName() << "Time to read data : "
        //                 << this->_timeInMilisecond - this->_memotimeInMilisecond << "[ms]";

        this->_waitDelayMili(sleepingDelay);

    }

}

double DataAnalyser::ATMAvg() const
{
    return _ATMAvg;
}

void DataAnalyser::setATMAvg(double ATMAvg)
{
    this->_ATMAvgSet = true;
    _ATMAvg = ATMAvg;
}

double DataAnalyser::ATMMax() const
{
    return _ATMMax;
}

void DataAnalyser::setATMMax(double ATMMax)
{
    _ATMMax = ATMMax;
    this->_ATMMaxSet = true;
}

double DataAnalyser::ATMMin() const
{
    return _ATMMin;
}

void DataAnalyser::setATMMin(double ATMMin)
{
    _ATMMin = ATMMin;
    this->_ATMMinSet = true;
}

qint16 DataAnalyser::PIDVolumeCoef() const
{
    return _PIDVolumeCoef;
}

void DataAnalyser::setPIDVolumeCoef(const qint16 &PIDVolumeCoef)
{
    _PIDVolumeCoef = PIDVolumeCoef;
}

void DataAnalyser::setTankIDchan5(const quint8 &tankIDchan5)
{
    _tankIDchan5 = tankIDchan5;
}

void DataAnalyser::setTankIDchan4(const quint8 &tankIDchan4)
{
    _tankIDchan4 = tankIDchan4;
}

void DataAnalyser::setTankChan5LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan5LiquideInside)
{
    _tankChan5LiquideInside = tankChan5LiquideInside;
}

void DataAnalyser::setTankChan4LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan4LiquideInside)
{
    _tankChan4LiquideInside = tankChan4LiquideInside;
}

void DataAnalyser::setTankChan3LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan3LiquideInside)
{
    _tankChan3LiquideInside = tankChan3LiquideInside;
}

void DataAnalyser::setTankChan2LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan2LiquideInside)
{
    _tankChan2LiquideInside = tankChan2LiquideInside;
}

void DataAnalyser::setTankChan1LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan1LiquideInside)
{
    _tankChan1LiquideInside = tankChan1LiquideInside;
}

void DataAnalyser::setTankChan0LiquideInside(const GlobalEnumerate::E_TankLiquidInside &tankChan0LiquideInside)
{
    _tankChan0LiquideInside = tankChan0LiquideInside;
}

void DataAnalyser::setChan5HighMaxValueInPuls(const quint64 &chan5HighMaxValueInPuls)
{
    _chan5HighMaxValueInPuls = chan5HighMaxValueInPuls;
}

void DataAnalyser::setChan4HighMaxValueInPuls(const quint64 &chan4HighMaxValueInPuls)
{
    _chan4HighMaxValueInPuls = chan4HighMaxValueInPuls;
}

void DataAnalyser::setChan3HighMaxValueInPuls(const quint64 &chan3HighMaxValueInPuls)
{
    _chan3HighMaxValueInPuls = chan3HighMaxValueInPuls;
}

void DataAnalyser::setChan2HighMaxValueInPuls(const quint64 &chan2HighMaxValueInPuls)
{
    _chan2HighMaxValueInPuls = chan2HighMaxValueInPuls;
}

void DataAnalyser::setChan1HighMaxValueInPuls(const quint64 &chan1HighMaxValueInPuls)
{
    _chan1HighMaxValueInPuls = chan1HighMaxValueInPuls;
}

void DataAnalyser::setChan0HighMaxValueInPuls(const quint64 &chan0HighMaxValueInPuls)
{
    _chan0HighMaxValueInPuls = chan0HighMaxValueInPuls;
}

void DataAnalyser::setOffsetChan5InPuls(const quint64 &offsetChan5InPuls)
{
    _offsetChan5InPuls = offsetChan5InPuls;
}

void DataAnalyser::setOffsetChan4InPuls(const quint64 &offsetChan4InPuls)
{
    _offsetChan4InPuls = offsetChan4InPuls;
}

void DataAnalyser::setOffsetChan3InPuls(const quint64 &offsetChan3InPuls)
{
    _offsetChan3InPuls = offsetChan3InPuls;
}

void DataAnalyser::setOffsetChan2InPuls(const quint64 &offsetChan2InPuls)
{
    _offsetChan2InPuls = offsetChan2InPuls;
}

void DataAnalyser::setOffsetChan1InPuls(const quint64 &offsetChan1InPuls)
{
    _offsetChan1InPuls = offsetChan1InPuls;
}

void DataAnalyser::setOffsetChan0InPuls(const quint64 &offsetChan0InPuls)
{
    _offsetChan0InPuls = offsetChan0InPuls;
}

void DataAnalyser::setTankChan3VolumeMaxHeightInMilimeter(const quint16 &tankChan3VolumeMaxHeightInMilimeter)
{
    _tankChan3VolumeMaxHeightInMilimeter = tankChan3VolumeMaxHeightInMilimeter;
}

void DataAnalyser::setTankChan2VolumeMaxHeightInMilimeter(const quint16 &tankChan2VolumeMaxHeightInMilimeter)
{
    _tankChan2VolumeMaxHeightInMilimeter = tankChan2VolumeMaxHeightInMilimeter;
}

void DataAnalyser::setTankChan1VolumeMaxHeightInMilimeter(const quint16 &tankChan1VolumeMaxHeightInMilimeter)
{
    _tankChan1VolumeMaxHeightInMilimeter = tankChan1VolumeMaxHeightInMilimeter;
}

void DataAnalyser::setTankChan0VolumeMaxHeightInMilimeter(const quint16 &tankChan0VolumeMaxHeightInMilimeter)
{
    _tankChan0VolumeMaxHeightInMilimeter = tankChan0VolumeMaxHeightInMilimeter;
}

void DataAnalyser::setTankChan5VolumeMax(const quint16 &tankChan5VolumeMax)
{
    _tankChan5VolumeMax = tankChan5VolumeMax;
}

void DataAnalyser::setTankChan4VolumeMax(const quint16 &tankChan4VolumeMax)
{
    _tankChan4VolumeMax = tankChan4VolumeMax;
}

void DataAnalyser::setTankChan3VolumeMax(const quint16 &tankChan3VolumeMax)
{
    _tankChan3VolumeMax = tankChan3VolumeMax;
}

void DataAnalyser::setTankChan2VolumeMax(const quint16 &tankChan2VolumeMax)
{
    _tankChan2VolumeMax = tankChan2VolumeMax;
}

void DataAnalyser::setTankChan1VolumeMax(const quint16 &tankChan1VolumeMax)
{
    _tankChan1VolumeMax = tankChan1VolumeMax;
}

void DataAnalyser::setTankChan0VolumeMax(const quint16 &tankChan0VolumeMax)
{
    _tankChan0VolumeMax = tankChan0VolumeMax;
}

void DataAnalyser::setDisplayPlotTime(const qint8 &displayPlotTime)
{
    _displayPlotTime = displayPlotTime;
}

qint16 DataAnalyser::offsetPressurChan5() const
{
    return _offsetPressurChan5;
}

qint16 DataAnalyser::offsetPressurChan4() const
{
    return _offsetPressurChan4;
}

qint16 DataAnalyser::offsetPressurChan3() const
{
    return _offsetPressurChan3;
}

qint16 DataAnalyser::offsetPressurChan2() const
{
    return _offsetPressurChan2;
}

qint16 DataAnalyser::offsetPressurChan1() const
{
    return _offsetPressurChan1;
}

qint16 DataAnalyser::offsetPressurChan0() const
{
    return _offsetPressurChan0;
}

void DataAnalyser::setOffsetPressurChan5(const qint16 &offsetPressurChan5)
{
    _offsetPressurChan5 = offsetPressurChan5;
}

void DataAnalyser::setOffsetPressurChan4(const qint16 &offsetPressurChan4)
{
    _offsetPressurChan4 = offsetPressurChan4;
}

void DataAnalyser::setTankIDchan3(const quint8 &tankIDchan3)
{
    _tankIDchan3 = tankIDchan3;
}

void DataAnalyser::setTankIDchan2(const quint8 &tankIDchan2)
{
    _tankIDchan2 = tankIDchan2;
}

void DataAnalyser::setTankIDchan1(const quint8 &tankIDchan1)
{
    _tankIDchan1 = tankIDchan1;
}

void DataAnalyser::setTankIDchan0(const quint8 &tankIDchan0)
{
    _tankIDchan0 = tankIDchan0;
}

void DataAnalyser::setOffsetPressurChan3(const qint16 &offsetPressurChan3)
{
    _offsetPressurChan3 = offsetPressurChan3;
}

void DataAnalyser::setOffsetPressurChan2(const qint16 &offsetPressurChan2)
{
    _offsetPressurChan2 = offsetPressurChan2;
}

void DataAnalyser::setOffsetPressurChan1(const qint16 &offsetPressurChan1)
{
    _offsetPressurChan1 = offsetPressurChan1;
}

void DataAnalyser::setOffsetPressurChan0(const qint16 &offsetPressurChan0)
{
    _offsetPressurChan0 = offsetPressurChan0;
}

bool DataAnalyser::saveTempDataFrame() const
{
    return _saveTempDataFrame;
}

void DataAnalyser::setSaveTempDataFrame(bool saveTempDataFrame)
{
    _saveTempDataFrame = saveTempDataFrame;
}

bool DataAnalyser::saveFile() const
{
    return _saveFile;
}

bool DataAnalyser::updateDataFrameForDataManager() const
{
    return _updateDataFrameFromDataManager;
}

void DataAnalyser::setUpdateDataFrameForDataManager(bool updateDataFrameForDataManager)
{
    _updateDataFrameFromDataManager = updateDataFrameForDataManager;
}

void DataAnalyser::_waitDelay(quint64 delaySeconde)
{
    QThread::sleep(delaySeconde);
}

void DataAnalyser::_waitDelayMili(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

void DataAnalyser::_waitDelayMicro(quint64 delayInMicroSeconde)
{
    QThread::usleep(delayInMicroSeconde);
}

void DataAnalyser::setItdataFrameOnWriting(const QVector<DataFrame>::iterator &itdataFrameOnWriting)
{
    _itdataFrameOnWriting = itdataFrameOnWriting;
}


void DataAnalyser::setItdataFrameToRead(const QVector<DataFrame>::iterator &itdataFrameToRead)
{
    _itdataFrameToRead = itdataFrameToRead;
}

bool DataAnalyser::saveFileFinished() const
{
    return _saveFileFinished;
}

bool DataAnalyser::saveTempFileFinished() const
{
    return _saveTempFileFinished;
}

void DataAnalyser::_updateDataForTheHour(quint8 minuteToUpdate)
{
    static bool fistDataToUpdate = true;
    static double memoVolumeTotal = 0;

    QDateTime dateTimeToSave =  this->_dateTime;
    QTime timeToSave = this->_dateTime.time();
    timeToSave.setHMS(timeToSave.hour(),minuteToUpdate,0);
    dateTimeToSave.setTime(timeToSave);

    QString fileNameMinute = dateTimeToSave.toString(GlobaleStaticValue::saveTimeFormatMinuteTXT);
    QString fileNameDay = dateTimeToSave.toString(GlobaleStaticValue::saveTimeFormatDayTXT);
    QString fileNameHour = fileNameDay + "_" + dateTimeToSave.toString("hh");

    QFile fileMinute(this->_directoryFileNameHour + "/" + fileNameMinute + ".csv");
    QFile fileHour(this->_directoryFileNameDay +  "/" + fileNameHour + ".csv");

    QTextStream streamMinute(&fileMinute);
    QTextStream streamHour(&fileHour);

    QStringList listeOfData;

    //    qint8 hourNumber = 0;
    double tempMin = 273;
    double tempMax = -273;
    double humMin = 273;
    double humMax = -273;
    double pressMin = 2000;
    double pressMax = -2000;
    double volumeChan0 = 0;
    double volumeChan1 = 0;
    double volumeChan2 = 0;
    double volumeChan3 = 0;
    double volumeTotal = 0;
    //    double VolumeTotalMin = 32000;
    double volumeConsoTotal = 0;


    if (fileMinute.open(QFile::ReadOnly))
    {
        quint16 cpt = 0;

        while (!streamMinute.atEnd())
        {
            QString s=streamMinute.readLine(); // reads line from file
            listeOfData.append(s.split(",")); // appends first column to list, ',' is separator

            //Analyse the data
            //            hourNumber = listeOfData[0].toInt();

            tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
            tempMax = listeOfData[1].toDouble() > tempMax ? listeOfData[1].toDouble() :  tempMax;

            humMin = listeOfData[2].toDouble() < humMin ? listeOfData[2].toDouble() :  humMin;
            humMax = listeOfData[2].toDouble() > humMax ? listeOfData[2].toDouble() :  humMax;

            pressMin = listeOfData[3].toDouble() < pressMin ? listeOfData[3].toDouble() :  pressMin;
            pressMax = listeOfData[3].toDouble() > pressMax ? listeOfData[3].toDouble() :  pressMax;

            volumeChan0 += listeOfData[4].toDouble();
            volumeChan1 += listeOfData[5].toDouble();
            volumeChan2 += listeOfData[6].toDouble();
            volumeChan3 += listeOfData[7].toDouble();

            //            volumeConsoTotal += listeOfData[11].toInt();
            listeOfData.clear();
            cpt++;
        }

        volumeChan0 = volumeChan0/cpt;
        volumeChan1 = volumeChan1/cpt;
        volumeChan2 = volumeChan2/cpt;
        volumeChan3 = volumeChan3/cpt;

        //        volumeChan0 = (quint32)qRound((double)volumeChan0/cpt);
        //        volumeChan1 = (quint32)qRound((double)volumeChan1/cpt);
        //        volumeChan2 = (quint32)qRound((double)volumeChan2/cpt);
        //        volumeChan3 = (quint32)qRound((double)volumeChan3/cpt);

        volumeTotal = volumeChan0 + volumeChan1 + volumeChan2 + volumeChan3;

    }
    else
    {
        qDebug() << "cannot open fileMinute";
    }
    fileMinute.close();

    fileMinute.setPermissions(GlobaleStaticValue::filePermissions);

    if(fistDataToUpdate)
    {
        fistDataToUpdate =  false;
        memoVolumeTotal = volumeTotal;
    }

    volumeConsoTotal = memoVolumeTotal - volumeTotal;
    volumeConsoTotal = volumeConsoTotal < 0.3 ? 0 : volumeConsoTotal;

    qDebug() << Q_FUNC_INFO << minuteToUpdate << ", "
             << tempMin << ", " << tempMax << ", " << humMin << ", " << humMax <<  ", "
             << pressMin << ", " << pressMax << ", " << volumeChan0 << ", " << volumeChan1 <<  ", "
             << volumeChan2 << ", " << volumeChan3 << ", "
             << memoVolumeTotal << ", " << volumeTotal << ", " << volumeConsoTotal << "\n";

    memoVolumeTotal = volumeTotal;
    volumeTotal = 0;

    //update the minute time data in hour file
    if (fileHour.open(QFile::WriteOnly|QFile::Append))
    {
        streamHour << minuteToUpdate << ", "
                   << tempMin << ", " << tempMax << ", " << humMin << ", " << humMax <<  ", "
                   << pressMin << ", " << pressMax << ", " << volumeChan0 << ", " << volumeChan1 <<  ", "
                   << volumeChan2 << ", " << volumeChan3 << ", "
                   << memoVolumeTotal << ", " << volumeConsoTotal << "\n";
    }
    else
    {
        qDebug() << "cannot open fileHour";
    }
    fileHour.close();

    fileHour.setPermissions(GlobaleStaticValue::filePermissions);
}

void DataAnalyser::setDateTime(const QDateTime &dateTime)
{
    _dateTime = dateTime;
}

bool DataAnalyser::saveFinished() const
{
    return _saveFinished;
}

void DataAnalyser::_updateDataForTheDay(QDateTime *dateToUpdate)
{
    QString fileNameDay = dateToUpdate->toString(GlobaleStaticValue::saveTimeFormatDayTXT);
    QTime hourToRead = dateToUpdate->time();
    //    QString fileNameHour = fileNameDay + "_" + dateToUpdate->toString("hh");

    QFile fileDay(this->_directoryFileNameMonth + "/" + fileNameDay + ".csv");

    QTextStream streamDay(&fileDay);

    QStringList listeOfData;

    //    qint8 hourNumber = 0;
    double tempMin = 200;
    double tempMax = 0;
    double humMin = 200;
    double humMax = 0 ;
    double pressMin = 2000;
    double pressMax = 0;
    double memoTempMin = 200;
    double memoTempMax = 0;
    double memoHumMin = 200;
    double memoHumMax = 0 ;
    double memoPressMin = 2000;
    double memoPressMax = 0;
    double volumeChan0 = 0;
    double volumeChan1 = 0;
    double volumeChan2 = 0;
    double volumeChan3 = 0;
    double volumeTotal = 0;
    //    double memoVolumeChan0 = 0;
    //    double memoVolumeChan1 = 0;
    //    double memoVolumeChan2 = 0;
    //    double memoVolumeChan3 = 0;
    double memoVolumeTotal = 0;
    double VolumeTotalMin = 32000;
    double consumThisHour = 0;
    double memoConsumThisHour = 0;

    //reset day file
    if (fileDay.open(QFile::WriteOnly|QFile::Truncate))
    {
    }

    fileDay.close();

    //read all hour file
    for(int i=0; i<24; i++)
    {
        hourToRead.setHMS(i, 0, 0 );
        dateToUpdate->setTime(hourToRead);

        //        hourNumber = 0;
        tempMin = 200;
        tempMax = 0;
        humMin = 200;
        humMax = 0 ;
        pressMin = 2000;
        pressMax = 0;
        volumeChan0 = 0;
        volumeChan1 = 0;
        volumeChan2 = 0;
        volumeChan3 = 0;
        volumeTotal = 0;
        //        memoVolumeChan0 = 0;
        //        memoVolumeChan1 = 0;
        //        memoVolumeChan2 = 0;
        //        memoVolumeChan3 = 0;
        consumThisHour = 0;

        QString fileNameHour = fileNameDay + "_" + dateToUpdate->toString("hh");
        QFile fileHour(this->_directoryFileNameDay +  "/" + fileNameHour + ".csv");
        QTextStream streamHour(&fileHour);

        if (fileHour.open(QFile::ReadOnly))
        {
            //read hour file
            while (!streamHour.atEnd())
            {
                QString s=streamHour.readLine(); // reads line from file
                listeOfData.append(s.split(",")); // appends first column to list, ',' is separator
                //            qDebug() << "_updateDataForTheDay" << listeOfData.count() << listeOfData[1];

                //Analyse the data
                //                hourNumber = listeOfData[0].toUtf8().at(0);

                tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
                tempMax = listeOfData[2].toDouble() > tempMax ? listeOfData[2].toDouble() :  tempMax;

                humMin = listeOfData[3].toDouble() < humMin ? listeOfData[3].toDouble() :  humMin;
                humMax = listeOfData[4].toDouble() > humMax ? listeOfData[4].toDouble() :  humMax;

                pressMin = listeOfData[5].toDouble() < pressMin ? listeOfData[5].toDouble() :  pressMin;
                pressMax = listeOfData[6].toDouble() > pressMax ? listeOfData[6].toDouble() :  pressMax;

                volumeChan0 = listeOfData[7].toDouble();
                volumeChan1 = listeOfData[8].toDouble();
                volumeChan2 = listeOfData[9].toDouble();
                volumeChan3 = listeOfData[10].toDouble();
                volumeTotal = listeOfData[11].toDouble();
                consumThisHour += listeOfData[12].toDouble();

                memoTempMin = memoTempMin < tempMin ? memoTempMin :  tempMin;
                memoTempMax = memoTempMax > tempMax ? memoTempMax :  tempMax;
                memoHumMin = memoHumMin < humMin ? memoHumMin :  humMin;
                memoHumMax = memoHumMax > humMax ? memoHumMax :  humMax;
                memoPressMin = memoPressMin < pressMin ? memoPressMin :  pressMin;
                memoPressMax = memoPressMax > pressMax ? memoPressMax :  pressMax;

                memoVolumeTotal = volumeTotal > memoVolumeTotal ? volumeTotal : memoVolumeTotal;
                VolumeTotalMin = volumeTotal < VolumeTotalMin ? volumeTotal : VolumeTotalMin;

                listeOfData.clear();
            }
        }
        else
        {
            qDebug() << "cannot open fileHour";
        }
        fileHour.close();

        qDebug() << Q_FUNC_INFO << i << ", "
                 << tempMin << ", " << tempMax << ", " << humMin << ", " << humMax <<  ", "
                 << pressMin << ", " << pressMax << ", "
                 << volumeChan0 << ", " << volumeChan1 <<  ", "
                 << volumeChan2 << ", " << volumeChan3 << ", "
                 << volumeTotal << ", " << consumThisHour << "\n";

        //conso calculation
        //        memoConsumThisHour = memoVolumeTotal - VolumeTotalMin;

        //
        //update the day
        if (fileHour.exists() && fileDay.open(QFile::WriteOnly|QFile::Append))
        {
            streamDay << i << ", "
                      << tempMin << ", " << tempMax << ", " << humMin << ", " << humMax <<  ", "
                      << pressMin << ", " << pressMax << ", "
                      << volumeChan0 << ", " << volumeChan1 <<  ", "
                      << volumeChan2 << ", " << volumeChan3 << ", "
                      << volumeTotal << ", " << consumThisHour << "\n";
        }
        else
        {
            qDebug() << "cannot open fileDay";
        }
        fileDay.close();


        //delete hour directory
        //this->_deleteHourDirectory(dateToUpdate);

    }

    //update screen values for today
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMinDayText", QString::number(memoTempMin, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMaxDayText", QString::number(memoTempMax, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMinDayText", QString::number(memoHumMin, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMaxDayText", QString::number(memoHumMax, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMinDayText", QString::number(memoPressMin, 'f', 1));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMaxDayText", QString::number(memoPressMax, 'f', 1));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoDayText", QString::number(memoConsumThisHour, 'f', 0));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoDayBeforeText", QString::number(memoVolumeTotal, 'f', 0));


    fileDay.setPermissions(GlobaleStaticValue::filePermissions);
}

void DataAnalyser::_updateDataForTheMonth(QDateTime *dateToUpdate)
{
    QString fileNameMonth = dateToUpdate->toString(GlobaleStaticValue::saveTimeFormatMonthTXT);
    QDate dayToRead = dateToUpdate->date();
    //    QString fileNameHour = fileNameDay + "_" + dateToUpdate->toString("hh");

    QFile fileMonth(this->_directoryFileNameYear + "/" + fileNameMonth + ".csv");

    QTextStream streamMonth(&fileMonth);

    QStringList listeOfData;

    qDebug() << "dayToRead : " << dayToRead.toString("yyyy-MM-dd");

    //    qint8 dayNumber = 0;
    double tempMin = 200;
    double tempMax = 0;
    double humMin = 200;
    double humMax = 0 ;
    double pressMin = 2000;
    double pressMax = 0;
    double memoTempMin = 200;
    double memoTempMax = 0;
    double memoHumMin = 200;
    double memoHumMax = 0 ;
    double memoPressMin = 2000;
    double memoPressMax = 0;
    double volumeChan0 = 0;
    double volumeChan1 = 0;
    double volumeChan2 = 0;
    double volumeChan3 = 0;
    double volumeTotal = 0;
    double memoVolumeChan0 = 0;
    double memoVolumeChan1 = 0;
    double memoVolumeChan2 = 0;
    double memoVolumeChan3 = 0;
    double memoVolumeTotal = 0;
    double consumChan0 = 0;
    double consumChan1 = 0;
    double consumChan2 = 0;
    double consumChan3 = 0;
    double consumThisHour = 0;
    double memoConsumThisHour = 0;

    //reset month file
    if (fileMonth.open(QFile::WriteOnly|QFile::Truncate))
    {
    }

    fileMonth.close();

    //read all hour file
    for(int i=1; i<=31; i++)
    {
        dayToRead.setDate(dateToUpdate->date().year(), dateToUpdate->date().month(),i);
        dateToUpdate->setDate(dayToRead);

        //        dayNumber = 0;
        tempMin = 200;
        tempMax = 0;
        humMin = 200;
        humMax = 0 ;
        pressMin = 2000;
        pressMax = 0;
        volumeChan0 = 0;
        volumeChan1 = 0;
        volumeChan2 = 0;
        volumeChan3 = 0;
        volumeTotal = 0;
        memoVolumeChan0 = 0;
        memoVolumeChan1 = 0;
        memoVolumeChan2 = 0;
        memoVolumeChan3 = 0;
        consumChan0 = 0;
        consumChan1 = 0;
        consumChan2 = 0;
        consumChan3 = 0;
        consumThisHour = 0;

        QString fileNameDay = fileNameMonth + "-" + dateToUpdate->date().toString("dd");
        QFile fileDay(this->_directoryFileNameMonth +  "/" + fileNameDay + ".csv");
        QTextStream streamDay(&fileDay);

        if (fileDay.open(QFile::ReadOnly))
        {
            //read hour file
            while (!streamDay.atEnd())
            {
                QString s=streamDay.readLine(); // reads line from file
                listeOfData.append(s.split(",")); // appends first column to list, ',' is separator
                //            qDebug() << "_updateDataForTheDay" << listeOfData.count() << listeOfData[1];

                //Analyse the data
                //                dayNumber = listeOfData[0].toUtf8().at(0);

                tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
                tempMax = listeOfData[2].toDouble() > tempMax ? listeOfData[2].toDouble() :  tempMax;

                humMin = listeOfData[3].toDouble() < humMin ? listeOfData[3].toDouble() :  humMin;
                humMax = listeOfData[4].toDouble() > humMax ? listeOfData[4].toDouble() :  humMax;

                pressMin = listeOfData[5].toDouble() < pressMin ? listeOfData[5].toDouble() :  pressMin;
                pressMax = listeOfData[6].toDouble() > pressMax ? listeOfData[6].toDouble() :  pressMax;

                volumeChan0 = listeOfData[7].toDouble();
                volumeChan1 = listeOfData[8].toDouble();
                volumeChan2 = listeOfData[9].toDouble();
                volumeChan3 = listeOfData[10].toDouble();

                memoTempMin = memoTempMin < tempMin ? memoTempMin :  tempMin;
                memoTempMax = memoTempMax > tempMax ? memoTempMax :  tempMax;
                memoHumMin = memoHumMin < humMin ? memoHumMin :  humMin;
                memoHumMax = memoHumMax > humMax ? memoHumMax :  humMax;
                memoPressMin = memoPressMin < pressMin ? memoPressMin :  pressMin;
                memoPressMax = memoPressMax > pressMax ? memoPressMax :  pressMax;

                volumeTotal = volumeChan0 + volumeChan1 + volumeChan2 + volumeChan3;
                memoVolumeTotal = volumeTotal;

                //conso calculation
                memoVolumeChan0 = volumeChan0;
                memoVolumeChan1 = volumeChan1;
                memoVolumeChan2 = volumeChan2;
                memoVolumeChan3 = volumeChan3;

                consumChan0 += (memoVolumeChan0-volumeChan0);
                consumChan1 += (memoVolumeChan1-volumeChan1);
                consumChan2 += (memoVolumeChan2-volumeChan2);
                consumChan3 += (memoVolumeChan3-volumeChan3);

                consumThisHour = consumChan0 + consumChan1 + consumChan2 + consumChan3;
                memoConsumThisHour = consumThisHour;
                listeOfData.clear();
            }
        }
        else
        {
            qDebug() << "cannot open fileDay";
        }
        fileDay.close();

        //
        //update the day
        if (fileDay.exists() && fileMonth.open(QFile::WriteOnly|QFile::Append))
        {
            streamMonth << i << ", "
                        << tempMin << ", " << tempMax << ", " << humMin << ", " << humMax <<  ", "
                        << pressMin << ", " << pressMax << ", " << volumeTotal << ", "
                        << consumChan0 << ", " << consumChan1 <<  ", "
                        << consumChan2 << ", " << consumChan3 << ", " << consumThisHour << "\n";
        }
        else
        {
            qDebug() << "cannot open fileMonth";
        }
        fileMonth.close();
    }

    fileMonth.setPermissions(GlobaleStaticValue::filePermissions);

    //update screen values for this month
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMinMonthText", QString::number(memoTempMin, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceTemperatureMaxMonthText", QString::number(memoTempMax, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMinMonthText", QString::number(memoHumMin, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceHumidityMaxMonthText", QString::number(memoHumMax, 'f', 2));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMaxMonthText", QString::number(memoPressMin, 'f', 1));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceAtmoPressurMinMonthText", QString::number(memoPressMax, 'f', 1));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoMonthText", QString::number(memoConsumThisHour, 'f', 0));
    this->_qobjectStastisticValueViewer->setProperty("labelDeviceConsoMonthBeforeText", QString::number(memoVolumeTotal, 'f', 0));


}

void DataAnalyser::_createDirectory(QDateTime *dateTimeToCheck)
{
    bool directoryExiste = false;

    this->_directoryFileNameYear = this->_directoryDataMain + dateTimeToCheck->toString("yyyy");
    this->_directoryFileNameMonth = _directoryFileNameYear + "/" + dateTimeToCheck->toString("MM");
    this->_directoryFileNameDay = _directoryFileNameMonth + "/" + dateTimeToCheck->toString("dd");
    this->_directoryFileNameHour = _directoryFileNameDay + "/" + dateTimeToCheck->time().toString("hh");
    this->_directoryFileNameMinute = _directoryFileNameHour + "/" + dateTimeToCheck->time().toString("mm");

    //check Home directory existe
    directoryExiste = QDir(this->_directoryDataMain).exists();

    qDebug() << Q_FUNC_INFO << _directoryDataMain << ", exist : " << "\n";

    if(!directoryExiste)
    {
        directoryExiste = QDir().mkdir(this->_directoryDataMain);
    }
    //check year directory existe
    directoryExiste = QDir(_directoryFileNameYear).exists();

    if(!directoryExiste)
    {
        directoryExiste = QDir().mkdir(_directoryFileNameYear);
    }

    //check month directory existe
    directoryExiste = QDir(_directoryFileNameMonth).exists();

    if(!directoryExiste)
    {
        directoryExiste = QDir().mkdir(_directoryFileNameMonth);
    }

    //check day directory existe
    directoryExiste = QDir(_directoryFileNameDay).exists();

    if(!directoryExiste)
    {
        directoryExiste = QDir().mkdir(_directoryFileNameDay);
    }

    //check hour directory existe
    directoryExiste = QDir(_directoryFileNameHour).exists();

    if(!directoryExiste)
    {
        directoryExiste = QDir().mkdir(_directoryFileNameHour);
    }
}

void DataAnalyser::_deleteHourDirectory(QDateTime *dateTimeToDelete)
{
    bool directoryExiste = false;
    bool directoryRemoved = false;
    this->_directoryFileNameYear = this->_directoryDataMain + dateTimeToDelete->toString("yyyy");
    this->_directoryFileNameMonth = _directoryFileNameYear + "/" + dateTimeToDelete->toString("MM");
    this->_directoryFileNameDay = _directoryFileNameMonth + "/" + dateTimeToDelete->toString("dd");
    this->_directoryFileNameHour = _directoryFileNameDay + "/" + dateTimeToDelete->time().toString("hh");
    this->_directoryFileNameMinute = _directoryFileNameHour + "/" + dateTimeToDelete->time().toString("mm");

    QDir dir(this->_directoryFileNameHour);

    //check hour directory existe
    directoryExiste = dir.exists();

    if(directoryExiste)
    {
        //        directoryRemoved = QDir().rmdir(_directoryFileNameHour);
        directoryRemoved = dir.removeRecursively();

    }

    qDebug() << Q_FUNC_INFO << _directoryFileNameHour << ", exist : " << directoryExiste << ", removed :" << directoryRemoved << "\n";

}

double DataAnalyser::_convertToVolumeInLiter(quint8 channelNumber, double valueIn, quint16 tankolumeMax, quint16 tankVolumeMMaxHeightInMilimeter, GlobalEnumerate::E_TankLiquidInside liquide)
{
    double liquideDensity = 0;
    double heightMaxInTankInPlus = 0;

    switch (liquide)
    {
    case GlobalEnumerate::WATER:
    {
        liquideDensity = GlobaleStaticValue::densityWater;
        break;
    }
    case GlobalEnumerate::OIL:
    {
        liquideDensity = GlobaleStaticValue::densityOil;
        break;
    }
    case GlobalEnumerate::ECO_OIL:
    {
        liquideDensity = GlobaleStaticValue::densityOilECO;
        break;
    }
    default:
        break;
    }

    //    heightMaxInTankInPlus = ((GlobaleStaticValue::pressureCapteurRangeMaxInPlus*tankVolumeMMaxHeightInMilimeter)/
    //                             (GlobaleStaticValue::pressureCapteurHeightMaxWater/liquideDensity));

    switch (channelNumber)
    {
    case 0:
    {
        heightMaxInTankInPlus = ((double)(this->_chan0HighMaxValueInPuls*tankVolumeMMaxHeightInMilimeter)/
                                 ((double)GlobaleStaticValue::pressureCapteurHeightMaxWater/liquideDensity));
        break;
    }
    case 1:
    {
        heightMaxInTankInPlus = ((double)(this->_chan1HighMaxValueInPuls*tankVolumeMMaxHeightInMilimeter)/
                                 ((double)GlobaleStaticValue::pressureCapteurHeightMaxWater/liquideDensity));
        break;
    }
    default:
        break;
    }

    //        qDebug() << Q_FUNC_INFO << qRound(valueIn*tankolumeMax/heightMaxInTankInPlus);
    //    this->_insertTextAtHomePage("_convertToVolumeInLiter chan" + QString::number(channelNumber) + " : " + QString::number(qRound(valueIn*tankolumeMax/heightMaxInTankInPlus)));
    // this->_insertTextAtHomePage("_convertToVolumeInLiter chan" + QString::number(channelNumber) + " : " + QString::number(valueIn*(double)tankolumeMax/heightMaxInTankInPlus));

    //    return (qRound(valueIn*tankolumeMax/heightMaxInTankInPlus));
    return (valueIn*(double)tankolumeMax/heightMaxInTankInPlus);

}

double DataAnalyser::_offsetVolumePressure(double deltaPressure,
                                           quint16 tankolumeMax,
                                           quint16 tankVolumeMMaxHeightInMilimeter,
                                           GlobalEnumerate::E_TankLiquidInside liquide)
{

    double liquideDensity = 0;

    switch (liquide)
    {
    case GlobalEnumerate::WATER:
    {
        liquideDensity = GlobaleStaticValue::densityWater;
        break;
    }
    case GlobalEnumerate::OIL:
    {
        liquideDensity = GlobaleStaticValue::densityOil;
        break;
    }
    case GlobalEnumerate::ECO_OIL:
    {
        liquideDensity = GlobaleStaticValue::densityOilECO;
        break;
    }
    default:
        break;
    }

    return ((deltaPressure * 100 * (tankolumeMax/tankVolumeMMaxHeightInMilimeter) * (1+((double)this->_PIDVolumeCoef/100))
             /(liquideDensity * 9.81)));
}

void DataAnalyser::_insertTextAtHomePage(QString textToInsert)
{
    QMetaObject::invokeMethod(this->_homeViewer, "addTextToDisplay",
                              Q_ARG(QVariant, textToInsert));
}

void DataAnalyser::ReceivedreplotWithSavedData(int year, int month, int day)
{
    qDebug() << Q_FUNC_INFO << "yyyy-MM-dd : " << year << "-" << month << "-" << day;

    QDateTime dateTimeToAnalyse =  QDateTime::currentDateTime();
    QDate dateToAnalyse;
    dateToAnalyse.setDate(year,1,1);
    dateTimeToAnalyse.setDate(dateToAnalyse);

    QString directoryfileName = GlobaleStaticValue::saveDataMain;
    QString fileName = "";

    if(month != 0)
    {
        dateToAnalyse.setDate(year,month,1);
        directoryfileName += dateTimeToAnalyse.toString("yyyy") + "/";
        fileName += dateTimeToAnalyse.toString("yyyy-MM");
    }

    if(day != 0)
    {
        dateToAnalyse.setDate(year,month,day);
        directoryfileName += dateTimeToAnalyse.toString("MM") + "/";
        fileName = dateTimeToAnalyse.toString("yyyy-MM-dd");
    }

    QFile fileToAnalyse(directoryfileName +  "/" + fileName + ".csv");

    QTextStream streamAnalyse(&fileToAnalyse);

    QStringList listeOfData;

    //    qint8 lineNumber = 0;
    double tempMin = 200;
    double tempMax = 0;
    double humMin = 200;
    double humMax = 0 ;
    double pressMin = 2000;
    double pressMax = 0;
    double consoChan0 = 0;
    double consoChan1 = 0;
    double consoChan2 = 0;
    double consoChan3 = 0;
    double consoTotal = 0;

    double memoTempMin = 200;
    double memoTempMax = 0;
    double memoHumMin = 200;
    double memoHumMax = 0 ;
    double memoPressMin = 2000;
    double memoPressMax = 0;
    double memoConsoTotal = 0;
    //    double memoConsoTotalDayBefore = 0;

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

            consoChan0 = listeOfData[7].toDouble() > consoChan0 ? listeOfData[7].toInt() :  consoChan0;
            consoChan1 = listeOfData[8].toDouble() > consoChan1 ? listeOfData[8].toInt() :  consoChan1;
            consoChan2 = listeOfData[9].toDouble() > consoChan2 ? listeOfData[9].toInt() :  consoChan2;
            consoChan3 = listeOfData[10].toDouble() > consoChan3 ? listeOfData[10].toInt() :  consoChan3;

            consoTotal += listeOfData[12].toDouble();


            listeOfData.clear();

            memoTempMin = tempMin < memoTempMin ? tempMin :  memoTempMin;
            memoTempMax = tempMax > memoTempMin ? tempMax :  memoTempMin;
            memoHumMin = humMin < memoHumMin ? humMin :  memoHumMin;
            memoHumMax = humMax > memoHumMax ? humMax :  memoHumMax;
            memoPressMin = pressMin < memoPressMin ? pressMin :  memoPressMin;
            memoPressMax = pressMax > memoPressMax ? pressMax :  memoPressMax;
            memoConsoTotal = consoTotal;

        }
    }
    else
    {
        qDebug() << "cannot open fileToAnalyse" ;

        memoTempMin = 0;
        memoTempMax = 0;
        memoHumMin = 0;
        memoHumMax = 0;
        memoPressMin = 0;
        memoPressMax = 0;
        memoConsoTotal += 0;
    }
    fileToAnalyse.close();

    QMetaObject::invokeMethod(this->_statisticViewer, "setStatisticValues",
                              Q_ARG(QVariant, QString::number(memoTempMin,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoTempMax,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoHumMin,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoHumMax,'f', 2)),
                              Q_ARG(QVariant, QString::number(memoPressMin,'f', 1)),
                              Q_ARG(QVariant, QString::number(memoPressMax,'f', 1)),
                              Q_ARG(QVariant, QString::number(memoConsoTotal,'f', 2))
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

void DataAnalyser::setResetTempFile(bool resetTempFile)
{
    _resetTempFile = resetTempFile;
}

//void DataAnalyser::setNbOfSavedDataInBuffer(const quint16 &nbOfSavedDataInBuffer)
//{
//    _nbOfSavedDataInBuffer = nbOfSavedDataInBuffer;
//}

//void DataAnalyser::setItdataFrameEnd(const QVector<DataFrame>::iterator &itdataFrameEnd)
//{
//    _itdataFrameEnd = itdataFrameEnd;
//}

void DataAnalyser::setDataFrame(DataFrame *dataFrame)
{
    _dataFrame = dataFrame;
}

void DataAnalyser::setSaveFile(bool saveFile)
{
    _saveFile = saveFile;
}

void DataAnalyser::setSaveTempFile(bool saveTempFile)
{
    _saveTempFile = saveTempFile;
}

