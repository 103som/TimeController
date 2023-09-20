#include "app.h"

App::App() {
    os = WindowsSystem::getInstance(); // создаем ос.
    client_ = new client(); // создаем клиента.
    connect(os, &WindowsSystem::activeWindowChanged, this, &App::onActiveWindowChanged);
}

void App::onActiveWindowChanged(HWND windowHandle, operatingsystemprogram previous) {
    client_->sendRequest(os->getProgramJson()); // Передаем данные для отправки клиентом серверу.
}

App::~App() {
    delete client_;
}
