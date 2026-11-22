#Bài 2 - Nhập/xuất kho theo FIFO

Sinh viên: Huỳnh Thị Như Quỳnh 
MSSV: DH52400767

Hàng được nhập theo từng lô. Khi xuất, kho lấy hàng từ lô nhập sớm nhất trước (First In - First Out); nếu lô đầu không đủ thì lấy tiếp sang lô kế tiếp.

Chương trình xử lý 3 lệnh:

- IMPORT sku lot qty: nhập một lô hàng.
- EXPORT sku qty: xuất hàng theo FIFO.
- STOCK sku: xem tồn kho của một mã hàng.

Thuật toán và cấu trúc dữ liệu:

- Mỗi mã hàng (SKU) có một hàng đợi (Queue<Lot>) chứa các lô theo thứ tự nhập, lô nhập sớm nhất nằm ở đầu hàng đợi.
- Dictionary<string, Queue<Lot>> giúp tìm nhanh hàng đợi của từng SKU.
- Dictionary<string, long> lưu tổng tồn kho của từng SKU, để biết ngay có đủ hàng để xuất hay không.
- HashSet<string> lưu các mã lô đã dùng, để phát hiện mã lô trùng trong toàn kho.
- Khi xuất: nếu tồn kho không đủ thì in NOT_ENOUGH <tồn kho> và không xuất gì. Nếu đủ thì lấy lần lượt từ lô đầu, lô nào lấy hết thì bỏ khỏi hàng đợi, lô cuối bị lấy dở thì giữ lại với số lượng còn lại.
- Dùng kiểu 'long' cho số lượng vì tổng tồn kho có thể vượt giới hạn của 'int'.
- Mỗi lệnh chạy trong thời gian gần như hằng số (trừ phần duyệt các lô được lấy khi xuất).

Input

- Dòng 1: 'Q' (1 ≤ Q ≤ 10^5) là số lệnh.
- Q dòng tiếp theo, mỗi dòng là một lệnh.
- 'sku' và 'lot' dài tối đa 20 ký tự, 'qty' là số nguyên từ 1 đến 10^9. Mã lô không được trùng trong toàn kho.

Output

Mỗi lệnh in ra một dòng:
- 'IMPORT': 'OK', hoặc 'DUPLICATE_LOT' nếu mã lô đã dùng.
- 'EXPORT': các lô đã lấy dạng 'lot:số_lượng' cách nhau dấu cách, hoặc 'NOT_ENOUGH <tồn kho>' (không xuất gì).
- 'STOCK': số lượng còn lại (SKU chưa có thì in '0').
- Lệnh sai tên, sai số tham số, 'qty' không hợp lệ hoặc mã dài quá 20 ký tự: 'INVALID'.

Cấu trúc chương trình :
- 'Lot': lớp lưu một lô hàng gồm mã lô và số lượng còn lại.
- 'XuLy()': phân tích một dòng lệnh, kiểm tra hợp lệ và thực hiện lệnh, trả về chuỗi kết quả.
- 'DocQty()': kiểm tra 'qty' hợp lệ (chỉ gồm chữ số, từ 1 đến 10^9).
- 'MaHopLe()': kiểm tra độ dài mã SKU hoặc mã lô (1 đến 20 ký tự).
- 'LayTon()': lấy tồn kho của một SKU (chưa có thì là 0).
- 'Main()': đọc Q và các dòng lệnh, gom kết quả rồi in ra một lần.
