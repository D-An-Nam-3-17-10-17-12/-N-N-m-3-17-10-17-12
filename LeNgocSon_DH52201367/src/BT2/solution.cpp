#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>

using namespace std;

// Cấu trúc lưu trữ thông tin của một lô hàng
struct Lot {
    string id;
    long long qty;
};

int main() {
    // Tối ưu hóa luồng I/O cho số lượng truy vấn lớn (Q = 10^5)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    if (!getline(cin, line)) return 0;

    long long Q = 0;
    stringstream sq(line);
    if (!(sq >> Q)) return 0;

    // Các cấu trúc dữ liệu chính
    unordered_map<string, queue<Lot>> inventory;    // Hàng đợi FIFO quản lý các lô theo từng SKU
    unordered_map<string, long long> totalStock;    // Tra cứu siêu tốc O(1) tổng tồn kho của mỗi SKU
    unordered_set<string> usedLots;                 // Kiểm tra trùng lặp mã lô trên toàn kho

    for (long long i = 0; i < Q; ) {
        if (!getline(cin, line)) break;
        if (line.empty()) continue;
        i++; // Chỉ đếm các dòng truy vấn thực tế có dữ liệu

        stringstream ss(line);
        string cmd;
        if (!(ss >> cmd)) {
            cout << "INVALID\n";
            continue;
        }

        if (cmd == "IMPORT") {
            string sku, lot, qty_str, extra;
            // Bắt lỗi: thiếu/thừa tham số, hoặc độ dài mã vượt 20 ký tự
            if (!(ss >> sku >> lot >> qty_str) || (ss >> extra) || sku.length() > 20 || lot.length() > 20) {
                cout << "INVALID\n"; continue;
            }

            long long qty;
            try { qty = stoll(qty_str); } // Chuyển đổi an toàn sang số nguyên 64-bit
            catch (...) { cout << "INVALID\n"; continue; }

            if (qty <= 0) { cout << "INVALID\n"; continue; }

            // Kiểm tra mã lô đã từng tồn tại chưa
            if (usedLots.count(lot)) {
                cout << "DUPLICATE_LOT\n";
            }
            else {
                usedLots.insert(lot);
                inventory[sku].push({ lot, qty });
                totalStock[sku] += qty; // Cộng dồn số lượng vào bộ đếm O(1)
                cout << "OK\n";
            }
        }
        else if (cmd == "EXPORT") {
            string sku, qty_str, extra;
            // Bắt lỗi: thiếu/thừa tham số, độ dài mã vượt 20 ký tự
            if (!(ss >> sku >> qty_str) || (ss >> extra) || sku.length() > 20) {
                cout << "INVALID\n"; continue;
            }

            long long qty;
            try { qty = stoll(qty_str); }
            catch (...) { cout << "INVALID\n"; continue; }

            if (qty <= 0) { cout << "INVALID\n"; continue; }

            long long currentStock = totalStock[sku]; // Tự động trả về 0 nếu mã hàng chưa tồn tại
            if (currentStock < qty) {
                cout << "NOT_ENOUGH " << currentStock << "\n";
            }
            else {
                long long rem = qty; // Số lượng còn cần lấy thêm
                vector<string> res;

                // Rút hàng dần dần từ các lô cũ nhất (Front của Queue)
                while (rem > 0 && !inventory[sku].empty()) {
                    Lot& frontLot = inventory[sku].front();
                    if (frontLot.qty <= rem) {
                        // Lấy sạch lô này và chuyển sang lô tiếp theo
                        res.push_back(frontLot.id + ":" + to_string(frontLot.qty));
                        rem -= frontLot.qty;
                        inventory[sku].pop();
                    }
                    else {
                        // Lấy một phần của lô và giữ lại lô này ở đầu Queue
                        res.push_back(frontLot.id + ":" + to_string(rem));
                        frontLot.qty -= rem;
                        rem = 0; // Đã lấy đủ
                    }
                }

                totalStock[sku] -= qty; // Trừ tổng tồn kho

                // In kết quả theo đúng định dạng
                for (size_t j = 0; j < res.size(); j++) {
                    cout << res[j] << (j + 1 == res.size() ? "" : " ");
                }
                cout << "\n";
            }
        }
        else if (cmd == "STOCK") {
            string sku, extra;
            // Bắt lỗi tham số và độ dài
            if (!(ss >> sku) || (ss >> extra) || sku.length() > 20) {
                cout << "INVALID\n"; continue;
            }
            // Trả về số lượng (nếu sku chưa tồn tại, Map tự tạo khóa và cho giá trị 0)
            cout << totalStock[sku] << "\n";
        }
        else {
            // Trường hợp gõ sai lệnh (VD: SELL EGG 1)
            cout << "INVALID\n";
        }
    }
    return 0;
}