#ifndef TANK_H
#define TANK_H


/**
  * \file tank.h
  * \author Sébastien Blessemaille
  * \version 1.0
  * \date 09 september 2018
  * \brief tank object class, use to link them with the QML object
  */

#include <QObject>
#include <globalenumerate.h>

class Tank : public QObject
{

    Q_OBJECT

public:


    /**
      * \fn explicit Tank(int objectID, QString objectName, QObject *parent = nullptr);
      * \brief constructor for Tank
      * \param[in] objectID is the unique ID for this object type.
      * \param[in] objectName is the unique name for this object type.
      * \param[in] parent is the parent of the new widget.
      * If it is nullptr (the default), the new widget will be a window.
      * If not, it will be a child of parent, and be constrained by parent's geometry
      */
    explicit Tank(int objectID, QString objectName, QObject *parent = nullptr);

    /**
      * \fn  objectName()
      * \brief getter for _objecName property
      */
    QString objectName() const;

    /**
      * \fn  title()
      * \brief getter for _title property
      */
    QString title() const;

    /**
      * \fn  setTitle()
      * \brief setter for _title property
      */
    void setTitle(const QString &title);

    /**
      * \fn  LiquideFillup()
      * \brief getter for _liquideFillup property
      */
    GlobalEnumerate::E_TankLiquidInside LiquideFillup() const;

    /**
      * \fn  setLiquideFillup()
      * \brief setter for _LiquideFillup property
      */
    void setLiquideFillup(const GlobalEnumerate::E_TankLiquidInside &LiquideFillup);

    /**
      * \fn  setLiquideFillup()
      * \brief setter for _setLiquideFillup property
      */
    void setLiquideFillup(const int &LiquideFillup);

    /**
      * \fn  isVisible()
      * \brief getter for _isVisible property
      */
    bool isVisible() const;

    /**
      * \fn  setLiquideFillup()
      * \brief setter for _setLiquideFillup property
      */
    void setIsVisible(const bool isVisible);

    /**
      * \fn  volumeMax()
      * \brief getter for _volumeMax property
      */
    int volumeMax() const;

    /**
      * \fn  setVolumeMax()
      * \brief setter for _setVolumeMax property
      */
    void setVolumeMax(const int &volumeMax);

    /**
      * \fn  lowLevelValue()
      * \brief getter for _lowLevelValue property
      */
    int lowLevelValue() const;

    /**
      * \fn  setLowLevelValue()
      * \brief setter for _setLowLevelValue property
      */
    void setLowLevelValue(const int &lowLevelValue);

    /**
      * \fn  objectID()
      * \brief getter for _objectID property
      */
    int objectID() const;

    /**
      * \fn  setObjectID()
      * \brief setter for _setObjectID property
      */
    void setObjectID(int objectID);

    /**
      * \fn  heightVMaxValue()
      * \brief getter for _heightVMaxValue property
      */
    int heightVMaxValue() const;

    /**
      * \fn  setHeightVMaxValue()
      * \brief setter for _heightVMaxValue property
      */
    void setHeightVMaxValue(int heightVMaxValue);

private:

    int _objectID;
    QString _objectName;
    QString _title;
    GlobalEnumerate::E_TankLiquidInside _LiquideFillup;
    bool _isVisible;
    int _volumeMax;
    int _lowLevelValue;
    int _heightVMaxValue;
};

#endif // TANK_H
