#include "dataanalyser.h"

DataAnalyser::DataAnalyser(quint16 nbDataFramToTempSave,
                           QObject *statisticValueViewer,
                           QObject *statisticViewer):
    _fileTempData(GlobaleStaticValue::saveTempFile),
    _nbDataFramToTempSave(nbDataFramToTempSave),
    _saveTempFile(false),
    _saveTempFileFinished(true),
    _saveFile(false),
    _saveFileFinished(true),
    _resetTempFile(true),
    _updateDayData(true),
    _updateMonthData(true),
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
    _nbOfSavedDataInBuffer(nbDataFramToTempSave),
    _waitDelayInMili(5),
    _dateTime(QDateTime::currentDateTime()),
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
    _qobjectStastisticValueViewer(statisticValueViewer),
    _statisticViewer(statisticViewer)
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
    //    this->_dateTime = QDateTime::currentDateTime();

    //    static int i = 0;

    //    this->_bufferTempData.append(*dataFrame);

    QTextStream stream(&this->_fileTempData);

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

    if (this->_fileTempData.open(QFile::WriteOnly|QFile::Append))
    {
        //                for(int j = i; j<this->_bufferTempData.size(); j++)
        //                {
        stream << this->_dateTime.time().second() << ", " <<  dataFrame->BME280_temperature() << ", " << dataFrame->BME280_humidity() << ", "
               << dataFrame->BME280_pressure() << ", " << dataFrame->ADS115_1_chan0() <<  ", "
               << dataFrame->ADS115_1_chan1() << ", " << dataFrame->ADS115_1_chan2() << ", " << dataFrame->ADS115_1_chan3() << endl;
        //                    i=j;
        //                }
        //            }
        this->_fileTempData.close();
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

    //    qDebug() << Q_FUNC_INFO <<
    //                "dataTempCount : " << this->_bufferTempData.count() <<
    //                "DataTemp temp: " << dataFrame->BME280_temperature() <<
    //                ", hum " << dataFrame->BME280_humidity() <<
    //                ", press : " << dataFrame->BME280_pressure() <<
    //                ", chan 0: " << dataFrame->ADS115_1_chan0() <<
    //                ", chan 1: " << dataFrame->ADS115_1_chan1() <<
    //                ", chan 2: " << dataFrame->ADS115_1_chan2() <<
    //                ", chan 3: " << dataFrame->ADS115_1_chan3() ;
}

void DataAnalyser::run()
{
    while(true)
    {
        this->_saveFinished = false;

        if(this->_saveTempFile)
        {
            this->_saveTempFile = false;
            this->_saveTempFileFinished = false;
            saveTempData(this->_dataFrame);
            this->_saveTempFileFinished = true;
        }

        if(this->_saveFile)
        {
            this->_saveFile = false;
            this->_saveFileFinished = false;
            saveDataFile();
            this->_saveFileFinished = true;
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

        msleep(_waitDelayInMili);

    }

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

    qint8 hourNumber = 0;
    double tempMin = 273;
    double tempMax = -273;
    double humMin = 273;
    double humMax = -273;
    double pressMin = 2000;
    double pressMax = -2000;
    qint16 volumeChan0 = 0;
    qint16 volumeChan1 = 0;
    qint16 volumeChan2 = 0;
    qint16 volumeChan3 = 0;
    qint16 volumeTotal = 0;
    qint16 memoVolumeTotal = 0;
    qint16 VolumeTotalMin = 32000;
    qint16 volumeConsoTotal = 0;


    if (fileMinute.open(QFile::ReadOnly))
    {
        while (!streamMinute.atEnd())
        {
            QString s=streamMinute.readLine(); // reads line from file
            listeOfData.append(s.split(",")); // appends first column to list, ',' is separator

            //Analyse the data
            hourNumber = listeOfData[0].toInt();

            tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
            tempMax = listeOfData[1].toDouble() > tempMax ? listeOfData[1].toDouble() :  tempMax;

            humMin = listeOfData[2].toDouble() < humMin ? listeOfData[2].toDouble() :  humMin;
            humMax = listeOfData[2].toDouble() > humMax ? listeOfData[2].toDouble() :  humMax;

            pressMin = listeOfData[3].toDouble() < pressMin ? listeOfData[3].toDouble() :  pressMin;
            pressMax = listeOfData[3].toDouble() > pressMax ? listeOfData[3].toDouble() :  pressMax;

            volumeChan0 = listeOfData[4].toInt();
            volumeChan1 = listeOfData[5].toInt();
            volumeChan2 = listeOfData[6].toInt();
            volumeChan3 = listeOfData[7].toInt();

            volumeTotal = volumeChan0 + volumeChan1 + volumeChan2 + volumeChan3;
            memoVolumeTotal = volumeTotal > memoVolumeTotal ? volumeTotal : memoVolumeTotal;
            VolumeTotalMin = volumeTotal < VolumeTotalMin ? volumeTotal : VolumeTotalMin;

            listeOfData.clear();            
        }
    }
    else
    {
        qDebug() << "cannot open fileMinute";
    }
    fileMinute.close();

    volumeConsoTotal = memoVolumeTotal - VolumeTotalMin;

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

    qint8 hourNumber = 0;
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
    qint16 volumeChan0 = 0;
    qint16 volumeChan1 = 0;
    qint16 volumeChan2 = 0;
    qint16 volumeChan3 = 0;
    qint16 volumeTotal = 0;
    qint16 memoVolumeChan0 = 0;
    qint16 memoVolumeChan1 = 0;
    qint16 memoVolumeChan2 = 0;
    qint16 memoVolumeChan3 = 0;
    qint16 memoVolumeTotal = 0;
    qint16 VolumeTotalMin = 32000;
    qint16 consumThisHour = 0;
    qint16 memoConsumThisHour = 0;

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

        hourNumber = 0;
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
                hourNumber = listeOfData[0].toUtf8().at(0);

                tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
                tempMax = listeOfData[2].toDouble() > tempMax ? listeOfData[2].toDouble() :  tempMax;

                humMin = listeOfData[3].toDouble() < humMin ? listeOfData[3].toDouble() :  humMin;
                humMax = listeOfData[4].toDouble() > humMax ? listeOfData[4].toDouble() :  humMax;

                pressMin = listeOfData[5].toDouble() < pressMin ? listeOfData[5].toDouble() :  pressMin;
                pressMax = listeOfData[6].toDouble() > pressMax ? listeOfData[6].toDouble() :  pressMax;

                volumeChan0 = listeOfData[7].toShort();
                volumeChan1 = listeOfData[8].toShort();
                volumeChan2 = listeOfData[9].toShort();
                volumeChan3 = listeOfData[10].toShort();
                volumeTotal = listeOfData[11].toShort();
                consumThisHour = listeOfData[12].toShort();

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

        //conso calculation
        memoConsumThisHour = memoVolumeTotal - VolumeTotalMin;

        //
        //update the day
        if (fileHour.exists() && fileDay.open(QFile::WriteOnly|QFile::Append))
        {
            streamDay << i << ", "
                      << tempMin << ", " << tempMax << ", " << humMin << ", " << humMax <<  ", "
                      << pressMin << ", " << pressMax << ", "
                      << volumeChan0 << ", " << volumeChan1 <<  ", "
                      << volumeChan2 << ", " << volumeChan3 << ", "
                      << volumeTotal << ", " << memoConsumThisHour << "\n";
        }
        else
        {
            qDebug() << "cannot open fileDay";
        }
        fileDay.close();
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

    qint8 dayNumber = 0;
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
    qint16 volumeChan0 = 0;
    qint16 volumeChan1 = 0;
    qint16 volumeChan2 = 0;
    qint16 volumeChan3 = 0;
    qint16 volumeTotal = 0;
    qint16 memoVolumeChan0 = 0;
    qint16 memoVolumeChan1 = 0;
    qint16 memoVolumeChan2 = 0;
    qint16 memoVolumeChan3 = 0;
    qint16 memoVolumeTotal = 0;
    qint16 consumChan0 = 0;
    qint16 consumChan1 = 0;
    qint16 consumChan2 = 0;
    qint16 consumChan3 = 0;
    qint16 consumThisHour = 0;
    qint16 memoConsumThisHour = 0;

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

        dayNumber = 0;
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
                dayNumber = listeOfData[0].toUtf8().at(0);

                tempMin = listeOfData[1].toDouble() < tempMin ? listeOfData[1].toDouble() :  tempMin;
                tempMax = listeOfData[2].toDouble() > tempMax ? listeOfData[2].toDouble() :  tempMax;

                humMin = listeOfData[3].toDouble() < humMin ? listeOfData[3].toDouble() :  humMin;
                humMax = listeOfData[4].toDouble() > humMax ? listeOfData[4].toDouble() :  humMax;

                pressMin = listeOfData[5].toDouble() < pressMin ? listeOfData[5].toDouble() :  pressMin;
                pressMax = listeOfData[6].toDouble() > pressMax ? listeOfData[6].toDouble() :  pressMax;

                volumeChan0 = listeOfData[7].toShort();
                volumeChan1 = listeOfData[8].toShort();
                volumeChan2 = listeOfData[9].toShort();
                volumeChan3 = listeOfData[10].toShort();

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

void DataAnalyser::setResetTempFile(bool resetTempFile)
{
    _resetTempFile = resetTempFile;
}

void DataAnalyser::setNbOfSavedDataInBuffer(const quint16 &nbOfSavedDataInBuffer)
{
    _nbOfSavedDataInBuffer = nbOfSavedDataInBuffer;
}

void DataAnalyser::setItdataFrameEnd(const QVector<DataFrame>::iterator &itdataFrameEnd)
{
    _itdataFrameEnd = itdataFrameEnd;
}

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

