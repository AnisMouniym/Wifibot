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
    void setButton(QPushButton *bouton, QRect Geometry, QString chemin);
    public slots:
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void moveStop();
    signals:
        void updateMove(const unsigned char data, const unsigned char rVelocity, const unsigned char lVelocity);
        void updateVelocityLeft(const unsigned char data);
        void updateVelocityRight(const unsigned char data);

        };





#endif // MOVE_H
