#ifndef CLIENTDB_H
#define CLIENTDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QFile>
#include <QDateTime>
#include <QVector>
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

class clientDB {
public:
    clientDB();
    std::pair<QString, QString> getClientAuthorizationData();
    void addRecord(QString name, QString description, QDateTime start_time, QDateTime finish_time,
                  QDateTime total_time, QString activity_type);
    QString getRecords(int n);

    void addApp(QString name);
    void deleteApp(QString name);


private:
    QSqlDatabase db; // Локальная БД.
    QSqlQuery *query; // Переменная Sql запроса.
    const QString name = "./clientsDB.db";
};

#endif // CLIENTDB_H
