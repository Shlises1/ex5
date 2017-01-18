//
// Created by ran on 29/12/16.
//

#ifndef SERVER_CLIENTOPS_H
#define SERVER_CLIENTOPS_H


#include "TaxiStation.h"
#include "StationInfo.h"
#include "Socket.h"
#include "Tcp.h"
#include "Udp.h"

class ClientOps {
private:
    Tcp* con;
    vector<Driver*>driverVec;
    vector<Trip*>tripVec;
    vector<Cab*>cabVec;
    StationInfo sInfo;
    vector<Node*>routeVec;
public:
    ClientOps(char* ipInput, int portInput);
    ~ClientOps();
    Socket* getConnection();
    void updateDriver(char* buffer,int size);
    void addCab(char* buffer,int size);
    void addTrip(char* buffer,int size);
    void addDriver(string dInput);
    void sendDriver();
    void getRoute();
};


#endif //SERVER_CLIENTOPS_H
