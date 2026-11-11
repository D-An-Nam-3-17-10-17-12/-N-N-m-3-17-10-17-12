#include "thuvien.h"

// Mang luu 4 huong di chuyen: len, xuong, trai, phai
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };


// ==================================================
// HAM 1: BFS TIM KHOANG CACH NGAN NHAT
// ==================================================

int bfs(KhoHang kho, int start, int finish)
{
    // Tong so o trong kho
    int n = kho.R * kho.C;

    // Mang luu khoang cach tu diem xuat phat
    // -1 nghia la chua tham
    vector<int> dist(n, -1);

    // Tao hang doi BFS
    queue<int> q;

    // Danh dau diem xuat phat co khoang cach bang 0
    dist[start] = 0;
    q.push(start);

    // Lap khi hang doi chua rong
    while (!q.empty())
    {
        // Lay o dau tien trong hang doi
        int u = q.front();
        q.pop();

        // Neu den dich thi tra ve khoang cach
        if (u == finish)
            return dist[u];

        // Chuyen vi tri 1 chieu thanh hang va cot
        int x = u / kho.C;
        int y = u % kho.C;

        // Kiem tra 4 huong di chuyen
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Kiem tra vi tri co nam ngoai kho khong
            if (nx < 0 || nx >= kho.R ||
                ny < 0 || ny >= kho.C)
                continue;

            // Neu la vat can thi khong di qua
            if (kho.banDo[nx][ny] == '#')
                continue;

            // Chuyen hang va cot thanh vi tri 1 chieu
            int v = nx * kho.C + ny;

            // Neu o nay chua duoc tham
            if (dist[v] == -1)
            {
                // Cap nhat khoang cach
                dist[v] = dist[u] + 1;

                // Dua o moi vao hang doi
                q.push(v);
            }
        }
    }

    // Khong tim thay duong di
    return -1;
}


// ==================================================
// HAM 2: BFS TRUY VET DUONG DI
// ==================================================

vector<int> bfsPath(KhoHang kho, int start, int finish)
{
    int n = kho.R * kho.C;

    // Mang luu khoang cach
    vector<int> dist(n, -1);

    // Mang luu o cha cua moi o
    vector<int> parent(n, -1);

    // Tao hang doi
    queue<int> q;

    // Bat dau tai diem xuat phat
    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        // Da den dich thi dung BFS
        if (u == finish)
            break;

        int x = u / kho.C;
        int y = u % kho.C;

        // Duyet 4 huong
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Kiem tra gioi han ban do
            if (nx < 0 || nx >= kho.R ||
                ny < 0 || ny >= kho.C)
                continue;

            // Bo qua vat can
            if (kho.banDo[nx][ny] == '#')
                continue;

            int v = nx * kho.C + ny;

            // Neu chua tham
            if (dist[v] == -1)
            {
                dist[v] = dist[u] + 1;

                // Luu lai o cha de truy vet
                parent[v] = u;

                q.push(v);
            }
        }
    }

    // Tao mang luu duong di
    vector<int> path;

    // Neu khong tim thay duong di
    if (dist[finish] == -1)
        return path;

    // Truy vet tu dich ve xuat phat
    int cur = finish;

    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    // Dao nguoc de duong di tu xuat phat den dich
    reverse(path.begin(), path.end());

    return path;
}


// ==================================================
// HAM 3: KIEM TRA VA CHUYEN CHUOI THANH SO
// ==================================================

bool chuyenSo(const string& s, long long& value)
{
    try
    {
        // Chuyen chuoi thanh so nguyen
        size_t pos;
        value = stoll(s, &pos);

        // Kiem tra chuoi co hop le hoan toan khong
        return pos == s.size();
    }
    catch (...)
    {
        // Neu khong chuyen duoc thi tra ve false
        return false;
    }
}


// ==================================================
// HAM 4: XU LY MOT TRUY VAN
// ==================================================

void xuLyTruyVan(
    KhoHang kho,
    const string& dong,
    string& ketQua,
    string& duongDi)
{
    // Tach dong truy van thanh cac chuoi
    vector<string> token;
    stringstream ss(dong);
    string s;

    while (ss >> s)
        token.push_back(s);

    long long k;

    // Kiem tra dong truy van co rong hay khong
    if (token.empty() || !chuyenSo(token[0], k))
    {
        ketQua = "INVALID";
        duongDi = "-";
        return;
    }

    // Kiem tra so diem
    if (k < 2 || k > 8)
    {
        ketQua = "INVALID";
        duongDi = "-";
        return;
    }

    // Kiem tra so luong toa do
    if ((long long)token.size() != 1 + 2 * k)
    {
        ketQua = "INVALID";
        duongDi = "-";
        return;
    }

    // Mang luu cac diem can di qua
    vector<int> diem(k);

    // Kiem tra tung toa do
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

        // Kiem tra toa do co nam trong kho khong
        if (r < 0 || r >= kho.R ||
            c < 0 || c >= kho.C)
        {
            ketQua = "INVALID";
            duongDi = "-";
            return;
        }

        // Kiem tra co phai vat can khong
        if (kho.banDo[r][c] == '#')
        {
            ketQua = "INVALID";
            duongDi = "-";
            return;
        }

        // Chuyen toa do thanh vi tri 1 chieu
        diem[i] = (int)r * kho.C + (int)c;
    }


    // ==================================================
    // BUOC 1: TINH KHOANG CACH GIUA CAC DIEM BANG BFS
    // ==================================================

    vector<vector<int>> d(k, vector<int>(k, -1));

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            d[i][j] = bfs(kho, diem[i], diem[j]);
        }
    }


    // ==================================================
    // BUOC 2: QUY HOACH DONG BITMASK DP
    // ==================================================

    int m = k - 1;

    // So trang thai cua Bitmask
    int N = 1 << m;

    const long long INF = LLONG_MAX / 4;

    // dp[mask][i]: chi phi nho nhat khi da tham
    // cac diem trong mask va ket thuc tai diem i
    vector<vector<long long>> dp(
        N, vector<long long>(m, INF));

    // Mang truy vet diem truoc do
    vector<vector<int>> trace(
        N, vector<int>(m, -1));

    // Khoi tao tu diem xuat phat
    for (int i = 0; i < m; i++)
    {
        if (d[0][i + 1] != -1)
        {
            dp[1 << i][i] = d[0][i + 1];
        }
    }

    // Duyet tat ca cac trang thai
    for (int mask = 1; mask < N; mask++)
    {
        for (int u = 0; u < m; u++)
        {
            // Neu diem u chua duoc tham thi bo qua
            if (!(mask & (1 << u)))
                continue;

            // Neu trang thai khong hop le thi bo qua
            if (dp[mask][u] == INF)
                continue;

            // Thu di den cac diem chua tham
            for (int v = 0; v < m; v++)
            {
                if (mask & (1 << v))
                    continue;

                // Khong co duong di thi bo qua
                if (d[u + 1][v + 1] == -1)
                    continue;

                // Tao trang thai moi
                int newMask = mask | (1 << v);

                // Tinh tong so buoc moi
                long long newCost =
                    dp[mask][u] + d[u + 1][v + 1];

                // Neu tim duoc duong tot hon
                if (newCost < dp[newMask][v])
                {
                    dp[newMask][v] = newCost;

                    // Luu diem truoc do
                    trace[newMask][v] = u;
                }
            }
        }
    }


    // ==================================================
    // BUOC 3: TIM TONG SO BUOC NHO NHAT
    // ==================================================

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

    // Neu khong the di qua tat ca cac diem
    if (ans == INF)
    {
        ketQua = "-1";
        duongDi = "-";
        return;
    }

    // Luu ket qua so buoc
    ketQua = to_string(ans);


    // ==================================================
    // BUOC 4: TRUY VET THU TU CAC DIEM
    // ==================================================

    vector<int> thuTu;

    int mask = fullMask;

    while (last != -1)
    {
        thuTu.push_back(last + 1);

        // Tim diem truoc do
        int pre = trace[mask][last];

        // Xoa diem hien tai khoi Bitmask
        mask ^= (1 << last);

        last = pre;
    }

    // Dao nguoc thu tu cac diem
    reverse(thuTu.begin(), thuTu.end());


    // ==================================================
    // BUOC 5: GHEP CAC DUONG DI
    // ==================================================

    vector<int> fullPath;

    // Bat dau tai vi tri xe
    fullPath.push_back(diem[0]);

    int current = diem[0];

    // Lan luot di qua cac diem lay hang
    for (int p : thuTu)
    {
        vector<int> path =
            bfsPath(kho, current, diem[p]);

        // Khong them lai o dau vi da co trong duong di
        for (int j = 1; j < (int)path.size(); j++)
        {
            fullPath.push_back(path[j]);
        }

        current = diem[p];
    }


    // ==================================================
    // BUOC 6: IN TOI DA 10 BUOC DI CHUYEN
    // ==================================================

    stringstream out;

    // 10 buoc di chuyen + 1 o xuat phat
    int soO = min((int)fullPath.size(), 11);

    for (int i = 0; i < soO; i++)
    {
        // Chuyen vi tri 1 chieu thanh hang va cot
        int x = fullPath[i] / kho.C;
        int y = fullPath[i] % kho.C;

        if (i > 0)
            out << " ";

        out << "(" << x << "," << y << ")";
    }

    // Neu duong di con dai hon 10 buoc
    if ((int)fullPath.size() > 11)
        out << " ...";

    // Luu duong di de main in ra
    duongDi = out.str();
}