#ifndef MENU_H
    #define MENU_H
    #include <iostream>
    #include <string>
    #include <regex> //Regular expressions library
   
    #include "menu.h"
    #include "system.h"
    #include "assembler.h"
    #include "ManchesterBaby.h"

    using namespace std;

    // Helper functions on displaying menu (text based)
    void mainMenu();
    void manchesterBabyMenu();
    void assemblyMenu();
    
    // User input for every type of menu
    void mainMenuChoice();
    void manchesterBabyChoice();
    void assemblyChoice();

    bool validateInput(const string* const text); //Check if number is numerical
    bool validateFilePath(const string* const filepath); //Check if filepath is exists - https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c - 09/12/2021
#endif