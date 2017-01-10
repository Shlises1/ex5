#include <iostream>
#include "Node.h"
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node);
using namespace std;
/**
 * constructor
 */
Node::Node(){}

/**
 * destructor
 */
Node::~Node(){}
/**
 *
 * @return y
 */
int Node::getY() {}
/**
 *
 * @return x
 */
int Node ::getX() {}
/**
 * changes the x
 * @param x - the new x
 */
void Node::setX(int x) {}
/**
 * changes the y
 * @param y - the new y
 */
void Node::setY(int y) {}
/**
 * changes the father
 * @param p -the new father
 */
void Node::SetFather(Node* p) {}
/**
 *
 * @return the father
 */
Node* Node::getFather(){}
/**
 *
 * @return current node
 */
Node* Node::getCurrent() {}
/**
 *
 * @return true if this node is an obstcle, else return false.
 */
bool Node::getIsObstacle(){}
/**
*
* @param b - true if we want to make this node an obstacle, else false.
*/
void Node::setIsObstacle(bool b){}
/**
 *
 * @return the number of visits the node got
 */
int Node:: getIsVisited(){}
/**
 *
 * @param b - the number of visits the node got
 * @return the new number of visits the node got
 */
int Node:: setIsVisited(int b){}
/**
 *
 * @param other - the other node
 * @return true for match and false if not.
 */
bool Node::operator==(Node &other){}
