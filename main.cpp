#include <QCoreApplication>
#include <QThread>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;
    client.demarrer();

    return a.exec();
}
