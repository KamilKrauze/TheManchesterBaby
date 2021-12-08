#ifndef MENU_H
    #define MENU_H
    #include <iostream>
    #include <string>

    #include "menu.h"
    #include "system.h"
    #include "assembler.h"

    using namespace std;

    enum menuState {
        mainmenu,
        mcloaded,
        mcnotloaded,
    };
    
    extern menuState menu_state;

    // Helper functions on displaying menu (text based)
    void mainMenu();
    void mainMenuChoice();
    void machineCodeOptions();

    void determineMenuToShow();
    
#endif