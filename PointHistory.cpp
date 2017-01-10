#include "PointHistory.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

using namespace std;
/**
 * constructor
 * @param input - the point
 */
PointHistory::PointHistory(PointBase input):PointBase(input.getX(),input.getY()) {
    current = input;
    isObstacle = false;
    isVisited = 0;
    father=NULL;
}
/**
 * constructor
 */
PointHistory::PointHistory(){}
/**
 * destructor
 */
PointHistory::~PointHistory() {}
/**
 * copy constructor
 */
PointHistory* PointHistory::clone() const
{
    return new PointHistory(*this);
}
/**
 * changes the father generic node
 * @param fatherInput - the new father
 */
void PointHistory:: SetFather(Node* fatherInput) {
    father = fatherInput;
}
/**
 *
 * @return current point
 */
Node* PointHistory:: getCurrent(){
    return (Node*)&current;
}
/**
 *
 * @return the father
 */
Node* PointHistory:: getFather() {
    return father;
}
/**
 *
 * @return true if this node is an obstcle, else return false.
 */
bool PointHistory:: getIsObstacle(){
    return isObstacle;
}
/**
*
* @param b - true if we want to make this node an obstacle, else false.
*/
void PointHistory::setIsObstacle(bool b){
    isObstacle = b;
}
/**
 *
 * @return the number of visits the node got
 */
int PointHistory:: getIsVisited(){
    return isVisited;
}
/**
 *
 * @param b - the number of visits the point got
 * @return the new number of visits the point got
 */
int PointHistory:: setIsVisited(int b){
    isVisited = b;
}
BOOST_CLASS_EXPORT(PointHistory)


