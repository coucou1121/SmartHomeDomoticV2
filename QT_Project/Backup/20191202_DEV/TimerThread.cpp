#include "TimerThread.h"

timerthread::timerthread(bool isWorking, QString name, quint16 delay) :
    _delay(delay),
  _isWorking(isWorking)
{
    this->setObjectName(name);
    moveToThread(this);
}

void timerthread::usleep(unsigned long usecs)
{
    QThread::usleep(usecs);
}

void timerthread::msleep(unsigned long msecs)
{
    QThread::msleep(msecs);
}

void timerthread::sleep(unsigned long secs)
{
    QThread::sleep(secs);
}

void timerthread::startWorking()
{
//    qDebug() << objectName() << "received start Working";
    this->_isWorking = true;
}

void timerthread::stopWorking()
{
//    qDebug() << objectName() << "received stop Working";
    this->_isWorking = false;
}

// run() will be called when a thread starts
void timerthread::run()
{
//    unsigned long int cpt=0;

    while(true)
    {

 //       qDebug() << objectName() << thread()->currentThreadId() << cpt << "is working : " << this->_isWorking;
        if(_isWorking)
        {
//            cpt++;
            emit delayFinished();
        }
        else
        {

        }
        this->msleep(_delay);
    }

}

bool timerthread::isWorking() const
{
    return _isWorking;
}



