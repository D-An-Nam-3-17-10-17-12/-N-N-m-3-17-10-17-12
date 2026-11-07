#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include "Warehouse.h"
using namespace std;
bool isValidNumber(const string& s) {
	if (s.empty()) return false;
	for (char c : s) {
		if (!isdigit(c)) return false;
	}
	return true;
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	WarehouseMap map;
	if (!(cin >> map.R >> map.C)) return 0;
	map.grid.resize(map.R);
	for (int i = 0;i<map.R;++i) {
		cin >> map.grid[i];
	}
	int Q;
	if (!(cin >> Q)) return 0;
	string dummy;
	getline(cin, dummy);
	vector < QueryResult> results;
	for (int q = 0;q < Q;++q) {
		QueryResult res;
		res.isInvalid = false;
		res.totalSteps = -1;
		string line;
		if (!getline(cin, line) || line.empty()) {
			res.isInvalid = true;
			results.push_back(res);
			continue;
		}
		stringstream ss(line);
		vector<string> tokens;
		string temp;
		while (ss >> temp) {
			tokens.push_back(temp);
		}
		if (tokens.empty() || !isValidNumber(tokens[0])) {
			res.isInvalid = true;
			results.push_back(res);
			continue;
		}
		int k = stoi(tokens[0]);
		if (k < 2 || k>8 || (int)tokens.size() != 1 + 2 * k) {
			res.isInvalid = true;
			results.push_back(res);
			continue;
		}
		vector<Point> points;
		bool valid = true;
		for (int i = 0;i < k;++i) {
			string strR = tokens[1 + 2 * i];
			string strC = tokens[2 + 2 * i];
			if (!isValidNumber(strR) || !isValidNumber(strC)) {
				valid = false;
				break;
			}
			int r = stoi(strR);
			int c = stoi(strC);
			if (r < 0 || r >= map.R || c < 0 || c >= map.C || map.grid[r][c] == '#') {
				valid = false;
				break;
			}
			points.push_back({ r,c });

		}
		if (!valid) {
			res.isInvalid = true;
			results.push_back(res);
			continue;
		}
		res = solveQuery(map, points);
		results.push_back(res);
	}
	for (int i = 0;i < Q;++i) {
		if (results[i].isInvalid) {
			cout << "INVALID\n";
		}
		else {
			cout << results[i].totalSteps << "\n";
		}
	}
	for (int i = 0;i < Q;++i) {
		if (results[i].isInvalid || results[i].totalSteps == -1) {
			cout << "-\n";
		}
		else {
			const auto& path = results[i].fullPath;
			int printCount = min((int)path.size(), 11);
			for (int j = 0;j < printCount;++j) {
				cout << "(" << path[j].r << "," << path[j].c << ")";
				if (j < printCount - 1) cout << " ";
			}
			if ((int)path.size() > 11) {
				cout << "...";
			}
			cout << "\n";
		}
	}
	return 0;
}