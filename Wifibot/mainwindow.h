#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
//#include <QWebEngineView>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include "myrobot.h"
#include "camera.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateBattery(quint8 battery);
    void updateIRSensor(quint8 lFront, quint8 rFront, quint8 back);


private slots:
//    void checkConnection();
    void updateWindows(const QByteArray);

    void on_Forward_pressed();

    void on_Forward_released();

    void on_Right_pressed();

    void on_Right_released();

    void on_Back_pressed();

    void on_Back_released();

    void on_Left_pressed();

    void on_Left_released();

    void on_Connexion_clicked();

private:
    Ui::MainWindow *ui;
    MyRobot *Robot;
    Camera *camera;
    QLCDNumber *lcdBattery;


    static void updateSensorDisplay(QPushButton *button, quint8 value);
};
#endif // MAINWINDOW_H
