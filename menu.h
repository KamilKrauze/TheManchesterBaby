/*
    Kamil Krauze - 2414951
    Sam Francis - 2413492
    Antoine Bonfili - 2423967
    Dmitrijs Novikovs - 2424525
    Euan West - 2420987
*/
#ifndef MENU_H
#define MENU_H
    // Helper functions on displaying menu (text based)
    void mainMenu();
    void manchesterBabyMenu();
    void assemblyMenu();
    
    // User input for every type of menu
    void mainMenuChoice();
    void manchesterBabyChoice();
    void assemblyChoice();

    bool validateInput(const std::string* const text); //Check if number is numerical
    bool validateFilePath(const std::string* const filepath); //Check if filepath is exists - https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-14-17-c - 09/12/2021
#endif