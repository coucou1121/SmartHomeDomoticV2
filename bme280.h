#ifndef BME280_H
#define BME280_H

#include <QObject>
#include <QDebug>

#include <QDialog>

class BME280 : public QObject
{
    Q_OBJECT

public:
    explicit BME280(QObject *parent = nullptr, QObject *bme280 = nullptr, QObject *roomDataPlot = nullptr);

public slots:
    void receivedudateValues(qreal temperature, qreal humidity, qreal pressure);
    void addValueInroomDataPlot();

private:
    QObject *_bme280;
    QObject *_roomDataPlot;
    qreal _temperaure;
    qreal _humidity;
    qreal _pressure;


};

#endif // BME280_H
