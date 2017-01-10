//
// Created by shani on 12/27/16.
//

#ifndef EX4_CLOCK_H
#define EX4_CLOCK_H


class Clock {
private:
    int time;
public:
    /**
     * constructor
     */
    Clock();
    /**
     * increase the time by 1
     */
    void incTime();
    /**
     *
     * @return the time
     */
    int getTime();
};


#endif //EX4_CLOCK_H
