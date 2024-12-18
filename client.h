#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#define PORT_SERVEUR 8000

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    void demarrer();
private:
    QTcpSocket *tcpSocket; // la socket

signals:

public slots:
    void estConnectee ();
    void estDeconnectee();
    void gestionErreur(QAbstractSocket::SocketError );
    void recevoir();
    void envoyer(QByteArray );
};



#endif // CLIENT_H
