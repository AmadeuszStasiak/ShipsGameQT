#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QDebug>
#include "myserver.h"
#include "sockettest.h"
#include <windows.h>
#include <QThread>
#include <QtWidgets>
#include "broadcasttest.h"
#include "updclient.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_maly_clicked();

    void on_srednipoziomo_clicked();

    void on_b11_clicked();

    void on_b12_clicked();

    void on_b13_clicked();

    void on_b14_clicked();

    void on_b15_clicked();

    void on_b21_clicked();

    void on_b22_clicked();

    void on_b23_clicked();

    void on_b24_clicked();

    void on_b25_clicked();

    void on_b31_clicked();

    void on_b32_clicked();

    void on_b33_clicked();

    void on_b34_clicked();

    void on_b35_clicked();

    void on_b41_clicked();

    void on_b42_clicked();

    void on_b43_clicked();

    void on_b44_clicked();

    void on_b45_clicked();

    void on_b51_clicked();

    void on_b52_clicked();

    void on_b53_clicked();

    void on_b54_clicked();

    void on_b55_clicked();

    void on_duzypoziomo_clicked();



    void on_duzypionowo_clicked();

    void on_srednipionowo_clicked();

    void on_b11_2_clicked();

    void on_b12_2_clicked();

    void on_b13_2_clicked();

    void on_b14_2_clicked();

    void on_b15_2_clicked();

    void on_b21_2_clicked();

    void on_b22_2_clicked();

    void on_b23_2_clicked();

    void on_b24_2_clicked();

    void on_b25_2_clicked();

    void on_b31_2_clicked();

    void on_b32_2_clicked();

    void on_b33_2_clicked();

    void on_b34_2_clicked();

    void on_b35_2_clicked();

    void on_b41_2_clicked();

    void on_b42_2_clicked();

    void on_b43_2_clicked();

    void on_b44_2_clicked();

    void on_b45_2_clicked();

    void on_b51_2_clicked();

    void on_b52_2_clicked();

    void on_b53_2_clicked();

    void on_b54_2_clicked();

    void on_b55_2_clicked();

    void on_zacznijIA_clicked();

    void on_restart_clicked();

    void on_server_clicked();

    void on_wyslij_clicked();

    void on_socket_clicked();

    void on_zablokuj_clicked();



    void on_odpalvoid_clicked();

    void on_wyslijbroadcast_clicked();

    void on_odbierz_broadcast_clicked();

    void on_polacz_broadcast_clicked();

private:
    Ui::MainWindow *ui;

    struct tablica {
      int duzypoziomo=0;
      int duzypionowo=0;
      int srednipoziomo=0;
      int srednipionowo=0;
      int maly=0;
      int x=0;
      int y=0;
      bool trafiony=false;
      int przycisk;


    };


    void setid();
    void przycisk1(int x,int y);
    void przycisk2(int x,int y);
    void losuj();
    void blokuj();
    void blokujtab2();
    void rysujplansze();
    void rysujplanszewroga();
    void ustaw_statki(QString wiadomosc);
    void delay()
    {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    int bylo[7][7]={{0}};
    tablica tab[7][7];
    tablica tab2[7][7];
    int bylstrzal[7][7]={{0}};
    bool statekmaly=false;
    bool stateksrednipoziomo=false;
    bool stateksrednipionowo=false;
    bool statekduzypoziomo=false;
    bool statekduzypionowo=false;
    int duzytrafiony=0;
    int srednitrafiony=0;
    int malytrafiony=0;
    int mojetrafienia=0;
    int twojetrafienia=0;
    int statki_do_ulozenia=3;
    int ia_wie[2]={{0}};
    int ia_wie_ruch=0;
    bool ia_ostani=false;
    bool wygrana=false;
    bool przegrana=false;
    bool sockerustawiony=false;
    bool serverustawiony=false;
    QList<QPushButton*> przyciski;
    QList<QPushButton*> przyciski_2;
    sockettest msocket;
    broadcasttest bbroadcast;
    UPDclient bclient;
    MyServer mserver;

};

#endif // MAINWINDOW_H
