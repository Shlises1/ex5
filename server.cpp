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


#define RECIEVE_DRIVER 1
#define RIDE 2
#define VEHICLE 3
#define DRIVER_LOCATION 4
#define STRART_DRIVING 6
#define EXIT 7
using namespace std;
int main(int argc, char **argv) {

  string gridSize, obs, obsChain = "";
    string input;
    int numObs, mission;
    int startX, startY;
    int endX, endY;
    int id;
    int numDrivers;
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
    Cab* cab;
    cin >> mission;
    while (1) {
        switch (mission) {
            case RECIEVE_DRIVER: {
                cin >> numDrivers;
                tx->addDriver();
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
                tx->getDriverLocation(id);
                break;
            }
            case STRART_DRIVING: {
                tx->startAll();
                break;
            }
            case 9: {
                tx->start();
                break;
            }
            case EXIT: {
                delete (tx);
                return 0;
            }
        }

        cin >> mission;
    }
}

