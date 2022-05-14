#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myrobot.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_Connect_clicked();
    void on_Disconnect_clicked();
    void checkConnection();

private:
    Ui::MainWindow *ui;
    MyRobot *Robot;
    QPushButton *_connect;
};
#endif // MAINWINDOW_H
