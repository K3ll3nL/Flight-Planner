//
// Created by Kellen Long on 11/6/2020.
//

#ifndef INC_20F_FLT_PLN_PAIR_H
#define INC_20F_FLT_PLN_PAIR_H

#include "DSString.h"

class DSPair{
public:
    DSString first;
    DSString second;
    DSPair() {
        first;
        second;
    }
    DSPair(DSString f, DSString s){
        first = f;
        second = s;
    }
    bool operator==(DSPair &p) {
        return first==p.first&&second==p.second;
    }
    bool operator!=(DSPair &p) {
        return !(first==p.first&&second==p.second);
    }
};


#endif //INC_20F_FLT_PLN_PAIR_H
