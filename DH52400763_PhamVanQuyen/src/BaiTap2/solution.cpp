#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

using namespace std;
struct Lot {
    string id;
    long long quantity;
};

struct Inventory {
    deque<Lot> lots;       // Các lô theo thứ tự nhập (FIFO)
    long long total = 0;   // Tổng tồn kho của SKU
};

// Chỉ chấp nhận chuỗi không rỗng gồm các chữ số 0..9.
// Giá trị phải nằm trong [1, 1,000,000,000].
bool parseQuantity(const string& s, long long& value) {
    if (s.empty()) return false;

    for (unsigned char c : s) {
        if (c < '0' || c > '9') return false;
    }

    try {
        size_t pos = 0;
        value = stoll(s, &pos);

        if (pos != s.size()) return false;
        if (value < 1 || value > 1'000'000'000LL) return false;
    }
    catch (...) {
        return false;
    }

    return true;
}

bool validCode(const string& s) {
    return !s.empty() && s.size() <= 20;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string firstLine;
    if (!getline(cin, firstLine)) return 0;

    // Dòng đầu phải có đúng một số Q.
    stringstream qStream(firstLine);
    string qToken, extra;
    if (!(qStream >> qToken) || (qStream >> extra)) return 0;

    long long qValue = 0;
    if (qToken.empty()) return 0;
    for (unsigned char c : qToken) {
        if (c < '0' || c > '9') return 0;
    }

    try {
        size_t pos = 0;
        qValue = stoll(qToken, &pos);
        if (pos != qToken.size() || qValue < 1 || qValue > 100000) return 0;
    }
    catch (...) {
        return 0;
    }


    const int Q = static_cast<int>(qValue);

    unordered_map<string, Inventory> warehouse;
    unordered_set<string> usedLots; // Mã lô đã từng được sử dụng trên toàn kho

    for (int lineNo = 0; lineNo < Q; ++lineNo) {
        string line;

        // Nếu hết input trước khi đủ Q dòng, dòng còn thiếu được xem là INVALID.
        if (!getline(cin, line)) {
            cout << "INVALID\n";
            continue;
        }

        stringstream ss(line);
        vector<string> tokens;
        string token;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            cout << "INVALID\n";
            continue;
        }

        const string& command = tokens[0];

        if (command == "IMPORT") {
            if (tokens.size() != 4 ||
                !validCode(tokens[1]) ||
                !validCode(tokens[2])) {
                cout << "INVALID\n";
                continue;
            }

            long long qty;
            if (!parseQuantity(tokens[3], qty)) {
                cout << "INVALID\n";
                continue;
            }

            const string& sku = tokens[1];
            const string& lotId = tokens[2];

            if (usedLots.count(lotId)) {
                cout << "DUPLICATE_LOT\n";
                continue;
            }

            // Theo đề, tổng tồn kho luôn nhỏ hơn 2,147,483,647.
            // Kiểm tra bổ sung để tránh vượt giới hạn nếu dữ liệu ngoài giả thiết.
            long long current = 0;
            auto it = warehouse.find(sku);
            if (it != warehouse.end()) current = it->second.total;

            if (current + qty >= 2'147'483'647LL) {
                cout << "INVALID\n";
                continue;
            }

            warehouse[sku].lots.push_back({ lotId, qty });
            warehouse[sku].total += qty;
            usedLots.insert(lotId);

            cout << "OK\n";
        }
        else if (command == "EXPORT") {
            if (tokens.size() != 3 || !validCode(tokens[1])) {
                cout << "INVALID\n";
                continue;
            }

            long long qty;
            if (!parseQuantity(tokens[2], qty)) {
                cout << "INVALID\n";
                continue;
            }

            const string& sku = tokens[1];
            auto it = warehouse.find(sku);
            long long available =
                (it == warehouse.end() ? 0LL : it->second.total);

            if (available < qty) {
                cout << "NOT_ENOUGH " << available << '\n';
                continue;
            }

            Inventory& inventory = it->second;
            long long remaining = qty;
            bool first = true;

            while (remaining > 0) {
                Lot& frontLot = inventory.lots.front();
                long long taken = min(remaining, frontLot.quantity);

                if (!first) cout << ' ';
                cout << frontLot.id << ':' << taken;
                first = false;

                frontLot.quantity -= taken;
                remaining -= taken;
                inventory.total -= taken;

                if (frontLot.quantity == 0) {
                    inventory.lots.pop_front();
                }
            }

            cout << '\n';
        }
        else if (command == "STOCK") {
            if (tokens.size() != 2 || !validCode(tokens[1])) {
                cout << "INVALID\n";
                continue;
            }

            auto it = warehouse.find(tokens[1]);
            cout << (it == warehouse.end() ? 0LL : it->second.total)
                << '\n';
        }
        else {
            cout << "INVALID\n";
        }
    }
}