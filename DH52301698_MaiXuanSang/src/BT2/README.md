# BT2 - Nhập/xuất kho theo FIFO

## 1. Giới thiệu

Chương trình quản lý nhập/xuất kho theo nguyên tắc FIFO (First In - First Out): khi xuất hàng, lấy từ lô nhập sớm nhất trước, nếu lô đầu không đủ thì lấy tiếp sang lô kế tiếp.

Các lệnh hỗ trợ: `IMPORT sku lot qty`, `EXPORT sku qty`, `STOCK sku`. Lệnh sai thì in `INVALID` và xử lý tiếp dòng sau.

## 2. Thuật toán

* **IMPORT:** kiểm tra mã lô đã dùng chưa; nếu chưa thì đẩy lô vào cuối Queue của SKU và cộng vào tổng tồn kho. Độ phức tạp O(1).
* **EXPORT:** nếu tồn kho không đủ thì in `NOT_ENOUGH <tồn kho>` (không xuất gì); nếu đủ thì lấy từ đầu Queue, lô nào hết thì bỏ ra khỏi Queue. Mỗi lô bị bỏ ra tối đa một lần nên tổng chi phí là O(tổng số lô).
* **STOCK:** trả về tổng tồn kho của SKU (chưa có thì `0`). Độ phức tạp O(1).

## 3. Cấu trúc dữ liệu

* **HashMap (`unordered_map`):** ánh xạ SKU -> thông tin SKU, tìm nhanh O(1).
* **Queue:** lưu các lô của từng SKU theo thứ tự nhập (FIFO).
* **Tổng tồn kho:** lưu sẵn trong từng SKU để `STOCK` và kiểm tra `EXPORT` không phải duyệt Queue.
* **HashSet (`unordered_set`):** lưu mã lô đã dùng để phát hiện `DUPLICATE_LOT` (mã lô không trùng trong toàn kho, kể cả lô đã xuất hết).

## 4. Cách biên dịch

Sử dụng trình biên dịch C++ hỗ trợ C++17:
g++ -std=c++17 solution.cpp -o BT2.exe

## 5. Cách chạy

Chạy chương trình và nhập dữ liệu từ bàn phím (stdin), kết quả được in ra màn hình (stdout). Chương trình hỗ trợ tệp đầu vào có kiểu xuống dòng Windows (CRLF) và Linux (LF).

Hoặc sử dụng file kiểm thử:
BT2.exe < tests/input1.txt

## 6. Giới hạn

* `sku`, `lot` dài tối đa 20 ký tự; `qty` là số nguyên từ 1 đến 10^9 chỉ gồm chữ số.
* Tên lệnh phân biệt chữ hoa/chữ thường.
* Mã lô đã dùng thì không được dùng lại, kể cả khi lô đó đã xuất hết.
