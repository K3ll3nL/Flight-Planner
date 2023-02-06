#include <iostream>
#include "LinkeDSList.h"


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
    if(this != &that)
    {
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
        DNode<T>* curr = head;
        while (head != nullptr) {
            DNode<T>* dlt = curr;
            curr = curr->next;
            delete dlt;
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
    return this->list_size;
}

template<typename T>
void DSList<T>::push_back(T d) {
    auto newNode = new DNode<T>();
    newNode->data = d;

    if (this->head == nullptr) {
        newNode->next = nullptr;
        newNode->previous = nullptr;
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->tail->next = newNode;
        newNode->previous = this->tail;
        newNode->previous = nullptr;
        this->tail = newNode;
    }
    list_size++;
}

template<typename T>
void DSList<T>::push_front(T d) {
    auto newNode = new DNode<T>();
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

template<typename T>
void DSList<T>::insert(T new_node) {
    this->push_back(new_node);
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
        DNode<T> *found = new DNode<T>();
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

}

template <typename T>
int DSList::find(T data){
    try{
        for(int i = 0; i < getSize(); i++){
            if(access(i) == data){
                return i;
            }
        }
        return -1;
    }catch(runtime_error){
    }
}


template<typename T>
void DSList<T>::printList() {
    T* temp = this->head;
    while(temp) {
        cout << temp->display() << endl << endl;
        temp = temp->next;
    }
}