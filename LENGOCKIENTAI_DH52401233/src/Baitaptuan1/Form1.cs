using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Baitaptuan1
{
    public partial class Form1 : Form
    {
        #region Khai bao biến và ma trận kho
        private List<COrder> DS_Orders = new List<COrder>();
        private HashSet<string> madh = new HashSet<string>();
        private int Num = 0;

        
        private Kho khoHang = new Kho(10, 10);
        #endregion

        public Form1()
        {
            InitializeComponent();
        }

        private void thongbao(string message)
        {
            txt_output.AppendText(message + "\n");
            txt_output.ScrollToCaret();
        }

        private int SoSanhDonHang(COrder a, COrder b)
        {
            return a.KiemtraPriority(b);
        }

        private void SOSANHPriority()
        {
            DS_Orders.Sort(SoSanhDonHang);

            dgv_List.Rows.Clear();
            foreach (COrder i in DS_Orders)
            {
                // Hiển thị thêm thông tin Vị trí (Row, Col) lên DataGridView
                dgv_List.Rows.Add(i.Id, i.Priority, $"({i.Row}, {i.Col})");
            }
        }

        #region Nút Thêm Đơn Hàng (btn_Order_Click)
        private void btn_Order_Click(object sender, EventArgs e)
        {
            string id = txt_id.Text.Trim();
            string priorityStr = txt_Priority.Text.Trim();
            string rowStr = txt_ROW.Text.Trim();
            string colStr = txt_COLUMN.Text.Trim();

            // 1. Kiểm tra định dạng số của Độ ưu tiên
            if (!long.TryParse(priorityStr, out long priority))
            {
                thongbao(" không hợp lệ!");
                return;
            }

            // 2. Kiểm tra định dạng số của Vị trí Hàng và Cột
            if (!int.TryParse(rowStr, out int row) || !int.TryParse(colStr, out int col))
            {
                thongbao("không hợp lệ");
                return;
            }

            try
            {
                // 3. Kiểm tra trùng mã đơn hàng
                if (madh.Contains(id))
                {
                    thongbao("id đã tồn tại");
                    return;
                }

                Num++;
                // Tạo đơn hàng mới kèm theo tọa độ (row, col)
                COrder newOrder = new COrder(id, priority, Num, row, col);

                DS_Orders.Add(newOrder);
                madh.Add(id);

                thongbao("OK");
                SOSANHPriority();
            }
            catch (ArgumentException ex)
            {
                thongbao(ex.Message);
            }
        }
        #endregion

        #region Nút Tìm đường ngắn nhất cho đơn hàng ưu tiên (btn_TIM_Click)
        private void btn_TIM_Click(object sender, EventArgs e)
        {
            if (DS_Orders.Count == 0)
            {
                thongbao("Danh sách đơn hàng rỗng!");
                return;
            }

            
            COrder topOrder = DS_Orders[0];

            
            Point2D viTriXe = new Point2D(0, 0);

            
            Point2D viTriDonHang = new Point2D(topOrder.Row, topOrder.Col);

            
            var res = khoHang.FindShortestPath(viTriXe, viTriDonHang);

            if (res.Distance == -1)
            {
                thongbao($"Vị trí đơn hàng ({topOrder.Row}, {topOrder.Col}) nằm ngoài phạm vi kho!");
            }
            else
            {
                thongbao($"=== LỘ TRÌNH LẤY ĐƠN HÀNG {topOrder.Id} TẠI VỊ TRÍ ({topOrder.Row}, {topOrder.Col}) ===");
                thongbao($"Tổng số bước di chuyển: {res.Distance}");

                string loTrinhStr = "";
                foreach (var p in res.Path)
                {
                    loTrinhStr += $"({p.X},{p.Y}) -> ";
                }
                if (loTrinhStr.EndsWith(" -> "))
                    loTrinhStr = loTrinhStr.Substring(0, loTrinhStr.Length - 4);

                thongbao("Lộ trình di chuyển: " + loTrinhStr);
            }
        }
        #endregion

        private void btn_Next_Click(object sender, EventArgs e)
        {
            if (DS_Orders.Count == 0)
            {
                thongbao(" Rỗng ");
                return;
            }

            COrder topOrder = DS_Orders[0];
            thongbao("Đã xử lý: " + topOrder.xuat());

            DS_Orders.RemoveAt(0);
            SOSANHPriority();
        }

        private void btn_Peek_Click(object sender, EventArgs e)
        {
            if (DS_Orders.Count == 0)
            {
                thongbao(" Rỗng ");
                return;
            }

            thongbao(DS_Orders[0].xuat());
        }

        private void btn_Size_Click(object sender, EventArgs e)
        {
            thongbao(DS_Orders.Count.ToString());
        }

        private void btn_Thoat_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
