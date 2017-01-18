//
// Created by yanaiela on 12/10/16.
//
#include <iostream>
#include <stdlib.h>
#define STOP_ADVANCE '7'
#include "Udp.h"
#include "TaxiStation.h"
#include "StationInfo.h"
#include "ClientOps.h"
#include <unistd.h>



using namespace std;

int main(int argc, char *argv[]) {
    //ip address and port number as parameters
    ClientOps co = ClientOps(argv[1], atoi(argv[2]));
    //driver input
    string input;
    cin >> input;
    co.addDriver(input);
    co.sendDriver();
    //mission num will hold the expected  object type from server
    char missionNum[1024];
    //mission num will hold the expected  object from server
    char buffer[2048];
    co.getConnection()->reciveData(missionNum, sizeof(missionNum), -1);
    co.getConnection()->sendData("0",-1);
    while (1) {
        switch(missionNum[0]) {
            case '2':
            {
                //co.getConnection()->reciveData(buffer, sizeof(buffer), -1);
                //co.addTrip(buffer,sizeof(buffer));
                break;
            }
            case '3':
            {
                //co.getConnection()->reciveData(buffer, sizeof(buffer), -1);
                //co.addCab(buffer,sizeof(buffer));
                break;

            }
            case '7':
            {
                return 0;

            }
            case '9':
            {
                co.getConnection()->reciveData(buffer, sizeof(buffer), -1);
                co.getConnection()->sendData("0",-1);
                co.updateDriver(buffer,sizeof(buffer));
                break;
            }

        }
        co.getConnection()->reciveData(missionNum, sizeof(missionNum), -1);
        co.getConnection()->sendData("0",-1);
    }
}