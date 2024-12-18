#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QObject {
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void newConnection();
    void readData();

private:
    QTcpServer *tcpServer;
};

#endif // SERVER_H
