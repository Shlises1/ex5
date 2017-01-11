//
// Created by shani on 11/28/16.
//

#ifndef EX2_STATIONSTATION_H
#define EX2_STATIONSTATION_H

#include <array>
#include <pthread.h>
using namespace std;

#include <vector>
#include "Driver.h"
#include "Cab.h"
#include "Trip.h"
#include "Map.h"
#include "Clock.h"
#include "Server.h"
#include <map>

class TaxiStation {
private:
    vector<Driver*> drivers;
    vector<Node*> Location;
    vector<Cab*> cabs;
    vector<Trip*> trips;
    Node *p;
    int findTripNumInVector(int tripId);
    Driver* findDriverAlreadyArrived(int startX,int startY,int id);
    Clock clock;
    Server* server;
public:
    /**
     * constructor
     */
    TaxiStation(int x);
    /**
     * destructor
     */
    ~TaxiStation();
    /**
     * add driver to driver's vector
     * @param driver Driver object to be added
     */
    void addDrivers(int numOfDrivers);
    /**
     * Add Cab to the cab's vector
     * @param cab Cab object to be added
     */
    void addCab(Cab* cab);
    /**
     * add Trip to trip's vector
     * @param trip Trip to be added
     * @param gridSize size of grid for creation of mao
     * @param numObs number of obstacles expected in map
     * @param obsChain string of obstacles
     */
    void addTrip(Trip* trip);
    /**
      * Get Driver object by id
      * @param id input
      * @return Driver object
      */
    Driver* getDriverByID(int id);
    /**
     * Get Cab object by id
     * @param id input
     * @return Cab object
     */
    Cab* getCab(int id);
    /**
     * Get Trip object by id
     * @param id input
     * @return Trip object
     */
    Trip* getTrip(int id);
    /**
     * prints the driver current location by id given
     * @param id input
     */
    void getDriverLocation(int id);
    /**
     * Start all trips added
     */
    void startAll();
    /**
     * handle the movement of the driver.
     * if the driver isn't in a middle of a trip - it assigning him a trip.
     * else - move him to the next point in the trip's pass.
     */
    void start();
    /**
     *
     * @return the first driver in the driver's vector
     */
    Driver* getDriver();
    /**
     *
     * @return the trip that strats now. if there is not such one - return null.
     */
    Trip* matchTrip();
    /**
     *
     * @return udp connection
     */
    Server* getConn();
    /**
     *
     * @param id - the id of the cab we want to find
     * @return the cab with the given id
     */
    Cab* getCabByID(int id);
    static void* calculatePass(void* trip);
    static void* clientSwitch(void* tx);
};


#endif //EX2_STATIONSTATION_H
