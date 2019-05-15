#ifndef ADS1115_H
#define ADS1115_H

/**************************************************************************/
/*
        Distributed with a free-will license.
        Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
        ADS1115
        This code is designed to work with the ADS1115_I2CADC I2C based on adafruit code and modified for Qt on Raspberry
*/
/**************************************************************************/


#include <QtGlobal>
#include <QDebug>
#include <wiringPiI2C.h>

#include <QTimer>
#include <QThread>


/**************************************************************************
    I2C ADDRESS/BITS
**************************************************************************/
#define ADS1115_DEFAULT_ADDRESS         (0x48)    // 1001 000 (ADDR = GND)
#define ADS1115_VDD_ADDRESS             (0x49)    // 1001 001 (ADDR = VDD)
#define ADS1115_SDA_ADDRESS             (0x4A)    // 1001 010 (ADDR = SDA)
#define ADS1115_SCL_ADDRESS             (0x4B)    // 1001 011 (ADDR = SCL)

/**************************************************************************
    CONVERSION DELAY (in mS)
**************************************************************************/
#define ADS1115_CONVERSIONDELAY         (200000)

/**************************************************************************
    POINTER REGISTER
**************************************************************************/
#define ADS1115_REG_POINTER_MASK        (0x03)
#define ADS1115_REG_POINTER_CONVERT     (0x00)
#define ADS1115_REG_POINTER_CONFIG      (0x01)
#define ADS1115_REG_POINTER_LOWTHRESH   (0x02)
#define ADS1115_REG_POINTER_HITHRESH    (0x03)

/**************************************************************************
    CONFIG REGISTER
**************************************************************************/
#define ADS1115_REG_CONFIG_OS_MASK      (0x8000)    // Operational status/single-shot conversion start
#define ADS1115_REG_CONFIG_OS_NOEFFECT  (0x0000)    // Write: Bit = 0 No effect
#define ADS1115_REG_CONFIG_OS_SINGLE    (0x8000)    // Write: Bit = 1 Begin a single conversion
#define ADS1115_REG_CONFIG_OS_BUSY      (0x0000)    // Read: Bit = 0 Device is performing a conversion
#define ADS1115_REG_CONFIG_OS_NOTBUSY   (0x8000)    // Read: Bit = 1 Device is not performing a conversion

#define ADS1115_REG_CONFIG_MUX_MASK     (0x7000)    // Input multiplexer configuration
#define ADS1115_REG_CONFIG_MUX_DIFF_0_1 (0x0000)    // Differential P = AIN0, N = AIN1 (default)
#define ADS1115_REG_CONFIG_MUX_DIFF_0_3 (0x1000)    // Differential P = AIN0, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_1_3 (0x2000)    // Differential P = AIN1, N = AIN3
#define ADS1115_REG_CONFIG_MUX_DIFF_2_3 (0x3000)    // Differential P = AIN2, N = AIN3
#define ADS1115_REG_CONFIG_MUX_SINGLE_0 (0x4000)    // Single-ended P = AIN0, N = GND
#define ADS1115_REG_CONFIG_MUX_SINGLE_1 (0x5000)    // Single-ended P = AIN1, N = GND
#define ADS1115_REG_CONFIG_MUX_SINGLE_2 (0x6000)    // Single-ended P = AIN2, N = GND
#define ADS1115_REG_CONFIG_MUX_SINGLE_3 (0x7000)    // Single-ended P = AIN3, N = GND

#define ADS1115_REG_CONFIG_PGA_MASK     (0x0E00)    // Programmable gain amplifier configuration
#define ADS1115_REG_CONFIG_PGA_6_144V   (0x0000)    // +/-6.144V range = Gain 2/3
#define ADS1115_REG_CONFIG_PGA_4_096V   (0x0200)    // +/-4.096V range = Gain 1
#define ADS1115_REG_CONFIG_PGA_2_048V   (0x0400)    // +/-2.048V range = Gain 2 (default)
#define ADS1115_REG_CONFIG_PGA_1_024V   (0x0600)    // +/-1.024V range = Gain 4
#define ADS1115_REG_CONFIG_PGA_0_512V   (0x0800)    // +/-0.512V range = Gain 8
#define ADS1115_REG_CONFIG_PGA_0_256V   (0x0A00)    // +/-0.256V range = Gain 16

#define ADS1115_REG_CONFIG_MODE_MASK    (0x0100)    // Device operating mode
#define ADS1115_REG_CONFIG_MODE_CONTIN  (0x0000)    // Continuous conversion mode
#define ADS1115_REG_CONFIG_MODE_SINGLE  (0x0100)    // Power-down single-shot mode (default)

#define ADS1115_REG_CONFIG_DR_MASK      (0x00E0)    // Data rate
#define ADS1115_REG_CONFIG_DR_8SPS      (0x0000)    // 8 samples per second
#define ADS1115_REG_CONFIG_DR_16SPS     (0x0020)    // 16 samples per second
#define ADS1115_REG_CONFIG_DR_32SPS     (0x0040)    // 32 samples per second
#define ADS1115_REG_CONFIG_DR_64SPS     (0x0060)    // 64 samples per second
#define ADS1115_REG_CONFIG_DR_128SPS    (0x0080)    // 128 samples per second (default)
#define ADS1115_REG_CONFIG_DR_250SPS    (0x00A0)    // 250 samples per second
#define ADS1115_REG_CONFIG_DR_475SPS    (0x00C0)    // 475 samples per second
#define ADS1115_REG_CONFIG_DR_860SPS    (0x00E0)    // 860 samples per second

#define ADS1115_REG_CONFIG_COMP_MODE_MASK   (0x0010)    // Comparator mode
#define ADS1115_REG_CONFIG_COMP_MODE_TRAD   (0x0000)    // Traditional comparator with hysteresis (default)
#define ADS1115_REG_CONFIG_COMP_MODE_WINDOW (0x0010)    // Window comparator

#define ADS1115_REG_CONFIG_COMP_POL_MASK    (0x0008)    // Comparator polarity
#define ADS1115_REG_CONFIG_COMP_POL_ACTVLOW (0x0000)    // ALERT/RDY pin is low when active (default)
#define ADS1115_REG_CONFIG_COMP_POL_ACTVHI  (0x0008)    // ALERT/RDY pin is high when active

#define ADS1115_REG_CONFIG_COMP_LAT_MASK    (0x0004)    // Latching comparator
#define ADS1115_REG_CONFIG_COMP_LAT_NONLAT  (0x0000)    // Non-latching comparator (default)
#define ADS1115_REG_CONFIG_COMP_LAT_LATCH   (0x0004)    // Latching comparator

#define ADS1115_REG_CONFIG_COMP_QUE_MASK    (0x0003)    // Comparator queue and disable
#define ADS1115_REG_CONFIG_COMP_QUE_1CONV   (0x0000)    // Assert ALERT/RDY after one conversions
#define ADS1115_REG_CONFIG_COMP_QUE_2CONV   (0x0001)    // Assert ALERT/RDY after two conversions
#define ADS1115_REG_CONFIG_COMP_QUE_4CONV   (0x0002)    // Assert ALERT/RDY after four conversions
#define ADS1115_REG_CONFIG_COMP_QUE_NONE    (0x0003)    // Disable the comparator and put ALERT/RDY in high state (default)

typedef enum
{
    OSMODE_SINGLE   = ADS1115_REG_CONFIG_OS_SINGLE,
    OSMODE_BUSY     = ADS1115_REG_CONFIG_OS_BUSY,
    OSMODE_NOTBUSY  = ADS1115_REG_CONFIG_OS_NOTBUSY

} adsOSMode_t;

typedef enum
{
    GAIN_TWOTHIRDS    = ADS1115_REG_CONFIG_PGA_6_144V,
    GAIN_ONE          = ADS1115_REG_CONFIG_PGA_4_096V,
    GAIN_TWO          = ADS1115_REG_CONFIG_PGA_2_048V,
    GAIN_FOUR         = ADS1115_REG_CONFIG_PGA_1_024V,
    GAIN_EIGHT        = ADS1115_REG_CONFIG_PGA_0_512V,
    GAIN_SIXTEEN      = ADS1115_REG_CONFIG_PGA_0_256V
} adsGain_t;

typedef enum
{
    MODE_CONTIN     = ADS1115_REG_CONFIG_MODE_CONTIN,
    MODE_SINGLE     = ADS1115_REG_CONFIG_MODE_SINGLE
} adsMode_t;

typedef enum
{
    RATE_8          = ADS1115_REG_CONFIG_DR_8SPS,
    RATE_16         = ADS1115_REG_CONFIG_DR_16SPS,
    RATE_32         = ADS1115_REG_CONFIG_DR_32SPS,
    RATE_64         = ADS1115_REG_CONFIG_DR_64SPS,
    RATE_128        = ADS1115_REG_CONFIG_DR_128SPS,
    RATE_250        = ADS1115_REG_CONFIG_DR_250SPS,
    RATE_475        = ADS1115_REG_CONFIG_DR_475SPS,
    RATE_860        = ADS1115_REG_CONFIG_DR_860SPS
} adsRate_t;

typedef enum
{
    COMPMODE_TRAD   = ADS1115_REG_CONFIG_COMP_MODE_TRAD,
    COMPMODE_WINDOW = ADS1115_REG_CONFIG_COMP_MODE_WINDOW
} adsCompMode_t;

typedef enum
{
    COMPPOL_LOW     = ADS1115_REG_CONFIG_COMP_POL_ACTVLOW,
    COMPPOL_HIGH    = ADS1115_REG_CONFIG_COMP_POL_ACTVHI
} adsCompPol_t;

typedef enum
{
    COMPLAT_NONLAT  = ADS1115_REG_CONFIG_COMP_LAT_NONLAT,
    COMPLAT_LATCH   = ADS1115_REG_CONFIG_COMP_LAT_LATCH
} adsCompLat_t;

typedef enum
{
    COMPQUE_ONE     = ADS1115_REG_CONFIG_COMP_QUE_1CONV,
    COMPQUE_TWO     = ADS1115_REG_CONFIG_COMP_QUE_2CONV,
    COMPQUE_FOUR    = ADS1115_REG_CONFIG_COMP_QUE_4CONV,
    COMPQUE_NONE    = ADS1115_REG_CONFIG_COMP_QUE_NONE
} adsCompQue_t;

class ADS1115
{
public:

    ADS1115(quint8 device_I2C_Adress = ADS1115_DEFAULT_ADDRESS);

    quint8 ads_i2cAddress() const;
    void setAds_i2cAddress(const quint8 &ads_i2cAddress);

    quint8 ads_fd() const;
    void setAds_fd(const quint8 &ads_fd);

    quint64 ads_conversionDelay() const;
    void setAds_conversionDelay(const quint64 &ads_conversionDelay);

    adsOSMode_t ads_osmode() const;
    void setAds_osmode(const adsOSMode_t &ads_osmode);

    /**************************************************************************/
    /*
            Sets the gain and input voltage range
            This configures the programmable gain amplifier
    */
    /**************************************************************************/
    adsGain_t ads_gain() const;
    void setAds_gain(const adsGain_t &ads_gain);

    adsMode_t ads_mode() const;
    void setAds_mode(const adsMode_t &ads_mode);

    adsRate_t ads_rate() const;
    void setAds_rate(const adsRate_t &ads_rate);

    adsCompMode_t ads_compmode() const;
    void setAds_compmode(const adsCompMode_t &ads_compmode);

    adsCompPol_t ads_comppol() const;
    void setAds_comppol(const adsCompPol_t &ads_comppol);

    adsCompLat_t ads_complat() const;
    void setAds_complat(const adsCompLat_t &ads_complat);

    adsCompQue_t ads_compque() const;
    void setAds_compque(const adsCompQue_t &ads_compque);

    /**************************************************************************/
    /*
            Reads the conversion results, measuring the voltage
            for a single-ended ADC reading from the specified channel
            Negative voltages cannot be applied to this circuit because the
            ADS1115 can only accept positive voltages
    */
    /**************************************************************************/
    quint16  Measure_SingleEnded_OnlyPositiveValue(quint8 channel);

    float convertValueToVolt(quint16 regValue);

    quint16 ads_config_register() const;

    void setRegister(bool forFirstInit);
    qint16 readConfigRegister();

private:

    quint8 _ads_i2cAddress;
    quint8 _ads_fd;
    quint64 _ads_conversionDelay;
    quint16 _ads_config_register;
    quint16 _ads_reading_value;
    qint16 _ads_lowthreshold;
    qint16 _ads_highthreshold;

    adsOSMode_t _ads_osmode;
    adsGain_t _ads_gain;
    adsMode_t _ads_mode;
    adsRate_t _ads_rate;
    adsCompMode_t _ads_compmode;
    adsCompPol_t _ads_comppol;
    adsCompLat_t _ads_complat;
    adsCompQue_t _ads_compque;


    /**************************************************************************/
    /*
            Writes 16-bits to the specified destination register
    */
    /**************************************************************************/
    void _writeRegister(quint16 regValue);

    qint16 _swapRegister(qint16 regValue);


    /**************************************************************************/
    /*
            Reads 16-bits to the specified destination register
    */
    /**************************************************************************/
    qint16 _readRegisterOnlyPositiveValue();

    void _waitDelay(quint64 delayInMiliSeconde);

    void _waitConvertionFinished();
};

#endif // ADS1115_H
