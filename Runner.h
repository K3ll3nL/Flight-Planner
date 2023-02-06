//
// Created by Kellen Long on 10/29/2020.
//

#ifndef INC_20F_FLT_PLN_RUNNER_H
#define INC_20F_FLT_PLN_RUNNER_H


#include "FlightAdjacency.h"
#include "DSStack.h"
#include "DSPair.h"

class Runner {
private:
    FlightAdjacency* F;
    int read,paths;
public:
    void ReadFile(char**);
    void Run(char**);
    void Record(DSStack<DSPair>*,std::ofstream&,DSString&);
    int total(DSStack<DSPair>*,DSString);
    void doSwap(DSStack<DSPair>&,DSStack<DSPair>&);
    void Print();
};


#endif //INC_20F_FLT_PLN_RUNNER_H
