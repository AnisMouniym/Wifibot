#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "QtDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Robot = new MyRobot();
    ui->setupUi(this);
    _connect = new QPushButton("Disconnected", this);
    _connect->setStyleSheet("background-color: red; border-style: outset; border-radius: 10px; color: black");
    _connect->setGeometry(QRect(200,10,300,20));

    connect(_connect, SIGNAL(clicked()), this, SLOT(checkConnection()));
    connect(Robot, SIGNAL(updateUI(QByteArray)), this, SLOT(updateWindows(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::checkConnection()
{
    qDebug()<<"Test";
    if(!Robot->isConnected)
    {
        if(Robot->doConnect()){
            _connect->setStyleSheet("background-color: red; border-style: outset; border-radius: 10px; color: black");
    }
    }
    else
    {
        Robot->disConnect();
        _connect->setText("Connected");
        _connect->setStyleSheet("background-color: green; border-style: outset; border-radius: 10px; color: black");
    }
}
