
#include "Grid.h"
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
Grid::Grid(int  gridLength, int  gridWidth, int gridGoalX, int gridGoalY, int gridStartx,
           int gridStartY,vector<Node*>obs):Map(){
    length = gridLength;
    width = gridWidth;
    goal = PointBase(gridGoalX,gridGoalY);
    start = PointHistory(PointBase(gridStartx,gridStartY));
    gridPath = Bfs(&start);
    std::vector<Node*>::iterator it;
    int i;
    for (i = 0; i < width;i++){
        int j;
        for (j = 0; j<length;j++){
            PointHistory* po =new PointHistory(PointBase(i, j));
            if((po->getX() == start.getX()) && (po->getY() == start.getY())){
                po->setIsVisited(1);
            }
            for (int k=0;k<obs.size();k++) {
                if ((obs[k]->getX()==po->getX())&&(obs[k]->getY()==po->getY())) {
                    po->setIsObstacle(true);
                }
            }
            matrix[i][j] = po;
        }
    }
    currentP = &start;
    for (int i=0;i<obs.size();i++){
        delete(obs[i]);
    }
}
/**
 * destructor
 */
Grid::~Grid() {
    for (int i=0;i<width;i++) {
        for (int j=0;j<length;j++) {
            delete (matrix[i][j]);
            matrix[i][j] = NULL;
        }
    }
}
/**
 * gets the path from a start point to a goal point
 * @param speed - the speed of the cab (1 or 2)
 * @return false if there is no path to the goal point, else return true.
 */
bool Grid::run() {
    bool flag;
    //currentP = &start;
    //while didnt reach the goal point
    while (!((currentP->getX()==goal.getX())&&(currentP->getY()==goal.getY()))) {
        int xAxes = currentP->getX();
        int yAxes = currentP->getY();
        vector <Node*>neighbors = vector<Node *>();
        flag = getNeighbors(xAxes, yAxes, &neighbors);
        if (flag) {
            Node* p = gridPath.getNext(neighbors);
            //currentP = gridPath.getNext(neighbors);
            if(p == NULL) {
                return false;
            }
            currentP = p;
        } else {
            break;
        }
    }
    goal.SetFather(currentP);
    currentP = &goal;
    return true;
}
/**
 *
 * @return a vector of the shortests way from start point to dest point
 */
vector<Node*> Grid:: getPass(){
    vector<Node*> passBackwards = vector<Node*>();
    vector<Node*> pass = vector<Node*>();
    do{
        passBackwards.push_back(currentP);
        currentP = currentP->getFather();
    }while(!((currentP->getX() == start.getX()) && (currentP->getY() == start.getY())));
    //passBackwards.push_back(currentP);
    //reverse the vector
    for(int i = passBackwards.size() - 1; i >= 0; i--){
        pass.push_back(passBackwards.at(i));
    }
    return pass;
}

/**
* prints the shortest path from the start point to the dest point
*/
void Grid::print(){
    gridPath.printPath();
    cout<<goal<<endl;
}
/**
*
* @param xAxes - the x axes
* @param yAxes - the y axes
* @param neighbors - empty vector
* @return true if there are any neighbors, and false if not.
*/
bool Grid::getNeighbors(int xAxes, int yAxes, vector<Node *> *neighbors) {
    //Left
    if (xAxes - 1 >= 0) {
        Node *left = matrix[xAxes - 1][yAxes];
        if (!left->getIsObstacle()){
            if ((left->getX() == goal.getX()) && (left->getY() == goal.getY())) {
                return false;
            }
            neighbors->push_back(left);
            left->setIsVisited(left->getIsVisited() +1);
        }

    }
    //Moving up
    if (yAxes + 1 < length) {
        Node *up = matrix[xAxes][yAxes + 1];
        if (!up->getIsObstacle()) {
            if ((up->getX() == goal.getX()) && (up->getY() == goal.getY())) {
                return false;
            }
            neighbors->push_back(up);
            up->setIsVisited(up->getIsVisited() + 1);
        }

    }

    //Moving Right
    if (xAxes + 1 < width) {
        Node *right = matrix[xAxes + 1][yAxes];
        if (!right->getIsObstacle()) {
            if ((right->getX() == goal.getX()) && (right->getY() == goal.getY())) {
                return false;
            }
            neighbors->push_back(right);
            right->setIsVisited(right->getIsVisited() + 1);
        }

    }
    //Moving down
    if (yAxes - 1 >= 0) {
        Node *down = matrix[xAxes][yAxes - 1];
        if (!down->getIsObstacle()) {
            if ((down->getX() == goal.getX()) && (down->getY() == goal.getY())) {
                return false;
            }
            neighbors->push_back(down);
            down->setIsVisited(down->getIsVisited() + 1);
        }
    }
    return true;
}
/**
 * get current location in grid
 * @return Node object
 */
Node* Grid:: getCurrent() {
    return  currentP;
}