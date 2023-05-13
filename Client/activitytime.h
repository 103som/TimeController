#ifndef ACTIVITYTIME_H
#define ACTIVITYTIME_H

#include <ctime>

class ActivityTime {
public:
    std::time_t getStartTime(); // Возвращает время запуска приложения.
    void addInactiveTime(); // Увеличивает неактивное время прложения(принимает time_t, время окончания программы).

    int calculateActivityTimeStatistic();
    ActivityTime();

private:
    std::time_t time;
    std::time_t becameInactive = 0;
    std::time_t totalInactiveTime = 0;
    // Завершилось => у приложения вызываем метод по получению времени => возвращаем сразу 3 параметра
    // (Время начала "Время начала работы", "Время окончания работы", "Продолжительность", "Результат функции
};

#endif // ACTIVITYTIME_H
