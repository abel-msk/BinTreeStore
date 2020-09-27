#ifndef SIMPLE_VECTOR_H__
#define  SIMPLE_VECTOR_H__
#include "stdlib.h"
#include <iostream>
#include <stdio.h>


template <class T>
struct element  {
    T data;
    element* next;
    element* prev;
};

template <class TC>
class SVector {
    element<TC>* vectorBegin;
    element<TC>* vectorEnd;
    element<TC>* current;

    public:
    SVector();
    TC push_back(TC el);
    TC pop_back();
    TC getFirst();
    TC getLast();
    TC getNext();
    void reset();
    void clear();
    ~SVector();
};

#include "SVector.tpp"
#endif