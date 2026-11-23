# Bài 3 – Xử lý đơn hàng theo mức ưu tiên

- **Họ tên:** Huỳnh Thị Như Quỳnh
- **MSSV:** DH52400767

## Mô tả
Chương trình C# xử lý đơn hàng theo mức ưu tiên: đơn có priority lớn hơn được xử lý trước; cùng priority thì đơn đến trước được xử lý trước.

## Cách làm
- Tự cài **min-heap** (priority queue) bằng `List<Order>`.
- Mỗi đơn lưu `Id`, `Priority` và `Seq` (số thứ tự đến) để phân xử khi trùng priority.
- Dùng `HashSet` lưu mọi mã đơn từng được thêm để phát hiện `DUPLICATE`.
- Độ phức tạp: **O(Q log Q)**.

## Lệnh hỗ trợ
| Lệnh | Kết quả |
|---|---|
| `ORDER id priority` | `OK` / `DUPLICATE` / `INVALID` |
| `NEXT` | `<id> <priority>` hoặc `EMPTY` |
| `PEEK` | `<id> <priority>` hoặc `EMPTY` |
| `SIZE` | số đơn đang chờ |

Lệnh sai tên, sai số tham số, priority không hợp lệ (ngoài 1..10^9) hoặc mã dài hơn 20 ký tự → `INVALID`.

## Cách chạy
1. Biên dịch và chạy `Program.cs` trong Visual Studio (hoặc `csc Program.cs`).
2. Nhập dữ liệu từ bàn phím hoặc chuyển hướng từ file.
3. So sánh kết quả với phần **OUTPUT MONG DOI** trong `test.txt`.
