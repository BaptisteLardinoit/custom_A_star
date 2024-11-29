#ifndef GRID_V2_H
#define GRID_v2_H

#include<iostream>
#include<algorithm>
#include<vector>
#include"node_V2.h"


class Grid{
public:
    Grid(int _height, int _width, std::vector<vector2> _obstical) : height(_height), width(_width), grid(_width , std::vector<int>(_height)), obstical(_obstical) {
        initialise();
        initialiseObstical();
    }

    int height;
    int width;
    std::vector<std::vector<int>> grid;
    std::vector<vector2> obstical;

    void initialise(){//Initialise grid with zeros (no obsticales)
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                grid[i][j] = 0;
            }
        }
    }
    void print(){//print grid
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                std::cout<<"    "<<grid[i][j];
            }
            std::cout<<std::endl<<std::endl;
        }
    }

    void initialiseObstical(){
        for(const auto& coord : obstical){
            grid[coord.x][coord.y] = 1;
        }
    }

};


#endif // GRID_V2_H
