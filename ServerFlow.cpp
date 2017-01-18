#include <iostream>
#include "ParseFromString.h"
//#include "MapCreator.h"
#include "StationInfo.h"
#include "Tcp.h"
#include <stdlib.h>
#include "TaxiStation.h"
#include <stdlib.h>
#include "Server.h"
#include "LuxuryCab.h"
#include <unistd.h>
#include <pthread.h>
//#include <mutex>
extern Clock globalClock;
 extern int mission;
 extern std::vector<int> printHour;
 extern std::vector<int>printId;
extern  int numOfMoveOn;
//extern bool isMissionDone;
extern vector<bool> isMissionDone;
extern bool keepMove;
extern vector<pthread_t> tVec;
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
    keepMove = true;
    //int numOfMoveOn;
    numOfMoveOn++;
    // std::vector<int> printHour;
    // std::vector<int>printId;

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
                cout<<"press 1 to enter driver"<<endl;
                cin >> numDrivers;
                //for (int i=0;i<numDrivers;i++) {
                    tx->addDrivers(numDrivers);
                cout<<"after add driver main thread"<<endl;
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
                //if (tx->getDriverByID(id)->getTrip()->checkIfThreadIsDone())
                printHour.push_back(globalClock.getTime());
                printId.push_back(id);
             //   tx->getDriverLocation(id);//
                break;//
            }/*
            case STRART_DRIVING: {
                tx->startAll();
                break;
            }*/
            case MOVE_ON: {
                cout<<"9 on main thread"<<endl;
                globalClock.incTime();
                numOfMoveOn++;
//                for(int i = 0; i < isMissionDone.size(); i++) {
          //          isMissionDone.at(i) = false;
         //       }
                //tx->matchTrip();
                break;
            }
            case EXIT: {
          //      for(int i = 0; i < isMissionDone.size(); i++) {
           //         isMissionDone.at(i) = false;
           //     }
                keepMove = false;
                for (int i=0;i<tVec.size();i++) {
                    pthread_join(tVec[i],NULL);
                }

                delete (tx);
                return 0;
            }
        }

        cin >> mission;
    }
}


