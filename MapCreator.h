//
// Created by shani on 11/28/16.
//

#ifndef EX2_MAPCREATOR_H
#define EX2_MAPCREATOR_H

#include "ParseFromString.h"
#include <iostream>
#include "Map.h"
#include "Node.h"
#include "PointHistory.h"
#include "Grid.h"

using namespace std;
class MapCreator {
private:
    string gridSize;
    int obstacles;
    string obsitclesPoints;
    int startX,startY;
    int endX,endY;

public:
    /**
     * constructor
     */
    MapCreator(string size,int startXP,int startYP,int endXP,int endYP,int obs,string obsPoints);
    /**
     *
     * @return a map from a text
     */
    Map* getMap();
};


#endif //EX2_MAPCREATOR_H
