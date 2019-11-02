#ifndef GLOBALENUMERATE_H
#define GLOBALENUMERATE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QMetaType>
#include <QQmlEngine>

class GlobalEnumerate : public QObject
{
    Q_OBJECT

public:
    GlobalEnumerate();

    //plotStyle mode
    /**
      * \struct  E_PlotStyle
      * \brief liste of the different mode of the plots
       *
      * Is use to set trace shape and limite for warning
      */

    typedef enum
    {
        PLOT_STYLE_WEATHER_STATION = 0,    /*!< weather station style, 1x temp, 1x humidity, 1x pressur and 1x horizontal limite line*/
        PLOT_STYLE_TANK_TRACE,    /*!< Tank trace from 1 to 6 trces possible */
        PLOT_STYLE_ANANLOG_TRACE,          /*!< line traces, 1x traces and 1x horizontal limite line */
        PLOT_STYLE_STATISTIC_TRACE,        /*!< line traces, 6x traces and 1x horizontal limite line */
        PLOT_STYLE_TEMPERATURE_TRACE,        /*!< line traces, 2x traces and 1x horizontal limite line */
        PLOT_STYLE_HUMIDITY_TRACE,        /*!< line traces, 2x traces and 1x horizontal limite line */
        PLOT_STYLE_PRESSURE_TRACE,        /*!< line traces, 2x traces and 1x horizontal limite line */
        PLOT_STYLE_CONSO_TRACE,        /*!< line traces, 2x traces and 1x horizontal limite line */
        PLOT_STYLE_NONE,                /*!< use as default value for function setupStyle */
    }E_PlotStyle;

    Q_ENUM(E_PlotStyle)

    //liquide inside the tank
    /**
      * \struct  E_TankLiquidInside
      * \brief liste of the product can be fill
      *
      * Is use to set the color of the tank level and the liquide density
      */

    typedef enum
    {
        WATER = 0,  /*!< water inside tank*/
        OIL,        /*!< oil inside tank*/
        ECO_OIL      /*!< ecoOil inside tank*/
    }E_TankLiquidInside;

    Q_ENUM(E_TankLiquidInside)

    //tank object for linking to custom name
    /**
         * \struct  E_TankObjectName
         * \brief structure of all tank possible
         *
         * Use to manage the link between the custom name and the object
         */
    typedef enum
    {
        TANK1 = 1,     /*!< tank on the 1 row 1 column */
        TANK2,         /*!< tank on the 1 row 2 column */
        TANK3,         /*!< tank on the 1 row 3 column */
        TANK4,         /*!< tank on the 2 row 1 column */
        TANK5,         /*!< tank on the 2 row 2 column */
        TANK6          /*!< tank on the 2 row 3 column */
    }E_TankObjectName;

    Q_ENUM(E_TankObjectName)


    //tank object for linking to custom name
    /**
         * \struct  E_TankObjectName
         * \brief structure of all tank possible
         *
         * Use to manage the link between the custom name and the object
         */
    typedef enum
    {
        HOMEBME280 = 0,     /*!< BME280 object */
        HOMETANK1,        /*!< Tank 1 object */
        HOMETANK2,          /*!< Tank 2 object */
        HOMETANK3,          /*!< Tank 3 object */
        HOMETANK4,          /*!< Tank 4 object */
        HOMETANK5,          /*!< Tank 5 object */
        HOMETANK6,          /*!< Tank 6 object */
        HOMESENSOR1,     /*!< Sensor 1 object */
        HOMESENSOR2,         /*!< Sensor 2 object */
        HOMESENSOR3,         /*!< Sensor 3 object */
        HOMESENSOR4,         /*!< Sensor 4 object */
        HOMESENSOR5,         /*!< Sensor 5 object */
        HOMESENSOR6,         /*!< Sensor 6 object */
        HOMEAD1115_1,        /*!< converter AD1115 number 1 object */
        HOMEAD1115_2         /*!< converter AD1115 number 2 object */
    }E_HomePageObject;

    Q_ENUM(E_HomePageObject)
    // Error Possible
    // from the Highest priority is at the top after noError
    /**
      * \struct  eError
      * \brief structure of all error possible
      *
      * The Highest priority message will be displaying and it's at the top after noError
      */
    typedef enum
    {
        ERR_NO_ERROR,                       /*!< no Error */
        ERR_LOW_LEVEL_REACHED,              /*!< on of the tank reach the low level warning */
    }E_ErrorMesseage;

    Q_ENUM(E_ErrorMesseage)


    //tank object for linking to custom name
    /**
         * \struct  E_TankObjectName
         * \brief structure of all tank possible
         *
         * Use to manage the link between the custom name and the object
         */
    typedef enum
    {
        STATE_NOT_FOUNDED = 0,    /*!< state not founded */
        STATE_FOUNDED,            /*!< state founded */
        STATE_INIT,               /*!< state in init*/
        STATE_ON_READING,         /*!< state on reading */
        STATE_READY,              /*!< state ready to use*/
    }E_StateMachine;

    Q_ENUM(E_StateMachine)

    /**
      * \fn init();
      * \brief create link bettween C++ and QML
      */
    static void initClass();
};

#endif // GLOBALENUMERATE_H
