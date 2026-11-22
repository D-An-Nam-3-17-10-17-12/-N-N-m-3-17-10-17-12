#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const long long MAX_VALUE = 2147483646LL;

struct Lot {
    string code;
    long long quantity;
};

struct SKUInfo {
    queue<Lot> lots;
    long long total = 0;
};

unordered_map<string, SKUInfo> warehouse;
unordered_set<string> usedLotCodes;

bool parseNumber(const string& token, long long& value) {
    if (token.empty()) return false;
    for (char ch : token) {
        if (ch < '0' || ch > '9') return false;
    }
    try {
        size_t pos = 0;
        value = stoll(token, &pos);
        return pos == token.size() && value <= MAX_VALUE;
    } catch (...) {
        return false;
    }
}

bool validCode(const string& code) {
    return !code.empty() && code.size() <= 20;
}

void processCommand(const string& line) {
    stringstream input(line);
    vector<string> p;
    string token;
    while (input >> token) p.push_back(token);

    if (p.empty()) {
        cout << "INVALID\n";
        return;
    }

    if (p[0] == "IMPORT") {
        if (p.size() != 4 || !validCode(p[1]) || !validCode(p[2])) {
            cout << "INVALID\n";
            return;
        }

        long long qty;
        if (!parseNumber(p[3], qty) || qty == 0) {
            cout << "INVALID\n";
            return;
        }

        if (usedLotCodes.count(p[2])) {
            cout << "DUPLICATE_LOT\n";
            return;
        }

        SKUInfo& info = warehouse[p[1]];
        if (info.total + qty > MAX_VALUE) {
            cout << "INVALID\n";
            return;
        }

        info.lots.push({p[2], qty});
        info.total += qty;
        usedLotCodes.insert(p[2]);
        cout << "OK\n";
        return;
    }

    if (p[0] == "EXPORT") {
        if (p.size() != 3 || !validCode(p[1])) {
            cout << "INVALID\n";
            return;
        }

        long long qty;
        if (!parseNumber(p[2], qty) || qty == 0) {
            cout << "INVALID\n";
            return;
        }

        auto it = warehouse.find(p[1]);
        long long stock = (it == warehouse.end()) ? 0 : it->second.total;

        if (stock < qty) {
            cout << "NOT_ENOUGH " << stock << '\n';
            return;
        }

        SKUInfo& info = it->second;
        long long remaining = qty;
        bool first = true;

        while (remaining > 0) {
            Lot& lot = info.lots.front();
            long long taken = min(lot.quantity, remaining);

            if (!first) cout << ' ';
            cout << lot.code << ':' << taken;
            first = false;

            lot.quantity -= taken;
            remaining -= taken;
            info.total -= taken;

            if (lot.quantity == 0) info.lots.pop();
        }
        cout << '\n';
        return;
    }

    if (p[0] == "STOCK") {
        if (p.size() != 2 || !validCode(p[1])) {
            cout << "INVALID\n";
            return;
        }
        auto it = warehouse.find(p[1]);
        cout << (it == warehouse.end() ? 0 : it->second.total) << '\n';
        return;
    }

    cout << "INVALID\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string firstLine;
    if (!getline(cin, firstLine)) return 0;

    stringstream qInput(firstLine);
    string qToken, extra;
    long long Q;

    if (!(qInput >> qToken) || (qInput >> extra) ||
        !parseNumber(qToken, Q) || Q < 1 || Q > 100000) {
        return 0;
    }

    for (long long i = 0; i < Q; ++i) {
        string line;
        if (!getline(cin, line)) line.clear();
        processCommand(line);
    }
    return 0;
}
