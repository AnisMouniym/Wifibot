#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRect>
#include "myrobot.h"
#include "QtDebug"
#include "move.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Robot = new MyRobot();
    movePanel = new Move(this);
    movePanel->move(QPoint(10,140));
    camera = new Camera("http://192.168.1.106:8080", this);
    camera->move(QPoint(560,140));

    this->setFixedSize(800,400); //setFixedSize(largeur,hauteur)
    ui->setupUi(this);


//Bouton de connexion
    _connect = new QPushButton("Disconnected", this);
    _connect->setStyleSheet("QPushButton { background-color: red; font: bold 15px; border-radius: 15px; color: black}"
                            "QPushButton:pressed {background-color: rgb(200, 0, 0); border-style: inset;}");
    _connect->setGeometry(QRect(250,10,300,35)); // Qrect(x,y,largeur,hauteur)
    connect(_connect, SIGNAL(clicked()), this, SLOT(checkConnection()));
    connect(Robot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindows(QByteArray)));

// Connexion avec les sliders
    connect(movePanel, SIGNAL(updateMove(unsigned char, unsigned char, unsigned char)), Robot, SLOT(move(unsigned char,unsigned char,unsigned char)));
    connect(movePanel, SIGNAL(updateVelocityRight(unsigned char)), Robot, SLOT(velocityRight(unsigned char)));
    connect(movePanel, SIGNAL(updateVelocityLeft(unsigned char)), Robot, SLOT(velocityLeft(unsigned char)));

// affichage camera (a finir)

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
    delete movePanel;
    delete camera;
}


//Etat de connexion et modification du boutton de connexion
void MainWindow::checkConnection()
{
    qDebug()<<"Test";
    if(!Robot->isConnected)
    {
        if(Robot->doConnect()){
            _connect->setStyleSheet("QPushButton { background-color: red; border-style: none; padding: 40px ; font: bold 20px; border-radius: 10px; color: black}"
                                    "QPushButton:pressed {background-color: rgb(200, 0, 0); border-style: inset;}");
    }
    }
    else
    {
        Robot->disConnect();
        _connect->setText("Connected");
        _connect->setStyleSheet("QPushButton { background-color: green; border-style: none; padding: 40px ; font: bold 20px; border-radius: 10px; color: black}"
                                "QPushButton:pressed {background-color: rgb(200, 0, 0); border-style: inset;}");
    }
}
