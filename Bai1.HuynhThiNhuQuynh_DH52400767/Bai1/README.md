Bài 1 - Tìm đường ngắn nhất trong kho hàng
Sinh viên: Huỳnh Thị Như Quỳnh 
MSSV : DH52400767
1. Giới thiệu
Kho hàng là lưới R × C, ô `.` là lối đi, ô `#` là vật cản. Xe đi lên, xuống, trái, phải sang ô kề.
- Tìm đường ngắn nhất giữa 2 điểm.
- Mở rộng: xuất phát từ một điểm, đi qua nhiều điểm lấy hàng (thứ tự tùy ý), tìm tổng số bước ít nhất, không cần quay về.
2. Thuật toán
- BFS: tìm đường ngắn nhất giữa 2 điểm, cài bằng hàng đợi dạng mảng (không đệ quy). Bản đồ lưu bằng `char[][]`, mỗi ô `(r, c)` được đánh số `r * C + c`.
- Quy hoạch động bitmask: chạy BFS từ từng điểm để lập ma trận khoảng cách, sau đó chọn thứ tự đi qua các điểm sao cho tổng số bước ít nhất.
3. Input
- Dòng 1: R C (1 ≤ R, C ≤ 1000), tiếp theo là R dòng bản đồ (`.` hoặc `#`).
- Dòng tiếp: Q (1 ≤ Q ≤ 10) là số truy vấn.
- Mỗi truy vấn: [k r1 c1 ... rk ck] (2 ≤ k ≤ 8). Điểm đầu là vị trí xe, các điểm còn lại là điểm lấy hàng. Hàng, cột đánh số từ 0.
4. Output
- Phần 1: mỗi truy vấn một dòng là số bước ít nhất, hoặc `-1` (không đi hết được), hoặc `INVALID` (truy vấn sai).
- Phần 2: mỗi truy vấn một dòng liệt kê ô xuất phát và tối đa 10 ô đầu tiên dạng `(dòng,cột)`, thêm `...` nếu dài hơn 10 bước. Truy vấn `-1` hoặc `INVALID` thì in `-`.
5. Cấu trúc chương trình
- Ngôn ngữ: C# (Visual Studio 2022)
- BFS(): tìm khoảng cách ngắn nhất từ một điểm, lưu ô cha để truy vết.
- TruyVan(): đọc và kiểm tra truy vấn.
- Giai(): BFS + quy hoạch động bitmask, truy vết thứ tự ghé các điểm.
- taoDuongDi(): tạo chuỗi đường đi tối đa 10 ô đầu.
- Main(): đọc dữ liệu, xử lý từng truy vấn, in Phần 1 rồi Phần 2.
