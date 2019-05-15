#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

//*

/**
  * \file TIMERTHREAD.h
  * \author Sébastien Blessemaille
  * \version 1.0
  * \date 17 septembre 2017
  * \brief generic thread to create a tick
  */

#include <QtDebug>
#include <QThread>

class timerthread : public QThread
{
    Q_OBJECT
public:    
    /**
      * \fn TIMERTHREAD(bool isWorking, QString name, quint16 delay);
      * \brief constructor for FrameThread
      * \param[in] isWorking is the status when the thread start
      * \param[in] name is the name of the object
      * \param[in] delay is the cycle time delay
      */
    timerthread(bool isWorking, QString name, quint16 delay);

    /**
      * \fn  static void usleep(unsigned long usecs)
      * \brief waiting delay
      * \param[in] msleep is the time in microseconds
      * \return void : nothing
      */
    static void usleep(unsigned long usecs);

    /**
      * \fn  static void msleep(unsigned long msecs)
      * \brief waiting delay
      * \param[in] msleep is the time in miliseconds
      * \return void : nothing
      */
    static void msleep(unsigned long msecs);

    /**
      * \fn  static void sleep(unsigned long secs)
      * \brief waiting delay
      * \param[in] secs is the time in seconds
      * \return void : nothing
      */
    static void sleep(unsigned long secs);

    //start real time reading
    /**
      * \fn  startWorking()
      * \brief start working operation
      * \return void : nothing
     */
    void startWorking();

    //start real time reading
    /**
      * \fn  stopWorking()
      * \brief stop working operation
      * \return void : nothing
     */
    void stopWorking();

    bool isWorking() const;

protected:
    /**
      * \fn void run()
      * \brief called function when the thread start
      * \return void : nothing
      */
    void run();
private:
    quint16 _delay;
    bool _isWorking;

signals:
    void delayFinished();
};

#endif // TIMERTHREAD_H
