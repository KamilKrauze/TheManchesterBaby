#include "menu.h"

menuState menu_state = mainmenu;

void mainMenu()
{
    cout << "\n\t=======================================" << endl;
    cout << "\t               ASSEMBLER         " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Insert machine code" << endl;
    cout << "\t\t2. Exit\n" << endl;
}

void machineCodeOptions()
{
}

void determineMenuToShow()
{
    switch (menu_state)
    {
        case mainmenu:
            mainMenu();
            break;
        case mcloaded:
            //Add options
            break;
        case mcnotloaded:
            //Add options
            break;
    }
}