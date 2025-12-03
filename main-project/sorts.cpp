#include "sorts.h"
#include <algorithm>

using namespace std;

void insertionSort(vector<InternetSession*>& sessions, ComparatorFunc comparator) {
    for (size_t i = 1; i < sessions.size(); ++i) {
        InternetSession* key = sessions[i];
        int j = i - 1;

        while (j >= 0 && comparator(sessions[j], key) > 0) {
            sessions[j + 1] = sessions[j];
            j--;
        }
        sessions[j + 1] = key;
    }
}

int partition(vector<InternetSession*>& sessions, int left, int right, ComparatorFunc comparator) {
    InternetSession* pivot = sessions[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (comparator(sessions[j], pivot) <= 0) {
            i++;
            swap(sessions[i], sessions[j]);
        }
    }

    swap(sessions[i + 1], sessions[right]);
    return i + 1;
}

void quickSortRecursive(vector<InternetSession*>& sessions, int left, int right, ComparatorFunc comparator) {
    if (left < right) {
        int pi = partition(sessions, left, right, comparator);
        quickSortRecursive(sessions, left, pi - 1, comparator);
        quickSortRecursive(sessions, pi + 1, right, comparator);
    }
}

void quickSort(vector<InternetSession*>& sessions, ComparatorFunc comparator) {
    if (!sessions.empty()) {
        quickSortRecursive(sessions, 0, sessions.size() - 1, comparator);
    }
}