#include "LuxuryCab.h"


//Constructor which inherits from Cab class
LuxuryCab::LuxuryCab(Cab input):Cab(input.getCabID(),input.getCabType(),input.getCabMan(),input.getCabColor()){
    standardCab = input;
    taarif = 2 * taarif;
}
/**
 * Method which checks if object is luxury cab
 * @return true for luxury cab
 */
bool LuxuryCab::IsLuxuryCab() { return true;}
/**
 * Method to get luxury cab speed
 * @return speed
 */
int LuxuryCab::getSpeed() { return 2*SPEED;}

