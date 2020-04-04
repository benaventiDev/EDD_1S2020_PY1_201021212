//
// Created by benav on 2/24/2020.
//

#include "RecentFile.h"
RecentFile::RecentFile(){}

RecentFile::RecentFile(string fileName){
    fullPath = fileName;
    size_t slash =  fileName.find_last_of("\\");
    path = fileName.substr(0, slash);
    name = fileName.substr(slash+1);

}
string RecentFile::getName(){
    return name;
}
string RecentFile::getPath(){
    return path;
}
string RecentFile::getFullPath() {
    return fullPath;
}

void find_and_replace(string& source, string const& find, string const& replace)
{
    for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
    {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}


string RecentFile::getPathGraphViz(){
    string newPath(getFullPath());
    find_and_replace(newPath, "\\", "\\\\");
    return newPath;
}

