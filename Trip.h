//
// Created by shani on 11/28/16.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H


//#include "Cab.h"

#include "Map.h"
#include "PointHistory.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace std;
class Trip {
private:
    int RideID;
    double totalMeterPassed;
    Node* startP;
    Node* destP;
    int numPassengers;
    double taarif;
    Map* layout;
    int timpOfStart;
    int done;
    string gridSize;
    int numObs;
    string obsChain;
    Node* currentP;
    vector<Node*> pass;
    int speed;
    //serialize
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive & ar,const unsigned int version) {
        ar & RideID;
        ar & startP;
        ar & destP;
        ar & numPassengers;
        ar & taarif;
        ar & gridSize;
        ar & numObs;
        ar & obsChain;
    }
public:
    /**
     * constructor
     */
    Trip();
    /**
     * destructor
     */
    ~Trip();
    /**
     * constructor
     * @param idPar - ID of the trip
     * @param startXP - x of start point
     * @param startYP - y of start point
     * @param endXP - x of end point
     * @param endYP - y of end point
     * @param numPass - num of passengers in the trip
     * @param taa - the tarrif of the trip
     */
    Trip(int idPar,int startXP,int startYP,int endXP,int endYP,int numPass,int taa, int timeOfSt);
    /**
     *
     * @return metter passed
     */
    double getMetterPassed();
    /**
     *
     * @return ride ID
     */
    int getRideID();
    /**
     *
     * @return taarif
     */
    double getTaarif();
    /**
     *
     * @return x of the start point
     */
    int getStartX();
    /**
     *
     * @return y of the start point
     */
    int getStartY();
    /**
     *
     * @return x of the end point
     */
    int getEndX();
    /**
     *
     * @return y of the end point
     */
    int getEndY();
    /**
     *
     * @param mapInput - the new map
     */
    void setMap(Map* mapInput);
    /**
     *
     * @return the map
     */
    Map* getMap();
    /**
     *
     * @return current map
     */
    Node* getMapCurrent();
    /**
    * return the next point in the trip pass, according to he speed of the cab.
    */
    Node* getNext();
    /**
     *
     * @return true if the trip is done, else return false.
     */
    int isDone();
    /**
     *
     * @return the time that the trip need to start
     */
    int getTimeOfStart();
    /**
     *
     * @return the grid size
     */
    string getGridSize();
    /**
     * changes the grid's size
     * @param gridSizeInput - the new grid size
     */
    void setGridSize(string gridSizeInput);
    /**
     *
     * @return the number of obsticles in the grid
     */
    int getNumObs();
    /**
     * changes the number of obsticles in the grid
     * @param numObsInput - the new number of obsticles
     */
    void setNumObs(int numObsInput);
    /**
     *
     * @return string that contains a chain of obsticles
     */
    string getObsChain();
    /**
     * changes the chain of obstacles
     * @param obsChainInput - the new string, that contains a chain of  obsticles
     */
    void setObsChain(string obsChainInput);
    /*
     * return a vector that contains the pass of the trip
     */
    vector<Node*> getpass();
    /**
     * creates the pass of the trip from the start point to the dest point
     */
    void createPass();
    /**
     * sets the done param to be true if the trip has ended, else sets it to false
     * @param b - true\false
     */
    void setDone(bool b);
    /**
     * sets the speed of the trip (1 or 2)
     * @param newSpeed - the speed
     */
    void setSpeed(int newSpeed);
    /**
     *
     * @return the speed
     */
    int getSpeed();
};

#endif //EX2_TRIP_H