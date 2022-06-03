#ifndef MOVE_H
#define MOVE_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>

class Move : public QWidget
{
    Q_OBJECT
public:
    explicit Move(QWidget *parent = nullptr);
private:
    QPushButton *_Up;
    QPushButton *_Down;
    QPushButton *_Left;
    QPushButton *_Right;
    QPushButton *_Stop;

    QSlider *leftSlider;
    QSlider *rightSlider;


    void setButton(QPushButton *bouton, QRect Geometry, QString chemin);
    public slots:
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void moveStop();

        void _rightSlider(const int data);
        void _leftSlider(const int data);
    signals:
        void updateMove(const unsigned char data, const unsigned char rVelocity, const unsigned char lVelocity);
        void updateVelocityLeft(const unsigned char data);
        void updateVelocityRight(const unsigned char data);

        };





#endif // MOVE_H
