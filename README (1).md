# Bài 1 -- Tìm đường ngắn nhất trong kho hàng

## Mô tả

Tìm đường đi ngắn nhất từ ô xuất phát đến tất cả các điểm cần ghé thăm
trong kho. Xe chỉ di chuyển lên, xuống, trái, phải; `#` là vật cản và
`.` là ô có thể đi.

## Thuật toán

-   **BFS:** Tính khoảng cách ngắn nhất giữa các điểm và truy vết đường
    đi.
-   **Bitmask DP:** Tìm thứ tự ghé thăm các điểm sao cho tổng số bước là
    nhỏ nhất.

## Cách chạy

Mở file `chuongtrinh.cpp` trong Visual Studio, biên dịch và chạy chương
trình. Nhập số hàng, số cột, bản đồ kho, số truy vấn và dữ liệu từng
truy vấn theo yêu cầu đề bài.

## Kết quả

Chương trình in ra số bước ngắn nhất của từng truy vấn, sau đó in đường
đi tương ứng. Kết quả là `-1` nếu không tìm được đường đi và `INVALID`
nếu dữ liệu truy vấn không hợp lệ.
