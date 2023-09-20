#include "server.h"

server::server() {
    if (this->listen(QHostAddress::Any, PORT)) {
        qDebug() << "Connected";
    } else {
        qDebug() << "Error";
    }
}

// Обработка входящего соединения.
void server::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "Client connected!!!!\n";
    if (!isClientConnected) {
        // Принимаем подключение только если нет активного клиента.
        //isClientConnected = true;

        QTcpSocket *clientSocket = new QTcpSocket(this);
        clientSocket->setSocketDescriptor(socketDescriptor);

        connect(clientSocket, &QTcpSocket::readyRead, this, &server::handleReadyRead); // связываем сигнал на чтение.
        connect(clientSocket, &QTcpSocket::disconnected, this, &server::handleClientDisconnected); // связываем сигнал на завершение.
    } else {
        // Игнорируем новое подключение
        // QTcpSocket *socket = new QTcpSocket(this);
        // socket->setSocketDescriptor(socketDescriptor);
        // socket->disconnectFromHost();
        // socket->deleteLater();
    }
}

std::time_t server::getTimeFromJson(QJsonValue timeValue) {
    std::time_t time;
    if (timeValue.isDouble()) {
        double timestamp = timeValue.toDouble(); // Получение значения как число
        time = static_cast<std::time_t>(timestamp); // Преобразование в тип time_t
        // Используйте переменную 'time' (time_t) по вашему усмотрению
    } else if (timeValue.isString()) {
        QString timeString = timeValue.toString(); // Получение значения как строку
        bool ok;
        time = timeString.toULongLong(&ok); // Преобразование строки в тип time_t
    } else {
        throw "error while parsing data back";
    }

    return time;
}

void server::handleReadyRead() {
    qDebug() << "Server got request!!!!!\n";
    QTcpSocket *clientSocket = (QTcpSocket*)(sender());

    QByteArray data = clientSocket->readAll();
    qDebug() << data.constData() << "\n";

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonDoc.object();

    QString info = jsonObject["info"].toString();
    QString name = jsonObject["path"].toString();
    qDebug() << "info:" << info << " name:" << name;
    std::time_t startTime = getTimeFromJson(jsonObject["start_time"]);
    std::time_t finishTime = getTimeFromJson(jsonObject["finish_time"]);
    std::time_t totalTime = getTimeFromJson(jsonObject["total_time"]);

    QJsonValue doubleValue = jsonObject["activity_type"];
    double activityType;

    if (doubleValue.isDouble()) {
        activityType = doubleValue.toDouble(); // Преобразование значения в тип double
    } else {
        throw "Error while parsing activityType";
    }

    clientDB_->addRecord(name, info, QDateTime::fromSecsSinceEpoch(startTime),
                         QDateTime::fromSecsSinceEpoch(finishTime), QDateTime::fromSecsSinceEpoch(totalTime),
                         QString::number(activityType));

    int n = 8;
    QByteArray cuuuurr = (clientDB_->getRecords(n)).toUtf8();
    clientSocket->write(cuuuurr);

}

void server::handleClientDisconnected()
{
    qDebug() << "Отключение!!!";
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket)
    {
        clientSocket->deleteLater();
    }
}
