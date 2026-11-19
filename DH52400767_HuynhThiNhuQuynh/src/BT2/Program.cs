using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Schema;

namespace BT2
{
    class LoHang 
    {
        public string ID;
        public long qty;
        public LoHang(string iD, long qty)
        {
            ID = iD;
            this.qty = qty;
        }
    }
    internal class Program
    {
        const int MAX_LEN = 20;
        const long MAX_QTY = 1000000000;
        static Dictionary<string, Queue<LoHang>> khoLo = new Dictionary<string, Queue<LoHang>>();
        static Dictionary<string, long> tonKho = new Dictionary<string, long>();
        static HashSet<string> maLoDaDung = new HashSet<string>();
        static bool docQty(string s, out long qty)
        {
            if (!long.TryParse(s, NumberStyles.None, CultureInfo.InvariantCulture, out qty))
                return false;
            return qty>=1&&qty <=MAX_QTY;
        }
        static bool maHopLe(string s)
        {
            return s.Length >= 1 && s.Length <= MAX_LEN;
        }
        static long layTon(string sku)
        {
            long ton;
            return tonKho.TryGetValue(sku, out ton) ? ton : 0;
        }
        static string xuLy(string line)
        {
            if (line == null)
                return "INVALID";
            string[] t = line.Split(new char[] { ' ', '\t', '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);
            if (t.Length == 0)
                return "INVALID";
            string cmd = t[0];
            if (cmd == "IMPORT")
            {
                long qty;
                if (t.Length != 4 || !maHopLe(t[1]) || !maHopLe(t[2]) || !docQty(t[3], out qty))
                    return "INVALID";
                string sku = t[1];
                string lot = t[2];
                if (maLoDaDung.Contains(lot))
                    return "DUPLICATE_LOT";
                maLoDaDung.Add(lot);
                if (!khoLo.ContainsKey(sku))
                    khoLo[sku] = new Queue<LoHang>();
                khoLo[sku].Enqueue(new LoHang(lot, qty));
                tonKho[sku] = layTon(sku) + qty;
                return "OK";
            }
            if (cmd == "EXPORT")
            {
                long qty;
                if(t.Length != 3 || !maHopLe(t[1]) || !docQty(t[2],out qty))
                    return "INVALID";
                string sku = t[1];
                long ton = layTon(sku);
                if (ton < qty)
                    return "NOT_ENOUGH " + ton; 
                Queue<LoHang> q = khoLo[sku];
                StringBuilder sb = new StringBuilder();
                long can = qty;
                while(can > 0)
                {
                    LoHang dau = q.Peek();
                    long lay;
                    if (dau.qty <= can)
                    {
                        lay=dau.qty;
                        q.Dequeue();
                    }
                    else
                    {
                        lay= can;
                        dau.qty -= can;
                    }
                    if(sb.Length > 0)
                        sb.Append(' ');
                    sb.Append(dau.ID).Append(':').Append(lay);
                    can -= lay;
                }
                tonKho[sku] = ton - qty;
                return sb.ToString();
            }
            if (cmd == "STOCK")
            {
                if (t.Length != 2 || !maHopLe(t[1]))
                    return "INVALID";
                return layTon(t[1]).ToString();
            }
            return "INVALID";
        }
        static void Main()
        {
            string first=Console.ReadLine();
            int Q;
            if (first == null || !int.TryParse(first.Trim(), out Q) || Q < 1)
                return;
            StringBuilder outPut = new StringBuilder();
            for(int i = 0; i < Q; i++)
            {
                string line =Console.ReadLine();
                if (line == null)
                    break;
                outPut.AppendLine(xuLy(line));
            }
            Console.Write(outPut.ToString());
        }
    }
}

