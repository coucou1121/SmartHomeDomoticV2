#include <bme280.h>

/**\name Internal macros */
/* To identify osr settings selected by user */
#define OVERSAMPLING_SETTINGS		UINT8_C(0x07)
/* To identify filter and standby settings selected by user */
#define FILTER_STANDBY_SETTINGS		UINT8_C(0x18)

BME280::BME280()
{

}

BME280::BME280(qint8 device_I2C_Adress):
    _pdev(&_dev),
    _pcalib_data(&_calib_data),
    _psetting(&_setting)
{
    this->_deviceAdresse = wiringPiI2CSetup(device_I2C_Adress);
    qDebug() << "BME280 addresse founded : " << this->_deviceAdresse;
}

qint8 BME280::init_sbme280_dev(BME280::psbme280_dev pdev)
{
    pdev->calib_data = this->_calib_data;
    pdev->chip_id = 0;
    pdev->delay_ms = NULL;
    pdev->intf = BME280_I2C_INTF;
    pdev->read = 0;
    pdev->settings = this->_setting;
    pdev->write = 0;
}

qint8 BME280::put_device_to_sleep(const sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_data[4];
    sbme280_setting settings;

    rslt = bme280_get_regs(BME280_CTRL_HUM_ADDR, reg_data, 4, dev);
    if (rslt == BME280_OK) {
        parse_device_settings(reg_data, &settings);
        rslt = bme280_soft_reset(dev);
        if (rslt == BME280_OK)
            rslt = reload_device_settings(&settings, dev);
    }

    return rslt;
}

qint8 BME280::write_power_mode(quint8 sensor_mode, const sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_addr = BME280_PWR_CTRL_ADDR;
    /* Variable to store the value read from power mode register */
    quint8 sensor_mode_reg_val;

    /* Read the power mode register */
    rslt = bme280_get_regs(reg_addr, &sensor_mode_reg_val, 1, dev);
    /* Set the power mode */
    if (rslt == BME280_OK) {
        sensor_mode_reg_val = BME280_SET_BITS_POS_0(sensor_mode_reg_val, BME280_SENSOR_MODE, sensor_mode);
        /* Write the power mode in the register */
        rslt = bme280_set_regs(&reg_addr, &sensor_mode_reg_val, 1, dev);
    }

    return rslt;
}

qint8 BME280::null_ptr_check(const sbme280_dev *dev)
{
    qint8 rslt;

    if ((dev == NULL) || (dev->read == NULL) || (dev->write == NULL) || (dev->delay_ms == NULL)) {
        /* Device ure pointer is not valid */
        rslt = BME280_E_NULL_PTR;
    } else {
        /* Device ure is fine */
        rslt = BME280_OK;
    }

    return rslt;
}

void BME280::interleave_reg_addr(const quint8 *reg_addr, quint8 *temp_buff, const quint8 *reg_data, quint8 len)
{
    quint8 index;

    for (index = 1; index < len; index++) {
        temp_buff[(index * 2) - 1] = reg_addr[index];
        temp_buff[index * 2] = reg_data[index];
    }
}

qint8 BME280::get_calib_data(sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_addr = BME280_TEMP_PRESS_CALIB_DATA_ADDR;
    /* Array to store calibration data */
    quint8 calib_data[BME280_TEMP_PRESS_CALIB_DATA_LEN] = {0};

    /* Read the calibration data from the sensor */
    rslt = bme280_get_regs(reg_addr, calib_data, BME280_TEMP_PRESS_CALIB_DATA_LEN, dev);

    if (rslt == BME280_OK) {
        /* Parse temperature and pressure calibration data and store
           it in device ure */
        parse_temp_press_calib_data(calib_data, dev);

        reg_addr = BME280_HUMIDITY_CALIB_DATA_ADDR;
        /* Read the humidity calibration data from the sensor */
        rslt = bme280_get_regs(reg_addr, calib_data, BME280_HUMIDITY_CALIB_DATA_LEN, dev);
        if (rslt == BME280_OK) {
            /* Parse humidity calibration data and store it in
               device ure */
            parse_humidity_calib_data(calib_data, dev);
        }
    }

    return rslt;
}

void BME280::parse_temp_press_calib_data(const quint8 *reg_data,  sbme280_dev *dev)
{
     sbme280_calib_data *calib_data = &dev->calib_data;

    calib_data->dig_T1 = BME280_CONCAT_BYTES(reg_data[1], reg_data[0]);
    calib_data->dig_T2 = (int16_t)BME280_CONCAT_BYTES(reg_data[3], reg_data[2]);
    calib_data->dig_T3 = (int16_t)BME280_CONCAT_BYTES(reg_data[5], reg_data[4]);
    calib_data->dig_P1 = BME280_CONCAT_BYTES(reg_data[7], reg_data[6]);
    calib_data->dig_P2 = (int16_t)BME280_CONCAT_BYTES(reg_data[9], reg_data[8]);
    calib_data->dig_P3 = (int16_t)BME280_CONCAT_BYTES(reg_data[11], reg_data[10]);
    calib_data->dig_P4 = (int16_t)BME280_CONCAT_BYTES(reg_data[13], reg_data[12]);
    calib_data->dig_P5 = (int16_t)BME280_CONCAT_BYTES(reg_data[15], reg_data[14]);
    calib_data->dig_P6 = (int16_t)BME280_CONCAT_BYTES(reg_data[17], reg_data[16]);
    calib_data->dig_P7 = (int16_t)BME280_CONCAT_BYTES(reg_data[19], reg_data[18]);
    calib_data->dig_P8 = (int16_t)BME280_CONCAT_BYTES(reg_data[21], reg_data[20]);
    calib_data->dig_P9 = (int16_t)BME280_CONCAT_BYTES(reg_data[23], reg_data[22]);
    calib_data->dig_H1 = reg_data[25];

}

void BME280::parse_humidity_calib_data(const quint8 *reg_data,  sbme280_dev *dev)
{
     sbme280_calib_data *calib_data = &dev->calib_data;
    int16_t dig_H4_lsb;
    int16_t dig_H4_msb;
    int16_t dig_H5_lsb;
    int16_t dig_H5_msb;

    calib_data->dig_H2 = (int16_t)BME280_CONCAT_BYTES(reg_data[1], reg_data[0]);
    calib_data->dig_H3 = reg_data[2];

    dig_H4_msb = (int16_t)(qint8)reg_data[3] * 16;
    dig_H4_lsb = (int16_t)(reg_data[4] & 0x0F);
    calib_data->dig_H4 = dig_H4_msb | dig_H4_lsb;

    dig_H5_msb = (int16_t)(qint8)reg_data[5] * 16;
    dig_H5_lsb = (int16_t)(reg_data[4] >> 4);
    calib_data->dig_H5 = dig_H5_msb | dig_H5_lsb;
    calib_data->dig_H6 = (qint8)reg_data[6];
}

#if BME280_HIGH_ACCURATED_VALUE
double BME280::compensate_pressure(const sbme280_uncomp_data *uncomp_data,
                        sbme280_calib_data *calib_data)
{
    double var1;
    double var2;
    double var3;
    double pressure;
    double pressure_min = 30000.0;
    double pressure_max = 110000.0;

    var1 = ((double)calib_data->t_fine / 2.0) - 64000.0;
    var2 = var1 * var1 * ((double)calib_data->dig_P6) / 32768.0;
    var2 = var2 + var1 * ((double)calib_data->dig_P5) * 2.0;
    var2 = (var2 / 4.0) + (((double)calib_data->dig_P4) * 65536.0);
    var3 = ((double)calib_data->dig_P3) * var1 * var1 / 524288.0;
    var1 = (var3 + ((double)calib_data->dig_P2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double)calib_data->dig_P1);
    /* avoid exception caused by division by zero */
    if (var1) {
        pressure = 1048576.0 - (double) uncomp_data->pressure;
        pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;
        var1 = ((double)calib_data->dig_P9) * pressure * pressure / 2147483648.0;
        var2 = pressure * ((double)calib_data->dig_P8) / 32768.0;
        pressure = pressure + (var1 + var2 + ((double)calib_data->dig_P7)) / 16.0;

        if (pressure < pressure_min)
            pressure = pressure_min;
        else if (pressure > pressure_max)
            pressure = pressure_max;
    } else { /* Invalid case */
        pressure = pressure_min;
    }

    return pressure;
}

double BME280::compensate_temperature(const sbme280_uncomp_data *uncomp_data,
                        sbme280_calib_data *calib_data)
{
    double var1;
    double var2;
    double temperature;
    double temperature_min = -40;
    double temperature_max = 85;

    var1 = ((double)uncomp_data->temperature) / 16384.0 - ((double)calib_data->dig_T1) / 1024.0;
    var1 = var1 * ((double)calib_data->dig_T2);
    var2 = (((double)uncomp_data->temperature) / 131072.0 - ((double)calib_data->dig_T1) / 8192.0);
    var2 = (var2 * var2) * ((double)calib_data->dig_T3);
    calib_data->t_fine = (int32_t)(var1 + var2);
    temperature = (var1 + var2) / 5120.0;

    if (temperature < temperature_min)
        temperature = temperature_min;
    else if (temperature > temperature_max)
        temperature = temperature_max;

    return temperature;
}

double BME280::compensate_humidity(const sbme280_uncomp_data *uncomp_data,
                        sbme280_calib_data *calib_data)
{
    double humidity;
    double humidity_min = 0.0;
    double humidity_max = 100.0;
    double var1;
    double var2;
    double var3;
    double var4;
    double var5;
    double var6;

    var1 = ((double)calib_data->t_fine) - 76800.0;
    var2 = (((double)calib_data->dig_H4) * 64.0 + (((double)calib_data->dig_H5) / 16384.0) * var1);
    var3 = uncomp_data->humidity - var2;
    var4 = ((double)calib_data->dig_H2) / 65536.0;
    var5 = (1.0 + (((double)calib_data->dig_H3) / 67108864.0) * var1);
    var6 = 1.0 + (((double)calib_data->dig_H6) / 67108864.0) * var1 * var5;
    var6 = var3 * var4 * (var5 * var6);
    humidity = var6 * (1.0 - ((double)calib_data->dig_H1) * var6 / 524288.0);

    if (humidity > humidity_max)
        humidity = humidity_max;
    else if (humidity < humidity_min)
        humidity = humidity_min;

    return humidity;
}

#else
quint32 BME280::compensate_pressure(const sbme280_uncomp_data *uncomp_data,
                        sbme280_calib_data *calib_data)
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    quint32 var5;
    quint32 pressure;
    quint32 pressure_min = 30000;
    quint32 pressure_max = 110000;

    var1 = (((int32_t)calib_data->t_fine) / 2) - (int32_t)64000;
    var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t)calib_data->dig_P6);
    var2 = var2 + ((var1 * ((int32_t)calib_data->dig_P5)) * 2);
    var2 = (var2 / 4) + (((int32_t)calib_data->dig_P4) * 65536);
    var3 = (calib_data->dig_P3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8;
    var4 = (((int32_t)calib_data->dig_P2) * var1) / 2;
    var1 = (var3 + var4) / 262144;
    var1 = (((32768 + var1)) * ((int32_t)calib_data->dig_P1)) / 32768;
     /* avoid exception caused by division by zero */
    if (var1) {
        var5 = (quint32)((quint32)1048576) - uncomp_data->pressure;
        pressure = ((quint32)(var5 - (quint32)(var2 / 4096))) * 3125;
        if (pressure < 0x80000000)
            pressure = (pressure << 1) / ((quint32)var1);
        else
            pressure = (pressure / (quint32)var1) * 2;

        var1 = (((int32_t)calib_data->dig_P9) * ((int32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
        var2 = (((int32_t)(pressure / 4)) * ((int32_t)calib_data->dig_P8)) / 8192;
        pressure = (quint32)((int32_t)pressure + ((var1 + var2 + calib_data->dig_P7) / 16));

        if (pressure < pressure_min)
            pressure = pressure_min;
        else if (pressure > pressure_max)
            pressure = pressure_max;
    } else {
        pressure = pressure_min;
    }

    return pressure;
}

int32_t BME280::compensate_temperature(const sbme280_uncomp_data *uncomp_data,
                        sbme280_calib_data *calib_data)
{
    int32_t var1;
    int32_t var2;
    int32_t temperature;
    int32_t temperature_min = -4000;
    int32_t temperature_max = 8500;

    var1 = (int32_t)((uncomp_data->temperature / 8) - ((int32_t)calib_data->dig_T1 * 2));
    var1 = (var1 * ((int32_t)calib_data->dig_T2)) / 2048;
    var2 = (int32_t)((uncomp_data->temperature / 16) - ((int32_t)calib_data->dig_T1));
    var2 = (((var2 * var2) / 4096) * ((int32_t)calib_data->dig_T3)) / 16384;
    calib_data->t_fine = var1 + var2;
    temperature = (calib_data->t_fine * 5 + 128) / 256;

    if (temperature < temperature_min)
        temperature = temperature_min;
    else if (temperature > temperature_max)
        temperature = temperature_max;

    return temperature;
}

quint32 BME280::compensate_humidity(const sbme280_uncomp_data *uncomp_data,
                        sbme280_calib_data *calib_data)
{
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    quint32 humidity;
    quint32 humidity_max = 102400;

    var1 = calib_data->t_fine - ((int32_t)76800);
    var2 = (int32_t)(uncomp_data->humidity * 16384);
    var3 = (int32_t)(((int32_t)calib_data->dig_H4) * 1048576);
    var4 = ((int32_t)calib_data->dig_H5) * var1;
    var5 = (((var2 - var3) - var4) + (int32_t)16384) / 32768;
    var2 = (var1 * ((int32_t)calib_data->dig_H6)) / 1024;
    var3 = (var1 * ((int32_t)calib_data->dig_H3)) / 2048;
    var4 = ((var2 * (var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
    var2 = ((var4 * ((int32_t)calib_data->dig_H2)) + 8192) / 16384;
    var3 = var5 * var2;
    var4 = ((var3 / 32768) * (var3 / 32768)) / 128;
    var5 = var3 - ((var4 * ((int32_t)calib_data->dig_H1)) / 16);
    var5 = (var5 < 0 ? 0 : var5);
    var5 = (var5 > 419430400 ? 419430400 : var5);
    humidity = (quint32)(var5 / 4096);

    if (humidity > humidity_max)
        humidity = humidity_max;

    return humidity;
}
#endif // BME280_HIGH_ACCURATED_VALUE
quint8 BME280::are_settings_changed(quint8 sub_settings, quint8 desired_settings)
{
    quint8 settings_changed = false;

    if (sub_settings & desired_settings) {
        /* User wants to modify this particular settings */
        settings_changed = true;
    } else {
        /* User don't want to modify this particular settings */
        settings_changed = false;
    }

    return settings_changed;
}

qint8 BME280::set_osr_humidity_settings(const sbme280_setting *settings, const sbme280_dev *dev)
{
    qint8 rslt;
    quint8 ctrl_hum;
    quint8 ctrl_meas;
    quint8 reg_addr = BME280_CTRL_HUM_ADDR;

    ctrl_hum = settings->osr_h & BME280_CTRL_HUM_MSK;
    /* Write the humidity control value in the register */
    rslt = bme280_set_regs(&reg_addr, &ctrl_hum, 1, dev);
    /* Humidity related changes will be only effective after a
       write operation to ctrl_meas register */
    if (rslt == BME280_OK) {
        reg_addr = BME280_CTRL_MEAS_ADDR;
        rslt = bme280_get_regs(reg_addr, &ctrl_meas, 1, dev);
        if (rslt == BME280_OK)
            rslt = bme280_set_regs(&reg_addr, &ctrl_meas, 1, dev);
    }

    return rslt;
}

qint8 BME280::set_osr_settings(quint8 desired_settings, const sbme280_setting *settings,
                                const sbme280_dev *dev)
{
    qint8 rslt = BME280_W_INVALID_OSR_MACRO;

    if (desired_settings & BME280_OSR_HUM_SEL)
        rslt = set_osr_humidity_settings(settings, dev);
    if (desired_settings & (BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL))
        rslt = set_osr_press_temp_settings(desired_settings, settings, dev);

    return rslt;
}

qint8 BME280::set_osr_press_temp_settings(quint8 desired_settings, const sbme280_setting *settings,
                                           const sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_addr = BME280_CTRL_MEAS_ADDR;
    quint8 reg_data;

    rslt = bme280_get_regs(reg_addr, &reg_data, 1, dev);

    if (rslt == BME280_OK) {
        if (desired_settings & BME280_OSR_PRESS_SEL)
            fill_osr_press_settings(&reg_data, settings);
        if (desired_settings & BME280_OSR_TEMP_SEL)
            fill_osr_temp_settings(&reg_data, settings);
        /* Write the oversampling settings in the register */
        rslt = bme280_set_regs(&reg_addr, &reg_data, 1, dev);
    }

    return rslt;
}

void BME280::fill_osr_press_settings(quint8 *reg_data, const sbme280_setting *settings)
{
    *reg_data = BME280_SET_BITS(*reg_data, BME280_CTRL_PRESS, settings->osr_p);
}

void BME280::fill_osr_temp_settings(quint8 *reg_data, const sbme280_setting *settings)
{
    *reg_data = BME280_SET_BITS(*reg_data, BME280_CTRL_TEMP, settings->osr_t);
}

qint8 BME280::set_filter_standby_settings(quint8 desired_settings, const sbme280_setting *settings,
                                           const  sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_addr = BME280_CONFIG_ADDR;
    quint8 reg_data;

    rslt = bme280_get_regs(reg_addr, &reg_data, 1, dev);

    if (rslt == BME280_OK) {
        if (desired_settings & BME280_FILTER_SEL)
            fill_filter_settings(&reg_data, settings);
        if (desired_settings & BME280_STANDBY_SEL)
            fill_standby_settings(&reg_data, settings);
        /* Write the oversampling settings in the register */
        rslt = bme280_set_regs(&reg_addr, &reg_data, 1, dev);
    }

    return rslt;
}

void BME280::fill_filter_settings(quint8 *reg_data, const  sbme280_setting *settings)
{
    *reg_data = BME280_SET_BITS(*reg_data, BME280_FILTER, settings->filter);
}

void BME280::fill_standby_settings(quint8 *reg_data, const  sbme280_setting *settings)
{
    *reg_data = BME280_SET_BITS(*reg_data, BME280_STANDBY, settings->standby_time);
}

void BME280::parse_device_settings(const quint8 *reg_data,  sbme280_setting *settings)
{
    settings->osr_h = BME280_GET_BITS_POS_0(reg_data[0], BME280_CTRL_HUM);
    settings->osr_p = BME280_GET_BITS(reg_data[2], BME280_CTRL_PRESS);
    settings->osr_t = BME280_GET_BITS(reg_data[2], BME280_CTRL_TEMP);
    settings->filter = BME280_GET_BITS(reg_data[3], BME280_FILTER);
    settings->standby_time = BME280_GET_BITS(reg_data[3], BME280_STANDBY);
}

qint8 BME280::reload_device_settings(const  sbme280_setting *settings, const  sbme280_dev *dev)
{
    qint8 rslt;

    rslt = set_osr_settings(BME280_ALL_SETTINGS_SEL, settings, dev);
    if (rslt == BME280_OK)
        rslt = set_filter_standby_settings(BME280_ALL_SETTINGS_SEL, settings, dev);

    return rslt;
}

/****************** Global Function Definitions *******************************/

qint8 BME280::bme280_init( sbme280_dev *dev)
{
    qint8 rslt;
    /* chip id read try count */
    quint8 try_count = 5;
    quint8 chip_id = 0;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);
    /* Proceed if null check is fine */
    if (rslt ==  BME280_OK)
    {
        while (try_count)
        {
            /* Read the chip-id of bme280 sensor */
            rslt = bme280_get_regs(BME280_CHIP_ID_ADDR, &chip_id, 1, dev);
            /* Check for chip id validity */
            if ((rslt == BME280_OK) && (chip_id == BME280_CHIP_ID)) {
                dev->chip_id = chip_id;
                /* Reset the sensor */
                rslt = bme280_soft_reset(dev);
                if (rslt == BME280_OK) {
                    /* Read the calibration data */
                    rslt = get_calib_data(dev);
                }
                break;
            }
            /* Wait for 1 ms */
            dev->delay_ms(1);
            --try_count;
        }
        /* Chip id check failed */
        if (!try_count)
            rslt = BME280_E_DEV_NOT_FOUND;
    }

    return rslt;
}

qint8 BME280::bme280_get_regs(quint8 reg_addr, quint8 *reg_data, uint16_t len, const  sbme280_dev *dev)
{
    qint8 rslt;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);
    /* Proceed if null check is fine */
    if (rslt == BME280_OK) {
        /* If interface selected is SPI */
        if (dev->intf != BME280_I2C_INTF)
            reg_addr = reg_addr | 0x80;
        /* Read the data  */
        rslt = dev->read(dev->dev_id, reg_addr, reg_data, len);
        /* Check for communication error */
        if (rslt != BME280_OK)
            rslt = BME280_E_COMM_FAIL;
    }

    return rslt;
}

qint8 BME280::bme280_set_regs(quint8 *reg_addr, const quint8 *reg_data, quint8 len, const  sbme280_dev *dev)
{
    qint8 rslt;
    quint8 temp_buff[20]; /* Typically not to write more than 10 registers */

    if (len > 10)
        len = 10;

    uint16_t temp_len;
    quint8 reg_addr_cnt;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);
    /* Check for arguments validity */
    if ((rslt ==  BME280_OK) && (reg_addr != NULL) && (reg_data != NULL)) {
        if (len != 0) {
            temp_buff[0] = reg_data[0];
            /* If interface selected is SPI */
            if (dev->intf != BME280_I2C_INTF) {
                for (reg_addr_cnt = 0; reg_addr_cnt < len; reg_addr_cnt++)
                    reg_addr[reg_addr_cnt] = reg_addr[reg_addr_cnt] & 0x7F;
            }
            /* Burst write mode */
            if (len > 1) {
                /* Interleave register address w.r.t data for
                burst write*/
                interleave_reg_addr(reg_addr, temp_buff, reg_data, len);
                temp_len = ((len * 2) - 1);
            } else {
                temp_len = len;
            }
            rslt = dev->write(dev->dev_id, reg_addr[0], temp_buff, temp_len);
            /* Check for communication error */
            if (rslt != BME280_OK)
                rslt = BME280_E_COMM_FAIL;
        } else {
            rslt = BME280_E_INVALID_LEN;
        }
    } else {
        rslt = BME280_E_NULL_PTR;
    }


    return rslt;
}

qint8 BME280::bme280_set_sensor_settings(quint8 desired_settings, const  sbme280_dev *dev)
{
    qint8 rslt;
    quint8 sensor_mode;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);
    /* Proceed if null check is fine */
    if (rslt == BME280_OK) {
        rslt = bme280_get_sensor_mode(&sensor_mode, dev);
        if ((rslt == BME280_OK) && (sensor_mode != BME280_SLEEP_MODE))
            rslt = put_device_to_sleep(dev);
        if (rslt == BME280_OK) {
            /* Check if user wants to change oversampling
               settings */
            if (are_settings_changed(OVERSAMPLING_SETTINGS, desired_settings))
                rslt = set_osr_settings(desired_settings, &dev->settings, dev);
            /* Check if user wants to change filter and/or
               standby settings */
            if ((rslt == BME280_OK) && are_settings_changed(FILTER_STANDBY_SETTINGS, desired_settings))
                rslt = set_filter_standby_settings(desired_settings, &dev->settings, dev);
        }
    }

    return rslt;
}

qint8 BME280::bme280_get_sensor_settings(sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_data[4];

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);
    /* Proceed if null check is fine */
    if (rslt == BME280_OK) {
        rslt = bme280_get_regs(BME280_CTRL_HUM_ADDR, reg_data, 4, dev);
        if (rslt == BME280_OK)
            parse_device_settings(reg_data, &dev->settings);
    }

    return rslt;
}

qint8 BME280::bme280_set_sensor_mode(quint8 sensor_mode, const  sbme280_dev *dev)
{
    qint8 rslt;
    quint8 last_set_mode;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);

    if (rslt == BME280_OK) {
        rslt = bme280_get_sensor_mode(&last_set_mode, dev);
        /* If the sensor is not in sleep mode put the device to sleep
           mode */
        if ((rslt == BME280_OK) && (last_set_mode != BME280_SLEEP_MODE))
            rslt = put_device_to_sleep(dev);
        /* Set the power mode */
        if (rslt == BME280_OK)
            rslt = write_power_mode(sensor_mode, dev);
    }

    return rslt;
}

qint8 BME280::bme280_get_sensor_mode(quint8 *sensor_mode, const  sbme280_dev *dev)
{
    qint8 rslt;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);

    if (rslt == BME280_OK) {
        /* Read the power mode register */
        rslt = bme280_get_regs(BME280_PWR_CTRL_ADDR, sensor_mode, 1, dev);
        /* Assign the power mode in the device ure */
        *sensor_mode = BME280_GET_BITS_POS_0(*sensor_mode, BME280_SENSOR_MODE);
    }

    return rslt;
}

qint8 BME280::bme280_soft_reset(const  sbme280_dev *dev)
{
    qint8 rslt;
    quint8 reg_addr = BME280_RESET_ADDR;
    /* 0xB6 is the soft reset command */
    quint8 soft_rst_cmd = 0xB6;

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);
    /* Proceed if null check is fine */
    if (rslt == BME280_OK) {
        /* Write the soft reset command in the sensor */
        rslt = bme280_set_regs(&reg_addr, &soft_rst_cmd, 1, dev);
        /* As per data sheet, startup time is 2 ms. */
        dev->delay_ms(2);
    }

    return rslt;
}

qint8 BME280::bme280_get_sensor_data(quint8 sensor_comp,  sbme280_data *comp_data,  sbme280_dev *dev)
{
    qint8 rslt;
    /* Array to store the pressure, temperature and humidity data read from
    the sensor */
    quint8 reg_data[BME280_P_T_H_DATA_LEN] = {0};
    sbme280_uncomp_data uncomp_data = {0};

    /* Check for null pointer in the device ure*/
    rslt = null_ptr_check(dev);

    if ((rslt == BME280_OK) && (comp_data != NULL)) {
        /* Read the pressure and temperature data from the sensor */
        rslt = bme280_get_regs(ebme280_data_ADDR, reg_data, BME280_P_T_H_DATA_LEN, dev);

        if (rslt == BME280_OK) {
            /* Parse the read data from the sensor */
            bme280_parse_sensor_data(reg_data, &uncomp_data);
            /* Compensate the pressure and/or temperature and/or
               humidity data from the sensor */
            rslt = bme280_compensate_data(sensor_comp, &uncomp_data, comp_data, &dev->calib_data);
        }
    } else {
        rslt = BME280_E_NULL_PTR;
    }

    return rslt;
}

void BME280::bme280_parse_sensor_data(const quint8 *reg_data,  sbme280_uncomp_data *uncomp_data)
{
    /* Variables to store the sensor data */
    quint32 data_xlsb;
    quint32 data_lsb;
    quint32 data_msb;

    /* Store the parsed register values for pressure data */
    data_msb = (quint32)reg_data[0] << 12;
    data_lsb = (quint32)reg_data[1] << 4;
    data_xlsb = (quint32)reg_data[2] >> 4;
    uncomp_data->pressure = data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for temperature data */
    data_msb = (quint32)reg_data[3] << 12;
    data_lsb = (quint32)reg_data[4] << 4;
    data_xlsb = (quint32)reg_data[5] >> 4;
    uncomp_data->temperature = data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for temperature data */
    data_lsb = (quint32)reg_data[6] << 8;
    data_msb = (quint32)reg_data[7];
    uncomp_data->humidity = data_msb | data_lsb;
}

qint8 BME280::bme280_compensate_data(quint8 sensor_comp, const  sbme280_uncomp_data *uncomp_data,
                      sbme280_data *comp_data,  sbme280_calib_data *calib_data)
{
    qint8 rslt = BME280_OK;

    if ((uncomp_data != NULL) && (comp_data != NULL) && (calib_data != NULL)) {
        /* Initialize to zero */
        comp_data->temperature = 0;
        comp_data->pressure = 0;
        comp_data->humidity = 0;
        /* If pressure or temperature component is selected */
        if (sensor_comp & (BME280_PRESS | BME280_TEMP | BME280_HUM)) {
            /* Compensate the temperature data */
            comp_data->temperature = compensate_temperature(uncomp_data, calib_data);
        }
        if (sensor_comp & BME280_PRESS) {
            /* Compensate the pressure data */
            comp_data->pressure = compensate_pressure(uncomp_data, calib_data);
        }
        if (sensor_comp & BME280_HUM) {
            /* Compensate the humidity data */
            comp_data->humidity = compensate_humidity(uncomp_data, calib_data);
        }
    } else {
        rslt = BME280_E_NULL_PTR;
    }

    return rslt;
}
