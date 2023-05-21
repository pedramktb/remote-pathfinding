#include <vector>
#include <string>
#include <queue>
#include "npy.hpp"

class Pathfinding{
public:
    Pathfinding (std::string mapfile, size_t gird_height, size_t grid_width)
    :  height_(gird_height), width_(grid_width)
    {
        std::vector<unsigned long> shape {};
        bool fortran_order;
        std::vector<int> data;
        npy::LoadArrayFromNumpy(mapfile, shape, fortran_order, data);
        map_=data;
    }

    std::string find(int xy[4]){
        // for(int i =0;i<50;i++){
        //     for(int j =0;j<50;j++)
        //         std::cout<<coords_(i,j)<<' ';
        //     std::cout<<'\n';
        // }
        int start_row = xy[0];
        int start_col = xy[1];
        int end_row = xy[2];
        int end_col = xy[3];

        std::queue<std::pair<int,int>> q;
        q.push({start_row, start_col});

        std::vector<std::vector<bool>> visited(height_, std::vector<bool>(width_, false));
        visited[start_row][start_col] = true;

        std::vector<std::vector<std::pair<int,int>>> parent(height_, std::vector<std::pair<int,int>>(width_));
        parent[start_row][start_col] = {-1, -1};

        std::vector<std::pair<int,int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};

        // BFS
        while (!q.empty()) {
            std::pair<int,int> curr = q.front();
            q.pop();
            // Path Complete
            if (curr.first == end_row && curr.second == end_col) {
                std::vector<std::pair<int,int>> path;
                while (curr.first != start_row || curr.second != start_col) {
                    path.push_back(curr);
                    curr = parent[curr.first][curr.second];
                }
                path.push_back({start_row,start_col});
                std::reverse(path.begin(), path.end());

                std::string instructions;
                for (int i = 0; i < path.size() - 1; i++) {
                    int dx = path[i+1].second - path[i].second;
                    int dy = path[i+1].first - path[i].first;
                    switch(dx){
                        case(1):
                            instructions.push_back('R');
                            break;
                        case(-1):
                            instructions.push_back('L');
                            break;
                        case(0):
                            switch(dy){
                                case(1):
                                    instructions.push_back('D');
                                    break;
                                case(-1):
                                    instructions.push_back('U');
                                    break;
                            }
                    }
                }
                return instructions;
            }

            for (auto dir : directions) {
                int next_row = curr.first + dir.first;
                int next_col = curr.second + dir.second;

                // Check if the neighbor is within the grid and not blocked
                if (next_row >= 0 && next_row < height_ && next_col >= 0 && next_col < width_ &&
                    !visited[next_row][next_col] && coords_(next_row, next_col) != 1) {

                    visited[next_row][next_col] = true;
                    parent[next_row][next_col] = curr;

                    q.push({next_row, next_col});
                }
            }
        }

        return "X";
    }

private:
    std::vector<int> map_;
    size_t height_, width_;

    int coords_(size_t row,size_t col){
        return map_[width_*row+col];
    }
};