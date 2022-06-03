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
#include "move.h"
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


private slots:
    void checkConnection();
    void updateWindows(const QByteArray);

private:
    Ui::MainWindow *ui;
    MyRobot *Robot;
    QPushButton *_connect;
    Move *movePanel;
    Camera *camera;
//    QWebEngineView* video;
    QLCDNumber *lcdBattery;
};
#endif // MAINWINDOW_H
