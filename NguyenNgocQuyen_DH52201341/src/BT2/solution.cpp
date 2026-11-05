#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

struct Lot {
    string lot_id;
    long long qty;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    if (!(cin >> Q)) return 0;
    string dummy;
    getline(cin, dummy);
    
    unordered_map<string, queue<Lot>> inventory;
    unordered_map<string, long long> total_stock;
    unordered_set<string> used_lots;
    
    for (int q = 0; q < Q; ++q) {
        string line;
        if (!getline(cin, line)) break;
        if (!line.empty() && line.back() == '\r') line.pop_back(); // Khử ký tự \r
        if (line.empty()) { q--; continue; }
        
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        
        if (cmd == "IMPORT") {
            string sku, lot;
            long long qty;
            if (!(ss >> sku >> lot >> qty)) {
                cout << "INVALID\n";
                continue;
            }
            string extra;
            if (ss >> extra || sku.length() > 20 || lot.length() > 20 || qty <= 0) {
                cout << "INVALID\n";
                continue;
            }
            if (used_lots.count(lot)) {
                cout << "DUPLICATE_LOT\n";
                continue;
            }
            used_lots.insert(lot);
            inventory[sku].push({lot, qty});
            total_stock[sku] += qty;
            cout << "OK\n";
        } 
        else if (cmd == "EXPORT") {
            string sku;
            long long qty;
            if (!(ss >> sku >> qty)) {
                cout << "INVALID\n";
                continue;
            }
            string extra;
            if (ss >> extra || sku.length() > 20 || qty <= 0) {
                cout << "INVALID\n";
                continue;
            }
            
            if (total_stock[sku] < qty) {
                cout << "NOT_ENOUGH " << total_stock[sku] << "\n";
                continue;
            }
            
            total_stock[sku] -= qty;
            vector<string> exported_parts;
            long long remaining_to_export = qty;
            
            while (remaining_to_export > 0) {
                Lot& current_lot = inventory[sku].front();
                if (current_lot.qty <= remaining_to_export) {
                    remaining_to_export -= current_lot.qty;
                    exported_parts.push_back(current_lot.lot_id + ":" + to_string(current_lot.qty));
                    inventory[sku].pop();
                } else {
                    current_lot.qty -= remaining_to_export;
                    exported_parts.push_back(current_lot.lot_id + ":" + to_string(remaining_to_export));
                    remaining_to_export = 0;
                }
            }
            
            for (size_t i = 0; i < exported_parts.size(); ++i) {
                cout << exported_parts[i] << (i + 1 == exported_parts.size() ? "" : " ");
            }
            cout << "\n";
        } 
        else if (cmd == "STOCK") {
            string sku;
            if (!(ss >> sku)) {
                cout << "INVALID\n";
                continue;
            }
            string extra;
            if (ss >> extra || sku.length() > 20) {
                cout << "INVALID\n";
                continue;
            }
            if (total_stock.find(sku) == total_stock.end()) {
                cout << "0\n";
            } else {
                cout << total_stock[sku] << "\n";
            }
        } 
        else {
            cout << "INVALID\n";
        }
    }
    
    return 0;
}