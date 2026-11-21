1. Giới thiệu

Chương trình mô phỏng hệ thống quản lý nhập và xuất hàng trong kho theo nguyên tắc FIFO (First In - First Out), viết bằng C++.

- Hàng hóa được nhập theo từng lô.
- Khi xuất hàng, kho lấy từ lô được nhập sớm nhất còn tồn.
- Nếu một lô không đủ số lượng cần xuất thì tiếp tục lấy từ lô kế tiếp.
- Mỗi mặt hàng (SKU) có thể có nhiều lô hàng khác nhau.
- Mã lô không được trùng trong toàn kho.

2. Thuật toán

- Queue: lưu danh sách các lô hàng của từng SKU theo đúng thứ tự nhập kho.
- HashMap (unordered_map): tìm nhanh thông tin (hàng đợi và tổng tồn kho) của mỗi SKU.
- HashSet (unordered_set): lưu các mã lô đã dùng để phát hiện trùng mã lô.
- Khi IMPORT: nếu mã lô đã dùng thì báo DUPLICATE_LOT, ngược lại thêm lô mới vào cuối Queue và cộng vào tổng tồn kho.
- Khi EXPORT: nếu tồn kho không đủ thì in NOT_ENOUGH kèm số tồn và không xuất gì. Nếu đủ thì lấy hàng từ đầu Queue theo nguyên tắc FIFO, lô nào lấy hết thì bỏ khỏi Queue, lô bị lấy dở thì giữ lại phần còn lại.
- Khi STOCK: trả về tổng số lượng tồn kho hiện tại của SKU (chưa có thì in 0).
- Dùng kiểu long long cho số lượng vì tổng tồn kho có thể vượt giới hạn của int.

3. Input / Output

Input:
- Dòng 1: Q (1 ≤ Q ≤ 10^5) là số lệnh.
- Q dòng tiếp theo, mỗi dòng là một lệnh.
- sku và lot dài tối đa 20 ký tự, qty là số nguyên từ 1 đến 10^9.

Các lệnh và kết quả:
- IMPORT sku lot qty: in OK, hoặc DUPLICATE_LOT nếu mã lô đã dùng.
- EXPORT sku qty: in các lô đã lấy dạng lot:số_lượng cách nhau dấu cách, hoặc NOT_ENOUGH <tồn kho>.
- STOCK sku: in số lượng còn lại.
- Lệnh sai tên, sai số tham số, qty không hợp lệ hoặc mã dài quá 20 ký tự: in INVALID.

