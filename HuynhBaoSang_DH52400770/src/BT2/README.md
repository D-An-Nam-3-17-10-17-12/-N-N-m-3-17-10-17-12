Bài 2 - Nhập/xuất kho theo FIFO



1\. Giới thiệu

Chương trình mô phỏng hệ thống quản lý nhập và xuất hàng trong kho theo nguyên tắc FIFO (First In - First Out).

\- Hàng hóa được nhập theo từng lô.

\- Khi xuất hàng, kho sẽ lấy từ lô được nhập sớm nhất còn tồn.

\- Nếu một lô không đủ số lượng cần xuất thì tiếp tục lấy từ lô kế tiếp.

\- Mỗi mặt hàng (SKU) có thể có nhiều lô hàng khác nhau.



2\. Thuật toán

\- Queue: lưu danh sách các lô hàng của từng SKU theo đúng thứ tự nhập kho.

\- HashMap (unordered\_map): dùng để tìm nhanh thông tin của mỗi SKU.

\- Khi IMPORT, thêm lô mới vào cuối Queue.

\- Khi EXPORT, lấy hàng từ đầu Queue theo nguyên tắc FIFO cho đến khi đủ số lượng yêu cầu hoặc hết hàng.

\- Khi STOCK, trả về tổng số lượng tồn kho hiện tại của SKU.



3\. Input

Phần 1:

\- Q (1 ≤ Q ≤ 10^5): số lượng lệnh.

Phần 2:

\- Q dòng lệnh, mỗi dòng thuộc 1 trong 3 dạng:

IMPORT sku lot qty

\- Nhập một lô hàng mới.

EXPORT sku qty

\- Xuất hàng theo nguyên tắc FIFO.

STOCK sku

\- Kiểm tra số lượng tồn kho.

Điều kiện:

\- sku và lot có độ dài tối đa 20 ký tự.

\- qty là số nguyên từ 1 đến 10^9.

\- Mã lô (lot) không được trùng trong toàn bộ kho.



4\. Output

IMPORT:

\- OK: nhập thành công.

\- DUPLICATE\_LOT: mã lô đã tồn tại.

EXPORT:

\- In danh sách các lô đã xuất theo dạng:

&#x20; lot:số\_lượng

\- Nếu không đủ hàng:

&#x20; NOT\_ENOUGH <tồn\_kho>

STOCK:

\- In số lượng hàng còn lại của SKU.

\- Nếu SKU chưa tồn tại thì in 0.

Lỗi dữ liệu:

\- INVALID nếu tên lệnh sai, sai số tham số, mã quá 20 ký tự hoặc qty không hợp lệ.



5\. Cấu trúc chương trình

\- Ngôn ngữ lập trình: C++.

\- laSoHopLe(): kiểm tra chuỗi có phải số nguyên dương hay không.

\- laQtyHopLe(): kiểm tra số lượng hợp lệ.

\- laMaHopLe(): kiểm tra mã SKU hoặc mã lô hợp lệ.

\- tachTu(): tách các thành phần của lệnh nhập vào.

\- xuLyImport(): xử lý nhập hàng vào kho.

\- xuLyExport(): xử lý xuất hàng theo nguyên tắc FIFO.

\- xuLyStock(): kiểm tra số lượng tồn kho của SKU.

\- unordered\_map khoHang: lưu thông tin các SKU trong kho, bao gồm Queue các lô hàng và tổng số lượng tồn kho.

\- unordered\_set maLoDaDung: lưu các mã lô đã tồn tại để tránh trùng lặp.

\- Queue: lưu các lô hàng theo thứ tự nhập kho.

