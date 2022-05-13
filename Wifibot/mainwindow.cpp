#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myrobot.h"
#include "QtDebug"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_Connect_clicked()
{
    Robot.doConnect();
}

void MainWindow::on_Disconnect_clicked()
{
    Robot.disConnect();
}

