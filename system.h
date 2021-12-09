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