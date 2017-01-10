//
// Created by shani on 11/28/16.
//

#ifndef EX2_LUXURYCAB_H
#define EX2_LUXURYCAB_H


#include "Cab.h"

class LuxuryCab: public Cab {
private:
    Cab standardCab;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & boost::serialization::base_object<Cab>(*this);
        ar & standardCab;
    }

public:
    LuxuryCab(Cab input);

    bool IsLuxuryCab();
    int getSpeed();
};


#endif //EX2_LUXURYCAB_H
