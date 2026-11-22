#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

struct DonHang {
    string maDon;
    long long uuTien;
    long long thuTu;
};

struct SoSanh {
    bool operator()(const DonHang& a, const DonHang& b) const {
        if (a.uuTien != b.uuTien) return a.uuTien < b.uuTien;
        return a.thuTu > b.thuTu;
    }
};

bool docUuTien(const string& s, long long& x) {
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
    if (!docUuTien(dong, q) || q > 100000) return 0;

    priority_queue<DonHang, vector<DonHang>, SoSanh> hangDoi;
    unordered_set<string> maDonDaThem;
    long long thuTu = 0;

    for (long long i = 0; i < q; i++) {
        if (!getline(cin, dong)) dong = "";
        stringstream ss(dong);
        vector<string> t;
        string s;
        while (ss >> s) t.push_back(s);

        if (t.empty()) {
            cout << "INVALID\n";
        }
        else if (t[0] == "ORDER") {
            if (t.size() != 3 || t[1].empty() || t[1].size() > 20) {
                cout << "INVALID\n";
                continue;
            }

            long long uuTien;
            if (!docUuTien(t[2], uuTien)) {
                cout << "INVALID\n";
            }
            else if (maDonDaThem.count(t[1])) {
                cout << "DUPLICATE\n";
            }
            else {
                maDonDaThem.insert(t[1]);
                hangDoi.push({t[1], uuTien, thuTu++});
                cout << "OK\n";
            }
        }
        else if (t[0] == "NEXT" || t[0] == "PEEK") {
            if (t.size() != 1) {
                cout << "INVALID\n";
            }
            else if (hangDoi.empty()) {
                cout << "EMPTY\n";
            }
            else {
                DonHang don = hangDoi.top();
                cout << don.maDon << ' ' << don.uuTien << '\n';
                if (t[0] == "NEXT") hangDoi.pop();
            }
        }
        else if (t[0] == "SIZE") {
            if (t.size() != 1) cout << "INVALID\n";
            else cout << hangDoi.size() << '\n';
        }
        else {
            cout << "INVALID\n";
        }
    }
    return 0;
}
