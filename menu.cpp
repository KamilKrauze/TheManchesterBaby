#include "menu.h"

void mainMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t               MAIN MENU               " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Manchester Baby" << endl;
    cout << "\t\t2. Insert assembly instructions" << endl;
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

    cout << "\t\t1. Run" << endl;
    cout << "\t\t2. Insert new machine code file" << endl;
    cout << "\t\t3. Display the accumulator value" << endl;
    cout << "\t\t4. Return to main menu" << endl;
    cout << "\t\t5. Exit" << endl;

    cout << "Enter a number that corresponds to the options above: " << endl;
}

void manchesterBabyChoice()
{
    ManchesterBaby manBaby;

    string choice;

    while (true)
    {
        manchesterBabyMenu();
        cout << "User: " << endl;
        cin >> choice;

        if (!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            sleep(2);
            continue;
        }
        else
        {
            if (choice == "1") // Run instructions
            {
                manBaby.run();
            }
            else if (choice == "2") // Insert new machine code file
            {
                string fp;

                cout << "Enter a filepath of your machine code: " << endl;
                cin >> fp;

                manBaby.readMachineCode(&fp);
                cout << "Loaded " << fp << endl;
            }
            else if (choice == "3") // Display the accumulator
            {
                cout << "Accumulator: " << manBaby.get_accumulator() << endl;
            }
            else if (choice == "4") // Return to main menu
            {
                mainMenuChoice();
                break;
            }
            else if (choice == "5")
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
}

// void assemblyChoice()
// {
//     string choice; // User input
//     string fp; // Filepath of assembly instructions
//     cout << "Enter a filepath of your assembly instructions file: " << endl;
//     bool isFpValid = false;
//     while(isFpValid != true)
//     {
//         cin >> fp;
//         isFpValid = validateFilePath(&fp);
//     }
//     while(true)
//     {
//         clear();
//         cout << "Filepath: " << fp << endl;
//         assemblyMenu();
//         cout << "User: " << endl;
//         cin >> choice;
//         if(!validateInput(&choice))
//         {
//             cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
//             sleep(1);
//             continue;
//         }
//         else
//         {
//             if(choice == "1") // Run instructions
//             {
//                 assembler(&fp);
//                 sleep(3);
//             }
//             else if (choice == "2") // Insert new assembly instruction file
//             {
//                 cout << "Enter a filepath of your assembly instructions file: " << endl;
//                 bool isFpValid = false;
//                 while(isFpValid != true)
//                 {
//                     cin >> fp;
//                     isFpValid = validateFilePath(&fp);
//                 }
//             }
//             else if (choice == "3") // Show as machine code
//             {
//             }
//             else if (choice == "4") // Export as machine code to file
//             {
//             }
//             else if (choice == "5") // Return to main menu
//             {
//                 mainMenuChoice();
//                 break;
//             }
//             else if (choice == "6")
//             {
//                 exit(0); // Exit program
//             }
//             else
//             {
//                 cout << "INCORRECT INPUT: Option " << choice << " does not exist in this menu" << endl;
//                 sleep(2);
//             }
//         }
//     }
// }

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

        if (!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            sleep(2);
            continue;
        }
        else
        {
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
            else if (choice == "3") // Exit
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
}

bool validateInput(const string *const text)
{
    regex pattern("[0-9]");             //Declares a regex pattern where if it contains the full number set
    return regex_match(*text, pattern); //Return true if string contains numbers only
}
