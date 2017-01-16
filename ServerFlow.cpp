#include <iostream>
#include "ParseFromString.h"
//#include "MapCreator.h"
#include "StationInfo.h"
#include <stdlib.h>
#include "TaxiStation.h"
#include <stdlib.h>
#include "Udp.h"
#include "Server.h"
#include "LuxuryCab.h"
#include <unistd.h>
//#include <mutex>
extern Clock globalClock;
extern int mission;
//extern bool isMissionDone;
extern vector<bool> isMissionDone;
//std::mutex mu;
#define RECIEVE_DRIVER 1
#define RIDE 2
#define VEHICLE 3
#define DRIVER_LOCATION 4
#define STRART_DRIVING 6
#define EXIT 7
#define MOVE_ON 9
//extern int mission;

using namespace std;
int main(int argc, char **argv) {
    globalClock = Clock();
    string gridSize, obs, obsChain = "";
    string input;
    int numObs;
    int startX, startY;
    int endX, endY;
    int id;
    int numDrivers;
   // int mission;
    std::getline(cin, gridSize);
    cin >> numObs;
    if (numObs > 0) {
        for (int i = 0; i < numObs; i++) {
            cin >> obs;
            obsChain += obs;
            obsChain += " ";
        }
    }
    StationInfo info = StationInfo();
    TaxiStation *tx;
    tx = new TaxiStation(atoi(argv[1]));
    Trip *t;
    cin >> mission;
    while (1) {
        switch (mission) {
            case RECIEVE_DRIVER: {
                cin >> numDrivers;
                //for (int i=0;i<numDrivers;i++) {
                    tx->addDrivers(numDrivers);
               // }
                break;
            }
            case RIDE: {
                cin >> input;
                t = info.getRide(input, startX, startY, endX, endY);
                t->setGridSize(gridSize);
                t->setNumObs(numObs);
                t->setObsChain(obsChain);
                tx->addTrip(t);
                break;
            }
            case VEHICLE: {
                cin >> input;
                tx->addCab(info.getVehicle(input));
                break;
            }
            case DRIVER_LOCATION: {
                cin >> id;
                tx->getDriverLocation(id);//
                break;
            }/*
            case STRART_DRIVING: {
                tx->startAll();
                break;
            }*/
            case MOVE_ON: {
                globalClock.incTime();
                tx->matchTrip();//
                for(int i = 0; i < isMissionDone.size(); i++) {
                    isMissionDone.at(i) = false;
                }
                break;
            }
            case EXIT: {
                for(int i = 0; i < isMissionDone.size(); i++) {
                    isMissionDone.at(i) = false;
                }
                delete (tx);
                return 0;
            }
        }

        cin >> mission;
    }
}


