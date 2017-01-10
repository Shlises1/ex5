//
// Created by shani on 12/27/16.
//

#ifndef EX4_CLIENT_H
#define EX4_CLIENT_H

#include "Trip.h"

using namespace std;

class Client{
private:
    Trip trip;
    Cab cab;
public:
    Client();
    void getVehicle();
    void getTrip();
    void sendDriverID();
};
#endif //EX4_CLIENT_H
