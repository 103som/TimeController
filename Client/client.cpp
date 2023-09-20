#include "client.h"

client::client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &client::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &client::readyRead);

    qDebug() << ("CLIENT CONNECTED!!!");
    // Устанавливаем соединение с сервером.
    socket->connectToHost("localhost", PORT);
}

void client::connected() {
    qDebug() << "Соединение установлено";
}
void client::disconnected() {
    qDebug() << "Соединение разорвано";
}

void client::readyRead() {
    // Чтение ответа от сервера
    QByteArray responseData = socket->readAll();
    QString response(responseData);
    qDebug() << "Received response:" << response;
}

void client::sendRequest(const QJsonObject& request) {
    // Проверка, установлено ли соединение с сервером
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QByteArray requestData = (QJsonDocument(request)).toJson();
        qDebug() << "ОТПРАВИЛ НА СЕРВЕР:" << requestData.constData() << "\n";
        socket->write(requestData);
        socket->flush();
    }
}
