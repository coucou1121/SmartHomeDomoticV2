#include <BME280/bme280.h>

BME280::BME280()
{

}

BME280::BME280(quint8 device_I2C_Adress):
    _BME280_i2cAddress(device_I2C_Adress),
    _BME280_fd(0)

{
   this->_BME280_fd = wiringPiI2CSetup(this->_BME280_i2cAddress);
   qDebug() << "BME280 addresse founded : " << this->_BME280_fd;
}

void BME280::init_sbme280_calib_data(psbme280_calib_data pCalib_data)
{
    pCalib_data->dig_T1 = 0;
    pCalib_data->dig_T2 = 0;
    pCalib_data->dig_T3 = 0;

    pCalib_data->dig_P1 = 0;
    pCalib_data->dig_P2 = 0;
    pCalib_data->dig_P3 = 0;
    pCalib_data->dig_P4 = 0;
    pCalib_data->dig_P5 = 0;
    pCalib_data->dig_P6 = 0;
    pCalib_data->dig_P7 = 0;
    pCalib_data->dig_P8 = 0;
    pCalib_data->dig_P9 = 0;

    pCalib_data->dig_H1 = 0;
    pCalib_data->dig_H2 = 0;
    pCalib_data->dig_H3 = 0;
    pCalib_data->dig_H4 = 0;
    pCalib_data->dig_H5 = 0;
    pCalib_data->dig_H6 = 0;
}

void BME280::init_sbme280_uncomp_data(psbme280_uncomp_data pUncomp_data)
{
    pUncomp_data->pmsb = 0;
    pUncomp_data->plsb = 0;
    pUncomp_data->pxsb = 0;

    pUncomp_data->tmsb = 0;
    pUncomp_data->tlsb = 0;
    pUncomp_data->txsb = 0;

    pUncomp_data->hmsb = 0;
    pUncomp_data->hlsb = 0;

    pUncomp_data->temperature = 0;
    pUncomp_data->pressure = 0;
    pUncomp_data->humidity = 0;
}

void BME280::init_sbme280_data(psbme280_data pComp_data)
{
    pComp_data->pressure = 0;
    pComp_data->temperature = 0;
    pComp_data->humidity = 0;
}

void BME280::init_sbme280_setting(psbme280_setting pBME280_setting)
{
    pBME280_setting->osr_t = 0;
    pBME280_setting->osr_t = 0;
    pBME280_setting->osr_h = 0;
    pBME280_setting->filter = 0;
    pBME280_setting->power_mode = 0;
    pBME280_setting->standby_time = 0;
}

void BME280::init_sbme280_device(psbme280_dev pBME280_device)
{
    pBME280_device->chip_id = 0;
    pBME280_device->dev_id = 0;
    this->init_sbme280_calib_data(&pBME280_device->calib_data);
    this->init_sbme280_uncomp_data(&pBME280_device->uncomp_data);
    this->init_sbme280_data(&pBME280_device->comp_data);
    this->init_sbme280_setting(&pBME280_device->settings);
}

quint8 BME280::readChipID(int fd)
{
    return (quint8)wiringPiI2CReadReg8(fd, BME280_CHIP_ID_ADDR);
}

quint8 BME280::readRegister(quint8 registerValue)
{
    return (quint8)wiringPiI2CReadReg8(this->_BME280_fd, registerValue);
}

void BME280::readCalibrationData(int fd, sbme280_calib_data *data)
{
    data->dig_T1 = (quint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_T1);
    data->dig_T2 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_T2);
    data->dig_T3 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_T3);

    data->dig_P1 = (quint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P1);
    data->dig_P2 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P2);
    data->dig_P3 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P3);
    data->dig_P4 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P4);
    data->dig_P5 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P5);
    data->dig_P6 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P6);
    data->dig_P7 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P7);
    data->dig_P8 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P8);
    data->dig_P9 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P9);

    data->dig_H1 = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H1);
    data->dig_H2 = (qint16)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_H2);
    data->dig_H3 = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H3);
    data->dig_H4 = (qint16)(wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H4_MSB) << 4) | (wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H4_LSB) & 0xF);
    data->dig_H5 = (qint16)(wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H5_MSB) & 0xF0 << 4) | (wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H5_LSB));
    data->dig_H6 = (qint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H6);

    data->t_fine = 0;
}

void BME280::readUncompensatedValue(int fd, psbme280_uncomp_data pUncomp_data)
{
    /* Variables to store the sensor data */
    quint32 data_xlsb;
    quint32 data_lsb;
    quint32 data_msb;

    /* Store the parsed register values for pressure data */
    pUncomp_data->pxsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_PRESS_XSB);
    pUncomp_data->plsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_PRESS_LSB);
    pUncomp_data->pmsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_PRESS_MSB);

    data_msb = (quint32)pUncomp_data->pmsb << 12;
    data_lsb = (quint32)pUncomp_data->plsb << 4;
    data_xlsb = (quint32)pUncomp_data->pxsb >> 4;
    pUncomp_data->pressure =  data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for temperature data */
    pUncomp_data->txsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_TEMP_XSB);
    pUncomp_data->tlsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_TEMP_LSB);
    pUncomp_data->tmsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_TEMP_MSB);

    data_msb = (quint32)pUncomp_data->tmsb << 12;
    data_lsb = (quint32)pUncomp_data->tlsb << 4;
    data_xlsb = (quint32)pUncomp_data->txsb >> 4;
    pUncomp_data->temperature =  data_msb | data_lsb | data_xlsb;

    /* Store the parsed register values for humidity data */
    pUncomp_data->hlsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_HUM_LSB);
    pUncomp_data->hmsb = (quint8)wiringPiI2CReadReg8(fd, BME280_REGISTER_HUM_MSB);

    data_msb = (quint32)pUncomp_data->hmsb << 8;
    data_lsb = (quint32)pUncomp_data->hlsb;
    pUncomp_data->humidity =  data_msb | data_lsb ;
}

void BME280::writBME280configuration(psbme280_dev pBME280_device)
{
    //temperature  and pressure oversampling and mode
    quint8 ctrl_meas = 0;
    quint8 ctrl_hum = (quint8)wiringPiI2CReadReg8(pBME280_device->dev_id, BME280_CTRL_HUM_ADDR);
    quint8 config = (quint8)wiringPiI2CReadReg8(pBME280_device->dev_id, BME280_CONFIG_ADDR);

    ctrl_meas |= pBME280_device->settings.osr_t << 5;
    ctrl_meas |= pBME280_device->settings.osr_p << 2;
    ctrl_meas |= pBME280_device->settings.power_mode;

    ctrl_hum |= pBME280_device->settings.osr_h;

    config = 0;
    config |= pBME280_device->settings.standby_time << 5;
    config |= pBME280_device->settings.filter << 2;

    wiringPiI2CWriteReg8(pBME280_device->dev_id, BME280_CTRL_HUM_ADDR, ctrl_hum);
    wiringPiI2CWriteReg8(pBME280_device->dev_id, BME280_CTRL_MEAS_ADDR, ctrl_meas);
    wiringPiI2CWriteReg8(pBME280_device->dev_id, BME280_CONFIG_ADDR, config);
}

void BME280::wakeupDevice(psbme280_dev pBME280_device)
{
    quint8 wakeupRegister = 0;

    wakeupRegister |= pBME280_device->settings.osr_t << 5;
    wakeupRegister |= pBME280_device->settings.osr_p << 2;
    wakeupRegister |= BME280_FORCED_MODE;


    wiringPiI2CWriteReg8(this->_BME280_fd, BME280_CTRL_MEAS_ADDR, wakeupRegister);
}


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


float BME280::getAltitude(double pressure)
{
    // Equation taken from BMP180 datasheet (page 16):
    //  http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

    // Note that using the equation from wikipedia can give bad results
    // at high altitude.  See this thread for more information:
    //  http://forums.adafruit.com/viewtopic.php?f=22&t=58064

 //   return 44330.0 * (1.0 - pow(pressure / MEAN_SEA_LEVEL_PRESSURE, 0.190294957));
    return (((pow(pressure*100/101325,(1/5.255))-1)*288.15)/-0.0065);
 //   return (((pow(pressure/101325,(1/5.255))-1)*288.15)/-0.0065);
//    return 44330.0 * (1.0 - pow(pressure / MEAN_SEA_LEVEL_PRESSURE, 0.190294957));
}

quint8 BME280::getBME280_fd() const
{
    return _BME280_fd;
}


