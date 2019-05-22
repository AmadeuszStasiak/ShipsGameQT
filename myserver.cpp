#include "myserver.h"

MyServer::MyServer(QObject *parent) : QObject(parent)
{



}

void MyServer::serverStart()
{
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));

        if(!server->listen(QHostAddress::Any,1234))
        {
             //QMessageBox::information(this,"serwer NIE wystartował","serwer NIE wystartował");
            qDebug() <<"Serwer nie wystartował";
        }
        else
        {
            qDebug() <<"Serwer wystartował";
        }

}

void MyServer::newConnection()
{
ssocket=server->nextPendingConnection();
if(ssocket->state() == QAbstractSocket::ConnectedState)
{
    czy_jest=true;
}


}

void MyServer::wyslij(QString str)
{

    const char *data=str.toStdString().c_str();
    ssocket->write(data);
    ssocket->flush();
}



QString MyServer::odbierz()
{
    QString wiadomosc=ssocket->readAll();
    qDebug()<<"server"<<wiadomosc;
    return wiadomosc;

}

