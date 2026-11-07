#include "thuvien.h"

#include <algorithm>
#include <climits>
#include <sstream>
#include <queue>
#include <cctype>
namespace {
    bool parseUnsigned(const std::string& s, int& value) {
        if (s.empty()) return false;
        long long number = 0;
        for (unsigned char ch : s) {
            if (ch < '0' || ch > '9') return false;
            number = number * 10 + (ch - '0');
            if (number > INT_MAX) return false;
        }
        value = static_cast<int>(number);
        return true;
    }
}
WarehouseRouter::WarehouseRouter(
    int r, int c, const std::vector<std::string>& map
) : rows(r), cols(c), grid(map) {
}
bool WarehouseRouter::isValidPosition(int r, int c) const {
    return r >= 0 && r < rows&&
        c >= 0 && c < cols&&
        grid[r][c] == '.';
}
int WarehouseRouter::bfsDistances(
    int start, std::vector<int>& dist
) const {
    const int total = rows * cols;
    dist.assign(total, -1);
    std::queue<int> q;
    q.push(start);
    dist[start] = 0;
    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int r = u / cols;
        int c = u % cols;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;
            if (grid[nr][nc] == '#')
                continue;
            int v = nr * cols + nc;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return 0;
}
bool WarehouseRouter::buildPath(
    int start, int target, std::vector<int>& path
) const {
    const int total = rows * cols;
    std::vector<int> parent(total, -2);
    std::queue<int> q;
    q.push(start);
    parent[start] = -1;
    const int dr[4] = { -1, 1, 0, 0 };
    const int dc[4] = { 0, 0, -1, 1 };
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) break;
        int r = u / cols;
        int c = u % cols;
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
                continue;
            if (grid[nr][nc] == '#')
                continue;
            int v = nr * cols + nc;
            if (parent[v] == -2) {
                parent[v] = u;
                q.push(v);
            }
        }
    }
    if (parent[target] == -2) return false;
    path.clear();
    for (int cur = target; cur != -1; cur = parent[cur])
        path.push_back(cur);
    std::reverse(path.begin(), path.end());
    return true;
}
void WarehouseRouter::processQuery(
    const std::string& line,
    std::string& stepOutput,
    std::string& pathOutput
) const {
    std::istringstream input(line);
    std::vector<std::string> tokens;
    std::string token;
    while (input >> token)
        tokens.push_back(token);
    stepOutput = "INVALID";
    pathOutput = "-";
    if (tokens.empty()) return;
    int k;
    if (!parseUnsigned(tokens[0], k) || k < 2 || k > 8)
        return;
    if (tokens.size() != static_cast<std::size_t>(1 + 2 * k))
        return;
    std::vector<int> points;
    points.reserve(k);
    for (int i = 0; i < k; ++i) {
        int r, c;
        if (!parseUnsigned(tokens[1 + 2 * i], r) ||
            !parseUnsigned(tokens[2 + 2 * i], c)) {
            return;
        }
        if (!isValidPosition(r, c))
            return;
        points.push_back(r * cols + c);
    }
    std::vector<std::vector<int> > distanceMatrix(
        k, std::vector<int>(k, -1)
    );
    for (int i = 0; i < k; ++i) {
        std::vector<int> dist;
        bfsDistances(points[i], dist);
        for (int j = 0; j < k; ++j)
            distanceMatrix[i][j] = dist[points[j]];
    }
    const int m = k - 1;
    const int states = 1 << m;
    const int INF = INT_MAX / 4;
    std::vector<std::vector<int> > dp(
        states, std::vector<int>(m, INF)
    );
    std::vector<std::vector<int> > parent(
        states, std::vector<int>(m, -1)
    );
    for (int i = 0; i < m; ++i) {
        int d = distanceMatrix[0][i + 1];
        if (d != -1)
            dp[1 << i][i] = d;
    }
    for (int mask = 1; mask < states; ++mask) {
        for (int last = 0; last < m; ++last) {
            if (!(mask & (1 << last)) || dp[mask][last] == INF)
                continue;
            for (int next = 0; next < m; ++next) {
                if (mask & (1 << next)) continue;
                int d = distanceMatrix[last + 1][next + 1];
                if (d == -1) continue;
                int newMask = mask | (1 << next);
                int candidate = dp[mask][last] + d;
                if (candidate < dp[newMask][next]) {
                    dp[newMask][next] = candidate;
                    parent[newMask][next] = last;
                }
            }
        }
    }
    int fullMask = states - 1;
    int bestSteps = INF;
    int last = -1;
    for (int i = 0; i < m; ++i) {
        if (dp[fullMask][i] < bestSteps) {
            bestSteps = dp[fullMask][i];
            last = i;
        }
    }
    if (last == -1 || bestSteps == INF) {
        stepOutput = "-1";
        pathOutput = "-";
        return;
    }
    std::vector<int> order;
    int mask = fullMask;
    int current = last;
    while (current != -1) {
        order.push_back(current + 1);
        int previous = parent[mask][current];
        mask ^= (1 << current);
        current = previous;
    }
    std::reverse(order.begin(), order.end());
    std::vector<int> routePoints;
    routePoints.push_back(0);
    for (int id : order)
        routePoints.push_back(id);
    std::vector<int> fullPath;
    fullPath.push_back(points[routePoints[0]]);
    for (std::size_t i = 1; i < routePoints.size(); ++i) {
        int from = points[routePoints[i - 1]];
        int to = points[routePoints[i]];
        std::vector<int> segment;
        if (!buildPath(from, to, segment)) {
            stepOutput = "-1";
            pathOutput = "-";
            return;
        }
        for (std::size_t j = 1; j < segment.size(); ++j)
            fullPath.push_back(segment[j]);
    }
    stepOutput = std::to_string(bestSteps);
    std::ostringstream outputPath;
    const std::size_t limit = 10;
    std::size_t shown = std::min(limit, fullPath.size());

    for (std::size_t i = 0; i < shown; ++i) {
        if (i > 0) outputPath << ' ';
        int r = fullPath[i] / cols;
        int c = fullPath[i] % cols;
        outputPath << '(' << r << ',' << c << ')';
    }
    if (bestSteps > 10) {
        if (shown > 0) outputPath << ' ';
        outputPath << "...";
    }

    pathOutput = outputPath.str();
}

