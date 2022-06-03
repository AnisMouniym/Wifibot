// myrobot.cpp

#include "myrobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);

// Creation d'un timer pour l'emission des données à intervalle régulier
    TimerEnvoi = new QTimer();

// setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
    this->isConnected = false;
}

//Connexion
int MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return EXIT_FAILURE;
    }
    TimerEnvoi->start(75);
    this->isConnected = true;
    return EXIT_SUCCESS;

}

//Déconnexion
void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
    this->isConnected = false;
}


void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";

}


void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}


// Mise à jours des octets pour le déplacement du robot (Update Direction + Vitesse)
void MyRobot::move(unsigned char dir, unsigned char rVelocity, unsigned char lVelocity)
{
    qDebug()<<dir;
    while(Mutex.tryLock());
    this->DataToSend[2] = lVelocity;
    this->DataToSend[4] = rVelocity;
    switch(dir){
    case 0:
        this->DataToSend[6] = 0b01010000; // Avant
        break;
    case 1:
        this->DataToSend[6] = 0b00010000; // G
        break;
    case 2:
        this->DataToSend[6] = 0b01000000; // D
        break;
    case 3:
        this->DataToSend[6] = 0b00000000; // Arr
        break;
    default:
        this->DataToSend[2] = 0; // Vitesse  à 0
        this->DataToSend[4] = 0; // Vitesse  à 0
        break;
    }
    Mutex.unlock();
}




void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}


void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

// Mise à jour de la vitesse
void MyRobot::velocityRight(quint8 value)
{
    while(Mutex.tryLock());
    this->DataToSend[4] = value;
    Mutex.unlock();
}
void MyRobot::velocityLeft(quint8 value)
{
    while(Mutex.tryLock());
    this->DataToSend[2] = value;
    Mutex.unlock();
}

// Fonction de calcul d'erreur pour les octets 8-9, la valeur de retour est non signée
quint16 MyRobot::crc16(unsigned int pos){
    unsigned char *data = (unsigned char*)DataToSend.constData();
    quint16 crc = 0xFFFF;
    quint16 Polynome = 0xA001;
    quint16 Parity = 0;
    for(; pos < (unsigned int)DataToSend.length(); pos++){
        crc ^= *(data+pos);
        for (unsigned int CptBit = 0; CptBit <= 7 ; CptBit++){
            Parity= crc;
            crc >>= 1;
            if (Parity%2 == true) crc ^= Polynome;
        }
    }
    return crc;
}
