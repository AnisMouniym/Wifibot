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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connect_clicked()
{
    Robot->doConnect();
}

void MainWindow::on_Disconnect_clicked()
{
    Robot->disConnect();
}

void MainWindow::checkConnection()
{
    qDebug()<<"Test";
    if(!Robot->isConnected)
    {
        if(Robot->doConnect())
            bConnect->setText("Disconnect");
    }
    else
    {
        Robot->disConnect();
        bConnect->setText("Connect");
    }
}
