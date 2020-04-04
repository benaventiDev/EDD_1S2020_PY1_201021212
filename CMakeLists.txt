cmake_minimum_required(VERSION 3.15)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)


set(LIB_LOCATION C:/MinGW64/x86_64-w64-mingw32/include/pdcurs36/wincon)


add_executable(Project_1 main.cpp  edd/node.h edd/stack.h edd/queue.h edd/linkedList.h edd/doubleLinkedList.h
        edd/circularLinkedList.h
        editor/Editor.cpp editor/Editor.h editor/RecentFile.cpp editor/RecentFile.h editor/ChangeLog.cpp editor/ChangeLog.h
        edd/BinaryTree.h edd/Matriz.h)


target_link_libraries(Project_1  ${LIB_LOCATION}/pdcurses.a)