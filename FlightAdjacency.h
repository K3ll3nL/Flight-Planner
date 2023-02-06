//
// Created by Kellen Long on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_FLIGHTADJACENCY_H
#define INC_20F_FLT_PLN_FLIGHTADJACENCY_H

#include "DSList.h"
#include "FlightList.h"
#include "DSPair.h"

class FlightAdjacency {
private:
    DSList<FlightList> AdjList;
public:
    FlightAdjacency();
    FlightAdjacency(const FlightAdjacency&);
    ~FlightAdjacency();
    void AddNew(DSString, DSString, int, int, DSString);
    void PrintList();
    int getSize();
    FlightList locate(DSString);
    int findRow(DSString);
    Flight locateFlight(DSPair, DSPair);
    FlightAdjacency& operator=(const FlightAdjacency&);
    bool operator==(FlightAdjacency&) const;
    bool operator!=(FlightAdjacency&) const;
    FlightList& operator[](const size_t&);
    const FlightList& operator[](const size_t &) const;

};


#endif //INC_20F_FLT_PLN_FLIGHTADJACENCY_H
