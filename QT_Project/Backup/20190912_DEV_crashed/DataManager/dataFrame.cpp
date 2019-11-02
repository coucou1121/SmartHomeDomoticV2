#include "dataFrame.h"

DataFrame::DataFrame() :
    _BME280_temperature(0),
    _BME280_humidity(0),
    _BME280_pressure(0),
    _ADS115_1_chan0(0),
    _ADS115_1_chan1(0),
    _ADS115_1_chan2(0),
    _ADS115_1_chan3(0),
    _ADS115_2_chan0(0),
    _ADS115_2_chan1(0),
    _ADS115_2_chan2(0),
    _ADS115_2_chan3(0)
{

}

double DataFrame::BME280_temperature() const
{
    return _BME280_temperature;
}

void DataFrame::setBME280_temperature(double BME280_temperature)
{
    _BME280_temperature = BME280_temperature;
}

double DataFrame::BME280_humidity() const
{
    return _BME280_humidity;
}

void DataFrame::setBME280_humidity(double BME280_humidity)
{
    _BME280_humidity = BME280_humidity;
}

double DataFrame::BME280_pressure() const
{
    return _BME280_pressure;
}

void DataFrame::setBME280_pressure(double BME280_pressure)
{
    _BME280_pressure = BME280_pressure;
}

double DataFrame::ADS115_1_chan0() const
{
    return _ADS115_1_chan0;
}

void DataFrame::setADS115_1_chan0(const double &ADS115_1_chan0)
{
    _ADS115_1_chan0 = ADS115_1_chan0;
}

double DataFrame::ADS115_1_chan1() const
{
    return _ADS115_1_chan1;
}

void DataFrame::setADS115_1_chan1(const double &ADS115_1_chan1)
{
    _ADS115_1_chan1 = ADS115_1_chan1;
}

double DataFrame::ADS115_1_chan2() const
{
    return _ADS115_1_chan2;
}

void DataFrame::setADS115_1_chan2(const double &ADS115_1_chan2)
{
    _ADS115_1_chan2 = ADS115_1_chan2;
}

double DataFrame::ADS115_1_chan3() const
{
    return _ADS115_1_chan3;
}

void DataFrame::setADS115_1_chan3(const double &ADS115_1_chan3)
{
    _ADS115_1_chan3 = ADS115_1_chan3;
}

double DataFrame::ADS115_2_chan0() const
{
    return _ADS115_2_chan0;
}

void DataFrame::setADS115_2_chan0(const double &ADS115_2_chan0)
{
    _ADS115_2_chan0 = ADS115_2_chan0;
}

double DataFrame::ADS115_2_chan1() const
{
    return _ADS115_2_chan1;
}

void DataFrame::setADS115_2_chan1(const double &ADS115_2_chan1)
{
    _ADS115_2_chan1 = ADS115_2_chan1;
}

double DataFrame::ADS115_2_chan2() const
{
    return _ADS115_2_chan2;
}

void DataFrame::setADS115_2_chan2(const double &ADS115_2_chan2)
{
    _ADS115_2_chan2 = ADS115_2_chan2;
}

double DataFrame::ADS115_2_chan3() const
{
    return _ADS115_2_chan3;
}

void DataFrame::setADS115_2_chan3(const double &ADS115_2_chan3)
{
    _ADS115_2_chan3 = ADS115_2_chan3;
}

