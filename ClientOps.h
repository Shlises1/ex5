//
// Created by ran on 29/12/16.
//

#ifndef SERVER_CLIENTOPS_H
#define SERVER_CLIENTOPS_H


#include "TaxiStation.h"
#include "StationInfo.h"
#include "Socket.h"

class ClientOps {
private:
    Udp* con;
    vector<Driver*>driverVec;
    vector<Trip*>tripVec;
    vector<Cab*>cabVec;
    StationInfo sInfo;
public:
    ClientOps(char* ipInput, int portInput);
    ~ClientOps();
    Socket* getConnection();
    void updateDriver(char* buffer,int size);
    void addCab(char* buffer,int size);
    void addTrip(char* buffer,int size);
    void addDriver(string dInput);
    void sendDriver();
};


#endif //SERVER_CLIENTOPS_H
