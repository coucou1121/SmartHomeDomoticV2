QT += quick
QT += quickcontrols2
QT += widgets

QT += network

QT += printsupport

CONFIG += qtquickcompiler

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    globalEnumatedAndExtern.cpp \
    setting.cpp \
    globalenumerate.cpp \
    tank.cpp \
    globalestaticvalue.cpp \
    errormanager.cpp \
    errormessage.cpp \
    customplotitem.cpp \
    qcustomplot.cpp \
    globalstyle.cpp \
    TimerThread.cpp \
    BME280/bme280.cpp \
    BME280/bme280item.cpp \
    ADS1115/ads1115.cpp \
    ADS1115/ads1115item.cpp \
    DataManager/dataFrame.cpp \
    DataManager/datamanager.cpp \
    DataManager/dataanalyser.cpp \
    MCP23017/mcp23017.cpp \
    MCP23017/mcp2317item.cpp \

RESOURCES += qml.qrc \
    pictures.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    main.h \
    globalEnumatedAndExtern.h \
    setting.h \
    globalenumerate.h \
    tank.h \
    globalestaticvalue.h \
    errormanager.h \
    errormessage.h \
    customplotitem.h \
    qcustomplot.h \
    globalstyle.h \
    TimerThread.h \
    BME280/bme280.h \
    BME280/bme280item.h \
    ADS1115/ads1115.h \
    ADS1115/ads1115item.h \
    DataManager/dataFrame.h \
    DataManager/datamanager.h \
    DataManager/dataanalyser.h \
    MCP23017/mcp23017.h \
    MCP23017/mcp2317item.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
