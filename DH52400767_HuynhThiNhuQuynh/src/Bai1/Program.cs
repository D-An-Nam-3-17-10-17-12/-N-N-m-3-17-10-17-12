using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Bai1
{
    internal class Program
    {
        static int R, C, N;
        static char[][] kho;
        static int[] kcach;
        static int[] parent;
        static int[] hangdoi;

        static readonly int[] dR = { 1, -1, 0, 0 };
        static readonly int[] dC = { 0, 0, -1, 1 };

        static void BFS(int start, int target = -1)
        {
            for (int i = 0; i < kcach.Length; i++)
            {
                kcach[i] = -1;
            }
            int head=0, tail=0;
            hangdoi[tail++] = start;
            kcach[start] = 0;
            parent[start] = -1;
            while(head < tail)
            {
                int u=hangdoi[head++];
                if (u == target)
                {
                    return;
                }
                int r = u / C;
                int c = u % C;
                for (int h = 0; h < 4; h++)
                {
                    int nR=r+dR[h];
                    int nC=c+dC[h];
                    if(nR<0||nR>=R||nC < 0 || nC >= C)                  
                        continue;                   
                    if (kho[nR][nC] == '#')                  
                        continue;                  
                    int v = nR * C + nC;
                    if (kcach[v] != -1)                  
                        continue;                  
                    kcach[v] = kcach[u] + 1;
                    parent[v] = u;
                    hangdoi[tail++] = v;

                }
            }
        }
        static bool TruyVan(string line, out int[] diem)
        {
            diem = new int[0];
            if (line == null)
                return false;
            string[] tokens =line.Split(new char[] { ' ','\t','\r','\n'}, StringSplitOptions.RemoveEmptyEntries);
            int k;
            if(tokens.Length==0||!int.TryParse(tokens[0], out k) || k < 2 || k > 8)
            {
                return false;
            }
            if (tokens.Length != 1 + 2 * k)
                return false;
            diem = new int[k];
            for(int i = 0; i < k; i++)
            {
                int r, c;
                if (!int.TryParse(tokens[1 + 2 * i], out r) || !int.TryParse(tokens[2 + 2 * i], out c))
                {
                    return false;
                }
                if (r < 0 || r >= R || c < 0 || c >= C)
                    return false;
                if (kho[r][c] == '#')
                    return false;
                diem[i] = r * C + c;
            }
            return true;
        }
        //HAM THEM
        static void Them(StringBuilder s, int id)
        {
            if (s.Length > 0)         
                s.Append(' ');          
            s.Append('(');
            s.Append(id/C);
            s.Append(',');
            s.Append(id % C);
            s.Append(')');
        }
        static string taoDuongDi(int[]diem, int[] order, int total)
        {
            StringBuilder s = new StringBuilder();
            Them(s, diem[0]);
            int daIn = 0;
            for (int i = 1; i < order.Length && daIn < 10; i++) 
            {
                int batDau = diem[order[i - 1]];
                int ketThuc=diem[order[i]];
                if (batDau == ketThuc)
                    continue;
                BFS(batDau); //chay bfs rieng doan giua 2 diem de lay mang parent cho dung
                int length = kcach[ketThuc];
                if (length == -1) break;
                int canLay = Math.Min(length, 10 - daIn);
                int[] first= new int[canLay];
                int current = ketThuc;
                for (int buoc = length; buoc >= 1; buoc--)
                {
                    if (buoc <= canLay)                   
                        first[buoc - 1] = current;                    
                    current = parent[current];
                }
                for(int j = 0; j < canLay; j++)
                {
                    Them(s, first[j]);
                    daIn++;
                }
            }
            if (total > 10)
                s.Append(" ...");
            return s.ToString();
        }
        static int Giai(int[] diem, out string DuongDi)
        {
            DuongDi = "-";
            int k = diem.Length;
            int[,] d= new int[k, k];
            for(int i = 0; i < k; i++)
            {
                BFS(diem[i]);
                for(int j = 0;j < k; j++)
                {
                    d[i, j] = kcach[diem[j]];
                }
                if (i == 0) 
                {
                    for(int j = 1; j < k; j++)
                    {
                        if (d[0, j] == -1)
                            return -1;
                    }
                }
            }
            int states = 1 << k;
            const int INF = int.MaxValue / 2;
            int[,] dp = new int[states, k];
            int[,] previous = new int[states, k];
            for(int mask = 0; mask < states; mask++)
            {
                for(int i = 0; i < k; i++)
                {
                    dp[mask, i] = INF;
                    previous[mask, i] = -1;
                }
            }
            dp[1, 0] = 0;
            for(int mask = 1; mask < states; mask++)
            {
                for(int i = 0; i < k; i++)
                {
                    if (dp[mask, i] == INF)                   
                        continue;                   
                    for (int j = 0; j < k; j++)
                    {
                        if ((mask & (1 << j)) != 0)
                            continue;
                        if (d[i, j] == -1) //khong co duong di giua i va j
                            continue;
                        int nextMask = mask | (1 << j);
                        int value = dp[mask, i] + d[i, j];
                        if(value<dp[nextMask, j])
                        {
                            dp[nextMask, j] = value;
                            previous[nextMask, j] = i;
                        }
                    }
                }
            }
            int fullMask = states - 1;
            int answer = INF;
            int last = -1;
            for(int i = 0; i < k; i++)
            {
                if (dp[fullMask, i] < answer)
                {
                    answer= dp[fullMask, i];
                    last = i;
                }
            }
            if (answer >= INF)
            {
                return -1; //neu khong tim duoc duong di qua cac diem
            }
            //truy van thu tu ghe cac diem
            int[] order = new int[k];
            int currentMask = fullMask;
            int currentPoint = last;
            for(int pos = k - 1; pos >= 0; pos--)
            {
                order[pos]=currentPoint;
                int prev = previous[currentMask,currentPoint];
                currentMask  ^=1 << currentPoint;
                currentPoint = prev;
            }
            DuongDi = taoDuongDi(diem, order, answer);
            return answer;
        }
        static void Main()
        {
            string line = Console.ReadLine();
            if (string.IsNullOrWhiteSpace(line))
            {
                Console.WriteLine("Ban chua nhap du lieu!");
                return;
            }
            string[] size = line.Split(new char[] { ' ', '\t' },StringSplitOptions.RemoveEmptyEntries);

            if (size.Length < 2 ||!int.TryParse(size[0], out R) || !int.TryParse(size[1], out C) ||R <= 0 || C <= 0)
            {
                Console.WriteLine("Du lieu khong hop le! (Vi du: 5 6)");
                return;
            }
            N = R * C;
            kho = new char[R][];
            for (int i = 0; i < R; i++)
            {
                string row = Console.ReadLine();
                while (row != null && string.IsNullOrEmpty(row)) //Phong khi dong bi trong
                    row = Console.ReadLine();
                if (row == null) return;
                kho[i] = row.Trim().PadRight(C,'#').ToCharArray();
            }
            kcach = new int[N];
            parent = new int[N];
            hangdoi = new int[N];
            string lineQ = Console.ReadLine();
            while (lineQ != null && string.IsNullOrWhiteSpace(lineQ))
                lineQ = Console.ReadLine();
            if (lineQ == null) return;
            int Q;
            if (!int.TryParse(lineQ, out Q) || Q < 0)
            {
                Console.WriteLine("Loi: Vui long nhap Q la mot so nguyen khong am.");
                return;
            }
            string[] ketQua = new string[Q];
            string[] duongDi = new string[Q];
            for (int q = 0; q < Q; q++)
            {
                string truyvanStr = Console.ReadLine();
                while (truyvanStr != null && string.IsNullOrWhiteSpace(truyvanStr)) //truyvan
                {
                    truyvanStr = Console.ReadLine();
                }
                int[] diem;
                if (!TruyVan(truyvanStr, out diem))
                {
                    ketQua[q] = "INVALID";
                    duongDi[q] = "-";
                    continue;
                }
                int answer = Giai(diem, out duongDi[q]);
                ketQua[q]=answer == -1 ? "-1" : answer.ToString();
            }
            for(int q = 0; q < Q; q++)
                Console.WriteLine(ketQua[q]);
            for(int q = 0; q < Q; q++)
                Console.WriteLine(duongDi[q]);

            Console.ReadLine();
        }
    }
}
