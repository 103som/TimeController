#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QStringList>
#include <QString>
#include <QVector>
#include <cstdlib>

class client : QObject {
    Q_OBJECT
public:
    explicit client(QObject *parent = nullptr);
    void connectToServer();
    void sendRequest(const QString& request);

private slots:
    void connected();
    void disconnected();
    void readyRead();

private:
    QTcpSocket *socket;
    QByteArray data;
    const int PORT = 49152; // Порт, для работы с сервером.
};

#endif // CLIENT_H
