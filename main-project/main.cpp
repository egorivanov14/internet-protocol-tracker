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
        << "Received: " << session.received << " | "
        << "Sent: " << session.sent << " | "
        << "Program: " << session.program
        << endl;
}

void printSessions(const vector<InternetSession>& sessions, const string& title) {
    cout << "\n=== " << title << " (" << sessions.size() << " records) ===" << endl;
    for (const auto& session : sessions) {
        printSession(session);
    }
}

int main() {

    cout << "Internet Protocol Log" << endl;
    cout << "Variant: Network Usage Protocol" << endl;
    cout << "Author: Ivanov Egor" << endl;
    cout << "Group: 25PInj-1d" << endl;

    auto sessions = readDataFromFile("data.txt");

    int choice;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Show all records\n";
        cout << "2. Filter: Skype Program\n";
        cout << "3. Filter: After 8:00:00\n";
        cout << "4. Sort records\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printSessions(sessions, "All Records");
            break;
        case 2:
            printSessions(filterBySkype(sessions), "Skype");
            break;
        case 3:
            printSessions(filterAfterEightAM(sessions), "After 8:00:00");
            break;
        case 4: {
            vector<InternetSession*> sessionPtrs;
            for (auto& session : sessions) {
                sessionPtrs.push_back(&session);
            }

            cout << "\n--- Select Sort Method ---\n";
            cout << "1. Insertion Sort\n";
            cout << "2. Quick Sort\n";
            int sortMethod;
            cin >> sortMethod;

            cout << "\n--- Select Comparison Criteria ---\n";
            cout << "1. By decreasing usage time\n";
            cout << "2. By program name and bytes\n";
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

                cout << "\n=== Sorted Records ===" << endl;
                for (const auto* session : sessionPtrs) {
                    printSession(*session);
                }
            }
            else {
                cout << "Invalid choice!" << endl;
            }
            break;
        }
        case 0:
            cout << "Exiting program" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
