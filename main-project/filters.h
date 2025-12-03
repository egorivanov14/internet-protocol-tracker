#pragma once
#include <vector>
#include "internet_session.h"

using namespace std;

vector<InternetSession> filterBySkype(const vector<InternetSession>& sessions);
vector<InternetSession> filterAfterEightAM(const vector<InternetSession>& sessions);