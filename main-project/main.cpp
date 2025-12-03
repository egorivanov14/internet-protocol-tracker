#include <iostream>
#include <iomanip>
#include "file_reader.h"
#include "filters.h"
#include "sorts.h"
#include "comparators.h"
#include <vector>

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

void printSessions(const vector<InternetSession>& sessions, const string& title) {
    cout << "\n=== " << title << " (" << sessions.size() << " записей) ===" << endl;
    for (const auto& session : sessions) {
        printSession(session);
    }
}

int main() {

    setlocale(LC_ALL, "Russian");
    cout << "Протокол работы в Интернет" << endl;
    cout << "Вариант: Протокол использования сети" << endl;
    cout << "Автор: Иванов Егор" << endl;
    cout << "Группа: 25ПИнж-1д" << endl;

    auto sessions = readDataFromFile("data.txt");

    int choice;
    do {
        cout << "\n--- Меню ---\n";
        cout << "1. Показать все записи\n";
        cout << "2. Фильтр: Программа Skype\n";
        cout << "3. Фильтр: После 8:00:00\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printSessions(sessions, "Все записи");
            break;
        case 2:
            printSessions(filterBySkype(sessions), "Skype");
            break;
        case 3:
            printSessions(filterAfterEightAM(sessions), "После 8:00:00");
            break;
        case 4: {
            vector<InternetSession*> sessionPtrs;
            for (auto& session : sessions) {
                sessionPtrs.push_back(&session);
            }

            cout << "\n--- Выбор метода сортировки ---\n";
            cout << "1. Сортировка вставками\n";
            cout << "2. Быстрая сортировка\n";
            int sortMethod;
            cin >> sortMethod;

            cout << "\n--- Выбор критерия сравнения ---\n";
            cout << "1. По убыванию времени использования\n";
            cout << "2. По названию программы и байтам\n";
            int compareMethod;
            cin >> compareMethod;

            void (*sortFuncs[])(vector<InternetSession*>&, ComparatorFunc) = {
                insertionSort,
                quickSort
            };

            ComparatorFunc compareFuncs[] = {
                compareByUsageTime,
                compareByProgramAndBytes
            };

            if (sortMethod >= 1 && sortMethod <= 2 && compareMethod >= 1 && compareMethod <= 2) {
                sortFuncs[sortMethod - 1](sessionPtrs, compareFuncs[compareMethod - 1]);

                cout << "\n=== Отсортированные записи ===" << endl;
                for (const auto* session : sessionPtrs) {
                    printSession(*session);
                }
            }
            else {
                cout << "Неверный выбор!" << endl;
            }
            break;
        }
        case 0:
            cout << "Выход из программы" << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}
