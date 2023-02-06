//
// Created by Kellen Long on 10/28/2020.
//

#ifndef INC_20F_FLT_PLN_DSAVLTREE_H
#define INC_20F_FLT_PLN_DSAVLTREE_H

#include "DSVector.h"

template <typename T>
struct DSTreeNode{
private:
    T data;
    DSVector<DSTreeNode<T>> children;
public:
    DSTreeNode(const T& d = T(), const DSVector<DSTreeNode<T>>& children) : data(d), children(children) {}
    
};

template <typename T>
class DSTree{
private:

public:

};

#endif //INC_20F_FLT_PLN_DSAVLTREE_H
