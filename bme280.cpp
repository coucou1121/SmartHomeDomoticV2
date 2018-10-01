#include "bme280.h"


BME280::BME280(QObject *parent, QObject *bme280, QObject *roomDataPlot):
    QObject(parent),
    _bme280(bme280),
    _roomDataPlot(roomDataPlot),
    _temperaure(-273),
    _humidity(-100),
    _pressure(-1000)
{
    receivedudateValues(this->_temperaure,this->_humidity,this->_pressure);
}

void BME280::receivedudateValues(qreal temperature, qreal humidity, qreal pressure)
{
    this->_temperaure = temperature;
    this->_humidity = humidity;
    this->_pressure = pressure;

    QMetaObject::invokeMethod(this->_bme280, "updateValue",
                              Q_ARG(QVariant, this->_temperaure),
                              Q_ARG(QVariant, this->_humidity),
                              Q_ARG(QVariant, this->_pressure)
                              );
}

void BME280::addValueInroomDataPlot()
{
    int highHumidity = 90;
    int lowHumidity = 40;
    int highPressure = 1050;
    int lowPressure = 950;
    int highTemperature = 0;
    int lowTemperature = 30;

    qreal temperature = qrand() % ((highTemperature + 1) - lowTemperature) + lowTemperature;
    qreal humidity = qrand() % ((highHumidity + 1) - lowHumidity) + lowHumidity;
    qreal pressure = qrand() % ((highPressure + 1) - lowPressure) + lowPressure;

    QMetaObject::invokeMethod(this->_roomDataPlot, "addYValue",
                              Q_ARG(QVariant, temperature),
                              Q_ARG(QVariant, humidity),
                              Q_ARG(QVariant, pressure / 10),
                              Q_ARG(QVariant, 6)
                              );

    QMetaObject::invokeMethod(this->_bme280, "updateValue",
                              Q_ARG(QVariant, temperature),
                              Q_ARG(QVariant, humidity),
                              Q_ARG(QVariant, pressure)
                              );

}
