#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <fstream>
struct Kho {
    int R = 0, C = 0;
    std::vector<char> diDuoc;  
};

enum class TrangThai { HOP_LE, KHONG_TOI_DUOC, INVALID };

struct KetQua {
    TrangThai trangThai = TrangThai::INVALID;
    long long soBuoc = 0;      
    std::string duongDi = "-"; 
};


namespace {

    const long long INF = LLONG_MAX / 4;

    std::string catKhoangTrang(const std::string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        if (a == std::string::npos) return "";
        size_t b = s.find_last_not_of(" \t\r\n");
        return s.substr(a, b - a + 1);
    }

    bool doiSo(const std::string& s, long long& v) {
        if (s.empty() || s.size() > 18) return false;  
        for (char ch : s)
            if (ch < '0' || ch > '9') return false;     
        v = std::stoll(s);
        return true;
    }

    std::string toaDo(const Kho& kho, int id) {
        return "(" + std::to_string(id / kho.C) + "," + std::to_string(id % kho.C) + ")";
    }

}  

bool docDongKhongRong(std::istream& in, std::string& dong) {
    while (std::getline(in, dong)) {
        dong = catKhoangTrang(dong);
        if (!dong.empty()) return true;
    }
    return false;
}

bool docKho(std::istream& in, Kho& kho) {
    std::string dong;
    if (!docDongKhongRong(in, dong)) return false;
    std::istringstream ss(dong);
    std::vector<std::string> tu;
    std::string t;
    while (ss >> t) tu.push_back(t);
    long long R, C;
    if (tu.size() != 2 || !doiSo(tu[0], R) || !doiSo(tu[1], C) || R < 1 || C < 1)
        return false;
    kho.R = (int)R;
    kho.C = (int)C;
    kho.diDuoc.assign((size_t)R * C, 0);
    for (int r = 0; r < kho.R; r++) {
        if (!docDongKhongRong(in, dong)) return false;
        for (int c = 0; c < kho.C && c < (int)dong.size(); c++)
            kho.diDuoc[(size_t)r * kho.C + c] = (dong[c] == '.');
    }
    return true;
}

bool phanTichTruyVan(const Kho& kho, const std::string& dong, std::vector<int>& diem) {
    diem.clear();
    std::istringstream ss(dong);
    std::vector<std::string> tu;
    std::string t;
    while (ss >> t) tu.push_back(t);

    long long k;
    if (tu.empty() || !doiSo(tu[0], k)) return false;
    if (k < 2 || k > 8) return false;
    if ((long long)tu.size() != 1 + 2 * k) return false;  

    for (int i = 0; i < k; i++) {
        long long r, c;
        if (!doiSo(tu[1 + 2 * i], r) || !doiSo(tu[2 + 2 * i], c)) return false;
        if (r < 0 || r >= kho.R || c < 0 || c >= kho.C) return false;
        int id = (int)(r * kho.C + c);
        if (!kho.diDuoc[id]) return false;
        diem.push_back(id);
    }
    return true;
}

void bfs(const Kho& kho, int nguon, std::vector<int>& dist, std::vector<int>& hangDoi,
    const std::vector<char>& danhDau, int soMucTieu) {
    std::fill(dist.begin(), dist.end(), -1);
    const int R = kho.R, C = kho.C;
    const bool dungSom = soMucTieu > 0;
    int dau = 0, cuoi = 0;
    dist[nguon] = 0;
    hangDoi[cuoi++] = nguon;
    if (dungSom && danhDau[nguon] && --soMucTieu == 0) return;

    while (dau < cuoi) {
        int u = hangDoi[dau++];
        int r = u / C, c = u % C;
        auto thu = [&](int v) -> bool {  // true = đã đủ mục tiêu, dừng
            if (kho.diDuoc[v] && dist[v] < 0) {
                dist[v] = dist[u] + 1;
                hangDoi[cuoi++] = v;
                if (dungSom && danhDau[v] && --soMucTieu == 0) return true;
            }
            return false;
            };
        if (r > 0 && thu(u - C)) return;
        if (r + 1 < R && thu(u + C)) return;
        if (c > 0 && thu(u - 1)) return;
        if (c + 1 < C && thu(u + 1)) return;
    }
}

KetQua giaiTruyVan(const Kho& kho, const std::vector<int>& diem) {
    KetQua kq;
    const int k = (int)diem.size();
    const int m = k - 1;  // số điểm cần đi qua
    const size_t N = (size_t)kho.R * kho.C;

    std::vector<int> dist(N), hangDoi(N);
    std::vector<char> danhDau(N, 0);

    int soMucTieu = 0;
    for (int id : diem)
        if (!danhDau[id]) { danhDau[id] = 1; soMucTieu++; }

    std::vector<std::vector<long long>> d(k, std::vector<long long>(k, INF));
    for (int i = 0; i < k; i++) {
        bfs(kho, diem[i], dist, hangDoi, danhDau, soMucTieu);
        for (int j = 0; j < k; j++)
            if (dist[diem[j]] >= 0) d[i][j] = dist[diem[j]];
    }
    for (int id : diem) danhDau[id] = 0;

    for (int j = 1; j < k; j++)
        if (d[0][j] >= INF) {  
            kq.trangThai = TrangThai::KHONG_TOI_DUOC;
            kq.duongDi = "-";
            return kq;
        }

    const int full = (1 << m) - 1;
    std::vector<std::vector<long long>> dp(1 << m, std::vector<long long>(m, INF));
    std::vector<std::vector<int>> cha(1 << m, std::vector<int>(m, -1));
    for (int j = 0; j < m; j++) dp[1 << j][j] = d[0][j + 1];

    for (int mask = 1; mask <= full; mask++)
        for (int last = 0; last < m; last++) {
            if (!(mask >> last & 1) || dp[mask][last] >= INF) continue;
            for (int nxt = 0; nxt < m; nxt++) {
                if (mask >> nxt & 1) continue;
                int nm = mask | (1 << nxt);
                long long cost = dp[mask][last] + d[last + 1][nxt + 1];
                if (cost < dp[nm][nxt]) {
                    dp[nm][nxt] = cost;
                    cha[nm][nxt] = last;
                }
            }
        }

    int lastTot = 0;
    for (int j = 1; j < m; j++)
        if (dp[full][j] < dp[full][lastTot]) lastTot = j;
    kq.trangThai = TrangThai::HOP_LE;
    kq.soBuoc = dp[full][lastTot];

    std::vector<int> thuTu;  
    for (int mask = full, last = lastTot; last >= 0;) {
        thuTu.push_back(last + 1);
        int p = cha[mask][last];
        mask ^= (1 << last);
        last = p;
    }
    thuTu.push_back(0);
    std::reverse(thuTu.begin(), thuTu.end());

    std::vector<int> duong = { diem[0] };
    int soBuocDaDi = 0;
    for (size_t s = 0; s + 1 < thuTu.size() && soBuocDaDi < 10; s++) {
        int a = diem[thuTu[s]], b = diem[thuTu[s + 1]];
        if (a == b) continue;
        danhDau[a] = 1;
        bfs(kho, b, dist, hangDoi, danhDau, 1);  
        danhDau[a] = 0;
        int cur = a;
        while (cur != b && soBuocDaDi < 10) {
            int r = cur / kho.C, c = cur % kho.C;
            int ung[4] = { r > 0 ? cur - kho.C : -1, r + 1 < kho.R ? cur + kho.C : -1,
                          c > 0 ? cur - 1 : -1, c + 1 < kho.C ? cur + 1 : -1 };
            for (int nb : ung)
                if (nb >= 0 && kho.diDuoc[nb] && dist[nb] == dist[cur] - 1) {
                    cur = nb;
                    break;
                }
            duong.push_back(cur);
            soBuocDaDi++;
        }
    }

    std::string s;
    for (size_t i = 0; i < duong.size(); i++) {
        if (i) s += ' ';
        s += toaDo(kho, duong[i]);
    }
    if (kq.soBuoc > 10) s += " ...";
    kq.duongDi = s;
    return kq;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Kho kho;
    if (!docKho(std::cin, kho)) return 0;

    std::string dong;
    if (!docDongKhongRong(std::cin, dong)) return 0;
    int Q = std::atoi(dong.c_str());

    std::vector<KetQua> ketQua;
    for (int i = 0; i < Q; i++) {
        std::string truyVan;
        if (!std::getline(std::cin, truyVan)) truyVan = ""; 

        std::vector<int> diem;
        if (!phanTichTruyVan(kho, truyVan, diem)) {
            KetQua kq;
            kq.trangThai = TrangThai::INVALID;
            kq.duongDi = "-";
            ketQua.push_back(kq);
        }
        else {
            ketQua.push_back(giaiTruyVan(kho, diem));
        }
    }

    for (const KetQua& kq : ketQua) {
        if (kq.trangThai == TrangThai::INVALID) std::cout << "INVALID\n";
        else if (kq.trangThai == TrangThai::KHONG_TOI_DUOC) std::cout << "-1\n";
        else std::cout << kq.soBuoc << "\n";
    }
    for (const KetQua& kq : ketQua) std::cout << kq.duongDi << "\n";
    return 0;
}