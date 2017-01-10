//
// Created by shani on 11/28/16.
//

#include "StationInfo.h"
#include "LuxuryCab.h"
#define LUXURY 2
/**
 * Empty constructor
 */
StationInfo::StationInfo(){}
/**
 * constructor
 * @param t - vector of trips
 * @param d - vector of drivers
 * @param p - vector of passengers
 * @param c - vector of cabs
 * @param st - station information
 * @return
 */
StationInfo::StationInfo( vector<Trip> t,  vector<Driver> d,  vector<Passenger>p,
                          vector<Cab> c, StationInfo* st){}
/**
 *Method which gets string input with driver details and returns the accordingyl driver object
 * @return Driver object
 */
Driver* StationInfo:: getDriver(string input){
    parseFromString = ParseFromString(input);
    int id,age;
    char status;
    int experience,vehicleId;
    parseFromString.parse(',',&id,&age);
    parseFromString.parse(&status);
    parseFromString.parse(',',&experience,&vehicleId);
    return new Driver(id,age,status,experience,vehicleId);

}
/**
 * Method which gets string input of Cab object details and return the accordingly Cab object
 * @param input Cab details
 * @return Cab object
 */
Cab* StationInfo::getVehicle(string input) {
    parseFromString = ParseFromString(input);
    int id,cabType;
    char manufacturer,color;
    parseFromString.parse(',',&id,&cabType);
    parseFromString.parse(&manufacturer);
    parseFromString.parse(&color);
    /*
    if (cabType ==LUXURY) {
        return new LuxuryCab(Cab(id, cabType, manufacturer, color));
    } else {
     */
        return new Cab(id, cabType, manufacturer, color);
   // }

}
/**
 * Method which get string details of ride and returns a Trip object
 * @param input string input of ride
 * @param startX X start
 * @param startY Y start
 * @param endX X end
 * @param endY Y end
 * @return Trip object
 */
Trip* StationInfo::getRide(string input,int startX,int startY,int endX,int endY) {
    int id;
    int numPass,taarif;
    int timeOfStart;
    parseFromString = ParseFromString(input);
    parseFromString.parse(',',&id,&startX);
    parseFromString.parse(',',&startY,&endX);
    parseFromString.parse(',',&endY,&numPass);
    parseFromString.parse(',',&taarif);
    parseFromString.parse(',',&timeOfStart);
    return new Trip(id,startX,startY,endX,endY,numPass,taarif,timeOfStart);
}
