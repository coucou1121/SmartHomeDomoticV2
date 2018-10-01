#include "tank.h"

Tank::Tank(int objectID, QString objectName, QObject *parent):
    QObject(parent),
    _objectID(objectID),
    _objectName(objectName),
    _title("no name"),
    _isVisible(false),
    _volumeMax(0),
    _lowLevelValue(0),
    _heightVMaxValue(0)
{

}

QString Tank::title() const
{
    return _title;
}

void Tank::setTitle(const QString &title)
{
    _title = title;
}

GlobalEnumerate::E_TankLiquidInside Tank::LiquideFillup() const
{
    return _LiquideFillup;
}

void Tank::setLiquideFillup(const GlobalEnumerate::E_TankLiquidInside &LiquideFillup)
{
    _LiquideFillup = LiquideFillup;
}

void Tank::setLiquideFillup(const int &LiquideFillup)
{
    switch (LiquideFillup)
    {
    case GlobalEnumerate::WATER :
        this->setLiquideFillup(GlobalEnumerate::WATER);
        break;
    case GlobalEnumerate::OIL :
        this->setLiquideFillup(GlobalEnumerate::OIL);
        break;
    case GlobalEnumerate::ECO_OIL :
        this->setLiquideFillup(GlobalEnumerate::ECO_OIL);
        break;
    }
}

bool Tank::isVisible() const
{
    return _isVisible;
}

void Tank::setIsVisible(const bool isVisible)
{
    _isVisible = isVisible;
}

int Tank::volumeMax() const
{
    return _volumeMax;
}

void Tank::setVolumeMax(const int &volumeMax)
{
    _volumeMax = volumeMax;
}

int Tank::lowLevelValue() const
{
    return _lowLevelValue;
}

void Tank::setLowLevelValue(const int &lowLevelValue)
{
    _lowLevelValue = lowLevelValue;
}

int Tank::objectID() const
{
    return _objectID;
}

void Tank::setObjectID(int objectID)
{
    _objectID = objectID;
}

int Tank::heightVMaxValue() const
{
    return _heightVMaxValue;
}

void Tank::setHeightVMaxValue(int heightVMaxValue)
{
    _heightVMaxValue = heightVMaxValue;
}

QString Tank::objectName() const
{
    return _objectName;
}
