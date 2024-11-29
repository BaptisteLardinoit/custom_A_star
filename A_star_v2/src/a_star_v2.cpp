#include<vector>
#include<algorithm>
#include<iostream>
#include<math.h>
#include <memory>
#include"grid_v2.h"
#include"node_v2.h"

std::vector<std::shared_ptr<Node>> closedSet;//Vector of pointers to Nodes
std::vector<std::shared_ptr<Node>> openSet;

vector2 goal;
vector2 startingCoord;

int gridHeight = 20;
int gridWidth = 20;

std::vector<vector2> creatObstical(int start_pos, int end_pos){
    std::vector<vector2> obstical;
    for(int i = start_pos; i < end_pos; i++){
        vector2 pos; pos.x = i; pos.y = 10;
        obstical.push_back(pos);
    }
    return obstical;
}
Grid grid(gridHeight, gridWidth, creatObstical(2, 19));
grid.grid


void space(int n){
    for(int i = 0; i < n; i++) std::cout<<std::endl;
}


bool mostEfficientInOpen(const std::shared_ptr<Node> currentNode_){//Returns true if currentNode is node with smallest g cost in openSet

    if(openSet.empty()){
        return true;
    }


    for(auto it = openSet.begin(); it != openSet.end();){

        if(currentNode_->coord.x == (*it)->coord.x && currentNode_->coord.y == (*it)->coord.y){//Check if same coord

            if(currentNode_->g < (*it)->g){//Node with bigger g cost in same place so remove it
                closedSet.push_back(*it);//add node_ to closedSet
                it = openSet.erase(it);//remove node_ from openSet if currentNode has smaller cost
            }
            else{
                return false;//Node with smaller g cost in openSet so do not add currrentNode to openSet
                ++it;
            }

        }

        else{
            ++it;
        }
    }
    return true;//did not find any nodes with smaller g cost in openSet

}


bool inBounds(int x, int y){
    return x >= 0 && y >= 0 && x < gridWidth && y < gridHeight;
}

int main(){
    startingCoord.x = 0; startingCoord.y = 0;
    grid.grid[startingCoord.x][startingCoord.y]=4;//Desplay start
    goal.x = 19; goal.y = 19;
    grid.grid[goal.x][goal.y]=5;//Desplay end

    std::shared_ptr<Node> startingNode = std::make_shared<Node>(startingCoord, goal, nullptr);//create pointer to starting node
    startingNode->g = 0;
    startingNode->euclidH(goal);
    openSet.push_back(startingNode);//Put starting node in openSet

    std::shared_ptr<Node> currentNode = startingNode;//Set pointer to current node equal to pointer to starting node

    std::vector<std::vector<int>> neigh{{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};

    int iter = 0;
    bool goalFound = false;

    while(!goalFound && iter < 5000){//Generate node until goal is reached

        //Get node with smallest cost in openSet
        auto compareNodeCost = [](const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) {
            return a->returnCost() < b->returnCost();
        };

        auto it = std::min_element(openSet.begin(), openSet.end(), compareNodeCost);

        if (it != openSet.end()) {
            currentNode = *it;
            closedSet.push_back(currentNode);//Add node with smallest cost in closed set
            openSet.erase(it);//Remove node with smallest cost in open set
        }


        //Generate neighbour nodes to the currentNode
        for(const auto& steps: neigh){
            //std::cout<<"in for loop"<<std::endl;

            int _x = currentNode->coord.x + steps[0];
            int _y = currentNode->coord.y + steps[1];

            if(inBounds(_x,_y)){
                if(grid.grid[_x][_y] != 1){//If node is free generate newNode
                    vector2 newCoord; newCoord.x = _x; newCoord.y = _y;
                    std::shared_ptr<Node> newNode = std::make_shared<Node>(newCoord, goal, currentNode);

                    //Initialise h cost
                    newNode->euclidH(goal);

                    //Initialise g cost
                    if(abs(steps[0]) == abs(steps[1])){//Diagonal
                        newNode->gCost(14);
                    }
                    else{//Transversal
                        newNode->gCost(10);
                    }

                    if(newNode->coord.x == goal.x && newNode->coord.y == goal.y){//If node is at goal position then set current node to newNode
                        goalFound = true;
                        currentNode = newNode;
                    }

                    if(mostEfficientInOpen(newNode)){//If new node is the node with smallest g on these coordinates then remove other nodes and add this one
                        openSet.push_back(newNode);
                        //grid.grid[newNode->coord.x][newNode->coord.y] = 3;
                        //space(40);
                        //grid.print();
                    }
                }
            }

        }
        iter ++;
    }
    //Print grid and path
    std::vector<vector2> path;
    while(currentNode->parent != nullptr){
        path.push_back(currentNode->coord);
        grid.grid[currentNode->coord.x][currentNode->coord.y] = 2;
        currentNode = currentNode->parent;
    }
    space(40);

    grid.print();


}
