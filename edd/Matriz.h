//
// Created by benav on 4/3/2020.
//

#ifndef PROJECT_1_MATRIZ_H
#define PROJECT_1_MATRIZ_H


#include "node.h"

namespace edd{
    template <typename T>
    class Matriz{

    private:
        node<T> *first;
        node<T> *last;
        node<T> *currentNode;
        node<T> *currentNodeBackup;
        node<T> *stopNode;
        int size;
    public:
        Matriz();
        void addLast(T );
        void addFirst(T );
        bool addAt(T , int);
        void clear();
        bool clone();
        bool contains(T );
        T getAt(int);
        T getFirst();
        T getLast();
        int getSize();
        int indexOf(T);
        int removeAt(int);
        T* toArray();

        //This is for the iterator
        void begin();
        void end();
        bool hasNext();
        bool hasPrevious();
        T next();
        T previous();

    };

}









template <typename T>
edd::Matriz<T>::Matriz(){
    first = nullptr;
    last = nullptr;
    currentNode = new node<T>();
    currentNodeBackup = currentNode;
    stopNode = nullptr;
    size = 0;
}
template <typename T>
void edd::Matriz<T>::addLast(T data){
    node<T>* newNode = new node<T>(data);
    if(first == nullptr){
        first = last = newNode;
    } else{
        last->setNext(newNode);
        newNode->setPrevious(last);
        last = newNode;
        last->setNext(first);
        first->setPrevious(last);
    }
    size ++;
}
template <typename T>
void edd::Matriz<T>::addFirst(T data){
    node<T>* newNode = new node<T>(data);
    if(first == nullptr){
        last = first = newNode;
        size ++;
    }else{
        newNode->setNext(first);
        first->setPrevious(newNode);
        first = newNode;
        first->setPrevious(last);
        last->setNext(first);
        size ++;
    }
}
template <typename T>
bool edd::Matriz<T>::addAt(T data, int index){
    if(index +1  > size ){
        addLast(data);
        return false;
    } else if(index == 0){
        addFirst(data);
        return true;
    }else {
        node<T>* supportNode = nullptr;
        node<T>* currentNode = first;
        node<T>* newNode = new node<T>(data);
        for (int i = 0; i <= index ; ++i) {
            if(index == i){
                newNode->setNext(currentNode);
                currentNode->setPrevious(newNode);
                if(supportNode != nullptr){supportNode->setNext(newNode); newNode->setPrevious(supportNode); }
                else{first = newNode;}

            }
            supportNode = currentNode;
            currentNode = currentNode->getNext();
        }
    }
    size++;
    return true;
}

template <typename T>
void edd::Matriz<T>::clear(){
    first = nullptr;
    //last = nullptr;
    //currentNode = nullptr;
    size = 0;
}
template <typename T>
bool edd::Matriz<T>::clone(){

}
template <typename T>
bool edd::Matriz<T>::contains(T data){

}
template <typename T>
T edd::Matriz<T>::getAt(int index){
    if(index < size){
        node<T>* tempNode = first;
        for (int i = 0; i <= index ; ++i) {
            if(i == index){
                return tempNode->getData();
            }
            tempNode = tempNode->getNext();
        }
    }
    return currentNode->getData();
}
template <typename T>
T edd::Matriz<T>::getFirst(){
    if(first== nullptr){ return nullptr;}
    return first->getData();
}
template <typename T>
T edd::Matriz<T>::getLast(){
    if(last == nullptr){ return nullptr;}
    return last->getData();
}
template <typename T>
int edd::Matriz<T>::getSize(){
    return size;
}
template <typename T>
int edd::Matriz<T>::indexOf(T data){

}
template <typename T>
int edd::Matriz<T>::removeAt(int index){
    if(index == 0){
        if(last == first){// si solo hay un elemento
            first = nullptr;
        }else{

            if(first->getNext() == last){// Si solo hay dos elementos
                last->setPrevious(nullptr);
                last->setNext(nullptr);
                first = last;
            }else{
                last->setNext(first->getNext());
                first->getNext()->setPrevious(last);
                first = first->getNext();
            }
        }
        size --;
        return 0;
    } else if(index + 1 == size){
        if(last->getPrevious() == first){// Si solo hay dos elementos
            first->setNext(nullptr);
            first->setPrevious(nullptr);
            last = first;
        } else{
            last->getPrevious()->setNext(first);
            first->setPrevious(last->getPrevious());
            last = last->getPrevious();
        }
        size --;
        return index;
    }

    if(index + 1 > size){ return -1;}



    node<T>* supportNode = nullptr;
    node<T>* currentNode = first;
    for (int i = 0; i <= index; ++i) {
        if(i == index){
            supportNode->setNext(currentNode->getNext());
            currentNode->getNext()->setPrevious(supportNode);
            size--;
            return i;


        }
        supportNode = currentNode;
        currentNode = currentNode->getNext();
    }

    size--;
    return index;
}
template <typename T>
T* edd::Matriz<T>::toArray(){

}

//This is for the iterator
template <typename T>
void edd::Matriz<T>::begin(){
    stopNode = last;
    currentNode = currentNodeBackup;
    currentNode->setPrevious(nullptr);
    currentNode->setNext(first);
}
template <typename T>
void edd::Matriz<T>::end(){
    stopNode = first;
    currentNode = currentNodeBackup;
    currentNode->setNext(nullptr);
    currentNode->setPrevious(last);
}
template <typename T>
bool edd::Matriz<T>::hasNext(){
    if(size == 0){ return false;}
    if(stopNode == currentNode){ return false;}
    if(currentNode->hasNext()){
        currentNode = currentNode->getNext();
        return true;
    }
    return false;
}
template <typename T>
bool edd::Matriz<T>::hasPrevious(){
    if(size == 0){ return false;}
    if(stopNode == currentNode){ return false;}
    if(currentNode->hasPrevious()){
        currentNode = currentNode->getPrevious();
        return true;
    }
    return false;
}
template <typename T>
T edd::Matriz<T>::next(){
    return currentNode->getData();
}
template <typename T>
T edd::Matriz<T>::previous(){
    return currentNode->getData();
}


#endif //PROJECT_1_MATRIZ_H
