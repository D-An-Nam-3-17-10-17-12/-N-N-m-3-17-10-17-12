#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int SO_KHOA_TOI_DA = 20;

struct Nut {
    bool laLa;
    vector<long long> khoa;
    vector<Nut*> con;

    Nut(bool laLa) : laLa(laLa) {}
};

struct KetQuaChen {
    long long khoa;
    Nut* nutPhai;
    bool tach;
};

class CayBTree {
private:
    Nut* goc;

    KetQuaChen chenDeQuy(Nut* nut, long long x) {
        if (nut->laLa) {
            auto it = lower_bound(nut->khoa.begin(), nut->khoa.end(), x);
            nut->khoa.insert(it, x);
        }
        else {
            int i = upper_bound(nut->khoa.begin(), nut->khoa.end(), x) - nut->khoa.begin();
            KetQuaChen kq = chenDeQuy(nut->con[i], x);
            if (kq.tach) {
                nut->khoa.insert(nut->khoa.begin() + i, kq.khoa);
                nut->con.insert(nut->con.begin() + i + 1, kq.nutPhai);
            }
        }

        if ((int)nut->khoa.size() <= SO_KHOA_TOI_DA)
            return {0, nullptr, false};

        int giua = (int)nut->khoa.size() / 2;
        long long khoaGiua = nut->khoa[giua];
        Nut* phai = new Nut(nut->laLa);
        phai->khoa.assign(nut->khoa.begin() + giua + 1, nut->khoa.end());
        nut->khoa.resize(giua);

        if (!nut->laLa) {
            phai->con.assign(nut->con.begin() + giua + 1, nut->con.end());
            nut->con.resize(giua + 1);
        }
        return {khoaGiua, phai, true};
    }

public:
    CayBTree() : goc(new Nut(true)) {}

    void chen(long long x) {
        KetQuaChen kq = chenDeQuy(goc, x);
        if (kq.tach) {
            Nut* gocMoi = new Nut(false);
            gocMoi->khoa.push_back(kq.khoa);
            gocMoi->con.push_back(goc);
            gocMoi->con.push_back(kq.nutPhai);
            goc = gocMoi;
        }
    }

    int tim(long long x) const {
        Nut* nut = goc;
        int buoc = 0;

        while (nut != nullptr) {
            buoc++;
            auto it = lower_bound(nut->khoa.begin(), nut->khoa.end(), x);
            if (it != nut->khoa.end() && *it == x) return buoc;
            if (nut->laLa) return -buoc;
            int i = it - nut->khoa.begin();
            nut = nut->con[i];
        }
        return -buoc;
    }
};

bool docSo12ChuSo(const string& s, long long& x) {
    if (s.size() != 12) return false;
    x = 0;
    for (char ch : s) {
        if (ch < '0' || ch > '9') return false;
        x = x * 10 + (ch - '0');
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, B;
    int n;
    if (!(cin >> A >> B >> n)) return 0;

    CayBTree cay;
    for (int i = 0; i < n; i++) {
        long long so;
        cin >> so;
        cay.chen(so);
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string truyVan;
        cin >> truyVan;

        long long x;
        if (!docSo12ChuSo(truyVan, x) || x < A || x > B)
            cout << "INVALID\n";
        else
            cout << cay.tim(x) << '\n';
    }
    return 0;
}
