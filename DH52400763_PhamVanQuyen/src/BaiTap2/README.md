Bài 2 – Nhập/xuất kho theo FIFO
1. Mô tả bài toán
Chương trình quản lý các lô hàng theo từng mã hàng (sku):
- IMPORT sku lot qty: nhập một lô hàng. Mỗi mã lô (lot) chỉ được sử dụng một lần trong toàn kho.
- EXPORT sku qty: xuất hàng theo nguyên tắc FIFO (lô nhập trước được xuất trước).
- STOCK sku: xem tổng số lượng còn trong kho của một SKU.
Mỗi lệnh được đọc trên một dòng và tạo đúng một dòng kết quả. Nếu lệnh sai cú pháp, sai số tham số, số lượng không hợp lệ hoặc mã SKU/mã lô dài hơn 20 ký tự, chương trình in INVALID và tiếp tục xử lý dòng sau.
2. Ý tưởng thiết kế
Sử dụng hai cấu trúc dữ liệu chính:
1. Hash map (unordered_map): ánh xạ mỗi sku tới thông tin kho của SKU đó. Nhờ vậy, việc tìm kho của một SKU thường có thời gian trung bình O(1).
2. Queue (deque) cho từng SKU: lưu các lô theo thứ tự nhập. Mỗi phần tử gồm mã lô và số lượng còn lại. Lô ở đầu hàng đợi luôn là lô được nhập sớm nhất.
Ngoài ra, sử dụng một hash set (unordered_set) toàn cục để ghi nhận tất cả mã lô đã từng được nhập. Tập hợp này không xóa mã lô khi lô đã xuất hết, vì mã lô không được phép sử dụng lại trong toàn kho.

Mỗi SKU cũng lưu biến total là tổng tồn kho hiện tại để truy vấn STOCK nhanh mà không cần duyệt qua các lô.
3. Thuật toán xử lý
IMPORT
1. Kiểm tra số lượng là chuỗi chỉ gồm chữ số và nằm trong phạm vi cho phép.
2. Kiểm tra độ dài SKU và mã lô không vượt quá 20 ký tự.
3. Nếu mã lô đã xuất hiện trong tập mã lô, in DUPLICATE_LOT.
4. Nếu hợp lệ, thêm {lot, qty} vào cuối queue của SKU, cập nhật tổng tồn kho và in OK.
EXPORT
1. Kiểm tra cú pháp và số lượng.
2. Tìm tổng tồn kho của SKU.
3. Nếu tồn kho nhỏ hơn số lượng cần xuất, in NOT_ENOUGH <tồn kho> và không thay đổi dữ liệu.
4. Nếu đủ hàng, lấy lần lượt từ đầu queue:
   - Nếu lô đầu còn ít hơn hoặc bằng lượng cần lấy, lấy hết lô đó và loại lô khỏi queue.
   - Nếu lô đầu còn nhiều hơn lượng cần lấy, chỉ giảm số lượng của lô đó.
5. In các lô đã lấy theo định dạng lot:số_lượng, cách nhau một dấu cách; cập nhật tổng tồn kho.
STOCK
- Nếu SKU chưa tồn tại, in 0.
- Nếu đã tồn tại, in biến tổng tồn kho của SKU.
4. Cấu trúc dữ liệu được chọn và lý do
Cấu trúc	Công dụng	Lý do
unordered_map<string, Inventory>	Tìm thông tin theo SKU	Tra cứu trung bình O(1)
deque<Lot>	Lưu các lô của một SKU theo thứ tự nhập	Thêm cuối, xem/xóa đầu hiệu quả
unordered_set<string>	Kiểm tra mã lô đã từng được dùng	Kiểm tra trùng trung bình O(1)
long long total	Lưu tổng tồn kho của SKU	Truy vấn tồn kho không cần duyệt queue


deque được dùng như một queue FIFO: chỉ thêm lô ở cuối và xuất từ đầu. Không cần sắp xếp các lô vì thứ tự nhập đã chính là thứ tự FIFO.
5. Ưu điểm và nhược điểm
Ưu điểm
- Đúng nguyên tắc FIFO: lô nhập trước luôn được xuất trước.
- Tra cứu SKU và kiểm tra mã lô trùng nhanh trong trường hợp trung bình.
- STOCK nhanh vì tổng tồn kho được cập nhật ngay sau mỗi lần nhập/xuất.
- Khi không đủ hàng, chương trình không thay đổi bất kỳ lô nào.
- Xử lý từng dòng độc lập; lệnh sai in INVALID và chương trình tiếp tục.
- Không cần sắp xếp dữ liệu sau khi nhập.
Nhược điểm
- unordered_map và unordered_set không đảm bảo O(1) trong trường hợp xấu nhất.
- Cần thêm bộ nhớ để lưu tập mã lô đã từng sử dụng, kể cả các lô đã xuất hết.
- Nếu cần xem hoặc truy vấn theo thứ tự SKU/mã lô, cấu trúc hash không tự duy trì thứ tự.
