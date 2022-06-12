#include "move.h"
#include "QtCore/qdebug.h"

Move::Move(QWidget *parent)
    : QWidget{parent}
{
 //. Taille fenetre
        this->setFixedSize(200,200);

// 5 boutons de commande
        _Up = new QPushButton(this);
        setButton(_Up, QRect(61,0,41,41), ":/Move/img/up.png");

        _Left = new QPushButton(this);
        setButton(_Left, QRect(20,41,41,41), ":/Move/img/left.png");

        _Right = new QPushButton(this);
        setButton(_Right, QRect(102,41,41,41), ":/Move/img/right.png");

        _Down = new QPushButton(this);
        setButton(_Down, QRect(61,82,41,41), ":/Move/img/down.png");

        _Stop = new QPushButton(this);
        setButton(_Stop, QRect(61,41,41,41), "");

// Création de 2 sliders de gestion de vitesse (Valeur entre 0 et 240)
        leftSlider = new QSlider(this);
        leftSlider->setMinimum(0);
        leftSlider->setMaximum(240);
        leftSlider->setGeometry(0,0,20,120);

        rightSlider = new QSlider(this);
        rightSlider->setMinimum(0);
        rightSlider->setMaximum(240);
        rightSlider->setGeometry(143,0,20,120);

// Definition des connexions entre les signaux des boutons et les slots
        connect(_Up, SIGNAL(pressed()), this, SLOT(moveUp()));
        connect(_Left, SIGNAL(pressed()), this, SLOT(moveLeft()));
        connect(_Right, SIGNAL(pressed()), this, SLOT(moveRight()));
        connect(_Down, SIGNAL(pressed()), this, SLOT(moveDown()));
        connect(_Stop, SIGNAL(pressed()), this, SLOT(moveStop()));

        connect(rightSlider, SIGNAL(valueChanged(int)), this, SLOT(_rightSlider(int)));
        connect(leftSlider, SIGNAL(valueChanged(int)), this, SLOT(_leftSlider(int)));
    }


 // ajoute un icone au bouton et place celui-ci au sein du widget
    void Move::setButton(QPushButton *bouton, QRect Geometry, QString chemin){
        bouton->setIcon(QIcon(chemin));
        bouton->setGeometry(Geometry);
    }


    void Move::moveUp()
    {
 // Emission d'un signal de modification de direction
        qDebug() << "ca va";
        emit updateMove(0, rightSlider->value(), leftSlider->value());
    }


    void Move::moveDown()
    {
// Emission d'un signal de modification de direction
        emit updateMove(3, rightSlider->value(), leftSlider->value());
    }


    void Move::moveLeft()
    {

// Emission d'un signal de modification de direction
        emit updateMove(1, rightSlider->value(), leftSlider->value());
    }

    void Move::moveRight()
    {

// Emission d'un signal de modification de direction
        emit updateMove(2, rightSlider->value(), leftSlider->value());
    }

    void Move::moveStop()
    {

// Emission d'un signal de modification de direction
        emit updateMove(4, rightSlider->value(), leftSlider->value());
    }

    void Move::_rightSlider(const int data)
    {

// Emission d'un signal de modification de la vitesse coté gauche
        emit updateVelocityRight((unsigned char)data);
    }
    void Move::_leftSlider(const int data)
    {

// Emission d'un signal de modification de la vitesse coté droit
        emit updateVelocityRight((unsigned char)data);
    }
