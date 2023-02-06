//
// Created by Kellen Long on 10/27/2020.
//

#ifndef INC_20F_FLT_PLN_DSSTACK_H
#define INC_20F_FLT_PLN_DSSTACK_H

#include "DSList.h"

template <typename T>
class DSStack{
private:
    DSList<T> stack;
public:
    DSStack();
    DSStack(const DSStack&);
    DSStack& operator=(const DSStack&);
    ~DSStack();
    void push(T);
    T& pop();
    T& peek();
    bool isEmpty();
    bool contains(T);
    void printStack();
    int size();
};


template<typename T>
DSStack<T>::DSStack() {
    stack;
}

template<typename T>
DSStack<T>::DSStack(const DSStack<T>& that){
    stack = that.stack;
}

template<typename T>
DSStack<T>& DSStack<T>::operator=(const DSStack<T>& that){
    if(this != &that)
    {
        stack = that.stack;
    }
    return *this;
}

template<typename T>
DSStack<T>::~DSStack() {
    //delete &stack;
}

template<typename T>
void DSStack<T>::push(T data) {
    stack.push_back(data);
}

template<typename T>
T &DSStack<T>::pop() {
    T* ret = new T(stack.access(stack.getSize()-1));
    stack.remove(*ret);
    return *ret;
}

template<typename T>
T &DSStack<T>::peek() {
    return stack.access(stack.getSize()-1);
}

template<typename T>
bool DSStack<T>::isEmpty() {
    return stack.getSize()==0;
}

template<typename T>
bool DSStack<T>::contains(T d){
    return stack.find(d)!=-1;
}

template<typename T>
void DSStack<T>::printStack() {
    stack.printList();
}

template<typename T>
int DSStack<T>::size() {
    return stack.getSize();
}


#endif //INC_20F_FLT_PLN_DSSTACK_H
