#include "move.h"
#include "QtCore/qdebug.h"

Move::Move(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(200,200);
}
