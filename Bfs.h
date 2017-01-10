//
// Created by ran on 17/11/16.
//

#ifndef EX1_BFS_H
#define EX1_BFS_H



#include <map>
#include <queue>
#include "PointBase.h"
#include "PointHistory.h"
#include "SearchAlgo.h"
#include <iostream>
#include <list>

using namespace std;



class Bfs: public SearchAlgo{
private:
    Node* currPoint;
    Node* startMap;
    std::queue<Node*> pointQue;
public:
    /**
    * constractor
    * @param lengthMap - the length
    * @param widthMap - the width
    * @param startP - start point
    */
    Bfs(Node* startP);
    /**
    * constractor
    */
    Bfs();
    /**
    *
    * @param neighbors - a vector with all the neighbors of the point
    * @return the next point
    */
    Node* getNext(vector<Node*> neighbors);
    /**
    * prints the path
    */
    void printPath();

};


#endif //EX1_BFS_H