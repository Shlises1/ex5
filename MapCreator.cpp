//
// Created by shani on 11/28/16.
//

#include "MapCreator.h"
#include "Grid.h"

/**
 * constructor.
 * This c,ass gets input of Grid details and retunrns a Grid object
 */
MapCreator::MapCreator(string size,int startXP,int startYP,int endXP,int endYP,int obs,string obsPoints){
    gridSize = size;
    obstacles = obs;
    obsitclesPoints  = obsPoints;
    startX = startXP;
    startY = startYP;
    endX = endXP;
    endY = endYP;

}
/**
 * return a Grid object
 * @return a map from a text
 */
Map* MapCreator:: getMap(){
    int width,length;
    int xAxex,yAxes;
    bool flag;
    ParseFromString parseFromString = ParseFromString(gridSize);
    parseFromString.parse(' ',&width,&length);
    //Vector of obstacles
    vector<Node*> nodeArr=vector<Node *>();
    if (obstacles > 0){
        parseFromString = ParseFromString(obsitclesPoints);
        for (int i=0;i<obstacles;i++) {
            flag = parseFromString.parse(',', &xAxex, &yAxes);
            if (flag) {
                PointHistory* po =new PointHistory(PointBase(xAxex, yAxes));
                nodeArr.push_back(po);
            }
        }
    }
    Map* map;
    map = new Grid(length,width,startX,startY,endX,endY,nodeArr);
    return map;
}