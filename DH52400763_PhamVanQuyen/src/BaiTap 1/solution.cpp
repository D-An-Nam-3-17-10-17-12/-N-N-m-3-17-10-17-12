#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

const int INF = 1000000000;

int R, C;
vector<string> gridMap;

int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

// Kiem tra so nguyen hop le
bool parseNumber(const string& s, int& value) {
    if (s.empty()) return false;

    long long num = 0;

    for (char ch : s) {
        if (ch < '0' || ch > '9')
            return false;

        int digit = ch - '0';

        if (num > (2147483646LL - digit) / 10)
            return false;

        num = num * 10 + digit;
    }

    value = (int)num;
    return true;
}

// Tach va kiem tra du lieu truy van
bool parseQuery(const string& line, vector<int>& a) {
    stringstream ss(line);
    string token;

    a.clear();

    while (ss >> token) {
        int x;

        if (!parseNumber(token, x))
            return false;

        a.push_back(x);
    }

    return true;
}

// Kiem tra toa do
bool validCell(int r, int c) {
    return r >= 0 && r < R &&
        c >= 0 && c < C &&
        gridMap[r][c] == '.';
}

// Chuyen toa do thanh ID
int getId(int r, int c) {
    return r * C + c;
}

// BFS tinh khoang cach
vector<int> bfs(int start) {
    int n = R * C;

    vector<int> dist(n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int r = u / C;
        int c = u % C;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!validCell(nr, nc))
                continue;

            int v = getId(nr, nc);

            if (dist[v] != -1)
                continue;

            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    return dist;
}

// BFS truy vet duong di
vector<int> getPath(int start, int target) {
    int n = R * C;

    vector<int> parent(n, -1);
    queue<int> q;

    parent[start] = start;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == target)
            break;

        int r = u / C;
        int c = u % C;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!validCell(nr, nc))
                continue;

            int v = getId(nr, nc);

            if (parent[v] != -1)
                continue;

            parent[v] = u;
            q.push(v);
        }
    }

    vector<int> path;

    if (parent[target] == -1)
        return path;

    int cur = target;

    while (cur != start) {
        path.push_back(cur);
        cur = parent[cur];
    }

    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}

// Quy hoach dong Bitmask DP
pair<int, vector<int>> solveQuery(
    const vector<int>& points,
    int k
) {
    vector<vector<int>> dist(k, vector<int>(k, -1));

    // Tinh khoang cach giua moi cap diem
    for (int i = 0; i < k; i++) {
        vector<int> d = bfs(points[i]);

        for (int j = 0; j < k; j++) {
            dist[i][j] = d[points[j]];
        }
    }

    int FULL = (1 << k) - 1;

    vector<vector<int>> dp(
        1 << k,
        vector<int>(k, INF)
    );

    vector<vector<int>> parent(
        1 << k,
        vector<int>(k, -1)
    );

    dp[1][0] = 0;

    // Tinh DP
    for (int mask = 1; mask <= FULL; mask++) {
        for (int last = 0; last < k; last++) {

            if (dp[mask][last] == INF)
                continue;

            if (!(mask & (1 << last)))
                continue;

            for (int nxt = 0; nxt < k; nxt++) {

                if (mask & (1 << nxt))
                    continue;

                if (dist[last][nxt] == -1)
                    continue;

                int newMask = mask | (1 << nxt);

                int newCost =
                    dp[mask][last] + dist[last][nxt];

                if (newCost < dp[newMask][nxt]) {
                    dp[newMask][nxt] = newCost;
                    parent[newMask][nxt] = last;
                }
            }
        }
    }

    // Tim ket qua tot nhat
    int bestCost = INF;
    int last = -1;

    for (int i = 0; i < k; i++) {
        if (dp[FULL][i] < bestCost) {
            bestCost = dp[FULL][i];
            last = i;
        }
    }

    if (bestCost == INF)
        return { -1,{} };

    // Truy vet thu tu cac diem
    vector<int> order;
    int mask = FULL;

    while (last != -1) {
        order.push_back(last);

        int previous = parent[mask][last];

        mask ^= (1 << last);
        last = previous;
    }

    reverse(order.begin(), order.end());

    // Ghép cac doan duong di
    vector<int> fullPath;

    for (int i = 0; i + 1 < (int)order.size(); i++) {
        int u = points[order[i]];
        int v = points[order[i + 1]];

        vector<int> segment = getPath(u, v);

        if (segment.empty())
            return { -1,{} };

        if (!fullPath.empty())
            segment.erase(segment.begin());

        fullPath.insert(
            fullPath.end(),
            segment.begin(),
            segment.end()
        );
    }

    if (fullPath.empty())
        fullPath.push_back(points[0]);

    return { bestCost, fullPath };
}

// Dinh dang duong di
string formatPath(const vector<int>& path) {
    if (path.empty())
        return "-";

    stringstream ss;

    int limit = min((int)path.size(), 11);

    for (int i = 0; i < limit; i++) {
        if (i > 0)
            ss << " ";

        int r = path[i] / C;
        int c = path[i] % C;

        ss << "(" << r << "," << c << ")";
    }

    if ((int)path.size() > 11)
        ss << " ...";

    return ss.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C;

    gridMap.resize(R);

    for (int i = 0; i < R; i++) {
        cin >> gridMap[i];
    }

    int Q;
    cin >> Q;

    string line;
    getline(cin, line);

    vector<string> part1;
    vector<string> part2;

    for (int query = 0; query < Q; query++) {

        getline(cin, line);

        vector<int> a;

        if (!parseQuery(line, a) || a.empty()) {
            part1.push_back("INVALID");
            part2.push_back("-");
            continue;
        }

        int k = a[0];

        if (k < 2 || k > 8) {
            part1.push_back("INVALID");
            part2.push_back("-");
            continue;
        }

        if ((int)a.size() != 1 + 2 * k) {
            part1.push_back("INVALID");
            part2.push_back("-");
            continue;
        }

        vector<int> points;
        bool invalid = false;

        for (int i = 0; i < k; i++) {
            int r = a[1 + 2 * i];
            int c = a[2 + 2 * i];

            if (r >= R || c >= C || !validCell(r, c)) {
                invalid = true;
                break;
            }

            points.push_back(getId(r, c));
        }

        if (invalid) {
            part1.push_back("INVALID");
            part2.push_back("-");
            continue;
        }

        pair<int, vector<int>> result =
            solveQuery(points, k);

        if (result.first == -1) {
            part1.push_back("-1");
            part2.push_back("-");
        }
        else {
            part1.push_back(to_string(result.first));
            part2.push_back(formatPath(result.second));
        }
    }

    // Phan 1
    for (const string& s : part1)
        cout << s << '\n';

    // Phan 2
    for (const string& s : part2)
        cout << s << '\n';

    return 0;
}

