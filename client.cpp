#include "client.h"
#include <QDebug>

// Constructeur de la classe Client
Client::Client(QObject *parent) : QObject(parent) {
    // Création d'un objet QTcpSocket
    tcpSocket = new QTcpSocket(this);
    
    // Connexion des signaux du socket aux slots correspondants
    connect(tcpSocket, &QTcpSocket::connected, this, &Client::connected);        // Signal 'connected' -> Slot 'connected'
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::readData);          // Signal 'readyRead' -> Slot 'readData'
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::disconnected);  // Signal 'disconnected' -> Slot 'disconnected'

    // Affichage du message dans le terminal pour indiquer la tentative de connexion
    qDebug() << "Attempting to connect to server...";

    // Tentative de connexion au serveur local (127.0.0.1) sur le port 8000
    tcpSocket->connectToHost("127.0.0.1", 8000);
}

// Destructeur de la classe Client
Client::~Client() {
    // Libération de la mémoire allouée pour le QTcpSocket
    tcpSocket->deleteLater();
}

// Slot appelé lorsque la connexion au serveur est réussie
void Client::connected() {
    qDebug() << "Connected to server.";  // Affichage du message de connexion réussie
    
    // Création d'un message à envoyer au serveur
    QByteArray message = "hello";
    
    // Envoi du message au serveur via le socket
    tcpSocket->write(message);
    tcpSocket->flush();  // Force l'envoi immédiat du message

    // Affichage du message envoyé dans le terminal
    qDebug() << "Sent message to server:" << message;
}

// Slot appelé lorsqu'il y a des données à lire dans le socket
void Client::readData() {
    // Lecture de toutes les données disponibles dans le socket et conversion en QString
    QString data = QString::fromUtf8(tcpSocket->readAll());
    
    // Affichage du message reçu du serveur dans le terminal
    qDebug() << "Message received from server:" << data;
}

// Slot appelé lorsque la connexion avec le serveur est fermée
void Client::disconnected() {
    qDebug() << "Disconnected from server.";  // Affichage du message de déconnexion
}
