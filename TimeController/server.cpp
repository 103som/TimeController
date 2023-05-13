#include "server.h"

server::server() {
    if (this->listen(QHostAddress::Any, PORT)) {
        qDebug() << "server started";
    } else {
        qDebug() << "error with starting server";
    }
}

// Обработка входящего соединения.
void server::incomingConnection(qintptr socketDescriptor) {
    if (!isClientConnected) {
        // Принимаем подключение только если нет активного клиента.
        isClientConnected = true;

        QTcpSocket *clientSocket = new QTcpSocket(this);
        clientSocket->setSocketDescriptor(socketDescriptor);

        connect(clientSocket, &QTcpSocket::readyRead, this, &server::handleReadyRead); // связываем сигнал на чтение.
        connect(clientSocket, &QTcpSocket::disconnected, this, &server::handleClientDisconnected); // связываем сигнал на завершение.

        // отправляем сигнал о том, что клиент подключен.
        emit clientConnected(clientSocket->peerAddress().toString(), clientSocket->peerPort());

    } else {
        // Игнорируем новое подключение
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        socket->disconnectFromHost();
        socket->deleteLater();
    }
}

void server::handleReadyRead() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket)
    {
        // отправляем сигнал о том, что клиент передал данные.
        emit dataReceived(clientSocket->peerAddress().toString(), clientSocket->peerPort(), clientSocket->readAll());
    }
}

void server::handleClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket)
    {
        clientSocket->deleteLater();
        // отправляем сигнал о удалении клиента.
        emit clientDisconnected(clientSocket->peerAddress().toString(), clientSocket->peerPort());
    }
}
