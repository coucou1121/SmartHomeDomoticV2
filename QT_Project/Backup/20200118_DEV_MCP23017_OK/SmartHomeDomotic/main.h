#ifndef MAIN_H
#define MAIN_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlProperties>
#include <QQuickView>


#include <QtWidgets/QApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtCore/QDir>



#include <QDebug>
#include <QTimer>
#include <QThread>

#include <globalenumerate.h>
#include <globalestaticvalue.h>
#include <globalenumerate.h>
#include <globalstyle.h>
#include <setting.h>
#include <errormanager.h>
#include <customplotitem.h>

#include <TimerThread.h>
#include <BME280/bme280item.h>
#include <ADS1115/ads1115item.h>
#include <MCP23017/mcp2317item.h>

#include <DataManager/datamanager.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>
#include <WiringPi/wiringpigardian.h>

//#include <wiringPiSPI.h>

class Main
{

    static QObject *qobjectHomeViewer;


};

#endif // MAIN_H
