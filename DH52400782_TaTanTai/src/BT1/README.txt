# BÀI 1 - TÌM ĐƯỜNG NGẮN NHẤT TRONG KHO

## 1. Ngôn ngữ
- C++

## 2. Cấu trúc dữ liệu
- Mảng 2 chiều: Lưu bản đồ kho.
- Queue (Hàng đợi): Phục vụ thuật toán BFS.
- Mảng đánh dấu: Lưu khoảng cách và trạng thái truy vấn.
- Duyệt hoán vị: Tìm thứ tự lấy hàng tối ưu khi đi qua nhiều điểm.

## 3. Thuật toán
- BFS (Breadth-First Search): Tìm đường đi ngắn nhất giữa hai tọa độ.
- Thuật toán sinh hoán vị: Xử lý tối ưu hóa đường đi qua nhiều điểm lấy hàng ($2 \le k \le 8$).

## 4. Cách chạy
- Mở file `solution.cpp`.
- Biên dịch chương trình C++ (ví dụ: `g++ solution.cpp -o solution`).
- Nhập dữ liệu đầu vào (hoặc dùng chuyển hướng file).
- Xem kết quả hiển thị trên màn hình.

## 5. Giới hạn
- Kích thước bản đồ theo cấu hình đề bài.
- Mỗi truy vấn có tối đa 8 điểm cần ghé thăm.