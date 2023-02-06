//
// Created by Kellen Long on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_FLIGHTLIST_H
#define INC_20F_FLT_PLN_FLIGHTLIST_H

#include "Flight.h"
#include "DSList.h"

#include "DSString.h"
#include "DSList.h"
#include "Flight.h"
#include "DSVector.h"
#include "DSPair.h"

class FlightList {
private:
    DSString Origin;
    DSVector<Flight> Destinations;
    int iter;
public:
    FlightList();
    FlightList(DSString);
    FlightList(const FlightList&);
    FlightList(FlightList&);
    ~FlightList();
    void AddNew(DSString, int, int, DSString);
    void PrintList();
    DSString getOrigin();
    Flight locate(DSString);
    int findFlight(DSPair);
    int findIter();
    bool oob();
    FlightList& operator=(const FlightList&);
    bool operator==(FlightList&) const;
    bool operator!=(FlightList&) const;
    Flight operator[] (const size_t&);
    Flight operator[](const size_t &) const;
    void inc();
    void res();
};


#endif //INC_20F_FLT_PLN_FLIGHTLIST_H
