#include "server.h"

// Constructeur de la classe Server
Server::Server(QObject *parent) : QObject(parent) {
    // Création d'un objet QTcpServer pour accepter les connexions des clients
    tcpServer = new QTcpServer(this);

    // Connexion du signal 'newConnection' (nouvelle connexion client) au slot 'newConnection' de la classe Server
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newConnection);

    // Tentative de démarrage du serveur en écoutant sur l'adresse locale (Any) et le port 8001
    if (!tcpServer->listen(QHostAddress::Any, 8001)) {
        // Si le serveur ne démarre pas, afficher l'erreur dans le terminal
        qDebug() << "Server could not start. Error:" << tcpServer->errorString();
    } else {
        // Si le serveur démarre correctement, afficher un message dans le terminal
        qDebug() << "Server started.";
    }
}

// Destructeur de la classe Server
Server::~Server() {
    // Si le serveur est encore en écoute, le fermer avant de détruire l'objet
    if (tcpServer->isListening()) {
        tcpServer->close();
    }
}

// Slot appelé lorsqu'une nouvelle connexion client est acceptée
void Server::newConnection() {
    // Récupération de la connexion du client
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    // Connexion des signaux du socket client pour gérer les lectures et la déconnexion
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);          // Signal 'readyRead' -> Slot 'readData'
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater); // Signal 'disconnected' -> Suppression du socket après la déconnexion

    // Affichage du message lorsque le client se connecte
    qDebug() << "Client connected.";
}

// Slot appelé lorsque des données sont disponibles à lire dans le socket du client
void Server::readData() {
    // Récupération du socket client via le signal 'sender()' pour savoir de quel client il s'agit
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientSocket) return;  // Si le cast échoue, on quitte la fonction

    // Lecture des données envoyées par le client et conversion en QString
    QString data = QString::fromUtf8(clientSocket->readAll());

    // Affichage des données reçues dans le terminal
    qDebug() << "Received data from client:" << data;

    // Si le message reçu est "hello" (insensible à la casse), envoyer "Bonjour" en réponse
    if (data.trimmed().toLower() == "hello") {
        qDebug() << "Sending response: Bonjour";  // Affichage du message de réponse
        clientSocket->write("Bonjour");          // Envoi du message "Bonjour" au client
    }
}
