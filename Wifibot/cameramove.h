#ifndef CAMERAMOVE_H
#define CAMERAMOVE_H
#include <QWidget>
#include <QPushButton>

class MoveLayout : public QWidget
{
    Q_OBJECT
public:
    explicit MoveLayout(QWidget *parent = nullptr);
private:
    QPushButton *_Up;
    QPushButton *_Left;
    QPushButton *_Right;
    QPushButton *_Down;
    QPushButton *_Stop;

    void setButton(QPushButton *bouton, QRect Geometry, QString chemin);
private slots:
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    void MoveStop();
signals:
    void updateMove(const unsigned char data);
};

#endif // CAMERAMOVE_H
