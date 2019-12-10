#ifndef BME280_H
#define BME280_H
/**\mainpage
 * This cpp library is based on the bosch driver in C.
 *
 * Theren't any warranties about the function and the working.
 * Everery dommage will be applies to the developper or user of this library
 *
 * File		bme280.h
 * Date		21.07.2018
 * Version	0.0.1
 *
 */

/**
  * \def BME280_I2C_ADDR_xxxx
  * \brief preprocessor symbole for BME280_I2C_ADDR_PRIM
  * \brief preprocessor symbole for BME280_I2C_ADDR_SEC
  *
  * This symbole is the adresse of the device.
  * BME280_I2C_ADDR_SEC is use for my BME_280
  */
#define BME280_I2C_ADDR_PRIM	UINT8_C(0x76)   //use for my device
#define BME280_I2C_ADDR_SEC		UINT8_C(0x77)

/**
  * \def BME280_CHIP_ID
  * \brief preprocessor symbole for BME280_CHIP_ID
  *
  * This symbole is the registre for the chip identifier number.
  * It's possible to read it on the adresse BME280_CHIP_ID_ADDR
  */
#define BME280_CHIP_ID  0x60   //96 in decimal

/**
  * \def Different register address
  * \brief preprocessor symbole for different register address
  *
  * different register address.
  */
/**\name Register Address */
#define BME280_CHIP_ID_ADDR					0xD0
#define BME280_REGISTER_VERSION             0xD1
#define BME280_RESET_ADDR					0xE0
#define BME280_TEMP_PRESS_CALIB_DATA_ADDR	0x88
#define BME280_HUMIDITY_CALIB_DATA_ADDR		0xE1
#define BME280_CTRL_HUM_ADDR				0xF2
#define BME280_STATUS_ADDR      			0xF3
#define BME280_CTRL_MEAS_ADDR				0xF4
#define BME280_CONFIG_ADDR					0xF5

/**
  * \def BME280_xxxx_MODE
  * \brief preprocessor symbole for BME280_xxxx_MODE
  *
  * Sensor power modes.
  */

#define	BME280_SLEEP_MODE		0x00
#define	BME280_FORCED_MODE		0x01
#define	BME280_NORMAL_MODE		0x03

/**
  * \def Oversampling macros
  * \brief preprocessor symbole for Oversampling macros
  *
  * Oversampling macros
  */
#define BME280_NO_OVERSAMPLING		0x00
#define BME280_OVERSAMPLING_1X		0x01
#define BME280_OVERSAMPLING_2X		0x02
#define BME280_OVERSAMPLING_4X		0x03
#define BME280_OVERSAMPLING_8X		0x04
#define BME280_OVERSAMPLING_16X		0x05

/**
  * \def Standby duration selection macros
  * \brief Standby duration selection macros
  *
  * Standby duration selection macros
  */
#define BME280_STANDBY_TIME_1_MS              0x00
#define BME280_STANDBY_TIME_62_5_MS           0x01
#define BME280_STANDBY_TIME_125_MS			  0x02
#define BME280_STANDBY_TIME_250_MS            0x03
#define BME280_STANDBY_TIME_500_MS            0x04
#define BME280_STANDBY_TIME_1000_MS           0x05
#define BME280_STANDBY_TIME_10_MS             0x06
#define BME280_STANDBY_TIME_20_MS             0x07

/**
  * \def Filter coefficient selection macros
  * \brief Filter coefficient selection macros
  *
  * Filter coefficient selection macros
  */
#define BME280_FILTER_COEFF_OFF               0x00
#define BME280_FILTER_COEFF_2                 0x01
#define BME280_FILTER_COEFF_4                 0x02
#define BME280_FILTER_COEFF_8                 0x03
#define BME280_FILTER_COEFF_16                0x04


/**
  * \def compensate parameter storage
  * \brief compensate parameter storage in the device
  *
  * compensate parameter storage in the device
  */
#define BME280_REGISTER_DIG_T1        0x88
#define BME280_REGISTER_DIG_T2        0x8A
#define BME280_REGISTER_DIG_T3        0x8C
#define BME280_REGISTER_DIG_P1        0x8E
#define BME280_REGISTER_DIG_P2        0x90
#define BME280_REGISTER_DIG_P3        0x92
#define BME280_REGISTER_DIG_P4        0x94
#define BME280_REGISTER_DIG_P5        0x96
#define BME280_REGISTER_DIG_P6        0x98
#define BME280_REGISTER_DIG_P7        0x9A
#define BME280_REGISTER_DIG_P8        0x9C
#define BME280_REGISTER_DIG_P9        0x9E
#define BME280_REGISTER_DIG_H1        0xA1
#define BME280_REGISTER_DIG_H2        0xE1
#define BME280_REGISTER_DIG_H3        0xE3
#define BME280_REGISTER_DIG_H4_MSB    0xE4
#define BME280_REGISTER_DIG_H4_LSB    0xE5
#define BME280_REGISTER_DIG_H5_MSB    0xE5
#define BME280_REGISTER_DIG_H5_LSB    0xE6
#define BME280_REGISTER_DIG_H6        0xE7

#define BME280_REGISTER_SOFTRESET     0xE0
#define BME280_RESET                  0xB6
#define BME280_REGISTER_CAL26         0xE1
#define BME280_REGISTER_CONTROLHUMID  0xF2
#define BME280_REGISTER_CONTROL       0xF4
#define BME280_REGISTER_CONFIG        0xF5
#define BME280_REGISTER_PRESSUREDATA  0xF7
#define BME280_REGISTER_TEMPDATA      0xFA
#define BME280_REGISTER_HUMIDDATA     0xFD

#define MEAN_SEA_LEVEL_PRESSURE       1013

/**
  * \def uncompensate value register
  * \brief uncompensate value register
  *
  * uncompensate value register
  */
#define BME280_REGISTER_HUM_LSB       0xFE
#define BME280_REGISTER_HUM_MSB       0xFD
#define BME280_REGISTER_TEMP_XSB      0xFC
#define BME280_REGISTER_TEMP_LSB      0xFB
#define BME280_REGISTER_TEMP_MSB      0xFA
#define BME280_REGISTER_PRESS_XSB     0xF9
#define BME280_REGISTER_PRESS_LSB     0xF8
#define BME280_REGISTER_PRESS_MSB     0xF7

#include <qglobal.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <wiringPiI2C.h>
#include <QDebug>

/*
* Immutable calibration data read from bme280
*/
typedef struct
{
  quint16 dig_T1;
  qint16  dig_T2;
  qint16  dig_T3;

  quint16 dig_P1;
  qint16  dig_P2;
  qint16  dig_P3;
  qint16  dig_P4;
  qint16  dig_P5;
  qint16  dig_P6;
  qint16  dig_P7;
  qint16  dig_P8;
  qint16  dig_P9;

  quint8  dig_H1;
  qint16  dig_H2;
  quint8  dig_H3;
  qint16  dig_H4;
  qint16  dig_H5;
  qint8   dig_H6;
  qint32  t_fine;
} sbme280_calib_data, *psbme280_calib_data;

/*
* Raw sensor measurement data from bme280
*/
typedef struct
{
  quint8 pmsb;
  quint8 plsb;
  quint8 pxsb;

  quint8 tmsb;
  quint8 tlsb;
  quint8 txsb;

  quint8 hmsb;
  quint8 hlsb;

  quint32 temperature;
  quint32 pressure;
  quint32 humidity;

}sbme280_uncomp_data, *psbme280_uncomp_data;

/**
* \  sbme280_data
* @brief bme280 sensor which comprises of temperature, pressure and
* humidity data
*
*/
typedef struct
{
    /*! Compensated pressure */
    double pressure;
    /*! Compensated temperature */
    double temperature;
    /*! Compensated humidity */
    double humidity;
}sbme280_data, *psbme280_data;


/**
* \  sbme280_setting
* @brief bme280 sensor settings ure which comprises of mode,
* oversampling and filter settings.
*
*/
typedef struct
{
    quint8 osr_p;           /*! pressure oversampling */
    quint8 osr_t;           /*! temperature oversampling */
    quint8 osr_h;           /*! humidity oversampling */
    quint8 filter;          /*! filter coefficient */
    quint8 power_mode;      /*! Power mode */
    quint8 standby_time;	/*! standby time */
}sbme280_setting, *psbme280_setting;


/*!
* \  sbme280_dev
* @brief bme280 device ure
*
*/
typedef struct
{
    quint8 chip_id;                     /*! Chip Id */
    quint8 dev_id;                      /*! Device Id */
    sbme280_calib_data calib_data;      /*! Trim data */
    sbme280_uncomp_data uncomp_data;    /*! Uncompensated data */
    sbme280_data comp_data ;            /*! Compensated data */
    sbme280_setting settings;           /*! Sensor settings */
}sbme280_dev, *psbme280_dev;


class BME280
{
public:
    BME280();
    BME280(quint8 device_I2C_Adress);

    void init_sbme280_calib_data(psbme280_calib_data pCalib_data);
    void init_sbme280_uncomp_data(psbme280_uncomp_data pUncomp_data);
    void init_sbme280_data(psbme280_data pComp_data);
    void init_sbme280_setting(psbme280_setting pBME280_setting);
    void init_sbme280_device(psbme280_dev pBME280_device);

    quint8 readChipID(int fd);
    quint8 readRegister(quint8 registerValue);
    void readCalibrationData(int fd, sbme280_calib_data *data);
    void readUncompensatedValue(int fd, psbme280_uncomp_data pUncomp_data);
    void writBME280configuration(psbme280_dev pBME280_device);
    void wakeupDevice(psbme280_dev pBME280_device);
    /*!
 * \fn static double compensate_pressure(const  ebme280_uncomp_data *uncomp_data,
 *                                       const  ebme280_calib_data *calib_data);
 * @brief This internal API is used to compensate the raw pressure data and
 * return the compensated pressure data in double data type.
 *
 * @param[in] uncomp_data : Contains the uncompensated pressure data.
 * @param[in] calib_data : Pointer to the calibration data ure.
 *
 * @return Compensated pressure data.
 * @retval Compensated pressure data in double.
 */
    static double compensate_pressure(const sbme280_uncomp_data *uncomp_data,
                                      sbme280_calib_data *calib_data);

    /*!
 * @brief This internal API is used to compensate the raw temperature data and
 * return the compensated temperature data in double data type.
 *
 * @param[in] uncomp_data : Contains the uncompensated temperature data.
 * @param[in] calib_data : Pointer to calibration data ure.
 *
 * @return Compensated temperature data.
 * @retval Compensated temperature data in double.
 */
    static double compensate_temperature(const sbme280_uncomp_data *uncomp_data,
                                         sbme280_calib_data *calib_data);

    /*!
 * \fn static double compensate_humidity(const  ebme280_uncomp_data *uncomp_data,
 *                                         const  ebme280_calib_data *calib_data);
 * @brief This internal API is used to compensate the raw humidity data and
 * return the compensated humidity data in double data type.
 *
 * @param[in] uncomp_data : Contains the uncompensated humidity data.
 * @param[in] calib_data : Pointer to the calibration data ure.
 *
 * @return Compensated humidity data.
 * @retval Compensated humidity data in double.
 */
    static double compensate_humidity(const sbme280_uncomp_data *uncomp_data,
                                      sbme280_calib_data *calib_data);

    float getAltitude(double pressure);


    quint8 getBME280_fd() const;

private:

    quint8 _BME280_i2cAddress;
    quint8 _BME280_fd;

};

#endif // BME280_H
