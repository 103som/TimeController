#include "clientdb.h"

clientDB::clientDB() {
    // Проверяем наличие файла базы данных
    if (QFile::exists(name)) {
        qDebug() << "База данных уже существует.";
        return; // Прерываем дальнейшую обработку
    }

    // Создаем БД.
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);

    if (!db.open()) {
        qDebug() << "Failed to connect to database:";
    } else {
        qDebug() << "Database: connection ok!";
    }


    // Создаем таблицу приложений ПК, если она еще не существует.
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE IF NOT EXISTS appication_logger(\
                id INT PRIMARY KEY AUTO_INCREMENT, \
                name VARCHAR(255), \
                description VARCHAR(255), \
                start_time DATETIME, \
                finish_time DATETIME, \
                total_time DATETIME, \
                activity_type VARCHAR(255))");


    // Создает таблицу используемых приложений.
    query->exec("CREATE TABLE IF NOT EXISTS usable_aplications(\
                id INT PRIMARY KEY AUTO_INCREMENT, \
                name VARCHAR(255))");
}

void clientDB::addRecord(QString name, QString description, QDateTime start_time, QDateTime finish_time,
               QDateTime total_time, QString activity_type) {
    query->prepare("INSERT INTO appication_logger (column2, column3, column4, column5, column6, column7) \
                    VALUES (:value2, :value3, :value4, :value5, :value6, :value7)");

    query->bindValue(":value2", name);
    query->bindValue(":value3", description);
    query->bindValue(":value4", start_time);
    query->bindValue(":value5", finish_time);
    query->bindValue(":value6", total_time);
    query->bindValue(":value7", activity_type);

    if (query->exec()) {
        qDebug() << "Record added successfully.";
    } else {
        qDebug() << "Failed to add record:" << query->lastError().text();
    }
}

// Получить n записей из журнала приложений.
QString clientDB::getRecords(int n) {
    query->prepare("SELECT * FROM appication_logger ORDER BY id DESC LIMIT :n");
    query->bindValue(":n", n);

    QString resultString;
    if (query->exec()) {
        while (query->next()) {
            for (int i = 0; i < query->record().count(); ++i) {
                resultString += query->value(i).toString(); // Добавляем значение столбца в строку результата
                if (i < query->record().count() - 1) {
                    resultString += ","; // Добавляем запятую между значениями столбцов
                }
            }
            resultString += "\n";
        }
    } else {
        qDebug() << "Failed to execute query:" << query->lastError().text();
        return QString(); // возвращаем пустую строку.
    }

    return resultString;
}

// Добавить приложение в таблицу используемых приложений.
void clientDB::addApp(QString name) {
    query->prepare("INSERT INTO usable_aplications (column2) VALUES (:value2)");
    query->bindValue(":value2", name);

    if (query->exec()) {
        qDebug() << "Application added successfully.";
    } else {
        qDebug() << "Failed to add application:" << query->lastError().text();
    }
}

// Удалить приложение из таблицы используемых приложений.
void clientDB::deleteApp(QString name) {
    query->prepare("DELETE FROM usable_aplications WHERE name = :value");
    query->bindValue(":value", name);
    if (query->exec()) {
        qDebug() << "Apllication deleted successfully.";
    } else {
        qDebug() << "Failed to delete Apllication:" << query->lastError().text();
    }
}
