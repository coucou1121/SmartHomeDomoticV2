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


    /**
      * \fn init();
      * \brief create link bettween C++ and QML
      */
    static void initClass();
};

#endif // GLOBALENUMERATE_H
