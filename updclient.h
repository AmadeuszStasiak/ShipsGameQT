#ifndef UPDCLIENT_H
#define UPDCLIENT_H

#include <QWidget>

class QUdpSocket;
class UPDclient : public QWidget
{
    Q_OBJECT
public:
    explicit UPDclient(QWidget *parent = nullptr);
    QUdpSocket *mSocket;
    QString adres="0";
    void odbierz();
    void polacz();
signals:

public slots:
};

#endif // UPDCLIENT_H
