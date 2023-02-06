//
// Created by Kellen Long on 10/29/2020.
//

#include "FlightAdjacency.h"
#include "DSPair.h"

FlightAdjacency::FlightAdjacency() {
    AdjList;
}

FlightAdjacency::FlightAdjacency(const FlightAdjacency& that) {
    AdjList = that.AdjList;
}

FlightAdjacency::~FlightAdjacency() {
//    delete &AdjList;
}

void FlightAdjacency::AddNew(DSString Origin, DSString Destination, int price, int time, DSString Airline) {
    bool found = false;
    for(int i = 0;i<AdjList.getSize();i++){     //loops through all places in adjacency list and compares origin city to parameter
        if(AdjList[i].getOrigin()==Origin){     //if matches
            found = true;
            AdjList[i].AddNew(Destination,time,price,Airline);  //pass off to Flightlist class
        }
    }
    if(!found){             //no city has been found, therefore, push_back a new one.
        FlightList* temp = new FlightList(Origin);
        AdjList.push_back(*temp);
        AdjList.access(AdjList.getSize()-1).AddNew(Destination,time,price,Airline);
    }
}

void FlightAdjacency::PrintList() {
    for(int i = 0; i<AdjList.getSize();i++){
        AdjList.access(i).PrintList();      //print each flightlist in DSList
    }
}

int FlightAdjacency::getSize() {
    return AdjList.getSize();
}

FlightList FlightAdjacency::locate(DSString d) {        //finds DSList row by keyword
    for(int i = 0; i < AdjList.getSize(); i++){
        if(AdjList[i].getOrigin()==d){
            return AdjList[i];
        }
    }
    return static_cast<FlightList>(nullptr);
}

int FlightAdjacency::findRow(DSString d) {      //finds row number by keyword
    for(int i = 0; i < AdjList.getSize(); i++){
        if(AdjList[i].getOrigin()==d){
            return i;
        }
    }
    return -1;
}

Flight FlightAdjacency::locateFlight(DSPair from, DSPair to) {
    return AdjList[findRow(from.first)][AdjList[findRow(from.first)].findFlight(to)];       //used during calculation of flight times
}


FlightAdjacency &FlightAdjacency::operator=(const FlightAdjacency & that) {
    if(this != &that)
    {
        AdjList = that.AdjList;
    }
    return *this;
}

bool FlightAdjacency::operator==(FlightAdjacency &that) const {
    return AdjList==that.AdjList;
}

bool FlightAdjacency::operator!=(FlightAdjacency &that) const {
    return AdjList!=that.AdjList;
}

FlightList &FlightAdjacency::operator[](const size_t &pos) {
    return AdjList[pos];
}

const FlightList &FlightAdjacency::operator[](const size_t &pos) const {
    return AdjList[pos];
}
