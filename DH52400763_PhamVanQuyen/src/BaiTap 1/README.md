BÀI 1: TÌM ĐƯỜNG NGẮN NHẤT TRONG KHO HÀNG

1. Giới thiệu bài toán

Bài toán yêu cầu tìm đường đi ngắn nhất trong một kho hàng được biểu diễn dưới dạng lưới hình chữ nhật gồm R hàng và C cột.

Trong bản đồ:

.: Ô trống, xe có thể đi qua.

#: Ô có vật cản, xe không thể đi qua.

Xe chỉ được di chuyển theo 4 hướng: lên, xuống, trái và phải. Mỗi lần di chuyển sang một ô liền kề được tính là 1 bước.

Chương trình giải quyết hai yêu cầu:

Tìm số bước ngắn nhất giữa hai điểm.

Tìm tổng số bước nhỏ nhất khi xe phải đi qua nhiều điểm lấy hàng theo thứ tự bất kỳ, không cần quay về điểm xuất phát.

2. Ý tưởng thiết kế

Chương trình sử dụng mô hình đồ thị để biểu diễn bản đồ kho hàng.

Mỗi ô trống được xem là một đỉnh của đồ thị. Hai ô trống nằm cạnh nhau theo chiều ngang hoặc chiều dọc được xem là hai đỉnh có cạnh nối với nhau.

Quy trình xử lý:

Bước 1: Đọc dữ liệu

Đọc kích thước bản đồ R và C.

Lưu bản đồ vào cấu trúc dữ liệu.

Đọc số lượng truy vấn Q.

Đọc và kiểm tra dữ liệu của từng truy vấn.

Bước 2: Kiểm tra dữ liệu

Kiểm tra:

Số lượng điểm cần đi qua phải từ 2 đến 8.

Các giá trị đầu vào chỉ chứa chữ số từ 0 đến 9.

Số lượng tọa độ phải chính xác.

Tọa độ phải nằm trong phạm vi bản đồ.

Các điểm phải nằm trên ô trống ..

Nếu dữ liệu không hợp lệ, chương trình in INVALID và tiếp tục xử lý truy vấn tiếp theo.

Bước 3: Tìm khoảng cách

Sử dụng thuật toán BFS để tính khoảng cách ngắn nhất giữa các điểm trong truy vấn.

Bước 4: Tối ưu thứ tự di chuyển

Sử dụng quy hoạch động Bitmask DP để tìm thứ tự đi qua tất cả điểm lấy hàng sao cho tổng số bước nhỏ nhất.

Bước 5: Truy vết và xuất kết quả

Khôi phục đường đi cụ thể bằng BFS và mảng truy vết parent.

Kết quả được xuất thành hai phần:

Phần 1: Số bước ngắn nhất.

Phần 2: Danh sách các tọa độ xe đi qua.

3. Cấu trúc dữ liệu được sử dụng

Cấu trúc dữ liệu

Chức năng

vector<string>

Lưu bản đồ kho hàng.

queue<int>

Lưu các ô cần duyệt trong BFS.

vector<int> dist

Lưu khoảng cách ngắn nhất từ điểm xuất phát đến các ô khác.

vector<int> parent

Lưu ô cha để truy vết đường đi.

vector<vector<int>> dp

Lưu kết quả quy hoạch động Bitmask DP.

vector<vector<int>> parent

Lưu trạng thái trước đó để truy vết thứ tự ghé điểm.

vector<int>

Lưu danh sách các điểm cần đi qua và đường đi cuối cùng.

Lý do lựa chọn

vector<string> phù hợp để lưu bản đồ hai chiều, dễ dàng truy cập từng ô bằng hàng và cột.

queue phù hợp với BFS vì hoạt động theo nguyên tắc FIFO (vào trước, ra trước).

vector<int> giúp lưu khoảng cách và thông tin truy vết với khả năng truy cập nhanh.

vector<vector<int>> phù hợp để lưu bảng quy hoạch động nhiều chiều.

Bitmask giúp biểu diễn tập hợp các điểm đã ghé thăm bằng một số nguyên, tiết kiệm bộ nhớ và thuận tiện cho việc chuyển trạng thái.

Mỗi ô (r, c) được chuyển thành một ID bằng công thức:

ID = r * C + c

Ngược lại:

Hàng: r = ID / C

Cột: c = ID % C

4. Thuật toán được lựa chọn

4.1. Thuật toán BFS (Breadth-First Search)

BFS là thuật toán tìm kiếm theo chiều rộng trên đồ thị.

Trong bài toán này, BFS được sử dụng để tìm khoảng cách ngắn nhất giữa hai ô trong kho.

Nguyên lý hoạt động:

Đưa ô xuất phát vào hàng đợi.

Đánh dấu khoảng cách của ô xuất phát bằng 0.

Lấy một ô ra khỏi hàng đợi.

Kiểm tra 4 ô liền kề.

Nếu ô tiếp theo hợp lệ và chưa được thăm, cập nhật khoảng cách và đưa vào hàng đợi.

Tiếp tục cho đến khi không còn ô nào cần duyệt.

Lý do chọn BFS:

Mỗi bước di chuyển đều có chi phí bằng 1.

BFS đảm bảo tìm được đường đi ngắn nhất trong đồ thị không trọng số.

Cách triển khai đơn giản, dễ kiểm tra và phù hợp với bài toán tìm đường trên lưới.

Độ phức tạp:

O(R * C)

Trong đó R là số hàng và C là số cột của bản đồ.

4.2. Thuật toán Bitmask DP

Khi có nhiều điểm lấy hàng, chỉ sử dụng BFS riêng lẻ không đủ để tìm thứ tự ghé điểm tối ưu.

Vì vậy, chương trình sử dụng Bitmask DP để giải quyết bài toán tối ưu thứ tự di chuyển.

Ý tưởng:

Mỗi điểm lấy hàng được đánh số từ 0 đến k-1.

Sử dụng một số nguyên mask để biểu diễn những điểm đã ghé.

dp[mask][last] lưu tổng số bước nhỏ nhất khi đã ghé các điểm trong mask và hiện đang đứng tại điểm last.

Điểm xuất phát luôn được cố định là điểm số 0.

Khởi tạo:

dp[1][0] = 0

Công thức chuyển trạng thái:

dp[newMask][next] = min(dp[newMask][next], dp[mask][last] + dist[last][next])

Trong đó:

mask: Tập hợp điểm đã ghé.

last: Điểm hiện tại.

next: Điểm tiếp theo chưa ghé.

dist[last][next]: Khoảng cách ngắn nhất giữa hai điểm.

Sau khi duyệt hết các trạng thái, lấy giá trị nhỏ nhất trong các trạng thái đã ghé tất cả điểm.

Lý do chọn Bitmask DP:

Số điểm tối đa chỉ là 8.

Có thể biểu diễn các tập hợp điểm bằng bit.

Tìm được thứ tự ghé điểm tối ưu.

Hiệu quả hơn việc thử tất cả hoán vị một cách trực tiếp khi cần mở rộng bài toán.

Độ phức tạp:

O(2^k * k^2)

Với k là số điểm cần đi qua.

4.3. Thuật toán truy vết đường đi

Sau khi tìm được tổng số bước nhỏ nhất, chương trình sử dụng mảng parent để khôi phục thứ tự các điểm cần ghé.

Sau đó, BFS được sử dụng để tìm đường đi cụ thể giữa từng cặp điểm liên tiếp.

Các đoạn đường được ghép lại thành một đường đi hoàn chỉnh.

Khi ghép hai đoạn đường, chương trình bỏ ô đầu tiên của đoạn tiếp theo để tránh lặp lại tọa độ tại điểm nối.

5. Lý do lựa chọn các thuật toán

Thuật toán

Lý do lựa chọn

BFS

Tìm đường ngắn nhất khi mỗi bước di chuyển có chi phí bằng nhau.

Bitmask DP

Tối ưu thứ tự đi qua nhiều điểm lấy hàng.

Truy vết Parent

Khôi phục đường đi cụ thể để kiểm tra kết quả.

Việc kết hợp BFS và Bitmask DP giúp giải quyết đầy đủ cả yêu cầu tìm đường ngắn nhất và yêu cầu tối ưu thứ tự ghé nhiều điểm.

6. Kết quả chạy bộ test

Sử dụng bộ dữ liệu ví dụ trong đề bài gồm 5 hàng, 6 cột và 7 truy vấn.

Input

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

Output

-1
0
4
13
INVALID
INVALID
11
-
(0,0)
(4,0) (4,1) (4,2) (3,2) (2,2)
(0,0) (1,0) (2,0) (3,0) (4,0) (4,1) (4,2) (3,2) (2,2) (2,3) (2,4) ...
-
-
(0,0) (1,0) (2,0) (3,0) (4,0) (4,1) (4,2) (3,2) (2,2) (2,3) (2,4) ...
