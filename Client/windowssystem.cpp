#include "windowssystem.h"

WindowsSystem* WindowsSystem::instance;

WindowsSystem::WindowsSystem() {
    // Получение активной программы.
    WindowsSystem::instance->activeProgram = GetActiveProgram();

    // Установка хука для события изменения активного окна
    hHook = SetWinEventHook(
        EVENT_OBJECT_FOCUS,
        EVENT_OBJECT_FOCUS,
        NULL,
        WindowsSystem::winEventProc,
        0,
        0,
        WINEVENT_OUTOFCONTEXT
    );

    if (hHook == nullptr) {
        throw "Не удалось установить hHook на SetWinEventHook";
    }
}

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

// Возвращает данные о текущей активной программе.
operatingsystemprogram* WindowsSystem::GetActiveProgram() const {
    HWND foregroundWindow = GetForegroundWindow();

    QString windowTitle = "";
    int titleLength = GetWindowTextLengthW(foregroundWindow);
    if (titleLength > 0) {
        // Выделение буфера для хранения заголовка окна
        WCHAR* titleBuffer = new WCHAR[titleLength + 1];
        GetWindowTextW(foregroundWindow, titleBuffer, titleLength + 1);

        // Преобразование заголовка в QString
        windowTitle = QString::fromWCharArray(titleBuffer);

        // Освобождение выделенной памяти
        delete[] titleBuffer;
    }
    qDebug() << "Window Title:" << windowTitle << ";";
    DWORD processId;
    GetWindowThreadProcessId(foregroundWindow, &processId);
    TCHAR windowTitleeee[MAX_PATH];
    GetWindowText(foregroundWindow, windowTitleeee, MAX_PATH);
    QString appPath = (LPSTR)windowTitleeee;
    qDebug() << "Window appPath:" << appPath << ";";

    return (new WindowsSystemProgram(processId, appPath, windowTitle));
}

// Просто функция-сигнал, реализация не требуется.
void activeWindowChanged(HWND windowHandle, operatingsystemprogram previous) {
}

bool WindowsSystem::ActiveProgramChanged(operatingsystemprogram* curProgram) const {
    return (activeProgram == curProgram);
}

void CALLBACK WindowsSystem::winEventProc(
    HWINEVENTHOOK hWinEventHook,
    DWORD event,
    HWND hwnd,
    LONG idObject,
    LONG idChild,
    DWORD dwEventThread,
    DWORD dwmsEventTime
) {
    WindowsSystem::instance->activeProgram->getTime().stopTimer();

    // Если окно было запущено меньше 5 секунд, то мы считаем, что пользователь не взаимодействовал с ним.
    // т.к. прошло слишком мало времени в нем.
    if (WindowsSystem::instance->activeProgram->getTime().getWorkingTime() < 5) {
        return;
    }

    operatingsystemprogram* program = WindowsSystem::instance->activeProgram;
    qDebug() << "Сохранение данных о предыдущей программе: " << program->info << ' ' << program->path;
    program->getTime().stopTimer(); // Останавливаем время.
    WindowsSystem::instance->activeProgram = WindowsSystem::instance->GetActiveProgram();

    qDebug() << "ПЕРЕДАННЫЕ ДАННЫЕ ПЕРЕД ВЫВОДОМ ВАЖНО:" << QJsonDocument(program->getProgramInfo()).toJson();
    // Посылаем сигнал о измении активного окна.
    emit (WindowsSystem::instance->activeWindowChanged(hwnd, *(program)));
}

WindowsSystem::~WindowsSystem() {
    // Удаление хука при уничтожении объекта WindowWatcher
    UnhookWinEvent(hHook);
}

WindowsSystem* WindowsSystem::getInstance() {
    if (instance == nullptr)
        instance = new WindowsSystem();

    return instance;
}

QJsonObject WindowsSystem::getProgramJson() const {
    return WindowsSystem::instance->activeProgram->getProgramInfo();
}
