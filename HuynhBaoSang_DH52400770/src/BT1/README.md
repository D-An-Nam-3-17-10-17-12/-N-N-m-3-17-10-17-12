Bài 1- Tìm đường ngắn nhất trong kho hàng



1. Giới thiệu

\- Chương trình này giải quyết bài toán tìm đường đi ngắn nhất trong kho hàng được mô hình hóa dưới dạng lưới R × C:

&#x20; - Ô “.”: lối đi.

&#x20; - Ô “#”: vật cản (tường, cột).

&#x20; - Xe di chuyển lên, xuống, trái, phải sang ô kề.

\- Nhiệm vụ:

&#x20; - Tìm đường ngắn nhất giữa 2 điểm.

&#x20; - Mở rộng: xe xuất phát từ một điểm và phải đi qua nhiều điểm lấy hàng (thứ tự tùy ý), tìm tổng số bước ít nhất. Không cần quay về điểm xuất phát.



2.Thuật toán

\- BFS: dùng để tìm đường đi ngắn nhất trên lưới giữa 2 điểm bất kỳ.

\- Quy hoạch động bitmask (TSP nhỏ): dùng để chọn thứ tự đi qua nhiều điểm lấy hàng sao cho tổng số bước ít nhất.



3\. Input

Phần 1: R C (1 ≤ R, C ≤ 1000).

&#x20; - R dòng tiếp theo: bản đồ kho (. hoặc #).

Phần 2: Q (1 ≤ Q ≤ 10) số truy vấn.

&#x20; - Mỗi truy vấn: k r1 c1 r2 c2 ... rk ck

&#x20;   - k = số điểm (2 ≤ k ≤ 8).

&#x20;   - Điểm đầu tiên: vị trí xe.

&#x20;   - Các điểm còn lại: vị trí lấy hàng.



4\. Output

Phần 1: Số bước

&#x20; - Mỗi truy vấn 1 dòng: Số bước ít nhất, hoặc -1, hoặc INVALID.

Phần 2: Bước di chuyển

&#x20; - Mỗi truy vấn 1 dòng: liệt kê liệt kê ô xuất phát và tối đa 10 ô đầu tiên xe đi qua.

&#x20; - Nếu đường dài hơn 10 bước thì thêm “...”.

&#x20; - Nếu kết quả là -1 hoặc INVALID thì in “-”.



5\. Cấu trúc chương trình

\- Ngôn ngữ lập trình: C++

\- bfs(): tìm đường ngắn nhất từ một điểm.

\- docBanDo(): đọc dữ liệu bản đồ.

\- docTruyVan(): đọc và kiểm tra truy vấn.

\- giaiTruyVan(): giải bài toán nhiều điểm bằng BFS + hoán vị.

\- ghiDuongDi(): in ra tối đa 10 bước đầu tiên.

\- inKetQua(): xuất kết quả.

