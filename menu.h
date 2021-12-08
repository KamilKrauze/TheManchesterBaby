#ifndef MENU_H
    #define MENU_H
    #include <iostream>
    #include <string>
    #include <regex> //Regular expressions library

    #include "menu.h"
    #include "system.h"
    #include "assembler.h"

    using namespace std;

    // Helper functions on displaying menu (text based)
    void mainMenu();
    void machineCodeMenu();
    void assemblyMenu();
    
    // User input for every type of menu
    void mainMenuChoice();
    void machineCodeChoice();
    void assemblyChoice();

    bool validateInput(const string* const text); //Check if number is numerical

    
#endif