#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
using namespace std;

struct LoHang {
    string maLo;
    long long soLuong;
};

bool docSoLuong(const string& s, long long& x) {
    if (s.empty()) return false;
    x = 0;
    for (char ch : s) {
        if (ch < '0' || ch > '9') return false;
        int d = ch - '0';
        if (x > (1000000000LL - d) / 10) return false;
        x = x * 10 + d;
    }
    return x >= 1 && x <= 1000000000LL;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string dong;
    if (!getline(cin, dong)) return 0;
    long long q;
    if (!docSoLuong(dong, q) || q > 100000) return 0;

    unordered_map<string, queue<LoHang>> kho;
    unordered_map<string, long long> tonKho;
    unordered_set<string> maLoDaDung;

    for (long long i = 0; i < q; i++) {
        if (!getline(cin, dong)) dong = "";
        stringstream ss(dong);
        vector<string> t;
        string s;
        while (ss >> s) t.push_back(s);

        if (t.empty()) {
            cout << "INVALID\n";
        }
        else if (t[0] == "IMPORT") {
            if (t.size() != 4 || t[1].empty() || t[2].empty() ||
                t[1].size() > 20 || t[2].size() > 20) {
                cout << "INVALID\n";
                continue;
            }

            long long qty;
            if (!docSoLuong(t[3], qty)) {
                cout << "INVALID\n";
            }
            else if (maLoDaDung.count(t[2])) {
                cout << "DUPLICATE_LOT\n";
            }
            else {
                maLoDaDung.insert(t[2]);
                kho[t[1]].push({ t[2], qty });
                tonKho[t[1]] += qty;
                cout << "OK\n";
            }
        }
        else if (t[0] == "EXPORT") {
            if (t.size() != 3 || t[1].empty() || t[1].size() > 20) {
                cout << "INVALID\n";
                continue;
            }

            long long canXuat;
            if (!docSoLuong(t[2], canXuat)) {
                cout << "INVALID\n";
                continue;
            }

            long long hienCo = tonKho[t[1]];
            if (hienCo < canXuat) {
                cout << "NOT_ENOUGH " << hienCo << '\n';
                continue;
            }

            vector<string> ketQua;
            while (canXuat > 0) {
                LoHang& lo = kho[t[1]].front();
                long long lay = min(lo.soLuong, canXuat);
                ketQua.push_back(lo.maLo + ":" + to_string(lay));
                lo.soLuong -= lay;
                canXuat -= lay;
                tonKho[t[1]] -= lay;
                if (lo.soLuong == 0) kho[t[1]].pop();
            }

            for (size_t j = 0; j < ketQua.size(); j++) {
                if (j) cout << ' ';
                cout << ketQua[j];
            }
            cout << '\n';
        }
        else if (t[0] == "STOCK") {
            if (t.size() != 2 || t[1].empty() || t[1].size() > 20)
                cout << "INVALID\n";
            else
                cout << tonKho[t[1]] << '\n';
        }
        else {
            cout << "INVALID\n";
        }
    }
    return 0;
}
