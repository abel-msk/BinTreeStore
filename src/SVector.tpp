#include "SVector.h"

template <class TC>
SVector<TC>::SVector() {
    vectorBegin = nullptr;
    vectorEnd = nullptr;
    current = nullptr;
}

template <class TC>
TC SVector<TC>::push_back(TC el) {
    
    element<TC>* newEl = new element<TC>;
    newEl->next = newEl->prev = nullptr;
    newEl->data = el;

    if (vectorEnd != nullptr) {
        vectorEnd->next = newEl;
        newEl->prev = vectorEnd;
    }
    vectorEnd = newEl;
    if ( vectorBegin == 0) vectorBegin=newEl;

    return el;
}

template <class TC>
TC SVector<TC>::pop_back() {
    if ( vectorEnd == nullptr) return nullptr;
    TC ret = vectorEnd->data;
    if (vectorEnd->prev == nullptr ) {  //  the vector has 1 element pointer by end and begin
        free(vectorEnd);
        vectorEnd = vectorBegin = nullptr;
    }
    else {
        vectorEnd->prev->next=0;
        vectorEnd = vectorEnd->prev;
        free(vectorEnd->next);
        vectorEnd->next = nullptr;
    }
    return ret;
}
template <class TC>
void SVector<TC>::reset() {
    current=vectorBegin;
}

template <class TC>
TC SVector<TC>::getFirst() {
    if (vectorBegin==nullptr) return nullptr;
    current=vectorBegin;
    return current->data; 
}

template <class TC>
TC SVector<TC>::getLast() {
    if (vectorEnd==nullptr) return nullptr;
    return vectorBegin->data; 
}

template <class TC>
TC SVector<TC>::getNext() {
    if (current == nullptr) return nullptr;
    TC ret = current->data;
    current = current->next;
    return ret;
}

template <class TC>
void SVector<TC>::clear()  {
        if ( vectorBegin != nullptr) {
        current = vectorBegin;
        while ((current = vectorBegin->next) != nullptr) {
            if ( vectorBegin->data != NULL) delete vectorBegin->data;
            delete(vectorBegin);
            vectorBegin = current;
        }
        if ( vectorBegin->data != NULL) delete vectorBegin->data;
        delete(vectorBegin);

        vectorBegin = vectorEnd = nullptr;
    }
}

template <class TC>
SVector<TC>::~SVector()  {
    clear();
}

