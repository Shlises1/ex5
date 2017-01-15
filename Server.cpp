//
// Created by ran on 27/12/16.
//
#include "Server.h"
#include "Tcp.h"

/**
 * Constructor
 * @param port for server
 * @return
 */
Server::Server(int port) {
    soc = new Tcp(true,port);
    soc->initialize();
    flag = false;
//    descriptorCom = soc->getDescriptor();
}
/**
 * Destructor
 */
Server::~Server(){
    delete soc;
}
/**
 * set driver object sent from client
 * @return
 */
Driver* Server::setDriver(int socComu) {
    char buffer[1024];
    soc->reciveData(buffer,sizeof(buffer),socComu);
    string serial_str (buffer,sizeof(buffer));
    Driver* driver;
    boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driver;
    return driver;


}
/**
 * Send trip object to client
 * @param trip
 */
void Server::sendTrip(Trip* trip) {
    //tell client that a trip is about to be sent
    soc->sendData("2",descriptorCom);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << trip;
    s.flush();
    soc->sendData(serial_str,descriptorCom);


}
/**
 * Send cab object to client
 * @param cab
 */
void Server::sendCab(Cab* cab) {
    //tell client that a cab is about to be sent
    soc->sendData("3",descriptorCom);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << cab;
    s.flush();
    soc->sendData(serial_str,descriptorCom);
}
/**
 * send client current driver location
 * @param loc current location of driver
 */
void Server::moveOn(Node* loc, int soketComu) {
    //tell client that his driver location needs to be updated
    soc->sendData("9",soketComu);
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << loc;
    s.flush();
    soc->sendData(serial_str,soketComu);
}
/**
 * Client needs to close connection
 */
void Server::endConn(int descriptor) {
    //tell client that connection needs to be closed
    soc->sendData("7",descriptor);
}
void Server::getDriver() {
    char buffer[1024];
    soc->reciveData(buffer, sizeof(buffer),descriptorCom);
}
void Server::printLocation() {
    cout<<*location<<endl;
}
Socket* Server::getConnection() {
    return soc;
}