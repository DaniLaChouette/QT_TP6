#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent) {
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::connected, this, &Client::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &Client::readData);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &Client::disconnected);

    qDebug() << "Attempting to connect to server...";
    tcpSocket->connectToHost("127.0.0.1", 8001);
}

Client::~Client() {
    tcpSocket->deleteLater();
}

void Client::connected() {
    qDebug() << "Connected to server.";
    // Send "hello" message to server upon connection
    tcpSocket->write("hello");
    tcpSocket->flush();
}

void Client::readData() {
    QString data = QString::fromUtf8(tcpSocket->readAll());
    qDebug() << "Received data from server:" << data;
}

void Client::disconnected() {
    qDebug() << "Disconnected from server.";
}
