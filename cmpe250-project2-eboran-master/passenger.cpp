//
// Created by emreb on 26-Oct-18.
//

#include <iostream>
using namespace std;
#include "passenger.h"

void passenger::print(){
    cout <<"arr time: " <<arrTime<<endl;
}

passenger::passenger(int x, int y, int z, int t,char a,char b,int i) {
    arrTime = x;
    depTime = y;
    LT = z;
    ST = t;
    vip = a;
    lug = b;
    id = i;
}

passenger::passenger(const passenger &other) {
    arrTime = other.arrTime;
    depTime = other.depTime;
    LT = other.LT;
    ST = other.ST;
    vip = other.vip;
    lug = other.lug;
    id = other.id;
}


passenger& passenger::operator=(const passenger &other) {
    arrTime = other.arrTime;
    depTime = other.depTime;
    LT = other.LT;
    ST = other.ST;
    vip = other.vip;
    lug = other.lug;
    id = other.id;
    return *this;
}


passenger::passenger() {
    arrTime = 0;
    depTime = 0;
    LT = 0;
    ST = 0;
    id = 0;
}

int passenger::getArr() {
    return arrTime;
}
int passenger::getDep() {
    return depTime;
}
int passenger::getLT() {
    return LT;
}
int passenger::getST() {
    return ST;
}
bool passenger::getVip() {
    if(vip=='V'){
        return true;
    }
    return false;
}
bool passenger::getLug() {
    if(lug=='L'){
        return true;
    }
    return false;
}
