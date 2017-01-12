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
#include "Tcp.h"
#include "Cab.h"
#include "Trip.h"
#include "ParseFromString.h"
#include "PointHistory.h"
#include "Driver.h"




class Server {
private:
    int driverId;
    Tcp* soc;
    Node* location;
    bool flag;
    int descriptorCom;
public:
    Server(int port);
    ~Server();
    Socket* getConnection();
    Driver* setDriver(int socComu);
    void sendTrip(Trip* trip);
    void sendCab(Cab* cab, int socComunication);
    void moveOn(Node* loc);
    void endConn();
    void getDriver();
    void printLocation();
};
#endif //EX3_SERVER_H
