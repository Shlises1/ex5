//
// Created by shani on 11/28/16.
//

#include "Trip.h"

/**
 * constructor
 */
Trip::Trip(){}
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
Trip::Trip(int idPar,int startXP,int startYP,int endXP,int endYP,int numPass,int taa,
           int timeOfSt) {
    RideID  = idPar;
    startP = new PointHistory(PointBase(startXP, startYP));
    destP = new PointHistory(PointBase(endXP, endYP));
    numPassengers = numPass;
    taarif = taa;
    layout = NULL;
    timpOfStart = timeOfSt;
    currentP = startP;
    pass = vector<Node*>();
    done = false;
}
/**
 * destructor
 */
Trip::~Trip()   {
    pthread_exit(&tripThread);
    delete(layout);
    delete startP;
    delete destP;
}
/**
 *
 * @return metter passed
 */
double Trip:: getMetterPassed(){return 0.0;}
/**
 *
 * @return the time that the trip need to start
 */
int Trip:: getTimeOfStart(){ return timpOfStart;}
/**
 *
 * @return the ride id
 */
int Trip:: getRideID(){ return RideID;}
/**
 *
 * @return taarif
 */
double Trip::getTaarif() { return taarif;}
/**
 *
 * @return x of the start point
 */
int Trip::getStartX(){
    return startP->getX();
}
/**
 *
 * @return y of the start point
 */
int Trip::getStartY(){
    return startP->getY();
}
/**
 *
 * @return x of the end point
 */
int Trip::getEndX(){
    return destP->getX();
}
/**
 *
 * @return y of the end point
 */
int Trip::getEndY(){
    return destP->getY();
}
/**
 *
 * @param mapInput - the new map
 */
void Trip::setMap(Map* mapInput) {
    layout = mapInput;
}
/**
 *
 * @return the map
 */
Map* Trip::getMap() {
    return layout;
}
/**
 *
 * @return current map
 */
Node* Trip:: getMapCurrent(){
    return layout->getCurrent();
}
/**
 * return the next point in the trip pass, according to he speed of the cab.
 */
Node* Trip::getNext(){
    pthread_join(tripThread,NULL);
    if(speed == 1){
        currentP = pass.front();
    }else if (speed == 2){
        if((pass.front()->getX() != destP->getX())&&((pass.front()->getY() != destP->getY()))){
            pass.erase(pass.begin());
            currentP = pass.front();
        } else{
            currentP = pass.back();
            if(pass.size() == 1){
                done = 1;
            }
        }
    }
    pass.erase(pass.begin());
    if(pass.size() == 0){
        done = 1;
    }
    return currentP;
}
/**
 *
 * @return true if the trip is done, else return false.
 */
int Trip::isDone() { return done;}
/**
 *
 * @return the grid size
 */
string Trip:: getGridSize(){return gridSize;}
/**
 * changes the grid's size
 * @param gridSizeInput - the new grid size
 */
void Trip:: setGridSize(string gridSizeInput){gridSize = gridSizeInput;}
/**
 *
 * @return the number of obsticles in the grid
 */
int Trip:: getNumObs(){ return numObs;}
/**
 * changes the number of obsticles in the grid
 * @param numObsInput - the new number of obsticles
 */
void Trip::setNumObs(int numObsInput){ numObs = numObsInput;}
/**
 *
 * @return string that contains a chain of obsticles
 */
string Trip:: getObsChain(){ return obsChain;}
/**
 * changes the chain of obstacles
 * @param obsChainInput - the new string, that contains a chain of  obsticles
 */
void Trip:: setObsChain(string obsChainInput){ obsChain = obsChainInput;}
/*
 * return a vector that contains the pass of the trip
 */
vector<Node*> Trip:: getpass() {
    return pass;
}
void Trip::threadCalcPass() {
    Trip* t = this;
    pthread_create(&tripThread,NULL,claculatePassWithThread,t);
}
/**
 * creates the pass of the trip from the start point to the dest point
 */
void Trip:: createPass() {
    pthread_join(tripThread,NULL);
    layout->run();
    pass = layout->getPass();
}
/**
 * sets the done param to be true if the trip has ended, else sets it to false
 * @param b - true\false
 */
void Trip:: setDone(bool b){
    done = b;
}
/**
 * sets the speed of the trip (1 or 2)
 * @param newSpeed - the speed
 */
void Trip::setSpeed(int newSpeed) {speed = newSpeed;}
/**
 *
 * @return the speed
 */
int Trip::getSpeed() { return speed;}
void* Trip::claculatePassWithThread(void* data){
    cout <<"starting to calc trip"<<endl;

    Trip* trip = (Trip*)data;
    trip->createPass();
    return NULL;
}