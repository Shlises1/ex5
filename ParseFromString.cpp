//
// Created by ran on 26/11/16.
//
#include "ParseFromString.h"
/**
* Constructor.
* @param inputStr string to take care of
*/
ParseFromString::ParseFromString(string inputStr) {
    input = inputStr;
}
ParseFromString::ParseFromString(){}
/**
 * method gets addresses of x axes and y axes and updates them according to string
 * @param input - inpust string
 * @param xCorInput - Xcoordinate to be updated
 * @param yCorInput - Ycoordinate to be updated
 * @return false if xCor/yCor < 0, else return true.
 */
bool ParseFromString:: parse(char seperateSign, int* xCorInput, int* yCorInput) {
    int xCor,yCor;
    size_t location = input.find(seperateSign);
    string first = input.substr(0,location);
    xCor = std::stoi(first);
    if (xCor < 0){
        return false;
    }
    *xCorInput = xCor;
    input = input.erase(0,location+1);
    yCor = std::stoi(input);
    location = input.find(seperateSign);
    input = input.erase(0,location+1);
    if (yCor < 0){
        return false;
    }
    *yCorInput = yCor;
    return true;
}
/**
 * parsing method with 1 char parameter
 * @param ch charachter
 * @return wanted charachter
 */
bool ParseFromString:: parse(char* ch) {
    *ch = input[0];
    input = input.erase(0,2);

}
/**
 * This is basically the same method as the one above only here it gets only 1
 * integer parameter .
 * This was done for convience puposes.
 * @param seperateSign sepreationg char to expect
 * @param xCorInput wanted integer
 * @return
 */
bool ParseFromString:: parse(char seperateSign, int* xCorInput) {
    int xCor;
    size_t location = input.find(seperateSign);
    string first = input.substr(0,location);
    xCor = std::stoi(first);
    if (xCor < 0){
        return false;
    }
    *xCorInput = xCor;
    input = input.erase(0,location+1);
}

/**
*
* @return devided strings the was in "x_x,y_y,..." pattern and now is in "x_x" pattern
* for the parse method
*/
string ParseFromString::devide() {
    size_t location = input.find(",");
    string string1 = input.substr(0,location);
    input = input.erase(0,location+1);
    return string1;
}