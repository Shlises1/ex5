//
// Created by shani on 11/28/16.
//

#ifndef EX2_CAB_H
#define EX2_CAB_H
#include <vector>
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
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#define SPEED 1
class Cab {

protected:
    char color;
    int cabID;
    double numOfKMPassed;
    char manufacturer;
    double taarif;
    int taxiType;
private:
    //serialize cab
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & color;
        ar & cabID;
        ar & numOfKMPassed;
        ar & taxiType;
        ar & manufacturer;
    }
public:

    /**
    * constractor
    * @param cabIDInput - the cab's ID
    * @param taxiTypeInput - the type of the cab
    * @param manufacturerInput - char of the cab's manufacturer first letter
    * @param colorInput - char of the cab's color first letter
    */
    Cab(int cabIDInput,int taxiTypeInput, char manufacturerInput, char colorInput);
/**
 * constructor
 */
    Cab();
/**
 * destructor
 */
    ~Cab();
/**
 *
 * @return false because this is a regular cab.
 */
    bool IsLuxuryCab();
/**
 *
 * @return cab ID
 */
    int getCabID(){ return cabID;}
    /**
     *
     * @return the cab's color
     */
    char getCabColor(){ return color;}
    /**
     *
     * @return the cab's manufacturer
     */
    char getCabMan(){ return manufacturer;}
    /**
     *
     * @return the cab's type
     */
    int getCabType(){ return taxiType;}
/**
 *
 * @return KM passed
 */
    double getKMPassed();
/**
 *
 * @return the speed (1 because it is a regular cab)
 */
    int getSpeed();
};


#endif //EX2_CAB_H
