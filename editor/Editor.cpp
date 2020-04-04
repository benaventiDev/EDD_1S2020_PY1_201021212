//
// Created by benav on 2/19/2020.
//
/*
 * currentPos will handle the position within the doubleLinkedList
 * y will handle the number of lines, while x will handle the postion in the current line
 * currentpos' purpose is to keep track within the list while x and y is to display on screen.
 *
 *
 */


#include <thread>
#include "Editor.h"


/*
 Modes

 i = initial mode
 e = editor mode
 f = find and replace
 o = open
 r = recent files
 s = saveStatus
 x = end program
 z = reports



*/
Editor::Editor() {
    mainText = new doubleLinkedList<char>();
    recentFilesList = new circularLinkedList<RecentFile>();
    undoList = new stack<ChangeLog>();
    redoList  = new stack<ChangeLog>();
    currentPos = -1;/*C'est seulement pour savoir la postion actuelle dedans la liste mais rien a voir avec la position sur l'ecran  */
    LinesCounter = 1; /* Afin de creer le tableau qui contient chaque ligne pour l'imprimer sur l'ecran rien a voir avec la position sur l'ecran*/
    status = "";
    saveFile = "";
    x = 0;
    y = 0;
    mode = 'i';
    findAndReplace = "";
    findReplaceStatus = "";
    fileSaved = false;
}
//TODO CTREL + X  para salir en cualquier momento

void Editor::handleInput(int c) {

    if (LinesCounter <= 1) { LinesCounter = 1; }
    if (currentPos < -1) { currentPos = -1; }

    switch (c) {
        case KEY_LEFT:
            switch (mode) {
                case 'i':
                    welcomeOption--;
                    if (welcomeOption < 9) { welcomeOption = 12; }
                    break;
                case 'r':
                    recentFileCounter--;if(recentFileCounter < 0){ recentFileCounter = recentFilesList->getSize()-1;}

                    break;
                case 'e':
                case 'f':
                case 'z':
                    moveLeft();
            }

            return;
        case KEY_RIGHT:
            switch (mode) {
                case 'i':
                    welcomeOption++;
                    if (welcomeOption > 12) { welcomeOption = 9; }
                    break;
                case 'r':
                    recentFileCounter++;if(recentFileCounter > recentFilesList->getSize()-1){ recentFileCounter = 0;}
                    break;
                case 'e':
                case 'f':
                case 'z':
                    moveRight();
            }

            return;
        case KEY_UP:
            switch (mode) {
                case 'i':
                    welcomeOption--;
                    if (welcomeOption < 9) { welcomeOption = 12; }
                    break;
                case 'r':
                    recentFileCounter--;if(recentFileCounter < 0){ recentFileCounter = recentFilesList->getSize()-1;}
                    break;
                case 'z':
                case 'e':
                case 'f':
                    moveUp();
            }

            return;
        case KEY_DOWN:
            switch (mode) {
                case 'i':
                    welcomeOption++;
                    if (welcomeOption > 12) { welcomeOption = 9; }
                    break;
                case 'r':
                    recentFileCounter++;if(recentFileCounter > recentFilesList->getSize()-1){ recentFileCounter = 0;}
                    break;
                case 'e':
                case 'z':
                case 'f':
                    moveDown();
            }

            return;
    }

    switch (mode) {
        case 'z':{
            switch (c){
                case 0x001B: //esc
                    mode = 'e';
                break;
                default:
                    char d = char(c);
                    switch (d){
                        case '1':
                            listReport();
                            break;
                        case '2':
                            searchedWords();
                            break;
                        case '3':
                            sortWords();
                            break;
                    }
            }
        }
            break;
        case 's':
            if(fileSaved){
                status = "";
                mode = 'i';
                return;
            }
            switch (c){
                case KEY_ENTER:
                case 10:
                    save();

                    break;
                case KEY_BTAB:
                case KEY_CTAB:
                case KEY_STAB:
                case KEY_CATAB:
                case 9:
                    saveFile += " ";
                    break;
                case 0x0008: //backspace
                case 127:
                case KEY_BACKSPACE:
                    if(!saveFile.empty()){ saveFile.pop_back();}
                    break;
                case 0x0016: //ctrl + v
                    saveFile += GetClipboardText();
                    break;
                case 0x001B: //esc
                    mode = 'e';
                    curs_set(2);
                    break;
                default:
                    saveFile += c;
            }
            break;
        case 'r':
            switch (c){
                case KEY_ENTER:
                case 10:
                    if(recentFilesList->getSize() == 0){ return;}
                    fileName = recentFilesList->getAt(recentFileCounter).getFullPath();
                    openFile();
                    break;
                case 0x0012:// ctrl+ c generar reporte
                    generateRecentReport();
                    break;
                case 0x001B: //esc
                    mode = 'i';
                    break;
            }
            break;
        case 'i':
            if (c == KEY_ENTER || c == 10) {
                if (welcomeOption == 9) { mode = 'e'; curs_set(2); }
                else if (welcomeOption == 10) {
                    fileName = "";
                    mode = 'o';
                    status = "Write the full path of the file and press Enter. Press \'esc\' to got to welcome screen";
                } else if (welcomeOption == 11) { mode = 'r'; setRecentFiles(); }
                else if (welcomeOption == 12) { mode = 'x'; }
                else
                    return;
            }
            switch (char(c)) {
                case '1':
                    mode = 'e';
                    break;
                case '2':
                    fileName = "";
                    mode = 'o';
                    status = "Write the full path of the file and press Enter. Press \'esc\' to got to welcome screen";
                    break;
                case '3':
                    mode = 'r';
                    setRecentFiles();
                    break;
                case '4':
                    mode = 'x';
                    break;
            }
            break;
        case 'o':
            switch (c) {
                case 0x0008: //backspace
                case 127:
                case KEY_BACKSPACE:
                    if (!fileName.empty()) { fileName.pop_back();}
                    break;
                case KEY_ENTER:
                case 10:
                    openFile();
                    break;
                case 0x0016: //ctrl + v
                    fileName += GetClipboardText();
                    break;
                case 0x001B: //esc
                    mode = 'i';
                    break;
                default:
                    fileName += char(c);
            }
            break;
        case 'f': //TODO:  un escape mode(en caso de arrepentirse) y backspace para borrar, tambien
            switch (c) {
                case 0x0008: //backspace
                case 127:
                case KEY_BACKSPACE:
                    if(findAndReplace.size() > 0){
                    findAndReplace.pop_back();}
                    status = "Find and Replace: " + findAndReplace;
                    break;
                case KEY_BTAB:
                case KEY_CTAB:
                case KEY_STAB:
                case KEY_CATAB:
                case 9:
                    findAndReplace += ' ';
                    status = "Find and Replace: " + findAndReplace;
                    break;
                case KEY_ENTER:
                case 10:
                    find_replace();
                    mode = 'e';
                    break;
                default:
                    findAndReplace += c;
                    status = "Find and Replace: " + findAndReplace;
            }
            break;

        case 'e':
            findReplaceStatus = "";
            if(laveWarningSent){
                switch (c) {
                    case 0x001B: //esc
                        curs_set(0);
                        mode = 'i';
                        fileName = "";
                        mainText->clear();
                        currentPos = -1;/*C'est seulement pour savoir la postion actuelle dedans la liste mais rien a voir avec la position sur l'ecran  */
                        LinesCounter = 1; /* Afin de creer le tableau qui contient chaque ligne pour l'imprimer sur l'ecran rien a voir avec la position sur l'ecran*/
                        x = 0;
                        y = 0;
                        undoList->clear();
                        redoList->clear();
                        laveWarningSent = false;
                        break;
                    case 0x0013: //CTRL+S
                        laveWarningSent = false;
                        saveStatus();
                        break;
                    case KEY_ENTER:
                    case 10: {
                        laveWarningSent = false;
                    }
                }
                return;
            }
            switch (c) {
                case 0x001B: //esc
                    if(undoList->isEmpty()){ // If no chances has been made
                        curs_set(0);
                        mode = 'i';
                        fileName = "";
                        mainText->clear();
                        currentPos = -1;/*C'est seulement pour savoir la postion actuelle dedans la liste mais rien a voir avec la position sur l'ecran  */
                        LinesCounter = 1; /* Afin de creer le tableau qui contient chaque ligne pour l'imprimer sur l'ecran rien a voir avec la position sur l'ecran*/
                        x = 0;
                        y = 0;
                        undoList->clear();
                        redoList->clear();
                        laveWarningSent = false;
                    }else{
                        laveWarningSent = true;
                        status = "Are you sure you want to leave, press \'esc\' to leave without saving changes, enter to dismiss, or ctrl+s to save the file.";

                    }

                    break;
                case 0x0017: // CTRL + W
                    mode = 'f';
                    findAndReplace = "";
                    status = "Find and Replace: " + findAndReplace;
                    break;
                case 0x0008: //backspace
                case 127:
                case KEY_BACKSPACE: {
                    if(!redoList->isEmpty()){redoList->clear();}
                    if (currentPos <= -1) { return; }
                    if (mainText->getNodeAt(currentPos)->getData() == '\n') {
                        LinesCounter--;
                    }
                    ChangeLog cl("", "", false, mainText->getAt(currentPos), currentPos, nullptr);
                    cl.setBackspace(true);
                    undoList->push(cl);
                    mainText->removeAt(currentPos);
                    currentPos--;
                    moveTo();
                    break;
                }
                case KEY_DC:
                    break;
                case 0x001A: //CTRL+Z
                    undo();
                    break;
                case 0x0019: //CTRL+Y
                    redo();
                    break;
                case 0x0012: //CTRL+C
                    reports();
                    break;
                case 0x0013: //CTRL+S
                    saveStatus();
                    break;
                case KEY_ENTER:
                case 10: {
                    if(!redoList->isEmpty()){redoList->clear();}
                    currentPos++;
                    LinesCounter++;
                    y++;
                    x = 0;
                    ChangeLog cl("", "", false, '\n', currentPos, nullptr);
                    undoList->push(cl);
                    mainText->addAt('\n', currentPos);

                    break;
                }
                case KEY_BTAB:
                case KEY_CTAB:
                case KEY_STAB:
                case KEY_CATAB:
                case 9: {
                    if(!redoList->isEmpty()){redoList->clear();}
                    currentPos++;
                    x++;
                    mainText->addAt(char(' '), currentPos);
                    ChangeLog cl("", "", false, char(' '), currentPos, nullptr);
                    undoList->push(cl);
                    break;
                }
                default:
                    if(!redoList->isEmpty()){redoList->clear();}
                    currentPos++;
                    x++;
                    mainText->addAt(char(c), currentPos);

                    ChangeLog cl("", "", false, char(c), currentPos, nullptr);
                    undoList->push(cl);
            }
            break;
    }

}

// TODO repalce \ and " \n
void Editor::listReport(){

    string text = "digraph D {\nnode[fillcolor=indigo\t fontcolor=white  style=\"filled, bold\" fontsize=20 ]\n1 [shape=plaintext label = \"null\"]\n";
    string arrows;
    int counter = 2;
    mainText->begin();
    while(mainText->hasNext()){
        if(mainText->next() == '\n'){
            text += tos(counter) + "[shape=box label = \"NewLine\"]\n";
        }else if(mainText->next() == '\\'){
            text += tos(counter) + "[shape=box label = \" \\\\ \"]\n";
        }else if(mainText->next() == '\"'){
            text += tos(counter) + "[shape=box label = \"\\\"\"]\n";
        }else{
            text += tos(counter) + "[shape=box label = \"" + mainText->next() + "\"]\n";
        }

        arrows += tos(counter -1 ) + "->" + tos(counter) + "\n" + tos(counter) + "->" + tos(counter -1 ) + "\n";
        counter ++;
    }
    text += arrows;
    text += "}";
    generateAndDisplayGraph(text);

}

void Editor::searchedWords(){
    int counter = 1;
    doubleLinkedList<ChangeLog>* undoCopy = undoList->getList();
    doubleLinkedList<ChangeLog>* redoCopy = redoList->getList();
    string text = "digraph D {\nnode[fillcolor=olivedrab3 fontcolor=white  style=\"filled, bold\" fontsize=20 ]\n";
    string rank;
    string rank2;
    string connections;
    undoCopy->end();
    while(undoCopy->hasPrevious()) {
        text += tos(counter) + "[ shape=box label=\"";
            if(undoCopy->previous().getPosition() == -1){
                text += "Palabra buscada: " + undoCopy->previous().getSearch() + "\\nReemplazada: " + undoCopy->previous().getReplace() + "\\nEstado: no revertido.\\n " + "Palabra: null\\nPosicion:null";
            }
        rank += tos(counter) + " ";
        text += "\"]\n";

        if(counter != 1){
            connections += tos(counter -1) + "->" + tos(counter) + "[penwidth=1 minlen=3]\n";
        }
        counter++;
    }





    int counterTemp = counter;
    text += "node[fillcolor=indianred fontcolor=white  style=\"filled, bold\" fontsize=20 ]\n";
    redoCopy->end();
    while(redoCopy->hasPrevious()) {
        text += tos(counter) + "[ shape=box label=\"";
        if(redoCopy->previous().getPosition() == -1){
            text += "Palabra buscada: " + redoCopy->previous().getSearch() + "\\nReemplazada: " + redoCopy->previous().getReplace() + "\\nEstado: Revertido.\\n " + "Palabra: null\\nPosicion:null";
        }
        rank2 += tos(counter) + " ";
        text += "\"]\n";

        if(counter != counterTemp){
            connections += tos(counter -1) + "->" + tos(counter) + "[penwidth=1 minlen=3]\n";
        }
        counter++;
    }
    text += connections + "}";
    generateAndDisplayGraph(text);

}

void Editor::sortWords(){
    linkedList<ChangeLog>* undoCopy = undoList->getSimpleList();
    linkedList<ChangeLog>* searchedSorted = new linkedList<ChangeLog>();
    linkedList<ChangeLog>* replacedSorted = new linkedList<ChangeLog>();

    string text;

    for(int i = 0; i <undoCopy->getSize();i++) {
        int pos = 0;
        int posbackup = 0;
        string word;
        undoCopy->begin();
        while (undoCopy->hasNext()) {
            if (word.empty()) {
                word = undoCopy->next().getSearch();
            } else if (word.compare(undoCopy->next().getSearch()) >= 0) {
                word = undoCopy->next().getSearch();
                posbackup = pos;
            }
            pos++;
        }
        searchedSorted->addFirst(undoCopy->getAt(posbackup));
        undoCopy->removeAt(posbackup);

    }









    searchedSorted->begin();
    while(searchedSorted->hasNext()){
        text += searchedSorted->next().getSearch() + "\n";
    }



    ofstream ofs(R"(C:\Users\benav\CLionProjects\EDDPractica1\build\graph.dot)");
    ofs << text;
    ofs.close();

}

//TODO work on find and replace as currently is crashing
void Editor::find_replace() {
    if (findAndReplace.find(';') == std::string::npos) { findReplaceStatus += "Delimiter \";\" not found";
        return;}
    string chercher = findAndReplace.substr(0, findAndReplace.find(';'));
    findAndReplace.erase(0, findAndReplace.find(';') + 1);
    string remplacer = findAndReplace;

    if (chercher.empty()) {
        findReplaceStatus += "0 words affected.";
        return;
    }
    //Si chercher = "" return no hay nada que reemplazar, si no si buscar

    int counter = 0;
    int chercherSize = chercher.length();


    auto *simpleList = new circularLinkedList<int>(); //TODO: puede ser una list de pos {int init, int final} o lenght en lugar de final
    int initPos = 0;
    int actualPos = 0;

    //add initpos with addFirst, therefore the last one will be on the first position on the list and the first one will be on the last position.
    mainText->begin();
    while (mainText->hasNext()) {
        if (mainText->next() == chercher.at(counter)) {
            counter++;
            if (counter > chercherSize - 1) {
                counter = 0;
                actualPos++;
                simpleList->addFirst(initPos);
                continue;
            }
        } else {
            initPos = actualPos+1;
            counter = 0;
        }
        actualPos++;
    }


    simpleList->begin();

    while(simpleList->hasNext()){
        initPos = simpleList->next();

        for(int i = 0; i < chercherSize; i++) {
            mainText->removeAt(initPos);
        }
        actualPos = 0;
        for(char i : remplacer) {
            mainText->addAt(i , initPos + actualPos++ );
        }
    }
    if(!redoList->isEmpty()){redoList->clear();}
    findReplaceStatus += " " + to_string( simpleList->getSize() )+  " words modified.";
    currentPos = -1;
    x = 0;
    y = 0;
    if(simpleList->getSize() > 0){
        ChangeLog cl(chercher, remplacer, false, '\0', -1, simpleList);
        undoList->push(cl);
    }
}


void Editor::openFile() {
    if (fileExists(fileName)) {
        string line;
        ifstream rf;
        rf.open(fileName);
        if (rf.is_open()) {
            while (!rf.eof()) {
                getline(rf, line);
                for (char c : line) {
                    switch (c) {
                        case 0x0017:
                        case 0x0008: //backspace
                        case 127:
                        case KEY_BACKSPACE:
                        case KEY_DC:
                        case KEY_ENTER:
                        case 10:
                        case KEY_BTAB:
                        case KEY_CTAB:
                        case KEY_STAB:
                        case KEY_CATAB:
                        case 9:
                            currentPos++;
                            mainText->addAt(char(' '), currentPos);
                            break;
                        default:
                            currentPos++;
                            mainText->addAt(char(c), currentPos);
                    }

                }
                currentPos++;
                LinesCounter++;
                mainText->addAt(char('\n'), currentPos);
            }
            currentPos--;
            LinesCounter--;
            mainText->removeAt(mainText->getSize()-1);


            mode = 'e';
            currentPos = -1;
            curs_set(2);
            status = "";
            rf.close();

            addToRecentFiles(fileName);

        } else {
            status = "Could not open file. Try another way;";
        }
    } else {
        status = "File does not exist. Try again and press enter or press \'esc\' to go to welcome screen.";
    }
}

void Editor::addToRecentFiles(string fileToAdd) {
    if(fileExists("recent.txt")){
        //string rfile;
        ifstream rif;
        rif.open("recent.txt");
        string recentLine;
        recentFiles = "";

        if (rif.is_open()) {
            while (!rif.eof()) {
                getline(rif, recentLine);
                if(recentLine != fileToAdd){
                    recentFiles = recentFiles + recentLine + "\n";
                }
            }
        }
        recentFiles = fileToAdd + "\n" + recentFiles;

        rif.close();

        ofstream ofs("recent.txt");
        ofs << recentFiles;
        ofs.close();
    }else{
        ofstream ofs("recent.txt");
        ofs << fileToAdd;
        ofs.close();
    }

}

void Editor::setRecentFiles(){
    recentFilesList->clear();

    if(fileExists("recent.txt")){
        ifstream rif;
        rif.open("recent.txt");
        string recentLine;
        recentFiles = "";
        if (rif.is_open()) {
            while (!rif.eof()) {
                getline(rif, recentLine);

                if(!recentLine.compare("")==0 && fileExists(recentLine)){recentFilesList->addLast(recentLine);}
            }
        }
        rif.close();
        status = "Select file to open and hit enter or press \'esc\' to got to welcome screen";
    }else{
        status = "No recent files found. Press \'esc\' to go to home screen.";
    }

}


void Editor::saveStatus(){
    fileSaved = false;
    status= "";
    mode = 's';
    curs_set(0);
    saveFile = fileName;
}

void Editor::save(){
    ofstream ofs(saveFile);
    mainText->begin();
    string text;
    while(mainText->hasNext()){
        text += mainText->next();
    }
    ofs << text;
    ofs.close();
    addToRecentFiles(saveFile);
    status = "File saved!";
    fileSaved = true;

    fileName = "";
    mainText->clear();
    currentPos = -1;/*C'est seulement pour savoir la postion actuelle dedans la liste mais rien a voir avec la position sur l'ecran  */
    LinesCounter = 1; /* Afin de creer le tableau qui contient chaque ligne pour l'imprimer sur l'ecran rien a voir avec la position sur l'ecran*/
    x = 0;
    y = 0;
    undoList->clear();
    redoList->clear();


}

void Editor::reports(){
    mode = 'z';
    status = "1) Lista 2) Palabras Buscadas 3) Palabras Ordenadas.";
}


void Editor::generateRecentReport(){

    int counter = 1;
    string definitions= "digraph D {\n  graph[bgcolor=\"#808080\"  center=true size=\"40,50\" ratio=fill fontsize=20]\n node[fillcolor=olivedrab3 fontcolor=white  style=\"filled, bold\" fontsize=20 ]\n" ;


    string connections;
    string rank;

    if(recentFilesList->getSize()>0){

        recentFilesList->begin();
        while(recentFilesList->hasNext()){

            definitions += to_string(counter) + " [shape=box label = \"" + recentFilesList->next().getName() +"\\n" + recentFilesList->next().getPathGraphViz() + "\" ]\n" ;
            rank += to_string(counter) + " ";
            if(counter != 1){
                connections +=  to_string(counter- 1) + "->"  += to_string(counter) + "[penwidth=1 dir=\"both\"   minlen=3]\n";
            }
            counter ++;
        }
    }
    connections +=  to_string(counter- 1) + "->"  + to_string(1) + "[penwidth=1 dir=\"both\"]\n";

    definitions +=    + "{rank = same " + rank + "}\n" + connections + "}" ;


     generateAndDisplayGraph(definitions);
    //test(definitions);

     }

void Editor::undo(){
   if(undoList->isEmpty()){ return;}
   if(undoList->peek().getPosition() == -1){
       undoList->peek().getPositionList()->end();
       while(undoList->peek().getPositionList()->hasPrevious()){
           int pos = undoList->peek().getPositionList()->previous();
           //  200 ,100, 80, 30, 5
               for(int i = 0; i < undoList->peek().getReplace().length(); i++) {
                   mainText->removeAt(pos);
               }
               for(char i : undoList->peek().getSearch()) {
                   mainText->addAt(i , pos);
                   pos++;
               }
       }
   } else{
        if(undoList->peek().getBackspace()){
            if(undoList->peek().getWord() == '\n'){
                LinesCounter++;
            }
            mainText->addAt( undoList->peek().getWord(), undoList->peek().getPosition());
            currentPos = undoList->peek().getPosition();
            moveTo();
        } else if(undoList->peek().getWord() == '\n'){
            mainText->removeAt(undoList->peek().getPosition() );
            LinesCounter--;
            currentPos = undoList->peek().getPosition() - 1;
            moveTo();
        } else{
            mainText->removeAt(undoList->peek().getPosition() );
            currentPos = undoList->peek().getPosition()-1;
            moveTo();
        }
   }
   undoList->peek().setState(true);
   redoList->push(undoList->pop());
}


void Editor::redo(){
    if(redoList->isEmpty()){ return;}
    if(redoList->peek().getPosition() == -1){
        redoList->peek().getPositionList()->begin(); 
        while(redoList->peek().getPositionList()->hasNext()){
            int pos = redoList->peek().getPositionList()->next();
            //  200 ,100, 80, 30, 5
            for(int i = 0; i < redoList->peek().getSearch().length(); i++) {
                mainText->removeAt(pos);
            }
            for(char i : redoList->peek().getReplace()) {
                mainText->addAt(i , pos);
                pos++;
            }
        }
    }else{
        if(redoList->peek().getBackspace()){
            if(redoList->peek().getWord() == '\n'){
                LinesCounter--;
            }
            mainText->removeAt(redoList->peek().getPosition());
            currentPos = redoList->peek().getPosition() - 1;
            moveTo();
        } else if(redoList->peek().getWord() == '\n'){
            mainText->addAt('\n',  redoList->peek().getPosition() );
            LinesCounter++;
            currentPos = redoList->peek().getPosition();
            moveTo();
        } else{
            mainText->addAt( redoList->peek().getWord() ,redoList->peek().getPosition() );
            currentPos = redoList->peek().getPosition();
            moveTo();
        }
    }
    redoList->peek().setState(false);
    undoList->push(redoList->pop());

}

void Editor::test(string test){

}


void Editor::generateAndDisplayGraph(string graphText){

    ofstream ofs(R"(C:\Users\benav\CLionProjects\EDDPractica1\build\graph.dot)");
    ofs << graphText;
    ofs.close();

    system(R"(dot -Tsvg  C:\Users\benav\CLionProjects\EDDPractica1\build\graph.dot -o C:\Users\benav\CLionProjects\EDDPractica1\build\demo.svg)");
    system(R"(C:\Users\benav\CLionProjects\EDDPractica1\build\\demo.svg)");


}


void Editor::printWelcomeScreen() {
    string welcomeLines[13] = {
            "UNIVERSIDAD DE SAN CARLOS DE GUATEMALA", //0
            "FACULTAD DE INGENIERIA", //1
            "ESTRUCTURAS DE DATOS", //
            "PRACTICA 1", //3
            "BENAVENTI BERNAL FUENTES ROLDAN", //4
            "201021212", //5
            "", //6
            "", //7
            "MENU", //8
            "1. CREAR ARCHIVO", //9
            "2. ABRIR ARCHIVO", //10
            "3. ARCHIVOS RECIENTES", //11
            "4. SALIR" //12
    };


    for (int i = 0; i < LINES - 1; i++) {
        if (i >= sizeof(welcomeLines) / sizeof(welcomeLines[0])) {
            move(i, 0);
            clrtoeol();
        } else {
            if (i == welcomeOption) {
                attron(COLOR_PAIR(2));
            }
            mvprintw(i, 0, welcomeLines[i].c_str());//buff->lines[i].c_str());

            if (i == welcomeOption) {
                attron(COLOR_PAIR(1));
            }
        }
        clrtoeol();
    }
}

void Editor::printEditorScreen() {
    string lines[LinesCounter] = {};
    string line = "";
    int i = 0;
    mainText->begin();

    while (mainText->hasNext()) {
        line += mainText->next();
        if (mainText->next() == '\n') {
            lines[i] = (line);
            i++;
            line = "";
        }
    }
    if (line.compare("") != 0) {
        lines[LinesCounter - 1] = line;
    }


    if (y >= LINES - 1) {
        int height_0 = y - LINES;
        for (int k = height_0; k <= y; ++k) {
            if (k >= (sizeof(lines) / sizeof(lines[0]))) { break; }
            mvprintw(k - height_0, 0, lines[k].c_str());
            clrtoeol();
        }
        return;
    }


    for (int i = 0; i < LINES - 1; i++) // LINES is /* terminal height */
    {
        if (i >= (sizeof(lines) / sizeof(lines[0]))) {
            move(i, 0);
            clrtoeol(); // Erase the current line to the right of the cursor.
        } else {
            mvprintw(i, 0, lines[i].c_str());
        }
        clrtoeol();
    }


}

void Editor::printOpenScreen() {
    clrtoeol();
    for (int i = 0; i < LINES - 1; i++) {
        if (i >= 1) {
            move(i, 0);
            clrtoeol();
        } else
            mvprintw(i, 0, fileName.c_str());//buff->lines[i].c_str());
    }
}

void Editor::printRecentScreen(){
    for(int i=0; i<LINES-1; i++)
    {
        if(i >= recentFilesList->getSize())
        {
            move(i, 0);
            clrtoeol();
        }
        else
        {
            if (i == recentFileCounter) {
                attron(COLOR_PAIR(2));
            }
            string name = recentFilesList->getAt(i).getName();
            int spacesNumber = 40 - name.size();
            for(int j = 0; j < spacesNumber; j++){name += " ";}
            mvprintw(i, 0, ("Name: " + name + "Path: " + recentFilesList->getAt(i).getPath()   ).c_str() );
            if (i == recentFileCounter) {
                attron(COLOR_PAIR(1));
            }
        }
        clrtoeol();
    }

    //recentFileCounter
}

void Editor::printReports(){
    /*
    for (int i = 0; i < LINES - 1; i++) {
        if (i >= sizeof(welcomeLines) / sizeof(welcomeLines[0])) {
            move(i, 0);
            clrtoeol();
        } else {
            if (i == welcomeOption) {
                attron(COLOR_PAIR(2));
            }
            mvprintw(i, 0, welcomeLines[i].c_str());//buff->lines[i].c_str());

            if (i == welcomeOption) {
                attron(COLOR_PAIR(1));
            }
        }
        clrtoeol();
    }*/
}

void Editor::printSave(){

    //presionar ctr+ algo volver al welcome screen descartando cambios con un warning message
    //presionando enter guardar file y volver al modo de edicion habilitar cursor curs_set(2);

    for (int i = 0; i < LINES - 1; i++) {
        if (i >= 1) {
            move(i, 0);
            clrtoeol();
        } else {
            mvprintw(i, 0, saveFile.c_str());
        }
        clrtoeol();
    }
}


void Editor::printScreen() {
    switch (mode) {

        case 'e'://editor
        case 'f'://find and replace
        case 'z':
            printEditorScreen();
            break;
        case 'i': // welcome screen;
            printWelcomeScreen();
            break;
        case 'o'://open screen
            printOpenScreen();
            break;
        case 'r':
            printRecentScreen();
            break;
        case 's':
            printSave();
            break;

        //    printReports();
          //  break;
    }


}

void Editor::updateStatus() {
    switch (mode) {
        case 'i':
            status = "";
            break;
        case 'o':

            break;
        case 'f':

            break;
        case 'e':
            if(!laveWarningSent){
                status = "\tCOL: " + tos(x) + "\tROW: " + tos(y) + "CP: " + tos(currentPos) + "LC: " +
                         tos(LinesCounter) + findReplaceStatus;
            }
            break;
        case 'r':

            break;
    }

}

void Editor::printStatusLine() { //TODO at the end delete status help
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, (status + statusHelp).c_str());
    clrtoeol();
    attroff(A_REVERSE);
    move(y, x);
}

string Editor::tos(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

void Editor::moveLeft() {
    currentPos--;
    if (currentPos < -1) {
        currentPos = -1;
    }

    moveTo();

}


void Editor::moveRight() {

    currentPos++;
    if (currentPos >= mainText->getSize()) {
        currentPos = mainText->getSize() - 1;
    }
    moveTo();

}

void Editor::moveUp() {
    int newY = y - 1;
    int newX = x;
    if (newY < 0) {
        return;
    }
    int ycounter = 0;
    int xcounter = 0;
    int newPos = 0;
    mainText->begin();
    while (mainText->hasNext()) {
        if (mainText->next() == '\n') {
            if (ycounter == newY) {

                break;
            }
            newPos++;
            xcounter = 0;
            ycounter++;
        } else {

            if (ycounter == newY && xcounter == newX) {
                break;
            }
            xcounter++;
            newPos++;
        }
    }
    currentPos = newPos - 1;
    moveTo();

}


void Editor::moveDown() {

    int currentPosCopy = currentPos;
    if (currentPosCopy < 0) { currentPosCopy = 0; }
    if (mainText->getSize() == 0) { return; }
    node<char> *current = mainText->getNodeAt(currentPosCopy);

    if (current != nullptr && current->getData() == '\n') {
        currentPosCopy++;
        current = mainText->getNodeAt(currentPosCopy);
        while (current != nullptr && current->getData() != '\n') {
            currentPosCopy++;
            current = current->getNext();
            if (current == nullptr) { return; }
            if (current->getData() == '\n') { break; }
        }
        currentPos = currentPosCopy;
        moveTo();
        return;
    }


    while (current != nullptr && current->getData() != '\n') {
        currentPosCopy++;
        current = current->getNext();
        if (current == nullptr) { return; }
        if (current->getData() == '\n') {
            currentPosCopy++;
            break;
        }
    }

    current = mainText->getNodeAt(currentPosCopy);
    int counter = 0;
    while (current != nullptr && current->getData() != '\n') {
        current = current->getNext();
        if (counter == x) { break; }
        counter++;
    }
    currentPos = currentPosCopy + counter - 1;
    moveTo();

}

void Editor::moveTo() {
    node<char> *current = mainText->getNodeAt(0);
    if (current == nullptr || currentPos == -1) {//if no data or new pos is -1
        x = 0;
        y = 0;
    } else {
        x = 0;
        y = 0;
        int counter = 0;
        mainText->begin();

        while (mainText->hasNext()) {
            x++;
            if (mainText->next() == '\n') {
                y++;
                x = 0;
            }
            if (counter == currentPos) {
                break;
            }
            counter++;
        }
    }

    //move(y, x);
    //move(50,100);

}

inline bool Editor::fileExists( std::string name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

std::string Editor::GetClipboardText() {
    HANDLE clip = nullptr;
    if (OpenClipboard(nullptr)) {
        clip = GetClipboardData(CF_TEXT);
        CloseClipboard();
    }
    std::string text;
    text = (char *) clip;

    //=== - O R - ====

    unsigned int i = 0;
    text = "";
    while (((char *) clip)[i] != 0) {
        text += ((char *) clip)[i];
        i++;
    }


    return text;
}