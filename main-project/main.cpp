#include <iostream>
#include <iomanip>
#include "file_reader.h"

using namespace std;

void printSession(const InternetSession& session) {
    cout << setfill('0')
        << setw(2) << session.start.hours << ":"
        << setw(2) << session.start.minutes << ":"
        << setw(2) << session.start.seconds << " - "
        << setw(2) << session.end.hours << ":"
        << setw(2) << session.end.minutes << ":"
        << setw(2) << session.end.seconds << " | "
        << "Получено: " << session.received << " | "
        << "Отправлено: " << session.sent << " | "
        << "Программа: " << session.program
        << endl;
}

int main() {

    setlocale(LC_ALL, "Russian");
    cout << "Протокол работы в Интернет" << endl;
    cout << "Вариант: Протокол использования сети" << endl;
    cout << "Автор: Иванов Егор" << endl;
    cout << "Группа: 25ПИнж-1д" << endl;

    auto sessions = readDataFromFile("data.txt");
    cout << "\nЗагружено записей: " << sessions.size() << endl;

    for (const auto& session : sessions) {
        printSession(session);
    }

    return 0;
}


