namespace Baitaptuan1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lb_lPriority = new System.Windows.Forms.Label();
            this.lb_lid = new System.Windows.Forms.Label();
            this.txt_id = new System.Windows.Forms.TextBox();
            this.txt_Priority = new System.Windows.Forms.TextBox();
            this.btn_Order = new System.Windows.Forms.Button();
            this.btn_Size = new System.Windows.Forms.Button();
            this.btn_Peek = new System.Windows.Forms.Button();
            this.btn_Next = new System.Windows.Forms.Button();
            this.dgv_List = new System.Windows.Forms.DataGridView();
            this.Colid = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.ColPriority = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.txt_output = new System.Windows.Forms.RichTextBox();
            this.btn_Thoat = new System.Windows.Forms.Button();
            this.btn_TIM = new System.Windows.Forms.Button();
            this.lb_ROW = new System.Windows.Forms.Label();
            this.txt_ROW = new System.Windows.Forms.TextBox();
            this.lb_COLUMN = new System.Windows.Forms.Label();
            this.txt_COLUMN = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_List)).BeginInit();
            this.SuspendLayout();
            // 
            // lb_lPriority
            // 
            this.lb_lPriority.AutoSize = true;
            this.lb_lPriority.Location = new System.Drawing.Point(26, 52);
            this.lb_lPriority.Name = "lb_lPriority";
            this.lb_lPriority.Size = new System.Drawing.Size(56, 13);
            this.lb_lPriority.TabIndex = 0;
            this.lb_lPriority.Text = "Độ ưu tiên";
            // 
            // lb_lid
            // 
            this.lb_lid.AutoSize = true;
            this.lb_lid.Location = new System.Drawing.Point(26, 9);
            this.lb_lid.Name = "lb_lid";
            this.lb_lid.Size = new System.Drawing.Size(41, 13);
            this.lb_lid.TabIndex = 1;
            this.lb_lid.Text = "Mã ĐH";
            // 
            // txt_id
            // 
            this.txt_id.Location = new System.Drawing.Point(106, 9);
            this.txt_id.Name = "txt_id";
            this.txt_id.Size = new System.Drawing.Size(120, 20);
            this.txt_id.TabIndex = 2;
            // 
            // txt_Priority
            // 
            this.txt_Priority.Location = new System.Drawing.Point(106, 52);
            this.txt_Priority.Name = "txt_Priority";
            this.txt_Priority.Size = new System.Drawing.Size(120, 20);
            this.txt_Priority.TabIndex = 3;
            // 
            // btn_Order
            // 
            this.btn_Order.Location = new System.Drawing.Point(347, 95);
            this.btn_Order.Name = "btn_Order";
            this.btn_Order.Size = new System.Drawing.Size(75, 23);
            this.btn_Order.TabIndex = 4;
            this.btn_Order.Text = "Order";
            this.btn_Order.UseVisualStyleBackColor = true;
            this.btn_Order.Click += new System.EventHandler(this.btn_Order_Click);
            // 
            // btn_Size
            // 
            this.btn_Size.Location = new System.Drawing.Point(239, 95);
            this.btn_Size.Name = "btn_Size";
            this.btn_Size.Size = new System.Drawing.Size(75, 23);
            this.btn_Size.TabIndex = 5;
            this.btn_Size.Text = "Size";
            this.btn_Size.UseVisualStyleBackColor = true;
            this.btn_Size.Click += new System.EventHandler(this.btn_Size_Click);
            // 
            // btn_Peek
            // 
            this.btn_Peek.Location = new System.Drawing.Point(128, 95);
            this.btn_Peek.Name = "btn_Peek";
            this.btn_Peek.Size = new System.Drawing.Size(75, 23);
            this.btn_Peek.TabIndex = 6;
            this.btn_Peek.Text = "Peek";
            this.btn_Peek.UseVisualStyleBackColor = true;
            this.btn_Peek.Click += new System.EventHandler(this.btn_Peek_Click);
            // 
            // btn_Next
            // 
            this.btn_Next.Location = new System.Drawing.Point(29, 95);
            this.btn_Next.Name = "btn_Next";
            this.btn_Next.Size = new System.Drawing.Size(75, 23);
            this.btn_Next.TabIndex = 7;
            this.btn_Next.Text = "Next";
            this.btn_Next.UseVisualStyleBackColor = true;
            this.btn_Next.Click += new System.EventHandler(this.btn_Next_Click);
            // 
            // dgv_List
            // 
            this.dgv_List.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_List.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Colid,
            this.ColPriority});
            this.dgv_List.Location = new System.Drawing.Point(29, 124);
            this.dgv_List.Name = "dgv_List";
            this.dgv_List.Size = new System.Drawing.Size(338, 267);
            this.dgv_List.TabIndex = 8;
            // 
            // Colid
            // 
            this.Colid.HeaderText = "Mã Đơn Hàng";
            this.Colid.Name = "Colid";
            // 
            // ColPriority
            // 
            this.ColPriority.HeaderText = "Độ ưu tiên ";
            this.ColPriority.Name = "ColPriority";
            // 
            // txt_output
            // 
            this.txt_output.BackColor = System.Drawing.SystemColors.InactiveCaption;
            this.txt_output.Location = new System.Drawing.Point(393, 124);
            this.txt_output.Name = "txt_output";
            this.txt_output.ReadOnly = true;
            this.txt_output.Size = new System.Drawing.Size(352, 267);
            this.txt_output.TabIndex = 9;
            this.txt_output.Text = "";
            // 
            // btn_Thoat
            // 
            this.btn_Thoat.Location = new System.Drawing.Point(669, 25);
            this.btn_Thoat.Name = "btn_Thoat";
            this.btn_Thoat.Size = new System.Drawing.Size(75, 23);
            this.btn_Thoat.TabIndex = 10;
            this.btn_Thoat.Text = "Thoat";
            this.btn_Thoat.UseVisualStyleBackColor = true;
            this.btn_Thoat.Click += new System.EventHandler(this.btn_Thoat_Click);
            // 
            // btn_TIM
            // 
            this.btn_TIM.Location = new System.Drawing.Point(454, 95);
            this.btn_TIM.Name = "btn_TIM";
            this.btn_TIM.Size = new System.Drawing.Size(75, 23);
            this.btn_TIM.TabIndex = 11;
            this.btn_TIM.Text = "Tìm BFS";
            this.btn_TIM.UseVisualStyleBackColor = true;
            this.btn_TIM.Click += new System.EventHandler(this.btn_TIM_Click);
            // 
            // lb_ROW
            // 
            this.lb_ROW.AutoSize = true;
            this.lb_ROW.Location = new System.Drawing.Point(278, 9);
            this.lb_ROW.Name = "lb_ROW";
            this.lb_ROW.Size = new System.Drawing.Size(29, 13);
            this.lb_ROW.TabIndex = 12;
            this.lb_ROW.Text = "Row";
            // 
            // txt_ROW
            // 
            this.txt_ROW.Location = new System.Drawing.Point(347, 9);
            this.txt_ROW.Name = "txt_ROW";
            this.txt_ROW.Size = new System.Drawing.Size(100, 20);
            this.txt_ROW.TabIndex = 13;
            // 
            // lb_COLUMN
            // 
            this.lb_COLUMN.AutoSize = true;
            this.lb_COLUMN.Location = new System.Drawing.Point(281, 51);
            this.lb_COLUMN.Name = "lb_COLUMN";
            this.lb_COLUMN.Size = new System.Drawing.Size(53, 13);
            this.lb_COLUMN.TabIndex = 14;
            this.lb_COLUMN.Text = "COLUMN";
            // 
            // txt_COLUMN
            // 
            this.txt_COLUMN.Location = new System.Drawing.Point(347, 52);
            this.txt_COLUMN.Name = "txt_COLUMN";
            this.txt_COLUMN.Size = new System.Drawing.Size(100, 20);
            this.txt_COLUMN.TabIndex = 15;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.txt_COLUMN);
            this.Controls.Add(this.lb_COLUMN);
            this.Controls.Add(this.txt_ROW);
            this.Controls.Add(this.lb_ROW);
            this.Controls.Add(this.btn_TIM);
            this.Controls.Add(this.btn_Thoat);
            this.Controls.Add(this.txt_output);
            this.Controls.Add(this.dgv_List);
            this.Controls.Add(this.btn_Next);
            this.Controls.Add(this.btn_Peek);
            this.Controls.Add(this.btn_Size);
            this.Controls.Add(this.btn_Order);
            this.Controls.Add(this.txt_Priority);
            this.Controls.Add(this.txt_id);
            this.Controls.Add(this.lb_lid);
            this.Controls.Add(this.lb_lPriority);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dgv_List)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lb_lPriority;
        private System.Windows.Forms.Label lb_lid;
        private System.Windows.Forms.TextBox txt_id;
        private System.Windows.Forms.TextBox txt_Priority;
        private System.Windows.Forms.Button btn_Order;
        private System.Windows.Forms.Button btn_Size;
        private System.Windows.Forms.Button btn_Peek;
        private System.Windows.Forms.Button btn_Next;
        private System.Windows.Forms.DataGridView dgv_List;
        private System.Windows.Forms.RichTextBox txt_output;
        private System.Windows.Forms.DataGridViewTextBoxColumn Colid;
        private System.Windows.Forms.DataGridViewTextBoxColumn ColPriority;
        private System.Windows.Forms.Button btn_Thoat;
        private System.Windows.Forms.Button btn_TIM;
        private System.Windows.Forms.Label lb_ROW;
        private System.Windows.Forms.TextBox txt_ROW;
        private System.Windows.Forms.Label lb_COLUMN;
        private System.Windows.Forms.TextBox txt_COLUMN;
    }
}

