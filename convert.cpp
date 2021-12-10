#include <algorithm>
#include <bitset>
#include <string>

#include "convert.h"

using namespace std;

// Reverse and parse binary from a string
int32_t reverse_and_stoi(string s)
{
    reverse(s.begin(), s.end());
    return stoi(s, 0, 2);
}

// Convert a string with binary number written in twos complement to int32_t
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