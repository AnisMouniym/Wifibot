#ifndef MOVE_H
#define MOVE_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>

class MoveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MoveWidget(QWidget *parent = nullptr);
private:
    QPushButton *_Up;
    QPushButton *_Down;
    QPushButton *_Left;
    QPushButton *_Right;
    QPushButton *_Stop;

    QSlider *_leftSlider;
    QSlider *_rightSlider;


    void setButton(QPushButton *bouton, QRect Geometry, QString chemin);
    public slots:
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void moveStop();

        void rightSlider(const int data);
        void leftSlider(const int data);
    signals:
        void updateMove(const unsigned char data, const unsigned char rVelocity, const unsigned char lVelocity);
        void updateVelocityLeft(const unsigned char data);
        void updateVelocityRight(const unsigned char data);

        };





#endif // MOVE_H
