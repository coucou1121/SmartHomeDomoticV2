#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

/**
  * \file errormanager.h
  * \author Sébastien Blessemaille
  * \version 1.0
  * \date 21 August 2017
  * \brief Management of the error messages
  */

#include <QWidget>
#include <QDebug>
#include <globalenumerate.h>
#include <globalestaticvalue.h>
#include <errormessage.h>

//#include "ledManager.h"

class ErrorManager : public QObject
{
    Q_OBJECT

public:

    /**
      * \fn  explicit ErrorMessage(QWidget *parent = 0)
      * \brief constructor for ErrorMessage
      * \param[in] parent is the parent of the new widget.
      * If it is 0 (the default), the new widget will be a window.
      * If not, it will be a child of parent, and be constrained by parent's geometry
      */
    explicit ErrorManager(QWidget *parent = nullptr, QObject *objectDisplayMessage = nullptr);

    /**
      * \fn  ~ErrorMessage()
      * \brief destructor for ErrorMessage
      */
    ~ErrorManager();

private:

    QObject *_objectDisplayMessage;

    ErrorMessage *_errorMessage;

    QMap<int, QString> _errorListPossible;
    QMap<int, ErrorMessage*> _errorListNow;


    /**
      * \fn void _setColor(bool inTrouble)
      * \brief Use to change the color of the message display.
      * Red in case of errors messages, grey no error message at all.
      * \param[in] inTrouble is the status of the message
      * \return void : nothing
      */
    void _setColor(bool inTrouble);

    /**
      * \fn void _displayMessage()
      * \brief Use to display the message in the dedicated frame.
      * \return void : nothing
      */
    bool _checkMessageAllreadyExiste(ErrorMessage *errorMessage);

    /**
      * \fn void _displayMessage()
      * \brief Use to display the message in the dedicated frame.
      * \return void : nothing
      */
    int _findIdToRemove(ErrorMessage *errorMessage);

    /**
      * \fn void _displayMessage()
      * \brief Use to display the message in the dedicated frame.
      * \return void : nothing
      */
    void _displayMessage();

private slots:
    void _reveived_Error(QString objectName, QString objectTitle, int errorNumber, bool active);

};

#endif // ERRORMANAGER_H
