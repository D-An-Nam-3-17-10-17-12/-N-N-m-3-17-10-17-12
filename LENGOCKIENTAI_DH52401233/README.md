
Bài 1 – Tìm đường ngắn nhất trong kho hàng

1. Giới thiệu

Chương trình tìm đường đi ngắn nhất trong bản đồ kho hàng kết hợp quản lý đơn hàng theo mức độ ưu tiên, sử dụng thuật toán tìm kiếm theo chiều rộng (BFS) để tìm đường đi từ cổng xuất phát (0, 0) đến vị trí lưu kho của đơn hàng ưu tiên nhất sao cho tổng số bước di chuyển là nhỏ nhất.
2. Công nghệ sử dụng

Ngôn ngữ lập trình: C#

Môi trường chạy: Visual Studio 2022 / 2026 (.NET Framework / Windows Forms App)

Thư viện chính:

using System;

using System.Collections.Generic;

using System.Linq;

using System.Text;

using System.Threading.Tasks;

using System.Windows.Forms;
3. Cách chạy chương trình

1/ Mở Visual Studio.

2/ Tạo dự án Windows Forms App (.NET Framework) hoặc mở dự án Baitaptuan1.

3/ Thêm các file Kho.cs, COrder.cs, và Form1.cs vào dự án.

4/ Xây dựng giao diện Form gồm các nút bấm (btn_Order, btn_TIM, btn_Next, btn_Peek, btn_Size, btn_Thoat), ô nhập liệu (txt_id, txt_Priority, txt_ROW, txt_COLUMN), ô xuất thông báo (txt_output) và bảng dgv_List.

5/ Nhấn F5 hoặc Ctrl + F5 để chạy chương trình.
4. Định dạng dữ liệu đầu vào

Người dùng nhập dữ liệu trực tiếp trên giao diện Windows Forms:

Mã đơn hàng (txt_id): Chuỗi không rỗng, độ dài tối đa 20 ký tự (không được trùng lặp).

Độ ưu tiên (txt_Priority): Số nguyên long >= 1 (số lớn hơn thể hiện độ ưu tiên cao hơn).

Vị trí Hàng (txt_ROW): Số nguyên int >= 0 đại diện cho tọa độ dòng trong kho.

Vị trí Cột (txt_COLUMN): Số nguyên int >= 0 đại diện cho tọa độ cột trong kho.

Kích thước bản đồ kho: Mặc định khởi tạo 10 x 10 lối đi (từ ô (0,0) đến (9,9)).
5. BFS (Breadth-First Search): Tìm đường đi ngắn nhất trên bản đồ lưới 2D từ vị trí cổng xuất phát (0, 0) đến vị trí kệ chứa đơn hàng (Row, Col) 
6. Kết quả đầu ra

Khi nhấn nút Tìm đường (btn_TIM): In ra tổng số bước di chuyển và chi tiết lộ trình từng bước: (0,0) -> (0,1) -> ... -> (Row,Col).

In ra thông báo lỗi nếu vị trí đơn hàng vượt quá phạm vi bản đồ kho.

Bài 2 – Nhập/xuất kho theo FIFO

1. Giới thiệu

Chương trình quản lý hoạt động nhập kho và xuất kho  theo nguyên tắc FIFO (First In, First Out - Hàng vào trước, xuất trước). Sử dụng cấu trúc dữ liệu hàng đợi (Queue) để đảm bảo các sản phẩm được nhập vào kho trước sẽ luôn được ưu tiên xuất kho trước, giúp tối ưu hóa việc quản lý tồn kho và tránh quá hạn hàng hóa.
2. Công nghệ sử dụng

Ngôn ngữ lập trình: C#

Môi trường chạy: Visual Studio 2022 / 2026 (.NET Framework / Windows Forms App)

Thư viện chính:

using System;

using System.Collections.Generic;

using System.Linq;

using System.Text;

using System.Threading.Tasks;

using System.Windows.Forms;
3. Cách chạy chương trình

1/ Mở Visual Studio.

2/ Tạo dự án Windows Forms App (.NET Framework) hoặc mở dự án Baitaptuan1.

3/ Thêm các file lớp quản lý sản phẩm (ví dụ: CProduct.cs / CItem.cs) và giao diện Form2.cs (hoặc tích hợp vào Form1.cs).

4/ Xây dựng giao diện Form gồm các nút bấm nhập kho (btn_NhapKho), xuất kho (btn_XuatKho), xem lô hàng đầu (btn_XemDauQueue), ô nhập thông tin lô hàng (txt_MaLo, txt_TenSanPham,   txt_SoLuong), ô xuất thông báo (txt_output) và danh sách hiển thị hàng đợi (dgv_FIFOList / listBox_FIFO).

5/ Nhấn F5 hoặc Ctrl + F5 để chạy chương trình.
4. Định dạng dữ liệu đầu vào

Người dùng nhập dữ liệu trực tiếp trên giao diện Windows Forms:

Mã  Sản phẩm: Chuỗi ký tự không rỗng, không được trùng với các sản phẩm đang có trong hàng đợi.

5. Thuật toán

Cấu trúc dữ liệu Queue (FIFO):

Nhập kho (Enqueue): Thêm sản phẩm mới vào cuối hàng đợi.

Xuất kho (Dequeue): Lấy và xóa sản phẩm ở đầu hàng đợi ra khỏi kho .

Xem sản phẩm vào sớm nhất  (Peek): Kiểm tra thông tin sản phẩm sắp được xuất tiếp theo mà không xóa khỏi hàng đợi.

Kiểm tra dữ liệu đầu vào (kiểu số nguyên ).

Kiểm tra hàng đợi rỗng trước khi thực hiện thao tác xuất kho.

Kiểm tra mã sản phẩm trùng lặp hoặc số lượng không hợp lệ.
6. Kết quả đầu ra

Danh sách hiển thị hàng đợi: Hiển thị thứ tự các sản phẩm đang chờ xuất kho theo đúng trình tự thời gian nhập.

Khung thông báo (txt_output):

Thông báo nhập kho thành công: "Đã nhập kho sản phẩm: [Mã lô] [ thứ tự ]".

Thông báo xuất kho thành công: "Đã xuất kho sản phẩm: [Mã lô] (Hàng nhập trước nhất)".

Thông báo lỗi hoặc cảnh báo khi xuất kho lúc kho rỗng: 

Bài 3 – Xử lý đơn hàng theo mức ưu tiên

1. Giới thiệu

Chương trình quản lý và xử lý danh sách đơn hàng dựa trên mức độ ưu tiên (Priority ). Hệ thống cho phép tiếp nhận các đơn hàng mới, tự động sắp xếp đơn hàng có độ ưu tiên cao nhất lên đầu danh sách để xử lý trước. Trong trường hợp các đơn hàng có cùng mức độ ưu tiên, hệ thống sẽ căn cứ vào số thứ tự đến  để xử lý đơn hàng đến trước theo đúng nguyên tắc .

2. Công nghệ sử dụng

Ngôn ngữ lập trình: C#

Môi trường chạy: Visual Studio 2022 / 2026 (.NET Framework / Windows Forms App)

Thư viện chính:

using System;

using System.Collections.Generic;

using System.Linq;

using System.Text;

using System.Threading.Tasks;

using System.Windows.Forms;

3. Cách chạy chương trình

1/ Mở Visual Studio.

2/ Tạo dự án Windows Forms App (.NET Framework) hoặc mở dự án Baitaptuan1.

3/ Thêm các file COrder.cs và Form1.cs vào dự án.

4/ Thiết kế giao diện Form gồm:

 +Các ô nhập dữ liệu: Mã đơn (txt_id), Độ ưu tiên (txt_Priority).

 +Các nút chức năng: Thêm đơn (btn_Order), Xử lý đơn tiếp theo (btn_Next), Xem đơn đầu (btn_Peek), Đếm số đơn (btn_Size), Thoát (btn_Thoat).

 +Bảng hiển thị danh sách đơn hàng (dgv_List) và ô xuất thông báo (txt_output).

5/ Nhấn F5 hoặc Ctrl + F5 để chạy chương trình.

4. Định dạng dữ liệu đầu vào

Người dùng nhập dữ liệu trực tiếp trên giao diện Windows Forms:

Mã đơn hàng (txt_id): Chuỗi ký tự không rỗng, độ dài tối đa 20 ký tự (duy nhất, không trùng lặp).

Độ ưu tiên (txt_Priority): Số nguyên long >= 1 (giá trị càng lớn thể hiện mức độ ưu tiên càng cao).

Số thứ tự đến (iSNumber): Tự động tăng (Num++) mỗi khi thêm một đơn hàng mới vào hệ thống.

5. Thuật toánThuật toán so sánh & sắp xếp ưu tiên (KiemtraPriority): So sánh Priority giữa các đơn hàng. Đơn nào có Priority lớn hơn sẽ được xếp lên trước.Thứ tự đến: Nếu 2 đơn có Priority bằng nhau, so sánh iSNumber. Đơn nào đến trước  sẽ được xếp lên trước.Tập hợp quản lý dữ liệu:List<COrder>: Lưu trữ danh sách các đơn hàng và thực hiện sắp xếp lại bằng hàm Sort() sau mỗi thao tác.HashSet<string>: Kiểm tra độ trùng lặp của mã đơn hàng (Id).Kiểm tra dữ liệu đầu vào (kiểu số nguyên): Bắt lỗi nhập chuỗi/số không hợp lệ, mã đơn đã tồn tại hoặc độ ưu tiên $< 1$.

6. Kết quả đầu ra

Bảng danh sách (dgv_List): Tự động cập nhật và hiển thị danh sách đơn hàng theo đúng thứ tự ưu tiên từ cao xuống thấp.

Khung thông báo (txt_output):

Hiển thị "OK" khi thêm đơn hàng thành công hoặc báo lỗi "Đã tồn tại", " Không hợp lệ ".

Hiển thị thông tin đơn hàng được xử lý khi bấm nút Next: [Mã đơn] [Độ ưu tiên].

Thông báo " Rỗng " nếu danh sách đơn hàng đang trống khi thực hiện thao tác xem hoặc xử lý.