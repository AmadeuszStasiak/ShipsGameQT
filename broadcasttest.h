#ifndef BROADCASTTEST_H
#define BROADCASTTEST_H

#include <QWidget>


class QUdpSocket;

class broadcasttest : public QWidget
{
    Q_OBJECT
public:
    explicit broadcasttest(QWidget *parent = nullptr);

    void wyslij();


private:
    QUdpSocket *mSocket;
signals:

public slots:
};

#endif // BROADCASTTEST_H
