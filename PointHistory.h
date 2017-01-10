//
// Created by ran on 20/11/16.
//

#ifndef EX1_1_POINTHISTORY_H
#define EX1_1_POINTHISTORY_H

#include "Node.h"
#include "PointHistory.h"
#include "PointBase.h"

class PointHistory : public PointBase{
private:
    Node* father;
    PointBase current;
    bool isObstacle;
    int isVisited;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PointBase);
        //ar & boost::serialization::base_object<Node>(*this);
        ar & father;
        ar & current;
        ar & isObstacle;
        ar & isVisited;

    }
public:
    /**
     * copy constructor
     */
    virtual PointHistory* clone() const;
    /**
     * constructor
     * @param input
     */
    PointHistory(PointBase input);
    /**
     * constructor
     */
    PointHistory();
    /**
     * destractor
     */
    ~PointHistory();
    /**
     * changes the father generic node
     * @param fatherInput - the new father
     */
    void SetFather(Node* fatherInput);
    /**
     *
     * @return the father
     */
    Node* getFather();
    /**
     *
     * @return current point
     */
    Node* getCurrent();
    /**
     *
     * @return true if this node is an obstcle, else return false.
     */
    bool getIsObstacle();
    /**
    *
    * @param b - true if we want to make this node an obstacle, else false.
    */
    void setIsObstacle(bool b);
    /**
     *
     * @return the number of visits the node got
     */
    int getIsVisited();
    /**
     *
     * @param b - the number of visits the point got
     * @return the new number of visits the point got
     */
    int setIsVisited(int b);

};
#endif //EX1_1_POINTHISTORY_H