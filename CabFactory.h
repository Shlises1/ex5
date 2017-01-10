//
// Created by shani on 11/28/16.
//

#ifndef EX2_CABFACTORY_H
#define EX2_CABFACTORY_H

#include <array>

using namespace std;

#include "Cab.h"

class CabFactory {
private:
    string cabinfo();

public:
    /**
     * Constructor
     */
    CabFactory();
    /**
     *
     * @return cab object after analyzing input details
     */
    Cab getCab();
};


#endif //EX2_CABFACTORY_H
