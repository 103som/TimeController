#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "clientdb.h"
#include <QDateTime>

class server : public QTcpServer
{
    Q_OBJECT
public:
    server();
    QTcpSocket *clientSocket;
signals:
    void clientDisconnected(const QString &ipAddress, quint16 port); // сигнал о отключении клиента.
    void dataReceived(const QString &ipAddress, quint16 port, const QByteArray &data); // сигнал о получении информации от клиента

private slots:
    void handleReadyRead();
    void handleClientDisconnected();
    void incomingConnection(qintptr socketDescriptor) override;
private:
    bool isClientConnected = false; // У нас только один клиент.
    const int PORT = 49152; // порт.
    clientDB* clientDB_; // Объект класса по работе с БД.
    QByteArray data; // Обмен сообщений сообщениями с клиентом.
    std::time_t getTimeFromJson(QJsonValue timeValue);
};

#endif // SERVER_H
