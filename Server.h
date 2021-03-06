//
// Created by ran on 27/12/16.
//

#ifndef EX3_SERVER_H
#define EX3_SERVER_H
#include <boost/serialization/export.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "Udp.h"
#include "Cab.h"
#include "Trip.h"
#include "ParseFromString.h"
#include "PointHistory.h"
#include "Driver.h"




class Server {
private:
    int driverId;
    Socket* soc;
    Node* location;
    bool flag;
    vector<Trip*>serverTrips;
    vector<Cab*>serverCabs;
    Node* goalPoint;
public:
    Server(int port);
    ~Server();
    Socket* getConnection();
    Driver* setDriver();
    void sendTrip(Trip* trip);
    void sendCab(Cab* cab);
    void moveOn(Node* loc);
    void endConn();
    void getDriver();
    void printLocation();
};
#endif //EX3_SERVER_H
