#pragma once
#include <vector>
#include "internet_session.h"

using namespace std;

typedef int (*ComparatorFunc)(const InternetSession*, const InternetSession*);

void insertionSort(vector<InternetSession*>& sessions, ComparatorFunc comparator);
void quickSort(vector<InternetSession*>& sessions, ComparatorFunc comparator);
