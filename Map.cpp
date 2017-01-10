//
// Created by shani on 11/28/16.
//

#include "Map.h"
#include "Node.h"
#include "PointHistory.h"
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Map);
/**
 * constractor
 */
 Map::Map(){}
/**
 * destructor
 */
 Map::~Map(){}
 /**
  * prints map
  */
/**
 * prints map
 */
void Map::print(){}
/**
 * gets the path from a start point to a goal point
 * @param speed - the speed of the cab (1 or 2)
 * @return false if there is no path to the goal point, else return true.
 */
bool Map::run(){}
/**
 * gets neighbors of certian points according to map
 */
bool Map::getNeighbors(){}
/**
 *
 * @return current point
 */
Node* Map::getCurrent(){}
/**
 *
 * @return a vector of the shortests way from start point to dest point
 */
std::vector<Node*> Map:: getPass(){}