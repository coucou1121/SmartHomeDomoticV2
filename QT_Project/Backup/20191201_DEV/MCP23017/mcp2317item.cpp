#include "mcp2317item.h"

MCP2317item::MCP2317item(quint8 deviceI2CAddress,
                         bool deviceAsAllOutput,
                         bool deviceAsAllInput,
                         QObject *homeViewer):
    _deviceI2CAddress(deviceI2CAddress),
    _fd(0),
    _mcp23017(new MCP23017(deviceI2CAddress)),
    _pmcp23017Device(&this->_smcp23017_device),
    _pmcp23017_IOCON(&this->_smcp23017_IOCON),
    _deviceAsAllOutput(deviceAsAllOutput),
    _deviceAsAllInput(deviceAsAllInput),
    _deviceIsReady(false),
    _onReadingData(true),
    _startToReadOnData(false),
    _sleepingDelay(1000),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0),
    _homeViewer(homeViewer),
    _stateMachine(GlobalEnumerate::STATE_NOT_FOUNDED)
{
    this->_mcp23017->init_smcp23017_device(this->_pmcp23017Device);
    this->_mcp23017->init_smcp23017_IOCON(this->_pmcp23017_IOCON);
    moveToThread(this);
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
    //set the device id
    this->_pmcp23017Device->device_id = this->_mcp23017->MCP23017_fd();

    //set the IODIR register
    if(this->_deviceAsAllOutput && this->_deviceAsAllInput)
    {
        qDebug() << Q_FUNC_INFO << "wrong bool value as init";
    }
    //set the IODIR register all IO as input
    else if(this->_deviceAsAllInput)
    {
        this->_pmcp23017Device->IODIR_reg = GPIO_ALL_INPUT;
    }
    //set the IODIR register all IO as output
    else if(this->_deviceAsAllOutput)
    {
        this->_pmcp23017Device->IODIR_reg = GPIO_ALL_OUTPUT;
    }
    else
    {

    }
    
    //set the IPOL register
    this->_pmcp23017Device->IPOL_reg = GPIO_ALL_OFF;

    //set the GPINT register
    this->_pmcp23017Device->GPINT_reg = GPIO_ALL_OFF;

    //set the DEFVAL register
    this->_pmcp23017Device->DEFVAL_reg = GPIO_ALL_OFF;

    //set the INTCON register
    this->_pmcp23017Device->INTCON_reg = GPIO_ALL_OFF;
    
    if(this->_deviceAsAllOutput && this->_deviceAsAllInput)
    {
        qDebug() << Q_FUNC_INFO << "wrong bool value as init";
    }
    //set the IOCON register all IO as input
    else if(this->_deviceAsAllInput)
    {
        this->_pmcp23017_IOCON->BANK = 0;    // sequential register addresses
        this->_pmcp23017_IOCON->MIRROR = 0;  // use configureInterrupt
        this->_pmcp23017_IOCON->SEQOP = IOCON_5_SEQOP;   // sequential operation disabled, address pointer does not increment
        this->_pmcp23017_IOCON->DISSLW = 0;  // slew rate enabled
        this->_pmcp23017_IOCON->HAEN = 0;    // hardware address pin is always enabled on 23017
        this->_pmcp23017_IOCON->ODR = 0;     // Active driver output (INTPOL bit sets the polarity.)
        this->_pmcp23017_IOCON->INTPOL = 0;  // interrupt active low
        this->_pmcp23017_IOCON->NOTUSED = 0;  // not used bite
    }
    //set the IOCON register all IO as output
    else if(this->_deviceAsAllOutput)
    {
        this->_pmcp23017_IOCON->BANK = 0;    // sequential register addresses
        this->_pmcp23017_IOCON->MIRROR = 0;  // use configureInterrupt
        this->_pmcp23017_IOCON->SEQOP = IOCON_5_SEQOP;   // sequential operation disabled, address pointer does not increment
        this->_pmcp23017_IOCON->DISSLW = 0;  // slew rate enabled
        this->_pmcp23017_IOCON->HAEN = 0;    // hardware address pin is always enabled on 23017
        this->_pmcp23017_IOCON->ODR = 0;     // Active driver output (INTPOL bit sets the polarity.)
        this->_pmcp23017_IOCON->INTPOL = 0;  // interrupt active low
        this->_pmcp23017_IOCON->NOTUSED = 0;  // not used bite
    }
    else
    {

    }
    this->_pmcp23017Device->IOCON_reg = this->_mcp23017->convertIOCONStructToRegValue(this->_pmcp23017_IOCON);

    //set the GPPU register
    this->_pmcp23017Device->GPPU_reg = GPIO_ALL_ON;

    //set the INTF register
    this->_pmcp23017Device->INTF_reg = GPIO_ALL_OFF;

    //set the INTCAP register
    this->_pmcp23017Device->INTCAP_reg = GPIO_ALL_OFF;

    //set the GPIO register
    this->_pmcp23017Device->GPIO_reg = GPIO_ALL_OFF;

    //set the OLAT register
    this->_pmcp23017Device->OLAT_reg = GPIO_ALL_OFF;

//    this->_mcp23017->setPIOCON(this->_pmcp23017_IOCON);
    this->_mcp23017->setPdevice(this->_pmcp23017Device);
    //    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id
    //             << this->_pmcp23017_IOCON->BANK << this->_pmcp23017_IOCON->MIRROR
    //             << this->_pmcp23017_IOCON->SEQOP << this->_pmcp23017_IOCON->DISSLW
    //             << this->_pmcp23017_IOCON->HAEN << this->_pmcp23017_IOCON->ODR << this->_pmcp23017_IOCON->INTPOL;
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
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title + " " + GlobaleStaticValue::stateNotFounded);

        //check if the object was created
        if(&this->_mcp23017 != nullptr)
        {
            this->_pmcp23017Device->device_id = this->_mcp23017->MCP23017_fd();
            _goToNextState();
        }
        break;
    }
    case GlobalEnumerate::STATE_FOUNDED:
    {
        //send text "founded" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                    + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                    + " " + GlobaleStaticValue::stateFounded);
        //change the color to red, not read to use
        //        QMetaObject::invokeMethod(this->_homeViewer, "changeColorBME280",
        //                                  Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
        //display FD of the device
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title + " FD : " + QString::number(this->_pmcp23017Device->device_id,10));
        _goToNextState();
        break;
    }
    case GlobalEnumerate::STATE_INIT:
    {
        //send text "init" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                    +" FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                    + " " + GlobaleStaticValue::stateInit);

        this->_initDevice();

        //programme the device register
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                    + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                    + " " + GlobaleStaticValue::stateOnProgramming);
        this->_initRegisterDevice();

        //check the good programming of the device register
        if(this->_checkRegisterConfiguration())
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateProgrammingSuccessful);
            _goToNextState();
        }
        break;
    }
    case GlobalEnumerate::STATE_ON_READING:
    {
        //send text "on reading" to display
        if(!this->_deviceIsReady)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateOnReading);
        }

        //change the color to blue, on analysis
        switch(this->_deviceI2CAddress)
        {
        case MCP23017_ADDRESS_DEFAULT_20:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_1",
                                      Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
            break;
        case MCP23017_ADDRESS_DEFAULT_22:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_2",
                                      Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
            break;
        case MCP23017_ADDRESS_DEFAULT_24:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_3",
                                      Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
            break;
        case MCP23017_ADDRESS_DEFAULT_26:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_4",
                                      Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
            break;
        default:
            break;
        }

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
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateReady);
            this->_deviceIsReady = true;
        }
        //change the color to green, ready to use
        switch(this->_deviceI2CAddress)
        {
        case MCP23017_ADDRESS_DEFAULT_20:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_1",
                                      Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
            break;
        case MCP23017_ADDRESS_DEFAULT_22:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_2",
                                      Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
            break;
        case MCP23017_ADDRESS_DEFAULT_24:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_3",
                                      Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
            break;
        case MCP23017_ADDRESS_DEFAULT_26:
            QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_4",
                                      Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
            break;
        default:
            break;
        }
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
    this->_mcp23017->init();


}

bool MCP2317item::_checkRegisterConfiguration()
{
    quint8 registerOK = 1;
        quint16 registerValue = 0;

    //    quint16 registertoSet = 0b00100000 << 8 | 0b00100000;

    //check the IOCON register
    //    this->_mcp23017->writeRegister(MCP23017_ADDRESS_IOCON, 0b00100000);
        registerValue = this->_mcp23017->readRegister(MCP23017_ADDRESS_INTCONA) << 8;
        registerValue |= this->_mcp23017->readRegister(MCP23017_ADDRESS_INTCONA);
    //    registerOK |= registerValue == registertoSet ? 1 : 0;
    //    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id<< "registertoSet IOCON : " << QString::number(registertoSet,2) ;
//        qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id<< "registerValue IOCON : " << QString::number(registerValue,2) << "register ok : " << registerOK;
//        registerValue = this->_mcp23017->readRegister(IODIR_REGISTER) << 8;
    //    registerValue |= this->_mcp23017->readRegister(IODIR_REGISTER + 1);
    //    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << "registerValue IODIR : " << QString::number(registerValue,2) << "register ok : " << registerOK;
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

    return (registerOK == 1 ? true : false);
}

void MCP2317item::_readDataI2C()
{
    static bool switchOn = true;

    qDebug()  << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " ,switchOn : " << switchOn;

    if(switchOn)
    {
        this->_mcp23017->gpioPinWriteAll(GPIO_ALL_ON);
    }
    else
    {
        this->_mcp23017->gpioPinWriteAll(GPIO_ALL_OFF);

    }

    switchOn = switchOn == true ? false : true;
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
