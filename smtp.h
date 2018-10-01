#ifndef SMTP_H
#define SMTP_H

#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <mytcpsocket.h>

class Smtp: public QObject
{
    Q_OBJECT


public:
    Smtp( const QString &from, const QString &to,
    const QString &subject, const QString &body );
    ~Smtp();

signals:
    void status( const QString &);

public slots:

    void connected();
        void disconnected();
        void bytesWritten(qint64 bytes);
        void readyRead();

private slots:
    void stateChanged(QTcpSocket::SocketState socketState);
    void errorReceived(QTcpSocket::SocketError socketError);
//    void disconnected();
//    void connected();
//    void readyRead();

private:
    QString message;
    QTextStream *t;
    QTcpSocket *socket;
    QString from;
    QString rcpt;
    QString response;
    enum states{Rcpt,Mail,Data,Init,Body,Quit,Close};
    int state;

};

#endif // SMTP_H
