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

    this->setFixedSize(1073,625); //setFixedSize(largeur,hauteur)
    ui->setupUi(this);

}
//Actualisation du capteurs de vitesse
void MainWindow::updateSpeed(QByteArray data) {
    long odometryL = ((long)data[8]<<24)+((long)data[7]<<16)+((long)data[6]<<8)+((long)data[5]);
    long odometryR = ((long)data[16]<<24)+((long)data[15]<<16)+((long)data[14]<<8)+((long)data[13]);

    double speedL;
    if (odometryLBefore<odometryL) {
        speedL = (odometryL - odometryLBefore) * 3.14 * 0.135 / 0.025;
        odometryLBefore = odometryL;
    }
    else {
        speedL = (0xFFFFFFFF-odometryLBefore + odometryL) * 3.14 * 0.135 / 0.025;
        odometryLBefore = odometryL;
    }

    double speedR;
    if (odometryRBefore<odometryR) {
        speedR = (odometryR - odometryRBefore) * 3.14 * 0.135 / 0.025;
        odometryRBefore = odometryR;
    }
    else {
        speedR = (0xFFFFFFFF-odometryRBefore + odometryR) * 3.14 * 0.135 / 0.025;
        odometryRBefore = odometryR;
    }

    double speed = (speedL + speedR) / 20000;


    if (speed > 1000000)
        speed = 0;

    QString textSpeed = QString::number(speed) + " m/s";
    ui->speed->setText(textSpeed);
    qDebug() << "Speed: " << speed;
}

//Actualisation des capteurs de position
void MainWindow::updateCaptor(QByteArray data) {
    unsigned char irRF = (unsigned char)data[3];
    //unsigned char irRB = (unsigned char)data[4];

    unsigned char irLF = (unsigned char)data[11];
    unsigned char irLB = (unsigned char)data[12];

    qDebug() << "Captor: " << irLF << "; " << irRF << "; " << irLB;

    if (irLF >= 180) {
        ui->sensorFL->setValue(100);
    }
    else {
        ui->sensorFL->setValue(irLF * 100 / 180);
    }

    if (irRF >= 180) {
        ui->sensorFR->setValue(100);
    }
    else {
        ui->sensorFR->setValue(irRF * 100 / 180);
    }

    if (irLB >= 180) {
        ui->sensorBL->setValue(100);
    }
    else {
        ui->sensorBL->setValue(irLB * 100 / 180);
    }

}

void MainWindow::updateWindows(const QByteArray data)
{
    updateSpeed(data);
    updateCaptor(data);
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
    Robot->move(Direction::FORWARD,ui->setSpeed->value());
    qDebug() << ui->setSpeed->value();
}


void MainWindow::on_Forward_released()
{
    Robot->move();
}


void MainWindow::on_Right_pressed()
{
    Robot->move(Direction::RIGHT, ui->setSpeed->value());
    qDebug() << ui->setSpeed->value();

}


void MainWindow::on_Right_released()
{
    Robot->move();
}


void MainWindow::on_Back_pressed()
{
    Robot->move(Direction::BACKWARD, ui->setSpeed->value());
    qDebug() << ui->setSpeed->value();

}


void MainWindow::on_Back_released()
{
    Robot->move();
}


void MainWindow::on_Left_pressed()
{
    Robot->move(Direction::LEFT, ui->setSpeed->value());
    qDebug() << ui->setSpeed->value();

}


void MainWindow::on_Left_released()
{
    Robot->move();
}

void MainWindow::on_Camera_Haut_clicked()
{
    camera->move(0);
}


void MainWindow::on_Camera_Droite_clicked()
{
    camera->move(2);
}


void MainWindow::on_Camera_Bas_clicked()
{
    camera->move(3);
}


void MainWindow::on_Camera_Gauche_clicked()
{
    camera->move(1);
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

Direction MainWindow::toDirection(double x, double y) {
    if((x*x)+(y*y) <= (0.1*0.1))
        return Direction::NONE;
    else if ((-2*x)>=y && (2*x)>=y)
        return Direction::FORWARD;
    else if ((2*x)<=y && (0.5*x)>=y)
        return Direction::FORWARD_RIGHT;
    else if ((0.5*x)<=y && (-0.5*x)>=y)
        return Direction::RIGHT;
    else if ((-0.5*x)<=y && (-2*x)>=y)
        return Direction::BACKWARD_RIGHT;
    else if ((-2*x)<=y && (2*x)<=y)
        return Direction::BACKWARD;
    else if ((2*x)>=y && (0.5*x)<=y)
        return Direction::BACKWARD_LEFT;
    else if ((0.5*x)>=y && (-0.5*x)<=y)
        return Direction::LEFT;
    else if ((-0.5*x)>=y && (-2*x)<=y)
        return Direction::FORWARD_LEFT;
    else return Direction::NONE;
}

