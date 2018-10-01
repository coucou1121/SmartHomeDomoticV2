#include "smtp.h"

Smtp::Smtp( const QString &from, const QString &to, const QString &subject, const QString &body )
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    message = "To: " + to + "\n";
    message.append("From: " + from + "\n");
    message.append("Subject: " + subject + "\n");
    message.append(body);
    message.replace( QString::fromLatin1( "\n" ), QString::fromLatin1( "\r\n" ) );
    message.replace( QString::fromLatin1( "\r\n.\r\n" ),
                     QString::fromLatin1( "\r\n..\r\n" ) );
    this->from = from;
    rcpt = to;
    state = Init;
    socket->connectToHost( "www.google.com", 80);
    if(socket->waitForConnected ( 30000 ))
    {
        qDebug() << "Connected!";

        // send
        socket->write("hello server\r\n\r\n\r\n\r\n");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Reading: " << socket->bytesAvailable();

        qDebug() << socket->readAll();

        socket->close();
    }

    t = new QTextStream( socket );
}
Smtp::~Smtp()
{
    delete t;
    delete socket;
}
void Smtp::stateChanged(QTcpSocket::SocketState socketState)
{

    qDebug() <<"stateChanged " << socketState;
}

void Smtp::errorReceived(QTcpSocket::SocketError socketError)
{
    qDebug() << "error " <<socketError;
}

void Smtp::disconnected()
{

    qDebug() <<"disconneted";
//    qDebug() << "error "  << socket->errorString();
}

void Smtp::bytesWritten(qint64 bytes)
{
    qDebug() << "We wrote: " << bytes;
}

void Smtp::connected()
{
    //    output->append("connected");
    qDebug() << "Connected ";
}

void Smtp::readyRead()
{

    qDebug() <<"readyRead";
    // SMTP is line-oriented

    QString responseLine;
    do
    {
        responseLine = socket->readLine();
        response += responseLine;
    }
    while ( socket->canReadLine() && responseLine[3] != ' ' );

    responseLine.truncate( 3 );


//    if ( state == Init && responseLine[0] == '2' )
//    {
//        // banner was okay, let's go on

//        *t << "HELO there\r\n";
//        t->flush();

//        state = Mail;
//    }
//    else if ( state == Mail && responseLine[0] == '2' )
//    {
//        // HELO response was okay (well, it has to be)

//        *t << "MAIL FROM: " << from << "\r\n";
//        t->flush();
//        state = Rcpt;
//    }
//    else if ( state == Rcpt && responseLine[0] == '2' )
//    {

//        *t << "RCPT TO: " << rcpt << "\r\n"; //r
//        t->flush();
//        state = Data;
//    }
//    else if ( state == Data && responseLine[0] == '2' )
//    {

//        *t << "DATA\r\n";
//        t->flush();
//        state = Body;
//    }
//    else if ( state == Body && responseLine[0] == '3' )
//    {

//        *t << message << "\r\n.\r\n";
//        t->flush();
//        state = Quit;
//    }
//    else if ( state == Quit && responseLine[0] == '2' )
//    {

//        *t << "QUIT\r\n";
//        t->flush();
//        // here, we just close.
//        state = Close;
//        emit status( tr( "Message sent" ) );
//    }
//    else if ( state == Close )
//    {
//        deleteLater();
//        return;
//    }
//    else
//    {
//        // something broke.
//        QMessageBox::warning( nullptr, tr( "Qt Mail Example" ), tr( "Unexpected reply from SMTP server:\n\n" ) + response );
//        state = Close;
//    }
//    response = "";
}
