//
// Created by ran on 26/11/16.
//

#ifndef EX1_SH1_1_PARSEFROMSTRING_H
#define EX1_SH1_1_PARSEFROMSTRING_H
#include <iostream>
using namespace std;
class ParseFromString {
private:
    string input;
public:
    ParseFromString();
/**
 * Constructor.
 * @param inputStr string to take care of
 */
    ParseFromString(string inputStr);
/**
 * method gets addresses of x axes and y axes and updates them according to string
 * @param input - inpust string
 * @param xCorInput - Xcoordinate to be updated
 * @param yCorInput - Ycoordinate to be updated
 * @return false if xCor/yCor < 0, else return true.
 */
    bool parse(char seperateSign, int* xCorInput, int* yCorInput);
/**
*
* @return devided strings the was in "x_x,y_y,..." pattern and now is in "x_x" pattern
* for the parse method
*/
    string devide();
    bool parse(char* ch);
    /**
     * This is basically the same method as the one above only here it gets only 1
     * integer parameter .
     * This was done for convience puposes.
     * @param seperateSign sepreationg char to expect
     * @param xCorInput wanted integer
     * @return
     */
    bool parse(char seperateSign, int* xCorInput);
};

#endif //EX1_SH1_1_PARSEFROMSTRING_H
