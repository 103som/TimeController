#include "operatingsystemprogram.h"

operatingsystemprogram::operatingsystemprogram() {
}

// Сериализует данные о приложении.
QJsonObject operatingsystemprogram::serialize() {
    QJsonObject json_programInfo = startup.getTotalTime();
    qDebug() << "ВАжный дебаг: " << info << ' ' << pid << ' ' << path;
    json_programInfo["info"] = info;
    json_programInfo["pid"] = pid;
    json_programInfo["path"] = path;

    return (json_programInfo);
}

QJsonObject operatingsystemprogram::getProgramInfo() {
    return serialize();
}

void operatingsystemprogram::setPid(int pid) {
    this->pid = pid;
}

void operatingsystemprogram::setInfo(QString info) {
    this->info = info;
}

void operatingsystemprogram::setPath(QString path) {
    QFile file(path);
    if (!file.exists()) {
        throw "Incorrect file path";
    }

    this->path = path;
}

ActivityTime operatingsystemprogram::getTime() {
    return startup;
}
