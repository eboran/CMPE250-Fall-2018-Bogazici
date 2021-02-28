//
// Created by emreb on 26-Oct-18.
//

#include "event.h"

int event::getTime(){
    return event_time;
}
event::event() {
    event_time=0;
    type = 0;
    p.arrTime = 0;
    p.depTime = 0;
    p.LT = 0;
    p.ST = 0;
}

event::event(int event_time,int t,passenger& p){
    //cout << "event constructor"<<endl;
    this->type = t;
    this->event_time = event_time;
    this->p=p;
}


event::event(const event &other) {
    event_time = other.event_time;
    type = other.type;
    p = other.p;
}


event& event::operator=(const event &other){
    this->type = other.type;
    this->event_time = other.event_time;
    this->p = other.p;
    return *this;
}

void event::print() {
    cout<< event_time<<" "<< type << " ";
    //p.print();
    cout<<endl;
}



