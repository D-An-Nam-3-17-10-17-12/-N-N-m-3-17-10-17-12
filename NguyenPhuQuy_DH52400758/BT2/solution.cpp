#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;
struct Lot {
    string id;
    long long qty;
};

struct SkuInfo {
    queue<Lot> lots; 
    long long total = 0;
};

bool isDigits(const string& s) {
    if (s.empty()) return false;
    for (char c : s)
        if (c < '0' || c > '9') return false;
    return true;
}

bool parseQty(const string& s, long long& qty) {
    if (!isDigits(s) || s.size() > 10) return false;
    qty = stoll(s);
    return qty >= 1 && qty <= 1000000000LL;
}

bool validCode(const string& s) {
    return !s.empty() && s.size() <= 20;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, SkuInfo> warehouse;
    unordered_set<string> usedLots;

    string line;
    if (!getline(cin, line)) return 0;
    long long Q = 0;
    {
        stringstream ss(line);
        ss >> Q;
    }
    for (long long i = 0; i < Q; i++) {
        if (!getline(cin, line)) break;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        vector<string> tok;
        {
            stringstream ss(line);
            string t;
            while (ss >> t) tok.push_back(t);
        }
        if (tok.empty()) {
            cout << "INVALID\n";
            continue;
        }
        const string& cmd = tok[0];
        if (cmd == "IMPORT") {
            long long qty;
            if (tok.size() != 4 || !validCode(tok[1]) || !validCode(tok[2]) ||
                !parseQty(tok[3], qty)) {
                cout << "INVALID\n";
                continue;
            }
            const string& sku = tok[1];
            const string& lot = tok[2];
            if (usedLots.count(lot)) {
                cout << "DUPLICATE_LOT\n";
                continue;
            }
            usedLots.insert(lot);
            SkuInfo& info = warehouse[sku];
            info.lots.push({ lot, qty });
            info.total += qty;
            cout << "OK\n";
        }
        else if (cmd == "EXPORT") {
            long long qty;
            if (tok.size() != 3 || !validCode(tok[1]) || !parseQty(tok[2], qty)) {
                cout << "INVALID\n";
                continue;
            }
            const string& sku = tok[1];
            auto it = warehouse.find(sku);
            long long stock = (it == warehouse.end()) ? 0 : it->second.total;

            if (qty > stock) {
                cout << "NOT_ENOUGH " << stock << "\n";
                continue;
            }
            SkuInfo& info = it->second;
            long long need = qty;
            bool first = true;
            while (need > 0) {
                Lot& front = info.lots.front();
                long long take = min(need, front.qty);
                if (!first) cout << ' ';
                cout << front.id << ':' << take;
                first = false;
                front.qty -= take;
                need -= take;
                if (front.qty == 0) info.lots.pop();
            }
            info.total -= qty;
            cout << "\n";
        }
        else if (cmd == "STOCK") {
            if (tok.size() != 2 || !validCode(tok[1])) {
                cout << "INVALID\n";
                continue;
            }
            auto it = warehouse.find(tok[1]);
            cout << (it == warehouse.end() ? 0 : it->second.total) << "\n";
        }
        else {
            cout << "INVALID\n";
        }
    }
    return 0;
}
