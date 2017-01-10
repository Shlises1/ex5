//
// Created by shani on 11/28/16.
//

#ifndef EX2_PASSENGERS_H
#define EX2_PASSENGERS_H


#include "Node.h"

class Passenger {
private:
    Node* sourcePoint;
    Node* destPoint;
public:
    /**
     * constructor
     * @param sourcePointInput - the source point given
     * @param destPointInput - the destination point given
     */
    Passenger(Node *sourcePoint, Node* destPoint);
    /**
     * constructor
     */
    Passenger();
    /**
     *
     * @return satisfaction
     */
    int getSatisfaction();
};


#endif //EX2_PASSENGERS_H
