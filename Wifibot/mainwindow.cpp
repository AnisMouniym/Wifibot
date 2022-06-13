#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include "QtDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Robot = new MyRobot();
    camera = new Camera("http://192.168.1.106:8080", this);
    camera->move(QPoint(560,140));

    this->setFixedSize(800,400); //setFixedSize(largeur,hauteur)
    ui->setupUi(this);

// Connexion avec les sliders
//    connect(movePanel, SIGNAL(updateMove(unsigned char,unsigned char,unsigned char)), Robot, SLOT(move(unsigned char,unsigned char,unsigned char)));
//    connect(movePanel, SIGNAL(updateVelocityRight(unsigned char)), Robot, SLOT(velocityRight(unsigned char)));
//    connect(movePanel, SIGNAL(updateVelocityLeft(unsigned char)), Robot, SLOT(velocityLeft(unsigned char)));

// affichage camera (à faire)

// Affichage de la batterie
        lcdBattery = new QLCDNumber(this);
        lcdBattery->setDigitCount(3);
        lcdBattery->setGeometry(QRect(5,5,40,30));
        lcdBattery->display(0);

}

void MainWindow::updateBattery(quint8 battery)
{
    if(battery > 175)
    {
        lcdBattery->display(100);
        lcdBattery->setStyleSheet("background-color: dark; color: rgb(0, 255, 0); border-radius: 10px;border-width: 2px");
    }
    else if(battery >100)
    {
        lcdBattery->display(100);
        lcdBattery->setStyleSheet("background-color: dark; color: rgb(255, 0, 0); border-radius: 10px;border-width: 2px");
    }
    else
    {
        lcdBattery->setStyleSheet("background-color: dark; color: rgb(255, 0, 0); border-radius: 10px;border-width: 2px");
        lcdBattery->display(battery);
    }

}

void MainWindow::updateWindows(const QByteArray data)
{
    this->updateBattery(data[2]);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete Robot;
    delete camera;
}

//Mise en place des bouttons

void MainWindow::on_Forward_pressed()
{
    Robot->move(Direction::FORWARD, 0x7F);
}


void MainWindow::on_Forward_released()
{
    Robot->move();
}


void MainWindow::on_Right_pressed()
{
    Robot->move(Direction::RIGHT, 0x7F);
}


void MainWindow::on_Right_released()
{
    Robot->move();
}


void MainWindow::on_Back_pressed()
{
    Robot->move(Direction::BACKWARD, 0x7F);
}


void MainWindow::on_Back_released()
{
    Robot->move();
}


void MainWindow::on_Left_pressed()
{
    Robot->move(Direction::LEFT, 0x7F);
}


void MainWindow::on_Left_released()
{
    Robot->move();
}

//Boutton de connexion
void MainWindow::on_Connexion_clicked()
{
    if(Robot->isConnected) {
        Robot->disConnect();
    }
    else {
        if(!Robot->isConnected){
        Robot->doConnect();        }
    }

    if (Robot->isConnected) {
        ui->Connexion->setText("Connected");
    }
    else {
        ui->Connexion->setText("Disconnected");
    }
}
