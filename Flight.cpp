//
// Created by Kellen Long on 10/29/2020.
//

#include <iostream>
#include "Flight.h"

Flight::Flight() {
    Destination;
    price = 0;
    time = 0;
    Airline;
}

Flight::Flight(DSString destination, int p, int t, DSString Line) {
    Destination = destination;
    price = p;
    time = t;
    Airline = Line;
}

Flight::Flight(const Flight &that) {
    Destination = that.Destination;
    price = that.price;
    time = that.time;
    Airline = that.Airline;
}

Flight::~Flight() {
//    delete &Destination;
//    price = 0;
//    time = 0;
//    delete &Airline;
}

void Flight::PrintList() {
    std::cout<<"\t";
    Destination.print();
    std::cout<<", $"<<price<<", "<<time<<"mins, ";      //print flight object
    Airline.print();
    std::cout<<std::endl;
}

DSString Flight::getDestination() {
    return Destination;
}

int Flight::getPrice() {
    return price;
}
                                            //all accessor methods
int Flight::getTime() {
    return time;
}

DSString Flight::getAirline() {
    return Airline;
}

Flight &Flight::operator=(const Flight &that) {
    if(this != &that)
    {
        Destination = that.Destination;
        price = that.price;
        time = that.time;
        Airline = that.Airline;
    }
    return *this;
}

bool Flight::operator==(const Flight &that) const {
    return this->Destination==that.Destination && this->price==that.price && this->time==that.time && this->Airline==that.Airline;
}

bool Flight::operator!=(const Flight &that) const {
    return this->Destination!=that.Destination && this->price!=that.price && this->time!=that.time && this->Airline!=that.Airline;
}
