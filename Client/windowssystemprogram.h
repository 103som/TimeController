#ifndef WINDOWSSYSTEMPROGRAM_H
#define WINDOWSSYSTEMPROGRAM_H

#include "operatingsystemprogram.h"

class WindowsSystemProgram : public operatingsystemprogram{
public:
    WindowsSystemProgram(int pid, QString path, QString info);
    bool operator==(const WindowsSystemProgram& other) const;
};

#endif // WINDOWSSYSTEMPROGRAM_H
