# Bài 2 – Nhập/xuất kho theo FIFO

## Giới thiệu

Chương trình mô phỏng chức năng nhập/xuất kho theo nguyên tắc **FIFO** (First In – First Out): hàng được nhập theo từng lô, khi xuất thì lấy từ lô nhập sớm nhất trước; nếu lô đầu không đủ thì lấy tiếp sang lô kế tiếp.

Chương trình đọc dữ liệu từ bàn phím (stdin) và in kết quả ra màn hình (stdout), mỗi lệnh in đúng một dòng.

## Cấu trúc dữ liệu

| Cấu trúc | Kiểu (C++) | Vai trò |
| --- | --- | --- |
| Hàng đợi lô theo SKU | `unordered_map<string, queue<pair<string, long long>>>` | Mỗi SKU có một Queue các lô (mã lô, số lượng còn lại). Lô nhập sớm nhất nằm ở đầu hàng đợi. |
| Tổng tồn kho | `unordered_map<string, long long>` | Lưu tổng số lượng còn lại của từng SKU để trả lời `STOCK` và kiểm tra `NOT_ENOUGH` ngay lập tức. |
| Mã lô đã dùng | `unordered_set<string>` | Lưu mọi mã lô đã từng nhập, **không bao giờ xóa** (kể cả khi lô đã xuất hết) để phát hiện `DUPLICATE_LOT`. |

**Lý do chọn:**

- Queue phù hợp tự nhiên với FIFO: thêm vào cuối, lấy ra từ đầu.
- HashMap giúp tìm Queue của một SKU trong thời gian trung bình O(1), cần thiết khi có đến 10^5 lệnh.
- Tách riêng tập mã lô đã dùng khỏi Queue, vì một lô xuất hết sẽ bị xóa khỏi Queue nhưng mã của nó vẫn không được dùng lại.

## Cách hoạt động

- `IMPORT sku lot qty`: nếu `lot` đã có trong tập mã lô thì in `DUPLICATE_LOT`. Ngược lại thêm `lot` vào tập mã lô, đẩy `(lot, qty)` vào Queue của `sku`, cộng `qty` vào tổng tồn kho và in `OK`.
- `EXPORT sku qty`: nếu tổng tồn kho nhỏ hơn `qty` thì in `NOT_ENOUGH <tồn kho>` và không xuất gì. Ngược lại lấy lần lượt từ lô đầu hàng đợi: lô nào bị lấy hết thì bỏ khỏi Queue, lô bị lấy một phần thì giảm số lượng còn lại. In các lô đã lấy dạng `lot:số_lượng`, cách nhau dấu cách.
- `STOCK sku`: in tổng tồn kho của `sku` (SKU chưa có thì in `0`).

## Kiểm tra dữ liệu sai

Một dòng lệnh bị coi là `INVALID` (chương trình vẫn xử lý tiếp dòng sau) khi:

- dòng rỗng, hoặc sai tên lệnh (tên lệnh phân biệt chữ hoa/thường, ví dụ `import` là sai);
- sai số lượng tham số (`IMPORT` cần 3 tham số, `EXPORT` cần 2, `STOCK` cần 1);
- `sku` hoặc `lot` dài hơn 20 ký tự;
- `qty` không hợp lệ: chứa ký tự không phải chữ số (ví dụ `-10`, `1e5`, `12abc`), hoặc nằm ngoài khoảng từ 1 đến 10^9.

## Độ phức tạp

Mỗi lệnh `IMPORT` và `STOCK` tốn O(1) trung bình. Lệnh `EXPORT` tốn O(số lô bị lấy hết + 1), và mỗi lô chỉ bị lấy hết đúng một lần trong toàn bộ chương trình, nên tổng thời gian cho Q lệnh là O(Q). Tổng tồn kho dùng `long long` để tránh tràn số.

## Cấu trúc thư mục

```
MSSV_HO_TEN/
└─ src/
   └─ BT2/
      ├─ README.md
      ├─ solution.cpp
      └─ tests/        <- các file test tự viết
```

## Hướng dẫn biên dịch và chạy

**Cách 1: dòng lệnh (g++, chuẩn C++17):**

```
g++ -std=c++17 -O2 solution.cpp -o solution
```

**Cách 2: Visual Studio:** tạo Console App C++, thêm `solution.cpp` vào project rồi chọn Build Solution.

**Chạy:**

```
solution < input.txt
```

hoặc chạy `solution` rồi gõ trực tiếp từ bàn phím.

## Ví dụ

Input:

```
10
IMPORT MILK L01 40
IMPORT MILK L02 30
IMPORT EGG E01 500
EXPORT MILK 50
STOCK MILK
EXPORT MILK 30
IMPORT MILK L01 5
EXPORT EGG -10
SELL EGG 1
STOCK BREAD
```

Output:

```
OK
OK
OK
L01:40 L02:10
20
NOT_ENOUGH 20
DUPLICATE_LOT
INVALID
INVALID
0
```

## Kết quả chạy bộ test

Các file trong thư mục `tests/` kiểm tra:

- dữ liệu sai: thiếu/thừa tham số, `qty` bằng 0, `1e5`, `12abc`, mã dài hơn 20 ký tự, lệnh viết thường, dòng rỗng, số quá lớn;
- xuất qua nhiều lô, lô xuất hết vẫn không được nhập lại mã (`DUPLICATE_LOT`), xuất khi kho hết (`NOT_ENOUGH 0`);
- kiểm tra tốc độ: file 100.000 lệnh chạy khoảng 1,5 giây ở cấu hình Debug (đo bằng `Measure-Command`, đã gồm thời gian đọc file).

## Giới hạn còn tồn tại

- Đề không nói rõ cách xử lý khi số dòng lệnh thực tế ít hơn Q đã khai báo. Chương trình hiện coi các dòng thiếu là dòng rỗng và in `INVALID`.
- Tên lệnh được so khớp chính xác theo chữ hoa; chương trình không tự chuyển chữ thường thành chữ hoa.