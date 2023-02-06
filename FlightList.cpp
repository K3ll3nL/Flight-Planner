//
// Created by Kellen Long on 10/29/2020.
//

#include "FlightList.h"
#include "DSPair.h"

FlightList::FlightList() {
    Origin;
    Destinations;
    iter=0;
}

FlightList::FlightList(DSString Orig){
    Origin = Orig;
    Destinations;
    iter=0;
}

FlightList::FlightList(const FlightList &that) {
    Origin = that.Origin;
    Destinations = that.Destinations;
    iter = that.iter;
}

FlightList::FlightList(FlightList &that) {
    Origin = that.Origin;
    Destinations = that.Destinations;
    iter = that.iter;
}

FlightList::~FlightList() {
    //delete &Origin;
    //delete &Destinations;
    iter = 0;
}

void FlightList::AddNew(DSString Destination, int price, int time, DSString Airline) {
    bool found = false;
    Flight* temp = new Flight(Destination,price,time,Airline);      //create flight object to add
    for(int i = 0;i<Destinations.getSize();i++){        //check DSVector for a matching destination
        if(Destinations[i]==*temp){
            found = true;
        }
    }
    if(!found){             //destination/airline combo not found
        Destinations.push_back(*temp);
    }
}

void FlightList::PrintList() {
    Origin.print();
    std::cout<<":"<<endl;           //print origin city, then on the next line, start printing flight objects
    for(int i = 0; i<Destinations.getSize();i++){
        Destinations[i].PrintList();
    }
}

DSString FlightList::getOrigin() {
    return Origin;          //returns name of origin city
}

Flight FlightList::locate(DSString d) {
    for(int i = 0; i < Destinations.getSize(); i++){
        if(Destinations[i].getDestination()==d){
            return Destinations[i];         //look up flight by keyword
        }
    }
    return *(new Flight());
}

int FlightList::findFlight(DSPair d){      //look up flight position by keyword
    for(int i = 0; i < Destinations.getSize(); i++){
        if(Destinations[i].getDestination()==d.first && Destinations[i].getAirline()==d.second){
            return i;
        }
    }
    return -1;}

int FlightList::findIter() {
    return iter;
}

bool FlightList::oob(){
    return iter>=Destinations.getSize();        //find if nullptr during iterative backtracking
}

FlightList &FlightList::operator=(const FlightList &that) {
    if(this != &that)
    {
        Origin = that.Origin;
        Destinations = that.Destinations;
        iter = that.iter;
    }
    return *this;
}

bool FlightList::operator==(FlightList &that) const {
    return Origin==that.Origin && this->Destinations==that.Destinations;
}

bool FlightList::operator!=(FlightList &that) const {
    return Origin!=that.Origin && this->Destinations!=that.Destinations;
}

Flight FlightList::operator[] (const size_t &pos) {
    return Destinations[pos];
}

Flight FlightList::operator[](const size_t &pos) const{
    return Destinations[pos];

}

void FlightList::inc() {
    iter++;         //increment iterator
}

void FlightList::res() {
    iter = 0;       //reset iterator
}


