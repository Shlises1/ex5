//
// Created by shani on 11/28/16.
//

#include "Passenger.h"
#include <stdlib.h>

/**
 * constructor
 */
Passenger::Passenger(){}
/**
 * constructor
 * @param sourcePointInput - the source point given
 * @param destPointInput - the destination point given
 */
Passenger::Passenger(Node *sourcePointInput, Node* destPointInput) {
    sourcePoint = sourcePointInput;
    destPoint = destPointInput;
}
/**
 *
 * @return satisfation
 */
int Passenger:: getSatisfaction(){
    return 4;
}