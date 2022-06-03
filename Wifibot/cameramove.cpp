#include "cameramove.h"
#include <QWidget>
#include <QPushButton>
MoveLayout::MoveLayout(QWidget *parent)
    : QWidget{parent}
{

 //. Taille fenetre
        this->setFixedSize(200,200);

// 5 boutons de commande
        _Up = new QPushButton(this);
        setButton(_Up, QRect(61,0,41,41), ":/Camera/img/up.png");

        _Left = new QPushButton(this);
        setButton(_Left, QRect(20,41,41,41), ":/Camera/img/left.png");

        _Right = new QPushButton(this);
        setButton(_Right, QRect(102,41,41,41), ":/Camera/img/right.png");

        _Down = new QPushButton(this);
        setButton(_Down, QRect(61,82,41,41), ":/Camera/img/down.png");

        _Stop = new QPushButton(this);
        setButton(_Stop, QRect(61,41,41,41), "");
}
