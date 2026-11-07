# Tìm đường ngắn nhất cho xe trong kho hàng

Bài 1 của đồ án phần mềm quản lý kho, viết bằng **C++**. Chương trình tìm số bước ít nhất để một xe di chuyển trong kho, xuất phát từ một vị trí và đi qua một hoặc nhiều điểm lấy hàng, sử dụng **ma trận 2D** và thuật toán **BFS**.

## Bài toán

- Kho là một lưới hình chữ nhật `R` hàng × `C` cột.
- Ô `.` là lối đi, ô `#` là vật cản (tường, cột).
- Xe đi theo 4 hướng (lên, xuống, trái, phải), mỗi bước sang một ô kề.
- Mỗi truy vấn cho `k` điểm (2 ≤ k ≤ 8). Điểm đầu tiên là vị trí xe, các điểm còn lại là nơi cần đi qua (thứ tự tùy ý, không cần quay về điểm xuất phát). Cần tìm tổng số bước ít nhất.

## Ý tưởng giải

1. **Lưu bản đồ:** dùng ma trận 2D `bandokho[r][c]`. Mỗi ô là một đỉnh của đồ thị, hai ô kề nhau (không phải `#`) là một cạnh.
2. **Đường ngắn nhất giữa hai ô (BFS):** hàm `loang` lan ra từ ô xuất phát theo từng lớp bằng hàng đợi, ghi số bước vào ma trận `buoc[r][c]`. Ô không tới được giữ giá trị `-1`.
3. **Khoảng cách giữa các điểm:** chạy BFS từ từng điểm trong truy vấn để lập bảng `khoangcach[i][j]`.
4. **Đi qua nhiều điểm:** hàm `timhoanvi` dùng đệ quy thử mọi thứ tự ghé thăm các điểm (điểm xuất phát cố định), lấy tổng nhỏ nhất. Nếu có đoạn không đi được thì bỏ nhánh đó; không có thứ tự nào đi hết thì kết quả là `-1`.

### Độ phức tạp

- BFS: O(R · C) cho mỗi lần chạy, chạy k lần cho mỗi truy vấn.
- Thử thứ tự: tối đa (k − 1)! ≤ 5040 hoán vị khi k = 8.

## Cấu trúc dự án

| File | Vai trò |
|---|---|
| `thuvien.h` | Khai báo thư viện, biến toàn cục (`R`, `C`, `bandokho`, `buoc`, `hangdoi`) và nguyên mẫu các hàm |
| `caidat.cpp` | Cài đặt các hàm: `kiemtratoado`, `kiemtralaso`, `them`, `loang`, `timhoanvi`, `timduongnhonhat` |
| `chuongtrinh.cpp` | Hàm `main`: đọc dữ liệu, xử lý từng truy vấn và in kết quả |

### Các hàm chính

| Hàm | Chức năng |
|---|---|
| `kiemtratoado(r, c)` | Kiểm tra ô nằm trong kho và không phải vật cản |
| `kiemtralaso(noidung)` | Kiểm tra một chuỗi chỉ gồm chữ số 0–9 |
| `them(r, c, b)` | Nếu ô hợp lệ và chưa thăm thì ghi `b` bước và đưa vào hàng đợi |
| `loang(r0, c0)` | BFS từ ô `(r0, c0)`, tính số bước đến mọi ô |
| `timhoanvi(...)` | Đệ quy thử mọi thứ tự ghé thăm các điểm |
| `timduongnhonhat(k, R[], C[])` | Trả về tổng số bước ít nhất của một truy vấn, hoặc `-1` |

## Biên dịch và chạy

Mã nguồn dùng biến `inline` ở `thuvien.h`, nên cần chuẩn **C++17** trở lên.

**g++ (Linux / macOS / MinGW):**

```bash
g++ -std=c++17 -O2 chuongtrinh.cpp caidat.cpp -o khohang
./khohang < input.txt
```

**Visual Studio:** thêm cả 3 file vào project, vào *Project → Properties → C/C++ → Language → C++ Language Standard* và chọn **ISO C++17**.

> Nếu g++ báo thiếu `INT_MAX`, thêm `#include <climits>` (và `#include <string>`) vào đầu `thuvien.h`.

## Định dạng dữ liệu

**Input**

```
R C
<R dòng bản đồ, mỗi dòng C ký tự '.' hoặc '#'>
Q
k r1 c1 r2 c2 ... rk ck      (lặp lại Q dòng)
```

Hàng và cột đánh số từ 0. Giới hạn: 1 ≤ R, C ≤ 1000; 1 ≤ Q ≤ 10; 2 ≤ k ≤ 8.

**Output:** mỗi truy vấn in một dòng:

- Số bước ít nhất.
- `-1` nếu không thể đi tới hết các điểm.
- `INVALID` nếu k không thuộc [2, 8], tọa độ nằm ngoài kho hoặc rơi vào ô `#`.

## Ví dụ

Input:

```
5 6
......
.##.#.
.#....
.#.###
...#..
7
2 0 0 4 5
2 0 0 0 0
2 4 0 2 2
3 0 0 4 0 0 5
2 1 1 0 0
2 0 0 5 0
4 0 0 2 5 2 3 4 2
```

Output:

```
-1
0
4
13
INVALID
INVALID
11
```

Giải thích:

- Truy vấn 1: ô (4,5) bị vây kín bởi vật cản nên không tới được, kết quả `-1`.
- Truy vấn 4: xe đi (0,0) → (4,0) → (0,5), tổng 4 + 9 = 13 bước.
- Truy vấn 5: ô (1,1) là vật cản, nên `INVALID`.
- Truy vấn 6: hàng 5 nằm ngoài kho (chỉ có hàng 0–4), nên `INVALID`.

## Hướng phát triển

- Dùng `kiemtralaso` để kiểm tra từng giá trị nhập vào theo dòng (loại các giá trị như `-5`, `1e5`, `12abc`).
- In thêm đường đi cụ thể của xe cho mỗi truy vấn.
- Làm tiếp các bài còn lại của đồ án: nhập/xuất kho theo FIFO, xử lý đơn hàng theo mức ưu tiên, tra cứu danh bạ bằng B-Tree.
