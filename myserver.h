#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtWidgets>
class MyServer : public QObject
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
    bool czy_jest=false;
signals:


public slots:
    void serverStart();
    void newConnection();
    void wyslij(QString wiadomosc);
    QString odbierz();


    void delay()
    {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
private:
    QTcpServer *server;
    QTcpSocket *ssocket;
};

#endif // MYSERVER_H
