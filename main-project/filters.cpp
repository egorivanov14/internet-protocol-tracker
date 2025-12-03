#include "filters.h"
#include <algorithm>

using namespace std;

bool isSkypeProgram(const string& program) {
    string lowerProgram = program;
    transform(lowerProgram.begin(), lowerProgram.end(), lowerProgram.begin(), ::tolower);
    return lowerProgram.find("skype") != string::npos;
}

vector<InternetSession> filterBySkype(const vector<InternetSession>& sessions) {
    vector<InternetSession> result;
    for (const auto& session : sessions) {
        if (isSkypeProgram(session.program)) {
            result.push_back(session);
        }
    }
    return result;
}

bool isAfterEightAM(const Time& time) {
    if (time.hours > 8) return true;
    if (time.hours == 8 && time.minutes > 0) return true;
    if (time.hours == 8 && time.minutes == 0 && time.seconds > 0) return true;
    return false;
}

vector<InternetSession> filterAfterEightAM(const vector<InternetSession>& sessions) {
    vector<InternetSession> result;
    for (const auto& session : sessions) {
        if (isAfterEightAM(session.start)) {
            result.push_back(session);
        }
    }
    return result;
}