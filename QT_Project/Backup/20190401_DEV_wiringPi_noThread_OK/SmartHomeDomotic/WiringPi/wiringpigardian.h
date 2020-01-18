#ifndef WIRINGPIGARDIAN_H
#define WIRINGPIGARDIAN_H

#include <QObject>
#include <QDebug>

#include <QDateTime>

#include <QTimer>
#include <QThread>

#include <QMutex>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <MCP23017/mcp23017.h>

class WiringPiGardian
{

public:
    WiringPiGardian();


    void setMCP23017_1Register(quint16 regNumber, quint16 regValue);
    void setMCP23017_2Register(quint16 regNumber, quint16 regValue);
    void setMCP23017_3Register(quint16 regNumber, quint16 regValue);
    void setMCP23017_4Register(quint16 regNumber, quint16 regValue);

    void setMCP23017_1isReady(bool MCP23017_1isReady);

    void setMCP23017_2isReady(bool MCP23017_2isReady);

    void setMCP23017_3isReady(bool MCP23017_3isReady);

    void setMCP23017_4isReady(bool MCP23017_4isReady);

    //protected:

    //    /**
    //      * \fn void run()
    //      * \brief called function when the thread start
    //      * \return void : nothing
    //      */
    //    void run();

    void setMCP23017_1fd(const quint8 &MCP23017_1fd);

    void setMCP23017_2fd(const quint8 &MCP23017_2fd);

    void setMCP23017_3fd(const quint8 &MCP23017_3fd);

    void setMCP23017_4fd(const quint8 &MCP23017_4fd);

private:

    QMutex _mutex;

    bool _MCP23017_1isReady;
    bool _MCP23017_2isReady;
    bool _MCP23017_3isReady;
    bool _MCP23017_4isReady;

    quint8 _MCP23017_1fd;
    quint8 _MCP23017_2fd;
    quint8 _MCP23017_3fd;
    quint8 _MCP23017_4fd;

    quint16 _MCP23017_1_regNumber;
    quint16 _MCP23017_2_regNumber;
    quint16 _MCP23017_3_regNumber;
    quint16 _MCP23017_4_regNumber;

    quint16 _MCP23017_1_regValue;
    quint16 _MCP23017_2_regValue;
    quint16 _MCP23017_3_regValue;
    quint16 _MCP23017_4_regValue;


    bool _i2CnetworkIsFree;

    quint16 _sleepingDelay;
    qint64 _timeInMilisecond;
    qint64 _memotimeInMilisecond;

    void _setMCP23017register(quint8 fd, quint16 regNumber, quint16 regValue);

    void _waitDelay(quint64 delayInSeconde);
    void _waitDelayMili(quint64 delayInMiliSeconde);
    void _waitDelayMicro(quint64 delayInMicroSeconde);

};

#endif // WIRINGPIGARDIAN_H
