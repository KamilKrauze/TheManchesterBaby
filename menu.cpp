#include <iostream>
#include <string>

#include "system.h"
#include "assembler.h"
#include "ManchesterBaby.h"
#include "menu.h"

using namespace std;

void mainMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t               MAIN MENU               " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Manchester Baby" << endl;
    cout << "\t\t2. Assembler" << endl;
    cout << "\t\t3. Exit" << endl;
    cout << endl;

    cout << "Enter a number that corresponds to the options above: " << endl;
}

void manchesterBabyMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t            MANCHESTER BABY            " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Run until halt" << endl;
    cout << "\t\t2. Execute a single step" << endl;
    cout << "\t\t3. Load machine code from a file" << endl;
    cout << "\t\t4. Display the accumulator value" << endl;
    cout << "\t\t5. Display a line from the store" << endl;
    cout << "\t\t6. Display all lines of the store" << endl;
    cout << "\t\tb. Return to main menu" << endl;
    cout << "\t\te. Exit" << endl;
}

void manchesterBabyChoice()
{
    ManchesterBaby manBaby;

    string choice;
    string fp = "";

    while (true)
    {
        manchesterBabyMenu();
        cout << "Using machine code file: \"" << fp << "\"" << endl;
        cout << "Your choice: ";
        cin >> choice;

        if (choice == "1") // Run instructions
        {
            manBaby.run();
            cout << "Manchester Baby halted.";
        }
        else if (choice == "2") // Insert new machine code file
        {
            manBaby.step();
        }
        else if (choice == "3") // Load file
        {
            manBaby.reset();
            while (true)
            {
                cout << "Enter a filepath of your machine code: " << endl;
                cin >> fp;

                try
                {
                    manBaby.readMachineCode(&fp);
                }
                catch (const invalid_argument &e)
                {
                    cerr << e.what() << endl;
                    continue;
                }
                break;
            }
            cout << "Loaded \"" << fp << "\"" << endl;
        }
        else if (choice == "4") // Display the accumulator
        {
            cout << "Accumulator: " << manBaby.get_accumulator() << endl;
        }
        else if (choice == "5") // Display line
        {
            while (true)
            {
                cout << "Enter a memory address to print: ";
                int addr;
                cin >> addr;
                if (cin.fail())
                {
                    cerr << "Could not parse an integer" << endl;
                    cin.clear();
                    cin.ignore(INT64_MAX, '\n');
                    continue;
                }

                try
                {
                    cout << addr << ": " << manBaby.get_addr(addr) << endl;
                }
                catch (const exception &e)
                {
                    cerr << e.what() << endl;
                    cin.clear();
                    cin.ignore(INT64_MAX, '\n');
                    continue;
                }
                break;
            }
        }
        else if (choice == "6") // Display all lines
        {
            cout << "===============================" << endl;
            for (int addr = 0; addr < 32; addr++)
                cout << ((addr > 9) ? "" : "0") << addr << ": " << manBaby.get_addr(addr) << endl;
            cout << "===============================" << endl;
        }
        else if (choice == "b") // Return to main menu
        {
            mainMenuChoice();
            break;
        }
        else if (choice == "e") // Exit program
        {
            exit(0);
        }
        else
        {
            cout << "INCORRECT INPUT: Option " << choice << " does not exist in this menu" << endl;
            sleep(2);
        }
    }
}

void mainMenuChoice()
{
    string choice;
    string fp;

    while (true)
    {
        clear();
        mainMenu();
        cout << "User: " << endl;
        cin >> choice;

        if (choice == "1") //Manchester Baby menu
        {
            manchesterBabyChoice();
            break;
        }
        else if (choice == "2") // Assembly menu
        {
            string assemblyFP;
            string outputFP;

            cout << "Enter a filepath of your assembly instructions: " << endl;
            cin >> assemblyFP;

            cout << "Enter a filepath of where you want to output your file: " << endl;
            cin >> outputFP;

            assembler(&assemblyFP, &outputFP);
        }
        else if (choice == "q") // Exit
        {
            exit(0); // Exit program
        }
        else
        {
            cout << "INCORRECT INPUT: Option " << choice << " does not exist in this menu" << endl;
            sleep(2);
        }
    }
}