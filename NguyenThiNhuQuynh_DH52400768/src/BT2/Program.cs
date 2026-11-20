namespace Bài_2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Dictionary<string, Queue<LoHang>> kho = new Dictionary<string, Queue<LoHang>>();

            Dictionary<string, long> tonKho = new Dictionary<string, long>();

            HashSet<string> danhSachMaLo = new HashSet<string>();

            int Q = int.Parse(Console.ReadLine());

            for (int i = 0; i < Q; i++)
            {
                string dong = Console.ReadLine();
                string[] p = dong.Split(
                    (char[])null,
                    StringSplitOptions.RemoveEmptyEntries);

                if (p.Length == 4 && p[0] == "IMPORT")
                {
                    string sku = p[1];
                    string maLo = p[2];

                    if (sku.Length > 20 || maLo.Length > 20 ||
                        !HopLeSoLuong(p[3], out long qty))
                    {
                        Console.WriteLine("INVALID");
                        continue;
                    }

                    if (danhSachMaLo.Contains(maLo))
                    {
                        Console.WriteLine("DUPLICATE_LOT");
                        continue;
                    }

                    danhSachMaLo.Add(maLo);

                    if (!kho.ContainsKey(sku))
                    {
                        kho[sku] = new Queue<LoHang>();
                        tonKho[sku] = 0;
                    }
                   

                    kho[sku].Enqueue(new LoHang(maLo, qty));
                    tonKho[sku] += qty;

                    Console.WriteLine("OK");
                }
                else if (p.Length == 2 && p[0] == "STOCK")
                {
                    string maHang = p[1];

                    if (maHang.Length > 20)
                    {
                        Console.WriteLine("INVALID");
                    }
                    else if (!tonKho.ContainsKey(maHang))
                    {
                        Console.WriteLine(0);
                    }
                    else
                    {
                        Console.WriteLine(tonKho[maHang]);
                    }
                }
                else if (p.Length == 3 && p[0] == "EXPORT")
                {
                    string sku = p[1];

                    if (sku.Length > 20 ||
                        !HopLeSoLuong(p[2], out long qty))
                    {
                        Console.WriteLine("INVALID");
                        continue;
                    }

                    long ton = tonKho.ContainsKey(sku)
                        ? tonKho[sku] : 0;

                    if (ton < qty)
                    {
                        Console.WriteLine("NOT_ENOUGH " + ton);
                        continue;
                    }

                    long canXuat = qty;
                    List<string> ketQua = new List<string>();

                    while (canXuat > 0)
                    {
                        LoHang lo = kho[sku].Peek();

                        long lay = Math.Min(canXuat, lo.soLuong);

                        ketQua.Add(lo.maLo + ":" + lay);

                        lo.soLuong -= lay;
                        canXuat -= lay;
                        tonKho[sku] -= lay;

                        if (lo.soLuong == 0)
                        {
                            kho[sku].Dequeue();
                        }
                    }

                    Console.WriteLine(string.Join(" ", ketQua));
                }
                else
                {
                    Console.WriteLine("INVALID");
                }
            }
        }
        static bool HopLeSoLuong(string s, out long qty)
        {
            return long.TryParse(s, out qty)
                && qty >= 1
                && qty <= 1000000000;
        }

    }
}
