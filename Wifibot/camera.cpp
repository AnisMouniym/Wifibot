#include "camera.h"
//#include <QWebEngineView>

Camera::Camera(QString url, QWidget *parent)
    : QWidget{parent}
{
    this->manager =  new QNetworkAccessManager();
    this->urlStream = url;

    this->setFixedSize(120,120);

}






