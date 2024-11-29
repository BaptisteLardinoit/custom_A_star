#ifndef NODE_v2_H
#define NODE_v2_H
#include<vector>
#include<algorithm>
#include<iostream>
#include<math.h>
#include <memory>


struct vector2{
    int x;
    int y;
};

class Node{
public:
    Node(vector2 _coord, vector2 goal, std::shared_ptr<Node> _parent): coord(_coord), parent(_parent) {//Class constructor
        euclidH(goal);
    }

    vector2 coord;
    std::shared_ptr<Node> parent;//Has to be shared_ptr because multiple nodes can have the same parent   std::shared_ptr<Node> parent = &_parent; parent is a pointer to the adresse of parent which is a Node
    float h = 0;
    float g = 0;

    void euclidH(vector2 goal){//Calculates distance between node and goal
        h = 9 * std::hypot(goal.x - coord.x, goal.y - coord.y);//hypotenus
    }

    void gCost(float step){
        g = (parent ? parent->g : 0) + step;//Check if perent is null
    }

    float returnCost() const{//returns total cost of node
        return  h + g;
    }

};

#endif // NODE_v2_H
