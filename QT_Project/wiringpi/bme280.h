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

#include <QtGlobal>
#include <QDebug>
#include <wiringPiI2C.h>

/**
  * \def BME280_64BIT_ENABLE
  * \brief preprocessor symbole for BME280_64BIT_ENABLE
  *
  * This symbole is to select the type of OS 32 or 64bits.
  */
#define BME280_64BIT_ENABLE 1

/**
  * \def BME280_HIGH_ACCURATED_VALUE
  * \brief preprocessor symbole for BME280_HIGH_ACCURATED_VALUE
  *
  * This symbole is to select the returne value.
  * 1 : return a double
  * 0 : return a quint32
  */
#define BME280_HIGH_ACCURATED_VALUE 1

/**
  * \def BME280_I2C_ADDR_xxxx
  * \brief preprocessor symbole for BME280_I2C_ADDR_PRIM
  * \brief preprocessor symbole for BME280_I2C_ADDR_SEC
  *
  * This symbole is the adresse of the device.
  * BME280_I2C_ADDR_SEC is use for my BME_280
  */
#define BME280_I2C_ADDR_PRIM	UINT8_C(0x76)
#define BME280_I2C_ADDR_SEC		UINT8_C(0x77)   //use for my device

/**
  * \def BME280_CHIP_ID
  * \brief preprocessor symbole for BME280_CHIP_ID
  *
  * This symbole is the registre for the chip identifier number.
  * It's possible to read it on the adresse BME280_CHIP_ID_ADDR
  */
#define BME280_CHIP_ID  UINT8_C(0x60)   //96 in decimal

/**
  * \def Different register address
  * \brief preprocessor symbole for different register address
  *
  * different register address.
  */
/**\name Register Address */
#define BME280_CHIP_ID_ADDR					UINT8_C(0xD0)
#define BME280_RESET_ADDR					UINT8_C(0xE0)
#define BME280_TEMP_PRESS_CALIB_DATA_ADDR	UINT8_C(0x88)
#define BME280_HUMIDITY_CALIB_DATA_ADDR		UINT8_C(0xE1)
#define BME280_PWR_CTRL_ADDR				UINT8_C(0xF4)
#define BME280_CTRL_HUM_ADDR				UINT8_C(0xF2)
#define BME280_CTRL_MEAS_ADDR				UINT8_C(0xF4)
#define BME280_CONFIG_ADDR					UINT8_C(0xF5)
#define ebme280_data_ADDR					UINT8_C(0xF7)

/**
  * \def BME280_OK
  * \brief preprocessor symbole for BME280_OK
  *
  * API success code.
  */
#define BME280_OK					INT8_C(0)

/**
  * \def BME280_E_xxxx
  * \brief preprocessor symbole for BME280_E_xxxx
  *
  * API error codes.
  */
#define BME280_E_NULL_PTR			INT8_C(-1)
#define BME280_E_DEV_NOT_FOUND		INT8_C(-2)
#define BME280_E_INVALID_LEN		INT8_C(-3)
#define BME280_E_COMM_FAIL			INT8_C(-4)
#define BME280_E_SLEEP_MODE_FAIL	INT8_C(-5)

/**
  * \def BME280_W_INVALID_OSR_MACRO
  * \brief preprocessor symbole for BME280_W_INVALID_OSR_MACRO
  *
  * API warning codes.
  */
#define BME280_W_INVALID_OSR_MACRO      INT8_C(1)

/**
  * \def Macros related to size
  * \brief preprocessor symbole for Macros related to size
  *
  * Macros related to size.
  */
#define BME280_TEMP_PRESS_CALIB_DATA_LEN	UINT8_C(26)
#define BME280_HUMIDITY_CALIB_DATA_LEN		UINT8_C(7)
#define BME280_P_T_H_DATA_LEN				UINT8_C(8)

/**
  * \def BME280_xxxx_MODE
  * \brief preprocessor symbole for BME280_xxxx_MODE
  *
  * Sensor power modes.
  */

#define	BME280_SLEEP_MODE		UINT8_C(0x00)
#define	BME280_FORCED_MODE		UINT8_C(0x01)
#define	BME280_NORMAL_MODE		UINT8_C(0x03)

/**
  * \def Macro to combine two 8 bit data's to form a 16 bit data
  * \brief preprocessor symbole for Macro to combine two 8 bit data's to form a 16 bit data
  *
  * Macro to combine two 8 bit data's to form a 16 bit data.
  */
#define BME280_CONCAT_BYTES(msb, lsb)     (((quint16)msb << 8) | (quint16)lsb)

#define BME280_SET_BITS(reg_data, bitname, data) \
    ((reg_data & ~(bitname##_MSK)) | \
    ((data << bitname##_POS) & bitname##_MSK))
#define BME280_SET_BITS_POS_0(reg_data, bitname, data) \
    ((reg_data & ~(bitname##_MSK)) | \
    (data & bitname##_MSK))

#define BME280_GET_BITS(reg_data, bitname)  ((reg_data & (bitname##_MSK)) >> \
    (bitname##_POS))
#define BME280_GET_BITS_POS_0(reg_data, bitname)  (reg_data & (bitname##_MSK))

/**
  * \def Macros for bit masking
  * \brief preprocessor symbole for Macros for bit masking
  *
  * Macros for bit masking.
  */
#define BME280_SENSOR_MODE_MSK	UINT8_C(0x03)
#define BME280_SENSOR_MODE_POS	UINT8_C(0x00)

#define BME280_CTRL_HUM_MSK		UINT8_C(0x07)
#define BME280_CTRL_HUM_POS		UINT8_C(0x00)

#define BME280_CTRL_PRESS_MSK	UINT8_C(0x1C)
#define BME280_CTRL_PRESS_POS	UINT8_C(0x02)

#define BME280_CTRL_TEMP_MSK	UINT8_C(0xE0)
#define BME280_CTRL_TEMP_POS	UINT8_C(0x05)

#define BME280_FILTER_MSK		UINT8_C(0x1C)
#define BME280_FILTER_POS		UINT8_C(0x02)

#define BME280_STANDBY_MSK		UINT8_C(0xE0)
#define BME280_STANDBY_POS		UINT8_C(0x05)

/**
  * \def Sensor component selection macros
  * \brief preprocessor symbole for Sensor component selection macros
  *
  * These values are internal for API implementation. Don't relate this to data sheet
  */
#define BME280_PRESS		UINT8_C(1)
#define BME280_TEMP			UINT8_C(1 << 1)
#define BME280_HUM			UINT8_C(1 << 2)
#define BME280_ALL			UINT8_C(0x07)

/**
  * \def Settings selection macros
  * \brief preprocessor symbole for Settings selection macros
  *
  * Settings selection macros
  */
#define BME280_OSR_PRESS_SEL		UINT8_C(1)
#define BME280_OSR_TEMP_SEL			UINT8_C(1 << 1)
#define BME280_OSR_HUM_SEL			UINT8_C(1 << 2)
#define BME280_FILTER_SEL			UINT8_C(1 << 3)
#define BME280_STANDBY_SEL			UINT8_C(1 << 4)
#define BME280_ALL_SETTINGS_SEL		UINT8_C(0x1F)

/**
  * \def Oversampling macros
  * \brief preprocessor symbole for Oversampling macros
  *
  * Oversampling macros
  */
#define BME280_NO_OVERSAMPLING		UINT8_C(0x00)
#define BME280_OVERSAMPLING_1X		UINT8_C(0x01)
#define BME280_OVERSAMPLING_2X		UINT8_C(0x02)
#define BME280_OVERSAMPLING_4X		UINT8_C(0x03)
#define BME280_OVERSAMPLING_8X		UINT8_C(0x04)
#define BME280_OVERSAMPLING_16X		UINT8_C(0x05)

/**
  * \def Standby duration selection macros
  * \brief Standby duration selection macros
  *
  * Standby duration selection macros
  */
#define BME280_STANDBY_TIME_1_MS              (0x00)
#define BME280_STANDBY_TIME_62_5_MS           (0x01)
#define BME280_STANDBY_TIME_125_MS			  (0x02)
#define BME280_STANDBY_TIME_250_MS            (0x03)
#define BME280_STANDBY_TIME_500_MS            (0x04)
#define BME280_STANDBY_TIME_1000_MS           (0x05)
#define BME280_STANDBY_TIME_10_MS             (0x06)
#define BME280_STANDBY_TIME_20_MS             (0x07)

/**
  * \def Filter coefficient selection macros
  * \brief Filter coefficient selection macros
  *
  * Filter coefficient selection macros
  */
#define BME280_FILTER_COEFF_OFF               (0x00)
#define BME280_FILTER_COEFF_2                 (0x01)
#define BME280_FILTER_COEFF_4                 (0x02)
#define BME280_FILTER_COEFF_8                 (0x03)
#define BME280_FILTER_COEFF_16                (0x04)

class BME280
{

public:
    BME280();
    BME280(qint8 device_I2C_Adress);

    /*!
 * @brief Interface selection Enums
 */
    typedef enum
    {
        BME280_SPI_INTF,    /*! SPI interface */
        BME280_I2C_INTF     /*! I2C interface */
    }ebme280_intf;

    /*!
 * @brief Type definitions
 */
    typedef qint8 (*bme280_com_fptr_t)(quint8 dev_id, quint8 reg_addr,
                                       quint8 *data, quint16 len);

    typedef void (*bme280_delay_fptr_t)(quint32 period);

    /**
  * \  sbme280_calib_data
  * \brief Trim Variables
  *
  * Compensation parameter storage
  */
    typedef struct
    {
        quint16 dig_T1;
        qint16 dig_T2;
        qint16 dig_T3;
        quint16 dig_P1;
        qint16 dig_P2;
        qint16 dig_P3;
        qint16 dig_P4;
        qint16 dig_P5;
        qint16 dig_P6;
        qint16 dig_P7;
        qint16 dig_P8;
        qint16 dig_P9;
        quint8  dig_H1;
        qint16 dig_H2;
        quint8  dig_H3;
        qint16 dig_H4;
        qint16 dig_H5;
        qint8  dig_H6;
        qint32 t_fine;
    }sbme280_calib_data, *psbme280_calib_data;

    /**
  * \  sbme280_data
  * @brief bme280 sensor ure which comprises of temperature, pressure and
  * humidity data
  *
  */
#ifdef BME280_HIGH_ACCURATED_VALUE
    typedef struct
    {
        /*! Compensated pressure */
        double pressure;
        /*! Compensated temperature */
        double temperature;
        /*! Compensated humidity */
        double humidity;
    }sbme280_data, *psbme280_data;
#else
    typedef struct
    {
        /*! Compensated pressure */
        quint32 pressure;
        /*! Compensated temperature */
        qint32 temperature;
        /*! Compensated humidity */
        quint32 humidity;
    }sbme280_data, *psbme280_data;
#endif /* BME280_USE_FLOATING_POINT */

    /**
  * \  bme280_uncomp_data
  * @brief bme280 sensor ure which comprises of uncompensated temperature,
  * pressure and humidity data
  *
  */
    typedef struct
    {
        quint32 pressure;       /*! un-compensated pressure */
        quint32 temperature;    /*! un-compensated temperature */
        quint32 humidity;       /*! un-compensated humidity */
    }sbme280_uncomp_data, *psbme280_uncomp_data;

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
        ebme280_intf intf;                  /*! SPI/I2C interface */
        bme280_com_fptr_t read;            	/*! Read function pointer */
        bme280_com_fptr_t write;           	/*! Write function pointer */
        bme280_delay_fptr_t delay_ms;      	/*! Delay function pointer */
        sbme280_calib_data calib_data;      /*! Trim data */
        sbme280_setting settings;           /*! Sensor settings */
    }sbme280_dev, *psbme280_dev;

    /*!
     * \fn qint8 init_sbme280_dev(psbme280_dev dev);
     * @brief This is for set all value to a knowwing value in the structure sbme280_dev.
     *
     * @param[in] dev : ure instance of sbme280_dev.
     *
     * @return Result of API execution status.
     * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
     */
     qint8 init_sbme280_dev(psbme280_dev dev);

    /*!
 * \fn static qint8 put_device_to_sleep(const  sbme280_dev *dev);
 * @brief This internal API puts the device to sleep mode.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status.
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 put_device_to_sleep(const sbme280_dev *dev);

    /*!
 * \fn static qint8 write_power_mode(quint8 sensor_mode, const  sbme280_dev *dev);
 * @brief This internal API writes the power mode in the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[in] sensor_mode : Variable which contains the power mode to be set.
 *
 * @return Result of API execution status.
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 write_power_mode(quint8 sensor_mode, const sbme280_dev *dev);

    /*!
 * \fn static qint8 null_ptr_check(const  sbme280_dev *dev);
 * @brief This internal API is used to validate the device pointer for
 * null conditions.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 null_ptr_check(const sbme280_dev *dev);

    /*!
 * \fn static void interleave_reg_addr(const quint8 *reg_addr, quint8 *temp_buff, const quint8 *reg_data, quint8 len);
 * @brief This internal API interleaves the register address between the
 * register data buffer for burst write operation.
 *
 * @param[in] reg_addr : Contains the register address array.
 * @param[out] temp_buff : Contains the temporary buffer to store the
 * register data and register address.
 * @param[in] reg_data : Contains the register data to be written in the
 * temporary buffer.
 * @param[in] len : No of bytes of data to be written for burst write.
 */
    static void interleave_reg_addr(const quint8 *reg_addr, quint8 *temp_buff, const quint8 *reg_data, quint8 len);

    /*!
 * \fn static qint8 get_calib_data( sbme280_dev *dev);
 * @brief This internal API reads the calibration data from the sensor, parse
 * it and store in the device ure.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 get_calib_data(sbme280_dev *dev);

    /*!
 * \fn static void parse_temp_press_calib_data(const quint8 *reg_data,  sbme280_dev *dev);
 *  @brief This internal API is used to parse the temperature and
 *  pressure calibration data and store it in the device ure.
 *
 *  @param[out] dev : ure instance of sbme280_dev to store the calib data.
 *  @param[in] reg_data : Contains the calibration data to be parsed.
 */
    static void parse_temp_press_calib_data(const quint8 *reg_data, sbme280_dev *dev);

    /*!
 * \fn static void parse_humidity_calib_data(const quint8 *reg_data,  sbme280_dev *dev);
 *  @brief This internal API is used to parse the humidity calibration data
 *  and store it in device ure.
 *
 *  @param[out] dev : ure instance of sbme280_dev to store the calib data.
 *  @param[in] reg_data : Contains calibration data to be parsed.
 */
    static void parse_humidity_calib_data(const quint8 *reg_data, sbme280_dev *dev);

#if BME280_HIGH_ACCURATED_VALUE
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
#else
    /*!
 * \fn static quint32 compensate_pressure(const  ebme280_uncomp_data *uncomp_data,
 *                                         const  ebme280_calib_data *calib_data);
 * @brief This internal API is used to compensate the raw pressure data and
 * return the compensated pressure data in integer data type.
 *
 * @param[in] uncomp_data : Contains the uncompensated pressure data.
 * @param[in] calib_data : Pointer to the calibration data ure.
 *
 * @return Compensated pressure data.
 * @retval Compensated pressure data in integer.
 */
    static quint32 compensate_pressure(const sbme280_uncomp_data *uncomp_data,
                                       const sbme280_calib_data *calib_data);

    /*!
 * @brief This internal API is used to compensate the raw temperature data and
 * return the compensated temperature data in integer data type.
 *
 * @param[in] uncomp_data : Contains the uncompensated temperature data.
 * @param[in] calib_data : Pointer to calibration data ure.
 *
 * @return Compensated temperature data.
 * @retval Compensated temperature data in integer.
 */
    static qint32 compensate_temperature(const sbme280_uncomp_data *uncomp_data,
                                         sbme280_calib_data *calib_data);

    /*!
 * \fn static quint32 compensate_humidity(const  ebme280_uncomp_data *uncomp_data,
 *                                         const  ebme280_calib_data *calib_data);
 * @brief This internal API is used to compensate the raw humidity data and
 * return the compensated humidity data in integer data type.
 *
 * @param[in] uncomp_data : Contains the uncompensated humidity data.
 * @param[in] calib_data : Pointer to the calibration data ure.
 *
 * @return Compensated humidity data.
 * @retval Compensated humidity data in integer.
 */
    static quint32 compensate_humidity(const ebme280_uncomp_data *uncomp_data,
                                       const ebme280_calib_data *calib_data);
#endif // BME280_HIGH_ACCURATED_VALUE

    /****************** Global Function Definitions *******************************/

    /*!
 * \fn static qint8 bme280_init( sbme280_dev *dev);
 *  @brief This API is the entry point.
 *  It reads the chip-id and calibration data from the sensor.
 *
 *  @param[in,out] dev : ure instance of sbme280_dev
 *
 *  @return Result of API execution status
 *  @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 bme280_init(sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_get_regs(quint8 reg_addr, quint8 *reg_data, quint16 len, const  sbme280_dev *dev);
 * @brief This API reads the data from the given register address of the sensor.
 *
 * @param[in] reg_addr : Register address from where the data to be read
 * @param[out] reg_data : Pointer to data buffer to store the read data.
 * @param[in] len : No of bytes of data to be read.
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 bme280_get_regs(quint8 reg_addr, quint8 *reg_data, quint16 len, const sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_set_regs(quint8 *reg_addr, const quint8 *reg_data, quint8 len, const  sbme280_dev *dev);
 * @brief This API writes the given data to the register address
 * of the sensor.
 *
 * @param[in] reg_addr : Register address from where the data to be written.
 * @param[in] reg_data : Pointer to data buffer which is to be written
 * in the sensor.
 * @param[in] len : No of bytes of data to write..
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 bme280_set_regs(quint8 *reg_addr, const quint8 *reg_data, quint8 len, const sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_set_sensor_settings(quint8 desired_settings, const  sbme280_dev *dev);
 * @brief This API sets the oversampling, filter and standby duration
 * (normal mode) settings in the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[in] desired_settings : Variable used to select the settings which
 * are to be set in the sensor.
 *
 * @note : Below are the macros to be used by the user for selecting the
 * desired settings. User can do OR operation of these macros for configuring
 * multiple settings.
 *
 * Macros		  |   Functionality
 * -----------------------|----------------------------------------------
 * BME280_OSR_PRESS_SEL    |   To set pressure oversampling.
 * BME280_OSR_TEMP_SEL     |   To set temperature oversampling.
 * BME280_OSR_HUM_SEL    |   To set humidity oversampling.
 * BME280_FILTER_SEL     |   To set filter setting.
 * BME280_STANDBY_SEL  |   To set standby duration setting.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
    static qint8 bme280_set_sensor_settings(quint8 desired_settings, const sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_get_sensor_settings( sbme280_dev *dev);
 * @brief This API gets the oversampling, filter and standby duration
 * (normal mode) settings from the sensor.
 *
 * @param[in,out] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
    static qint8 bme280_get_sensor_settings(sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_set_sensor_mode(quint8 sensor_mode, const  sbme280_dev *dev);
 * @brief This API sets the power mode of the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[in] sensor_mode : Variable which contains the power mode to be set.
 *
 *    sensor_mode           |   Macros
 * ---------------------|-------------------
 *     0                | BME280_SLEEP_MODE
 *     1                | BME280_FORCED_MODE
 *     3                | BME280_NORMAL_MODE
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 bme280_set_sensor_mode(quint8 sensor_mode,
                                        const sbme280_dev *dev);
    /*!
 * \fn static qint8 bme280_get_sensor_mode(quint8 *sensor_mode, const  sbme280_dev *dev);
 * @brief This API gets the power mode of the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[out] sensor_mode : Pointer variable to store the power mode.
 *
 *   sensor_mode            |   Macros
 * ---------------------|-------------------
 *     0                | BME280_SLEEP_MODE
 *     1                | BME280_FORCED_MODE
 *     3                | BME280_NORMAL_MODE
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 bme280_get_sensor_mode(quint8 *sensor_mode, const sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_soft_reset(const  sbme280_dev *dev);
 * @brief This API performs the soft reset of the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
    static qint8 bme280_soft_reset(const sbme280_dev *dev);

    /*!
 * \fn static qint8 bme280_get_sensor_data(quint8 sensor_comp,  ebme280_data *comp_data,  sbme280_dev *dev);
 * @brief This API reads the pressure, temperature and humidity data from the
 * sensor, compensates the data and store it in the ebme280_data ure
 * instance passed by the user.
 *
 * @param[in] sensor_comp : Variable which selects which data to be read from
 * the sensor.
 *
 * sensor_comp |   Macros
 * ------------|-------------------
 *     1       | BME280_PRESS
 *     2       | BME280_TEMP
 *     4       | BME280_HUM
 *     7       | BME280_ALL
 *
 * @param[out] comp_data : ure instance of ebme280_data.
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 bme280_get_sensor_data(quint8 sensor_comp,  sbme280_data *comp_data, sbme280_dev *dev);

    /*!
 * \fn static void bme280_parse_sensor_data(const quint8 *reg_data,  ebme280_uncomp_data *uncomp_data);
 *  @brief This API is used to parse the pressure, temperature and
 *  humidity data and store it in the ebme280_uncomp_data ure instance.
 *
 *  @param[in] reg_data     : Contains register data which needs to be parsed
 *  @param[out] uncomp_data : Contains the uncompensated pressure, temperature
 *  and humidity data.
 */
    static void bme280_parse_sensor_data(const quint8 *reg_data,  sbme280_uncomp_data *uncomp_data);

    /*!
 * \fn static qint8 bme280_compensate_data(quint8 sensor_comp, const  ebme280_uncomp_data *uncomp_data,
 *                                    ebme280_data *comp_data,  ebme280_calib_data *calib_data);
 * @brief This API is used to compensate the pressure and/or
 * temperature and/or humidity data according to the component selected by the
 * user.
 *
 * @param[in] sensor_comp : Used to select pressure and/or temperature and/or
 * humidity.
 * @param[in] uncomp_data : Contains the uncompensated pressure, temperature and
 * humidity data.
 * @param[out] comp_data : Contains the compensated pressure and/or temperature
 * and/or humidity data.
 * @param[in] calib_data : Pointer to the calibration data ure.
 *
 * @return Result of API execution status.
 * @retval zero -> Success / -ve value -> Error
 */
    static qint8 bme280_compensate_data(quint8 sensor_comp, const  sbme280_uncomp_data *uncomp_data,
                                        sbme280_data *comp_data,  sbme280_calib_data *calib_data);

private:

    quint8 _deviceAdresse;

    sbme280_dev _dev;
    psbme280_dev _pdev;

    sbme280_calib_data _calib_data;
    psbme280_calib_data _pcalib_data;

    sbme280_setting _setting;
    psbme280_setting _psetting;

    /*!
 * \fn static quint8 are_settings_changed(quint8 sub_settings, quint8 desired_settings);
 * @brief This internal API is used to identify the settings which the user
 * wants to modify in the sensor.
 *
 * @param[in] sub_settings : Contains the settings subset to identify particular
 * group of settings which the user is interested to change.
 * @param[in] desired_settings : Contains the user specified settings.
 *
 * @return Indicates whether user is interested to modify the settings which
 * are related to sub_settings.
 * @retval True -> User wants to modify this group of settings
 * @retval False -> User does not want to modify this group of settings
 */
    static quint8 are_settings_changed(quint8 sub_settings, quint8 desired_settings);

    /*!
 * \fn static qint8 set_osr_humidity_settings(const  sbme280_setting *settings, const  sbme280_dev *dev);
 * @brief This API sets the humidity oversampling settings of the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 set_osr_humidity_settings(const sbme280_setting *settings, const  sbme280_dev *dev);

    /*!
 *\fn static qint8 set_osr_settings(quint8 desired_settings, const  sbme280_setting *settings,
 *                                   const  sbme280_dev *dev);
 * @brief This internal API sets the oversampling settings for pressure,
 * temperature and humidity in the sensor.
 *
 * @param[in] desired_settings : Variable used to select the settings which
 * are to be set.
 * @param[in] dev : ure instance of sbme280_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 set_osr_settings(quint8 desired_settings, const sbme280_setting *settings,
                                  const  sbme280_dev *dev);

    /*!
 * \fn static qint8 set_osr_press_temp_settings(quint8 desired_settings, const  sbme280_setting *settings,
 *                                               const  sbme280_dev *dev);
 * @brief This API sets the pressure and/or temperature oversampling settings
 * in the sensor according to the settings selected by the user.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[in] desired_settings: variable to select the pressure and/or
 * temperature oversampling settings.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 set_osr_press_temp_settings(quint8 desired_settings, const  sbme280_setting *settings,
                                             const  sbme280_dev *dev);
    /*!
 * \fn static void fill_osr_press_settings(quint8 *reg_data, const  sbme280_setting *settings);
 * @brief This internal API fills the pressure oversampling settings provided by
 * the user in the data buffer so as to write in the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[out] reg_data : Variable which is filled according to the pressure
 * oversampling data provided by the user.
 */
    static void fill_osr_press_settings(quint8 *reg_data, const  sbme280_setting *settings);

    /*!
 * \fn static void fill_osr_temp_settings(quint8 *reg_data, const  sbme280_setting *settings);
 * @brief This internal API fills the temperature oversampling settings provided
 * by the user in the data buffer so as to write in the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[out] reg_data : Variable which is filled according to the temperature
 * oversampling data provided by the user.
 */
    static void fill_osr_temp_settings(quint8 *reg_data, const  sbme280_setting *settings);

    /*!
 * \fn static qint8 set_filter_standby_settings(quint8 desired_settings, const  sbme280_setting *settings,
 *                                               const  sbme280_dev *dev);
 * @brief This internal API sets the filter and/or standby duration settings
 * in the sensor according to the settings selected by the user.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[in] desired_settings : variable to select the filter and/or
 * standby duration settings.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 set_filter_standby_settings(quint8 desired_settings, const  sbme280_setting *settings,
                                             const  sbme280_dev *dev);
    /*!
 * \fn static void fill_filter_settings(quint8 *reg_data, const  sbme280_setting *settings);
 * @brief This internal API fills the filter settings provided by the user
 * in the data buffer so as to write in the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[out] reg_data : Variable which is filled according to the filter
 * settings data provided by the user.
 */
    static void fill_filter_settings(quint8 *reg_data, const sbme280_setting *settings);

    /*!
 *\fn static void fill_standby_settings(quint8 *reg_data, const  sbme280_setting *settings);
 * @brief This internal API fills the standby duration settings provided by the
 * user in the data buffer so as to write in the sensor.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[out] reg_data : Variable which is filled according to the standby
 * settings data provided by the user.
 */
    static void fill_standby_settings(quint8 *reg_data, const sbme280_setting *settings);

    /*!
 * \fn static void parse_device_settings(const quint8 *reg_data,  sbme280_setting *settings);
 * @brief This internal API parse the oversampling(pressure, temperature
 * and humidity), filter and standby duration settings and store in the
 * device ure.
 *
 * @param[out] dev : ure instance of sbme280_dev.
 * @param[in] reg_data : Register data to be parsed.
 */
    static void parse_device_settings(const quint8 *reg_data,  sbme280_setting *settings);

    /*!
 * \fn static qint8 reload_device_settings(const  sbme280_setting *settings, const  sbme280_dev *dev);
 * @brief This internal API reloads the already existing device settings in the
 * sensor after soft reset.
 *
 * @param[in] dev : ure instance of sbme280_dev.
 * @param[in] settings : Pointer variable which contains the settings to
 * be set in the sensor.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
    static qint8 reload_device_settings(const sbme280_setting *settings, const  sbme280_dev *dev);

};
#endif // BME280_H
