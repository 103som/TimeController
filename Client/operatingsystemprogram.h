#ifndef OPERATINGSYSTEMPROGRAM_H
#define OPERATINGSYSTEMPROGRAM_H

#include <QString>
#include "activitytime.h"

class operatingsystemprogram {
public:
    int pid; // Procces ID;
    QString path; // Path.
    QString info; // Special info about program.
    ActivityTime startup; // Время начала активности программы.
    operatingsystemprogram();
};

#endif // OPERATINGSYSTEMPROGRAM_H
