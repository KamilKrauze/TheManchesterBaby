#ifndef ASSEMBLER_H
    #define ASSEMBLER_H
    #include "assembler.h"
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    using namespace std;

    string stringPartToString(string line, int start, int end);
    string instToInt(string input);
    int checkInst(string input);
    int assembler();
    void test(int n);
#endif