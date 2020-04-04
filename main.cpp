#include <pdcurs36/curses.h>
#include <string>
#include <stdio.h>
#include "editor/Editor.h"

void curses_init();
using namespace edd;






int main(int argc, char *argv[]) {



    Editor ed;
    string fn = "";
    if(argc > 1)
    {
        fn = argv[1];               // Set the filename
        //ed = Editor(fn);
    }
    else
    {
        ed = Editor();
    }

    curses_init();                  // Initialize ncurses

    while(ed.getMode() != 'x')
    {

        ed.printScreen();
        ed.updateStatus();
        ed.printStatusLine();


        int input = getch();        // Blocking until input
        ed.handleInput(input);
    }


    refresh();                      // Refresh display
    endwin();                       // End ncurses mode



    return 0;
}



void curses_init()
{
    initscr();                      // Start ncurses mode
    if(has_colors() == TRUE){

        start_color();
        //init_pair(1, COLOR_BLACK, COLOR_WHITE);
        init_color(11,  169*(200/51), 169*(200/51), 169*(200/51)); // Background Color
        init_color(12,  14*(200/51), 17*(200/51), 17*(200/51)); // Font Color

        init_pair(1, 12, COLOR_WHITE);
        init_pair(2, 12 , COLOR_GREEN);
        wbkgd(stdscr, COLOR_PAIR(1) );

    }
    curs_set(0);
    //start_color();
    //init_color(1, 799, 600,111);
    //init_pair(1, 1, 3);
    //init_pair(2, 2, 4);
    /*

    wcolor_set(stdscr, COLOR_WHITE, nullptr);
    wcolor_set(stdscr, 1 , NULL);
    attron(COLOR_PAIR(1));
    //attron(COLOR_PAIR(2));
*/





    noecho();                       // Don't echo keystrokes
    cbreak();                       // Disable line buffering
    keypad(stdscr, true);           // Enable special keys to be recorded
}