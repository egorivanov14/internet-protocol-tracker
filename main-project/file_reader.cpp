#include "file_reader.h"
#include "constants.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Time parseTime(const string& timeStr) {
    Time t;
    char delimiter;
    stringstream ss(timeStr);
    ss >> t.hours >> delimiter >> t.minutes >> delimiter >> t.seconds;
    return t;
}

vector<InternetSession> readDataFromFile(const char* filename) {
    vector<InternetSession> sessions;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return sessions;
    }

    string line;
    while (getline(file, line) && sessions.size() < MAX_RECORDS) {
        stringstream ss(line);
        InternetSession session;
        string startTime, endTime;

        ss >> startTime >> endTime >> session.received >> session.sent;

        getline(ss, session.program);
        if (!session.program.empty() && session.program[0] == ' ') {
            session.program.erase(0, 1);
        }

        session.start = parseTime(startTime);
        session.end = parseTime(endTime);

        sessions.push_back(session);
    }

    file.close();
    return sessions;
}