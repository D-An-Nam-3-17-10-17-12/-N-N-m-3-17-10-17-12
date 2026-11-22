# Bài 2 – Nhập/xuất kho theo FIFO

## Ý tưởng
- Mỗi mã hàng (SKU) có một hàng đợi (queue) các lô; lô nhập sớm nhất nằm ở đầu hàng đợi.
- Dùng `unordered_map` để tìm hàng đợi của SKU nhanh (trung bình O(1)).
- Dùng `unordered_set` lưu mọi mã lô đã từng nhập để phát hiện `DUPLICATE_LOT` trong toàn kho
  (lô đã xuất hết vẫn tính là đã dùng).
- `EXPORT`: kiểm tra tồn kho trước; nếu không đủ in `NOT_ENOUGH <tồn>` và không xuất gì.
  Nếu đủ thì lấy lần lượt từ lô đầu hàng đợi, lô hết thì bỏ khỏi hàng đợi.

## Cách chạy
Visual Studio: mở file `solution.cpp` trong project C++, nhấn Ctrl + F5, dán dữ liệu vào cửa sổ.

Dòng lệnh:

    g++ -O2 -std=c++17 -o solution solution.cpp
    ./solution < tests/test_example.in

## Kiểm tra với các test
Mỗi test có file `.in` (đầu vào) và `.out` (kết quả đúng):

    ./solution < tests/test_example.in | diff - tests/test_example.out

| Test | Nội dung |
|---|---|
| test_example | Ví dụ trong đề |
| test_fifo | Xuất qua nhiều lô, xuất đúng hết lô, xuất khi hết hàng |
| test_invalid | Dữ liệu sai: số lượng 0, quá 10^9, có chữ, mã quá 20 ký tự, thiếu tham số, sai tên lệnh |

## Độ phức tạp
IMPORT và STOCK: O(1) trung bình. EXPORT: O(số lô bị lấy); mỗi lô chỉ bị lấy ra khỏi hàng đợi một lần
nên tổng cho Q lệnh là O(Q).