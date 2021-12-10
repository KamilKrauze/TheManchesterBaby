/*
Kamil Krauze - 2414951
Sam Francis - 2413492
Antoine Bonfili - 2423967
Dmitrijs Novikovs - 2424525
Euan West - 2420987
*/
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "ManchesterBaby.h"
#include "menu.h"
#include "convert.h"

using namespace std;
ManchesterBaby::ManchesterBaby()
{
    this->program_counter = 0;
    this->accumulator = 0;

    this->stop = false;
    this->test_flip_flop = false;

    // The initial memory should be 32 lines of '0'
    for (size_t i = 0; i < 32; i++)
    {
        string zeros(32, '0');
        store[i] = zeros;
    }
}

void ManchesterBaby::reset()
{
    this->program_counter = 0;
    this->accumulator = 0;

    this->stop = false;
    this->test_flip_flop = false;

    for (size_t i = 0; i < 32; i++)
    {
        string zeros(32, '0');
        store[i] = zeros;
    }
}

void ManchesterBaby::load_program(vector<string> newStore)
{
    // Copy lines from 'store' to the store.
    size_t line = 0;
    for (; line < newStore.size(); line++)
    {
        // All lines MUST be 32 bits(chars) long
        if (store[line].length() != 32)
        {
            throw invalid_argument("Line " + to_string(line) + " is not 32 bits long.");
        }

        this->store[line] = newStore[line];
    }

    // Fill remaining lines with zeros to avoid memory corruption from previous programs
    for (; line < 32; line++)
    {
        string zeros(32, '0');
        this->store[line] = zeros;
    }
}

void ManchesterBaby::readMachineCode(const string *const filepath)
{
    vector<string> newStore;

    ifstream reader;
    reader.open(*filepath);
    if (!reader.good())
    {
        throw invalid_argument("Invalid input filepath. Incorrect file type and/or file does not exist.");
    }

    string line(32, '0');
    while (getline(reader, line))
    {
        for (size_t i = 0; i < line.length() - 1; i++)
        {
            if (line[i] == '0' || line[i] == '1')
                continue;
            else
            {
                throw invalid_argument("File is not in a binary format. Must be only 1s and 0s.");
                break;
            }
        }
        newStore.push_back(line);
    }

    load_program(newStore);
}

// Get the current value of the accumulator
int32_t ManchesterBaby::get_accumulator()
{
    return this->accumulator;
}

// Get a string with binary data stored at 'addr' in store
string ManchesterBaby::get_addr(uint8_t addr)
{
    if (addr > 31)
    {
        throw invalid_argument("The address must be within [0-31] range.");
    }
    return this->store[addr];
}

// Loads store line into program counter
void ManchesterBaby::JMP()
{
    this->program_counter = binstr2s_to_int32_t(this->store[this->line_no]);
}

// Adds store line to program counter

void ManchesterBaby::JRP()
{
    this->program_counter += binstr2s_to_int32_t(this->store[this->line_no]);
}

// Loads negated store line into the accumulator
void ManchesterBaby::LDN()
{
    this->accumulator = -binstr2s_to_int32_t(this->store[this->line_no]);
}

// Stores the accumulator value into a store line
void ManchesterBaby::STO()
{
    this->store[this->line_no] = int32_t_to_binstr2s(this->accumulator);
}

// Subtracts a store line from the accumulator
void ManchesterBaby::SUB()
{
    this->accumulator -= binstr2s_to_int32_t(this->store[this->line_no]);
}

// Skips the next instruction if the accumulator is negative
void ManchesterBaby::CMP()
{
    if (this->accumulator < 0)
    {
        this->test_flip_flop = true;
    }
}

void ManchesterBaby::STP()
{
    // Set the stop flag
    this->stop = true;
}

void ManchesterBaby::fetch()
{
    // The program counter is always incremented before execution
    // Which is why the program code starts at store[1]
    if (this->test_flip_flop)
    {
        this->program_counter++;
        this->test_flip_flop = false;
    }

    this->program_counter = (this->program_counter + 1) % 32;
    this->present_instruction = this->store[this->program_counter];
}

void ManchesterBaby::decode()
{
    // Get the bits corresponding to the instruction (13,14,15)
    this->op = reverse_and_stoi(this->present_instruction.substr(13, 3));
    // Get the bits corresponding to the operand of the instruction
    this->line_no = reverse_and_stoi(this->present_instruction.substr(0, 5));
}

void ManchesterBaby::execute()
{
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
        STP();
        break;
    }
}

void ManchesterBaby::printout()
{
    cout << endl;
    cout << "\t=======================================" << endl;
    cout << "\t                RUNNING                " << endl;
    cout << "\t=======================================" << endl;

    cout << "\t\tCurrent Line : " << present_instruction << endl;
    cout << "\t\tProgram Counter : " << program_counter << endl;
    cout << "\t\tAccumulator : " << accumulator << endl;
}

void ManchesterBaby::run()
{
    while (!this->stop)
    {
        this->fetch();
        this->decode();
        this->execute();
        this->printout();
    }
}

bool ManchesterBaby::step()
{
    if (!this->stop)
    {
        this->fetch();
        this->decode();
        this->execute();
        this->printout();

        return true;
    }

    return false;
}

// int main()
// {
//     ManchesterBaby test;

//     cout << "binstr2s_to_int32_t:" << endl;
//     cout << (binstr2s_to_int32_t("10000000001000000000000000000000") == 1025 ? "Pass" : "Fail") << endl;
//     cout << (binstr2s_to_int32_t("10110110010000000000000000000000") == 621 ? "Pass" : "Fail") << endl;
//     cout << (binstr2s_to_int32_t("00000000000000000000000000000000") == 0 ? "Pass" : "Fail") << endl;
//     cout << (binstr2s_to_int32_t("11111111111111111111111111111110") == 2147483647 ? "Pass" : "Fail") << endl;
//     cout << endl;
//     cout << (binstr2s_to_int32_t("11111111110111111111111111111111") == -1025 ? "Pass" : "Fail") << endl;
//     cout << (binstr2s_to_int32_t("11111111111111111111111111111111") == -1 ? "Pass" : "Fail") << endl;
//     cout << (binstr2s_to_int32_t("00000000000000000000000000000001") == -2147483648 ? "Pass" : "Fail") << endl;
//     cout << endl;
//     cout << (binstr2s_to_int32_t("00000000000000000000000000000001") == -2147483648 ? "Pass" : "Fail") << endl;
//     cout << "int32_t_to_binstr2s: " << endl;
//     cout << ("10000000001000000000000000000000" == int32_t_to_binstr2s(1025) ? "Pass" : "Fail") << endl;
//     cout << ("10110110010000000000000000000000" == int32_t_to_binstr2s(621) ? "Pass" : "Fail") << endl;
//     cout << ("00000000000000000000000000000000" == int32_t_to_binstr2s(0) ? "Pass" : "Fail") << endl;
//     cout << ("11111111111111111111111111111110" == int32_t_to_binstr2s(2147483647) ? "Pass" : "Fail") << endl;
//     cout << endl;
//     cout << ("11111111110111111111111111111111" == int32_t_to_binstr2s(-1025) ? "Pass" : "Fail") << endl;
//     cout << ("11111111111111111111111111111111" == int32_t_to_binstr2s(-1) ? "Pass" : "Fail") << endl;
//     cout << ("00000000000000000000000000000001" == int32_t_to_binstr2s(-2147483648) ? "Pass" : "Fail") << endl;
//     cout << endl;

//     // BabyTest1-MC.txt
//     test.load_program(vector<string>{"00000000000000000000000000000000",
//                                      "11100000000000100000000000000000",
//                                      "00010000000000010000000000000000",
//                                      "10010000000001100000000000000000",
//                                      "10010000000000100000000000000000",
//                                      "10010000000001100000000000000000",
//                                      "00000000000001110000000000000000",
//                                      "10000000001000000000000000000000",
//                                      "10110110010000000000000000000000",
//                                      "00000000000000000000000000000000"});
//     test.run();
//     cout << "Expected: 1646, Got: " << test.get_accumulator() << " == " << binstr2s_to_int32_t(test.get_addr(9)) << endl;
//     return 0;
// }
