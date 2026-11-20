#include <bits/stdc++.h>
using namespace std;

static const long long MAX_QTY = 1000000000LL;
static const size_t MAX_LEN = 20;

static bool parseNonNegativeInt(const string& s, long long& value) {
    if (s.empty()) return false;
    long long x = 0;
    for (char ch : s) {
        if (ch < '0' || ch > '9') return false;
        x = x * 10 + (ch - '0');
        if (x > INT_MAX) return false;
    }
    value = x;
    return true;
}

static bool parseQty(const string& s, long long& qty) {
    return parseNonNegativeInt(s, qty) && qty >= 1 && qty <= MAX_QTY;
}

struct Lot {
    string id;
    long long qty;
};

struct SkuInfo {
    queue<Lot> lots;
    long long total = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;

    long long Q = 0;
    bool gotQ = false;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        gotQ = true;
        break;
    }
    if (!gotQ) return 0;
    if (!parseNonNegativeInt(line, Q) || Q < 1 || Q > 100000) return 0;

    unordered_map<string, SkuInfo> warehouse;
    unordered_set<string> usedLots;
    warehouse.reserve(1 << 17);
    usedLots.reserve(1 << 17);

    vector<string> answers;
    answers.reserve(Q);

    for (long long qi = 0; qi < Q; ++qi) {
        if (!getline(cin, line)) line.clear();
        if (!line.empty() && line.back() == '\r') line.pop_back();

        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (ss >> token) tokens.push_back(token);

        if (tokens.empty()) {
            answers.push_back("INVALID");
            continue;
        }

        const string& cmd = tokens[0];

        if (cmd == "IMPORT") {
            long long qty;
            if (tokens.size() != 4 ||
                tokens[1].size() > MAX_LEN || tokens[2].size() > MAX_LEN ||
                !parseQty(tokens[3], qty)) {
                answers.push_back("INVALID");
                continue;
            }
            const string& sku = tokens[1];
            const string& lot = tokens[2];

            if (usedLots.count(lot)) {
                answers.push_back("DUPLICATE_LOT");
                continue;
            }
            usedLots.insert(lot);
            SkuInfo& info = warehouse[sku];
            info.lots.push({lot, qty});
            info.total += qty;
            answers.push_back("OK");

        } else if (cmd == "EXPORT") {
            long long qty;
            if (tokens.size() != 3 || tokens[1].size() > MAX_LEN ||
                !parseQty(tokens[2], qty)) {
                answers.push_back("INVALID");
                continue;
            }
            auto it = warehouse.find(tokens[1]);
            long long stock = (it == warehouse.end()) ? 0 : it->second.total;

            if (stock < qty) {
                answers.push_back("NOT_ENOUGH " + to_string(stock));
                continue;
            }

            SkuInfo& info = it->second;
            string result;
            long long need = qty;
            while (need > 0) {
                Lot& front = info.lots.front();
                long long take = min(need, front.qty);
                if (!result.empty()) result += ' ';
                result += front.id + ":" + to_string(take);
                front.qty -= take;
                need -= take;
                if (front.qty == 0) info.lots.pop();
            }
            info.total -= qty;
            answers.push_back(result);

        } else if (cmd == "STOCK") {
            if (tokens.size() != 2 || tokens[1].size() > MAX_LEN) {
                answers.push_back("INVALID");
                continue;
            }
            auto it = warehouse.find(tokens[1]);
            long long stock = (it == warehouse.end()) ? 0 : it->second.total;
            answers.push_back(to_string(stock));

        } else {
            answers.push_back("INVALID");
        }
    }

    for (const string& s : answers) cout << s << '\n';
    return 0;
}