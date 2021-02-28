//
// Created by emreb on 26-Oct-18.
//

#ifndef A_EVENT_H
#define A_EVENT_H

#include "type.h"

#include <iostream>
#include <string>
#include <queue>
#include "passenger.h"
using namespace std;

extern queue <passenger> LQ;
extern queue <passenger> SQ;
extern int Lmax,Smax,Lcount,Scount;
extern int world_time;


class event {
public:

    int event_time;
    int type;
    passenger p;
    //void make();

    //void addToLug(passenger p);
    //void addToLQ(passenger p);
    //void addToSeq(passenger p);
    //void popFromSeq(passenger p);
    //void popFromLug(passenger p);
    //void popFromLQ();
    //  void popFromSQ(passenger p);

    int getTime();
    void print();
    event();
    event(int event_time,int t,passenger &p); //constructor
    event(const event &other); // copy constructor
    event& operator=(const event &other); //assignment operator
};





#endif //A_EVENT_H
