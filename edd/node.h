//
// Created by benav on 2/16/2020.
//

#ifndef TEST4_NODE_H
#define TEST4_NODE_H
#include <iostream>
/*
iterator:
hasNext() true then next() has elements



*/

namespace edd{
    template <class T>
    class node{
    private:
        node *next;
        node *previous;
        T data; // this is a pointer;

    public:
        node(T);
        node();
        void setNext(node *);
        void removeNext();
        void setPrevious(node *);
        void removePrevious();
        node *getNext();
        node *getPrevious();
        bool hasNext();
        bool hasPrevious();
        T getData();
        void print();// To Delete
        ~node();
    };


}


template <class T>
edd::node<T>::node() {

    previous = nullptr;
    next = nullptr;
}


template <class T>
edd::node<T>::node(T value) {
    data = value;
    previous = nullptr;
    next = nullptr;
}

template <class T>
void edd::node<T>::setNext(node *newNode){
    next = newNode;
}

template <class T>
void edd::node<T>::removeNext(){
    next = nullptr;
}

template <class T>
void edd::node<T>::setPrevious(node *newNode){
    previous = newNode;
}

template <class T>
void edd::node<T>::removePrevious(){
    previous = nullptr;
}

template <class T>
edd::node<T> *edd::node<T>::getNext(){
    return next;
}

template <class T>
edd::node<T> *edd::node<T>::getPrevious(){
    return previous;
}

template <class T>
T edd::node<T>::getData(){
    return data; // retorna un puntero de data
}

template <class T>
bool edd::node<T>::hasNext(){
    return next != nullptr;
}

template <class T>
bool edd::node<T>::hasPrevious(){
    return previous != nullptr;
}

template <class T>
void edd::node<T>::print() {
    std::cout<< *data << std::endl;
}

template <class T>
edd::node<T>::~node(){}



#endif //TEST4_NODE_H
