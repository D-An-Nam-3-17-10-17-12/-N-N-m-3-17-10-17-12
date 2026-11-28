
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <set>
using namespace std;

struct LoHang {
    string maLo;
    long long soLuong;
};

struct SanPham {
    deque<LoHang> dsLo;
    long long tong = 0;
};
int main() {
    int q;
    cin >> q;
    cin.ignore();
    map<string, SanPham> kho;
    set<string> maLoDaDung;
    while (q--) {
        string dong;
        getline(cin, dong);
        stringstream ss(dong);
        vector<string> a;
        string x;
        while (ss >> x) {
            a.push_back(x);
        }
        if (a.size() == 0) {
            cout << "INVALID\n";
            continue;
        }
        if (a[0] == "IMPORT") {

            if (a.size() != 4 ||
                a[1].size() > 20 ||
                a[2].size() > 20) {
                cout << "INVALID\n";
                continue;
            }
            bool hopLe = true;

            if (a[3].empty() || a[3].size() > 10) {
                hopLe = false;
            }
            for (char c : a[3]) {
                if (c < '0' || c > '9') {
                    hopLe = false;
                }
            }
            long long sl = 0;

            if (hopLe) {
                sl = stoll(a[3]);

                if (sl < 1 || sl > 1000000000LL) {
                    hopLe = false;
                }
            }
            if (!hopLe) {
                cout << "INVALID\n";
                continue;
            }
            if (maLoDaDung.count(a[2])) {
                cout << "DUPLICATE_LOT\n";
                continue;
            }
            maLoDaDung.insert(a[2]);
            LoHang lo;
            lo.maLo = a[2];
            lo.soLuong = sl;
            kho[a[1]].dsLo.push_back(lo);
            kho[a[1]].tong += sl;
            cout << "OK\n";
        }
        else if (a[0] == "EXPORT") {

            if (a.size() != 3 || a[1].size() > 20) {
                cout << "INVALID\n";
                continue;
            }
            bool hopLe = true;
            if (a[2].empty() || a[2].size() > 10) {
                hopLe = false;
            }
            for (char c : a[2]) {
                if (c < '0' || c > '9') {
                    hopLe = false;
                }
            }
            long long sl = 0;
            if (hopLe) {
                sl = stoll(a[2]);
                if (sl < 1 || sl > 1000000000LL) {
                    hopLe = false;
                }
            }
            if (!hopLe) {
                cout << "INVALID\n";
                continue;
            }
            if (kho[a[1]].tong < sl) {
                cout << "NOT_ENOUGH " << kho[a[1]].tong << "\n";
                continue;
            }
            long long canXuat = sl;
            bool dauTien = true;
            while (canXuat > 0) {
                LoHang& lo = kho[a[1]].dsLo.front();
                long long lay = min(lo.soLuong, canXuat);
                if (!dauTien) {
                    cout << " ";
                }
                cout << lo.maLo << ":" << lay;
                dauTien = false;
                lo.soLuong -= lay;
                canXuat -= lay;
                if (lo.soLuong == 0) {
                    kho[a[1]].dsLo.pop_front();
                }
            }
            kho[a[1]].tong -= sl;
            cout << "\n";
        }
        else if (a[0] == "STOCK") {

            if (a.size() != 2 || a[1].size() > 20) {
                cout << "INVALID\n";
                continue;
            }
            cout << kho[a[1]].tong << "\n";
        }
        else {
            cout << "INVALID\n";
        }
    }
    return 0;

}
