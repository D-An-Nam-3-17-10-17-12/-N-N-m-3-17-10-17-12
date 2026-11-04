namespace Đồ_án_bài_1
{
    using System;
    using System.Collections.Generic;
    internal class Program
    {
        static int[] dx = { -1, 1, 0, 0 };
        static int[] dy = { 0, 0, -1, 1 };
        static void Main(string[] args)
        {
            string[] kichThuoc = Console.ReadLine().Split(' ');

            int R=int.Parse(kichThuoc[0]);
            int C=int .Parse(kichThuoc[1]);
            char[,] map = new char[R,C];
          
           
            for(int i = 0;i<R;i++)
            {

                string s = Console.ReadLine()?? "";

                if (s.Length != C)
                {
                    Console.WriteLine("Sai so cot!");
                    return;
                }

                for (int j = 0; j < C; j++)
                {
                    map[i, j] = s[j];
                }
            }
            int Q = int.Parse(Console.ReadLine());
            List<int> ketQuaCacTruyVan = new List<int>();
            List<List<(int, int)>> duongDiCacTruyVan =
                new List<List<(int, int)>>();
            for (int q = 0; q < Q; q++)
            {
                string dongNhap = Console.ReadLine() ?? "";
                string[] duLieu = dongNhap.Split(' ', StringSplitOptions.RemoveEmptyEntries);

                if (duLieu.Length == 0)
                {
                    ketQuaCacTruyVan.Add(-2);
                    duongDiCacTruyVan.Add(new List<(int, int)>());
                    continue;
                }
                if (!int.TryParse(duLieu[0], out int k))
                {
                    ketQuaCacTruyVan.Add(-2);
                    duongDiCacTruyVan.Add(new List<(int, int)>());
                    continue;
                }

                if (k < 2 || k > 8)
                {
                    ketQuaCacTruyVan.Add(-2);
                    duongDiCacTruyVan.Add(new List<(int, int)>());
                    continue;
                }
                if (duLieu.Length != 1 + 2 * k)
                {
                    ketQuaCacTruyVan.Add(-2);
                    duongDiCacTruyVan.Add(new List<(int, int)>());
                    continue;
                }
                int[,] cacDiem = new int[k, 2];
                bool hopLe = true;
                for (int i = 0; i < k; i++)
                {
                    if (!int.TryParse(duLieu[1 + i * 2], out int x) || !int.TryParse(duLieu[2 + i * 2], out int y))
                    {
                        hopLe = false;
                        continue;
                    }

                    cacDiem[i, 0] = x;
                    cacDiem[i, 1] = y;

                    

                    if (x < 0 || x >= R || y < 0 || y >= C ||(x >= 0 && x < R && y >= 0 && y < C && map[x, y] == '#'))
                    {
                        hopLe = false;
                    }
                }
                if (!hopLe)
                {
                    ketQuaCacTruyVan.Add(-2);
                    duongDiCacTruyVan.Add(new List<(int, int)>());
                    continue;
                }
                int[,] kcDiem = new int[k, k];


                for (int i = 0; i < k; i++)
                {
                    for (int j = 0; j < k; j++)
                    {
                        kcDiem[i, j] = BFS(
                            map, R, C,
                            cacDiem[i, 0], cacDiem[i, 1],
                            cacDiem[j, 0], cacDiem[j, 1],
                            out _);
                    }
                }
                int soTrangThai = 1 << (k - 1);
                int[,] dp = new int[soTrangThai, k];
                int[,] truocDo = new int[soTrangThai, k];
                for (int mask = 0; mask < soTrangThai; mask++)
                {
                    for (int i = 0; i < k; i++)
                    {
                        dp[mask, i] = int.MaxValue;
                        truocDo[mask, i] = -1;
                    }
                }


                dp[0, 0] = 0;
                for (int mask = 0; mask < soTrangThai; mask++)
                {
                    for (int i = 0; i < k; i++)
                    {
                        if (dp[mask, i] == int.MaxValue)
                            continue;

                        for (int j = 1; j < k; j++)
                        {
                            int bit = 1 << (j - 1);

                            if ((mask & bit) == 0 && kcDiem[i, j] != -1)
                            {
                                int maskMoi = mask | bit;
                                int tongMoi = dp[mask, i] + kcDiem[i, j];

                                if (tongMoi < dp[maskMoi, j])
                                {
                                    dp[maskMoi, j] = tongMoi;
                                    truocDo[maskMoi, j] = i;
                                }
                            }
                        }
                    }
                }
                int maskCuoi = soTrangThai - 1;
                int ketQua = int.MaxValue;
                int diemCuoi = -1;

                for (int i = 1; i < k; i++)
                {
                    if (dp[maskCuoi, i] < ketQua)
                    {
                        ketQua = dp[maskCuoi, i];
                        diemCuoi = i;
                    }
                }

                if (ketQua == int.MaxValue)
                    ketQua = -1;

                ketQuaCacTruyVan.Add(ketQua);
                List<int> thuTu = new List<int>();
                List<(int, int)> duongDiTong = new List<(int, int)>();

                if (ketQua != -1)
                {
                    int mask = maskCuoi;
                    int hienTai = diemCuoi;

                    while (hienTai != 0)
                    {
                        thuTu.Add(hienTai);

                        int bit = 1 << (hienTai - 1);
                        int maskTruoc = mask ^ bit;

                        hienTai = truocDo[mask, hienTai];
                        mask = maskTruoc;
                    }


                    thuTu.Add(0);
                    thuTu.Reverse();


                    for (int i = 0; i < thuTu.Count - 1; i++)
                    {
                            int a = thuTu[i];
                            int b = thuTu[i + 1];

                            BFS(map, R, C,
                                cacDiem[a, 0], cacDiem[a, 1],
                                cacDiem[b, 0], cacDiem[b, 1],
                                out List<(int, int)> duongDiDoan);

                            if (i == 0)
                                duongDiTong.AddRange(duongDiDoan);
                            else
                            {
                                for (int j = 1; j < duongDiDoan.Count; j++)
                                    duongDiTong.Add(duongDiDoan[j]);
                            }
                        }
                    
                }
                duongDiCacTruyVan.Add(duongDiTong);





            }

            
            for (int i = 0; i < Q; i++)
            {
                if (ketQuaCacTruyVan[i] == -2)
                    Console.WriteLine("INVALID");
                else
                    Console.WriteLine(ketQuaCacTruyVan[i]);
            }


            for (int i = 0; i < Q; i++)
            {
                if  (ketQuaCacTruyVan[i] == -1 ||ketQuaCacTruyVan[i] == -2)
                {
                    Console.WriteLine("-");
                }
                else
                {
                    int gioiHan = Math.Min(duongDiCacTruyVan[i].Count, 11);

                    for (int j = 0; j < gioiHan; j++)
                    {
                        Console.Write("(" + duongDiCacTruyVan[i][j].Item1 +
                                      "," + duongDiCacTruyVan[i][j].Item2 + ") ");
                    }

                    if (duongDiCacTruyVan[i].Count > 11)
                        Console.Write("...");

                    Console.WriteLine();
                }
            }


        }
        static int BFS(char[,] map, int R, int C, int x1, int y1, int x2, int y2, out List<(int, int)> duongDi2)
        {
            duongDi2 = new List<(int, int)>();

            if (x1 < 0 || x1 >= R || y1 < 0 || y1 >= C ||
                x2 < 0 || x2 >= R || y2 < 0 || y2 >= C ||
                map[x1, y1] == '#' || map[x2, y2] == '#')
            {
                return -1;
            }
            int[,] khoangCach = new int[R, C];
            (int, int)[,] cha = new (int, int)[R, C];
            for (int i = 0;i < R; i++)
            {
                for(int j = 0;j < C; j++)
                {
                    khoangCach[i, j] = -1;
                }    
            }    
            Queue<(int,int)> hangDoi = new Queue<(int, int )>();
            khoangCach[x1,y1] = 0;
            hangDoi.Enqueue((x1,y1));
            while(hangDoi.Count > 0)
            {
                var hienTai=hangDoi.Dequeue();
                int x = hienTai.Item1;
                int y = hienTai.Item2;  

                for(int i = 0; i < 4; i++)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (nx >= 0 && nx < R && ny >= 0 && ny < C &&
                            map[nx, ny] != '#' &&
                            khoangCach[nx, ny] == -1)
                    {
                        khoangCach[nx, ny] = khoangCach[x, y] + 1;
                        cha[nx, ny] = (x, y);
                        hangDoi.Enqueue((nx, ny));
                    }
                } 
                    
            }

            
            
            if (khoangCach[x2, y2] == -1)
            {
                return -1;
            }
            int dong = x2;
            int cot = y2;
            while (dong != x1 || cot != y1)
            {
                duongDi2.Add((dong, cot));

                var truoc = cha[dong, cot];

                dong = truoc.Item1;
                cot = truoc.Item2;
            }
            duongDi2.Add((x1, y1));
            duongDi2.Reverse();


            return khoangCach[x2,y2];
        }
        
    }
}
