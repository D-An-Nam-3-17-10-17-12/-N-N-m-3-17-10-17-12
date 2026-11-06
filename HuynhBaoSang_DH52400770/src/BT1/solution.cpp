#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

int R, C, Q;
char g[1005][1005];
int dist[8][1000][1000];
int qr[1000000], qc[1000000];

int dr[4] = { 1, 0, -1, 0 };
int dc[4] = { 0, 1, 0, -1 };

char line[4096];
int k, pr[8], pc[8];
bool hopLe;
int m, best, bestOrder[8];

int dp[1 << 7][8];
int par[1 << 7][8];

long long ans[10];
char path[10][400];


void bfs(int id, int sr, int sc)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            dist[id][i][j] = -1;
    int head = 0, tail = 0;
    dist[id][sr][sc] = 0;
    qr[tail] = sr;
    qc[tail] = sc;
    tail++;
    while (head < tail)
    {
        int r = qr[head], c = qc[head];
        head++;
        for (int d = 0; d < 4; d++)
        {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                continue;
            if (g[nr][nc] == '#' || dist[id][nr][nc] != -1)
                continue;
            dist[id][nr][nc] = dist[id][r][c] + 1;
            qr[tail] = nr;
            qc[tail] = nc;
            tail++;
        }
    }
}

void docBanDo()
{
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; i++) scanf("%s", g[i]);
    scanf("%d", &Q);
    fgets(line, sizeof line, stdin);
}

void docTruyVan()
{
    hopLe = true;
    if (!fgets(line, sizeof line, stdin)) line[0] = 0;

    long long t[100];
    int cnt = 0;
    char* p = line;
    while (true)
    {
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')
            p++;
        if (!*p)
            break;
        char* e;
        long long x = strtoll(p, &e, 10);
        if (e == p || (*e && !isspace((unsigned char)*e)))
        {
            hopLe = false;
            return;
        }
        if (cnt < 100)
            t[cnt] = x;
        cnt++;
        p = e;
    }
    if (cnt == 0 || t[0] < 2 || t[0] > 8 || cnt != 1 + 2 * (int)t[0])
    {
        hopLe = false;
        return;
    }
    k = (int)t[0];
    for (int i = 0; i < k; i++)
    {
        long long r = t[1 + 2 * i], c = t[2 + 2 * i];
        if (r < 0 || r >= R || c < 0 || c >= C || g[r][c] == '#')
        {
            hopLe = false;
            return;
        }
        pr[i] = (int)r; pc[i] = (int)c;
    }
}

void giaiTruyVan(int qi)
{
    for (int i = 0; i < k; i++)
        bfs(i, pr[i], pc[i]);

    for (int j = 1; j < k; j++)
        if (dist[0][pr[j]][pc[j]] == -1)
        {
            ans[qi] = -1;
            return;
        }

    m = k - 1;
    int full = (1 << m) - 1;

    for (int mask = 0; mask <= full; mask++)
        for (int i = 0; i <= m; i++)
            dp[mask][i] = INT_MAX;

    for (int i = 1; i <= m; i++)
    {
        dp[1 << (i - 1)][i] = dist[0][pr[i]][pc[i]];
        par[1 << (i - 1)][i] = 0;
    }

    for (int mask = 1; mask <= full; mask++)
        for (int i = 1; i <= m; i++)
        {
            if (!(mask & (1 << (i - 1))) || dp[mask][i] == INT_MAX)
                continue;
            for (int j = 1; j <= m; j++)
            {
                if (mask & (1 << (j - 1)))
                    continue;
                int nmask = mask | (1 << (j - 1));
                int val = dp[mask][i] + dist[i][pr[j]][pc[j]];
                if (val < dp[nmask][j])
                {
                    dp[nmask][j] = val;
                    par[nmask][j] = i;
                }
            }
        }

    best = INT_MAX;
    int last = 1;
    for (int i = 1; i <= m; i++)
        if (dp[full][i] < best)
        {
            best = dp[full][i];
            last = i;
        }

    int mask = full;
    for (int i = m - 1; i >= 0; i--)
    {
        bestOrder[i] = last;
        int p = par[mask][last];
        mask ^= (1 << (last - 1));
        last = p;
    }

    ans[qi] = best;
}

void ghiDuongDi(int qi)
{
    int r = pr[0], c = pc[0], steps = 0, pos = 0;
    pos += sprintf(path[qi] + pos, "(%d,%d)", r, c);
    for (int i = 0; i < m && steps < 10; i++)
    {
        int target = bestOrder[i];
        while (steps < 10 && !(r == pr[target] && c == pc[target]))
        {
            int cd = dist[target][r][c];
            for (int d = 0; d < 4; d++)
            {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C)
                    continue;
                if (dist[target][nr][nc] == cd - 1)
                {
                    r = nr;
                    c = nc;
                    break;
                }
            }
            pos += sprintf(path[qi] + pos, " (%d,%d)", r, c);
            steps++;
        }
    }
    if (best > 10) strcat(path[qi], " ...");
}

void inKetQua()
{
    for (int i = 0; i < Q; i++)
    {
        if (ans[i] == -2)
            printf("INVALID\n");
        else
            printf("%lld\n", ans[i]);
    }
    for (int i = 0; i < Q; i++) printf("%s\n", path[i]);
}

int main()
{
    docBanDo();
    for (int qi = 0; qi < Q; qi++)
    {
        strcpy(path[qi], "-");
        docTruyVan();
        if (!hopLe)
        {
            ans[qi] = -2;
            continue;
        }
        giaiTruyVan(qi);
        if (ans[qi] >= 0)
            ghiDuongDi(qi);
    }
    inKetQua();
    return 0;
}