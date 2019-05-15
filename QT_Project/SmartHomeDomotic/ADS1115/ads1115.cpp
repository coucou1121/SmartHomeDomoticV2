#include "ads1115.h"

/**************************************************************************/
/*
        Instantiates a new ADS1115 class with appropriate properties
*/
/**************************************************************************/
ADS1115::ADS1115(quint8 device_I2C_Adress):
    _ads_i2cAddress(device_I2C_Adress),
    _ads_fd(0),
    _ads_conversionDelay(ADS1115_CONVERSIONDELAY),
    _ads_config_register(0),
    _ads_reading_value(0),
    _ads_lowthreshold(0),
    _ads_highthreshold(0),
    _ads_osmode(OSMODE_SINGLE),
    _ads_gain(GAIN_TWOTHIRDS),
    _ads_mode(MODE_SINGLE),
    _ads_rate(RATE_128),
    _ads_compmode(COMPMODE_TRAD),
    _ads_comppol(COMPPOL_LOW),
    _ads_complat(COMPLAT_NONLAT),
    _ads_compque(COMPQUE_NONE)
{
    this->_ads_fd = wiringPiI2CSetup(_ads_i2cAddress);
    qDebug() << "ADS1115 addresse founded : " << this->_ads_fd;
    //    this->set_config_register();
    qDebug() << "ADS1115 default config register set : " << this->_ads_config_register;

}


quint8 ADS1115::ads_i2cAddress() const
{
    return _ads_i2cAddress;
}
void ADS1115::setAds_i2cAddress(const quint8 &ads_i2cAddress)
{
    _ads_i2cAddress = ads_i2cAddress;
}
quint8 ADS1115::ads_fd() const
{
    return _ads_fd;
}
void ADS1115::setAds_fd(const quint8 &ads_fd)
{
    _ads_fd = ads_fd;
}
quint64 ADS1115::ads_conversionDelay() const
{
    return _ads_conversionDelay;
}
void ADS1115::setAds_conversionDelay(const quint64 &ads_conversionDelay)
{
    _ads_conversionDelay = ads_conversionDelay;
}
adsOSMode_t ADS1115::ads_osmode() const
{
    return _ads_osmode;
}
void ADS1115::setAds_osmode(const adsOSMode_t &ads_osmode)
{
    _ads_osmode = ads_osmode;
}
adsGain_t ADS1115::ads_gain() const
{
    return _ads_gain;
}
void ADS1115::setAds_gain(const adsGain_t &ads_gain)
{
    _ads_gain = ads_gain;
}
adsMode_t ADS1115::ads_mode() const
{
    return _ads_mode;
}
void ADS1115::setAds_mode(const adsMode_t &ads_mode)
{
    _ads_mode = ads_mode;
}
adsRate_t ADS1115::ads_rate() const
{
    return _ads_rate;
}
void ADS1115::setAds_rate(const adsRate_t &ads_rate)
{
    _ads_rate = ads_rate;
}
adsCompMode_t ADS1115::ads_compmode() const
{
    return _ads_compmode;
}
void ADS1115::setAds_compmode(const adsCompMode_t &ads_compmode)
{
    _ads_compmode = ads_compmode;
}
adsCompPol_t ADS1115::ads_comppol() const
{
    return _ads_comppol;
}
void ADS1115::setAds_comppol(const adsCompPol_t &ads_comppol)
{
    _ads_comppol = ads_comppol;
}
adsCompLat_t ADS1115::ads_complat() const
{
    return _ads_complat;
}
void ADS1115::setAds_complat(const adsCompLat_t &ads_complat)
{
    _ads_complat = ads_complat;
}
adsCompQue_t ADS1115::ads_compque() const
{
    return _ads_compque;
}
void ADS1115::setAds_compque(const adsCompQue_t &ads_compque)
{
    _ads_compque = ads_compque;
}

void ADS1115::setRegister(bool forFirstInit)
{
    // Go out of power-down mode for conversion.
    this->_ads_config_register = this->_ads_osmode;

    // config the gain
    this->_ads_config_register |= this->_ads_gain;

    // Set the mode (continuous or single shot).
    this->_ads_config_register |= this->_ads_mode;

    // Set rate
    this->_ads_config_register |= this->_ads_rate;

    // Comparator mode
    this->_ads_config_register |= this->_ads_compmode;

    // Comparator polarity
    this->_ads_config_register |= this->_ads_comppol;

    // Latching comparator
    this->_ads_config_register |= this->_ads_complat;

    //  Comparator queue, Disble comparator mode.
    this->_ads_config_register |= this->_ads_compque;

    if(forFirstInit)
    {
        this->_writeRegister(this->ads_config_register());
    }

}

qint16 ADS1115::readConfigRegister()
{
    qint16 val = 0;

    val = wiringPiI2CReadReg16(this->_ads_fd,
                               ADS1115_REG_POINTER_CONFIG);

    //        qDebug() << "register value: " << QString::number(val,2);
    val = this->_swapRegister(val);
    //        qDebug() << "register value swap: " << QString::number(val,2);

    return val;
}

void ADS1115::_writeRegister(quint16 regValue)
{
    wiringPiI2CWriteReg16(this->_ads_fd,
                          ADS1115_REG_POINTER_CONFIG,
                          this->_swapRegister(regValue));
}

qint16 ADS1115::_swapRegister(qint16 regValue)
{
    qint16 val = regValue;
    qint16 MSB = 0;
    qint16 LSB = 0;

    MSB = (regValue & 0x00FF) << 8;
    LSB =  (regValue & 0xFF00) >> 8;

    val = MSB | LSB;
    return val;
}

qint16 ADS1115::_readRegisterOnlyPositiveValue()
{
    qint16 val = 0;

    val = wiringPiI2CReadReg16(this->_ads_fd,
                               ADS1115_REG_POINTER_CONVERT);

    //swap the register
    val = this->_swapRegister(val);

    //Check for sign bit and turn into a negative value if set.
    if((val & 0x8000) != 0)
    {
        val -= 1 << 16;
    }

    //set negative value to zero
    val = val < 0 ? 0: val;
    return val;
}

quint16 ADS1115::Measure_SingleEnded_OnlyPositiveValue(quint8 channel)
{
    if (channel > 3)
    {
        return 0;
    }
    else
    {
        //this->_waitConvertionFinished();

        //set the register for reading
        this->setRegister(false);

        // Specify mux value.
        this->_ads_config_register |= ((channel + 0x04) & 0x07) << 12;

        // Write config register to the ADC
        this->_writeRegister(this->_ads_config_register);

        // Wait for the conversion to complete
        this->_waitConvertionFinished();

        //      this->_waitDelay(this->_ads_conversionDelay);


        // Read the conversion results
        // 16-bit unsigned results for the ADS1115
        return this->_readRegisterOnlyPositiveValue();
    }
}

float ADS1115::convertValueToVolt(quint16 regValue)
{
    float voltRangeValue = 0;

    switch (this->_ads_gain) {
    case GAIN_TWOTHIRDS:
        voltRangeValue = 6.144;
        break;
    case GAIN_ONE:
        voltRangeValue = 4.096;
        break;
    case GAIN_TWO:
        voltRangeValue = 2.048;
        break;
    case GAIN_FOUR:
        voltRangeValue = 1.024;
        break;
    case GAIN_EIGHT:
        voltRangeValue = 0.512;
        break;
    case GAIN_SIXTEEN:
        voltRangeValue = 0.256;
        break;
    default:
        break;
    }

    return ((regValue*voltRangeValue)/32767.);
}

quint16 ADS1115::ads_config_register() const
{
    return _ads_config_register;
}

void ADS1115::_waitDelay(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

void ADS1115::_waitConvertionFinished()
{
    bool conversionIsFinished = false;
    quint32 val = 0;

    do
    {
        val = 0x0000;
        val = this->readConfigRegister();
//        val = wiringPiI2CReadReg16(this->_ads_fd,
//                                   ADS1115_REG_POINTER_CONFIG);

        val = val & 0x8000 ;
        conversionIsFinished = val == 0x8000 ? true : false;
//        qDebug() << "wait conversion: " << QString::number(val,2);
        // wait a miliseconde
        this->_waitDelay(10);
    }
    while(!conversionIsFinished);
}


































