//
// Created by shani on 11/28/16.
//


#include "Cab.h"
/**
* constractor
* @param cabIDInput - the cab's ID
* @param taxiTypeInput - the type of the cab
* @param manufacturerInput - char of the cab's manufacturer first letter
* @param colorInput - char of the cab's color first letter
*/
Cab::Cab(int cabIDInput,int taxiTypeInput, char manufacturerInput, char colorInput) {
    cabID = cabIDInput;
    manufacturer = manufacturerInput;
    color = colorInput;
    numOfKMPassed = 0.0;
    taxiType = taxiTypeInput;
}
/**
 * constructor
 */
Cab::Cab() {}
/**
 * destructor
 */
Cab::~Cab(){}
/**
 *
 * @return false because this is a regular cab.
 */
bool Cab:: IsLuxuryCab(){ return false;}
/**
 *
 * @return KM passed
 */
double Cab:: getKMPassed(){ return numOfKMPassed;}
/**
 *
 * @return the speed (1 for regular cab, 2 for luxury cab)
 */
int Cab::getSpeed(){
    if(taxiType == 1) {
        return SPEED;
    } else return 2 * SPEED;
}
