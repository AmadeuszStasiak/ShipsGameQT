#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/zbyszek.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    setid();
    ui->duzypionowo->setVisible(false);
    ui->duzypoziomo->setVisible(false);
    ui->srednipionowo->setVisible(false);
    ui->srednipoziomo->setVisible(false);
    blokujtab2();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::przycisk1(int x, int y)
{
    if(statekmaly==true)
    {
        tab[x][y].x=1;
        tab[x][y].maly=1;
        tab[x-1][y].x=2;
        tab[x+1][y].x=2;
        tab[x][y+1].x=2;
        tab[x][y-1].x=2;
        tab[x-1][y+1].x=2;
        tab[x-1][y-1].x=2;
        tab[x+1][y+1].x=2;
        tab[x+1][y-1].x=2;

        statekmaly=false;
        blokuj();
        rysujplansze();
    }
    else if(stateksrednipoziomo==true)
    {
        tab[x][y].x=1;
        tab[x][y+1].x=1;

        tab[x][y].srednipoziomo=1;
        tab[x][y+1].srednipoziomo=2;


        tab[x-1][y].x=2;
        tab[x+1][y].x=2;
        tab[x][y-1].x=2;
        tab[x][y+2].x=2;
        tab[x-1][y+1].x=2;
        tab[x+1][y+1].x=2;
        tab[x-1][y+2].x=2;
        tab[x+1][y+2].x=2;
        tab[x-1][y-1].x=2;
        tab[x+1][y-1].x=2;



        stateksrednipoziomo=false;
        blokuj();

        rysujplansze();
    }
    else if(stateksrednipionowo==true)
    {
        tab[x][y].x=1;
        tab[x+1][y].x=1;

        tab[x][y].srednipionowo=1;
        tab[x+1][y].srednipionowo=2;


        tab[x-1][y].x=2;
        tab[x+2][y].x=2;
        tab[x][y-1].x=2;
        tab[x][y+1].x=2;
        tab[x+1][y-1].x=2;
        tab[x+1][y+1].x=2;
        tab[x+2][y+1].x=2;
        tab[x+2][y-1].x=2;
        tab[x-1][y+1].x=2;
        tab[x-1][y-1].x=2;

        stateksrednipionowo=false;
        blokuj();

        rysujplansze();
    }
    else if(statekduzypionowo==true)
    {
        tab[x-1][y].x=1;
        tab[x][y].x=1;
        tab[x+1][y].x=1;

        tab[x-1][y].duzypionowo=1;
        tab[x][y].duzypionowo=2;
        tab[x+1][y].duzypionowo=3;


        tab[x-2][y].x=2;
        tab[x-1][y-1].x=2;
        tab[x-1][y+1].x=2;
        tab[x][y-1].x=2;
        tab[x][y+1].x=2;
        tab[x+1][y-1].x=2;
        tab[x+1][y+1].x=2;
        tab[x+2][y].x=2;
        tab[x+2][y-1].x=2;
        tab[x+2][y+1].x=2;
        tab[x-2][y-1].x=2;
        tab[x-2][y+1].x=2;


        statekduzypionowo=false;
        blokuj();

        rysujplansze();
    }
    else if(statekduzypoziomo==true)
    {
        tab[x][y-1].x=1;
        tab[x][y].x=1;
        tab[x][y+1].x=1;

        tab[x][y-1].duzypoziomo=1;
        tab[x][y].duzypoziomo=2;
        tab[x][y+1].duzypoziomo=3;


        tab[x][y-2].x=2;
        tab[x-1][y-1].x=2;
        tab[x+1][y-1].x=2;
        tab[x-1][y].x=2;
        tab[x+1][y].x=2;
        tab[x-1][y+1].x=2;
        tab[x+1][y+1].x=2;
        tab[x][y+2].x=2;
        tab[x-1][y+2].x=2;
        tab[x+1][y+2].x=2;
        tab[x+1][y-2].x=2;
        tab[x-1][y-2].x=2;


        statekduzypoziomo=false;
        blokuj();

        rysujplansze();
    }
    statki_do_ulozenia--;
    if(statki_do_ulozenia==0)
    {
        ui->zacznijIA->setEnabled(true);
        ui->server->setEnabled(true);
        //ui->socket->setEnabled(true);
    }

}

void MainWindow::przycisk2(int x, int y)
{
    tab2[x][y].trafiony=true;
    tab2[x][y].y=1;
    if(tab2[x][y].x==1)
    {
        ui->textBrowser->setText("Trafiłeś !");
        mojetrafienia++;
        if(mojetrafienia==6)
        {   ui->textBrowser->setText("Wygrałeś");
           QMessageBox::information(this,"Wygrałeś","Wygrałeś");
           blokujtab2();
           wygrana=true;
        }
    }else
    {
        ui->textBrowser->setText("Pudło !");
    }

    if(tab2[x][y].duzypionowo!=0||tab2[x][y].duzypoziomo!=0)
    {
        duzytrafiony++;
    }
    else if(tab2[x][y].srednipionowo!=0||tab2[x][y].srednipoziomo!=0)
    {
        srednitrafiony++;
    }
    rysujplanszewroga();
    blokujtab2();

    if(serverustawiony==false&&sockerustawiony==false)
    {
       losuj();
       blokuj();
    }else if(serverustawiony==true)
    {
        QString wiadomosc;
        for (int i=1;i<6;i++)
        {
            for (int i2=1;i2<6;i2++)
            {
                qDebug()<<wiadomosc;
                wiadomosc+=QString::number(tab2[i][i2].y);
            }
        }


        mserver.wyslij(wiadomosc);
        for(int i=100;i>0;i++)
        {
            delay();
            wiadomosc=mserver.odbierz();
            if(wiadomosc!="")
            {
                twojetrafienia=0;
                for(int i2=1;i2<6;i2++)
                {
                    for(int i3=1;i3<6;i3++)
                    {

                        QString g1=wiadomosc.mid(0,1);
                        wiadomosc.remove(0,1);
                        tab[i2][i3].trafiony=g1.toInt();
                        if(tab[i2][i3].x==1&&tab[i2][i3].trafiony==1)
                        {
                            twojetrafienia++;
                            if(twojetrafienia==6&&wygrana==false)
                            {   ui->textBrowser->setText("Przegrałeś");
                                 QMessageBox::information(this,"Przegrałeś","Przegrałeś");
                                 blokujtab2();
                                 przegrana=true;
                            }else if(twojetrafienia==6&&wygrana==true)
                            {   ui->textBrowser->setText("A jednak remis");
                                QMessageBox::information(this,"A jednak remis","A jednak remis");
                                blokujtab2();
                                przegrana=true;
                            }
                        }
                    }
                }
                if(przegrana==false)
                {
                    blokuj();
                }

                break;
            }
        }
        rysujplansze();
    }else if(sockerustawiony==true)
    {
        QString wiadomosc;
        for (int i=1;i<6;i++)
        {
            for (int i2=1;i2<6;i2++)
            {
                qDebug()<<wiadomosc;
                wiadomosc+=QString::number(tab2[i][i2].y);
            }
        }


        msocket.wyslij(wiadomosc);
        for(int i=100;i>0;i++)
        {
            delay();
            wiadomosc=msocket.odbierz();
            if(wiadomosc!="")
            {
                twojetrafienia=0;
                for(int i2=1;i2<6;i2++)
                {
                    for(int i3=1;i3<6;i3++)
                    {

                        QString g1=wiadomosc.mid(0,1);
                        wiadomosc.remove(0,1);
                        tab[i2][i3].trafiony=g1.toInt();
                        if(tab[i2][i3].x==1&&tab[i2][i3].trafiony==1)
                        {
                            twojetrafienia++;
                            if(twojetrafienia==6&&wygrana==false)
                            {ui->textBrowser->setText("Przegrales");
                                 QMessageBox::information(this,"przegrales","przegrales");
                                 blokujtab2();
                                 przegrana=true;
                            }else if(twojetrafienia==6&&wygrana==true)
                            {ui->textBrowser->setText("A jednak remis");
                                QMessageBox::information(this,"A jednak remis","A jednak remis");
                                blokujtab2();
                                przegrana=true;
                            }
                        }
                    }
                }
                if(przegrana==false)
                {
                    blokuj();
                }

                break;
            }
        }
        rysujplansze();
    }

}

void MainWindow::losuj()
{

    if(ia_ostani==true)
    {
        if(ia_wie[0]+1<6&&bylstrzal[ia_wie[0]+1][ia_wie[1]]!=1)
        {
            tab[ia_wie[0]+1][ia_wie[1]].trafiony=true;
            bylstrzal[ia_wie[0]+1][ia_wie[1]]=1;
            if(tab[ia_wie[0]+1][ia_wie[1]].x==1)
            {
                twojetrafienia++;
                if(twojetrafienia==6&&wygrana==false)
                {ui->textBrowser->setText("Przegrales");
                    blokujtab2();
                    QMessageBox::information(this,"przegrales","przegrales");
                    blokujtab2();
                }else if(twojetrafienia==6&&wygrana==true)
                {ui->textBrowser->setText("A jednak remis");
                    blokujtab2();
                    QMessageBox::information(this,"A jednak remis","A jednak remis");
                }
                ia_wie[0]+=1;

            }

        }else if(ia_wie[0]-1>0&&bylstrzal[ia_wie[0]-1][ia_wie[1]]!=1)
        {
            tab[ia_wie[0]-1][ia_wie[1]].trafiony=true;
            bylstrzal[ia_wie[0]-1][ia_wie[1]]=1;
            if(tab[ia_wie[0]-1][ia_wie[1]].x==1)
            {
                twojetrafienia++;
                if(twojetrafienia==6&&wygrana==false)
                {ui->textBrowser->setText("Przegrales");
                    blokujtab2();
                    QMessageBox::information(this,"przegrales","przegrales");
                    blokujtab2();
                }else if(twojetrafienia==6&&wygrana==true)
                {ui->textBrowser->setText("A jednak remis");
                    blokujtab2();
                    QMessageBox::information(this,"A jednak remis","A jednak remis");
                }

                ia_wie[0]-=1;
            }

        }else if(ia_wie[1]+1<6&&bylstrzal[ia_wie[0]][ia_wie[1]+1]!=1)
        {
            tab[ia_wie[0]][ia_wie[1]+1].trafiony=true;
            bylstrzal[ia_wie[0]][ia_wie[1]+1]=1;
            if(tab[ia_wie[0]][ia_wie[1]+1].x==1)
            {
                twojetrafienia++;
                if(twojetrafienia==6&&wygrana==false)
                {ui->textBrowser->setText("Przegrales");
                            blokujtab2();
                    QMessageBox::information(this,"przegrales","przegrales");
                    blokujtab2();
                }else if(twojetrafienia==6&&wygrana==true)
                {ui->textBrowser->setText("A jednak remis");
                    blokujtab2();
                    QMessageBox::information(this,"A jednak remis","A jednak remis");
                }

                ia_wie[1]+=1;
            }

        }else if(ia_wie[1]-1>0&&bylstrzal[ia_wie[0]][ia_wie[1]-1]!=1)
        {
            tab[ia_wie[0]][ia_wie[1]-1].trafiony=true;
            bylstrzal[ia_wie[0]][ia_wie[1]-1]=1;
            if(tab[ia_wie[0]][ia_wie[1]-1].x==1)
            {
                twojetrafienia++;
                if(twojetrafienia==6&&wygrana==false)
                {ui->textBrowser->setText("Przegrales");
                    blokujtab2();
                    QMessageBox::information(this,"przegrales","przegrales");
                    blokujtab2();
                }else if(twojetrafienia==6&&wygrana==true)
                {ui->textBrowser->setText("A jednak remis");
                    blokujtab2();
                    QMessageBox::information(this,"A jednak remis","A jednak remis");
                }

                ia_wie[1]-=1;
            }

        }else
        {
            int liczba1;
            int liczba2;
            do
            {
                liczba1=qrand()%5+1;
                liczba2=qrand()%5+1;
            }while(bylstrzal[liczba1][liczba2]==1);

            bylstrzal[liczba1][liczba2]=1;
            tab[liczba1][liczba2].trafiony=true;
            if(tab[liczba1][liczba2].x==1)
            {
                twojetrafienia++;
                if(twojetrafienia==6&&wygrana==false)
                {ui->textBrowser->setText("Przegrales");
                    blokujtab2();
                    QMessageBox::information(this,"przegrales","przegrales");
                    blokujtab2();
                }else if(twojetrafienia==6&&wygrana==true)
                {ui->textBrowser->setText("A jednak remis");
                    blokujtab2();
                    QMessageBox::information(this,"A jednak remis","A jednak remis");
                }
                ia_wie[0]=liczba1;
                ia_wie[1]=liczba2;
                ia_ostani=true;
            } else
            {
                ia_ostani=false;
            }
        }

    }else
    {

        int liczba1;
        int liczba2;
        do
        {
            liczba1=qrand()%5+1;
            liczba2=qrand()%5+1;
        }while(bylstrzal[liczba1][liczba2]==1);

        bylstrzal[liczba1][liczba2]=1;
        tab[liczba1][liczba2].trafiony=true;
        if(tab[liczba1][liczba2].x==1)
        {
            twojetrafienia++;
            if(twojetrafienia==6&&wygrana==false)
            {ui->textBrowser->setText("Przegrales");
                blokujtab2();
                QMessageBox::information(this,"przegrales","przegrales");
                blokujtab2();
            }else if(twojetrafienia==6&&wygrana==true)
            {ui->textBrowser->setText("A jednak remis");
                blokujtab2();
                QMessageBox::information(this,"A jednak remis","A jednak remis");
            }
            ia_wie[0]=liczba1;
            ia_wie[1]=liczba2;
            ia_ostani=true;
        }else
        {
            ia_ostani=false;
        }
    }
    rysujplansze();
}


void MainWindow::blokuj()
{
    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            if(tab[i][i2].x==2)
               przyciski[tab[i][i2].przycisk]->setEnabled(false);

            else
                przyciski[tab[i][i2].przycisk]->setEnabled(true);
        }
    }


    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            if(tab2[i][i2].trafiony==true)
               przyciski_2[tab[i][i2].przycisk]->setEnabled(false);

            else
                przyciski_2[tab[i][i2].przycisk]->setEnabled(true);
        }
    }
}

void MainWindow::blokujtab2()
{
    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
              przyciski_2[tab[i][i2].przycisk]->setEnabled(false);
    }
}

void MainWindow::rysujplansze()
{
    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            if(tab[i][i2].x==1&&tab[i][i2].maly==1&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekmaly.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].maly==1&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekmalytrafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipoziomo==1&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipoziomo1.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipoziomo==1&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipoziomo1trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipoziomo==2&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipoziomo2.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipoziomo==2&&tab[i][i2].trafiony==true)
                 przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipoziomo2trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipionowo==1&&tab[i][i2].trafiony==false)
                 przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipionowo1.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipionowo==1&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipionowo1trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipionowo==2&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipionowo2.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].srednipionowo==2&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipionowo2trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypoziomo==1&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo1.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypoziomo==1&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo1trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypoziomo==2&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo2.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypoziomo==2&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo2trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypoziomo==3&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo3.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypoziomo==3&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo3trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypionowo==3&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo3.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypionowo==3&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo3trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypionowo==2&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo2.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypionowo==2&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo2trafiony.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypionowo==1&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo1.png);");

            else if(tab[i][i2].x==1&&tab[i][i2].duzypionowo==1&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo1trafiony.png);");

            else if(tab[i][i2].x==0&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:woda.png);");

            else if(tab[i][i2].x==0&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:wodatrafiona.png);");

            else if(tab[i][i2].x==2&&tab[i][i2].trafiony==false)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:wodaszara.png);");

            else if(tab[i][i2].x==2&&tab[i][i2].trafiony==true)
                przyciski[tab[i][i2].przycisk]->setStyleSheet("border-image: url(:wodatrafiona.png);");
        }
    }
}

void MainWindow::rysujplanszewroga()
{
    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            if(tab2[i][i2].trafiony==false)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:woda.png);");

            else if(tab2[i][i2].x==0&&tab2[i][i2].trafiony==true)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:wodatrafiona.png);");

            else if(tab2[i][i2].x==1&&tab2[i][i2].maly==1&&tab2[i][i2].trafiony==true)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekmalytrafiony.png);");

            else if(tab2[i][i2].x==1&&tab2[i][i2].trafiony==true&&tab2[i][i2].maly==0)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statektrafiony.png);");

            if(duzytrafiony==3&&tab2[i][i2].trafiony==true&&tab2[i][i2].duzypionowo==1)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo1trafiony.png);");

            if(duzytrafiony==3&&tab2[i][i2].trafiony==true&&tab2[i][i2].duzypionowo==2)
                 przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo2trafiony.png);");

            if(duzytrafiony==3&&tab2[i][i2].trafiony==true&&tab2[i][i2].duzypionowo==3)
              przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypionowo3trafiony.png);");

            if(duzytrafiony==3&&tab2[i][i2].trafiony==true&&tab2[i][i2].duzypoziomo==1)
                 przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo1trafiony.png);");

            if(duzytrafiony==3&&tab2[i][i2].trafiony==true&&tab2[i][i2].duzypoziomo==2)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo2trafiony.png);");

            if(duzytrafiony==3&&tab2[i][i2].trafiony==true&&tab2[i][i2].duzypoziomo==3)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:statekduzypoziomo3trafiony.png);");

            if(srednitrafiony==2&&tab2[i][i2].trafiony==true&&tab2[i][i2].srednipionowo==1)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipionowo1trafiony.png);");

            if(srednitrafiony==2&&tab2[i][i2].trafiony==true&&tab2[i][i2].srednipionowo==2)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipionowo2trafiony.png);");

            if(srednitrafiony==2&&tab2[i][i2].trafiony==true&&tab2[i][i2].srednipoziomo==1)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipoziomo1trafiony.png);");

            if(srednitrafiony==2&&tab2[i][i2].trafiony==true&&tab2[i][i2].srednipoziomo==2)
                przyciski_2[tab2[i][i2].przycisk]->setStyleSheet("border-image: url(:stateksrednipoziomo2trafiony.png);");
        }
    }
}


void MainWindow::on_maly_clicked()
{
    statekmaly=true;
    ui->maly->setVisible(false);
    ui->srednipionowo->setVisible(true);
    ui->srednipoziomo->setVisible(true);

}

void MainWindow::on_srednipoziomo_clicked()
{
    stateksrednipoziomo=true;
    ui->b15->setEnabled(false);
    ui->b25->setEnabled(false);
    ui->b35->setEnabled(false);
    ui->b45->setEnabled(false);
    ui->b55->setEnabled(false);
    ui->srednipionowo->setVisible(false);
    ui->srednipoziomo->setVisible(false);
    ui->duzypionowo->setVisible(true);
    ui->duzypoziomo->setVisible(true);

}
void MainWindow::on_duzypoziomo_clicked()
{
    statekduzypoziomo=true;
    ui->b15->setEnabled(false);
    ui->b25->setEnabled(false);
    ui->b35->setEnabled(false);
    ui->b45->setEnabled(false);
    ui->b55->setEnabled(false);
    ui->b11->setEnabled(false);
    ui->b21->setEnabled(false);
    ui->b31->setEnabled(false);
    ui->b41->setEnabled(false);
    ui->b51->setEnabled(false);
    ui->duzypionowo->setVisible(false);
    ui->duzypoziomo->setVisible(false);


}
void MainWindow::on_duzypionowo_clicked()
{
     statekduzypionowo=true;
     ui->b51->setEnabled(false);
     ui->b52->setEnabled(false);
     ui->b53->setEnabled(false);
     ui->b54->setEnabled(false);
     ui->b55->setEnabled(false);
     ui->duzypionowo->setVisible(false);
     ui->duzypoziomo->setVisible(false);

}
void MainWindow::on_srednipionowo_clicked()
{
    stateksrednipionowo=true;
    ui->b51->setEnabled(false);
    ui->b52->setEnabled(false);
    ui->b53->setEnabled(false);
    ui->b54->setEnabled(false);
    ui->b55->setEnabled(false);
    ui->srednipionowo->setVisible(false);
    ui->srednipoziomo->setVisible(false);
    ui->duzypionowo->setVisible(true);
    ui->duzypoziomo->setVisible(true);

}



void MainWindow::on_zacznijIA_clicked()
{
    for(int i=0;i<25;i++)
    {
        przyciski_2[i]->setEnabled(true);

    }
    ui->zacznijIA->setVisible(false);
    //ui->socket->setVisible(false);
    ui->server->setVisible(false);
    QTime now = QTime::currentTime();
    qsrand(now.msec());

    int poziompion=qrand()%2;
    int liczba1=qrand()%3+2;
    int liczba2=qrand()%3+2;

    if(poziompion==1)
    {
        tab2[liczba1][liczba2].x=1;
        tab2[liczba1][liczba2].duzypoziomo=2;
        tab2[liczba1][liczba2+1].x=1;
        tab2[liczba1][liczba2+1].duzypoziomo=3;
        tab2[liczba1][liczba2-1].x=1;
        tab2[liczba1][liczba2-1].duzypoziomo=1;

        bylo[liczba1][liczba2]=1;
        bylo[liczba1][liczba2+1]=1;
        bylo[liczba1][liczba2-1]=1;


        bylo[liczba1+1][liczba2]=1;
        bylo[liczba1+1][liczba2+1]=1;
        bylo[liczba1+1][liczba2-1]=1;

        bylo[liczba1-1][liczba2]=1;
        bylo[liczba1-1][liczba2+1]=1;
        bylo[liczba1-1][liczba2-1]=1;


        bylo[liczba1-1][liczba2]=1;
        bylo[liczba1-1][liczba2-1]=1;
        bylo[liczba1-1][liczba2+1]=1;
        bylo[liczba1-1][liczba2-2]=1;
        bylo[liczba1-1][liczba2+2]=1;


        bylo[liczba1+1][liczba2]=1;
        bylo[liczba1-1][liczba2]=1;

    }else if(poziompion==0)
    {
        tab2[liczba1][liczba2].x=1;
        tab2[liczba1][liczba2].duzypionowo=2;
        tab2[liczba1+1][liczba2].x=1;
        tab2[liczba1+1][liczba2].duzypionowo=3;
        tab2[liczba1-1][liczba2].x=1;
        tab2[liczba1-1][liczba2].duzypionowo=1;

        bylo[liczba1][liczba2]=1;
        bylo[liczba1+1][liczba2]=1;
        bylo[liczba1-1][liczba2]=1;

        bylo[liczba1+1][liczba2-1]=1;
        bylo[liczba1-1][liczba2-1]=1;

        bylo[liczba1+1][liczba2+1]=1;
        bylo[liczba1-1][liczba2+1]=1;

        bylo[liczba1-2][liczba2]=1;
        bylo[liczba1-2][liczba2-1]=1;
        bylo[liczba1-2][liczba2+1]=1;


        bylo[liczba1][liczba2-1]=1;
        bylo[liczba1][liczba2+1]=1;

    }

    poziompion=qrand()%2;
    do
    {
        liczba1=qrand()%3+2;
        liczba2=qrand()%3+2;
    }while(bylo[liczba1][liczba2]==1);

    if(poziompion==1)
    {
        tab2[liczba1][liczba2].x=1;
        tab2[liczba1][liczba2].srednipionowo=1;
        tab2[liczba1+1][liczba2].x=1;
        tab2[liczba1+1][liczba2].srednipionowo=2;


        bylo[liczba1][liczba2]=1;
        bylo[liczba1][liczba2+1]=1;
        bylo[liczba1][liczba2-1]=1;
        bylo[liczba1+1][liczba2]=1;
        bylo[liczba1+1][liczba2+1]=1;
        bylo[liczba1+1][liczba2-1]=1;
        bylo[liczba1-1][liczba2]=1;
        bylo[liczba1+2][liczba2]=1;

    }else if(poziompion==0)
    {
        tab2[liczba1][liczba2].x=1;
        tab2[liczba1][liczba2].srednipoziomo=1;
        tab2[liczba1][liczba2+1].x=1;
        tab2[liczba1][liczba2+1].srednipoziomo=2;


        bylo[liczba1][liczba2]=1;
        bylo[liczba1][liczba2+1]=1;
        bylo[liczba1][liczba2-1]=1;
        bylo[liczba1][liczba2+1]=1;
        bylo[liczba1-1][liczba2+1]=1;
        bylo[liczba1+1][liczba2+1]=1;
        bylo[liczba1+1][liczba2]=1;
        bylo[liczba1-2][liczba2]=1;

    }
    do
    {
        liczba1=qrand()%5+1;
        liczba2=qrand()%5+1;
    }while(bylo[liczba1][liczba2]==1);
    tab2[liczba1][liczba2].x=1;
    tab2[liczba1][liczba2].maly=1;


}



void MainWindow::on_b11_clicked()
{
    przycisk1(1,1);
}

void MainWindow::on_b12_clicked()
{
    przycisk1(1,2);
}

void MainWindow::on_b13_clicked()
{
    przycisk1(1,3);
}

void MainWindow::on_b14_clicked()
{
    przycisk1(1,4);

}

void MainWindow::on_b15_clicked()
{
    przycisk1(1,5);
}

void MainWindow::on_b21_clicked()
{
    przycisk1(2,1);
}

void MainWindow::on_b22_clicked()
{
    przycisk1(2,2);
}

void MainWindow::on_b23_clicked()
{
    przycisk1(2,3);
}

void MainWindow::on_b24_clicked()
{
    przycisk1(2,4);
}

void MainWindow::on_b25_clicked()
{
    przycisk1(2,5);
}

void MainWindow::on_b31_clicked()
{
    przycisk1(3,1);
}

void MainWindow::on_b32_clicked()
{
    przycisk1(3,2);
}

void MainWindow::on_b33_clicked()
{
    przycisk1(3,3);
}

void MainWindow::on_b34_clicked()
{
    przycisk1(3,4);
}

void MainWindow::on_b35_clicked()
{
    przycisk1(3,5);
}

void MainWindow::on_b41_clicked()
{
    przycisk1(4,1);
}

void MainWindow::on_b42_clicked()
{
    przycisk1(4,2);
}

void MainWindow::on_b43_clicked()
{
    przycisk1(4,3);
}

void MainWindow::on_b44_clicked()
{
    przycisk1(4,4);
}

void MainWindow::on_b45_clicked()
{
    przycisk1(4,5);
}

void MainWindow::on_b51_clicked()
{
    przycisk1(5,1);
}

void MainWindow::on_b52_clicked()
{
    przycisk1(5,2);
}

void MainWindow::on_b53_clicked()
{
    przycisk1(5,3);
}

void MainWindow::on_b54_clicked()
{
    przycisk1(5,4);
}

void MainWindow::on_b55_clicked()
{
    przycisk1(5,5);
}









void MainWindow::on_b11_2_clicked()
{
    przycisk2(1,1);
}

void MainWindow::on_b12_2_clicked()
{
    przycisk2(1,2);
}

void MainWindow::on_b13_2_clicked()
{
    przycisk2(1,3);
}

void MainWindow::on_b14_2_clicked()
{
    przycisk2(1,4);
}

void MainWindow::on_b15_2_clicked()
{
    przycisk2(1,5);
}

void MainWindow::on_b21_2_clicked()
{
    przycisk2(2,1);
}

void MainWindow::on_b22_2_clicked()
{
    przycisk2(2,2);
}

void MainWindow::on_b23_2_clicked()
{
    przycisk2(2,3);
}

void MainWindow::on_b24_2_clicked()
{
    przycisk2(2,4);
}

void MainWindow::on_b25_2_clicked()
{
    przycisk2(2,5);
}

void MainWindow::on_b31_2_clicked()
{
    przycisk2(3,1);
}

void MainWindow::on_b32_2_clicked()
{
    przycisk2(3,2);
}

void MainWindow::on_b33_2_clicked()
{
    przycisk2(3,3);
}

void MainWindow::on_b34_2_clicked()
{
    przycisk2(3,4);
}

void MainWindow::on_b35_2_clicked()
{
    przycisk2(3,5);
}

void MainWindow::on_b41_2_clicked()
{
    przycisk2(4,1);
}

void MainWindow::on_b42_2_clicked()
{
    przycisk2(4,2);
}

void MainWindow::on_b43_2_clicked()
{
    przycisk2(4,3);
}

void MainWindow::on_b44_2_clicked()
{
    przycisk2(4,4);
}

void MainWindow::on_b45_2_clicked()
{
    przycisk2(4,5);
}

void MainWindow::on_b51_2_clicked()
{
    przycisk2(5,1);
}

void MainWindow::on_b52_2_clicked()
{
    przycisk2(5,2);
}

void MainWindow::on_b53_2_clicked()
{
    przycisk2(5,3);
}

void MainWindow::on_b54_2_clicked()
{
    przycisk2(5,4);
}

void MainWindow::on_b55_2_clicked()
{
    przycisk2(5,5);
}



void MainWindow::on_restart_clicked()
{
   for(int i=0;i<7;i++)
    {
        for(int i2=0;i2<7;i2++)
        {
            tab[i][i2].x=0;
            tab2[i][i2].x=0;

            tab[i][i2].duzypionowo=0;
            tab2[i][i2].duzypionowo=0;
            tab[i][i2].duzypoziomo=0;
            tab2[i][i2].duzypoziomo=0;
            tab2[i][i2].srednipionowo=0;
            tab[i][i2].srednipionowo=0;
            tab[i][i2].srednipoziomo=0;
            tab2[i][i2].srednipoziomo=0;

            tab[i][i2].maly=0;
            tab2[i][i2].maly=0;
            tab[i][i2].trafiony=0;
            tab2[i][i2].trafiony=0;

            bylo[i][i2]=0;

            qDebug()<<i<<i2;

        }
    }
    srednitrafiony=0;
    duzytrafiony=0;

    ui->srednipoziomo->setVisible(true);
    ui->srednipionowo->setVisible(true);
    ui->duzypoziomo->setVisible(true);
    ui->duzypionowo->setVisible(true);
    ui->maly->setVisible(true);
    rysujplansze();
    rysujplanszewroga();
    blokuj();
}

void MainWindow::ustaw_statki(QString wiadomosc)
{

    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            QString g1;
            g1=wiadomosc.mid(0,3);
            wiadomosc.remove(0,3);
            QString g2;
            g2=g1.mid(0,1);
            g1.remove(0,1);
            QString g3;
            g3=g1.mid(0,1);
            g1.remove(0,1);
            QString g4;
            g4=g1.mid(0,1);
            g1.remove(0,1);

            if(g2=="1")
            {
                tab2[i][i2].x=1;
                qDebug()<<tab2[i][i2].x;
            }
            if(g3=="5")
            {
                tab2[i][i2].maly=g4.toInt();
            }
            if(g3=="6")
            {
                tab2[i][i2].srednipoziomo=g4.toInt();
            }
            if(g3=="7")
            {
                tab2[i][i2].srednipionowo=g4.toInt();
            }if(g3=="8")
            {
                tab2[i][i2].duzypoziomo=g4.toInt();
            }if(g3=="9")
            {
                tab2[i][i2].duzypionowo=g4.toInt();
            }

        }
    }



}

void MainWindow::on_server_clicked()
{

    bclient.odbierz();
    if(bclient.adres!="0")
    {
        for(int i=0;i<25;i++)
        {
            przyciski_2[i]->setEnabled(true);

        }
        qDebug()<<"jest adres";
        msocket.adres=bclient.adres;
        ui->textBrowser->setText("Wyszukiwanie przeciwnika");
        ui->zacznijIA->setVisible(false);
       // ui->socket->setVisible(false);
        ui->server->setVisible(false);
        sockerustawiony=true;
        msocket.znajdz_polaczenie();
        QString wiadomosc;
        for (int i=1;i<6;i++)
        {
            for (int i2=1;i2<6;i2++)
            {
                wiadomosc+=QString::number(tab[i][i2].x);
                if(tab[i][i2].maly==1)
                {

                     wiadomosc+=QString::number(51);
                }else if(tab[i][i2].duzypionowo==1)
                {
                     wiadomosc+=QString::number(91);
                }else if(tab[i][i2].duzypionowo==2)
                {
                     wiadomosc+=QString::number(92);
                }else if(tab[i][i2].duzypionowo==3)
                {
                     wiadomosc+=QString::number(93);
                }else if(tab[i][i2].duzypoziomo==1)
                {
                     wiadomosc+=QString::number(81);
                }else if(tab[i][i2].duzypoziomo==2)
                {
                     wiadomosc+=QString::number(82);
                }else if(tab[i][i2].duzypoziomo==3)
                {
                     wiadomosc+=QString::number(83);
                }else if(tab[i][i2].srednipionowo==1)
                {
                     wiadomosc+=QString::number(71);
                }else if(tab[i][i2].srednipionowo==2)
                {
                     wiadomosc+=QString::number(72);
                }else if(tab[i][i2].srednipoziomo==1)
                {
                     wiadomosc+=QString::number(61);
                }else if(tab[i][i2].srednipoziomo==2)
                {
                     wiadomosc+=QString::number(62);
                }else
                {
                    wiadomosc+=QString::number(11);
                }

            }
        }
        msocket.wyslij(wiadomosc);
        QString wiadomosc1;
        for(int i=10;i>0;i--)
        {
            delay();

            wiadomosc1=msocket.odbierz();
            if(wiadomosc1!="")
            {
                ustaw_statki(wiadomosc1);
                ui->textBrowser->setText("Znaleziono przeciwnika");
                break;
            }
        }


    }
    else
    {
        qDebug()<<"nie ma adresu";
        ui->zacznijIA->setVisible(false);
        //ui->socket->setVisible(false);
        ui->server->setVisible(false);
        serverustawiony=true;
        mserver.serverStart();
        for(int i=0;i<100;i++)
        {
            ui->textBrowser->setText("Wyszukiwanie przeciwnika");

            bbroadcast.wyslij();
            delay();
            if(mserver.czy_jest==true)
            {
                for(int i=0;i<25;i++)
                {
                    przyciski_2[i]->setEnabled(true);

                }
                break;
            }

        }
        QString wiadomosc;
        for (int i=1;i<6;i++)
        {
            for (int i2=1;i2<6;i2++)
            {
                wiadomosc+=QString::number(tab[i][i2].x);
                if(tab[i][i2].maly==1)
                {

                     wiadomosc+=QString::number(51);
                }else if(tab[i][i2].duzypionowo==1)
                {
                     wiadomosc+=QString::number(91);
                }else if(tab[i][i2].duzypionowo==2)
                {
                     wiadomosc+=QString::number(92);
                }else if(tab[i][i2].duzypionowo==3)
                {
                     wiadomosc+=QString::number(93);
                }else if(tab[i][i2].duzypoziomo==1)
                {
                     wiadomosc+=QString::number(81);
                }else if(tab[i][i2].duzypoziomo==2)
                {
                     wiadomosc+=QString::number(82);
                }else if(tab[i][i2].duzypoziomo==3)
                {
                     wiadomosc+=QString::number(83);
                }else if(tab[i][i2].srednipionowo==1)
                {
                     wiadomosc+=QString::number(71);
                }else if(tab[i][i2].srednipionowo==2)
                {
                     wiadomosc+=QString::number(72);
                }else if(tab[i][i2].srednipoziomo==1)
                {
                     wiadomosc+=QString::number(61);
                }else if(tab[i][i2].srednipoziomo==2)
                {
                     wiadomosc+=QString::number(62);
                }else
                {
                    wiadomosc+=QString::number(11);
                }

            }
        }


        mserver.wyslij(wiadomosc);
        qDebug()<<wiadomosc;
        wiadomosc=mserver.odbierz();
        ustaw_statki(wiadomosc);
        ui->textBrowser->setText("Znaleziono przeciwnika");
    }
}

void MainWindow::on_socket_clicked()
{



}
void MainWindow::on_wyslij_clicked()
{
    QString wiadomosc;
    for (int i=1;i<6;i++)
    {
        for (int i2=1;i2<6;i2++)
        {
            qDebug()<<wiadomosc;
            wiadomosc+=QString::number(tab2[i][i2].y);
        }
    }


    mserver.wyslij(wiadomosc);


}

void MainWindow::on_zablokuj_clicked()
{
    blokujtab2();
    blokuj();
}

void MainWindow::setid()
{
    ui->b11->setProperty("myId",1);
    przyciski.push_back(ui->b11);
    przyciski.push_back(ui->b12);
    przyciski.push_back(ui->b13);
    przyciski.push_back(ui->b14);
    przyciski.push_back(ui->b15);
    przyciski.push_back(ui->b21);
    przyciski.push_back(ui->b22);
    przyciski.push_back(ui->b23);
    przyciski.push_back(ui->b24);
    przyciski.push_back(ui->b25);
    przyciski.push_back(ui->b31);
    przyciski.push_back(ui->b32);
    przyciski.push_back(ui->b33);
    przyciski.push_back(ui->b34);
    przyciski.push_back(ui->b35);
    przyciski.push_back(ui->b41);
    przyciski.push_back(ui->b42);
    przyciski.push_back(ui->b43);
    przyciski.push_back(ui->b44);
    przyciski.push_back(ui->b45);
    przyciski.push_back(ui->b51);
    przyciski.push_back(ui->b52);
    przyciski.push_back(ui->b53);
    przyciski.push_back(ui->b54);
    przyciski.push_back(ui->b55);

    przyciski_2.push_back(ui->b11_2);
    przyciski_2.push_back(ui->b12_2);
    przyciski_2.push_back(ui->b13_2);
    przyciski_2.push_back(ui->b14_2);
    przyciski_2.push_back(ui->b15_2);
    przyciski_2.push_back(ui->b21_2);
    przyciski_2.push_back(ui->b22_2);
    przyciski_2.push_back(ui->b23_2);
    przyciski_2.push_back(ui->b24_2);
    przyciski_2.push_back(ui->b25_2);
    przyciski_2.push_back(ui->b31_2);
    przyciski_2.push_back(ui->b32_2);
    przyciski_2.push_back(ui->b33_2);
    przyciski_2.push_back(ui->b34_2);
    przyciski_2.push_back(ui->b35_2);
    przyciski_2.push_back(ui->b41_2);
    przyciski_2.push_back(ui->b42_2);
    przyciski_2.push_back(ui->b43_2);
    przyciski_2.push_back(ui->b44_2);
    przyciski_2.push_back(ui->b45_2);
    przyciski_2.push_back(ui->b51_2);
    przyciski_2.push_back(ui->b52_2);
    przyciski_2.push_back(ui->b53_2);
    przyciski_2.push_back(ui->b54_2);
    przyciski_2.push_back(ui->b55_2);

    int pomocnicza=0;
    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            tab[i][i2].przycisk=pomocnicza;
            pomocnicza++;
        }
    }
    pomocnicza=0;
    for(int i=1;i<6;i++)
    {
        for(int i2=1;i2<6;i2++)
        {
            tab2[i][i2].przycisk=pomocnicza;
            pomocnicza++;
        }
    }

}


void MainWindow::on_odpalvoid_clicked()
{
    setid();
}

void MainWindow::on_wyslijbroadcast_clicked()
{
    bbroadcast.wyslij();

}

void MainWindow::on_odbierz_broadcast_clicked()
{
    bclient.odbierz();
}

void MainWindow::on_polacz_broadcast_clicked()
{
    bclient.polacz();
}
