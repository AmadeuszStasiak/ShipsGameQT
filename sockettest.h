#ifndef SOCKETTEST_H
#define SOCKETTEST_H

#include <QObject>

#include <QTcpSocket>
#include <QDebug>
#include <QtWidgets>
class sockettest : public QObject
{
    Q_OBJECT
public:
    explicit sockettest(QObject *parent = nullptr);
    QString adres;
signals:

public slots:
    void znajdz_polaczenie();
    void connected();
    void wyslij(QString str);
    QString odbierz();
    void delay()
    {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }



public:
       QTcpSocket *socket;
};

#endif // SOCKETTEST_H
