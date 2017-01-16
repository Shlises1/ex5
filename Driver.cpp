//
// Created by shani on 11/28/16.
//

#include "Driver.h"

/**
 * constractor
 */
Driver::Driver() {}
/**
 * constructor
 * @param ID1 - the driver's ID
 * @param age1 - the driver's age
 * @param materialStatus1 - the driver's material status
 * @param yearsOfExperience1 - the driver's years of experience
 * @param avgDestination1 - the driver's avg destination
 * @param cabID1 - the driver's cab ID
 */
Driver::Driver(int ID1, int age1, char materialStatus1, int yearsOfExperience1, int cabID1){
    ID = ID1;
    age = age1;
    materialStatus = materialStatus1;
    yearsOfExperience = yearsOfExperience1;
    cabID = cabID1;
    avgsatisfaction = 0;
    location = new PointHistory(PointBase(0,0));
    steps = 0;
    isTripDone = true;
    trip = NULL;
    firstStep = true;
    socketCom = -1;
}
/**
 * Destructor
 */
Driver::~Driver() {
    if(trip != NULL) {
        delete (trip);
    }
    if(location != NULL) {
       // delete (location);
    }
    return;
}
/**
 *
 * @return avg of satisfaction.
 */
double Driver:: getAvgSatisfaction(){ return avgsatisfaction;}
/**
 *
 * @return driver ID
 */
int Driver :: getDriverID(){ return ID;}
/**
 *
 * @return location
 */
Node* Driver:: getLocation(){ return location;}
/**
 * sests the location to a new one
 * @param p - the new location
 */
void Driver::setLocation(Node* p) {
    delete (location);
    location = p;
}
/**
 * steps discribes each trip made by driver
 */
void Driver::increaseSteps() {
    steps++;
}
/**
 *
 * @return number of trips made by driver
 */
int Driver::getSteps() { return steps;}
/**
 * move the driver one step in the pass of the trip
 */
void Driver::doOneStep() {
    if(firstStep == true){
        delete(location);
        location = NULL;
        firstStep = false;
    }
    location = trip->getNext();
    if (location->getX() == trip->getEndX() && location->getY() == trip->getEndY()) {
        isTripDone = true;
    }
}
/**
 * assign a new trip to the driver
 * @param newTrip - the new trip to assign
 */
void Driver::addTrip(Trip* newTrip){
    trip = newTrip;
    isTripDone = false;
    trip->setSpeed(cab->getSpeed());
}
/**
 *
 * @return the trip the driver is assign to
 */
Trip* Driver:: getTrip(){ return trip;}
/*
 * changes the status of the trip(done or not done)
 * true if the trip is done, else false
 */
void Driver::setTripDone(bool b){ isTripDone = b;}
/*
 * changes the trip
 */
void setTrip(Trip* newTrip){}
/**
 * changes the trip
 * @param newTrip - the new trip
 */
void Driver:: setTrip(Trip* newTrip){ trip = newTrip;}
/**
 * delete the trip when it's done
 */
void Driver::deletetrip() {
    location = new PointHistory(PointBase(location->getX(),location->getY()));
    delete trip;
    trip = NULL;
    isTripDone = true;
    firstStep = true;
}
/**
 * changes the driver's cab
 * @param newCab - the new cab
 */
void Driver::setCab(Cab *newCab) { cab = newCab; }
/**
 *
 * @return the driver's cab ID
 */
int Driver:: getCabID(){ return cabID; }
/**
 *
 * @return true if the trip the driver is doing is done, else return false
 */
bool Driver::getIsDone() { return isTripDone;}
int Driver::getSocketCom() { return socketCom;}
void Driver::setSocketCom(int socketC) {socketCom = socketC;}
Cab* Driver::getCab() { return cab;}
int Driver::getCounter() { return counter;}
void Driver::setCounter(int newCounter) {counter = newCounter;}