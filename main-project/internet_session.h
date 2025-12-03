#pragma once
#include <string>

using namespace std;

struct Time {
    int hours;
    int minutes;
    int seconds;
};

struct InternetSession {
    Time start;
    Time end;
    unsigned long long received;
    unsigned long long sent;
    string program;
};
