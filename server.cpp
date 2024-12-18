#include "server.h"

Server::Server(QObject *parent) : QObject(parent) {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);
    if (!tcpServer->listen(QHostAddress::Any, 8001)) {
        qDebug() << "Server could not start. Error:" << tcpServer->errorString();
    } else {
        qDebug() << "Server started.";
    }
}

Server::~Server() {
    if (tcpServer->isListening()) {
        tcpServer->close();
    }
}

void Server::newConnection() {
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    qDebug() << "Client connected.";
}

void Server::readData() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) return;
    QString data = QString::fromUtf8(clientSocket->readAll());
    qDebug() << "Received data from client:" << data;
    if (data.trimmed().toLower() == "hello") {
        qDebug() << "Sending response: Bonjour";
        clientSocket->write("Bonjour");
    }
}
