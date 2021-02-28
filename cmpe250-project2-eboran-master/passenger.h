//
// Created by emreb on 26-Oct-18.
//

#ifndef A_PASSENGER_H
#define A_PASSENGER_H


class passenger {
public:
    passenger(int x,int y,int z,int t,char vip,char lug,int i);
    passenger();
    passenger(const passenger &other);
    passenger& operator=(const passenger &other);

    void print();

    int getArr();
    int getDep();
    int getLT();
    int getST();
    int id;
    bool getVip();
    bool getLug();
    int arrTime,depTime,LT,ST;
    char vip,lug;
};

#endif //A_PASSENGER_H
