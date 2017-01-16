
#ifndef EX1_GRID_H
#define EX1_GRID_H
#define MAX_SIZE 1000
#include "Bfs.h"
#include "PointBase.h"
#include "Map.h"

class Grid: public Map {
private:
    int length;
    int width;
    Bfs gridPath;
    PointHistory start;
    PointHistory goal;
    Node* matrix[MAX_SIZE][MAX_SIZE];
    vector<Node*>obstacles;
    Node* currentP;
public:
    /**
     * destructor
     */
    ~Grid();
    /**
      * constractor
      * @param gridLength - the length
      * @param gridWidth - the width
      * @param gridGoalX  - the x of the goal point
      * @param gridGoalY - the y of the goal point
      * @param gridStartx - the x of the start point
      * @param gridStartY - the y of the start point
       * @param obs - map of obsticals
      */
    Grid(int  gridLength, int  gridWidth, int gridGoalX, int gridGoalY, int gridStartx, int gridStartY,vector<Node*>obs);
    /**
     * gets the path from a start point to a goal point
     * @param speed - the speed of the cab (1 or 2)
     * @return false if there is no path to the goal point, else return true.
     */
    bool run();
    /**
    * prints the shortest path from the start point to the dest point
    */
    void print();
    /**
   *
   * @param xAxes - the x axes
   * @param yAxes - the y axes
   * @param neighbors - empty vector
   * @return true if there are any neighbors, and false if not.
   */
    bool getNeighbors(int xAxes, int yAxes, vector<Node *> *neighbors);
    /**
     * get current location in grid
     * @return Node object
     */
    Node* getCurrent();
    /**
     * 
     * @return a vector of the shortests way from start point to dest point
     */
    vector<Node*> getPass();
};
#endif //EX1_PATH_H