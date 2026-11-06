#include <bits/stdc++.h>
using namespace std;

static bool parseNonNegativeInt(const string& s, int& value) {
    if (s.empty()) return false;
    long long x = 0;
    for (char ch : s) {
        if (ch < '0' || ch > '9') return false;
        x = x * 10 + (ch - '0');
        if (x > INT_MAX) return false;
    }
    value = static_cast<int>(x);
    return true;
}

struct Point {
    int r, c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    if (!(cin >> R >> C)) return 0;

    vector<string> grid(R);
    for (int i = 0; i < R; ++i) cin >> grid[i];

    string line;
    getline(cin, line); 

    if (!getline(cin, line)) return 0;
    if (!line.empty() && line.back() == '\r') line.pop_back();
    while (line.empty() && cin.good()) {
        if (!getline(cin, line)) break;
        if (!line.empty() && line.back() == '\r') line.pop_back();
    }

    int Q;
    if (!parseNonNegativeInt(line, Q) || Q < 1 || Q > 10) return 0;

    const int N = R * C;
    auto id = [C](int r, int c) { return r * C + c; };
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    auto bfsDistances = [&](int source) {
        vector<int> dist(N, -1);
        queue<int> qu;
        dist[source] = 0;
        qu.push(source);

        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();
            int r = u / C, c = u % C;

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (grid[nr][nc] == '#') continue;
                int v = id(nr, nc);
                if (dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                qu.push(v);
            }
        }
        return dist;
    };

    auto getPath = [&](int source, int destination) {
        vector<int> parent(N, -1);
        queue<int> qu;
        parent[source] = source;
        qu.push(source);

        while (!qu.empty() && parent[destination] == -1) {
            int u = qu.front();
            qu.pop();
            int r = u / C, c = u % C;

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (grid[nr][nc] == '#') continue;
                int v = id(nr, nc);
                if (parent[v] != -1) continue;
                parent[v] = u;
                qu.push(v);
            }
        }

        vector<int> path;
        if (parent[destination] == -1) return path;
        for (int cur = destination; cur != source; cur = parent[cur])
            path.push_back(cur);
        path.push_back(source);
        reverse(path.begin(), path.end());
        return path;
    };

    vector<string> answers;
    vector<string> paths;
    answers.reserve(Q);
    paths.reserve(Q);

    for (int qi = 0; qi < Q; ++qi) {
        if (!getline(cin, line)) line.clear();
        if (!line.empty() && line.back() == '\r') line.pop_back();

        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (ss >> token) tokens.push_back(token);

        int k;
        bool valid = !tokens.empty() && parseNonNegativeInt(tokens[0], k)
                     && k >= 2 && k <= 8
                     && tokens.size() == static_cast<size_t>(1 + 2 * k);

        vector<Point> points;
        if (valid) {
            for (int i = 0; i < k; ++i) {
                int r, c;
                if (!parseNonNegativeInt(tokens[1 + 2 * i], r) ||
                    !parseNonNegativeInt(tokens[2 + 2 * i], c) ||
                    r < 0 || r >= R || c < 0 || c >= C ||
                    grid[r][c] == '#') {
                    valid = false;
                    break;
                }
                points.push_back({r, c});
            }
        }

        if (!valid) {
            answers.push_back("INVALID");
            paths.push_back("-");
            continue;
        }

        vector<int> pointIds;
        for (const auto& p : points) pointIds.push_back(id(p.r, p.c));

        vector<vector<int>> dist(k, vector<int>(k, -1));
        for (int i = 0; i < k; ++i) {
            vector<int> allDist = bfsDistances(pointIds[i]);
            for (int j = 0; j < k; ++j)
                dist[i][j] = allDist[pointIds[j]];
        }

        int m = k - 1;
        int states = 1 << m;
        const int INF = INT_MAX / 4;
        vector<vector<int>> dp(states, vector<int>(m, INF));
        vector<vector<int>> parent(states, vector<int>(m, -1));

        for (int j = 0; j < m; ++j) {
            if (dist[0][j + 1] != -1)
                dp[1 << j][j] = dist[0][j + 1];
        }

        for (int mask = 1; mask < states; ++mask) {
            for (int last = 0; last < m; ++last) {
                if (!(mask & (1 << last)) || dp[mask][last] == INF) continue;

                for (int nxt = 0; nxt < m; ++nxt) {
                    if (mask & (1 << nxt)) continue;
                    int d = dist[last + 1][nxt + 1];
                    if (d == -1) continue;

                    int nextMask = mask | (1 << nxt);
                    int candidate = dp[mask][last] + d;
                    if (candidate < dp[nextMask][nxt]) {
                        dp[nextMask][nxt] = candidate;
                        parent[nextMask][nxt] = last;
                    }
                }
            }
        }

        int fullMask = states - 1;
        int bestLast = -1, bestDistance = INF;
        for (int last = 0; last < m; ++last) {
            if (dp[fullMask][last] < bestDistance) {
                bestDistance = dp[fullMask][last];
                bestLast = last;
            }
        }

        if (bestLast == -1 || bestDistance == INF) {
            answers.push_back("-1");
            paths.push_back("-");
            continue;
        }

        answers.push_back(to_string(bestDistance));

        vector<int> order;
        int mask = fullMask, last = bestLast;
        while (last != -1) {
            order.push_back(last + 1); 
            int previous = parent[mask][last];
            mask ^= (1 << last);
            last = previous;
        }
        reverse(order.begin(), order.end());

        vector<int> fullPath;
        fullPath.push_back(pointIds[0]);
        int current = pointIds[0];

        for (int pointIndex : order) {
            int destination = pointIds[pointIndex];
            vector<int> segment = getPath(current, destination);
            
            for (size_t t = 1; t < segment.size(); ++t)
                fullPath.push_back(segment[t]);
            current = destination;
        }

        ostringstream out;
        int shown = min<int>(static_cast<int>(fullPath.size()), 11);
        for (int i = 0; i < shown; ++i) {
            if (i) out << ' ';
            int r = fullPath[i] / C, c = fullPath[i] % C;
            out << '(' << r << ',' << c << ')';
        }
        if (static_cast<int>(fullPath.size()) - 1 > 10) out << " ...";
        paths.push_back(out.str());
    }

    for (const string& s : answers) cout << s << '\n';
    for (const string& s : paths) cout << s << '\n';

    return 0;
}
