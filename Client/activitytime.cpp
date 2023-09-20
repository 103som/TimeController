#include "activitytime.h"

ActivityTime::ActivityTime() {
    time = std::time(nullptr); // текущее время.
    totalInactiveTime = 0;
}

void ActivityTime::updateInactiveTime() {
    std::time_t curTime = std::time(NULL);
    // Если пользовтаель был активен.
    if (becameInactive == -1) {
        becameInactive = curTime;
        return;
    }

    if ((curTime - becameInactive) > inactiveLimit) {
        totalInactiveTime += (curTime - becameInactive);
    }

    becameInactive = -1;
}

// Сериализация объекта времени.
QJsonObject ActivityTime::serialize(std::time_t finishTime) {
    QJsonObject jsonTime;
    jsonTime["start_time"] = time;
    jsonTime["finish_time"] = finishTime;
    jsonTime["total_time"] = (finishTime - time);
    jsonTime["activity_type"] = (double(totalInactiveTime) / double(finishTime - time));
    return jsonTime;
}

QJsonObject ActivityTime::getTotalTime() {
    return serialize(std::time(NULL));
}

void ActivityTime::stopTimer() {
    finish = std::time_t(NULL);
}

std::time_t ActivityTime::getWorkingTime() {
    // Если приложение уже было завершено.
    if (finish != -1) {
        return (finish - time);
    }

    // Если приложение еще работает.
    return (std::time(NULL) - time);
}
