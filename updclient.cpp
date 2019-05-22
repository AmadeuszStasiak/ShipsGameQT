#include "updclient.h"
#include <QUdpSocket>
#include <QtNetwork>
UPDclient::UPDclient(QWidget *parent) : QWidget(parent)
{

    mSocket= new QUdpSocket(this);
    mSocket->bind(1234,QUdpSocket::ShareAddress);
    connect(mSocket,SIGNAL(readyRead()),this,
           SLOT(processPendingDatagrams()));

}

void UPDclient::odbierz()
{
    QByteArray datagram;
    while (mSocket->hasPendingDatagrams()) {
           datagram.resize(int(mSocket->pendingDatagramSize()));
           mSocket->readDatagram(datagram.data(), datagram.size());
           qDebug()<<QString(datagram);
           this->adres=QString(datagram);
       }

}
void UPDclient::polacz()
{
}
