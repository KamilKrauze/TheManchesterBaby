#include <algorithm>

#include "ManchesterBaby.h"

// TODO: remove
#include <iostream>

using namespace std;

ManchesterBaby::ManchesterBaby()
{
    // The initial memory should be 32 lines of '0'
    for (unsigned int i = 0; i < 32; i++)
    {
        string line(32, '0');
        store[i] = line;
    }
}

int unsignedbinstr_to_int(string s)
{
    reverse(s.begin(), s.end());
    return stoi(s, 0, 2);
}

void ManchesterBaby::JMP()
{
    throw logic_error("Not implemented");
}

void ManchesterBaby::JRP()
{
    throw logic_error("Not implemented");
}

void ManchesterBaby::LDN()
{
    throw logic_error("Not implemented");
}

void ManchesterBaby::STO()
{
    throw logic_error("Not implemented");
}

void ManchesterBaby::SUB()
{
    throw logic_error("Not implemented");
}

void ManchesterBaby::CMP()
{
    throw logic_error("Not implemented");
}

void ManchesterBaby::start()
{
    program_counter = 0;
    accumulator = 0;

    bool stop = false;
    while (!stop)
    {
        // The program counter is always incremented before execution
        // Which is why the program code starts at store[1]
        program_counter++;
        // Fetch
        present_instruction = store[program_counter];

        // I would just use switch-case with the substring, but
        // strings can not be in the expression of the switch
        // Thanks, C++

        // Get the bits corresponding to the instruction (13,14,15)
        int op = unsignedbinstr_to_int(present_instruction.substr(13, 3));

        switch (op)
        {
        case 0:
            JMP();
            break;
        case 1:
            JRP();
            break;
        case 2:
            LDN();
            break;
        case 3:
            STO();
            break;
        case 4:
        case 5:
            SUB();
            break;
        case 6:
            CMP();
            break;
        case 7:
            // STP();
            stop = true;
            break;
        default:
            break;
        }
    }
}

int main()
{

    ManchesterBaby test;
    return 0;
}