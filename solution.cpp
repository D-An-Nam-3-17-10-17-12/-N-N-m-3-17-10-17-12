// Bai 1 - Tim duong ngan nhat trong kho hang
// Cau truc du lieu: luoi 2D (luu phang), BFS cho khoang cach, thu moi thu tu cho nhieu diem.
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace std;

static int R, C;
static vector<string> grid;
static const int DR[4] = { -1, 1, 0, 0 };
static const int DC[4] = { 0, 0, -1, 1 };

static string readLine() {
    string s;
    getline(cin, s);
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
    return s;
}

static bool isDigits(const string& s) {
    if (s.empty()) return false;
    for (char ch : s)
        if (ch < '0' || ch > '9') return false;
    return true;
}

// BFS tu o src, tra ve mang khoang cach (-1 neu khong toi duoc)
static vector<int> bfs(int src) {
    vector<int> dist(R * C, -1);
    vector<int> q;
    q.reserve(R * C);
    dist[src] = 0;
    q.push_back(src);
    for (size_t head = 0; head < q.size(); head++) {
        int cur = q[head];
        int r = cur / C, c = cur % C;
        for (int d = 0; d < 4; d++) {
            int nr = r + DR[d], nc = c + DC[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            if (grid[nr][nc] == '#') continue;
            int nxt = nr * C + nc;
            if (dist[nxt] != -1) continue;
            dist[nxt] = dist[cur] + 1;
            q.push_back(nxt);
        }
    }
    return dist;
}

// Phan tich 1 truy van. Hop le -> tra ve true va dien pts (id o = r*C + c)
static bool parseQuery(const string& line, vector<int>& pts) {
    istringstream iss(line);
    vector<string> tok;
    string t;
    while (iss >> t) tok.push_back(t);
    if (tok.empty()) return false;
    if (!isDigits(tok[0]) || tok[0].size() > 2) return false;
    int k = stoi(tok[0]);
    if (k < 2 || k > 8) return false;
    if ((int)tok.size() != 1 + 2 * k) return false;
    pts.clear();
    for (int i = 0; i < k; i++) {
        const string& a = tok[1 + 2 * i];
        const string& b = tok[2 + 2 * i];
        if (!isDigits(a) || !isDigits(b)) return false;
        if (a.size() > 7 || b.size() > 7) return false;  // chac chan ngoai kho
        int r = stoi(a), c = stoi(b);
        if (r >= R || c >= C) return false;
        if (grid[r][c] == '#') return false;
        pts.push_back(r * C + c);
    }
    return true;
}

// Cac o (toi da 11) cua duong di tu o s den o t, dung mang dist tinh tu t
static void walk(int s, int t, const vector<int>& distT, vector<int>& path, size_t limit) {
    int cur = s;
    while (cur != t && path.size() < limit) {
        int r = cur / C, c = cur % C;
        for (int d = 0; d < 4; d++) {
            int nr = r + DR[d], nc = c + DC[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            int nxt = nr * C + nc;
            if (distT[nxt] != -1 && distT[nxt] == distT[cur] - 1) {
                cur = nxt;
                path.push_back(cur);
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    {
        istringstream iss(readLine());
        iss >> R >> C;
    }
    grid.assign(R, string(C, '#'));
    for (int i = 0; i < R; i++) {
        string s = readLine();
        for (int j = 0; j < C && j < (int)s.size(); j++) grid[i][j] = s[j];
    }
    string ql = readLine();
    while (ql.empty() && cin) ql = readLine();
    int Q = stoi(ql);

    vector<string> part1(Q), part2(Q);

    for (int qi = 0; qi < Q; qi++) {
        string line = readLine();
        vector<int> pts;
        if (!parseQuery(line, pts)) {
            part1[qi] = "INVALID";
            part2[qi] = "-";
            continue;
        }
        int k = pts.size();

        // BFS tu moi diem, luu lai de tinh khoang cach tung cap va dung lai de dung duong di
        vector<vector<int>> dist(k);
        for (int i = 0; i < k; i++) dist[i] = bfs(pts[i]);

        // d[i][j] = khoang cach giua diem i va diem j
        vector<vector<long long>> d(k, vector<long long>(k, -1));
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++) d[i][j] = dist[i][pts[j]];

        // Thu moi thu tu tham cac diem 1..k-1 (diem 0 la xuat phat)
        vector<int> order(k - 1);
        iota(order.begin(), order.end(), 1);
        long long best = -1;
        vector<int> bestOrder;
        do {
            long long total = 0;
            int prev = 0;
            bool ok = true;
            for (int x : order) {
                if (d[prev][x] < 0) { ok = false; break; }
                total += d[prev][x];
                prev = x;
            }
            if (ok && (best < 0 || total < best)) {
                best = total;
                bestOrder = order;
            }
        } while (next_permutation(order.begin(), order.end()));

        if (best < 0) {
            part1[qi] = "-1";
            part2[qi] = "-";
            continue;
        }
        part1[qi] = to_string(best);

        // Dung duong di: o xuat phat + toi da 10 o dau
        vector<int> path = { pts[0] };
        int prev = 0;
        for (int x : bestOrder) {
            if (path.size() >= 11) break;
            walk(pts[prev], pts[x], dist[x], path, 11);
            prev = x;
        }
        string out;
        for (size_t i = 0; i < path.size() && i < 11; i++) {
            if (i) out += ' ';
            out += "(" + to_string(path[i] / C) + "," + to_string(path[i] % C) + ")";
        }
        if (best > 10) out += " ...";
        part2[qi] = out;
    }

    string res;
    for (int i = 0; i < Q; i++) res += part1[i] + "\n";
    for (int i = 0; i < Q; i++) res += part2[i] + "\n";
    cout << res;
    return 0;
}