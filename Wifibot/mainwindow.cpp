#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "QtDebug"
#include "move.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Robot = new MyRobot();
    movePanel = new Move(this);
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
}


MainWindow::~MainWindow()
{
    delete ui;
    delete Robot;
    delete movePanel;
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
