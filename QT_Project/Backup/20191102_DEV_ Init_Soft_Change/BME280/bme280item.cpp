#include <BME280/bme280item.h>

BME280Item::BME280Item(quint8 deviceI2CAdresse,
                       QObject *bme280Display,
                       QObject *roomDataPlot,
                       QObject *homeViewer):
    _deviceI2CAdress(deviceI2CAdresse),
    _fd(0),
    _bme280(new BME280(this->_deviceI2CAdress)),
    _pbme280Device(&this->_bme280Device),
    _deviceIsReady(false),
    _onReadingData(true),
    _startToReadOnData(false),
    _sleepingDelay(1000),
    _bme280Display(bme280Display),
    _roomDataPlot(roomDataPlot),
    _homeViewer(homeViewer),
    _dataFrame(new DataFrame()),
    _temperature(-273),
    _humidity(-100),
    _pressure(-1000),
    _stateMachine(GlobalEnumerate::STATE_NOT_FOUNDED)
{
    moveToThread(this);

    //reset the device structure
    this->_bme280->init_sbme280_device(this->_pbme280Device);
}

void BME280Item::readSavedData()
{
    //    bool readToCheck = false;

    //    if(this->_deviceIsReady)
    //    {
    //        do
    //        {
    //            readToCheck = this->_stateMachine == GlobalEnumerate::STATE_READY ? true : false;
    //            this->_waitDelayMicro(1000);
    //        }
    //        while(!readToCheck);


    //        _goToNextState();
    //        this->_checkStateOfDevice();
    //    }
    //    else
    //    {
    //        this->_checkStateOfDevice();
    //    }
}

bool BME280Item::onReadingData() const
{
    return _onReadingData;
}

bool BME280Item::deviceIsReady() const
{
    return _deviceIsReady;
}

void BME280Item::run()
{
    while(true)
    {
//            qDebug() << Q_FUNC_INFO;
        while(!this->_deviceIsReady)
        {
            this->_initDevice();
            this->_waitDelayMili(1000);
        }

        _goToNextState();
        this->_checkStateOfDevice();

        if(this->_startToReadOnData && this->_deviceIsReady)
        {
            this->_startToReadOnData = false;
//            _goToNextState();
//            this->_checkStateOfDevice();
//            QMetaObject::invokeMethod(this->_roomDataPlot, "addYValue",
//                                      Q_ARG(QVariant, QString::number(this->_temperature,'f', 2)),
//                                      Q_ARG(QVariant, QString::number(this->_humidity,'f', 2)),
//                                      Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                      Q_ARG(QVariant, 6)
//                                      );
//            QMetaObject::invokeMethod(this->_roomDataPlot, "addYValue",
//                                      Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                      Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                      Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                      Q_ARG(QVariant, 6)
//                                      );
        }

        this->_waitDelayMili(this->_sleepingDelay);
    }
}

bool BME280Item::startToReadOnData() const
{
    return _startToReadOnData;
}

void BME280Item::setStartToReadOnData(bool startToReadOnData)
{
    _startToReadOnData = startToReadOnData;
}

void BME280Item::setOnReadingData(bool onReadingData)
{
    _onReadingData = onReadingData;
}

DataFrame *BME280Item::dataFrame() const
{
    return _dataFrame;
}

void BME280Item::_initDevice()
{
    do
    {
        this->_checkStateOfDevice();
        this->_waitDelay(1);
    }
    while(!this->_deviceIsReady);
}

void BME280Item::_insertTextAtHomePage(QString textToInsert)
{
    QMetaObject::invokeMethod(this->_homeViewer, "addTextToDisplay",
                              Q_ARG(QVariant, textToInsert));
}

void BME280Item::_checkStateOfDevice()
{
    switch (this->_stateMachine)
    {
    case GlobalEnumerate::STATE_NOT_FOUNDED:
    {
        //send text "not founded" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateNotFounded);

        //check if the object was created
        if(&this->_bme280 != nullptr)
        {
            this->_bme280Device.dev_id = this->_bme280->getBME280_fd();
        }
        //check if the object was founded
        if(this->_bme280Device.dev_id)
        {
            this->_bme280Device.chip_id = this->_bme280->readChipID(this->_bme280Device.dev_id);
            _goToNextState();
        }
        break;
    }
    case GlobalEnumerate::STATE_FOUNDED:
    {
        //send text "founded" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateFounded);
        //change the color to red, not read to use
        QMetaObject::invokeMethod(this->_homeViewer, "changeColorBME280",
                                  Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
        //display FD of the device
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " FD : " + QString::number(this->_bme280Device.dev_id,10));
        //display ID of the device
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " ID : " + QString::number(this->_bme280Device.chip_id,10));
        _goToNextState();
        break;
    }
    case GlobalEnumerate::STATE_INIT:
    {
        //send text "init" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateInit);

        //programme the device register
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateOnProgramming);
        this->_initRegisterDevice();

        //check the good programming of the device register
        if(this->_checkRegisterConfiguration())
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateProgrammingSuccessful);
            _goToNextState();
        }
        break;
    }
    case GlobalEnumerate::STATE_ON_READING:
    {
        //send text "on reading" to display
        if(!this->_deviceIsReady)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateOnReading);
        }
        //change the color to blue, on analysis
        QMetaObject::invokeMethod(this->_homeViewer, "changeColorBME280",
                                  Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
        if(!this->_checkRegisterConfiguration())
        {
            this->_stateMachine = GlobalEnumerate::STATE_INIT;
            this->_checkStateOfDevice();
        }
        else
        {
            this->_onReadingData = true;
            this->_readDataI2C();
        }
        break;
    }
    case GlobalEnumerate::STATE_READY:
    {
        //send text "ready" to display
        if(!this->_deviceIsReady)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " " + GlobaleStaticValue::stateReady);
            this->_deviceIsReady = true;
        }
        //change the color to green, ready to use
        QMetaObject::invokeMethod(this->_homeViewer, "changeColorBME280",
                                  Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
        this->_onReadingData = false;

        break;
    }
    default:
        break;
    }

}

void BME280Item::_initRegisterDevice()
{

    //read chip ID
    //    this->_bme280Device.dev_id = this->_fd;
    //    qDebug() << "BME280 FD : " << this->_bme280Device.dev_id;

    //read chip ID
    //   this->_bme280Device.chip_id = this->_bme280->readChipID(this->_fd);
    //    qDebug() << "BME280 ID : " << this->_bme280Device.chip_id;

    //read the calibration data
    this->_bme280->readCalibrationData(this->_bme280Device.dev_id, &this->_pbme280Device->calib_data);

    //set temperature, humidity and pressure oversampling x16
    this->_bme280Device.settings.osr_t = BME280_OVERSAMPLING_16X;
    this->_bme280Device.settings.osr_h = BME280_OVERSAMPLING_16X;
//    this->_bme280Device.settings.osr_h = BME280_OVERSAMPLING_1X;
    this->_bme280Device.settings.osr_p = BME280_OVERSAMPLING_16X;

    //set filter x16
    this->_bme280Device.settings.filter = BME280_FILTER_COEFF_16;

    //set power mode to normal
    this->_bme280Device.settings.power_mode = BME280_SLEEP_MODE;

    //set stand by to 1000ms
    this->_bme280Device.settings.standby_time = BME280_STANDBY_TIME_1000_MS;

    //write configuration register
    this->_bme280->writBME280configuration(this->_pbme280Device);
}

bool BME280Item::_checkRegisterConfiguration()
{
    quint8 registerOK = 0;
    quint8 registerValue = 0;
    //check the ctrl_hum register
    registerValue = this->_bme280->readRegister(BME280_CTRL_HUM_ADDR);
    registerOK |= registerValue == 0b00000101 ? 1 : 0;
    //    qDebug() << "ctrl_hum register : " << QString::number(registerValue,2) << "register ok : " << registerOK;
    //check the status register
    registerValue = this->_bme280->readRegister(BME280_CTRL_HUM_ADDR);
    registerOK |= registerValue == 0b00000101 ? 2 : 0;
    //    qDebug() << "status register : " << QString::number(registerValue,2) << "register ok : " << registerOK;

    //check the ctrl_meas register
    registerValue = this->_bme280->readRegister(BME280_CTRL_MEAS_ADDR);
    registerOK |= registerValue == 0b10110100 ? 4 : 0;
    //    qDebug() << "ctrl_meas register : " << QString::number(registerValue,2) << "register ok : " << registerOK;

    //check the config register
    registerValue = this->_bme280->readRegister(BME280_CONFIG_ADDR);
    registerOK |= registerValue == 0b10110000 ? 8 : 0;
    //    qDebug() << "config register : " << QString::number(registerValue,2)<< "register ok : " << registerOK;

    return (registerOK == 15 ? true : false);
}

void BME280Item::_readDataI2C()
{
    static int cpt = 0;
    //    qDebug() << Q_FUNC_INFO << "CPT : " << cpt;

    this->_dataFrame->setDataFrameState(0);

    quint8 registerValue = 1;

    registerValue = this->_bme280->readRegister(BME280_CTRL_MEAS_ADDR);

    //wakeup the device
    this->_bme280->wakeupDevice(this->_pbme280Device);

    //wait comme back to sleeping mode
    do
    {
        registerValue = this->_bme280->readRegister(BME280_CTRL_MEAS_ADDR) & 0b00000011;
        this->_waitDelayMicro(1000);
    }
    while(registerValue);

    //read uncompensated values
    this->_bme280->readUncompensatedValue(this->_bme280Device.dev_id, &this->_pbme280Device->uncomp_data);

    //read compensate temperature
    this->_temperature = BME280::compensate_temperature(&this->_pbme280Device->uncomp_data,
                                                        &this->_pbme280Device->calib_data);
    //    qDebug() << "temperature : " << this->_temperature;


    //read compensate pressure
    this->_pressure = BME280::compensate_pressure(&this->_pbme280Device->uncomp_data,
                                                  &this->_pbme280Device->calib_data);
    //    qDebug() << "pressure : " << this->_pressure;

    //change pascal to millibar
    this->_pressure = this->_pressure/100;


    //read compensate humidity
    this->_humidity = BME280::compensate_humidity(&this->_pbme280Device->uncomp_data,
                                                  &this->_pbme280Device->calib_data);
    //    qDebug() << "humidity : " << this->_humidity;

    //    qDebug() << "altitude : " << this->_bme280->getAltitude(this->_pressure);

//    qDebug() << Q_FUNC_INFO << "BME280 state: " << this->_dataFrame->dataFrameState();

    if(this->_deviceIsReady)
    {
        if(this->_dataFrame!=nullptr)
        {
            this->_dataFrame->setBME280_temperature(this->_temperature);
            this->_dataFrame->setBME280_humidity(this->_humidity);
            this->_dataFrame->setBME280_pressure(this->_pressure);

            this->_temperature != 0 ? this->_dataFrame->setDataFrameState(this->_dataFrame->dataFrameState() | (1 << 0)) :
                                      this->_dataFrame->setDataFrameState(this->_dataFrame->dataFrameState() & (0 << 0));
            this->_humidity != 0 ? this->_dataFrame->setDataFrameState(this->_dataFrame->dataFrameState() | (1 << 1)) :
                                   this->_dataFrame->setDataFrameState(this->_dataFrame->dataFrameState() & (0 << 1));
            this->_pressure != 0 ? this->_dataFrame->setDataFrameState(this->_dataFrame->dataFrameState() | (1 << 2)) :
                                   this->_dataFrame->setDataFrameState(this->_dataFrame->dataFrameState() & (0 << 2));
        }

         //        if(cpt%60 == 0)
        //        {
//        QMetaObject::invokeMethod(this->_roomDataPlot, "addYValue",
//                                  Q_ARG(QVariant, QString::number(this->_humidity,'f', 2)),
//                                  Q_ARG(QVariant, QString::number(this->_temperature,'f', 2)),
//                                  Q_ARG(QVariant, QString::number(this->_pressure/10,'f', 2)),
//                                  Q_ARG(QVariant, 6)
//                                  );
        QMetaObject::invokeMethod(this->_bme280Display, "updateValue",
                                  Q_ARG(QVariant, QString::number(this->_temperature,'f', 2)),
                                  Q_ARG(QVariant, QString::number(this->_humidity,'f', 2)),
                                  Q_ARG(QVariant, QString::number(this->_pressure,'f', 2))
                                  );

//        QMetaObject::invokeMethod(this->_roomDataPlot, "addYValue",
//                                  Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                  Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                  Q_ARG(QVariant, QString::number(this->_pressure,'f', 2)),
//                                  Q_ARG(QVariant, 6)
//                                  );
        //            cpt = 0;
        //        }
    }

    else
    {
        this->_insertTextAtHomePage(GlobaleStaticValue::bme280Title + " :   " +
                                    GlobaleStaticValue::bme280Temperature + " " + QString::number(this->_temperature,'f',2) + " " + GlobaleStaticValue::bme280DegCelcuis + ",\t\t" +
                                    GlobaleStaticValue::bme280Humidity + " " + QString::number(this->_humidity,'f',2) + " " + GlobaleStaticValue::bme280PerCent + ",\t\t" +
                                    GlobaleStaticValue::bme280Pressure + " " + QString::number(this->_pressure,'f',1) + " " + GlobaleStaticValue::bme280Milibar
                                    );
    }
    _goToNextState();

    //    jumpToNextState();
    this->_checkStateOfDevice();
    cpt++;

//    qDebug() << Q_FUNC_INFO << "BME280 state: " << this->_dataFrame->dataFrameState();

}

void BME280Item::_waitDelay(quint64 delayInSeconde)
{
    QThread::sleep(delayInSeconde);
}

void BME280Item::_waitDelayMili(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

void BME280Item::_waitDelayMicro(quint64 delayInMicroSeconde)
{
    QThread::usleep(delayInMicroSeconde);
}

void BME280Item::_goToNextState()
{
    switch (this->_stateMachine)
    {
    case GlobalEnumerate::STATE_NOT_FOUNDED:
    {
        this->_stateMachine = GlobalEnumerate::STATE_FOUNDED;
        break;
    }
    case GlobalEnumerate::STATE_FOUNDED:
    {
        this->_stateMachine = GlobalEnumerate::STATE_INIT;
        break;
    }
    case GlobalEnumerate::STATE_INIT:
    {
        this->_stateMachine = GlobalEnumerate::STATE_ON_READING;
        break;
    }
    case GlobalEnumerate::STATE_ON_READING:
    {
        this->_stateMachine = GlobalEnumerate::STATE_READY;
        break;
    }
    case GlobalEnumerate::STATE_READY:
    {
        this->_stateMachine = GlobalEnumerate::STATE_ON_READING;
        break;
    }
    default:
        break;
    }
}
