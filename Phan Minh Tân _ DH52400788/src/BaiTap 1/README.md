**Bài 1 – Tìm đường ngắn nhất trong kho hàng**



**1. Giới thiệu**

Chương trình tìm đường đi ngắn nhất trong bản đồ kho hàng, sử dụng thuật toán BFS và quy hoạch động để tìm thứ tự ghé các điểm cần đến sao cho tổng số bước di chuyển là nhỏ nhất.



**2. Công nghệ sử dụng**

\- Ngôn ngữ lập trình: C++

\- Môi trường chạy: Visual Studio 2022

\- Thư Viện:

\#include <iostream>   // Nhập, xuất dữ liệu

\#include <vector>     // Mảng động

\#include <string>     // Xử lý chuỗi ký tự

\#include <queue>      // Hàng đợi, dùng cho BFS

\#include <sstream>    // Tách chuỗi thành các phần

\#include <algorithm>  // Các thuật toán như reverse(), min()

\#include <climits>    // Giới hạn kiểu số nguyên

\#include <cctype>     // Kiểm tra ký tự khoảng trắng



**3. Cách chạy chương trình**

1\. Mở Visual Studio 2022.

2\. Tạo hoặc mở dự án Console App bằng C++.

3\. Thêm file baitap1 vào dự án.

4\. Chọn chuẩn C++17 trong Project Properties → C/C++ → Language → C++ Language Standard.

5\. Nhấn Ctrl + F5 để chạy chương trình.

6\. Nhập ma tran cho chuong trinh



**4. Định dạng dữ liệu đầu vào**

\- Dòng đầu tiên gồm hai số R C, lần lượt là số hàng và số cột của bản đồ.

\- Tiếp theo là "R" dòng mô tả bản đồ.

\- Ký tự "." biểu thị ô có thể di chuyển.

\- Ký tự "#" biểu thị ô bị chặn.

\- Tiếp theo là số lượng truy vấn "Q".

\- Mỗi truy vấn gồm số điểm "k", sau đó là "k" cặp tọa độ hàng và cột. Tọa độ được đánh số từ 0.



**5. Thuật toán**

\- BFS: Tính khoảng cách ngắn nhất giữa các điểm và tìm đường đi giữa hai vị trí.

\- Quy hoạch động kết hợp bitmask: Tìm thứ tự ghé các điểm sao cho tổng số bước nhỏ nhất.

\- Kiểm tra dữ liệu đầu vào: Phát hiện truy vấn không hợp lệ hoặc vị trí nằm ngoài bản đồ hay trên vật cản.



**6. Kết quả đầu ra**

\- In tổng số bước di chuyển ít nhất cho từng truy vấn.

\- In đường đi minh họa tương ứng.

\- In "-1" nếu không thể đi qua tất cả các điểm.

\- In "INVALID" nếu truy vấn không hợp lệ theo quy định của đề bài.

