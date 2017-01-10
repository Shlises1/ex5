//
// Created by ran on 21/11/16.
//

#ifndef EX1_2_POINT_H
#define EX1_2_POINT_H

#include <iostream>
#include <boost/serialization/assume_abstract.hpp>
//#include <boost/serialization/base_object.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;
class Node
{
private:

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {

    }

    

    public:
        /**
         * constructor
         * @return
         */
         Node();
        virtual Node* clone() const = 0;
        /**
         * destructor
         */
        virtual ~Node();
        /**
         *
         * @return x
         */
        virtual int getX();
        /**
         *
         * @return y
         */
        virtual int getY();
        /**
         * changes the x
         * @param x - the new x
         */
        virtual void  setX(int x);
        /**
         * changes the new y
         * @param y - the new y
         */
        virtual void setY(int y);
        /**
         * changes the father
         * @param p - the new father
         */
        virtual void SetFather(Node* p);
        /**
         *
         * @return the father
         */
        virtual Node* getFather();
        /**
         *
         * @return current node
         */
        virtual Node* getCurrent();
        /**
         *
         * @param other - the other node
         * @return true for match and false if not.
         */
        virtual bool operator==(Node &other);
        /**
         *
         * @return true if this node is an obstcle, else return false.
         */
        virtual bool getIsObstacle();
        /**
         *
         * @param b - true if we want to make this node an obstacle, else false.
         */
        virtual void setIsObstacle(bool b);
        /**
        *
        * @return the number of visits the node got
        */
        virtual int getIsVisited();
        /**
         *
         * @param b - the number of visits the node got
         * @return the new number of visits the node got
         */
        virtual int setIsVisited(int b);
    };
    /**
     * operator overload for output
     * @param out
     * @param point
     */

    std:: ostream &operator<<(std::ostream& out,Node& point);

#endif //EX1_2_POINT_H