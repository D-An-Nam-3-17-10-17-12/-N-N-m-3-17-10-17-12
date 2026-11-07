#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <vector>
#include <string>
struct Point {
	int r, c;
};
struct WarehouseMap {
	int R, C;
	std::vector<std::string>grid;
};
struct PathResult {
	int dist;
	std::vector<Point> path;
};
struct QueryResult {
	int totalSteps;
	bool isInvalid;
	std::vector<Point> fullPath;
};
int bfsDistance(const WarehouseMap& map, Point start, Point end);
int solveMultiPoints(const WarehouseMap& map, const std::vector<Point>& points);
PathResult bfsWithPath(const WarehouseMap& map, Point start, Point end);
QueryResult solveQuery(const WarehouseMap& map, const std::vector<Point>& points);
#endif
