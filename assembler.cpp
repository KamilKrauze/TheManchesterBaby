#include "assembler.h"

//makes a string out of a bigger string (might exist as a function but oh well)
string stringPartToString(string line, int start, int end)
{
	return line.substr(start, end - start);
}

//replace string by instruction number
string instToInt(string input)
{
	//bool test = false;
	string result = "***";
	string inst[8] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP"};
	string bin[8] = {"000", "001", "010", "011", "100", "101", "110", "111"};
	for (int i = 0; i < 8; ++i)
	{
		//cout << input << " = " << inst[i] << "?" << endl;
		if (/*input.compare(inst[i])==1*/ input == inst[i])
		{
			//cout << "yes"<<endl;
			//test = true;
			return bin[i];
		}
	}
	return result;
}

//check if string is an instruction
int checkInst(string input)
{
	int result = 0;
	string inst[8] = {"JMP", "JRP", "LDN", "STO", "SUB", "SUB", "CMP", "STP"};
	for (int i = 0; i < 8; ++i)
	{
		if (input == inst[i])
		{
			return 1;
		}
		else
		{
			result = 0;
		}
	}
	return result;
}

/*void addToArray(string &varName[], string newVar, int &varValue[], int newValue){
	int size = varValue.size();

	string newNameArray[size+1];
	int newValueArray[size+1];

	for (int i = 0; i < size; ++i)
	{
		newNameArray[i]=varName
	}
}*/

int assembler(const string *const assemblyFP, const string *const outputFP)
{
	//dw about that for now
	//int initialAddress;

	//line to print on the mc file
	char output[32];
	for (int i = 0; i < 32; ++i)
	{
		output[i] = '0';
	}

	//variables to read the assembly language
	string line;

	//vectors to store variables and their value
	vector<string> variables;
	vector<int> variablesNum;

	//line counter and comment counter, used later for the variables
	int lineCounter = 0;
	int minusComment = 0;

	//things to read/write
	ifstream reader;
	reader.open(*assemblyFP);
	if (!reader.good())
	{
		cout << "Error opening input file" << endl;
		return 1;
	}

	ofstream writer;
	writer.open(*outputFP, ios::out | ios::trunc);
	if (!writer.good())
	{
		cerr << "Error opening file for output" << endl;
		return 1;
	}

	//loop to read the file
	while (getline(reader, line))
	{
		string label = stringPartToString(line, 0, 5);
		cout << "INSTR: " << line << endl;

		//count comments and exclude them from the mc file
		if (line[0] == ';')
		{
			//exclude comments in the mc
			minusComment++;
		}
		else
		{
			//check when var is declared
			if (stringPartToString(line, 10, 13) == "VAR")
			{
				//name of the variable to be stored in the vector
				string newVar;
				int start = 0;
				while (line[start] != ' ')
				{
					if (line[start] == ':')
					{
					}
					else
					{
						newVar += line[start];
					}
					start++;
				}

				//value of variable, to be converted to binary
				string varVal;
				int startB = 14;
				while (line[startB] != ' ')
				{
					varVal += line[startB];
					startB++;
				}
				//cout << varVal << endl;

				//conversion to binary, rtl
				int n = stoi(varVal);
				vector<char> binary;
				for (int i = 0; n > 0; i++)
				{
					binary.push_back((n % 2 + '0'));
					n = n / 2;
				}

				//initalise line to be full of 0 because it would do weird things otherwise
				for (size_t i = 0; i < 31; ++i)
				{
					output[i] = '0';
				}

				//put binary value in the mc file
				for (size_t i = 0; i < binary.size(); ++i)
				{
					output[i] = binary[i];
				}

				//add variables to vectors
				if (newVar != "")
				{
					variables.push_back(newVar);
					variablesNum.push_back(lineCounter - minusComment);
				}
			}
			//check instructions
			else if (checkInst(stringPartToString(line, 10, 13)) == 1)
			{
				//put instruction in binary in the mc file
				string bin = instToInt(stringPartToString(line, 10, 13));
				//cout << stringPartToString(line, 10, 13) << " "<<bin << endl;
				for (int i = 0; i < 3; ++i)
				{
					output[i + 10] = bin[i];
				}
				//writer <<instToInt(stringPartToString(line, 10, 13));
			}
			//just a test
			else if (checkInst(stringPartToString(line, 10, 13)) == 0)
			{
				//cout << "test" << endl;
			}

			//write to file
			for (int i = 0; i < 32; ++i)
			{
				writer << output[i];
			}
			writer << endl;
		}
		lineCounter++;
	}

	for (size_t i = 0; i < variables.size(); ++i)
	{
		cout << variables[i] << "->" << variablesNum[i] << endl;
	}

	writer.close();
	reader.close();
	return 0;
}

void test(int n)
{

	vector<int> a;
	for (int i = 0; n > 0; i++)
	{
		a.push_back(n % 2);
		n = n / 2;
	}

	for (size_t i = 0; i < a.size(); ++i)
	{
		cout << a[i];
	}

	cout << endl;
	cout << a.size() << endl;
}
