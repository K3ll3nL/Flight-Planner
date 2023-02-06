//
// Created by Kellen Long on 9/20/2020.
//

#ifndef INC_20F_AUTO_IDX_DSVECTOR_H
#define INC_20F_AUTO_IDX_DSVECTOR_H


#include <ostream>
#include <iostream>

template<typename T>
class DSVector {
    T *data;
    int size;
    int capacity;

public:
    DSVector();
    DSVector(const DSVector&);
    ~DSVector();
    void resize(const size_t&);
    void reserve(size_t);
    void push_back(const T);
    void pop_back();
    size_t getSize() const;
    size_t getCapacity() const;
    T& operator [](const size_t &);
    const T& operator [](const size_t &) const;
    bool operator==(const DSVector<T>&) const;
    bool operator!=(const DSVector<T>&) const;
    bool empty() const;
    T& at(const size_t&);
    const T& at(const size_t&) const;
    void erase(const size_t&);
    void erase(const size_t&,const size_t&);
    void insert(const size_t&,const T&);
    void insert(const size_t&,const size_t&,const T&);
    void clear();
    friend void swap(DSVector &a,DSVector &b){
        using std::swap;
        swap(a.size,b.size);
        swap(a.capacity,b.capacity);
        swap(a.data,b.data);
    }
};
template<typename T>
DSVector<T>::DSVector():data(nullptr),size(0),capacity(0) {}

template<typename T>
DSVector<T>::DSVector(const DSVector& other):data(NULL),size(0),capacity(0){
    data=new T[other.capacity];
    std::copy(&other[0],&other[0]+other.size,data);
    size=other.size;
    capacity=other.capacity;
}

template<typename T>
DSVector<T>::~DSVector(){
    if(data == nullptr) {
        delete[] data;
    }
}

template<typename T>
void DSVector<T>::resize(const size_t &newsize){
    if(newsize<size){
        T* temp=new T[newsize];
        memcpy(temp,data,sizeof(T)*newsize);
        delete[] data;
        data=temp;
    }
    else if(newsize>capacity){
        reserve(newsize);
    }
    size=newsize;

}
template<typename T>
void DSVector<T>::reserve(size_t newcapacity){
    if(capacity == 0) {
        newcapacity=1;
    }else{
        newcapacity = 2*capacity;
    }
    if(newcapacity>capacity)
    {
        T* temp=new T[newcapacity];
        std::copy(data,data+capacity,temp);
//        delete[] data;
        data=temp;
        capacity=newcapacity;
    }
}

template<typename T>
void DSVector<T>::push_back(const T val){
    if(capacity<=size)
        reserve(capacity);
    data[size++]=val;
}

template<typename T>
void DSVector<T>::pop_back(){
    if(size)
        --size;
}

template<typename T>
size_t DSVector<T>::getSize() const{
    return size;
}

template<typename T>
size_t DSVector<T>::getCapacity() const{
    return capacity;
}

template<typename T>
T& DSVector<T>::operator [](const size_t &pos){
    return data[pos];
}

template<typename T>
const T& DSVector<T>::operator[](const size_t &pos) const{
    return data[pos];
}

template<typename T>
bool DSVector<T>::operator==(const DSVector<T> &that) const{
    for(int i = 0; i < size; i++){
        if(data[i]!=that[i]){
            return false;
        }
    }
    return true;
}

template<typename T>
bool DSVector<T>::operator!=(const DSVector<T> &that) const{
    return !(*this==that);
}

template<typename T>
bool DSVector<T>::empty() const{
    return size==0;
}

template<typename T>
T& DSVector<T>::at(const size_t& pos){
    if(pos>=size)
        throw std::out_of_range("");
    else
        return data[pos];
}

template<typename T>
const T& DSVector<T>::at(const size_t& pos) const{
    if(pos>=size)
        throw std::out_of_range("");
    else
        return data[pos];
}

template<typename T>
void DSVector<T>::erase(const size_t& a){
    for(size_t i=a; i<size-1; i++)
    {
        data[i]=data[i+1];
    }
    --size;
}

template<typename T>
void DSVector<T>::erase(const size_t& a,const size_t& b){
    for(size_t i=a; i<size-(b-a); i++)
    {
        data[i]=data[i+b-a];
    }
    size-=b-a;
}

template<typename T>
void DSVector<T>::insert(const size_t& pos,const T& val){
    if(capacity<=size)
        reserve(size);
    size++;
    for(size_t i=size-1; i>pos; i--)
    {
        data[i]=data[i-1];
    }
    data[pos]=val;
}

template<typename T>
void DSVector<T>::insert(const size_t& pos,const size_t& n,const T& val){
    if(size<n+capacity)
        reserve(size+n);
    size+=n;
    for(size_t i=size-1; i>=pos+n; i--)
    {
        data[i]=data[i-n];
    }
    for(size_t i=pos; i<pos+n; i++)
    {
        data[i]=val;
    }
}

template<typename T>
void DSVector<T>::clear() {
    size = 0;
}



template<typename T>
std::ostream& operator <<(std::ostream& out,const DSVector<T> &a)
{
    for(size_t i=0; i<a.getSize()-1; i++)
    {
        std::cout<<a[i]<<", ";
    }
    std::cout<<a[a.getSize()-1];
    return out;
}


#endif //INC_20F_AUTO_IDX_DSVECTOR_H
