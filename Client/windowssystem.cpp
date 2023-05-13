#include "windowssystem.h"

// Добавление программы в список автозагружаемых.
void WindowsSystem::AddToAutoLoad() const {
    try {
        // Получить путь к исполняемому файлу текущего процесса
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);

        // Открыть ключ реестра для автозагрузки
        HKEY hkey = NULL;
        RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &hkey);

        // Добавить путь к исполняемому файлу в ключ реестра автозагрузки
        RegSetValueEx(hkey, TEXT("TimeController"), 0, REG_SZ, (BYTE*)szPath, sizeof(TCHAR) * (lstrlen(szPath) + 1));

        // Закрыть ключ реестра и выйти
        RegCloseKey(hkey);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "\n";
        exit(-1);
    }
}

// Удаление программы из списка автозагружаемых.
void WindowsSystem::DeleteFromAutoLoad() const {
    try {
        // Получить путь к исполняемому файлу текущего процесса
        TCHAR szPath[MAX_PATH];
        GetModuleFileName(NULL, szPath, MAX_PATH);

        // Открыть ключ реестра для автозагрузки
        HKEY hKey = NULL;
        if (RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &hKey) != ERROR_SUCCESS) {
            std::cerr << "Ошибка обработки открытия ключа(RegOpenKey).\n";
            exit(-1);
        }

        if (RegDeleteValueA(hKey, "TimeController") != ERROR_SUCCESS) {
            std::cerr << "Ошибка обработки удаления ключа(RegDeleteValueA).\n";
            exit(-1);
        }

        RegCloseKey(hKey);
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << "\n";
        exit(-1);
    }
}

// Получение текущей активной программы.
WindowsSystemProgram WindowsSystem::GetActiveProgram() const {
    return WindowsSystemProgram();
}


