#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <string>
#include <vector>
class WarehouseRouter {
private:
    int rows, cols;
    std::vector<std::string> grid;
    int bfsDistances(int start, std::vector<int>& dist) const;
    bool buildPath(int start, int target, std::vector<int>& path) const;
    bool isValidPosition(int r, int c) const;

public:
    WarehouseRouter(int r, int c, const std::vector<std::string>& map);
    void processQuery(const std::string& line,
        std::string& stepOutput,
        std::string& pathOutput) const;
};
#endif

