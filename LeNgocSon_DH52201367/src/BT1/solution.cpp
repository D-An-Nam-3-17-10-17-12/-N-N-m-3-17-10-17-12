#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>

using std::vector;
using std::string;
using std::queue;
using namespace std;

struct Point
{
	int r;
	int c;
};

int R, C;	
vector<string> map_grid;
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };
vector<int> dist_arr;
vector<int> parent_arr;

void BFS(Point start)
{
    fill(dist_arr.begin(), dist_arr.end(), -1);
    std::queue<int> q;
    int sId = start.r * C + start.c;

    q.push(sId);
    dist_arr[sId] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int ur = u / C, uc = u % C, d = dist_arr[u];

        for (int i = 0; i < 4; i++) {
            int nr = ur + dr[i], nc = uc + dc[i];
            // Chỉ đi vào các ô '.' nằm trong ranh giới
            if (nr >= 0 && nr < R && nc >= 0 && nc < C && map_grid[nr][nc] == '.') {
                int nId = nr * C + nc;
                if (dist_arr[nId] == -1) {
                    dist_arr[nId] = d + 1;
                    parent_arr[nId] = u;
                    q.push(nId);
                }
            }
        }
    }
}

vector<Point> GetPathTrace(Point start, Point end) {
    BFS(start);
    vector<Point> path;
    int currId = end.r * C + end.c;
    int startId = start.r * C + start.c;

    while (currId != startId) {
        path.push_back({ currId / C, currId % C });
        currId = parent_arr[currId];
    }
    path.push_back(start);
    reverse(path.begin(), path.end()); // Đảo ngược vì truy xuất từ đích về nguồn
    return path;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    if (!(std::cin >> R >> C)) return 0;
    map_grid.resize(R);
    for (int i = 0; i < R; i++) {
        std::cin >> map_grid[i];
    }

    int Q;
    if (!(std::cin >> Q)) return 0;

    string dummy;
    getline(std::cin, dummy);

    dist_arr.resize(R * C);
    parent_arr.resize(R * C);

    vector<string> out1, out2;

    for (int i = 0; i < Q; i++) {
        string line;
        getline(std::cin, line);
        if (line.empty()) {
            out1.push_back("INVALID"); out2.push_back("-"); continue;
        }

        stringstream ss(line);
        int k;
        if (!(ss >> k) || k < 2 || k > 8) {
            out1.push_back("INVALID"); out2.push_back("-"); continue;
        }

        vector<Point> points;
        bool valid = true;
        for (int j = 0; j < k; j++) {
            int r, c;
            if (!(ss >> r >> c) || r < 0 || r >= R || c < 0 || c >= C || map_grid[r][c] == '#') {
                valid = false; break;
            }
            points.push_back({ r, c });
        }

        string extra;
        if (!valid || (ss >> extra)) {
            out1.push_back("INVALID"); out2.push_back("-"); continue;
        }

        vector<vector<int>> D(k, vector<int>(k, 0));
        bool possible = true;

        // Tính ma trận khoảng cách giữa toàn bộ các điểm lấy hàng
        for (int j = 0; j < k; j++) {
            BFS(points[j]);
            for (int m = 0; m < k; m++) {
                D[j][m] = dist_arr[points[m].r * C + points[m].c];
                if (j == 0 && D[j][m] == -1) possible = false;
            }
        }

        if (!possible) {
            out1.push_back("-1"); out2.push_back("-"); continue;
        }

        // Sinh hoán vị các điểm cần đến (trừ điểm xuất phát)
        vector<int> arr(k - 1);
        for (int j = 0; j < k - 1; j++) arr[j] = j + 1;

        int minCost = 2e9;
        vector<int> bestArr;

        do {
            int cost = 0, curr = 0;
            for (int next : arr) {
                cost += D[curr][next];
                curr = next;
            }
            if (cost < minCost) {
                minCost = cost;
                bestArr = arr;
            }
        } while (next_permutation(arr.begin(), arr.end()));

        out1.push_back(to_string(minCost));

        // Nối và lọc các đoạn đường đi của lộ trình ngắn nhất
        vector<Point> fullPath;
        int currentIdx = 0;
        for (int nextIdx : bestArr) {
            vector<Point> seg = GetPathTrace(points[currentIdx], points[nextIdx]);
            if (!fullPath.empty()) {
                for (size_t j = 1; j < seg.size(); j++) fullPath.push_back(seg[j]);
            }
            else {
                fullPath.insert(fullPath.end(), seg.begin(), seg.end());
            }
            currentIdx = nextIdx;
        }

        // Chuẩn hóa định dạng chuỗi in (ô xuất phát + tối đa 10 ô tiếp theo)
        string trace = "";
        int maxPrint = min(11, (int)fullPath.size());
        for (int j = 0; j < maxPrint; j++) {
            trace += "(" + to_string(fullPath[j].r) + "," + to_string(fullPath[j].c) + ") ";
        }
        if (fullPath.size() > 11) trace += "...";

        while (!trace.empty() && trace.back() == ' ') trace.pop_back();
        out2.push_back(trace);
    }

    // In toàn bộ Phần 1 (số bước) sau đó in Phần 2 (tọa độ)
    for (const string& s : out1) cout << s << "\n";
    for (const string& s : out2) cout << s << "\n";

    return 0;
}