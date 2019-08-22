#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QObject>

class ErrorMessage : public QObject
{
    Q_OBJECT
public:
    explicit ErrorMessage(QObject *parent = nullptr);

    QString objectName() const;
    void setObjectName(const QString &objectName);

    QString objectTitle() const;
    void setObjectTitle(const QString &objectTitle);

    int errorNumber() const;
    void setErrorNumber(int errorNumber);

    bool active() const;
    void setActive(bool active);

private:
    QString _objectName;
    QString _objectTitle;
    int _errorNumber;
    bool _active;
};

#endif // ERRORMESSAGE_H
