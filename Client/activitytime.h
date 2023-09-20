#ifndef ACTIVITYTIME_H
#define ACTIVITYTIME_H

#include <ctime>
#include <QJsonDocument>
#include <QJsonObject>

class ActivityTime {
private:
    QJsonObject serialize(std::time_t finishTime);

public:
    QJsonObject getTotalTime(); // Возвращает все данные о времени.
    std::time_t getWorkingTime();
    void stopTimer();
    void updateInactiveTime(); // Приложение сменило тип активности.

    ActivityTime();

private:
    // По умолчанию -1 означает, что время неактивно.
    std::time_t time = -1;
    std::time_t finish = -1;
    std::time_t becameInactive = -1; // Время в которое приложение стало неактивным.
    std::time_t totalInactiveTime = 0; // Суммарное вермя бездействия пользователя.
    const std::time_t inactiveLimit = 10; // Допустимое количество секунд,
                                          // на которое пользователь может отвлечься.

    // Завершилось => у приложения вызываем метод по получению времени => возвращаем сразу 3 параметра
    // (Время начала "Время начала работы", "Время окончания работы", "Продолжительность", "Результат функции
};

#endif // ACTIVITYTIME_H
