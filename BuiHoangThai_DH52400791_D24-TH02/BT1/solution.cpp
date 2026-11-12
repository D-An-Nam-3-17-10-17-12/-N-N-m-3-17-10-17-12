
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <sstream>
#include <cstddef>

using namespace std;

const int INF = 1e9;

int R, C;
vector<string> warehouse;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

bool isValidCell(int x, int y) {
    return x >= 0 && x < R &&
           y >= 0 && y < C &&
           warehouse[x][y] == '.';
}

// BFS: tinh khoang cach tu start den tat ca cac o co the di toi.
// parent[v] luu dinh dung truoc v de truy vet duong di.
vector<int> bfs(int start, vector<int>& parent) {
    int n = R * C;
    vector<int> dist(n, -1);
    parent.assign(n, -2);

    queue<int> q;
    dist[start] = 0;
    parent[start] = -1;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int x = u / C;
        int y = u % C;

        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (!isValidCell(nx, ny)) continue;

            int v = nx * C + ny;
            if (dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            parent[v] = u;
            q.push(v);
        }
    }

    return dist;
}

// Tra ve danh sach cac o tren duong di ngan nhat tu start den finish.
vector<int> getPath(int start, int finish) {
    vector<int> parent;
    vector<int> dist = bfs(start, parent);

    if (dist[finish] == -1) return {};

    vector<int> path;
    for (int cur = finish; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

void solveQuery(const vector<long long>& a,
                string& distanceAnswer,
                string& pathAnswer) {
    distanceAnswer.clear();
    pathAnswer.clear();

    // Moi truy van co dang: k r1 c1 r2 c2 ... rk ck.
    if (a.empty()) {
        distanceAnswer = "INVALID";
        pathAnswer = "-";
        return;
    }

    long long kValue = a[0];
    if (kValue < 2 || kValue > 8 ||
        a.size() != static_cast<size_t>(1 + 2 * kValue)) {
        distanceAnswer = "INVALID";
        pathAnswer = "-";
        return;
    }

    int k = static_cast<int>(kValue);
    vector<int> points;
    points.reserve(k);

    // Kiem tra toa do va vat can.
    for (int i = 0; i < k; ++i) {
        long long x = a[1 + 2 * i];
        long long y = a[2 + 2 * i];

        if (x < 0 || x >= R || y < 0 || y >= C) {
            distanceAnswer = "INVALID";
            pathAnswer = "-";
            return;
        }

        if (warehouse[static_cast<int>(x)][static_cast<int>(y)] != '.') {
            distanceAnswer = "INVALID";
            pathAnswer = "-";
            return;
        }

        points.push_back(static_cast<int>(x) * C + static_cast<int>(y));
    }

    // Tinh khoang cach BFS giua moi cap diem trong truy van.
    int dist[8][8];
    for (int i = 0; i < k; ++i) {
        vector<int> parent;
        vector<int> allDist = bfs(points[i], parent);

        for (int j = 0; j < k; ++j) {
            dist[i][j] = allDist[points[j]];
        }
    }

    // Diem 0 la diem xuat phat; can tham k-1 diem con lai.
    int m = k - 1;
    int stateCount = 1 << m;

    // dp[mask][last]: chi phi nho nhat khi da tham cac diem trong mask
    // va ket thuc tai diem last (last nam trong [1..m]).
    vector<vector<int>> dp(stateCount, vector<int>(m, INF));
    vector<vector<int>> trace(stateCount, vector<int>(m, -1));

    for (int i = 0; i < m; ++i) {
        if (dist[0][i + 1] != -1) {
            dp[1 << i][i] = dist[0][i + 1];
        }
    }

    for (int mask = 1; mask < stateCount; ++mask) {
        for (int last = 0; last < m; ++last) {
            if (!(mask & (1 << last)) || dp[mask][last] == INF) {
                continue;
            }

            for (int next = 0; next < m; ++next) {
                if (mask & (1 << next)) continue;

                int d = dist[last + 1][next + 1];
                if (d == -1) continue;

                int newMask = mask | (1 << next);
                int newCost = dp[mask][last] + d;

                if (newCost < dp[newMask][next]) {
                    dp[newMask][next] = newCost;
                    trace[newMask][next] = last;
                }
            }
        }
    }

    // Chon diem ket thuc tot nhat sau khi da tham tat ca diem.
    int fullMask = stateCount - 1;
    int best = INF;
    int last = -1;

    for (int i = 0; i < m; ++i) {
        if (dp[fullMask][i] < best) {
            best = dp[fullMask][i];
            last = i;
        }
    }

    if (best == INF) {
        distanceAnswer = "-1";
        pathAnswer = "-";
        return;
    }

    distanceAnswer = to_string(best);

    // Truy vet thu tu cac diem can tham.
    vector<int> order;
    int mask = fullMask;

    while (last != -1) {
        order.push_back(last + 1);
        int previous = trace[mask][last];
        mask ^= (1 << last);
        last = previous;
    }
    reverse(order.begin(), order.end());

    // Ghép duong di BFS giua cac diem theo thu tu DP tim duoc.
    vector<int> fullPath;
    fullPath.push_back(points[0]);

    int current = points[0];
    for (int pointIndex : order) {
        vector<int> segment = getPath(current, points[pointIndex]);

        // Bo qua phan tu dau vi no trung voi o cuoi cua doan truoc.
        for (int j = 1; j < static_cast<int>(segment.size()); ++j) {
            fullPath.push_back(segment[j]);
        }
        current = points[pointIndex];
    }

    // In o xuat phat va toi da 10 o tiep theo (10 buoc di chuyen).
    // Neu con duong di phia sau thi them "...".
    stringstream output;
    int limit = min(11, static_cast<int>(fullPath.size()));

    for (int i = 0; i < limit; ++i) {
        if (i > 0) output << ' ';
        int x = fullPath[i] / C;
        int y = fullPath[i] % C;
        output << '(' << x << ',' << y << ')';
    }

    if (static_cast<int>(fullPath.size()) > 11) {
        output << " ...";
    }

    pathAnswer = output.str();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> R >> C)) return 0;

    warehouse.resize(R);
    for (int i = 0; i < R; ++i) {
        cin >> warehouse[i];
    }

    int Q;
    cin >> Q;

    string line;
    getline(cin, line); // Bo ky tu xuong dong sau Q.

    vector<string> distanceAnswers;
    vector<string> pathAnswers;

    for (int i = 0; i < Q; ++i) {
        if (!getline(cin, line)) line.clear();

        stringstream ss(line);
        vector<long long> values;
        string token;
        bool malformed = false;

        // Doc tung token de phat hien ca ky tu khong phai so
        // va truong hop co token thua sau cac toa do.
        while (ss >> token) {
            try {
                size_t used = 0;
                long long value = stoll(token, &used);
                if (used != token.size()) {
                    malformed = true;
                    break;
                }
                values.push_back(value);
            } catch (...) {
                malformed = true;
                break;
            }
        }

        if (malformed) values.clear();

        string distanceAnswer, pathAnswer;
        solveQuery(values, distanceAnswer, pathAnswer);

        distanceAnswers.push_back(distanceAnswer);
        pathAnswers.push_back(pathAnswer);
    }

    // Phan 1: Q dong ket qua so buoc.
    for (const string& answer : distanceAnswers) {
        cout << answer << '\n';
    }

    // Phan 2: Q dong mo ta duong di.
    for (const string& answer : pathAnswers) {
        cout << answer << '\n';
    }

    return 0;
}
