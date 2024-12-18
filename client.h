#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();

private slots:
    void connected();
    void readData();
    void disconnected();

private:
    QTcpSocket *tcpSocket;
};

#endif // CLIENT_H
