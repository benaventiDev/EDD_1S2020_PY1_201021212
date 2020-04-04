//
// Created by benav on 2/16/2020.
//

#ifndef TEST4_STACK_H
#define TEST4_STACK_H
#include "node.h"
#include "doubleLinkedList.h"
#include "linkedList.h"
#include <stdlib.h>
#include <iostream>

namespace edd{
    template <typename T>
    class stack{
    private:
        doubleLinkedList<T> *llist;
    public:
        stack();
        void push(T);
        T pop();
        T peek();
        bool isEmpty();
        int getSize();
        bool clear();
        doubleLinkedList<T> *getList();
        linkedList<T> *getSimpleList();
    };

}



template <typename T>
edd::stack<T>::stack(){//LIFO
    llist = new doubleLinkedList<T>();
}

template <typename T>
T edd::stack<T>::pop(){
    if(llist->getSize()!=0){
        T last = llist->getLast();
        llist->removeAt(getSize()-1);
        return last;
    }

}

template <typename T>
void edd::stack<T>::push(T data){
    llist->addLast(data);
}

template <typename T>
T edd::stack<T>::peek(){
    return llist->getLast();
}

template <typename T>
bool edd::stack<T>::isEmpty(){
    return llist->getSize() == 0;
}

template <typename T>
int edd::stack<T>::getSize(){
    return llist->getSize();
}

template <typename T>
bool edd::stack<T>::clear(){
    llist->clear();
}

template <typename T>
edd::doubleLinkedList<T>* edd::stack<T>::getList(){
    return llist;
}

template <typename T>
edd::linkedList<T>* edd::stack<T>::getSimpleList(){
    llist->begin();
    linkedList<T>* list = new linkedList<T>();
    while(llist->hasNext()){
        list->addLast(llist->next());
    }
    return list;
}

#endif //TEST4_STACK_H
