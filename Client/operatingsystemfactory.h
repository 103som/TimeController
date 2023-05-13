#ifndef OPERATINGSYSTEMFACTORY_H
#define OPERATINGSYSTEMFACTORY_H

#include <windows.h>
#include <iostream>
#include "windowssystemprogram.h"

class OperatingSystemFactory {
public:
    OperatingSystemFactory();
    virtual void AddToAutoLoad() const = 0;
    virtual void DeleteFromAutoLoad() const = 0;
    virtual WindowsSystemProgram GetActiveProgram()const = 0;
};

#endif // OPERATINGSYSTEMFACTORY_H
