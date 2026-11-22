# BT2 - Nhập/xuất kho theo FIFO

 1. Giới thiệu

Bài này quản lý các lô hàng trong kho. Mỗi mặt hàng có một mã SKU và có thể được nhập thành nhiều lô.

Khi xuất hàng, chương trình lấy hàng từ lô được nhập sớm nhất trước. Nếu lô đầu không đủ thì lấy tiếp ở lô sau. Cách làm này gọi là FIFO (nhập trước, xuất trước).

 2. Cách em làm

Em dùng `unordered_map` để tìm thông tin của từng SKU. Mỗi SKU có một `queue` lưu các lô theo thứ tự nhập và một biến tổng số lượng còn trong kho.

Em dùng thêm `unordered_set` để kiểm tra mã lô đã được sử dụng hay chưa. Mã lô đã dùng vẫn được xem là đã sử dụng kể cả khi hàng trong lô đó đã xuất hết.

Khi có lệnh `EXPORT`, chương trình kiểm tra tồn kho trước. Nếu không đủ hàng thì in `NOT_ENOUGH` và không thay đổi kho. Nếu đủ thì lấy lần lượt từ đầu queue cho đến khi đủ số lượng cần xuất.

 3. Các tệp trong bài

```text
BT2/
|-- README.md
|-- solution.cpp
`-- tests/
    `-- input1.txt
```

- `solution.cpp`: mã nguồn C++ của bài 2.
- `README.md`: giới thiệu và hướng dẫn chạy.
- `tests/input1.txt`: dữ liệu ví dụ để kiểm tra.

 4. Cách chạy bằng Visual Studio

1. Mở Visual Studio và chọn **Create a new project**.
2. Chọn **Console App** có ngôn ngữ C++.
3. Tạo project, ví dụ đặt tên `BT2`.
4. Mở file `.cpp` được tạo sẵn, xóa code mẫu rồi dán nội dung trong `solution.cpp` vào.
5. Vào **Project > Properties > C/C++ > Language** và chọn **ISO C++17** ở mục **C++ Language Standard**.
6. Nhấn `Ctrl + F5` để chạy.

Khi chương trình chạy, nhập số lệnh `Q` ở dòng đầu, sau đó nhập từng lệnh trên một dòng.

 5. Cách chạy bằng MinGW

Mở Terminal tại thư mục `BT2`, sau đó nhập:

```bash
g++ -std=c++17 -O2 solution.cpp -o BT2.exe
BT2.exe < tests/input1.txt
```

 6. Đầu vào

Dòng đầu là số lệnh `Q`, với `1 <= Q <= 100000`. Các dòng sau là một trong các lệnh:

```text
IMPORT sku lot qty
EXPORT sku qty
STOCK sku
```

Mã `sku` và `lot` dài tối đa 20 ký tự. `qty` là số nguyên dương. Mã lô không được trùng trong toàn kho.

 7. Đầu ra

Mỗi lệnh in đúng một dòng:

- `IMPORT`: in `OK` nếu nhập thành công; in `DUPLICATE_LOT` nếu mã lô đã được sử dụng.
- `EXPORT`: in các lô đã lấy theo dạng `lot:so_luong`. Nếu kho không đủ hàng thì in `NOT_ENOUGH <ton_kho>` và không xuất hàng.
- `STOCK`: in tổng số lượng còn lại của SKU. SKU chưa có trong kho thì in `0`.
- Lệnh sai, sai số tham số, mã quá dài hoặc số lượng không hợp lệ thì in `INVALID` và tiếp tục lệnh sau.

Token số chỉ được chứa chữ số `0` đến `9`. Số âm, dạng `1e5`, token như `12abc`, số lượng bằng 0 và giá trị từ `2.147.483.647` trở lên đều không hợp lệ. Tổng tồn kho cũng phải nhỏ hơn `2.147.483.647`.

 8. Kiểm tra

Có thể chạy thử bằng dữ liệu trong `tests/input1.txt`. Nên thử thêm trường hợp nhập trùng mã lô, xuất thiếu hàng, SKU chưa có và lệnh sai.
