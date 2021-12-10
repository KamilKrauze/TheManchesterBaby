/*
	Kamil Krauze - 2414951
	Sam Francis - 2413492
	Antoine Bonfili - 2423967
	Dmitrijs Novikovs - 2424525
	Euan West - 2420987
*/
#ifndef ASSEMBLER_H
    #define ASSEMBLER_H
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    using namespace std;

    string stringPartToString(string line, int start, int end);
    string instToInt(string input);
    int checkInst(string input);
    int checkVar(const vector<string> variables, string stringVar);
    int assembler(const string* const fpMachineCode, const string* const outputFP);
    void test();
#endif
