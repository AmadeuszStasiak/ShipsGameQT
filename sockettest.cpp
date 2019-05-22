#include "sockettest.h"

sockettest::sockettest(QObject *parent) : QObject(parent)
{

}

void sockettest::znajdz_polaczenie()
{
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    socket->connectToHost(adres,1234);
    if(!socket->waitForConnected(5000))
    {
        qDebug()<<"nie polaczono"<<socket->errorString();
    }
    else
    {
        qDebug()<<" polaczono";

    }
}

void sockettest::connected()
{
    qDebug()<<"connected";
}

void sockettest::wyslij(QString str)
{
    const char *data=str.toStdString().c_str();
    socket->write(data);
    socket->flush();
}

QString sockettest::odbierz()
{
    QString wiadomosc=socket->readAll();
    qDebug()<<"socket"<<wiadomosc;
    return wiadomosc;
}
