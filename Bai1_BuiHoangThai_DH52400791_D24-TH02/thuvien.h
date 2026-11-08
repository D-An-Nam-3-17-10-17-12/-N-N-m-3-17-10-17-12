
#ifndef THUVIEN_H
#define THUVIEN_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>
#include <climits>

using namespace std;

const int INF = 1000000000;

extern int R, C;
extern vector<string> gridMap;

bool valid(int x, int y);

vector<int> BFS(int start, vector<int>& parent);

vector<int> getPath(int start, int finish);

void solveQuery(
    const vector<long long>& a,
    string& answer,
    string& pathAnswer
);

#endif

