#include "wiringpigardian.h"

WiringPiGardian::WiringPiGardian():
    _i2CnetworkIsFree(false),
    _MCP23017_1isReady(false),
    _MCP23017_2isReady(false),
    _MCP23017_3isReady(false),
    _MCP23017_4isReady(false),
    _MCP23017_1fd(0),
    _MCP23017_2fd(0),
    _MCP23017_3fd(0),
    _MCP23017_4fd(0),
    _MCP23017_1_regNumber(0),
    _MCP23017_2_regNumber(0),
    _MCP23017_3_regNumber(0),
    _MCP23017_4_regNumber(0),
    _MCP23017_1_regValue(0),
    _MCP23017_2_regValue(0),
    _MCP23017_3_regValue(0),
    _MCP23017_4_regValue(0),
    _sleepingDelay(500),
    _timeInMilisecond(0),
    _memotimeInMilisecond(0)
{
    // this->_mutex.lock();
    // moveToThread(this);
}

void WiringPiGardian::run()
{
    qint64 sleepingDelay = 0;

//    static bool ledON = false;

    while(true)
    {
        this->_memotimeInMilisecond = QDateTime::currentMSecsSinceEpoch();

        while(!this->_MCP23017_1isReady && !this->_MCP23017_2isReady && !this->_MCP23017_3isReady && !this->_MCP23017_4isReady)
        {
            qDebug() << Q_FUNC_INFO << "wait all MCP23017 device are ready";
            this->_waitDelay(1);
        }

        qDebug() << Q_FUNC_INFO << "All MCP23017 device are ready";
        //        this->_checkStateOfDevice();

//        if(this->_MCP23017_1setRegister)
//        {
//        this->_setMCP23017register(20, this->_MCP23017_1_regNumber, this->_MCP23017_1_regValue);
//            this->_MCP23017_1setRegister = false;
//        }

//        if(this->_MCP23017_2setRegister)
//        {
//        this->_setMCP23017register(22, this->_MCP23017_2_regNumber, this->_MCP23017_2_regValue);
//            this->_MCP23017_2setRegister = false;
//        }

//        if(this->_MCP23017_3setRegister)
//        {
//        this->_setMCP23017register(24, this->_MCP23017_2_regNumber, this->_MCP23017_3_regValue);
//            this->_MCP23017_3setRegister = false;
//        }

//        if(this->_MCP23017_4setRegister)
//        {
//        this->_setMCP23017register(26, this->_MCP23017_4_regNumber, this->_MCP23017_4_regValue);
//            this->_MCP23017_4setRegister = false;
//        }

//        if(ledON)
//        {
//            this->setMCP23017_1Register(0x12, 0xFFFF);
//            this->setMCP23017_2Register(0x12, 0x0000);
//            this->setMCP23017_3Register(0x12, 0xFFFF);
//            this->setMCP23017_4Register(0x12, 0x0000);
//        }
//        else
//        {
//            this->setMCP23017_1Register(0x12, 0x0000);
//            this->setMCP23017_2Register(0x12, 0xFFFF);
//            this->setMCP23017_3Register(0x12, 0x0000);
//            this->setMCP23017_4Register(0x12, 0xFFFF);
//        }
//        qDebug() << Q_FUNC_INFO << this->objectName() <<  "Time to read data : "
//                 << this->_timeInMilisecond - this->_memotimeInMilisecond << "[ms]";

//        ledON = ledON == true ? false : true;

        this->_timeInMilisecond = QDateTime::currentMSecsSinceEpoch();// - QDateTime(QDate::currentDate()).toMSecsSinceEpoch();
        sleepingDelay = (this->_timeInMilisecond - this->_memotimeInMilisecond) > this->_sleepingDelay ?
                    0 : this->_sleepingDelay - (this->_timeInMilisecond - this->_memotimeInMilisecond);


        this->_waitDelayMili(sleepingDelay);
    }
}

void WiringPiGardian::_setMCP23017register(quint8 fd, quint16 regNumber, quint16 regValue)
{
     wiringPiI2CWriteReg16(fd, regNumber, regValue);
}

void WiringPiGardian::setMCP23017_4isReady(bool MCP23017_4isReady)
{
    _MCP23017_4isReady = MCP23017_4isReady;
}

void WiringPiGardian::setMCP23017_1fd(const quint8 &MCP23017_1fd)
{
    _MCP23017_1fd = MCP23017_1fd;
}

void WiringPiGardian::setMCP23017_2fd(const quint8 &MCP23017_2fd)
{
    _MCP23017_2fd = MCP23017_2fd;
}

void WiringPiGardian::setMCP23017_3fd(const quint8 &MCP23017_3fd)
{
    _MCP23017_3fd = MCP23017_3fd;
}

void WiringPiGardian::setMCP23017_4fd(const quint8 &MCP23017_4fd)
{
    _MCP23017_4fd = MCP23017_4fd;
}

void WiringPiGardian::setMCP23017_3isReady(bool MCP23017_3isReady)
{
    _MCP23017_3isReady = MCP23017_3isReady;
}

void WiringPiGardian::setMCP23017_2isReady(bool MCP23017_2isReady)
{
    _MCP23017_2isReady = MCP23017_2isReady;
}

void WiringPiGardian::setMCP23017_1isReady(bool MCP23017_1isReady)
{
    _MCP23017_1isReady = MCP23017_1isReady;
}

void WiringPiGardian::setMCP23017_1Register(quint16 regNumber, quint16 regValue)
{

        this->_mutex.lock();

    this->_setMCP23017register(this->_MCP23017_1fd, regNumber,  regValue);
        this->_mutex.unlock();

}

void WiringPiGardian::setMCP23017_2Register(quint16 regNumber, quint16 regValue)
{
        this->_mutex.lock();

    this->_setMCP23017register(this->_MCP23017_2fd, regNumber, regValue);
        this->_mutex.unlock();

}

void WiringPiGardian::setMCP23017_3Register(quint16 regNumber, quint16 regValue)
{
    this->_mutex.lock();

    this->_setMCP23017register(this->_MCP23017_3fd, regNumber, regValue);

    this->_mutex.unlock();
}

void WiringPiGardian::setMCP23017_4Register(quint16 regNumber, quint16 regValue)
{
    this->_mutex.lock();

    this->_setMCP23017register(this->_MCP23017_4fd, regNumber, regValue);

    this->_mutex.unlock();
}

void WiringPiGardian::_waitDelay(quint64 delayInSeconde)
{
    QThread::sleep(delayInSeconde);
}

void WiringPiGardian::_waitDelayMili(quint64 delayInMiliSeconde)
{
    QThread::msleep(delayInMiliSeconde);
}

void WiringPiGardian::_waitDelayMicro(quint64 delayInMicroSeconde)
{
    QThread::usleep(delayInMicroSeconde);
}
