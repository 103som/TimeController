#include "client.h"

client::client(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

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

void client::sendRequest(const QString& request) {
    // Проверка, установлено ли соединение с сервером
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // Отправка запроса на сервер
        QByteArray requestData = request.toUtf8();
        socket->write(requestData);
        socket->flush();
    }
}
