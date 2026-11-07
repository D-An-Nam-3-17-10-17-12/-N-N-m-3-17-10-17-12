#include "Warehouse.h"
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
const int dr[] = { -1,0,1,0 };
const int dc[] = { 0,1,0,-1 };
int bfsDistance(const WarehouseMap& map, Point start, Point end) {
	if (start.r == end.r && start.c == end.c)
		return 0;
	vector<vector<int>>dist(map.R, vector<int>(map.C, -1));
	queue<Point> q;
	q.push(start);
	dist[start.r][start.c] = 0;
	while (!q.empty()) {
		Point curr = q.front();
		q.pop();
		if (curr.r == end.r && curr.c == end.c) {
			return dist[curr.r][curr.c];
		}
		for (int i = 0;i < 4;i++) {
			int nr = curr.r + dr[i];
			int nc = curr.c + dc[i];
			if (nr >= 0 && nr < map.R && nc >= 0 && nc < map.C) {
				if (map.grid[nr][nc] == '.' && dist[nr][nc] == -1) {
					dist[nr][nc] = dist[curr.r][curr.c] + 1;
					q.push({ nr,nc });
				}
			}
		}
	}
	return -1;
}
int solveMultiPoints(const WarehouseMap& map, const std::vector<Point>& points) {
	int k = points.size();
	if (k == 0) return 0;
	vector<vector<int>>dist(k, vector<int>(k, 0));
	for (int i = 0;i < k;++i) {
		for (int j = i + 1;j < k;++j) {
			int d = bfsDistance(map, points[i], points[j]);
			if (d == -1) return -1;
			dist[i][j] = dist[i][j] = d;
		}
	}
	const int INF = 1e9;
	vector<vector<int>> dp(1 << k, vector<int>(k, INF));
	dp[1][0] = 0;
	for (int mask = 1;mask < (1 << k);++mask) {
		for (int u = 0;u < k;++u) {
			if (!(mask & (1 << u))) continue;
			if (dp[mask][u] == INF) continue;
			for (int v = 0;v < k;++v) {
				if (!(mask & (1 << v))) {
					int next_mask = mask | (1 << v);
					dp[next_mask][v] = min(dp[next_mask][v], dp[mask][u] + dist[u][v]);
				}
			}
		}
	}
	int full_mask = (1 << k) - 1;
	int ans = INF;
	for (int u = 0;u < k;++u) {
		ans = min(ans, dp[full_mask][u]);
	}
	return (ans >= INF) ? -1 : ans;
}
PathResult bfsWithPath(const WarehouseMap& map, Point start, Point end) {
	if (start.r == end.r && start.c == end.c) {
		return { 0,{ start } };
	}
	vector<vector<int>> dist(map.R, vector<int>(map.C, -1));
	vector<vector<Point>> parent(map.R, vector<Point>(map.C, { -1,-1 }));
	queue<Point> q;
	q.push(start);
	dist[start.r][start.c] = 0;
	bool found = false;
	while (!q.empty()) {
		Point curr = q.front();
		q.pop();
		if (curr.r == end.r && curr.c == end.c) {
			found = true;
			break;
		}
		for (int i = 0;i < 4;++i) {
			int nr = curr.r + dr[i];
			int nc = curr.c + dc[i];
			if (nr >= 0 && nr < map.R && nc >= 0 && nc < map.C) {
				if (map.grid[nr][nc] == '.' && dist[nr][nc] == -1) {
					dist[nr][nc] = dist[curr.r][curr.c] + 1;
					parent[nr][nc] = curr;
					q.push({ nr,nc });
				}
			}
		}
	}
	if (!found) return { -1,{} };
	vector<Point> path;
	Point curr = end;
	while (curr.r != -1 && curr.c != -1) {
		path.push_back(curr);
		curr = parent[curr.r][curr.c];
	}
	reverse(path.begin(), path.end());
	return { dist[end.r][end.c],path };
}
QueryResult solveQuery(const WarehouseMap& map, const vector<Point>& points) {
	int k = points.size();
	QueryResult res;
	res.isInvalid = false;
	if (k == 0) {
		res.totalSteps = 0;
		return res;
	}
	vector<vector<PathResult>> pairPaths(k, vector<PathResult>(k));
	vector<vector<int>> dist(k, vector<int>(k, 0));
	for (int i = 0;i < k;++i) {
		for (int j = 0;j < k;++j) {
			if (i == j) continue;
			pairPaths[i][j] = bfsWithPath(map, points[i], points[j]);
			dist[i][j] = pairPaths[i][j].dist;
			if (dist[i][j] == -1) {
				res.totalSteps = -1;
				return res;
			}
		}
	}
	const int INF = 1e9;
	vector<vector<int>> dp(1 << k, vector<int>(k, INF));
	vector<vector<int>> parent_node(1 << k, vector<int>(k, -1));
	dp[1][0] = 0;
	for (int mask = 1;mask < (1 << k);++mask) {
		for (int u = 0;u < k;++u) {
			if (!(mask & (1 << u))) continue;
			if (dp[mask][u] == INF) continue;
			for (int v = 0;v < k;++v) {
				if (!(mask & (1 << v))) {
					int next_mask = mask | (1 << v);
					if (dp[mask][u] + dist[u][v] < dp[next_mask][v]) {
						dp[next_mask][v] = dp[mask][u] + dist[u][v];
						parent_node[next_mask][v] = u;
					}
				}
			}
		}
	}
	int full_mask = (1 << k) - 1;
	int best_end = -1;
	int min_ans = INF;
	for (int u = 0;u < k;++u) {
		if (dp[full_mask][u] < min_ans) {
			min_ans = dp[full_mask][u];
			best_end = u;
		}
	}
	if (min_ans >= INF) {
		res.totalSteps = -1;
		return res;
	}
	res.totalSteps = min_ans;
	vector<int> order;
	int curr_mask = full_mask;
	int curr_u = best_end;
	while (curr_u != -1) {
		order.push_back(curr_u);
		int prev_u = parent_node[curr_mask][curr_u];
		curr_mask ^= (1 << curr_u);
		curr_u = prev_u;
	}
	reverse(order.begin(), order.end());
	res.fullPath.push_back(points[order[0]]);
	for (size_t i = 0;i < order.size() - 1;++i) {
		int u = order[i];
		int v = order[i + 1];
		const auto& p = pairPaths[u][v].path;
		for (size_t j = 1;j < p.size();++j) {
			res.fullPath.push_back(p[j]);
		}
	}
	return res;
}
