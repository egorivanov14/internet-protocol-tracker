#include "comparators.h"
#include <string>

using namespace std;

int timeToSeconds(const Time& t) {
    return t.hours * 3600 + t.minutes * 60 + t.seconds;
}

int compareByUsageTime(const InternetSession* a, const InternetSession* b) {
    int durationA = timeToSeconds(a->end) - timeToSeconds(a->start);
    int durationB = timeToSeconds(b->end) - timeToSeconds(b->start);

    if (durationA > durationB) return -1;
    if (durationA < durationB) return 1;
    return 0;
}

int compareByProgramAndBytes(const InternetSession* a, const InternetSession* b) {
    if (a->program < b->program) return -1;
    if (a->program > b->program) return 1;

    unsigned long long totalA = a->received + a->sent;
    unsigned long long totalB = b->received + b->sent;

    if (totalA > totalB) return -1;
    if (totalA < totalB) return 1;
    return 0;
}