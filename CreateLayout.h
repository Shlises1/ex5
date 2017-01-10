//
// Created by shani on 11/28/16.
//

#ifndef EX2_CREATEMAP_H
#define EX2_CREATEMAP_H


#include "Map.h"

class CreateMap {
public:
    /**
     * constructor
     */
    CreateMap();
    /**
     * creates a layout
     * @return a new map
     */
    Map createLayout();
    /**
     * creates a cab station
     */
    void createStation();

};


#endif //EX2_CREATEMAP_H
