#include "menu.h"

void mainMenu()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t               MAIN MENU               " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\t1. Manchester Baby" << endl;
    cout << "\t\t2. Insert assembly instructions" << endl;
    cout << "\t\t3. Exit\n" << endl;

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
    cout << "\t\t3. Show code in assembly" << endl;
    cout << "\t\t4. Return to main menu" << endl;
    cout << "\t\t5. Exit" << endl;

    cout << "Enter a number that corresponds to the options above: " << endl;
}

void manchesterBabyChoice()
{
    string choice;
    string fp;

    cout << "Enter a filepath of your machine code: " << endl;
    bool isFpValid = false;
    while(isFpValid != true)
    {
        cin >> fp;
        isFpValid = validateFilePath(&fp);
    }
    
    while(true)
    {
        clear();
        cout << "Filepath: " << fp << endl;
        manchesterBabyMenu();
        cout << "User: " << endl; 
        cin >> choice;

        if(!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            sleep(2);
            continue;
        }
        else
        {
            if(choice == "1") // Run instructions
            {
                exit(0); // TODO: Replace it with the manchester baby class baby.run()...
            }
            else if (choice == "2") // Insert new machine code file
            {
                break; // TODO: Use manchester baby read from file function to get instructions.
            }
            else if (choice == "3") // Show code in assembly
            {
                break; // Possible implementation
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
    
    while(true)
    {
        clear();
        mainMenu();
        cout << "User: " << endl; 
        cin >> choice;

        if(!validateInput(&choice))
        {
            cout << "INCORRECT INPUT: " << choice << " is not an integer" << endl;
            sleep(2);
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
                string assemblyFP;
                string outputFP;

                cout << "Enter a filepath of your assembly instructions: " << endl;
                bool isFpValid = false;
                while(isFpValid != true)
                {
                    cin >> assemblyFP;
                    isFpValid = validateFilePath(&assemblyFP);
                }
                
                cout << "Enter a filepath of where you want to output your file: " << endl;
                isFpValid = false;
                while(isFpValid != true)
                {
                    cin >> outputFP;
                    isFpValid = validateFilePath(&outputFP);
                }
                
                assembler(&assemblyFP, &outputFP);
            }
            else if(choice == "3") // Exit
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

bool validateInput(const string* const text)
{
    regex pattern("[0-9]"); //Declares a regex pattern where if it contains the full number set
    return regex_match(*text, pattern); //Return true if string contains numbers only
}

bool validateFilePath(const string* const filepath) //Check if filepath is exists - https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c - 09/12/2021
{
    ifstream infile(*filepath);
    return infile.good();
}