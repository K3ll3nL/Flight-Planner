//
// Created by Kellen Long on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_FLIGHT_H
#define INC_20F_FLT_PLN_FLIGHT_H

#include "DSString.h"

class Flight {
private:
    DSString Destination;
    int price;
    int time;
    DSString Airline;
public:
    Flight();
    Flight(DSString, int, int, DSString);
    Flight(const Flight&);
    ~Flight();
    void PrintList();
    DSString getDestination();
    int getPrice();
    int getTime();
    DSString getAirline();
    Flight& operator=(const Flight&);
    bool operator==(const Flight&) const;
    bool operator!=(const Flight&) const;



};


#endif //INC_20F_FLT_PLN_FLIGHT_H
