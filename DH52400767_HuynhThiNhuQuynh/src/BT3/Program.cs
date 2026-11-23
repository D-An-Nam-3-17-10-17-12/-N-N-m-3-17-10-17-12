using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace BT3
{
    class DonHang
    {
        public string Id;
        public long priority;
        public long thuTu;
    }
    class Program
    {
        static List<DonHang> heap = new List<DonHang>();
        static bool duocUuTien(DonHang a, DonHang b)
        {
            if (a.priority != b.priority) return a.priority > b.priority;
            return a.thuTu < b.thuTu;
        }
        static void Push(DonHang o)
        {
            heap.Add(o);
            int i = heap.Count - 1;
            while (i > 0)
            {
                int p = (i - 1) / 2;
                if (!duocUuTien(heap[i], heap[p])) break;
                DonHang t = heap[i]; heap[i] = heap[p]; heap[p] = t;
                i = p;
            }
        }
        static DonHang Pop()
        {
            DonHang top = heap[0];
            int last = heap.Count - 1;
            heap[0] = heap[last];
            heap.RemoveAt(last);
            int n = heap.Count;
            int i = 0;
            while (true)
            {
                int l = 2 * i + 1, r = 2 * i + 2, best = i;
                if (l < n && duocUuTien(heap[l], heap[best])) best = l;
                if (r < n && duocUuTien(heap[r], heap[best])) best = r;
                if (best == i) break;
                DonHang t = heap[i]; heap[i] = heap[best]; heap[best] = t;
                i = best;
            }
            return top;
        }
        static bool TryParsePriority(string s, out long value)
        {
            value = 0;
            if (s.Length == 0) return false;
            for (int i = 0; i < s.Length; i++)
                if (s[i] < '0' || s[i] > '9') return false;

            string t = s.TrimStart('0');
            if (t.Length == 0 || t.Length > 10) return false;
            value = long.Parse(t);
            return value >= 1 && value <= 1000000000L;
        }
        static void Main()
        {
            int q = int.Parse(Console.ReadLine().Trim());
            HashSet<string> seen = new HashSet<string>();
            StringBuilder sb = new StringBuilder();
            char[] sep = new char[] { ' ', '\t', '\r' };
            long seq = 0;

            for (int i = 0; i < q; i++)
            {
                string line = Console.ReadLine();
                if (line == null) line = "";
                string[] parts = line.Split(sep, StringSplitOptions.RemoveEmptyEntries);

                if (parts.Length == 0) { sb.AppendLine("INVALID"); continue; }

                string cmd = parts[0];

                if (cmd == "ORDER")
                {
                    long pr;
                    if (parts.Length != 3 || parts[1].Length > 20 ||
                        !TryParsePriority(parts[2], out pr))
                    {
                        sb.AppendLine("INVALID");
                    }
                    else if (seen.Contains(parts[1]))
                    {
                        sb.AppendLine("DUPLICATE");
                    }
                    else
                    {
                        seen.Add(parts[1]);
                        seq++;
                        DonHang o = new DonHang();
                        o.Id = parts[1];
                        o.priority = pr;
                        o.thuTu = seq;
                        Push(o);
                        sb.AppendLine("OK");
                    }
                }
                else if (cmd == "NEXT")
                {
                    if (parts.Length != 1) sb.AppendLine("INVALID");
                    else if (heap.Count == 0) sb.AppendLine("EMPTY");
                    else
                    {
                        DonHang o = Pop();
                        sb.AppendLine(o.Id + " " + o.priority);
                    }
                }
                else if (cmd == "PEEK")
                {
                    if (parts.Length != 1) sb.AppendLine("INVALID");
                    else if (heap.Count == 0) sb.AppendLine("EMPTY");
                    else
                    {
                        DonHang o = heap[0];
                        sb.AppendLine(o.Id + " " + o.priority);
                    }
                }
                else if (cmd == "SIZE")
                {
                    if (parts.Length != 1) sb.AppendLine("INVALID");
                    else sb.AppendLine(heap.Count.ToString());
                }
                else
                {
                    sb.AppendLine("INVALID");
                }
            }
            Console.Write(sb.ToString());
        }
    }
}
