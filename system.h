/*
    Kamil Krauze - 2414951
    Sam Francis - 2413492
    Antoine Bonfili - 2423967
    Dmitrijs Novikovs - 2424525
    Euan West - 2420987
*/
#ifndef SYSTEM_H
#define SYSTEM_H
	#include <string>
    #include <cstdlib>
	#include "system.h"

    #ifdef _WIN32 // Sleep command - https://www.softwaretestinghelp.com/cpp-sleep/ - 09/12/2021
        #include <Windows.h>
    #else
        #include <unistd.h>
    #endif

    using namespace std;
    
    int clear();
#endif