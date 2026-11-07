#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "thuvien.h"
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R, C;
    if (!(cin >> R >> C)) return 0;
    vector<string> map(R);
    for (int i = 0; i < R; ++i) {
        if (!(cin >> map[i])) return 0;
    }
    int Q;
    if (!(cin >> Q)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    WarehouseRouter warehouse(R, C, map);
    vector<string> stepAnswers;
    vector<string> pathAnswers;
    for (int i = 0; i < Q; ++i) {
        string line;
        if (!getline(cin, line))
            line.clear();
        string step, path;
        warehouse.processQuery(line, step, path);
        stepAnswers.push_back(step);
        pathAnswers.push_back(path);
    }
    for (const string& answer : stepAnswers)
        cout << answer << '\n';
    for (const string& answer : pathAnswers)
        cout << answer << '\n';
    return 0;
}
