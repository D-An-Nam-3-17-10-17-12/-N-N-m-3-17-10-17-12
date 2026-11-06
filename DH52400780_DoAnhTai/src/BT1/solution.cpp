#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <cctype>
#include <algorithm>
using namespace std;

bool isNumeric(const string& s) {
	if (s.empty()) return false;
	for (char ch : s) {
		if (!isdigit(ch)) return false;
	}
	return true;
}

vector<vector<int>> bfs(const vector<string>& grid, int R, int C, int sr, int sc, vector<vector<pair<int, int>>>& parent) {
	vector<vector<int>> dist(R, vector<int>(C, -1));
	parent.assign(R, vector<pair<int, int>>(C, { -1,-1 }));
	dist[sr][sc] = 0;
	queue<pair<int, int>> q;
	q.push({ sr,sc });
	int dr[] = { -1,1,0,0 };
	int dc[] = { 0,0,-1,1 };
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();
		for (int d = 0;d < 4;d++) {
			int nr = r + dr[d];
			int nc = c + dc[d];

			if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#' && dist[nr][nc] == -1) {
				dist[nr][nc] = dist[r][c] + 1;
				parent[nr][nc] = { r,c };
				q.push({ nr,nc });
			}
		}
	}
	return dist;
}
vector<pair<int, int>> layDuong(const vector<vector<pair<int, int>>>& parent, pair<int, int>from, pair<int, int> to) {
	vector<pair<int, int>> path;
	pair<int, int>cur = to;
	while (cur != make_pair(-1, -1)) {
		path.push_back(cur);
		if (cur == from)break;
		cur = parent[cur.first][cur.second];
	}
	reverse(path.begin(), path.end());
	return path;
}

int main() {
	int R, C;
	cin >> R >> C;

	vector<string> grid(R);
	for (int i = 0;i < R;i++)
		cin >> grid[i];


	int Q;
	if (!(cin >> Q)) return 0;
	cin.ignore();

	vector<string> phan1, phan2;
	auto loi = [&](const string& s) {
		phan1.push_back(s);
		phan2.push_back("-");
		};
	for (int t = 0;t < Q;t++) {
		string line;
		getline(cin, line);
		stringstream ss(line);
		vector<string> tokens;
		string tok;
		while (ss >> tok) tokens.push_back(tok);

		if (tokens.empty()) {
			loi("INVALID");
			continue;
		}
		if (!isNumeric(tokens[0])) {
			loi("INVALID");
			continue;
		}
		int k = stoi(tokens[0]);
		if (k < 2 || k>8) {
			loi("INVALID");
			continue;
		}
		if (tokens.size() != 1 + 2 * k) {
			loi("INVALID");
			continue;
		}
		bool allTokensValid = true;
		for (size_t j = 1;j < tokens.size();j++) {
			if (!isNumeric(tokens[j])) {
				allTokensValid = false;
				break;
			}
		}
		if (!allTokensValid) {
			loi("INVALID");
			continue;
		}
		bool coordinatesValid = true;
		vector<pair<int, int>> points;
		for (size_t j = 1;j < tokens.size();j += 2) {
			int r = stoi(tokens[j]);
			int c = stoi(tokens[j + 1]);

			if (r < 0 || r >= R || c < 0 || c >= C || grid[r][c] == '#') {
				coordinatesValid = false;
				break;
			}
			points.push_back({ r,c });
		}
		if (!coordinatesValid) {
			loi("INVALID");
			continue;
		}
		vector<vector<int>> d(k, vector<int>(k));
		bool reachable = true;
		vector<vector<vector<pair<int, int>>>> parents(k);
		for (int i = 0;i < k;i++) {
			
			auto dist = bfs(grid, R, C, points[i].first, points[i].second, parents[i]);
			for (int j = 0;j < k;j++) {
				d[i][j] = dist[points[j].first][points[j].second];
				if (d[i][j] == -1) reachable = false;
			}
		}
		if (!reachable) {
			loi("-1");
			continue;
		}
		vector<int> order;
		for (int i = 1;i < k;i++) order.push_back(i);
		vector<int> bestOrder;
		long long best = -1;
		do {
			long long sum = d[0][order[0]];
			for (int i = 0;i + 1 < (int)order.size();i++)
				sum += d[order[i]][order[i + 1]];
			if (best == -1 || sum < best) {
				best = sum;
				bestOrder = order;
			}
		} while (next_permutation(order.begin(), order.end()));
		phan1.push_back(to_string(best));
		
		vector<int>seq = { 0 };
		for (int x : bestOrder)seq.push_back(x);
		vector<pair<int, int>> fullPath;
		for (size_t s = 0;s + 1 < seq.size();s++) {
			int a = seq[s], b = seq[s + 1];
			auto seg = layDuong(parents[a], points[a], points[b]);

			size_t from = (s == 0) ? 0 : 1;
			for (size_t i = from;i < seg.size();i++) fullPath.push_back(seg[i]);
		}
		string duong;
		for (size_t i = 0;i < fullPath.size() && i < 11;i++) {
			if (i > 0)duong += " ";
			duong += "(" + to_string(fullPath[i].first) + "," + to_string(fullPath[i].second) + ")";
		}
		if (fullPath.size() > 11)duong += " ...";
		phan2.push_back(duong);
	
	}
	for (const string& s : phan1)cout << s << "\n";
	for (const string& s : phan2)cout << s << "\n";

	return 0;
}