//
// Created by Kellen Long on 10/29/2020.
//

#include <fstream>
#include "Runner.h"
#include "DSStack.h"
#include "DSPair.h"

void Runner::ReadFile(char** argv){
    F = new FlightAdjacency;            //creates the object
    std::ifstream file(argv[1]);
    if(!file.is_open()){
        std::cout<<"file not opened";
    }else{
        DSString *One, *Two, *Line;     //creates placeholders for parsing in file
        int t, p;//more placeholders
        char* frst = new char[10];
        file.getline(frst,10);
        while(!file.eof()){
            char *temp = new char[80];
            char *wrd = new char[20];
            file.getline(temp,80);
            if (strcmp(temp,"")!=0) {
                wrd = strtok(temp, "|\r");
                One = new DSString(wrd);
                wrd = strtok(NULL, "|\r");
                Two = new DSString(wrd);            //reads in the files
                wrd = strtok(NULL, "|\r");
                p = atoi(wrd);
                wrd = strtok(NULL, "|\r");
                t = atoi(wrd);
                wrd = strtok(NULL, "|\r");
                Line = new DSString(wrd);
                F->AddNew(*One, *Two, t, p, *Line);     //adds the cities in normal and reverse to the structure
                F->AddNew(*Two, *One, t, p, *Line);
            }
        }
    }
    file.close();
}


void Runner::Run(char** argv){
    read = 1, paths = 0;
    ReadFile(argv);         //these two methods set up the structure
    std::ifstream file(argv[2]);
    std::ofstream outFile(argv[3]);
    if(!file.is_open()){
        std::cout<<"file not opened";
    }else{
        DSString *Origin, *Destination, *Type, *Curr;
        DSStack<DSPair>* s = new DSStack<DSPair>();
        DSStack<DSString>* s2 = new DSStack<DSString>();    //All temporary holder objects
        DSStack<DSPair> Lines[15] = {};
        int Linecount[15] = {};
        char* frst = new char[10];
        file.getline(frst,10);
        while(!file.eof()) {
            char *temp = new char[80];
            char *wrd = new char[20];
            file.getline(temp,80);
            if(strcmp(temp,"")!=0) {
                wrd = strtok(temp, "|\r");
                Origin = new DSString(wrd);
                wrd = strtok(NULL, "|\r");
                Destination = new DSString(wrd);        //reads in the flightplan file
                wrd = strtok(NULL, "|\r");
                Type = new DSString(wrd);
                s->push(*new DSPair(*Origin, ""));
                s2->push(*Origin);          //sets the origin city
                Curr = Origin;
                outFile << "Flight " << read++ << ": " << Origin->getString() << ", " << Destination->getString()
                        << (strcmp(Type->getString(), "T") == 0 ? " (Time)" : " (Price)") << endl; //sets up the output
                while (!s->isEmpty()) {       //while stack not empty
                    if (s2->peek() == *Destination) {   //check if arrived
                        Linecount[paths] = total(s, *Type);  //adds flight goal value to array
                        DSStack<DSPair> *stack = new DSStack<DSPair>(); //creates temporary stack to extract values
                        while (!s->isEmpty()) {
                            stack->push(s->pop());
                        }
                        DSPair temp;                    //extracting values to the paths value of Lines[]
                        while (!stack->isEmpty()) {
                            temp = stack->pop();
                            Lines[paths - 1].push(temp);
                            s->push(temp);
                        }
                        //Lines[paths-1] = *new DSStack<DSPair>(*s);
                        s->pop();           //removes cities from stacks
                        s2->pop();
                        Curr = &(s2->peek());
                    } else {
                        int row = F->findRow(*Curr);    //if not arrived
                        FlightList *focus = &F[0][row];
                        if (focus->oob()) {       //check if nullptr, reset iter
                            s->pop();
                            s2->pop();
                            focus->res();
                            Curr = &(s2->peek());
                        } else if (s2->contains(
                                focus[0][focus->findIter()].getDestination())) {   //check if city is already in stack, increment iter
                            focus->inc();
                        } else {          //else add to stack, continue, and increment iter
                            s->push(*new DSPair(focus[0][focus->findIter()].getDestination(),
                                                focus[0][focus->findIter()].getAirline()));
                            s2->push(focus[0][focus->findIter()].getDestination());     //adds new values to the arrays
                            focus->inc();
                            Curr = &(s2->peek());
                        }
                    }
                }
                if (paths == 0) {   //no possible paths
                    outFile << "No paths found" << endl;
                } else {      //sort paths according to value
                    for (int i = 0; i < paths - 1; i++) {
                        // Find the minimum element in unsorted array
                        int min_idx = i;
                        for (int j = i + 1; j < paths; j++) {
                            if (Linecount[j] < Linecount[min_idx]) {
                                min_idx = j;
                            }
                        }
                        // Swap the found minimum element with the first element
                        doSwap(Lines[min_idx], Lines[i]);
                        std::swap(Linecount[min_idx], Linecount[i]);
                    }
                    for (int i = 0; i < paths; i++) {
                        Record(&Lines[i], outFile, *Type);        //print out each line to output file
                    }
                }
                paths = 0;
            }
        }
        outFile.close();
        file.close();
    }
}

void Runner::Record(DSStack<DSPair>* s,std::ofstream& outFile,DSString& Type){
    DSString* ret = new DSString("");
    DSStack<DSPair>* stack = new DSStack<DSPair>();    //holder objects
    DSPair temp;
    int time = -43, price = -19;        //set time and price to account for adding layover values each flight
    Flight list[15];
    int j = s->size() - 2;
    for (int i = j; i >= 0; i--) {
        temp = s->pop();
        stack->push(temp);
        auto *test = &(s->peek());      //flips stack for extracting values and prepping for output
        list[i] = F->locateFlight(*test, temp);
        time += list[i].getTime() + 43;
        price += list[i].getPrice() + 19;
    }
    stack->push(s->pop());
    while (!stack->isEmpty()) { //start of output loop
        temp = stack->pop();
        outFile << temp.first.getString();
        if(temp.second!=""){        //if there is an airline associated, denote it.
            outFile << " (" <<temp.second.getString() << ")";
        }
        if (stack->isEmpty()) {         //finished all flight legs
            outFile << ". Time: " << time << " Price: " << price << endl;
        } else {            //more flight legs
            outFile << " -> ";
        }
    }
}

int Runner::total(DSStack<DSPair>* s, DSString Type){
    paths++;
    DSStack<DSPair>* stack = new DSStack<DSPair>();
    DSPair temp;            //holder objects
    int ret = 0;
    int j = s->size() - 2;
    for (int i = j; i >= 0; i--) {
        temp = s->pop();
        stack->push(temp);
        auto *test = &(s->peek());      //totals value
        ret+= (strcmp(Type.getString(),"T")==0?(F->locateFlight(*test, temp).getTime()):(F->locateFlight(*test, temp).getPrice()));
    }
    while(!stack->isEmpty()){
        s->push(stack->pop());      //flips stack back
    }
    return ret;
}


void Runner::doSwap(DSStack<DSPair>&a, DSStack<DSPair>&b){          //swaps a with b
    DSStack<DSPair> temp, temp2;
    while(!a.isEmpty()){
        temp.push(a.pop());
    }
    while(!b.isEmpty()){
        temp2.push(b.pop());
    }
    while(!temp.isEmpty()){
        b.push(temp.pop());
    }
    while(!temp2.isEmpty()){
        a.push(temp2.pop());
    }
}


void Runner::Print() {
    F->PrintList();
}
