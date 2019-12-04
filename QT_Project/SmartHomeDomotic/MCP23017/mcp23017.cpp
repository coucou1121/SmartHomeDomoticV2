#include "mcp23017.h"
MCP23017::MCP23017()
{

};

MCP23017::MCP23017(quint8 device_I2C_Adress):
    _MCP23017_i2cAddress(device_I2C_Adress),
    _MCP23017_fd(0),
    _MCP23017_IOCON(0)
{
    this->_MCP23017_fd = wiringPiI2CSetup(this->_MCP23017_i2cAddress);
    qDebug() << "BME280 addresse founded : " << this->_MCP23017_fd;
}

void MCP23017::init_smcp23017_device(pmcp23017_device pmcp23017_device)
{
    pmcp23017_device->chip_id = 0;
    pmcp23017_device->device_id = 0;
    pmcp23017_device->IODIR_reg = IODIR_REGISTER;
    pmcp23017_device->IPOL_reg = IPOL_REGISTER;
    pmcp23017_device->GPINT_reg = GPINT_REGISTER;
    pmcp23017_device->DEFVAL_reg = DEFVAL_REGISTER;
    pmcp23017_device->INTCON_reg = INTCON_REGISTER;
}

void MCP23017::init_smcp23017_IOCON(pmcp23017_IOCON pmcp23017_IOCONreg)
{
    pmcp23017_IOCONreg->BANK = IOCON_7_BANK;
    pmcp23017_IOCONreg->MIRROR = IOCON_6_MIRROR;
    pmcp23017_IOCONreg->SEQOP = IOCON_5_SEQOP;
    pmcp23017_IOCONreg->DISSLW = IOCON_4_IPOLB;
    pmcp23017_IOCONreg->HAEN = IOCON_3_HAEN;
    pmcp23017_IOCONreg->ODR = IOCON_2_ODR;
    pmcp23017_IOCONreg->INTPOL = IOCON_1_INTPOL;
}

void MCP23017::init()
{
    //write icon register
    wiringPiI2CWriteReg8(this->_pdevice->chip_id, IOCON, this->_sIOCON);

    //enable all pull up resistors (will be effective for input pins only)
    //	writeRegister(GPPUA, 0xFF, 0xFF);
}

smcp23017_IOCON MCP23017::sIOCON() const
{
    return _sIOCON;
}

void MCP23017::setSIOCON(const smcp23017_IOCON &sIOCON)
{
    _sIOCON = sIOCON;
}
