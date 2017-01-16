//
// Created by shani on 11/28/16.
//

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include <array>
#include "Node.h"
#include "Trip.h"
#include "Cab.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
enum MaterialStatus{S, M, D, W};
class Driver {
private:
    Trip* trip;
    Node* location;
    int ID;
    int age;
    string materialStatus;
    int yearsOfExperience;
    double avgsatisfaction;
    int cabID;
    int steps;
    bool isTripDone;
    Cab* cab;
    enum material {S,M,D,W};
    bool firstStep;
    int socketCom;
    int counter;
    //serialize
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & ID;
        ar & age;
        ar & materialStatus;
        ar & yearsOfExperience;
        ar & cabID;
        ar & isTripDone;
        ar & location;
        ar & firstStep;
    }
public:
    /**
     * constructor
     */
    Driver();
    /**
     * destructor
     */
    ~Driver();
    /**
     * constructor
     * @param ID1 - the driver's ID
     * @param age1 - the driver's age
     * @param materialStatus1 - the driver's material status
     * @param yearsOfExperience1 - the driver's years of experience
     * @param avgDestination1 - the driver's avg destination
     * @param cabID1 - the driver's cab ID
     */
    Driver(int ID1, int age1, char materialStatus1, int yearsOfExperience1, int cabID1);
    /**
     *
     * @return avg of satisfaction
     */
    double getAvgSatisfaction();
    /**
     *
     * @return driver ID
     */
    int getDriverID();
    /**
     *
     * @return current location of the driver
     */
    Node* getLocation();
    /**
     * sests the location to a new one
     * @param p - the new location
     */
    void setLocation(Node* p);
    /**
     * steps discribes each trip made by driver
     */
    void increaseSteps();
    /**
     *
     * @return number of trips made by driver
     */
    int getSteps();
    /**
     * move the driver one step in the pass of the trip
     */
    void doOneStep();
    /**
     * assign a new trip to the driver
     * @param newTrip - the new trip to assign
     */
    void addTrip(Trip* newTrip);
    /**
     * delete the trip when it's done
     */
    void deletetrip();
    /**
     *
     * @return the trip the driver is assign to
     */
    Trip* getTrip();
    /*
     * changes the status of the trip(done or not done)
     * true if the trip is done, else false
     */
    void setTripDone(bool b);
    /*
     * changes the trip
     */
    void setTrip(Trip* newTrip);
    /**
     * changes the driver's cab
     * @param newCab - the new cab
     */
    void setCab(Cab* newCab);
    /**
     *
     * @return the driver's cab ID
     */
    int getCabID();
    /**
     *
     * @return true if the trip the driver is doing is done, else return false
     */
    bool getIsDone();
    int getSocketCom();
    void setSocketCom(int socketC);
    Cab* getCab();
    int getCounter();
    void setCounter(int newCounter);
};


#endif //EX2_DRIVER_H