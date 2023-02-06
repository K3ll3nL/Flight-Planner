#include "DSString.h"
#include<cstring>
#include<iostream>


DSString::DSString(){
    size = 0;
    data = nullptr;
}

DSString::DSString(const char* word){
    size = strlen(word);
    data = new char[size+1];
    strcpy(data, word);
}
DSString::DSString(const DSString& copy){
    size = copy.size;
    data = new char[size+1];
    strcpy(data,copy.data);
}
DSString &DSString::operator=(const DSString & copy) {
    if (this != &copy) {
        if (this->data != nullptr) {
            delete[] data;
        }
        size = copy.size;
        data = new char[copy.size+1];
        strcpy(data,copy.data);
    }
    return *this;
}
DSString &DSString::operator=(const char* in) {
    if (this->data != nullptr) {
        if (this->data != nullptr) {
            delete[] data;
        }
        size = strlen(in);
        data = new char[size+1];
        strcpy(data,in);
    }
    return *this;
}
DSString::~DSString() {
//    if(data!=nullptr){
//        delete[] data;
//    }
}
char* DSString::getString() const {
    return data;
}
void DSString::setString(char* a){
    size = strlen(a);
    data = new char[size+1];
    strcpy(data,a);
}
int DSString::getSize() const{
    return size;
}
void DSString::print() const {
    std::cout << data;
}
void DSString::Lower() {
    if (size != 0) {
        for (int i = 0; i < size; i++) {
            if (isupper(data[i])) {
                data[i] = char(tolower(data[i]));
            }
        }
    }
}
void DSString::Capitalize(){
    if(size !=0){
        data[0] = char(toupper(data[0]));
    }
}


