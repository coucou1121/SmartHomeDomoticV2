#ifndef DATAFRAME_H
#define DATAFRAME_H

//*

/**
  * \file dataFrame.h
  * \author Sébastien Blessemaille
  * \version 1.0
  * \date 16 septembre 2017
  * \brief Structure of the data
  */

#include <QDebug>
#include <QTime>

class DataFrame
{

public:
    /**
      * \fn DataFrame();
      * \brief constructor for DataFrame
      */
    DataFrame();

    /**
      * \fn quint8 msbCPT() const
      * \brief Getter for msbCPT attribute
      * \return msbCPT : quint8
      */
    quint8 msbCPT() const;

    /**
      * \fn  void setMsbCPT(const quint8 &msbCPT)
      * \brief Setter for msbCPT attribute
      * \param[in] msbCPT is highest byte counter .
      * \return void : nothing
      */
    void setMsbCPT(const quint8 &msbCPT);

    /**
      * \fn double BME280_temperature() const
      * \brief Getter for BME280_temperature attribute
      * \return BME280_temperature : double
      */
    double BME280_temperature() const;
    /**
      * \fn  void setBME280_temperature(double BME280_temperature);
      * \brief Setter for BME280_temperature attribute
      * \param[in] BME280_temperature is room temperature .
      * \return void : nothing
      */
    void setBME280_temperature(double BME280_temperature);

    /**
      * \fn double BME280_humidity() const
      * \brief Getter for BME280_humidity attribute
      * \return BME280_humidity : double
      */

    double BME280_humidity() const;
    /**
      * \fn  void setBME280_humidity(double BME280_temperature);
      * \brief Setter for BME280_humidity attribute
      * \param[in] BME280_humidity is room relative humidity.
      * \return void : nothing
      */
    void setBME280_humidity(double BME280_humidity);

    /**
      * \fn double BME280_pressure() const
      * \brief Getter for BME280_pressure attribute
      * \return BME280_pressure : double
      */
    double BME280_pressure() const;
    /**
      * \fn  void setBME280_pressure(double BME280_temperature)
      * \brief Setter for BME280_pressure attribute
      * \param[in] BME280_pressure is atospheric pressure.
      * \return void : nothing
      */
    void setBME280_pressure(double BME280_pressure);

    /**
      * \fn double ADS115_1_chan0() const
      * \brief Getter for ADS115_1_chan0 attribute
      * \return ADS115_1_chan0 : double
      */
    qint16 ADS115_1_chan0() const;
    /**
      * \fn  void setADS115_1_chan0(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_1_chan0 attribute
      * \param[in] ADS115_1_chan0 is volume value on channel 0
      * of ADS1115_1.
      * \return void : nothing
      */
    void setADS115_1_chan0(const qint16 &ADS115_1_chan0);

    /**
      * \fn qint16 ADS115_1_chan1() const
      * \brief Getter for ADS115_1_chan1 attribute
      * \return ADS115_1_chan1 : double
      */
    qint16 ADS115_1_chan1() const;
    /**
      * \fn  void setADS115_1_chan1(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_1_chan1 attribute
      * \param[in] ADS115_1_chan1 is volume value on channel 1
      * of ADS1115_1.
      * \return void : nothing
      */
    void setADS115_1_chan1(const qint16 &ADS115_1_chan1);

    /**
      * \fn double ADS115_1_chan2() const
      * \brief Getter for ADS115_1_chan2 attribute
      * \return ADS115_1_chan2 : double
      */
    qint16 ADS115_1_chan2() const;
    /**
      * \fn  void setADS115_1_chan2(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_1_chan2 attribute
      * \param[in] ADS115_1_chan2 is volume value on channel 2
      * of ADS1115_1.
      * \return void : nothing
      */
    void setADS115_1_chan2(const qint16 &ADS115_1_chan2);

    /**
      * \fn double ADS115_1_chan3() const
      * \brief Getter for ADS115_1_chan3 attribute
      * \return ADS115_1_chan3 : double
      */
    qint16 ADS115_1_chan3() const;
    /**
      * \fn  void setADS115_1_chan3(const double &ADS115_1_chan0)
      * \brief Setter for setADS115_1_chan3 attribute
      * \param[in] setADS115_1_chan3 is volume value on channel 3
      * of ADS1115_1.
      * \return void : nothing
      */
    void setADS115_1_chan3(const qint16 &setADS115_1_chan3);

    /**
      * \fn double ADS115_2_chan0() const
      * \brief Getter for ADS115_2_chan0 attribute
      * \return ADS115_2_chan0 : double
      */
    qint16 ADS115_2_chan0() const;
    /**
      * \fn  void setADS115_2_chan0(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_2_chan0 attribute
      * \param[in] ADS115_1_chan0 is volume value on channel 0.
      * of ADS1115_2.
      * \return void : nothing
      */
    void setADS115_2_chan0(const qint16 &ADS115_2_chan0);

    /**
      * \fn double ADS115_2_chan1() const
      * \brief Getter for ADS115_2_chan1 attribute
      * \return ADS115_2_chan1 : double
      */
    qint16 ADS115_2_chan1() const;
    /**
      * \fn  void setADS115_2_chan1(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_2_chan1 attribute
      * \param[in] ADS115_2_chan1 is volume value on channel 1.
      * of ADS1115_2.
      * \return void : nothing
      */
    void setADS115_2_chan1(const qint16 &ADS115_2_chan1);

    /**
      * \fn double ADS115_2_chan2() const
      * \brief Getter for ADS115_2_chan2 attribute
      * \return ADS115_2_chan2 : double
      */
    qint16 ADS115_2_chan2() const;
    /**
      * \fn  void setADS115_2_chan2(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_2_chan2 attribute
      * \param[in] ADS115_2_chan2 is volume value on channel 2.
      * of ADS1115_2.
      * \return void : nothing
      */
    void setADS115_2_chan2(const qint16 &ADS115_2_chan2);

    /**
      * \fn double ADS115_2_chan3() const
      * \brief Getter for ADS115_2_chan3 attribute
      * \return ADS115_2_chan3 : double
      */
    qint16 ADS115_2_chan3() const;
    /**
      * \fn  void setADS115_2_chan3(const double &ADS115_1_chan0)
      * \brief Setter for ADS115_2_chan3 attribute
      * \param[in] ADS115_2_chan3 is volume value on channel 2
      * of ADS1115_2.
      * \return void : nothing
      */
    void setADS115_2_chan3(const qint16 &ADS115_2_chan3);

    /**
      * \fn  quint16 dataFrameState() const
      * \brief Getter for the state of the DataFrame
      * \return dataFrameState : quint16
      */
    quint16 dataFrameState() const;

    /**
      * \fn  void setDataFrameState(const quint16 &dataFrameState)
      * \brief Setter for dataFrameState attribute
      * \param[in] dataFrameState is the state of the Dataframe
      * \return void : nothing
      */
    void setDataFrameState(const quint16 &dataFrameState);

    /**
      * \fn  QDateTime dateTime() const
      * \brief Getter for the date and time when the data was wrotes
      * \return dateTime : QDateTime
      */
    QDateTime dateTime() const;

    /**
      * \fn  void setDateTime(const QDateTime &dateTime)
      * \brief Setter for dateTime attribute
      * \param[in] dateTime date and time when the data was wrotes
      * \return void : nothing
      */
    void setDateTime(const QDateTime &dateTime);

private:

    //frame structure
    QDateTime _dateTime;
    double _BME280_temperature;
    double _BME280_humidity;
    double _BME280_pressure;
    qint16 _ADS115_1_chan0;
    qint16 _ADS115_1_chan1;
    qint16 _ADS115_1_chan2;
    qint16 _ADS115_1_chan3;
    qint16 _ADS115_2_chan0;
    qint16 _ADS115_2_chan1;
    qint16 _ADS115_2_chan2;
    qint16 _ADS115_2_chan3;

    quint16 _dataFrameState;

};

#endif // DATAFRAME_H
