using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Baitaptuan1
{
    public struct Point2D
    {
        public int X { get; set; } 
        public int Y { get; set; } 

        public Point2D(int x, int y)
        {
            X = x;
            Y = y;
        }
    }
    internal class Kho
    {
        #region Khai bao
        
        private int rows;
        private int cols;

        
        private int[] dRow = { -1, 1, 0, 0 };
        private int[] dCol = { 0, 0, -1, 1 };
        #endregion

        #region Phuong thuc
        public Kho(int maxRows, int maxCols)
        {
            rows = maxRows;
            cols = maxCols;
        }


        private bool IsValid(int r, int c, bool[,] visited)
        {
            return (r >= 0 && r < rows && c >= 0 && c < cols && !visited[r, c]);
        }


        public (int Distance, List<Point2D> Path) FindShortestPath(Point2D start, Point2D target)
        {
            
            if (start.X < 0 || start.X >= rows || start.Y < 0 || start.Y >= cols ||target.X < 0 || target.X >= rows || target.Y < 0 || target.Y >= cols)
            {
                return (-1, new List<Point2D>());
            }

            bool[,] visited = new bool[rows, cols];
            Point2D?[,] parent = new Point2D?[rows, cols];

            Queue<Point2D> queue = new Queue<Point2D>();

            queue.Enqueue(start);
            visited[start.X, start.Y] = true;
            parent[start.X, start.Y] = null;

            bool found = false;

            while (queue.Count > 0)
            {
                Point2D current = queue.Dequeue();

                
                if (current.X == target.X && current.Y == target.Y)
                {
                    found = true;
                    break;
                }

                for (int i = 0; i < 4; i++)
                {
                    int newRow = current.X + dRow[i];
                    int newCol = current.Y + dCol[i];

                    if (IsValid(newRow, newCol, visited))
                    {
                        visited[newRow, newCol] = true;
                        parent[newRow, newCol] = current;
                        queue.Enqueue(new Point2D(newRow, newCol));
                    }
                }
            }

            List<Point2D> path = new List<Point2D>();
            if (!found) return (-1, path);

            
            Point2D? currNode = target;
            while (currNode.HasValue)
            {
                path.Add(currNode.Value);
                currNode = parent[currNode.Value.X, currNode.Value.Y];
            }

            path.Reverse(); 
            int distance = path.Count - 1;

            return (distance, path);
        }
        #endregion
    }
}
