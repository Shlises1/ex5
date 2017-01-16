//
// Created by shani on 11/28/16.
//

#include <mutex>
#include "TaxiStation.h"
#include "MapCreator.h"
int mission;
bool isMissionDone;
Clock globalClock;
pthread_mutex_t mutexLock;
#define EXIT 7


/**
 * constructor
 */
TaxiStation::TaxiStation(int x){
    server = new Server(x);
}
/**
 * Destructor to delete all the vectors
 */
TaxiStation::~TaxiStation() {
  //  server->endConn();
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
void TaxiStation::addDrivers(int numOfDrivers) {
    numberOfDrivers = numOfDrivers;
    pthread_mutex_init(&mutexLock,0);
    for(int i =0; i < numOfDrivers; i++) {
        dataThread* dThread = new dataThread;
        int x = server->getConnection()->accept_();
        drivers.push_back(server->setDriver(x));
        drivers[i]->setSocketCom(x);
        dThread->tx = this;
        dThread->cDescriptor = x;
        dThread->driverId = drivers[i]->getDriverID();
        //dThread->finishedOp =false;
        //structVec.push_back(dThread);
       // pthread_t thread[numOfDrivers];
        pthread_t rThr;
        for (int i=0;i<numOfDrivers;i++) {
            int status = pthread_create(&rThr,NULL,flow,dThread);
            if (status)
            {
                cout<<"error opening thread"<<endl;
                return;
            }
        }

        drivers[i]->setCab(getCabByID(drivers[i]->getCabID()));
        //server->sendCab(drivers[i]->getCab(), drivers[i]->getSocketCom());
        //server->sendTrip(trips[0]);
    }

}
/**
 * Add Cab to the cab's vector
 * @param cab Cab object to be added
 */
void TaxiStation::addCab(Cab* cab) {
    /*
    if (drivers.size() > 0) {
        server->sendCab(cab);
    }*/
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
    trips.push_back(trip);
    trip->threadCalcPass();
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
void TaxiStation::start(int driverID) {
    cout<<driverID<<"got to start"<<endl;
    Driver* driver = getDriverByID(driverID);

  //  clock.incTime();
    //assign
    if (driver->getIsDone() == true) {
        pthread_mutex_lock(&mutexLock);
        Trip* trip = matchTrip();
        if(trip == NULL){
            pthread_mutex_unlock(&mutexLock);
            return;
        }
        server->sendTrip(trip,driver->getSocketCom());
        server->sendCab(driver->getCab(),driver->getSocketCom());
        pthread_mutex_unlock(&mutexLock);
        driver->addTrip(trip);
        //server->moveOn(driver->getLocation(), driver->getSocketCom());

        cout<<driverID<<"assigned"<<endl;
        return;
    }
        driver->doOneStep();
        server->moveOn(driver->getLocation(), driver->getSocketCom());
        cout<<driverID<<"moved one step"<<endl;
        if(driver->getTrip()->isDone() == true) {
         //   int x = findTripNumInVector(driver->getTrip()->getRideID());
         //   trips.erase(trips.begin() + x);
            driver->deletetrip();
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
        if(globalClock.getTime() == trips.at(i)->getTimeOfStart()){
            Trip* t = trips.at(i);
            int x = findTripNumInVector(t->getRideID());
            trips.erase(trips.begin() + x);
            return t;
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
void* TaxiStation::flow(void *threadData){//
    dataThread* td  =(dataThread*)threadData;
    TaxiStation* tx = td->tx;
    int id = td->driverId;
    int threadCounter=0;
    while (1) {
        if(isMissionDone == false) {//
            switch (mission) {
                /*
                case DRIVER_LOCATION: {
                    tx->getDriverLocation(id);
                    isMissionDone = true;
                    break;
                }*/
                case 9: {
                    cout<<id<<"got to static flow"<<endl;
                    tx->start(id);
                    threadCounter++;
                    if (threadCounter == tx->numberOfDrivers) {
                        isMissionDone = true;
                    }
                    break;
                }
                case EXIT: {
                    tx->getConn()->endConn(td->cDescriptor);
                    delete td;
                    pthread_exit(NULL);
                }
            }
        }
        //?
       // cin >> mission;
    }

}