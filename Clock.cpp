//
// Created by shani on 12/27/16.
//

#include "Clock.h"
/**
 * constructor
 */
Clock::Clock() {
    time = 0;
}
/**
 * increase the time by 1
 */
void Clock::incTime() { time++; }
/**
 *
 * @return the time
 */
int Clock::getTime() { return time;}