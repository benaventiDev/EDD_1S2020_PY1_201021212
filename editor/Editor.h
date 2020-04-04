//
// Created by benav on 2/19/2020.
//

#ifndef EDDPROJECT1_EDITOR_H
#define EDDPROJECT1_EDITOR_H

#include <pdcurs36/curses.h>
#include "../edd/doubleLinkedList.h"
#include "../edd/circularLinkedList.h"
#include "../editor/RecentFile.h"
#include "../edd/stack.h"
#include "ChangeLog.h"
#include <windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <process.h>


using namespace edd;
using namespace std;

class Editor {
private:
    doubleLinkedList<char> *mainText;
    circularLinkedList<RecentFile> *recentFilesList;
    stack<ChangeLog> *undoList;
    stack<ChangeLog> *redoList;
    int currentPos, x, y, mode;
    int LinesCounter = 1;
    int welcomeOption = 9;
    int recentFileCounter = 0;
    string status;
    string findReplaceStatus = "";
    string findAndReplace;
    string fileName = "";
    string saveFile = "";
    string recentFiles = "";
    string statusHelp = "";
    bool fileSaved = false;
    bool laveWarningSent = false;


public:
    Editor();

    void handleInput(int c);
    void printScreen();
    char getMode() {return mode;}
    void printWelcomeScreen();
    void printEditorScreen();
    void printOpenScreen();
    void printRecentScreen();
    static void printReports();
    void printSave();
    void openFile();
    void setRecentFiles();
    void addToRecentFiles(string);
    void undo();
    void redo();
    void saveStatus();
    void save();
    void reports();
    void listReport();
    void searchedWords();
    void sortWords();
    void test(string);

    void moveDown();
    void moveUp();
    void moveRight();
    void moveLeft();
    void moveTo();
    void printStatusLine();
    void updateStatus();
    static void generateAndDisplayGraph( string);
    static string tos(int );
    void find_replace();
    static inline bool fileExists (std::string name);
    static std::string GetClipboardText();


    void generateRecentReport();

};


#endif //EDDPROJECT1_EDITOR_H
