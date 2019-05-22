#include "broadcasttest.h"
#include <QUdpSocket>
#include <QNetworkInterface>
broadcasttest::broadcasttest(QWidget *parent) : QWidget(parent)
{
    mSocket = new QUdpSocket(this);
}

void broadcasttest::wyslij()
{
    QString mojip="0";
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
             qDebug() <<"ip1" <<address.toString();
        mojip= address.toString();
        }
    }
    qDebug()<<"wyslałem broadcast ip2"<<mojip;

    auto mojip1=mojip.toUtf8();
    mSocket->writeDatagram(mojip1,QHostAddress::Broadcast,1234);
}
