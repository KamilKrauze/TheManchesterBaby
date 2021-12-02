#ifndef MANCHESTER_BABY_H
#define MANCHESTER_BABY_H
#include <string>

class ManchesterBaby
{
public:
    ManchesterBaby();

    void start();

    // Get a copy of a word from the store
    std::string get_addr(short idx);
    // Get the accumulator value
    unsigned int get_accumulator();

    void load_program(std::string filename);
    // TODO: expect a vector of instructions? Should probably be
    void load_program(std::string *store);

private:
    /*
    TODO: create a class for instrucion?
    Should be nicer to use and work with, but I think the goal is
    to be as close to the internal processes of SSEM, and any processing
    of the instruction is undesirable.
    */

    // Because of the weird requirements of of the project, the binary is stored in strings
    // Manchester baby had a memory of 32 words, so an array can be used to simulate the whole memory
    // Each string must be 32 chars long, but there isn't a way to enforce that
    std::string store[32];

    // Instruction that is being executed
    std::string present_instruction;
    // Address of the current instruction
    uint32_t program_counter;
    // The Accumulator
    uint32_t accumulator;

    // The operations should only be called from execution loop

    // 000 - 0
    void JMP();
    // 100 - 1
    void JRP();
    // 010 - 2
    void LDN();
    // 110 - 3
    void STO();
    // 001 OR 101 - 4 OR 5
    void SUB();
    // 011 - 6
    void CMP();
    // 111 - 7
    void STP(); // TODO: remove
};

#endif // !MANCHESTER_BABY_H