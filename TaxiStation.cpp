//
// Created by shani on 11/28/16.
//

#include <mutex>
#include "TaxiStation.h"
#include "MapCreator.h"
 int mission;
//bool isMissionDone;
 Clock globalClock;
 vector<bool> isMissionDone;//
 int numOfMoveOn;
 std::vector<int> printHour;
 std::vector<int>printId;
 bool keepMove;
 extern vector<pthread_t> tVec;
 std::mutex mu;
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
  //  pthread_mutex_init(&mutexLock,0);
    for(int i =0; i < numOfDrivers; i++) {
        dataThread* dThread = new dataThread;
        int x = server->getConnection()->accept_();
        drivers.push_back(server->setDriver(x));
        drivers[i]->setSocketCom(x);
        drivers[i]->setCounter(0);
        drivers[i]->setCab(getCabByID(drivers[i]->getCabID()));
        dThread->tx = this;
        dThread->cDescriptor = x;
        dThread->driverId = drivers[i]->getDriverID();
        dThread->i = i;
//        isMissionDone.push_back(true);
        pthread_t newThread;
        int status = pthread_create(&newThread,NULL,flow,dThread);
        tVec.push_back(newThread);
        if (status)
        {
            cout<<"error opening thread"<<endl;
            return;
        }

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
//    }

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
    if (driver->getIsDone() == false) {

        if(driver->getTrip()!= NULL) {
            //means that it has just assigned to a trip and doedn't need to move one step
           /* if(driver->getCounter() == 1){
                driver->setCounter(2);
                return;
            }*/
            if (driver->getTrip()->checkIfThreadIsDone()) {
                driver->doOneStep();
                server->moveOn(driver->getLocation(), driver->getSocketCom());
                cout << driverID << "moved one step" << endl;
            }
            if (driver->getTrip()->isDone() == true) {
                int x = findTripNumInVector(driver->getTrip()->getRideID());
                trips.erase(trips.begin() + x);
                driver->deletetrip();
            }
        }
    }
}
/*void TaxiStation::IncreaseAll() {
    for (int i=0;i<drivers.size();i++) {
        if (drivers[i]->getTrip()->checkIfThreadIsDone())
        drivers[i]->doOneStep();
}*/


/**
 *
 * @return the first driver in the driver's vector
 */
Driver* TaxiStation::getDriver(int i) { return drivers[i];}
/**
 *
 * @return the trip that strats now. if there is not such one - return null.
 */
void TaxiStation:: matchTrip(int counter) {

   cout<<"matchTrip"<<endl;
    for(int i = 0; i < trips.size(); i++){
        if(counter == trips[i]->getTimeOfStart()){
            for(int j = 0; j < drivers.size();j++) {
                if(drivers[j]->getIsDone() == true && !trips[i]->taken) {
                    if ((trips[i]->getStartX() == drivers[j]->getLocation()->getX()) &&
                            (trips[i]->getStartY() == drivers[j]->getLocation()->getY())) {
                        drivers[j]->addTrip(trips[i]);
                        trips[i]->taken = true;

                        //  trips.erase(trips.begin() +i);
//                    isMissionDone[j] = true;
                        drivers[j]->setCounter(1);
                        cout << drivers[j]->getDriverID() << "assigned" << endl;
                    }
                    break;
                } else {
                   // drivers.at(j)->setDoOneStepFlag(false);
                }
            }
        }
    }

  //  return NULL;
}
/**
 *
 * @return udp connection
 */
Server* TaxiStation::getConn() {
    return server;
}
void* TaxiStation::flow(void *threadData){
    dataThread* td  =(dataThread*)threadData;
    TaxiStation* tx = td->tx;
    int counter=0;
    int id = td->driverId;
    int i = td->i;
    while (true) {
        while (!keepMove) {
            while (counter < numOfMoveOn) {
                // if(isMissionDone.at(i) == false) {
                if (printHour.size() > 0 && printHour[0] == counter) {
                    if (printId.size() > 0 && id == printId[0]) {
                        cout << "ENTER PRINT" << endl;
                        tx->getDriverLocation(id);
                        printId.erase(printId.begin());
                        printHour.erase(printHour.begin());
                    }
                }
                cout << id << "got to static flow" << endl;
                tx->start(id);
                counter++;
                tx->matchTrip(counter);

                //     }
                /*if (mission == EXIT) {
                    tx->getConn()->endConn(td->cDescriptor);
                    delete td;
                    pthread_exit(NULL);
                }*/
            }
            tx->getConn()->endConn(td->cDescriptor);
            delete td;
            pthread_exit(NULL);
        }
    }
}




