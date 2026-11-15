 # BT1 - Tìm đường ngắn nhất trong kho hàng

## 1. Giới thiệu

Bài này yêu cầu tìm đường đi trong một kho hàng được biểu diễn bằng bảng gồm `R` hàng và `C` cột.

- `.` là ô có thể đi qua.
- `#` là vật cản.
- Xe chỉ được đi lên, xuống, sang trái hoặc sang phải.
- Mỗi lần chuyển sang ô bên cạnh được tính là 1 bước.

Mỗi truy vấn có một điểm xuất phát và các điểm cần ghé qua. Xe được chọn thứ tự ghé các điểm sao cho tổng số bước ít nhất và không cần quay lại điểm xuất phát.

## 2. Ý tưởng 

Đầu tiên, em lưu bản đồ bằng `vector<string>`. Sau đó em dùng BFS để tìm khoảng cách từ một vị trí đến những ô khác. Em dùng BFS vì mỗi lần di chuyển đều có chi phí bằng 1 bước.

Khi chạy BFS, chương trình lưu lại ô đứng trước để có thể tìm lại đường đi. Sau khi có khoảng cách giữa các điểm cần ghé, chương trình dùng quy hoạch động Bitmask để chọn thứ tự ghé điểm có tổng số bước nhỏ nhất. Mảng `trace` dùng để khôi phục thứ tự đó.

Cuối cùng, chương trình ghép các đoạn đường đi và in ra tọa độ theo yêu cầu của đề.

## 3. Các tệp trong bài

```text
BT1/
|-- README.md
|-- solution.cpp
`-- tests/
    `-- input1.txt
```

- `solution.cpp`: mã nguồn C++ của bài 1.
- `README.md`: file giới thiệu và hướng dẫn chạy.
- `tests/input1.txt`: dữ liệu mẫu dùng để chạy thử.

## 4. Cách chạy bằng Visual Studio

Bài làm sử dụng C++17.

1. Mở Visual Studio và chọn **Create a new project**.
2. Chọn mẫu **Console App** có ngôn ngữ C++.
3. Đặt tên project, ví dụ `BT1`.
4. Mở file `.cpp` được tạo sẵn trong project.
5. Xóa code mẫu và dán nội dung trong `solution.cpp` vào.
6. Vào **Project > Properties > C/C++ > Language** và chọn **ISO C++17** ở mục **C++ Language Standard**.
7. Nhấn `Ctrl + F5` để chạy chương trình.

Lưu ý: Không nên chỉ mở riêng `solution.cpp` bằng Open File rồi bấm F5. Khi đó Visual Studio có thể hiện `Miscellaneous Files`; cần tạo hoặc mở một project C++ trước thì mới chạy được.

## 5. Cách chạy bằng MinGW (nếu dùng)

Mở Terminal tại thư mục `BT1`, sau đó nhập:

```bash
g++ -std=c++17 -O2 solution.cpp -o BT1.exe
BT1.exe < tests/input1.txt
```

## 6. Input
1. Dòng đầu gồm hai số `R C`.
2. `R` dòng tiếp theo là bản đồ, mỗi dòng có `C` ký tự `.` hoặc `#`.
3. Dòng tiếp theo là số truy vấn `Q`.
4. Mỗi truy vấn có dạng:

```text
k r1 c1 r2 c2 ... rk ck
```

Trong đó `2 <= k <= 8`. Điểm đầu tiên là vị trí xuất phát của xe. Tọa độ hàng và cột được đánh số từ 0.

## 7. Output

Chương trình in ra hai phần:

- `Q` dòng đầu là số bước ít nhất của từng truy vấn.
  - In `-1` nếu không thể đi qua hết các điểm.
  - In `INVALID` nếu `k` không thuộc `[2,8]`, số lượng dữ liệu không đúng, tọa độ nằm ngoài kho hoặc tọa độ rơi vào vật cản.
- `Q` dòng tiếp theo là các tọa độ xe đi qua, theo dạng `(dòng,cột)`.
  - In ô xuất phát và tối đa 10 ô tiếp theo.
  - Nếu đường đi còn dài hơn phần đã in thì thêm `...`.
  - Nếu kết quả là `-1` hoặc `INVALID` thì in `-`.

Nếu có nhiều đường đi ngắn nhất, chương trình có thể in ra một trong các đường đó.

## 8. Kiểm tra

Có thể chạy thử bằng dữ liệu trong `tests/input1.txt`. Đây là dữ liệu ví dụ của đề bài. Có thể tạo thêm file input khác trong thư mục `tests` để thử các trường hợp khác.