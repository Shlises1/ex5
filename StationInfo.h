//
// Created by shani on 11/28/16.
//

#ifndef EX2_STATIONINFO_H
#define EX2_STATIONINFO_H
using namespace std;
#include <vector>

#include "Trip.h"
#include "Driver.h"
#include "Passenger.h"
#include "Cab.h"
#include "TaxiStation.h"
#include "ParseFromString.h"

class StationInfo {
private:
    vector<Trip> trips;
    vector<Driver> drivers;
    vector<Passenger> passengers;
    vector<Cab> cabs;
    StationInfo* stationInfo;
    ParseFromString parseFromString;

public:
    /**
     * construction
     */
    StationInfo();
    /**
     * constructor
     * @param t - vector of trips
     * @param d - vector of drivers
     * @param p - vector of passengers
     * @param c - vector of cabs
     * @param st - station information
     * @return
     */
    StationInfo( vector<Trip> t,  vector<Driver> d,  vector<Passenger>p,
                 vector<Cab> c, StationInfo* st);
    /**
     *
     * @return a station from a text
     */
    Driver* getDriver(string input);
    /**
     * Method which get string details of ride and returns a Trip object
     * @param input string input of ride
     * @param startX X start
     * @param startY Y start
     * @param endX X end
     * @param endY Y end
     * @return Trip object
     */
    Trip* getRide(string input,int startX,int startY,int endX,int endY);
    /**
     * Method which gets string input of Cab object details and return the accordingly Cab object
     * @param input Cab details
     * @return Cab object
     */
    Cab* getVehicle(string input);
};


#endif //EX2_STATIONINFO_H
