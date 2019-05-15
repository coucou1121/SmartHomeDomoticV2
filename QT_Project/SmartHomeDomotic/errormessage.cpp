#include "errormessage.h"

ErrorMessage::ErrorMessage(QObject *parent):
    QObject(parent),
    _objectName("NoName"),
    _objectTitle(this->_objectName),
    _errorNumber(0),
    _active(false)
{

}

QString ErrorMessage::objectName() const
{
    return _objectName;
}

void ErrorMessage::setObjectName(const QString &objectName)
{
    _objectName = objectName;
}

QString ErrorMessage::objectTitle() const
{
    return _objectTitle;
}

void ErrorMessage::setObjectTitle(const QString &objectTitle)
{
    _objectTitle = objectTitle;
}

int ErrorMessage::errorNumber() const
{
    return _errorNumber;
}

void ErrorMessage::setErrorNumber(int errorNumber)
{
    _errorNumber = errorNumber;
}

bool ErrorMessage::active() const
{
    return _active;
}

void ErrorMessage::setActive(bool active)
{
    _active = active;
}

