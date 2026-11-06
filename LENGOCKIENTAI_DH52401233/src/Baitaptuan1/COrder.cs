using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Baitaptuan1
{
    internal class COrder
    {
        #region khai bao
        private string sId; // ma don hang
        private long iPriority;  // do uu tien
        private int iSNumber; // Số thứ tự đến[ 0 1 2 3 4 ]
        private int iRow; // Vi tri dong (Row)
        private int iCol; // Vi tri cot (Column)
        #endregion
        #region cap nhat gia tri
        public int Row 
        {
            get { return iRow; }
            set 
            {
                if (value < 0)
                    throw new ArgumentException("Chỉ số dòng không được nhỏ hơn 0!");
                iRow = value;
            }
        }
        public int Col
        {
            get { return iCol; }
            set 
            {
                if (value < 0)
                    throw new ArgumentException("Chỉ số cột không được nhỏ hơn 0!");
                iCol = value;
            }
        }
        public string Id
        {
            get { return sId; }
            set
            {
                if (string.IsNullOrEmpty(value) || value.Length > 20)
                    throw new ArgumentException("Mã đơn không hợp lệ!");
                sId = value;
            }
        }

        public long Priority
        {
            get { return iPriority; }
            set
            {
                if (value < 1)
                    throw new ArgumentException("Độ ưu tiên phải lớn hơn 0!");
                iPriority = value;
            }
        }

        public int Number
        {
            get { return iSNumber; }
            set { iSNumber = value; }
        }
        #endregion
        #region cac phuong thuc
        // khoi tao k tham so
        public COrder()
        {
            sId = "";
            iPriority = 1;
            iSNumber = 0;
            this.Row = 0;
            this.Col = 0;
        }

       // khoi tao co tham so
        public COrder(string id, long priority, int aNumber,int row,int col)
        {
            this.Id = id;             
            this.Priority = priority; 
            this.iSNumber = aNumber;
            this.Row = row;
            this.Col = col;
        }

        // kiem tra do uu tien
        public int KiemtraPriority(COrder a)
        {
            if (a == null) return 1;

           
            int sosanh = a.iPriority.CompareTo(this.iPriority);//(a=b 0 , a<b -1 , a>b 1 )
            if (sosanh != 0) // do uu tien khac nhau 
            {
                return sosanh;
            }

          
            return this.iSNumber.CompareTo(a.iSNumber);
        }

        // xuat
        public string xuat()
        {
            return $"{sId} {iPriority} - Vị trí: ({iRow}, {iCol})";
        }
        #endregion


    }
}
