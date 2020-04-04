//
// Created by benav on 2/24/2020.
//

#ifndef EDDPROJECT1_CHANGELOG_H
#define EDDPROJECT1_CHANGELOG_H

#include "../edd/circularLinkedList.h"
#include <string>
#include <stdlib.h>


using namespace std;
using namespace edd;
class ChangeLog {
private:
    string search;
    string replace;
    bool state;
    char word;
    int position;
    circularLinkedList<int> *listOfPosition;
    bool backspace;
public:
    ChangeLog();
    ChangeLog(string, string , bool, char, int, circularLinkedList<int>*);

    const string &getSearch() const;
    void setSearch(const string &search);
    const string &getReplace() const;
    void setReplace(const string &replace);
    bool isState() const;
    void setState(bool state);
    char getWord();
    void setWord(char word);
    int getPosition() const;
    void setPosition(int);
    circularLinkedList<int> *getPositionList();
    bool getBackspace();
    void setBackspace(bool);

};


#endif //EDDPROJECT1_CHANGELOG_H
