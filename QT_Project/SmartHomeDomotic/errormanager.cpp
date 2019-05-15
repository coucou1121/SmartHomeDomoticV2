#include "errormanager.h"

ErrorManager::ErrorManager(QWidget *parent, QObject *objectDisplayMessage):
    QObject (parent),
    _objectDisplayMessage(objectDisplayMessage),
    _errorMessage(new ErrorMessage),
   _errorListPossible(GlobaleStaticValue::initErrorPossible())
{
    this->_displayMessage();
}

ErrorManager::~ErrorManager()
{

}

void ErrorManager::_setColor(bool inTrouble)
{
    if(inTrouble)
    {
        //        CommonStyle::setErrorColor(ui->label);
        //        CommonStyle::setErrorColor(ui->line);

        //setup sample / second frame
        //       ui->label->setStyleSheet("background-color:" + _myStyle.getBackGroundColorErrorFrame().name()+ ";");
        //       ui->line->setStyleSheet("background-color:" + _myStyle.getErrorLineInTrouble().name()+ ";");
    }
    else
    {
        //setup sample / second frame
        //        CommonStyle::setBackGroundColor(ui->label);
        //        CommonStyle::setbackGroundColorFrame(ui->line);
        //ui->label->setStyleSheet("background-color:" + _myStyle.getBackGroundColor().name()+ ";");
        //       ui->line->setStyleSheet("background-color:" + _myStyle.getBackGroundColorBottomBar().name()+ ";");
    }
}

bool ErrorManager::_checkMessageAllreadyExiste(ErrorMessage *errorMessage)
{
    bool findErrorInListe = false;

    //check if the message existe
    foreach(int key, _errorListNow.keys())
    {
        if(!findErrorInListe)
        {
            if(errorMessage->objectName() == this->_errorListNow[key]->objectName() &&
                    errorMessage->errorNumber() ==  this->_errorListNow[key]->errorNumber())
            {
                findErrorInListe = true;
            }
        }
    }

    return findErrorInListe;
}

int ErrorManager::_findIdToRemove(ErrorMessage *errorMessage)
{
    int IDfound = -1;

    foreach(int key, _errorListNow.keys())
    {
        if(errorMessage->objectName() == this->_errorListNow[key]->objectName() &&
                errorMessage->errorNumber() ==  this->_errorListNow[key]->errorNumber())
        {
            IDfound = key;
        }
    }

    return IDfound;
}

void ErrorManager::_displayMessage()
{
    static int memoCounterNbError = -1;
    int highestPriorityMessageToDisplay = 0;
    int IDhighPriotityMessageToDisplay = 0;
    QString objectName = "";

//    qDebug() << "nb error :" << _errorListNow.size();
//    qDebug() << "_errorListNow.isEmpty()" << _errorListNow.isEmpty();

    if(memoCounterNbError != _errorListNow.size() && !_errorListNow.isEmpty())
    {
        memoCounterNbError = _errorListNow.size();
        QMetaObject::invokeMethod(this->_objectDisplayMessage, "errorCounterNumberToDisplay",
                                  Q_ARG(QVariant, GlobaleStaticValue::errorCounterTxt),
                                  Q_ARG(QVariant, memoCounterNbError));
    }


    if(_errorListNow.isEmpty())
    {
//        this->_setColor(false);
        QMetaObject::invokeMethod(this->_objectDisplayMessage, "noErrorToDisplay");
        memoCounterNbError = 0;
    }
    else
    {
//        this->_setColor(true);

        //find the highest priority message to display
        foreach(int key, _errorListNow.keys())
        {

            if(highestPriorityMessageToDisplay < this->_errorListNow[key]->errorNumber())
            {
              highestPriorityMessageToDisplay = this->_errorListNow[key]->errorNumber();
              IDhighPriotityMessageToDisplay = key;
            }

        }

//        qDebug() << "highestPriorityMessageToDisplay :" << highestPriorityMessageToDisplay;

        QMetaObject::invokeMethod(this->_objectDisplayMessage, "errorMessageReceivedToDisplay",
                                  Q_ARG(QVariant, this->_errorListNow[IDhighPriotityMessageToDisplay]->objectTitle()),
                                  Q_ARG(QVariant, this->_errorListPossible[highestPriorityMessageToDisplay]));

    }


//    MyTcpSocket socket;
//    socket.doConnect();

//    Smtp *newMail  = new Smtp("coucoulhb1121@gmail.com","coucoulhb1121@gmail.com"," Your Subject","My body text");
//    delete newMail;
}

void ErrorManager::_reveived_Error(QString objectName, QString objectTitle, int errorNumber, bool active)
{
    qDebug() << "recievedError :" << objectName << ", " << errorNumber << ", " << active;
    static qint16 IDerrorNumber = 0;

    bool errorAllreadyExiste = false;

    ErrorMessage *errorMessage = new ErrorMessage();


    errorMessage->setObjectName(objectName);
    errorMessage->setObjectTitle(objectTitle);
    errorMessage->setErrorNumber(errorNumber);
    errorMessage->setActive(active);

//    qDebug() << "errorMessage:" << errorMessage;
//    qDebug() << "errorMessage->objectName :" << errorMessage->objectName();
//    qDebug() << "errorMessage->objectTitle :" << errorMessage->objectTitle();
//    qDebug() << "errorMessage->errorNumber :" << errorMessage->errorNumber();
//    qDebug() << "errorMessage->active :" << errorMessage->active();

    //check if the message allready existe
    errorAllreadyExiste = this->_checkMessageAllreadyExiste(errorMessage);
//    qDebug() << "errorAllreadyExiste" << errorAllreadyExiste;
//    qDebug() << "nb error :" << _errorListNow.size();

    if(!errorAllreadyExiste && active)
    {
        _errorListNow.insert(IDerrorNumber,errorMessage);
        IDerrorNumber++;
        //        ledManager::redLedOn();
    }

    if(errorAllreadyExiste && !active)
    {
        _errorListNow.remove(_findIdToRemove(errorMessage));
        // IDerrorNumber--;
        //        ledManager::redLedOff();
    }
//    qDebug() << "nb error :" << _errorListNow.size();

    this->_displayMessage();
}
