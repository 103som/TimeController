#ifndef APP_H
#define APP_H

#include "windowssystem.h"
#include "client.h"
#include <QJsonDocument>
#include <QJsonObject>

class App : public QObject {
    Q_OBJECT
public:
    App();
    ~App();

    void Execute();
private slots:
    void onActiveWindowChanged(HWND windowHandle, operatingsystemprogram previous);

private:
    WindowsSystem* os;
    client* client_;
};

#endif // APP_H
