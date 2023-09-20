#ifndef OPERATINGSYSTEMPROGRAM_H
#define OPERATINGSYSTEMPROGRAM_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include "activitytime.h"

class operatingsystemprogram {
private:
    QJsonObject serialize();

public:
    operatingsystemprogram();
    QJsonObject getProgramInfo(); // Вызывается при закрытии программы.
    void setPid(int pid);
    void setInfo(QString info);
    void setPath(QString path);

    ActivityTime getTime();
public:
    int pid; // Procces ID;
    QString path; // Path.
    QString info = NULL; // Special info about program.
    ActivityTime startup; // Временные данные о программе.
};

#endif // OPERATINGSYSTEMPROGRAM_H
