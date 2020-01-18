#include "MCP23017/mcp23017.h"

MCP23017::MCP23017(quint8 device_I2C_Adress, quint8 pinbase, quint8 fd):
    _MCP23017_i2cAddress(device_I2C_Adress),
    _MCP23017_pinBase(pinbase),
    _MCP23017_fd(fd),
    _MCP23017_IOCON(0),
    _gpioDirection(GPIO_ALL_OUTPUT),
    _gpioState(GPIO_ALL_OFF)
{
//      this->_MCP23017_fd = device_I2C_Adress;
//    this->_MCP23017_pinBase += (this->_MCP23017_i2cAddress - GlobalEnumerate::MCP23017_1) * 16;
//    mcp23017Setup(this->_MCP23017_pinBase, this->_MCP23017_i2cAddress);
//    this->_MCP23017_fd = wiringPiI2CSetup(this->_MCP23017_i2cAddress);
//    qDebug() << Q_FUNC_INFO << "address founded : " << this->_MCP23017_fd;
}

void MCP23017::init_smcp23017_device(pmcp23017_device pmcp23017_device)
{
    pmcp23017_device->chip_id = 0;
    pmcp23017_device->device_id = 0;
    pmcp23017_device->IODIR_reg = 0;
    pmcp23017_device->IPOL_reg = 0;
    pmcp23017_device->GPINT_reg = 0;
    pmcp23017_device->DEFVAL_reg = 0;
    pmcp23017_device->INTCON_reg = 0;
}

void MCP23017::init_smcp23017_IOCON(pmcp23017_IOCON pmcp23017_IOCONreg)
{
    pmcp23017_IOCONreg->BANK = 0;
    pmcp23017_IOCONreg->MIRROR = 0;
    pmcp23017_IOCONreg->SEQOP = 0;
    pmcp23017_IOCONreg->DISSLW = 0;
    pmcp23017_IOCONreg->HAEN = 0;
    pmcp23017_IOCONreg->ODR = 0;
    pmcp23017_IOCONreg->INTPOL = 0;
    pmcp23017_IOCONreg->NOTUSED = 0;
}

//void MCP23017::init()
//{
//    wiringPiSetupSys();
//    this->_MCP23017_fd = wiringPiI2CSetup(this->_MCP23017_i2cAddress);
//    this->_MCP23017_pinBase += (this->MCP23017_fd() - MCP23017_ADDRESS_DEFAULT_20) * 16;
//    mcp23017Setup(this->_MCP23017_pinBase, this->_MCP23017_i2cAddress);
//    this->writeGPIOPinMode();
    //    quint16 regValue = this->convertIOCONStructToRegValue(this->_pIOCON);
//    mcp23017Setup(65,this->_MCP23017_fd);

//    for (int i = 0 ; i < 16 ; i++)
//    {
//        pinMode (_MCP23017_pinBase + i, OUTPUT) ;
//        digitalWrite(_MCP23017_pinBase + i, 1);
//    }

//    quint16 regValue = this->_pdevice->IOCON_reg;

//    qDebug() << Q_FUNC_INFO << this->_pdevice->device_id
//             << QString::number(regValue,2);

//    //write icon register
//    //    this->writeRegister(MCP23017_ADDRESS_INTCONA, regValue);
//    this->writeRegister8(MCP23017_ADDRESS_IOCONA, regValue &0xFF);
//    this->writeRegister8(MCP23017_ADDRESS_IOCONB, regValue >> 8);

//    //write direction of IO
//    this->gpioPinMode(this->_gpioDirection);

//    //switch all to 0
//    if(this->_gpioDirection == GPIO_ALL_OUTPUT)
//    {
//        this->writeRegister8(MCP23017_ADDRESS_GPIOA, GPIO_ALL_ON & 0xFF);
//        this->writeRegister8(MCP23017_ADDRESS_GPIOB, GPIO_ALL_ON >> 8);
//    }

//    //enable all pull up resistors (will be effective for input pins only)
//    this->writeRegister8(MCP23017_ADDRESS_GPPUA, GPIO_ALL_ON & 0xFF);
//    this->writeRegister8(MCP23017_ADDRESS_GPIOB, GPIO_ALL_ON >> 8);
//}

void MCP23017::writeGPIOPinMode()
{
    this->writeRegister16(MCP23017_ADDRESS_IODIR, this->_gpioDirection);
    qDebug() << Q_FUNC_INFO << "IODIR: " << QString::number((readRegister16(MCP23017_ADDRESS_IODIR)),2);
}

void MCP23017::gpioSinglePinModeDirection(quint8 pin, bool direction)
{
    pinMode (this->_MCP23017_pinBase + pin, direction) ;
}

void MCP23017::gpioPinDigitalWrite(quint8 pin, bool value)
{
    digitalWrite(this->_MCP23017_pinBase + pin, value);
}

bool MCP23017::gpioPinDigitalRead(quint8 pin)
{
    return digitalRead(this->_MCP23017_pinBase + pin);
}

void MCP23017::gpioPinWriteAll(quint16 allPinValue)
{
    wiringPiI2CWriteReg16(this->_MCP23017_fd, MCP23017_ADDRESS_GPIO, allPinValue);

}

quint16 MCP23017::gpioPinReadAll()
{
    return wiringPiI2CReadReg16(this->_MCP23017_fd, MCP23017_ADDRESS_GPIO);
}

void MCP23017::writeRegister16(quint8 registerName, quint16 value)
{
    wiringPiI2CWriteReg16(this->_MCP23017_fd, registerName, value);
}

void MCP23017::writeRegister8(quint8 registerName, quint8 value)
{
    wiringPiI2CWriteReg8(this->_MCP23017_fd, registerName, value);
}

quint8 MCP23017::readRegister8(quint8 registerName)
{
    return wiringPiI2CReadReg8(this->_MCP23017_fd, registerName);
}

quint16 MCP23017::readRegister16(quint16 registerName)
{
    return wiringPiI2CReadReg16(this->_MCP23017_fd, registerName);
}

quint8 MCP23017::MCP23017_fd() const
{
    return _MCP23017_fd;
}

pmcp23017_device MCP23017::pdevice() const
{
    return _pdevice;
}

void MCP23017::setPdevice(const pmcp23017_device &pdevice)
{
    _pdevice = pdevice;
}

//pmcp23017_IOCON MCP23017::pIOCON() const
//{
//    return _pIOCON;
//}

//void MCP23017::setPIOCON(const pmcp23017_IOCON &pIOCON)
//{
//    _pIOCON = pIOCON;
//}

quint16 MCP23017::convertIOCONStructToRegValue(pmcp23017_IOCON pIOCON)
{
    quint16  regValue = 0;

    regValue |= pIOCON->BANK;
    regValue |= pIOCON->MIRROR;
    regValue |= pIOCON->SEQOP;
    regValue |= pIOCON->DISSLW ;
    regValue |= pIOCON->HAEN;
    regValue |= pIOCON->ODR;
    regValue |= pIOCON->INTPOL;
    regValue |= pIOCON->NOTUSED;

    regValue = regValue << 8;

    regValue |= pIOCON->BANK;
    regValue |= pIOCON->MIRROR;
    regValue |= pIOCON->SEQOP;
    regValue |= pIOCON->DISSLW;
    regValue |= pIOCON->HAEN;
    regValue |= pIOCON->ODR;
    regValue |= pIOCON->INTPOL;
    regValue |= pIOCON->NOTUSED;

    qDebug() << Q_FUNC_INFO << this->_MCP23017_fd
             << pIOCON->BANK << pIOCON->MIRROR
             << pIOCON->SEQOP << pIOCON->DISSLW
             << pIOCON->HAEN << pIOCON->ODR
             << pIOCON->INTPOL;
    qDebug() << Q_FUNC_INFO << this->_MCP23017_fd << QString::number(regValue,2);

    return regValue;
}

quint16 MCP23017::gpioDirection() const
{
    return _gpioDirection;
}

void MCP23017::setGpioDirection(const quint16 &gpioDirection)
{
    _gpioDirection = gpioDirection;
}
