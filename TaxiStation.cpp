//
// Created by shani on 11/28/16.
//

#include "TaxiStation.h"
#include "MapCreator.h"
#define DRIVER_LOCATION 4
int globalSwitch;
/**
 * Empty constructor
 */
TaxiStation::TaxiStation(int x){
    server = new Server(x);
}
/**
 * Destructor to delete all the vectors
 */
TaxiStation::~TaxiStation() {
    server->endConn();
    for (int i=0;i<drivers.size();i++) {
        delete(drivers[i]);
    }
    for (int i=0;i<cabs.size();i++) {
        delete(cabs[i]);
    }
    for (int i=0;i<trips.size();i++){
        delete(trips[i]);
    }
    delete server;
}
/**
 * add driver to driver's vector
 * @param driver Driver object to be added
 */
void TaxiStation::addDriver(){

    drivers.push_back(server->setDriver());
    drivers[0]->setCab(getCabByID(drivers[0]->getCabID()));
    server->sendCab(cabs[0]);
    server->sendTrip(trips[0]);

}
/**
 * Add Cab to the cab's vector
 * @param cab Cab object to be added
 */
void TaxiStation::addCab(Cab* cab) {
    if (drivers.size() > 0) {
        server->sendCab(cab);
    }
    cabs.push_back(cab);

}
/**
 * add Trip to trip's vector
 * @param trip Trip to be added
 * @param gridSize size of grid for creation of mao
 * @param numObs number of obstacles expected in map
 * @param obsChain string of obstacles
 */
void TaxiStation::addTrip(Trip* trip) {
    /**
     * Use the MapCreator parser class to turn string inputs into
     * a Map object
     */
    MapCreator creator = MapCreator(trip->getGridSize(), trip->getEndX(),
                                    trip->getEndY(), trip->getStartX(), trip->getStartY(),
                                    trip->getNumObs(), trip->getObsChain());
    Map* m = creator.getMap();
    //Set map in Trip class
    trip->setMap(m);
    //drivers[0]->addTrip(trip);
    if (drivers.size() > 0) {
        server->sendTrip(trip);
    }
    trips.push_back(trip);
    pthread_t p1;
    int status = pthread_create(&p1, NULL, this->calculatePass, (void*)trip);
}

void* TaxiStation:: calculatePass(void* trip){
    Trip* t = (Trip*)trip;
    t->createPass();
    cout<<"shani is the best!!"<<endl;
    return NULL;
}

/**
 *
 * @param id - the id of the cab we want to find
 * @return the cab with the given id
 */
Cab* TaxiStation::getCabByID(int id) {
    for(int i = 0; i < cabs.size(); i++){
        if(cabs.at(i)->getCabID() == id){
            return cabs.at(i);
        }
    }
}
/**
 * Get Driver object by id
 * @param id input
 * @return Driver object
 */
Driver* TaxiStation::getDriverByID(int id) {
    std::vector<Driver*>::iterator it;
    for (it = drivers.begin(); it != drivers.end(); it++) {
        if ((*it)->getDriverID()==id) {
            return (*it);
        }
    }
}
/**
 * Get Cab object by id
 * @param id input
 * @return Cab object
 */
Cab* TaxiStation::getCab(int id) {
    std::vector<Cab*>::iterator it;
    for (it = cabs.begin(); it != cabs.end(); it++) {
        if ((*it)->getCabID()==id) {
            return (*it);
        }
    }
}
/**
 * prints the driver current location by id given
 * @param id input
 */
void TaxiStation::getDriverLocation(int id) {
    /**
     * location is saved uniqely in driver object
     */
        for (int i = 0; i < drivers.size(); i++) {
            if (drivers[i]->getDriverID() == id) {
                cout << (*drivers[i]->getLocation()) << endl;
                return;
            }
        }
    }

/**
 * Get Trip object by id
 * @param id input
 * @return Trip object
 */
Trip* TaxiStation::getTrip(int id) {
    for (int i = 0; i < trips.size(); i++) {
        if (trips[i]->getRideID() == id) {
            return trips[i];
        }
    }
}
/**
 * Start all trips added
 */
void TaxiStation::startAll() {
    int id;
    Driver* d;
    for (int i=0;i<drivers.size();i++) {
        for (int j=0;j<trips.size();j++) {
            //find if any driver arrived to desired place erlier
            d = findDriverAlreadyArrived(trips[j]->getStartX(),trips[j]->getStartY(),drivers[i]->getDriverID());
            if (d == NULL) {
                if (drivers[i]->getLocation()->getX() == trips[j]->getStartX() &&
                    drivers[i]->getLocation()->getY() == trips[j]->getStartY()) {
                    trips[j]->getNext();
                    //make a copy of trip current location after the ride is ended
                    p = trips[j]->getMapCurrent()->clone();
                    drivers[i]->setLocation(p);
                    drivers[i]->increaseSteps();
                    id = findTripNumInVector(trips[j]->getRideID());
                    delete (trips[j]);
                    //delete the trip from vector
                    trips.erase(trips.begin() + id);
                }
            } else {
                //A driver Arrived before
                trips[j]->getNext();
                //make a copy of trip current location after the ride is ended
                p = trips[j]->getMapCurrent()->clone();
                d->setLocation(p);
                d->increaseSteps();
                id = findTripNumInVector(trips[j]->getRideID());
                delete (trips[j]);
                //delete the trip from vector
                trips.erase(trips.begin() + id);
            }
            if (trips.size() == 0) {
                return;
            }
        }
    }
}
/**
 * Look for a driver which came for wanted spot before you
 * @param startX start of trip X
 * @param startY start of trip Y
 * @param id of driver we check about
 * @return NULL if no one was here before , Driver object else
 */
Driver* TaxiStation::findDriverAlreadyArrived(int startX,int startY,int id) {
    if (startX == 0 && startY == 0) {
        return NULL;
    }
    int min = getDriverByID(id)->getSteps();
    int idMin = getDriverByID(id)->getDriverID();
    //Check which driver had done the least steps to desired point
    for (int i=0;i<drivers.size();i++) {
        if (drivers[i]->getLocation()->getX() == startX && drivers[i]->getLocation()->getY() ==startY) {
            if (drivers[i]->getSteps()<min) {
                idMin = drivers[i]->getDriverID();
                min = drivers[i]->getSteps();
            }
        }
    }
    if (idMin != id) {
        return getDriverByID(idMin);
    } else {
        return NULL;
    }
}
/**
 * Method to find where the trip is located in the vector.
 * @param tripId id of trip
 * @return position of trip
 */
int TaxiStation::findTripNumInVector(int tripId) {
    for (int i=0;i<trips.size();i++) {
        if (trips[i]->getRideID() == tripId) {
            return i;
        }
    }
}
/**
 * handle the movement of the driver.
 * if the driver isn't in a middle of a trip - it assigning him a trip.
 * else - move him to the next point in the trip's pass.
 */
void TaxiStation::start() {
    clock.incTime();
    //assign
    if (drivers[0]->getIsDone() == true) {
        Trip* trip = matchTrip();
        if(trip == NULL){
            return;
        }
        drivers[0]->addTrip(trip);

        server->moveOn(drivers[0]->getLocation());
        return;
    }
        drivers[0]->doOneStep();
        server->moveOn(drivers[0]->getLocation());
        if(drivers[0]->getTrip()->isDone() == true) {
            int x = findTripNumInVector(drivers[0]->getTrip()->getRideID());
            trips.erase(trips.begin() + x);
            drivers[0]->deletetrip();
    }
}
/**
 *
 * @return the first driver in the driver's vector
 */
Driver* TaxiStation::getDriver() { return drivers[0];}
/**
 *
 * @return the trip that strats now. if there is not such one - return null.
 */
Trip* TaxiStation:: matchTrip(){
   // Trip* maxTrip = trips[0];
    for(int i = 0; i < trips.size(); i++){
        if(clock.getTime() == trips.at(i)->getTimeOfStart()){
            return trips.at(i);
        }

    }
    return NULL;
}
/**
 *
 * @return udp connection
 */
Server* TaxiStation::getConn() {
    return server;
}

void* TaxiStation::clientSwitch(void* tx1) {
    TaxiStation* tx = (TaxiStation*)tx1;
    bool isBeen = false;
    int id;
    if(isBeen == false) {
        switch (globalSwitch){
            case DRIVER_LOCATION: {
                cin >> id;
                tx->getDriverLocation(id);
                isBeen = true;
            }
            case 9: {
                tx->start();
                isBeen = true;
                break;
            }
        }
    }
}