#include "camera.h"
//#include <QWebEngineView>

Camera::Camera(QString url, QWidget *parent)
    : QWidget{parent}
{
    this->manager =  new QNetworkAccessManager();
    this->urlStream = url;

    this->setFixedSize(120,120);

}

void Camera::move(int a){
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    switch(a){
    case 0: //haut
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
        break;
    case 1: //gauche
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
        break;
    case 2: //bas
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
        break;
    case 3: //droite
        manager->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
        break;
    default:
        break;
    }

}

