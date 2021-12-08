#include "menu.h"

void mainMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t            MANCHESTER BABY            " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Insert machine code" << endl;
    cout << "\t\t2. Insert assembly instructions" << endl;
    cout << "\t\t3. Exit\n" << endl;

    cout << "Enter a number that corresponds to the options above: " << endl;
}

void machineCodeMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t              MACHINE CODE             " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Run" << endl;
    cout << "\t\t2. Reload machine code" << endl;
    cout << "\t\t3. Insert new machine code" << endl;
    cout << "\t\t4. Show code in assembly" << endl;
    cout << "\t\t5. Exit" << endl;

    cout << "Enter a number that corresponds to the options above: " << endl;
}

void assemblyMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t                ASSEMBLY               " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Run" << endl;
    cout << "\t\t2. Reload assembly instructions file" << endl;
    cout << "\t\t3. Insert new assembly instructions file" << endl;
    cout << "\t\t4. Show it in machine code" << endl;
    cout << "\t\t5. Export assembly instructions to file as machine code" << endl;
    cout << "\t\t6. Exit" << endl;

    cout << "Enter a number that corresponds to the options above: " << endl;
}

void machineCodeChoice()
{
    string choice;
    
    while(true)
    {
        clear();
        machineCodeMenu();
        cout << "User: " << endl; 
        cin >> choice;

        if(!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            continue;
        }
        else
        {
            if(choice == "1") // Run instructions
            {
                break;
            }
            else if (choice == "2") // Reload machine code file
            {
                break;
            }
            else if (choice == "3") // Insert new machine code file
            {
                break;
            }
            else if (choice == "4") // Show code in assembly
            {
                break;
            }
            else if (choice == "5")
            {
                exit(0); // Exit program
            }
            else
                cout << "INCORRECT INPUT: Option " << choice << " does not exist in this menu" << endl;
        }
    }
}

void assemblyChoice()
{
    string choice;
    
    while(true)
    {
        clear();
        assemblyMenu();
        cout << "User: " << endl; 
        cin >> choice;

        if(!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            continue;
        }
        else
        {
            if(choice == "1") // Run instructions
            {
            }
            else if (choice == "2") // Reload assembly instructions file
            {
            }
            else if (choice == "3") // Insert new assembly instruction file
            {
            }
            else if (choice == "4") // Show as machine code
            {
            }
            else if (choice == "5") // Export as machine code to file
            {
            }
            else if (choice == "6")
            {
                exit(0); // Exit program
            }
            else
                cout << "INCORRECT INPUT: Option " << choice << " does not exist in this menu" << endl;
        }
    }
}

void mainMenuChoice()
{
    string choice;
    
    while(true)
    {
        clear();
        mainMenu();
        cout << "User: " << endl; 
        cin >> choice;

        if(!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            continue;
        }
        else
        {
            if(choice == "1") //Machine code menu
            {
                machineCodeChoice();
                break;
            }
            else if (choice == "2") // Assembly menu
            {
                assemblyChoice();
                break;
            }
            else if(choice == "3") // Exit
            {
                exit(0); // Exit program
            }
            else
                cout << "INCORRECT INPUT: Option " << choice << " does not exist in this menu" << endl;
        }
    }
}



bool validateInput(const string* const text)
{
    regex pattern("[0-9]"); //Declares a regex pattern where if it contains the full number set
    return regex_match(*text, pattern); //Return true if string contains numbers only
}