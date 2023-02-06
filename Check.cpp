//
// Created by Kellen Long on 9/20/2020.
//

#include "catch.hpp"
#include "DSList.h"
#include "DSStack.h"

TEST_CASE("DSList"){


    SECTION("Adding items"){
        DSList<int> test;
        test.push_front(20);
        test.push_front(10);
        test.push_back(30);
        test.push_back(40);
        int arr[4] = {10,20,30,40};
        DSList<int> basis1(arr,4);
        CHECK(test == basis1);
    }
    SECTION("Removing items"){
        int arr[4] = {10,20,30,40};
        DSList<int> test(arr,4);
        test.remove(20);
        test.remove(50);
        int arr2[3] = {10,30,40};
        DSList<int> basis2(arr2,3);
        CHECK(test == basis2);
    }

}
TEST_CASE("DSStack"){
    DSStack<int>* test = new DSStack<int>();
    SECTION("Adding"){
        test->push(1);
        test->push(2);
        test->push(3);
        CHECK(test->peek()==3);
    }
    SECTION("Popping"){
        test->push(1);
        test->push(2);
        test->push(3);
        CHECK(test->pop()==3);
        CHECK(test->peek()==2);
    }
}