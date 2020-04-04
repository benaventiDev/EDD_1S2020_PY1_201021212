//
// Created by benav on 2/24/2020.
//

#ifndef EDDPROJECT1_RECENTFILE_H
#define EDDPROJECT1_RECENTFILE_H


#include <string>
#include <cstddef>         // std::size_t
using namespace std;


class RecentFile {
private:
    string name;
    string path;
    string fullPath;
public:
    RecentFile();
    RecentFile(string);
    string getName();
    string getPath();
    string getPathGraphViz();
    string getFullPath();
};


#endif //EDDPROJECT1_RECENTFILE_H
