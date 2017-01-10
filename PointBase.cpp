//
// Created by ran on 15/11/16.
//

#include "PointBase.h"
#include <boost/serialization/export.hpp>
using namespace std;
/**
 * constractor
 * @param x1 - the x
 * @param y1 - the y
 */
PointBase::PointBase(int x1, int y1):Node() {
    x = x1;
    y = y1;
}
/**
 * constractor
 */
PointBase::PointBase(){}
PointBase* PointBase::clone() const
{
    return new PointBase(*this);
}
/**
 *
 * @return x
 */
int PointBase::getX() {
    return x;
}
/**
 *
 * @return y
 */
int PointBase::getY() {
    return y;
}
/**
 * changes the x
 * @param x1 - the new x
 */
void PointBase::setX(int x1) {
    x = x1;
}
/**
 * changes the y
 * @param y1 - the new y
 */
void PointBase::setY(int y1) {
    y = y1;
}
/**
     *
     * @param other - the other point
     * @return true for match and false if not.
     */
bool PointBase:: operator==(PointBase &other) {
    return ((x==other.getX()) && (y==other.getY()));
}
    /**
    * operator overload for output
    * @param out - stream
    * @param point - point to be printed
    */
ostream &operator<<(std::ostream& out,Node& point) {
    out<<"("<<point.getX()<<","<<point.getY()<<")";
}
BOOST_CLASS_EXPORT(PointBase);

