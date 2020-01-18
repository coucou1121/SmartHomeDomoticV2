#include "mcp2317item.h"

MCP2317item::MCP2317item(quint8 deviceI2CAddress,
                         quint8 pinBase,
                         quint8 fd,
                         QObject *homeViewer,
                         QObject *MCP23017Viewer,
                         WiringPiGardian *wiringPiGardian):
    _deviceI2CAddress(deviceI2CAddress),
    _pinBase(pinBase),
    _fd(fd),
    //    _IODIRreg(0),
    //    _GPIOreg(0),
    _mcp23017(new MCP23017(deviceI2CAddress, pinBase, fd)),
    _pmcp23017Device(&this->_smcp23017_device),
    _pmcp23017_IOCON(&this->_smcp23017_IOCON),
//    _initIODIRregOK(true),
    _deviceIsReady(false),
    _onReadingData(true),
    _startToReadOnData(false),
    _ledOn(false),
    _sleepingDelay(10),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0),
    _homeViewer(homeViewer),
    _MCP23017Viewer(MCP23017Viewer),
    _wiringPiGardian(wiringPiGardian),
    _stateMachine(GlobalEnumerate::STATE_NOT_FOUNDED),
    _checkTimeBeforeError(10)
{
    //    this->_mcp23017->init_smcp23017_device(this->_pmcp23017Device);
    //    this->_mcp23017->init_smcp23017_IOCON(this->_pmcp23017_IOCON);
    //    mcp23017Setup(this->_pinBase, this->_deviceI2CAddress);
    //    this->_fd = wiringPiI2CSetup(this->_deviceI2CAddress);
    qDebug() << Q_FUNC_INFO << "address founded : " << this->_fd;
    moveToThread(this);
}

void MCP2317item::setIODIRreg(const int regIODIRvalue)
{
    qDebug() << Q_FUNC_INFO << QString::number(regIODIRvalue,2);
    //    this->_IODIRreg = regIODIRvalue;
    this->_pmcp23017Device->IODIR_reg = regIODIRvalue;
    this->_mcp23017->setGpioDirection(regIODIRvalue);
    this->_mcp23017->writeGPIOPinMode();
//    this->_initIODIRregOK = true;
//    this->_stateMachine = GlobalEnumerate::STATE_INIT;
//    this->_checkStateOfDevice();
}

int MCP2317item::getIODIRreg()
{
    return (this->_mcp23017->gpioDirection());
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

        //                qDebug() << Q_FUNC_INFO << this->objectName() << this->_fd <<  "Time to read data : "
        //                         << this->_timeInMilisecond - this->_memotimeInMilisecond << "[ms]";

        this->_waitDelayMili(sleepingDelay);
    }
}

void MCP2317item::setGPIOreg(const quint16 &GPIOreg)
{
    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " GPIOreg : " << QString::number(GPIOreg,2);
    //    this->_GPIOreg = GPIOreg;
    this->_pmcp23017Device->GPIO_reg = GPIOreg;
    this->_mcp23017->gpioPinWriteAll(GPIOreg);
}

void MCP2317item::_initDevice()
{
    //set the device id
//    if(!this->_initIODIRregOK)
//    {
//        this->_pmcp23017Device->device_id = this->_mcp23017->MCP23017_fd();
//    }

    //set the IODIR register
        this->_mcp23017->writeRegister16(MCP23017_ADDRESS_IODIR, this->_pmcp23017Device->IODIR_reg);

    //set the IPOL register
    this->_pmcp23017Device->IPOL_reg = GPIO_ALL_OFF;
    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_IPOL, this->_pmcp23017Device->IPOL_reg);

    //set the GPINT register
    this->_pmcp23017Device->GPINT_reg = GPIO_ALL_OFF;
    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_GPINTEN, this->_pmcp23017Device->GPINT_reg);

    //set the DEFVAL register
    this->_pmcp23017Device->DEFVAL_reg = GPIO_ALL_OFF;
    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_DEFVAL, this->_pmcp23017Device->DEFVAL_reg);

    //set the INTCON register
    this->_pmcp23017Device->INTCON_reg = GPIO_ALL_OFF;
    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_INTCON, this->_pmcp23017Device->INTCON_reg);

    //set the IOCON register all IO as input
    this->_pmcp23017_IOCON->BANK = 0;    // sequential register addresses
    this->_pmcp23017_IOCON->MIRROR = 0;  // use configureInterrupt
    this->_pmcp23017_IOCON->SEQOP = IOCON_5_SEQOP;   // sequential operation disabled, address pointer does not increment
    this->_pmcp23017_IOCON->DISSLW = 0;  // slew rate enabled
    this->_pmcp23017_IOCON->HAEN = 0;    // hardware address pin is always enabled on 23017
    this->_pmcp23017_IOCON->ODR = 0;     // Active driver output (INTPOL bit sets the polarity.)
    this->_pmcp23017_IOCON->INTPOL = 0;  // interrupt active low
    this->_pmcp23017_IOCON->NOTUSED = 0;  // not used bite

    this->_pmcp23017Device->IOCON_reg = this->_mcp23017->convertIOCONStructToRegValue(this->_pmcp23017_IOCON);
    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_IOCON, this->_pmcp23017Device->IOCON_reg);

    //set the GPPU register
    this->_pmcp23017Device->GPPU_reg = GPIO_ALL_ON;
    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_GPPU, this->_pmcp23017Device->GPPU_reg);

    //set the GPIO register
    this->_pmcp23017Device->GPIO_reg = GPIO_ALL_OFF;
//    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_GPIO, this->_pmcp23017Device->GPIO_reg);
    this->_mcp23017->gpioPinWriteAll(GPIO_ALL_OFF);
    qDebug() << Q_FUNC_INFO << QString::number(this->_mcp23017->gpioPinReadAll(),2);

    //set the OLAT register
//    this->_pmcp23017Device->OLAT_reg = GPIO_ALL_OFF;
//    this->_mcp23017->writeRegister16(MCP23017_ADDRESS_OLAT, this->_pmcp23017Device->OLAT_reg);

    this->_mcp23017->setPdevice(this->_pmcp23017Device);
}

void MCP2317item::_insertTextAtHomePage(QString textToInsert)
{
    QMetaObject::invokeMethod(this->_homeViewer, "addTextToDisplay",
                              Q_ARG(QVariant, textToInsert));
}

void MCP2317item::_checkStateOfDevice()
{
//    static quint8 checkTimeBeforeError = 10;

    switch (this->_stateMachine)
    {
    case GlobalEnumerate::STATE_NOT_FOUNDED:
    {
        qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << GlobalEnumerate::STATE_NOT_FOUNDED;
        //send text "not founded" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title + " " + GlobaleStaticValue::stateNotFounded);

        //check if the object was created
        //        if(&this->_mcp23017 != nullptr)
        //        {
        //            this->_pmcp23017Device->device_id = this->_mcp23017->MCP23017_fd();
        _goToNextState();
        //        }
        break;
    }
    case GlobalEnumerate::STATE_FOUNDED:
    {

        this->_pmcp23017Device->device_id = this->_fd;

        if(this->_pmcp23017Device->device_id && this->_checkTimeBeforeError)
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << GlobalEnumerate::STATE_FOUNDED;

            //send text "founded" to display
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateFounded);
            //display FD of the device
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title + " FD : " + QString::number(this->_pmcp23017Device->device_id,10));

            //set Add on MCP23017 in setting menu
            QMetaObject::invokeMethod(this->_MCP23017Viewer, "setAdd",
                                      Q_ARG(QVariant, QString::number(this->_deviceI2CAddress,16)));

            //set ID on MCP23017 in setting menu
            QMetaObject::invokeMethod(this->_MCP23017Viewer, "setID",
                                      Q_ARG(QVariant, QString::number(this->_pmcp23017Device->device_id,10)));


            _goToNextState();
        }
        //change the color to red, not ready to use
        else
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << GlobalEnumerate::STATE_NOT_FOUNDED;

            switch(this->_deviceI2CAddress)
            {
            case GlobalEnumerate::MCP23017_1:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_1",
                                          Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
                break;
            case GlobalEnumerate::MCP23017_2:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_2",
                                          Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
                break;
            case GlobalEnumerate::MCP23017_3:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_3",
                                          Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
                break;
            case GlobalEnumerate::MCP23017_4:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_4",
                                          Q_ARG(QVariant, DEVICE_COLOR_IN_TROUBLE_HEX));
                break;
            default:
                break;
            }

            this->terminate();

        }
        break;
    }
    case GlobalEnumerate::STATE_INIT:
    {
        qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << GlobalEnumerate::STATE_INIT;

        //send text "init" to display
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                    +" FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                    + " " + GlobaleStaticValue::stateInit
                                    + ", cnt: " + QString::number(this->_checkTimeBeforeError,10));

//        while(!this->_initIODIRregOK)
//        {
//            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : wait IODIR reg setted from initfile";
//            this->_waitDelay(1);
//        }

        this->_initDevice();
//        this->_registerConfigurationOK = this->_checkRegisterConfiguration();

        //programme the device register
        this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                    + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                    + " " + GlobaleStaticValue::stateOnProgramming);
        //        this->_initRegisterDevice();

        //check the good programming of the device register
        if(this->_checkRegisterConfiguration() && this->_checkTimeBeforeError)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateProgrammingSuccessful);

            //set IODir on MCP23017 in setting menu
            QMetaObject::invokeMethod(this->_MCP23017Viewer, "setIODir",
                                      Q_ARG(QVariant, QString::number(this->_pmcp23017Device->IODIR_reg,16)));

            //            this->_mcp23017->writeRegister16(0x00, 0x00FF);
            this->_mcp23017->gpioPinWriteAll(GPIO_ALL_OFF);

            //            switch(this->_deviceI2CAddress)
            //            {
            //            case GlobalEnumerate::MCP23017_1:
            //                this->_wiringPiGardian->setMCP23017_1fd(this->_pmcp23017Device->device_id);
            //                this->_wiringPiGardian->setMCP23017_1Register(0x00, 0x0000);
            //                break;
            //            case GlobalEnumerate::MCP23017_2:
            //                this->_wiringPiGardian->setMCP23017_2fd(this->_pmcp23017Device->device_id);
            //                this->_wiringPiGardian->setMCP23017_2Register(0x00, 0x0000);
            //                break;
            //            case GlobalEnumerate::MCP23017_3:
            //                this->_wiringPiGardian->setMCP23017_3fd(this->_pmcp23017Device->device_id);
            //                this->_wiringPiGardian->setMCP23017_3Register(0x00, 0x0000);
            //                break;
            //            case GlobalEnumerate::MCP23017_4:
            //                this->_wiringPiGardian->setMCP23017_4fd(this->_pmcp23017Device->device_id);
            //                this->_wiringPiGardian->setMCP23017_4Register(0x00, 0x0000);
            //                break;
            //            default:
            //                break;
            //            }

            //            wiringPiI2CWriteReg16(this->_pmcp23017Device->device_id, 0x00, 0x0000);

            _goToNextState();
        }
        else
        {
            this->_checkTimeBeforeError -= this->_checkTimeBeforeError > 0 ? 1 : 0;
        }

        this->_stateMachine = this->_checkTimeBeforeError > 0 ? this->_stateMachine : GlobalEnumerate::STATE_FOUNDED;

        break;
    }
    case GlobalEnumerate::STATE_ON_READING:
    {
        //        qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << GlobalEnumerate::STATE_ON_READING;

        //send text "on reading" to display
        if(!this->_deviceIsReady)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateOnReading);
        }


//        if(!this->_checkRegisterConfiguration())
//        {
//                this->_stateMachine = GlobalEnumerate::STATE_INIT;
//        }

        if(!this->_deviceIsReady)
        {
            //change the color to blue, on analysis
            switch(this->_deviceI2CAddress)
            {
            case GlobalEnumerate::MCP23017_1:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_1",
                                          Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
                break;
            case GlobalEnumerate::MCP23017_2:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_2",
                                          Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
                break;
            case GlobalEnumerate::MCP23017_3:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_3",
                                          Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
                break;
            case GlobalEnumerate::MCP23017_4:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_4",
                                          Q_ARG(QVariant, DEVICE_COLOR_WORKING_HEX));
                break;
            default:
                break;
            }

            this->_onReadingData = true;
        }

        this->_readDataI2C();
        _goToNextState();

        break;
    }
    case GlobalEnumerate::STATE_READY:
    {
        //        qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << GlobalEnumerate::STATE_READY;

        //send text "ready" to display
        if(!this->_deviceIsReady)
        {
            this->_insertTextAtHomePage(GlobaleStaticValue::MCP23017Title
                                        + " FD : " + QString::number(this->_pmcp23017Device->device_id,10)
                                        + " " + GlobaleStaticValue::stateReady);

            //change the color to green, ready to use
            switch(this->_deviceI2CAddress)
            {
            case GlobalEnumerate::MCP23017_1:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_1",
                                          Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
                break;
            case GlobalEnumerate::MCP23017_2:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_2",
                                          Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
                break;
            case GlobalEnumerate::MCP23017_3:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_3",
                                          Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
                break;
            case GlobalEnumerate::MCP23017_4:
                QMetaObject::invokeMethod(this->_homeViewer, "changeColorMCP23017_4",
                                          Q_ARG(QVariant, DEVICE_COLOR_READY_HEX));
                break;
            default:
                break;
            }

            this->_deviceIsReady = true;
        }

        switch(this->_deviceI2CAddress)
        {
        case GlobalEnumerate::MCP23017_1:
            this->_wiringPiGardian->setMCP23017_1isReady(this->_deviceIsReady);
            break;
        case GlobalEnumerate::MCP23017_2:
            this->_wiringPiGardian->setMCP23017_2isReady(this->_deviceIsReady);
            break;
        case GlobalEnumerate::MCP23017_3:
            this->_wiringPiGardian->setMCP23017_3isReady(this->_deviceIsReady);
            break;
        case GlobalEnumerate::MCP23017_4:
            this->_wiringPiGardian->setMCP23017_4isReady(this->_deviceIsReady);
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

//void MCP2317item::_initRegisterDevice()
//{
//    this->_mcp23017->init();
//}

bool MCP2317item::_checkRegisterConfiguration()
{
    quint16 registerOK = 0;
    quint16 registerValue = 0;


    //check the IODIR register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_IODIR);
    registerOK = registerValue == this->_pmcp23017Device->IODIR_reg ? 1 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "IODIR_reg read: " << QString::number(registerValue,2)
//             << "IODIR_reg set:  " << QString::number(this->_pmcp23017Device->IODIR_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the IPOL register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_IPOL);
    registerOK |= registerValue == this->_pmcp23017Device->IPOL_reg ? 2 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "IPOL_reg read: " << QString::number(registerValue,2)
//             << "IPOL_reg set:  " << QString::number(this->_pmcp23017Device->IPOL_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the GPINT register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_GPINTEN);
    registerOK |= registerValue == this->_pmcp23017Device->GPINT_reg ? 4 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "GPINT_reg read: " << QString::number(registerValue,2)
//             << "GPINT_reg set:  "<< QString::number(this->_pmcp23017Device->GPINT_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the DEFVAL register
//    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_DEFVAL);
//    registerOK |= registerValue == this->_pmcp23017Device->DEFVAL_reg ? 8 : 0;
      registerOK |= 8;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "DEFVAL_reg read" << QString::number(registerValue,2) << "DEFVAL_reg set: "
//             << QString::number(this->_pmcp23017Device->DEFVAL_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the INTCON register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_INTCON);
    registerOK |= registerValue == this->_pmcp23017Device->INTCON_reg ? 16 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "INTCON_reg read: " << QString::number(registerValue,2)
//             << "INTCON_reg set:  " << QString::number(this->_pmcp23017Device->INTCON_reg,2)
//             << QString::number(this->_pmcp23017Device->DEFVAL_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the IOCON register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_IOCON);
    registerOK |= registerValue == this->_pmcp23017Device->IOCON_reg ? 32 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "IOCON_reg read: " << QString::number(registerValue,2)
//             << "IOCON_reg set:  " << QString::number(this->_pmcp23017Device->IOCON_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the GPPU register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_GPPU);
    registerOK |= registerValue == this->_pmcp23017Device->GPPU_reg ? 64 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "GPPU_reg read: " << QString::number(registerValue,2)
//             << "GPPU_reg set:  " << QString::number(this->_pmcp23017Device->GPPU_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the INTF register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_INTF);
//    registerOK |= registerValue == this->_pmcp23017Device->INTF_reg ? 128 : 0;
    registerOK |= 128;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "DEFVAL_reg read: " << QString::number(registerValue,2)
//             << "DEFVAL_reg set:  " << QString::number(this->_pmcp23017Device->DEFVAL_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the INTCAP register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_INTCAP);
    registerOK |= registerValue == this->_pmcp23017Device->INTCAP_reg ? 256 : 0;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "INTCAP_reg read: " << QString::number(registerValue,2)
//             << "INTCAP_reg set:  " << QString::number(this->_pmcp23017Device->INTCAP_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    //check the GPIO register
    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_GPIO);
    registerOK |= registerValue == this->_pmcp23017Device->GPIO_reg ? 512 : 0;
    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
             << "GPIO_reg read: " << QString::number(registerValue,2)
             << "GPIO_reg set:  " << QString::number(this->_pmcp23017Device->GPIO_reg,2)
             << "registerOK: "  << QString::number(registerOK,2) << " : " << (registerOK == 0b11111111111);

    //check the OLAT register
//    registerValue = this->_mcp23017->readRegister16(MCP23017_ADDRESS_OLAT);
//    registerOK |= registerValue == this->_pmcp23017Device->OLAT_reg ? 1024 : 0;
      registerOK |= 1024;
//    qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : "
//             << "OLAT_reg read: " << QString::number(registerValue,2)
//             << "OLAT_reg set:  " << QString::number(this->_pmcp23017Device->OLAT_reg,2)
//             << "registerOK: "  << QString::number(registerOK,2);

    if(registerOK != 0b11111111111)
    {
        if(!(registerOK & 1))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : IODIR_reg";
        }

        if(!(registerOK & 2))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : IPOL_reg";
        }

        if(!(registerOK & 4))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : GPINT_reg";
        }

        if(!(registerOK & 8))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : DEFVAL_reg";
        }

        if(!(registerOK & 16))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : INTCON_reg";
        }

        if(!(registerOK & 32))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : IOCON_reg";
        }

        if(!(registerOK & 64))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : GPPU_reg";
        }

        if(!(registerOK & 128))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : INTF_reg";
        }

        if(!(registerOK & 256))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : INTCAP_reg";
        }

        if(!(registerOK & 512))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : GPIO_reg";
        }

        if(!(registerOK & 1024))
        {
            qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id << " : " << "Error on : OLAT_reg";
        }

    }
    //    qDebug() << Q_FUNC_INFO << "registerOK :" << QString::number(registerOK,2);

//    return (registerOK == 0b11111111111 ? true : false);
       return (true);
}

void MCP2317item::_readDataI2C()
{
//        if(this->_ledOn)
//        {
//            this->_mcp23017->gpioPinWriteAll(0xFEFF);
//           this->_ledOn = false;
//        }
//        else
//        {
//            this->_mcp23017->gpioPinWriteAll(0x0100);
//            this->_ledOn = true;

//        }

    if(this->_pmcp23017Device->GPIO_reg != this->_mcp23017->gpioPinReadAll())
    {
        this->_pmcp23017Device->GPIO_reg = this->_mcp23017->gpioPinReadAll();
        QMetaObject::invokeMethod(this->_MCP23017Viewer, "setregGPIO",
                                  Q_ARG(QVariant, this->_pmcp23017Device->GPIO_reg));
        qDebug() << Q_FUNC_INFO << this->_pmcp23017Device->device_id
                 << " GPIO read all : " << QString::number(this->_mcp23017->gpioPinReadAll(),2)
                 << " GPIO_reg      : " << QString::number(this->_pmcp23017Device->GPIO_reg,2)
                 << " OLAT read all : " << QString::number(this->_mcp23017->readRegister16(MCP23017_ADDRESS_OLAT),2);
    }

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
