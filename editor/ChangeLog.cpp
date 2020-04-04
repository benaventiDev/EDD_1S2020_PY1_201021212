//
// Created by benav on 2/24/2020.
//

#include "ChangeLog.h"






ChangeLog::ChangeLog(){}

ChangeLog::ChangeLog(string s, string r, bool st, char w, int p,  circularLinkedList<int>* list){
    search = std::move(s);
    replace = std::move(r);
    state = st;
    word = w;
    position = p; // Pos -1 for find_replace
    listOfPosition = list;
    backspace = false;

}

circularLinkedList<int> *ChangeLog::getPositionList(){
    return listOfPosition;
}

const string &ChangeLog::getSearch() const {
    return search;
}

void ChangeLog::setSearch(const string &search) {
    ChangeLog::search = search;
}

const string  &ChangeLog::getReplace() const {
    return replace;
}

void ChangeLog::setReplace(const string &replace) {
    ChangeLog::replace = replace;
}

bool ChangeLog::isState() const {
    return state;
}

void ChangeLog::setState(bool state) {
    state = state;
}

char ChangeLog::getWord() {
    return word;
}

void ChangeLog::setWord(char word) {
    ChangeLog::word = word;
}

int ChangeLog::getPosition() const {
    return position;
}

void ChangeLog::setPosition(int position) {
    ChangeLog::position = position;
}

bool ChangeLog::getBackspace(){
    return backspace;
}

void ChangeLog::setBackspace(bool bs){
    backspace = bs;
}
