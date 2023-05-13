#include "activitytime.h"

ActivityTime::ActivityTime() {
    time = std::time(nullptr); // текущее время.
    totalInactiveTime = 0;
}

std::time_t ActivityTime::getStartTime() {
    return time;
}

void ActivityTime::addInactiveTime() {

}

int ActivityTime::calculateActivityTimeStatistic() {

}

