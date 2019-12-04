#include "mcp2317item.h"

MCP2317item::MCP2317item(quint8 deviceI2CAddress,
                         QObject *homeViewer):
    _deviceI2CAddress(deviceI2CAddress),
    _fd(0),
    _mcp23017(new MCP23017(this->_deviceI2CAddress)),
    _pmcp23017Device(&this->_mcp23017Device),
    _pmcp23017iocon(&this->_mcp23017iocon),
    _deviceIsReady(false),
    _onReadingData(true),
    _startToReadOnData(false),
    _sleepingDelay(500),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0),
    _homeViewer(homeViewer),
    _stateMachine(GlobalEnumerate::STATE_NOT_FOUNDED)
{
    moveToThread(this);

    //reset the device structure
    this->_mcp23017->init_smcp23017_device(this->_pmcp23017Device);
    this->_mcp23017->init_smcp23017_IOCON(this->_pmcp23017iocon);
}

void MCP2317item::run()
{
    qint64 sleepingDelay = 0;

    while(true)
    {
        this->_memotimeInMilisecond = QDateTime::currentMSecsSinceEpoch();

        this->_checkStateOfDevice();

       this->_timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        sleepingDelay = (this->_timeInMilisecond - this->_memotimeInMilisecond) > this->_sleepingDelay ?
                    0 : this->_sleepingDelay - (this->_timeInMilisecond - this->_memotimeInMilisecond);

//        qDebug() << Q_FUNC_INFO << this->objectName() << "Time to read data : "
//                 << this->_timeInMilisecond - this->_memotimeInMilisecond << "[ms]";

        this->_waitDelayMili(sleepingDelay);
    }
}

void MCP2317item::_initDevice()
{

}

void MCP2317item::_insertTextAtHomePage(QString textToInsert)
{
    QMetaObject::invokeMethod(this->_homeViewer, "addTextToDisplay",
                              Q_ARG(QVariant, textToInsert));
}

void MCP2317item::_checkStateOfDevice()
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
//            this->_checkStateOfDevice();
        }
        else
        {
            this->_onReadingData = true;
            this->_readDataI2C();
            _goToNextState();
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
        _goToNextState();

        break;
    }
    default:
        break;
    }

}

void MCP2317item::_initRegisterDevice()
{

}

bool MCP2317item::_checkRegisterConfiguration()
{
    quint8 registerOK = 0;
    quint8 registerValue = 0;
    //check the ctrl_hum register
//    registerValue = this->_bme280->readRegister(BME280_CTRL_HUM_ADDR);
//    registerOK |= registerValue == 0b00000101 ? 1 : 0;
//    //    qDebug() << "ctrl_hum register : " << QString::number(registerValue,2) << "register ok : " << registerOK;
//    //check the status register
//    registerValue = this->_bme280->readRegister(BME280_CTRL_HUM_ADDR);
//    registerOK |= registerValue == 0b00000101 ? 2 : 0;
//    //    qDebug() << "status register : " << QString::number(registerValue,2) << "register ok : " << registerOK;

//    //check the ctrl_meas register
//    registerValue = this->_bme280->readRegister(BME280_CTRL_MEAS_ADDR);
//    registerOK |= registerValue == 0b10110100 ? 4 : 0;
//    //    qDebug() << "ctrl_meas register : " << QString::number(registerValue,2) << "register ok : " << registerOK;

//    //check the config register
//    registerValue = this->_bme280->readRegister(BME280_CONFIG_ADDR);
//    registerOK |= registerValue == 0b10110000 ? 8 : 0;
    //    qDebug() << "config register : " << QString::number(registerValue,2)<< "register ok : " << registerOK;

    return (registerOK == 15 ? true : false);
}

void MCP2317item::_readDataI2C()
{

}

void MCP2317item::_waitDelay(quint64 delayInSeconde)
{
    QThread::sleep(delayInSeconde);
}

void MCP2317item::_waitDelayMili(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

void MCP2317item::_waitDelayMicro(quint64 delayInMicroSeconde)
{
    QThread::usleep(delayInMicroSeconde);
}

void MCP2317item::_goToNextState()
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
