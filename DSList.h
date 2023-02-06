//
// Created by Kellen Long on 9/20/2020.
//

#ifndef INC_20F_AUTO_IDX_DSLIST_H
#define INC_20F_AUTO_IDX_DSLIST_H

#include <iostream>
#include "FlightList.h"

using namespace std;

template <typename T>
struct DSNode{
    T data;
    DSNode* next;
    DSNode* previous;
    //DSNode(const T &d = T(), DSNode *n = NULL, DSNode *p = NULL) : data(d), next(n), previous(p) {}
};

template <typename T>
class DSList {
private:
    DSNode<T> *head;
    DSNode<T> *tail;
    int list_size;
public:
    DSList();
    DSList(T arr[],int len);
    DSList(const DSList& that);
    ~DSList();
    T* getHead();
    T* getTail();
    int getSize();
    int getSize() const;
    bool remove(T);
    T& access(int);
    T& access(int) const;
    int find(T);
    void push_back(T);
    void push_front(T);
    void printList();
    DSList& operator=(const DSList&);
    bool operator==(const DSList&) const;
    bool operator!=(const DSList&) const;
    T& operator [](const size_t &);
    const T& operator[](const size_t &) const;
    friend void swap(DSList<T> &a,DSList<T> &b){
        using std::swap;
        swap(a.head,b.head);
        swap(a.tail,b.tail);
        swap(a.list_size,b.list_size);
    }

};

template<typename T>
DSList<T>::DSList() {
    head = nullptr;
    tail = nullptr;
    list_size = 0;
}

template<typename T>
DSList<T>::DSList(const DSList<T>& that){
    head = that->head;
    tail = that->tail;
    list_size = that->list_size;
}

template<typename T>
DSList<T> &DSList<T>::operator=(const DSList<T>& that){
    if(this != &that){
        head = that.head;
        tail = that.tail;
        list_size = that.list_size;
    }
    return *this;
}

template<typename T>
DSList<T>::~DSList() {
    try {
        if(head == nullptr){
            throw runtime_error("No head declared");
        }
        DSNode<T>* curr = head;
        while (curr != NULL) {
            DSNode<T>* temp = curr;
            curr = temp->next;
            remove(temp->data);
        }
    }catch(runtime_error){
    }

}

template<typename T>
T* DSList<T>::getHead() {
    return this->head;
}

template<typename T>
T* DSList<T>::getTail() {
    return this->tail;
}

template<typename T>
int DSList<T>::getSize(){
    return list_size;
}

template<typename T>
int DSList<T>::getSize() const{
    return list_size;
}


template<typename T>
void DSList<T>::push_back(T d) {
    auto newNode = new DSNode<T>();
    newNode->data = d;

    if (this->head == nullptr) {
        newNode->next = nullptr;
        newNode->previous = nullptr;
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        newNode->previous = this->tail;
        this->tail = newNode;
    }
    list_size++;
}

template<typename T>
void DSList<T>::push_front(T d) {
    auto newNode = new DSNode<T>();
    newNode->data = d;

    if (this->head == nullptr) {
        newNode->next = nullptr;
        newNode->previous = nullptr;
        this->head = newNode;
        this->tail = newNode;
    } else {
        newNode->next = this->head;
        newNode->previous = nullptr;
        this->head->previous = newNode;
        this->head = newNode;
    }
    list_size++;
}

template <typename T>
bool DSList<T>::remove(T value){
    auto* temp = head;
    while(temp && temp->data != value){
        temp = temp->next;
    }
    if(temp){
        if(temp == head)
            head = head->next;
        if(temp == tail)
            tail = tail->previous;
        if(temp->next)
            temp->next->previous = temp->previous;
        if(temp->previous)
            temp->previous->next = temp->next;
        delete temp;
        list_size--;
        return true;
    }
    return false;
}

template<typename T>
T& DSList<T>::access(int data) {
    try {
        if(data < 0 || data > list_size - 1){
            throw runtime_error("Invalid index");
        }
        int i = 0;
        auto temp = head;
        DSNode<T> *found = new DSNode<T>();
        while(temp != nullptr){
            if(i == data){
                found = temp;
            }
            i++;
            temp = temp->next;
        }
        return found->data;
    }catch(runtime_error){
    }
    return *(new T());
}

template <typename T>
int DSList<T>::find(T data){
    try{
        for(int i = 0; i < getSize(); i++){
            if(access(i) == data){
                return i;
            }
        }
        return -1;
    }catch(runtime_error){
    }
    return -1;
}


template<typename T>
void DSList<T>::printList() {
    DSNode<T>* temp = this->head;
    while(temp) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}

template<typename T>
DSList<T>::DSList(T arr[],int len){
    head = nullptr;
    tail = nullptr;
    list_size = 0;
    for(int i = 0; i < len;i++){
        push_back(arr[i]);
    }
}

template<typename T>
T& DSList<T>::access(int place) const{
    try {
        if(place < 0 || place > list_size){
            throw runtime_error("Invalid index");
        }
        int i = 0;
        auto temp = head->next;
        DSNode<T> *found = new DSNode<T>();
        while(temp != nullptr){
            if(i++ == place){
                found = temp;
            }
            temp = temp->next;
        }
        return found->data;
    }catch(runtime_error){
    }
    return *(new T());
}

template<typename T>
bool DSList<T>::operator==(const DSList<T>& that) const{
    if(list_size!=that.list_size){
        return false;
    }
    for(int i = 0; i<list_size;i++){
        if(access(i)!=that.access(i)){
            return false;
        }
    }
    return true;
}

template<typename T>
bool DSList<T>::operator!=(const DSList<T>& that) const{
    return !(*this == that);
}

template<typename T>
T& DSList<T>::operator[](const size_t &pos){
    return access(pos);
}

template<typename T>
const T& DSList<T>::operator[](const size_t &pos) const {
    return access(pos);
}


template<typename T>std::ostream& operator <<(std::ostream& out,const DSList<T> &a)
{
    for(int i=0; i <a.getSize(); i++){
        std::cout<<a[i]<<" ";
    }
    return out;
}


#endif //INC_20F_AUTO_IDX_DSLIST_H
