# BT1 - Tìm đường ngắn nhất trong kho hàng

## 1\. Giới thiệu

Chương trình tìm đường đi ngắn nhất trong kho hàng dạng lưới R × C, với các ô `.` là đường đi và `#` là vật cản.

## 2\. Thuật toán

* **BFS:** Tìm khoảng cách ngắn nhất giữa các vị trí.
* **Bitmask DP:** Tìm thứ tự đi qua các điểm cần ghé thăm với tổng số bước nhỏ nhất.

## 3\. Cấu trúc dữ liệu

* **Vector:** Lưu bản đồ kho hàng.
* **Queue:** Hỗ trợ thuật toán BFS.
* **Ma trận khoảng cách:** Lưu khoảng cách giữa các điểm.
* **DP Bitmask:** Lưu kết quả các trạng thái trung gian.

## 4\. Cách biên dịch

Sử dụng trình biên dịch C++ hỗ trợ C++17:
g++ -std=c++17 solution.cpp -o BT1.exe

## 5\. Cách chạy

Chạy chương trình và nhập dữ liệu từ bàn phím (stdin), kết quả được in ra màn hình (stdout). Chương trình hỗ trợ tệp đầu vào có kiểu xuống dòng Windows (CRLF) và Linux (LF).

Hoặc sử dụng file kiểm thử:
BT1.exe < tests/input1.txt

## 6\. Giới hạn

Số điểm trong mỗi truy vấn từ 2 đến 8 theo điều kiện của chương trình.

