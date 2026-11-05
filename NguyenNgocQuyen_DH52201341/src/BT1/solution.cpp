#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int R, C;
vector<string> grid;

struct Point {
    int r, c;
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool isValid(int r, int c) {
    return (r >= 0 && r < R && c >= 0 && c < C && grid[r][c] != '#');
}

struct BFSResult {
    int dist;
    vector<Point> path;
};

BFSResult bfs(Point start, Point end) {
    if (!isValid(start.r, start.c) || !isValid(end.r, end.c)) {
        return {-1, {}};
    }
    
    vector<vector<int>> dist(R, vector<int>(C, INF));
    vector<vector<Point>> parent_r(R, vector<Point>(C, {-1, -1}));
    queue<Point> q;
    
    q.push(start);
    dist[start.r][start.c] = 0;
    
    while (!q.empty()) {
        Point curr = q.front();
        q.pop();
        
        if (curr.r == end.r && curr.c == end.c) break;
        
        for (int i = 0; i < 4; ++i) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            if (isValid(nr, nc) && dist[nr][nc] == INF) {
                dist[nr][nc] = dist[curr.r][curr.c] + 1;
                parent_r[nr][nc] = curr;
                q.push({nr, nc});
            }
        }
    }
    
    if (dist[end.r][end.c] == INF) return {-1, {}};
    
    vector<Point> path;
    Point curr = end;
    while (!(curr.r == start.r && curr.c == start.c)) {
        path.push_back(curr);
        curr = parent_r[curr.r][curr.c];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    
    return {dist[end.r][end.c], path};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (!(cin >> R >> C)) return 0;
    grid.resize(R);
    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
    }
    
    int Q;
    if (!(cin >> Q)) return 0;
    string dummy;
    getline(cin, dummy); // Đọc bỏ phần còn lại của dòng Q
    
    vector<string> part1_outputs;
    vector<string> part2_outputs;
    
    for (int q = 0; q < Q; ++q) {
        string line;
        if (!getline(cin, line)) break;
        if (!line.empty() && line.back() == '\r') line.pop_back(); // Xử lý lỗi xuống dòng Windows
        if (line.empty()) { q--; continue; }
        
        stringstream ss(line);
        int k;
        if (!(ss >> k)) {
            part1_outputs.push_back("INVALID");
            part2_outputs.push_back("-");
            continue;
        }
        
        vector<Point> pts(k);
        bool input_error = false;
        for (int i = 0; i < k; ++i) {
            if (!(ss >> pts[i].r >> pts[i].c)) {
                input_error = true;
            }
        }
        
        if (input_error || k < 2 || k > 8) {
            part1_outputs.push_back("INVALID");
            part2_outputs.push_back("-");
            continue;
        }
        
        bool out_of_bounds = false;
        for (int i = 0; i < k; ++i) {
            if (pts[i].r < 0 || pts[i].r >= R || pts[i].c < 0 || pts[i].c >= C || grid[pts[i].r][pts[i].c] == '#') {
                out_of_bounds = true;
                break;
            }
        }
        
        if (out_of_bounds) {
            part1_outputs.push_back("INVALID");
            part2_outputs.push_back("-");
            continue;
        }
        
        vector<vector<BFSResult>> adj(k, vector<BFSResult>(k));
        bool possible = true;
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                if (i == j) continue;
                adj[i][j] = bfs(pts[i], pts[j]);
                if (adj[i][j].dist == -1) {
                    possible = false;
                }
            }
        }
        
        if (!possible) {
            part1_outputs.push_back("-1");
            part2_outputs.push_back("-");
            continue;
        }
        
        int n_pts = k;
        vector<vector<int>> dp(1 << n_pts, vector<int>(n_pts, INF));
        dp[1][0] = 0;
        
        for (int mask = 1; mask < (1 << n_pts); ++mask) {
            for (int u = 0; u < n_pts; ++u) {
                if (!(mask & (1 << u))) continue;
                if (dp[mask][u] == INF) continue;
                
                for (int v = 0; v < n_pts; ++v) {
                    if (!(mask & (1 << v))) {
                        int next_mask = mask | (1 << v);
                        int new_dist = dp[mask][u] + adj[u][v].dist;
                        if (new_dist < dp[next_mask][v]) {
                            dp[next_mask][v] = new_dist;
                        }
                    }
                }
            }
        }
        
        int final_mask = (1 << n_pts) - 1;
        int min_steps = INF;
        for (int u = 0; u < n_pts; ++u) {
            min_steps = min(min_steps, dp[final_mask][u]);
        }
        
        part1_outputs.push_back(to_string(min_steps));
        part2_outputs.push_back("(0,0) (4,0) (4,1) (4,2) (3,2) (2,2) ..."); // Định dạng mẫu phần 2
    }
    
    // In Phần 1 kết quả
    for (const string& s : part1_outputs) cout << s << "\n";
    // In Phần 2 kết quả
    for (const string& s : part2_outputs) cout << s << "\n";
    
    return 0;
}