#include "client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QObject *parent) : QObject(parent)
{
    qDebug() << QString::fromUtf8("Instancie un objet QTcpSocket");
    tcpSocket = new QTcpSocket(this);
    qDebug() << QString::fromUtf8("Création de la socket et visualisation de l'état de la socket :") << tcpSocket->state();

    // Connexions des signaux et slots
    connect(tcpSocket, &QTcpSocket::connected, this, &Client::estConnectee);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::estDeconnectee);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred), this, &Client::gestionErreur);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::recevoir);
}

Client::~Client()
{
    qDebug() << QString::fromUtf8("Ferme la socket");
    tcpSocket->close();
}

void Client::demarrer()
{
    qDebug() << QString::fromUtf8("Connexion au serveur");

    QHostAddress serverAddress = QHostAddress::LocalHost;
    quint16 serverPort = 8000; // Assurez-vous que cela correspond au port utilisé par Netcat

    tcpSocket->connectToHost(serverAddress, serverPort);
    qDebug() << QString::fromUtf8("État de la connexion de la socket :") << tcpSocket->state();
}

void Client::estConnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien connecté au serveur ayant pour adresse :") << this->tcpSocket->peerAddress().toString() << "\n";
    qDebug() << QString::fromUtf8("et pour port :") << this->tcpSocket->peerPort() << "`\n";

    this->envoyer("Bonjour à vous !");
}

void Client::estDeconnectee()
{
    qDebug() << QString::fromUtf8("Le client est bien déconnecté");
}

void Client::gestionErreur(QAbstractSocket::SocketError erreur)
{
    qDebug() << QString::fromUtf8("Message d'erreur :") << tcpSocket->errorString();
}

void Client::recevoir()
{
    qDebug() << "Des données ont été reçues : " << tcpSocket->readAll();
}

void Client::envoyer(QByteArray message)
{
    // envoi du message de
    //QByteArray message("Hello world !\n"); // représente le message de la couche Application

    qint64 ecrits = -1;
    // Envoie du message
    ecrits = tcpSocket->write(message);
    switch(ecrits)
    {
    case -1 : /* une erreur ! */
        qDebug() << QString::fromUtf8("Erreur lors de l’envoi !"); break;
    default: /* envoi de n octets */
        qDebug() << QString::fromUtf8("Message envoyé : ") << message;
        qDebug() << QString::fromUtf8("Octets envoyés : ") << ecrits;
        qDebug() << QString::fromUtf8("Message envoyé avec succès !");
    }


}


