#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "clientdb.h"

class server : public QTcpServer
{
    Q_OBJECT
public:
    server(); // Запускаем сервер.
    QTcpSocket *clientSocket;
signals:
    void clientConnected(const QString &ipAddress, quint16 port); // сигнал о подключении клиента.
    void clientDisconnected(const QString &ipAddress, quint16 port); // сигнал о отключении клиента.
    void dataReceived(const QString &ipAddress, quint16 port, const QByteArray &data); // сигнал о получении информации от клиента.

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void handleReadyRead();
    void handleClientDisconnected();
private:
    bool isClientConnected = false; // У нас только один клиент.
    const int PORT = 49152; // порт.
    clientDB* clientDB_; // Объект класса по работе с БД.
    QByteArray data; // Обмен сообщений сообщениями с клиентом.
};

#endif // SERVER_H
