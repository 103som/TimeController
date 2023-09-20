#ifndef OPERATINGSYSTEMFACTORY_H
#define OPERATINGSYSTEMFACTORY_H

#include <windows.h>
#include <iostream>
#include "operatingsystemprogram.h"

class OperatingSystemFactory {
public:
    virtual void AddToAutoLoad() const = 0; // Добавление программы в автозагрузку.
    virtual void DeleteFromAutoLoad() const = 0; // Удаление программы из автозагрузки.
    virtual bool ActiveProgramChanged(operatingsystemprogram* curProgram) const = 0;
    virtual operatingsystemprogram* GetActiveProgram() const = 0; // Получить текущее активное приложение.
    virtual QJsonObject getProgramJson() const  = 0; // Возвращает всю информацию о программе в JSON формате.

protected:
    operatingsystemprogram* activeProgram;
};

#endif // OPERATINGSYSTEMFACTORY_H
