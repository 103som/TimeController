#ifndef WINDOWS_H
#define WINDOWS_H

#include "operatingsystemfactory.h"
#include "windowssystemprogram.h"

// Данный класс реализует паттерн Singleton, совмещенный с паттерном абстрактная фабрика для operatingsystemfactory.
class WindowsSystem : public QObject {
    Q_OBJECT
private:
    WindowsSystem();
    ~WindowsSystem();

private:
    void handleWindowEvent(HWND windowHandle);
    static void CALLBACK winEventProc(
        HWINEVENTHOOK hWinEventHook,
        DWORD event,
        HWND hwnd,
        LONG idObject,
        LONG idChild,
        DWORD dwEventThread,
        DWORD dwmsEventTime
    );

public:
    static WindowsSystem* getInstance();

    void AddToAutoLoad() const; // Добавление программы в автозагрузку.
    void DeleteFromAutoLoad() const; // Удаление программы из автозагрузки.
    bool ActiveProgramChanged(operatingsystemprogram* curProgram) const;
    QJsonObject getProgramJson() const; // Возвращает всю информацию о программе в JSON формате.
    operatingsystemprogram* GetActiveProgram() const; // Получить текущее активное приложение.

signals:
    void activeWindowChanged(HWND windowHandle, operatingsystemprogram previous);

private:
    static WindowsSystem* instance;
    operatingsystemprogram* activeProgram;
    HWINEVENTHOOK hHook;
};


#endif // WINDOWS_H
