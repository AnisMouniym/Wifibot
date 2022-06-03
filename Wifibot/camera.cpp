#include "camera.h"

Camera::Camera(QString url, QWidget *parent)
    : QWidget{parent}
{
    this->manager =  new QNetworkAccessManager();
    this->urlStream = url;

    this->setFixedSize(120,120);
    _Up = new QPushButton(this);
    setButton(_Up, QRect(41,0,41,41), ":/Camera/img/camera/up.png");

    _Left = new QPushButton(this);
    setButton(_Left, QRect(0,41,41,41), ":/Camera/img/camera/left.png");

    _Right = new QPushButton(this);
    setButton(_Right, QRect(82,41,41,41), ":/Camera/img/camera/right.png");

    _Down = new QPushButton(this);
    setButton(_Down, QRect(41,82,41,41), ":/Camera/img/camera/down.png");


    connect(_Up, SIGNAL(pressed()), this, SLOT(MoveUp()));
    connect(_Left, SIGNAL(pressed()), this, SLOT(MoveLeft()));
    connect(_Right, SIGNAL(pressed()), this, SLOT(MoveRight()));
    connect(_Down, SIGNAL(pressed()), this, SLOT(MoveDown()));
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

void Camera::setButton(QPushButton *bouton, QRect Geometry, QString chemin){
    bouton->setIcon(QIcon(chemin));
    bouton->setGeometry(Geometry);
}
