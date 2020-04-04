//
// Created by benav on 2/16/2020.
//

#ifndef TEST4_QUEUE_H
#define TEST4_QUEUE_H
#include "node.h"
#include "linkedList.h"
#include "doubleLinkedList.h"
#include <stdlib.h>

namespace edd{
    template <typename T>
    class queue{
    private:
        doubleLinkedList<T> *llist;

    public:
        queue();
        bool isEmpty();
        int getSize();
        T getFront();
        T dequeue();
        void enqueue(T);
        void clear();



    };
}




template <typename T>
edd::queue<T>::queue(){ //FIFO
    llist = new doubleLinkedList<T>();
}

template <typename T>
bool edd::queue<T>::isEmpty(){
    return llist->getSize() == 0;
}

template <typename T>
int edd::queue<T>::getSize(){
    return llist->getSize();
}

template <typename T>
T edd::queue<T>::getFront(){
    return llist->getFirst();
}

template <typename T>
T edd::queue<T>::dequeue(){
    if(llist->getSize()==0){
        return nullptr;
    }
    T* first = llist->getFirst();
    llist->removeAt(0);
    return first;
}

template <typename T>
void edd::queue<T>::enqueue(T data){
    llist->addLast(data);
}

template <typename T>
void edd::queue<T>::clear(){
    llist->clear();
}






#endif //TEST4_QUEUE_H
