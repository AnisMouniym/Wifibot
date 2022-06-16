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
}

void MainWindow::updateWindows(const QByteArray data)
{
//    this->updateBattery(data[2]);
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
