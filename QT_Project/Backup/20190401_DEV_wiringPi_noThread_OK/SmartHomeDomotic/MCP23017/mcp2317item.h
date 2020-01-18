#ifndef MCP2317ITEM_H
#define MCP2317ITEM_H

#include <QObject>
#include <QDebug>
#include <QDialog>
#include <QStateMachine>

#include <globalestaticvalue.h>
#include <globalenumerate.h>
#include <globalstyle.h>

#include <QTimer>
#include <QThread>
#include <TimerThread.h>

#include <WiringPi/wiringpigardian.h>

#include <MCP23017/mcp23017.h>
#include <mcp23017.h>

class MCP2317item : public QThread
{
    Q_OBJECT

public:
    explicit MCP2317item(quint8 deviceI2CAddress,
                         quint8 pinBase,
                         quint8 fd,
                         QObject *homeViewer = nullptr,
                         QObject *MCP23017Viewer = nullptr,
                         WiringPiGardian *wiringPiGardian = nullptr);

public:
    void setIODIRreg(const int regIODIRvalue);
    int getIODIRreg();

protected:

    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();

private:
    quint8 _deviceI2CAddress;
    quint8 _pinBase;
    quint8 _fd;
    quint16 _IODIRreg;
    MCP23017 *_mcp23017;
    smcp23017_device _smcp23017_device;
    pmcp23017_device _pmcp23017Device;
    smcp23017_IOCON _smcp23017_IOCON;
    pmcp23017_IOCON _pmcp23017_IOCON;
    bool _deviceIsReady;
    bool _onReadingData;
    bool _startToReadOnData;
    bool _ledOn;

    quint16 _sleepingDelay;
    qint64 _timeInMilisecond;
    qint64 _memotimeInMilisecond;

    QObject *_homeViewer;
    QObject *_MCP23017Viewer;

    WiringPiGardian *_wiringPiGardian;

    GlobalEnumerate::E_StateMachine _stateMachine;

    void _initDevice();
    void _insertTextAtHomePage(QString textToInsert);
    void _checkStateOfDevice();
//    void _initRegisterDevice();
    bool _checkRegisterConfiguration();
    void _readDataI2C();

    void _waitDelay(quint64 delayInSeconde);
    void _waitDelayMili(quint64 delayInMiliSeconde);
    void _waitDelayMicro(quint64 delayInMicroSeconde);
    void _goToNextState();

};

#endif // MCP2317ITEM_H
