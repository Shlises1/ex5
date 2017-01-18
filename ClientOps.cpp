//
// Created by ran on 29/12/16.
//

#include "ClientOps.h"
#include "MapCreator.h"

ClientOps::ClientOps(char* ipInput, int portInput) {
    sInfo = StationInfo();
    string ip = ipInput;
    con = new Tcp(false, portInput);
    con->setIP(ipInput);
    con->initialize();
}
/**
 * destructor for class
 */
ClientOps::~ClientOps() {
    for (int i=0;i<driverVec.size();i++) {
        delete driverVec[i];
        driverVec.erase(driverVec.begin()+i);
    }
    for (int i=0;i<tripVec.size();i++) {
        delete tripVec[i];
        tripVec.erase(tripVec.begin()+i);
    }
    for (int i=0;i<cabVec.size();i++) {
        delete cabVec[i];
        cabVec.erase(cabVec.begin()+i);
    }
    //close conneection
    delete currPoint;
    delete  con;
}
/**
 * connection getter
 * @return Socket connection
 */
Socket* ClientOps::getConnection() {//
    return con;
}
Node* ClientOps::getCurrentPoint() {

}
/**
 * set current driver location according to server
 * @param buffer location object
 * @param size
 */
void ClientOps::updateDriver(char *buffer,int size) {
    std::string serial_str (buffer, size);

    //unserialize the location
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> currPoint;
   // delete loc->getFather();
    //driverVec[0]->setLocation(loc);

}
/**
 * add trip to driver awaiting trips vector
 * @param buffer trip object
 * @param size
 */
void ClientOps::addTrip(char *buffer, int size) {
    string serial_str (buffer, size);
    Trip* trip;

    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> trip;
    tripVec.push_back(trip);
}
/**
 * add cab to driver awaiting cabs vector
 * @param buffer cab object
 * @param size
 */
void ClientOps::addCab(char* buffer,int size) {
    std::string serial_str (buffer, size);
    Cab* cab;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> cab;
    cabVec.push_back(cab);

}
/**
 * add driver to vector of drivers
 * @param dInput
 */
void ClientOps::addDriver(string dInput) {
    Driver* d = sInfo.getDriver(dInput);
    driverVec.push_back(d);
}
/**
 * send driver to server
 */
void ClientOps::sendDriver() {
    cout<<"befor sending driver"<<endl;
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << driverVec[0];
    s.flush();
    con->sendData(serial_str,-1);
    cout<<"after sending driver"<<endl;
}