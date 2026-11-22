// Bai 2: Nhap/xuat kho theo FIFO (First In - First Out)#include <iostream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
// Thong tin cua mot SKU
struct HangHoa {
    queue<pair<string, long long>> cacLo;  
    long long tong = 0;                    
};

unordered_map<string, HangHoa> kho;  
unordered_set<string> loDaDung;      

// Kiem tra chuoi chi gom chu so 0-9
bool laSo(const string& s) {
    if (s.empty()) return false;
    for (char c : s)
        if (c < '0' || c > '9') return false;
    return true;
}


bool docSoLuong(const string& s, long long& kq) {
    if (!laSo(s) || s.size() > 10) return false;  
    kq = stoll(s);
    return kq >= 1 && kq <= 1000000000LL;
}

// Xu ly mot lenh, tra ve dong ket qua
string xuLy(const string& dong) {
    istringstream ss(dong);
    vector<string> tu;
    string t;
    while (ss >> t) tu.push_back(t);
    if (tu.empty()) return "INVALID";

    const string& lenh = tu[0];

    if (lenh == "IMPORT") {
        if (tu.size() != 4) return "INVALID";
        const string& sku = tu[1];
        const string& lo = tu[2];
        long long qty;
        if (sku.size() > 20 || lo.size() > 20) return "INVALID";
        if (!docSoLuong(tu[3], qty)) return "INVALID";

        if (loDaDung.count(lo)) return "DUPLICATE_LOT";
        loDaDung.insert(lo);
        kho[sku].cacLo.push({ lo, qty });
        kho[sku].tong += qty;
        return "OK";
    }

    if (lenh == "EXPORT") {
        if (tu.size() != 3) return "INVALID";
        const string& sku = tu[1];
        long long qty;
        if (sku.size() > 20) return "INVALID";
        if (!docSoLuong(tu[2], qty)) return "INVALID";

        auto it = kho.find(sku);
        long long ton = (it == kho.end()) ? 0 : it->second.tong;
        if (ton < qty) return "NOT_ENOUGH " + to_string(ton);  

        HangHoa& h = it->second;
        string kq;
        long long canLay = qty;
        while (canLay > 0) {
            pair<string, long long>& dau = h.cacLo.front();  
            long long lay = (dau.second < canLay) ? dau.second : canLay;
            if (!kq.empty()) kq += " ";
            kq += dau.first + ":" + to_string(lay);
            dau.second -= lay;
            canLay -= lay;
            if (dau.second == 0) h.cacLo.pop();  
        }
        h.tong -= qty;
        return kq;
    }

    if (lenh == "STOCK") {
        if (tu.size() != 2) return "INVALID";
        if (tu[1].size() > 20) return "INVALID";
        auto it = kho.find(tu[1]);
        if (it == kho.end()) return "0";
        return to_string(it->second.tong);
    }

    return "INVALID"; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string dong;
    getline(cin, dong);
    int Q = stoi(dong);

    string out;
    for (int i = 0; i < Q; i++) {
        if (!getline(cin, dong)) dong = "";
        while (!dong.empty() && (dong.back() == '\r' || dong.back() == '\n')) dong.pop_back();
        out += xuLy(dong) + "\n";
    }
    cout << out;
    return 0;
}
