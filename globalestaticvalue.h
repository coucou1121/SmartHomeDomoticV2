#ifndef GLOBALESTATICVALUE_H
#define GLOBALESTATICVALUE_H

#include <QMap>

#include <globalenumerate.h>

class GlobaleStaticValue
{
public:
    GlobaleStaticValue();

    //warning static text
    static QString errorCounterTxt;

    //Saved staric String
    static QString saveIDTxt;
    static QString saveObjectNameTxt;
    static QString saveTitleTxt;
    static QString saveVisibleTxt;
    static QString saveLiquideInsideTxt;
    static QString saveVolumeMaxTxt;
    static QString saveLowLevelWarningTxt;
    static QString saveHeightVMaxValueTxt;
    //static array

    //TankObjectName
    /**
      * \struct  TankObjectName
      * \brief Array for all tank object name possible
      *
      * Linked the E_TankObjectName to the objectName
      * Use the objectName as groupe for saving the data
    */
    static QMap<int, QString> TankObjectName;

    // init array for external use

    // initTankObjectName
    /**
      * \func  initTankObjectName
      * \brief init the array for all tank object name possible
      *
      * static function to init the array for all tank object name possible
    */
    static QMap<int, QString> initTankObjectName();

    //TankObjectName
    /**
      * \func  initErrorPossible
      * \brief init the array for all possible error on application
      *
      * static function to init the array for all tank object name possible
    */
    static QMap<int, QString> initErrorPossible();
};

#endif // GLOBALESTATICVALUE_H
