\# Bài 2 – Nhập/xuất kho theo FIFO



\## 1. Giới thiệu

Chương trình quản lý hàng hóa trong kho bằng C++. Hỗ trợ nhập hàng, xuất hàng và kiểm tra số lượng tồn kho theo nguyên tắc FIFO (First In – First Out).



\## 2. Chức năng

\- `IMPORT`: Nhập lô hàng mới.

\- `EXPORT`: Xuất hàng theo thứ tự nhập trước, xuất trước.

\- `STOCK`: Kiểm tra số lượng hàng tồn kho.

\- Kiểm tra mã lô trùng và dữ liệu không hợp lệ.



\## 3. Cấu trúc dữ liệu

\- `struct`: Lưu thông tin lô hàng và sản phẩm.

\- `map`: Quản lý sản phẩm theo mã SKU.

\- `deque`: Lưu các lô hàng theo thứ tự nhập.

\- `set`: Kiểm tra mã lô bị trùng.

\- `vector`: Lưu dữ liệu lệnh nhập vào.



\## 4. Công nghệ sử dụng

\- Ngôn ngữ: C++.

\- Môi trường: Visual Studio.

\- Thư viện: iostream, string, sstream, vector, deque, map, set.



\## 5. Kết luận

Chương trình giúp quản lý nhập xuất kho hiệu quả, áp dụng cấu trúc dữ liệu và nguyên tắc FIFO trong C++.

