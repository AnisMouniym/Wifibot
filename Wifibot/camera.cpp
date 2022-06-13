#include "camera.h"
//#include <QWebEngineView>

Camera::Camera(QString url, QWidget *parent)
    : QWidget{parent}
{
    this->manager =  new QNetworkAccessManager();
    this->urlStream = url;


}

void Camera::MoveUp(){
    request("53", "-200");
}

void Camera::MoveDown(){
   request("53", "200");
}

void Camera::MoveRight(){
     request("52", "-200");
}

void Camera::MoveLeft(){
    request("52", "200");
}

QUrl Camera::getStreamUrl()
{
    return this->urlStream + "/?action=stream";
}

void Camera::request(QString direction, QString sens){

    requete.setUrl(QUrl(this->urlStream + "?action=command&dest=0&plugin=0&id=100948"+ direction + "&group=1&value="+ sens));
    manager->get(requete);
}

