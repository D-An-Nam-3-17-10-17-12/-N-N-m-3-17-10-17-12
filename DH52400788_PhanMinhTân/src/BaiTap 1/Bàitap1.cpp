#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
#include <climits>
#include <cctype>
using namespace std;

struct Point {
    int r, c;
};

struct QueryResult {
    bool invalid = false;
    bool reachable = false;
    int steps = -1;
    vector<int> order;
};

bool laSoNguyenKhongAm(const string& s) {
    if (s.empty()) return false;

    for (char ch : s) {
        if (ch < '0' || ch > '9')
            return false;
    }

    return true;
}

bool chuyenSoNguyenKhongAm(const string& s, int& value) {
    if (!laSoNguyenKhongAm(s))
        return false;

    int x = 0;

    for (char ch : s) {
        int digit = ch - '0';

        if (x > (INT_MAX - digit) / 10)
            return false;

        x = x * 10 + digit;
    }

    value = x;
    return true;
}
vector<string> tachTu(const string& line) {
    stringstream ss(line);
    vector<string> tokens;
    string token;

    while (ss >> token)
        tokens.push_back(token);

    return tokens;
}

int maO(int r, int c, int cols) {
    return r * cols + c;
}

Point toaDoO(int id, int cols) {
    return { id / cols, id % cols };
}
const int DR[4] = { -1, 1, 0, 0 };
const int DC[4] = { 0, 0, -1, 1 };
vector<int> tinhKhoangCachBFS(
    const vector<string>& grid,
    int startId
) {
    int R = (int)grid.size();
    int C = (int)grid[0].size();
    int total = R * C;
    vector<int> dist(total, -1);
    queue<int> q;
    dist[startId] = 0;
    q.push(startId);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int r = u / C;
        int c = u % C;
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (nr < 0 || nr >= R ||
                nc < 0 || nc >= C)
                continue;
            if (grid[nr][nc] == '#')
                continue;
            int v = maO(nr, nc, C);
            if (dist[v] != -1)
                continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}
vector<int> timDuongBFS(
    const vector<string>& grid,
    int startId,
    int targetId
) {
    int R = (int)grid.size();
    int C = (int)grid[0].size();
    int total = R * C;
    vector<int> parent(total, -1);
    queue<int> q;
    parent[startId] = startId;
    q.push(startId);
    while (!q.empty() && parent[targetId] == -1) {
        int u = q.front();
        q.pop();
        int r = u / C;
        int c = u % C;
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];

            if (nr < 0 || nr >= R ||
                nc < 0 || nc >= C)
                continue;

            if (grid[nr][nc] == '#')
                continue;

            int v = maO(nr, nc, C);

            if (parent[v] != -1)
                continue;

            parent[v] = u;
            q.push(v);
        }
    }

    if (parent[targetId] == -1)
        return {};

    vector<int> path;

    for (int cur = targetId;
        cur != startId;
        cur = parent[cur]) {
        path.push_back(cur);
    }

    path.push_back(startId);
    reverse(path.begin(), path.end());

    return path;
}

QueryResult giaiTruyVan(
    const vector<string>& grid,
    const vector<Point>& points
) {
    QueryResult result;

    int k = (int)points.size();
    int C = (int)grid[0].size();

    vector<int> ids(k);

    for (int i = 0; i < k; ++i) {
        ids[i] = maO(
            points[i].r,
            points[i].c,
            C
        );
    }

    vector<vector<int>> dist(
        k, vector<int>(k, -1)
    );

    for (int i = 0; i < k; ++i) {
        vector<int> allDist =
            tinhKhoangCachBFS(grid, ids[i]);

        for (int j = 0; j < k; ++j) {
            dist[i][j] = allDist[ids[j]];
        }
    }

    int targetCount = k - 1;
    int maskCount = 1 << targetCount;

    const int INF = 1000000000;

    vector<vector<int>> dp(
        maskCount,
        vector<int>(targetCount, INF)
    );
    vector<vector<int>> parentLast(
        maskCount,
        vector<int>(targetCount, -1)
    );

    for (int i = 0; i < targetCount; ++i) {
        if (dist[0][i + 1] != -1) {
            dp[1 << i][i] = dist[0][i + 1];
        }
    }

    for (int mask = 1;
        mask < maskCount;
        ++mask) {

        for (int last = 0;
            last < targetCount;
            ++last) {

            if (!(mask & (1 << last)))
                continue;

            if (dp[mask][last] == INF)
                continue;

            for (int next = 0;
                next < targetCount;
                ++next) {

                if (mask & (1 << next))
                    continue;

                int d = dist[last + 1][next + 1];

                if (d == -1)
                    continue;

                int nextMask = mask | (1 << next);

                int candidate =
                    dp[mask][last] + d;

                if (candidate < dp[nextMask][next]) {
                    dp[nextMask][next] = candidate;

                    parentLast[nextMask][next] =
                        last;
                }
            }
        }
    }
    int fullMask = maskCount - 1;
    int bestLast = -1;
    int bestDistance = INF;

    for (int last = 0;
        last < targetCount;
        ++last) {

        if (dp[fullMask][last] < bestDistance) {
            bestDistance = dp[fullMask][last];
            bestLast = last;
        }
    }

    if (bestLast == -1 ||
        bestDistance == INF) {
        result.reachable = false;
        return result;
    }

    result.reachable = true;
    result.steps = bestDistance;

    vector<int> reverseOrder;

    int mask = fullMask;
    int last = bestLast;

    while (last != -1) {
        reverseOrder.push_back(last + 1);

        int previous =
            parentLast[mask][last];

        mask ^= (1 << last);
        last = previous;
    }

    reverse(
        reverseOrder.begin(),
        reverseOrder.end()
    );

    result.order = reverseOrder;

    return result;
}
void inDuongDi(
    const vector<string>& grid,
    const vector<Point>& points,
    const QueryResult& result
) {
    if (result.invalid || !result.reachable) {
        cout << "-\n";
        return;
    }

    int C = (int)grid[0].size();

    vector<int> route;

    route.push_back(
        maO(points[0].r, points[0].c, C)
    );

    int current = route[0];

    for (int pointIndex : result.order) {
        int target = maO(
            points[pointIndex].r,
            points[pointIndex].c,
            C
        );

        vector<int> segment =
            timDuongBFS(grid, current, target);

        for (size_t i = 1;
            i < segment.size();
            ++i) {
            route.push_back(segment[i]);
        }

        current = target;
    }

    int cellsToPrint = min(
        (int)route.size(), 11
    );

    for (int i = 0; i < cellsToPrint; ++i) {
        if (i > 0)
            cout << ' ';

        Point p = toaDoO(route[i], C);
        cout << '(' << p.r << ',' << p.c << ')';
    }

    if ((int)route.size() - 1 > 10)
        cout << " ...";

    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;

    if (!(cin >> R >> C))
        return 0;

    string line;
    getline(cin, line);

    if (R < 1 || R > 1000 ||
        C < 1 || C > 1000)
        return 0;

    vector<string> grid(R);

    for (int i = 0; i < R; ++i) {
        if (!getline(cin, grid[i]))
            return 0;

        while (!grid[i].empty() &&
            isspace((unsigned char)grid[i].back())) {
            grid[i].pop_back();
        }

        size_t first = 0;

        while (first < grid[i].size() &&
            isspace((unsigned char)grid[i][first])) {
            ++first;
        }

        grid[i] = grid[i].substr(first);

        if ((int)grid[i].size() != C)
            return 0;

        for (char ch : grid[i]) {
            if (ch != '.' && ch != '#')
                return 0;
        }
    }

    string qLine;

    do {
        if (!getline(cin, qLine))
            return 0;
    } while (
        qLine.find_first_not_of(" \t\r\n")
        == string::npos
        );

    vector<string> qTokens = tachTu(qLine);

    int Q;

    if (qTokens.size() != 1 ||
        !chuyenSoNguyenKhongAm(qTokens[0], Q) ||
        Q < 1 || Q > 10) {
        return 0;
    }

    vector<QueryResult> results;
    vector<vector<Point>> allPoints;

    results.reserve(Q);
    allPoints.reserve(Q);

    for (int qi = 0; qi < Q; ++qi) {
        string queryLine;

        if (!getline(cin, queryLine))
            queryLine = "";

        vector<string> tokens =
            tachTu(queryLine);

        int k = 0;

        QueryResult result;
        result.invalid = true;

        vector<Point> points;

        if (!tokens.empty() &&
            chuyenSoNguyenKhongAm(tokens[0], k) &&
            k >= 2 && k <= 8 &&
            tokens.size() == (size_t)(1 + 2 * k)) {
            bool valid = true;
            points.reserve(k);

            for (int i = 0; i < k; ++i) {
                int r, c;

                if (!chuyenSoNguyenKhongAm(
                    tokens[1 + 2 * i], r) ||
                    !chuyenSoNguyenKhongAm(
                        tokens[2 + 2 * i], c)) {
                    valid = false;
                    break;
                }

                if (r >= R || c >= C ||
                    grid[r][c] == '#') {
                    valid = false;
                    break;
                }

                points.push_back({ r, c });
            }

            if (valid) {
                result = giaiTruyVan(grid, points);
                result.invalid = false;
            }
        }

        results.push_back(result);
        allPoints.push_back(points);
    }

    for (const QueryResult& result : results) {
        if (result.invalid)
            cout << "INVALID\n";
        else if (!result.reachable)
            cout << "-1\n";
        else
            cout << result.steps << '\n';
    }

    for (int i = 0; i < Q; ++i) {
        inDuongDi(
            grid,
            allPoints[i],
            results[i]
        );
    }

    return 0;
}