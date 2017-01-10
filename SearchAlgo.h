//
// Created by ran on 04/12/16.
//

#ifndef EX2_SEARCHALGO_H
#define EX2_SEARCHALGO_H

//#include <gtest/gtest-typed-test.h>
#include "Node.h"

using namespace std;
class SearchAlgo{
public:
    /**
     * constructor
     */
    SearchAlgo();
    //print path of map
    virtual void printPath();
    //get next element
    virtual Node* getNext();
};







#endif //EX2_SEARCHALGO_H
