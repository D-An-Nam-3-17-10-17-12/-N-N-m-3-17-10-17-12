# BÀI 2 - NHẬP/XUẤT KHO THEO FIFO

## 1. Ngôn ngữ
- C++

## 2. Cấu trúc dữ liệu
- HashMap (bảng băm địa chỉ chuỗi): Tra cứu nhanh hàng đợi lô hàng theo mã SKU và kiểm tra trùng mã lô toàn kho.
- Queue (hàng đợi FIFO cài đặt bằng danh sách liên kết đơn): Quản lý các lô hàng theo thứ tự nhập trước - xuất trước cho từng SKU.

## 3. Thuật toán
- Cơ chế FIFO (First-In, First-Out): Khi xuất hàng, lấy lần lượt từ lô ở đầu hàng đợi; nếu không đủ thì chuyển sang lô kế tiếp.
- Kiểm tra tính hợp lệ dữ liệu đầu vào (`sku`, `lot` tối đa 20 ký tự, `qty` nguyên dương) và xuất `INVALID` nếu sai quy định.

## 4. Cách chạy
- Mở file `solution.cpp`.
- Biên dịch chương trình C++ (ví dụ: `g++ -O3 solution.cpp -o solution`).
- Nhập dữ liệu đầu vào từ bàn phím hoặc chuyển hướng file test.
- Xem kết quả hiển thị trên màn hình.

## 5. Giới hạn
- Số lượng lệnh tối đa theo đề bài ($Q \le 10^5$), mã `sku` và `lot` tối đa 20 ký tự, số lượng `qty` trong $[1, 10^9]$.
- Mã lô không được trùng nhau trên toàn bộ kho hàng.