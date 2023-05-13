#ifndef WINDOWS_H
#define WINDOWS_H

#include "operatingsystemfactory.h"

class WindowsSystem : public OperatingSystemFactory {
public:
    WindowsSystemProgram activeProgram;
    WindowsSystem() {
    }

    void AddToAutoLoad() const override;
    void DeleteFromAutoLoad() const override;
    WindowsSystemProgram GetActiveProgram() const override;

    // Если пользователь не был активен
    bool isActive = true;
};


#endif // WINDOWS_H
