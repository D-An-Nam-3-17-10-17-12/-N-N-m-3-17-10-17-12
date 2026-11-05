#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <sstream>

using namespace std;

struct Order {
    string id;
    long long priority;
    long long order_index;
    
    bool operator<(const Order& other) const {
        if (priority != other.priority) {
            return priority < other.priority;
        }
        return order_index > other.order_index;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Q;
    if (!(cin >> Q)) return 0;
    string dummy;
    getline(cin, dummy);
    
    priority_queue<Order> pq;
    unordered_set<string> existing_ids;
    long long global_counter = 0;
    
    for (int q = 0; q < Q; ++q) {
        string line;
        if (!getline(cin, line)) break;
        if (!line.empty() && line.back() == '\r') line.pop_back(); // Khử ký tự \r
        if (line.empty()) { q--; continue; }
        
        stringstream ss(line);
        string cmd;
        ss >> cmd;
        
        if (cmd == "ORDER") {
            string id;
            long long priority;
            if (!(ss >> id >> priority)) {
                cout << "INVALID\n";
                continue;
            }
            string extra;
            if (ss >> extra || id.length() > 20 || priority < 0) {
                cout << "INVALID\n";
                continue;
            }
            if (existing_ids.count(id)) {
                cout << "DUPLICATE\n";
                continue;
            }
            existing_ids.insert(id);
            pq.push({id, priority, ++global_counter});
            cout << "OK\n";
        } 
        else if (cmd == "NEXT") {
            string extra;
            if (ss >> extra) {
                cout << "INVALID\n";
                continue;
            }
            if (pq.empty()) {
                cout << "EMPTY\n";
            } else {
                Order top_order = pq.top();
                pq.pop();
                cout << top_order.id << " " << top_order.priority << "\n";
            }
        } 
        else if (cmd == "PEEK") {
            string extra;
            if (ss >> extra) {
                cout << "INVALID\n";
                continue;
            }
            if (pq.empty()) {
                cout << "EMPTY\n";
            } else {
                Order top_order = pq.top();
                cout << top_order.id << " " << top_order.priority << "\n";
            }
        } 
        else if (cmd == "SIZE") {
            string extra;
            if (ss >> extra) {
                cout << "INVALID\n";
                continue;
            }
            cout << pq.size() << "\n";
        } 
        else {
            cout << "INVALID\n";
        }
    }
    
    return 0;
}