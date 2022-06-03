#ifndef CAMERA_H
#define CAMERA_H
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QPushButton>

/*
*  Creation d'un groupe de 4 boutons pour le déplacement de la caméra.
*/

class Camera : public QWidget
{
    Q_OBJECT
public:
    explicit Camera(QString url, QWidget *parent = nullptr);
    QUrl getStreamUrl();
    void setButton(QPushButton *bouton, QRect Geometry, QString chemin);

private:
    void request(QString direction, QString sens);
    QNetworkRequest requete;
    QNetworkAccessManager *manager;
    QString urlStream;
    QPushButton *_Up;
    QPushButton *_Left;
    QPushButton *_Right;
    QPushButton *_Down;

public slots:
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
};
#endif // CAMERA_H
