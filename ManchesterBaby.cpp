#include <algorithm>
#include <bitset>

#include "ManchesterBaby.h"

// TODO: remove
#include <iostream>

using namespace std;

ManchesterBaby::ManchesterBaby()
{
    // The initial memory should be 32 lines of '0'
    for (unsigned int i = 0; i < 32; i++)
    {
        string zeros(32, '0');
        store[i] = zeros;
    }
}

void ManchesterBaby::load_program(vector<string> store)
{
    // Copy lines from 'store' to the store.
    size_t line = 0;
    for (; line < store.size(); line++)
    {
        // All lines MUST be 32 bits(chars) long
        if (store[line].length() != 32)
        {
            throw invalid_argument("Line " + to_string(line) + " is not 32 bits long.");
        }

        this->store[line] = store[line];
    }

    // Fill remaining lines with zeros to avoid memory corruption from previous programs
    for (; line < 32; line++)
    {
        string zeros(32, '0');
        this->store[line] = zeros;
    }
}

// Get the current value of the accumulator
int32_t ManchesterBaby::get_accumulator()
{
    return this->accumulator;
}

// Get a string with binary data stored at 'addr' in store
string ManchesterBaby::get_addr(uint8_t addr)
{
    if (addr < 0 || addr > 31)
    {
        throw invalid_argument("The addres must be within [0-31] range.");
    }
    return this->store[addr];
}

// Reverse and parse binary from a string
// TODO: move to a separate file?
int32_t reverse_and_stoi(string s)
{
    reverse(s.begin(), s.end());
    return stoi(s, 0, 2);
}

// Convert a string with binary number written in twos complement to int32_t
// TODO: move to a separate file?
int32_t binstr2s_to_int32_t(string line)
{
    if (line[31] == '1')
    {
        reverse(line.begin(), line.end());
        // Negates the binary value of line, adds 1 and makes it negative.
        // It is one of the ways to convert twos complement binary into an int
        return -((int32_t)(~bitset<32>(line).to_ulong()) + 1);
    }
    else
    {
        // Number is positive, and can simply be parsed
        return reverse_and_stoi(line);
    }
}

// Convert int32_t into a twos complement binary string
// TODO: move to a separate file?
string int32_t_to_binstr2s(int32_t num)
{
    string output;

    if (num < 0)
    {
        // If the number is negative it needs to be stored in twos complement
        // Does the opposite of what is done in binstr2s_to_int32_t() function for negative numbers
        output = bitset<32>(~(-num - 1)).to_string();
    }
    else
    {
        // Simply convert the number into string
        output = bitset<32>(num).to_string();
    }

    reverse(output.begin(), output.end());

    return output;
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
        this->program_counter++;
    }
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
        int op = reverse_and_stoi(present_instruction.substr(13, 3));
        this->line_no = reverse_and_stoi(this->present_instruction.substr(0, 5));

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

    cout << "binstr2s_to_int32_t:" << endl;
    cout << (binstr2s_to_int32_t("10000000001000000000000000000000") == 1025 ? "Pass" : "Fail") << endl;
    cout << (binstr2s_to_int32_t("10110110010000000000000000000000") == 621 ? "Pass" : "Fail") << endl;
    cout << (binstr2s_to_int32_t("00000000000000000000000000000000") == 0 ? "Pass" : "Fail") << endl;
    cout << (binstr2s_to_int32_t("11111111111111111111111111111110") == 2147483647 ? "Pass" : "Fail") << endl;
    cout << endl;
    cout << (binstr2s_to_int32_t("11111111110111111111111111111111") == -1025 ? "Pass" : "Fail") << endl;
    cout << (binstr2s_to_int32_t("11111111111111111111111111111111") == -1 ? "Pass" : "Fail") << endl;
    cout << (binstr2s_to_int32_t("00000000000000000000000000000001") == -2147483648 ? "Pass" : "Fail") << endl;
    cout << endl;
    cout << (binstr2s_to_int32_t("00000000000000000000000000000001") == -2147483648 ? "Pass" : "Fail") << endl;
    cout << "int32_t_to_binstr2s: " << endl;
    cout << ("10000000001000000000000000000000" == int32_t_to_binstr2s(1025) ? "Pass" : "Fail") << endl;
    cout << ("10110110010000000000000000000000" == int32_t_to_binstr2s(621) ? "Pass" : "Fail") << endl;
    cout << ("00000000000000000000000000000000" == int32_t_to_binstr2s(0) ? "Pass" : "Fail") << endl;
    cout << ("11111111111111111111111111111110" == int32_t_to_binstr2s(2147483647) ? "Pass" : "Fail") << endl;
    cout << endl;
    cout << ("11111111110111111111111111111111" == int32_t_to_binstr2s(-1025) ? "Pass" : "Fail") << endl;
    cout << ("11111111111111111111111111111111" == int32_t_to_binstr2s(-1) ? "Pass" : "Fail") << endl;
    cout << ("00000000000000000000000000000001" == int32_t_to_binstr2s(-2147483648) ? "Pass" : "Fail") << endl;
    cout << endl;
    cout << ("00000000000000000000000000000001" == int32_t_to_binstr2s(-2147483648) ? "Pass" : "Fail") << endl;

    // BabyTest1-MC.txt
    test.load_program(vector<string>{"00000000000000000000000000000000",
                                     "11100000000000100000000000000000",
                                     "00010000000000010000000000000000",
                                     "10010000000001100000000000000000",
                                     "10010000000000100000000000000000",
                                     "10010000000001100000000000000000",
                                     "00000000000001110000000000000000",
                                     "10000000001000000000000000000000",
                                     "10110110010000000000000000000000",
                                     "00000000000000000000000000000000"});
    test.start();
    cout << "Expected: 1646, Got: " << test.get_accumulator() << " == " << binstr2s_to_int32_t(test.get_addr(9)) << endl;
    return 0;
}