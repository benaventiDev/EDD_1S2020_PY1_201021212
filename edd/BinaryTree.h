//
// Created by benav on 4/3/2020.
//

#ifndef PROJECT_1_BINARYTREE_H
#define PROJECT_1_BINARYTREE_H


//
// Created by benav on 2/16/2020.
//


#include "node.h"
#include <iostream>

namespace edd{
    template <typename T>
    class BinaryTree{

    private:
        node<T> *first;
        node<T> *last;
        node<T> *currentNode;
        node<T> *currentNodeBackup;
        int size;
    public:
        BinaryTree();
        void addLast(T );
        void addFirst(T );
        bool addAt(T , int);
        void clear();
        bool clone();
        bool contains(T );
        T getAt(int);
        node<T>* getNodeAt(int index);
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
edd::BinaryTree<T>::BinaryTree(){
    first = nullptr;
    last = nullptr;
    currentNode = new node<T>();
    currentNodeBackup = currentNode;
    size = 0;
}
template <typename T>
void edd::BinaryTree<T>::addLast(T data){
    node<T>* newNode = new node<T>(data);
    if(last == nullptr){
        first = last = newNode;
    } else{
        last->setNext(newNode);
        newNode->setPrevious(last);
        last = newNode;
    }
    size ++;
}
template <typename T>
void edd::BinaryTree<T>::addFirst(T data){
    node<T>* newNode = new node<T>(data);
    if(first == nullptr){
        last = first = newNode;
        size ++;
    }else{
        newNode->setNext(first);
        first->setPrevious(newNode);
        first = newNode;
        size ++;
    }
}

template <typename T>
bool edd::BinaryTree<T>::addAt(T data, int index){
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
                currentNode->setPrevious(newNode);
                if(supportNode != nullptr){supportNode->setNext(newNode); newNode->setPrevious(newNode); }
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
void edd::BinaryTree<T>::clear(){
    first = nullptr;
    last = nullptr;
    currentNode = nullptr;
    size = 0;
}

template <typename T>
bool edd::BinaryTree<T>::clone(){

}
template <typename T>
bool edd::BinaryTree<T>::contains(T ){

}
template <typename T>
T edd::BinaryTree<T>::getAt(int index){
    if(index < size){
        node<T>* tempNode = first;
        for (int i = 0; i <= index ; ++i) {
            if(i == index){
                return tempNode->getData();
            }
            tempNode = tempNode->getNext();
        }
    }
    //return nullptr;
}

template <typename T>
edd::node<T>* edd::BinaryTree<T>::getNodeAt(int index){
    if(index < size){
        node<T>* tempNode = first;
        for (int i = 0; i <= index ; ++i) {
            if(i == index){
                return tempNode;
            }
            tempNode = tempNode->getNext();
        }
    }
    return nullptr;
}

template <typename T>
T edd::BinaryTree<T>::getFirst(){
    if(first== nullptr){ return nullptr;}
    return first->getData();
}
template <typename T>
T edd::BinaryTree<T>::getLast(){
    if(last != nullptr){ return last->getData();}
}
template <typename T>
int edd::BinaryTree<T>::getSize(){
    return size;
}
template <typename T>
int edd::BinaryTree<T>::indexOf(T){

}
template <typename T>
int edd::BinaryTree<T>::removeAt(int index){

    if(index == 0){
        if(last == first){// si solo hay un elemento
            first = last = nullptr;
        }else{

            if(first->getNext() == last){// Si solo hay dos elementos
                last->setPrevious(nullptr);
                first = last;
            }else{
                first->getNext()->setPrevious(nullptr);
                node<T>* temp;
                temp = first;
                first = first->getNext();
                temp->setNext(nullptr);
            }
        }
        size --;
        return 0;
    } else if(index + 1 == size){ // En caso de que sea el ultimo
        if(last->getPrevious() == first){// Si solo hay dos elementos
            first->setNext(nullptr);
            last->setPrevious(nullptr);
            last = first;
        } else{ // Si hay mas de dos elementos
            node<T>* temp = last;
            last = last->getPrevious();
            last->setNext(nullptr);
            temp->setPrevious(nullptr);
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

    return -1;
}

template <typename T>
T* edd::BinaryTree<T>::toArray(){

}

//This is for the iterator
template <typename T>
void edd::BinaryTree<T>::begin(){
    currentNode = currentNodeBackup;
    currentNode->setPrevious(nullptr);
    currentNode->setNext(first);
}
template <typename T>
void edd::BinaryTree<T>::end(){
    currentNode = currentNodeBackup;
    currentNode->setNext(nullptr);
    currentNode->setPrevious(last);
}
template <typename T>
bool edd::BinaryTree<T>::hasNext(){
    if(currentNode->hasNext()){
        currentNode = currentNode->getNext();
        return true;
    }
    return false;
}
template <typename T>
bool edd::BinaryTree<T>::hasPrevious(){
    if(currentNode->hasPrevious()){
        currentNode = currentNode->getPrevious();
        return true;
    }
    return false;
}
template <typename T>
T edd::BinaryTree<T>::next(){
    return currentNode->getData();
}
template <typename T>
T edd::BinaryTree<T>::previous(){
    return currentNode->getData();
}









#endif //PROJECT_1_BINARYTREE_H
