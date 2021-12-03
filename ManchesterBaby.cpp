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
        string line(32, '0');
        store[i] = line;
    }
}

void ManchesterBaby::load_program(vector<string> store)
{
    for (size_t line = 0; (line < 31) && (line < store.size()); line++)
    {
        this->store[line] = store[line];
    }
}

int32_t ManchesterBaby::get_accumulator()
{
    return this->accumulator;
}

string ManchesterBaby::get_addr(uint8_t addr)
{
    return this->store[addr];
}

int32_t reverse_and_stoi(string s)
{
    reverse(s.begin(), s.end());
    return stoi(s, 0, 2);
}

int32_t binstr2s_to_int32_t(string line)
{
    if (line[31] == '1')
    {
        reverse(line.begin(), line.end());
        // Bruh
        return -((int32_t)(~bitset<32>(line).to_ulong()) + 1);
    }
    else
    {
        return reverse_and_stoi(line);
    }
}

string int32_t_to_binstr2s(int32_t num)
{
    string output;

    if (num < 0)
    {
        output = bitset<32>(~(-num - 1)).to_string();
    }
    else
    {
        output = bitset<32>(num).to_string();
    }

    reverse(output.begin(), output.end());

    return output;
}

void ManchesterBaby::JMP()
{
    this->program_counter = binstr2s_to_int32_t(this->store[this->line_no]);
}

void ManchesterBaby::JRP()
{
    this->program_counter += binstr2s_to_int32_t(this->store[this->line_no]);
}

void ManchesterBaby::LDN()
{
    this->accumulator = binstr2s_to_int32_t(this->store[this->line_no]);
}

void ManchesterBaby::STO()
{
    this->store[this->line_no] = int32_t_to_binstr2s(this->accumulator);
}

void ManchesterBaby::SUB()
{
    this->accumulator -= binstr2s_to_int32_t(this->store[this->line_no]);
}

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
    cout << "Expected: 404, Got: " << test.get_accumulator() << " == " << binstr2s_to_int32_t(test.get_addr(9)) << endl;
    return 0;
}