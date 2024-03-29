/*
    Kamil Krauze - 2414951
    Sam Francis - 2413492
    Antoine Bonfili - 2423967
    Dmitrijs Novikovs - 2424525
    Euan West - 2420987
*/
#ifndef MANCHESTER_BABY_H
#define MANCHESTER_BABY_H

class ManchesterBaby
{
public:
    ManchesterBaby();

    // Sets memory and all registers to their default values.
    void reset();

    // Run the currently loaded program until stop
    void run();
    // Fetch and execute a signgle instruction
    bool step();

    // Get a copy of a word from the store
    std::string get_addr(uint8_t addr);
    // Get the accumulator value
    int32_t get_accumulator();

    // Load a program from an array of strings with binary code
    // Each string MUST be 32 characters long, and there can be up to 32 strings
    void load_program(std::vector<std::string> newStore);

    void readMachineCode(const std::string *const filepath);

private:
    // Because of the weird requirements of of the project, the binary is stored in strings
    // Manchester baby had a memory of 32 words, so an array can be used to simulate the whole memory
    // Each string must be 32 chars long, but there isn't a way to enforce that
    // TODO: use a bitset to store the 'store'?
    std::string store[32];

    // Instruction that is being executed
    std::string present_instruction;
    // Address of the current instruction
    uint32_t program_counter;
    // The Accumulator
    int32_t accumulator;

    // Stores line number of current operation to avoid passing it to every function
    uint8_t line_no;
    // Stores the current operation
    uint8_t op;

    bool stop;
    bool test_flip_flop;

    void fetch();
    void decode();
    void execute();
    void printout();

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
    void STP();
};

#endif // !MANCHESTER_BABY_H
