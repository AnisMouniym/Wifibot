#ifndef CAMERA_H
#define CAMERA_H
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QPushButton>

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


public slots:
    void move(int a);
};
#endif // CAMERA_H
