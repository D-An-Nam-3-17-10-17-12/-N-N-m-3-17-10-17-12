
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
#include <climits>
#include <limits>

using namespace std;

// Luu thong tin ban do kho
struct KhoHang
{
    int R, C;
    vector<string> banDo;
};

int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

// BFS tinh khoang cach
int bfs(KhoHang kho, int start, int finish)
{
    int n = kho.R * kho.C;
    vector<int> dist(n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (u == finish)
            return dist[u];

        int x = u / kho.C;
        int y = u % kho.C;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= kho.R ||
                ny < 0 || ny >= kho.C)
                continue;

            if (kho.banDo[nx][ny] == '#')
                continue;

            int v = nx * kho.C + ny;

            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return -1;
}

// BFS truy vet duong di
vector<int> bfsPath(KhoHang kho, int start, int finish)
{
    int n = kho.R * kho.C;

    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (u == finish)
            break;

        int x = u / kho.C;
        int y = u % kho.C;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= kho.R ||
                ny < 0 || ny >= kho.C)
                continue;

            if (kho.banDo[nx][ny] == '#')
                continue;

            int v = nx * kho.C + ny;

            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;

    if (dist[finish] == -1)
        return path;

    int cur = finish;

    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    return path;
}

// Chuyen chuoi thanh so nguyen
bool chuyenSo(const string& s, long long& value)
{
    try
    {
        size_t pos;
        value = stoll(s, &pos);
        return pos == s.size();
    }
    catch (...)
    {
        return false;
    }
}

// Xu ly tung truy van
void xuLyTruyVan(
    KhoHang kho,
    const string& dong,
    string& ketQua,
    string& duongDi)
{
    vector<string> token;
    stringstream ss(dong);
    string s;

    while (ss >> s)
        token.push_back(s);

    long long k;

    if (token.empty() || !chuyenSo(token[0], k))
    {
        ketQua = "INVALID";
        duongDi = "-";
        return;
    }

    if (k < 2 || k > 8)
    {
        ketQua = "INVALID";
        duongDi = "-";
        return;
    }

    if ((long long)token.size() != 1 + 2 * k)
    {
        ketQua = "INVALID";
        duongDi = "-";
        return;
    }

    vector<int> diem(k);

    // Kiem tra toa do
    for (int i = 0; i < k; i++)
    {
        long long r, c;

        if (!chuyenSo(token[1 + 2 * i], r) ||
            !chuyenSo(token[2 + 2 * i], c))
        {
            ketQua = "INVALID";
            duongDi = "-";
            return;
        }

        if (r < 0 || r >= kho.R ||
            c < 0 || c >= kho.C)
        {
            ketQua = "INVALID";
            duongDi = "-";
            return;
        }

        if (kho.banDo[r][c] == '#')
        {
            ketQua = "INVALID";
            duongDi = "-";
            return;
        }

        diem[i] = (int)r * kho.C + (int)c;
    }

    // Tinh khoang cach giua cac diem bang BFS
    vector<vector<int>> d(k, vector<int>(k, -1));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            d[i][j] = bfs(kho, diem[i], diem[j]);
        }
    }

    // Bitmask DP
    int m = k - 1;
    int N = 1 << m;

    const long long INF = LLONG_MAX / 4;

    vector<vector<long long>> dp(
        N, vector<long long>(m, INF));

    vector<vector<int>> trace(
        N, vector<int>(m, -1));

    // Khoi tao tu diem xuat phat
    for (int i = 0; i < m; i++)
    {
        if (d[0][i + 1] != -1)
            dp[1 << i][i] = d[0][i + 1];
    }

    // Quy hoach dong
    for (int mask = 1; mask < N; mask++)
    {
        for (int u = 0; u < m; u++)
        {
            if (!(mask & (1 << u)))
                continue;

            if (dp[mask][u] == INF)
                continue;

            for (int v = 0; v < m; v++)
            {
                if (mask & (1 << v))
                    continue;

                if (d[u + 1][v + 1] == -1)
                    continue;

                int newMask = mask | (1 << v);

                long long newCost =
                    dp[mask][u] + d[u + 1][v + 1];

                if (newCost < dp[newMask][v])
                {
                    dp[newMask][v] = newCost;
                    trace[newMask][v] = u;
                }
            }
        }
    }

    // Tim ket qua nho nhat
    int fullMask = N - 1;
    long long ans = INF;
    int last = -1;

    for (int i = 0; i < m; i++)
    {
        if (dp[fullMask][i] < ans)
        {
            ans = dp[fullMask][i];
            last = i;
        }
    }

    if (ans == INF)
    {
        ketQua = "-1";
        duongDi = "-";
        return;
    }

    ketQua = to_string(ans);

    // Truy vet thu tu cac diem
    vector<int> thuTu;
    int mask = fullMask;

    while (last != -1)
    {
        thuTu.push_back(last + 1);

        int pre = trace[mask][last];

        mask ^= (1 << last);
        last = pre;
    }

    reverse(thuTu.begin(), thuTu.end());

    // Ghép cac duong di BFS
    vector<int> fullPath;
    fullPath.push_back(diem[0]);

    int currentIndex = 0;

    for (int p : thuTu)
    {
        vector<int> path =
            bfsPath(kho, diem[currentIndex], diem[p]);

        for (int j = 1; j < (int)path.size(); j++)
            fullPath.push_back(path[j]);

        currentIndex = p;
    }

    // In toi da 10 buoc di chuyen sau o bat dau
    stringstream out;

    int soO = min((int)fullPath.size(), 11);

    for (int i = 0; i < soO; i++)
    {
        int x = fullPath[i] / kho.C;
        int y = fullPath[i] % kho.C;

        if (i > 0)
            out << " ";

        out << "(" << x << "," << y << ")";
    }

    if ((int)fullPath.size() > 11)
        out << " ...";

    duongDi = out.str();
}

// HAM MAIN
int main()
{
    KhoHang kho;

    cout << "=== CHUONG TRINH TIM DUONG DI TRONG KHO ===\n";

    cout << "Nhap so hang (R) va so cot (C) cua kho: ";
    cin >> kho.R >> kho.C;

    kho.banDo.resize(kho.R);

    cout << "Nhap ban do kho (" << kho.R
        << " dong, moi dong " << kho.C
        << " ky tu . hoac #):\n";

    for (int i = 0; i < kho.R; i++)
    {
        cin >> kho.banDo[i];
    }

    int Q;

    cout << "Nhap so luong truy van Q: ";
    cin >> Q;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> ketQua(Q);
    vector<string> duongDi(Q);

    // Xu ly tung truy van
    for (int i = 0; i < Q; i++)
    {
        string dong;

        cout << "Nhap truy van " << i + 1
            << " (k va cac toa do):\n";

        getline(cin, dong);

        xuLyTruyVan(kho, dong, ketQua[i], duongDi[i]);
    }

    // Phan 1: Ket qua so buoc
    cout << "\n=== PHAN 1: SO BUOC NGAN NHAT ===\n";

    for (int i = 0; i < Q; i++)
        cout << ketQua[i] << "\n";

    // Phan 2: Duong di
    cout << "\n=== PHAN 2: CAC O DI CHUYEN ===\n";

    for (int i = 0; i < Q; i++)
        cout << duongDi[i] << "\n";

    cout << "\n=== KET THUC CHUONG TRINH ===\n";

    return 0;
}
