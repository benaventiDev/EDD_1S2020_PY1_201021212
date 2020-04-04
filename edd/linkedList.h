//
// Created by benav on 2/16/2020.
//

#ifndef TEST4_LINKEDLIST_H
#define TEST4_LINKEDLIST_H
#include "node.h"
#include <stdlib.h>
#include <iostream>

namespace edd{
    template <typename T>
    class linkedList{

    private:
        node<T> *first;
        node<T> *last;
        node<T> *currentNode;
        node<T> *currentNodeBackup;
        int size;
    public:
        linkedList();
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
        bool hasNext();
        T next();


    };

}



template <typename T>
edd::linkedList<T>::linkedList() {
    first = nullptr;
    last = nullptr;
    currentNode = new node<T>();
    currentNodeBackup = currentNode;
    size = 0;
}

template <typename T>
void edd::linkedList<T>::addLast(T data){
    node<T>* newNode = new node<T>(data);
    if(last == nullptr){
        first = last = newNode;
    } else{
        last->setNext(newNode);
        last = newNode;
    }
    size ++;
}

template <typename T>
void edd::linkedList<T>::addFirst(T data){
    node<T>* newNode = new node<T>(data);
    if(first == nullptr){
        last = first = newNode;
        size ++;
    }else{
        newNode->setNext(first);
        first = newNode;
        size ++;
    }
}

template <typename T>
bool edd::linkedList<T>::addAt(T data, int index){
    if(index +1  >= size ){
        addLast(data);
        return false;
    } else if(index == 0){
        addFirst(data);
        return true;
    }else{

        node<T>* supportNode = nullptr;
        node<T>* currentNode = first;
        node<T>* newNode = new node<T>(data);
        for (int i = 0; i <= index ; ++i) {

            if(index == i){
                newNode->setNext(currentNode);
                if(supportNode != nullptr){supportNode->setNext(newNode);}
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
void edd::linkedList<T>::clear(){
    first = nullptr;
    last = nullptr;
    currentNode = nullptr;
    size = 0;
}

template <typename T>
bool edd::linkedList<T>::clone(){}

template <typename T>
bool edd::linkedList<T>::contains(T data){}

template <typename T>
T edd::linkedList<T>::getAt(int index){
    if(index < size){
        node<T>* tempNode = first;
        for (int i = 0; i <= index ; ++i) {
            if(i == index){
                return tempNode->getData();
            }
            tempNode = tempNode->getNext();
        }
    }

}

template <typename T>
T edd::linkedList<T>::getFirst(){
    if(first== nullptr){ return nullptr;}
    return first->getData();
}

template <typename T>
T edd::linkedList<T>::getLast(){
    if(last == nullptr){ return nullptr;}
    return last->getData();
}

template <typename T>
int edd::linkedList<T>::getSize(){
    return size;
}

template <typename T>
int edd::linkedList<T>::indexOf(T){} //TODO

template <typename T>
int edd::linkedList<T>::removeAt(int index){

    if(index + 1 > size){ return -1;}
    if(index == 0){
        if(last == first){// si solo hay un elemento
            first = last = nullptr;
        }else{

            if(first->getNext() == last){// Si solo hay dos elementos
                first->setNext(nullptr);
                first = last;
            }else{//Si hay 3 elementos o mas
                first = first->getNext();
            }
        }
        size --;
        return 0;
    } else if(index + 1 <= size){ // Si el indice a remover es el ultimo y no es el primero


        node<T>* supportNode = nullptr;
        node<T>* currentNode = first;
        for (int i = 0; i <= index; ++i) {
            if(i == index){
                if(supportNode != nullptr) {
                    supportNode->setNext(currentNode->getNext());
                    if(i == size-1){ last = supportNode; }
                    else{currentNode->setNext(nullptr);}
                    size--;
                    return i;
                } else{ // en el caso de que el indice a remover es 0

                    std::cout <<"Error" << std::endl;
                    return -1;
                }

            }

            supportNode = currentNode;
            currentNode = currentNode->getNext();
        }






    }


    return -1;
}

template <typename T>
T* edd::linkedList<T>::toArray(){} // TODO

//This is for the iterator
template <typename T>
void  edd::linkedList<T>::begin(){
    currentNode = currentNodeBackup;
    currentNode->setNext(first);
}

template <typename T>
bool edd::linkedList<T>::hasNext(){

    if(currentNode->hasNext()){
        currentNode = currentNode->getNext();
        return true;
    }
    return false;
}



template <typename T>
T edd::linkedList<T>::next(){
    return currentNode->getData();
}


/*



C:\Users\benav\CLionProjects\test4\build\test4.exe
Node at pos 3: 33
Size: 6
6
7
10
15
20
33
6
7
10
15
First: 33
Last: 6
6
7
10
15
20
33
6
7
10
15
new list:
33
20
15
10
7
6

33
20
15
10



*/





#endif //TEST4_LINKEDLIST_H
