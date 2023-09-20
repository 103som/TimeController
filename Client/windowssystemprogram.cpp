#include "windowssystemprogram.h"

// Реализация конструктора от родителя.
WindowsSystemProgram::WindowsSystemProgram(int pid, QString path, QString info) {
    qDebug() << "Конструктор windowssystemprogram" << pid << ' ' << path << ' ' << info;
    this->pid = pid;
    this->path = path;
    this->info = info;
}

bool WindowsSystemProgram::operator==(const WindowsSystemProgram& other) const {
    return (pid == other.pid);
}
