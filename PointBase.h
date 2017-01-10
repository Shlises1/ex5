//
// Created by ran on 15/11/16.
//

#ifndef EX1_POINT_H
#define EX1_POINT_H
#include <iostream>
//#include <iostream>
//#include <fstream>
//#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
/*#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>*/
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include "Node.h"

class PointBase : public Node {
private:
    int x;
    int y;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar, unsigned ) {
    //    boost::serialization::void_cast_register<Node, PointBase>();
         ar & boost::serialization::base_object<Node>(*this);

        ar & x;
        ar & y;

    }
public:
    /**
     * constractor
     * @param x - the x
     * @param y - the y
     */
    PointBase(int x, int y);
    /**
     * constractor
     */
    PointBase();
    virtual PointBase* clone() const;
    /**
     *
     * @return x
     */
    int getX();
    /**
     *
     * @return y
     */
    int getY();
    /**
     * changes the x
     * @param x1 - the new x
     */
    void setX(int x1);
    /**
     * changes the y
     * @param y1 - the new y
     */
    void setY(int y1);
    /**
   *
   * @param other - the other point
   * @return true for match and false if not.
   */
    bool operator==(PointBase &other);
    /**
    * operator overload for output
    * @param out - stream
    * @param point - point to be printed
    */
    friend  std:: ostream &operator<<(std::ostream& out,Node& point);
};


#endif //EX1_POINT_H