**Bài 1 – Tìm đường ngắn nhất trong kho hàng**

**1. Giới thiệu**

Chương trình tìm số bước di chuyển ít nhất của xe trong bản đồ kho hàng, sử dụng thuật toán BFS và đệ quy để chọn thứ tự ghé các điểm cần đến sao cho tổng số bước là nhỏ nhất.

**2. Công nghệ sử dụng**

\- Ngôn ngữ lập trình: C++

\- Môi trường chạy: Visual Studio

\- Thư viện:

\#include \<iostream\> // Nhập, xuất dữ liệu

\#include \<string\> // Xử lý chuỗi ký tự

\#include \<queue\> // Hàng đợi, dùng cho BFS

\#include \<algorithm\> // Các thuật toán chuẩn

\#include \<climits\> // Giới hạn kiểu số nguyên

**3. Cách chạy chương trình**

1\. Mở Visual Studio.

2\. Tạo hoặc mở dự án Console App bằng C++.

3\. Thêm 3 file thuvien.h, caidat.cpp, chuongtrinh.cpp vào dự án.

4\. Chọn chuẩn C++17 trong Project Properties → C/C++ → Language → C++ Language Standard.

5\. Nhấn Ctrl + F5 để chạy chương trình.

6\. Nhập bản đồ và các truy vấn cho chương trình.

**4. Định dạng dữ liệu đầu vào**

\- Dòng đầu tiên gồm hai số R C, lần lượt là số hàng và số cột của bản đồ.

\- Tiếp theo là "R" dòng mô tả bản đồ.

\- Ký tự "." biểu thị ô có thể di chuyển.

\- Ký tự "#" biểu thị ô bị chặn.

\- Tiếp theo là số lượng truy vấn "Q".

\- Mỗi truy vấn gồm số điểm "k", sau đó là "k" cặp tọa độ hàng và cột. Tọa độ được đánh số từ 0.

**5. Thuật toán**

\- BFS: Tính khoảng cách ngắn nhất giữa các điểm.

\- Đệ quy: Thử các thứ tự ghé các điểm để tìm tổng số bước nhỏ nhất.

\- Kiểm tra dữ liệu đầu vào: Phát hiện k không hợp lệ, tọa độ nằm ngoài bản đồ hoặc trên vật cản.

**6. Kết quả đầu ra**

\- In tổng số bước di chuyển ít nhất cho từng truy vấn.

\- In "-1" nếu không thể đi qua tất cả các điểm.

\- In "INVALID" nếu truy vấn không hợp lệ theo quy định của đề bài.
