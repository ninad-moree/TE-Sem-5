#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

std::map<std::string, std::string> OPTAB = {
    {"STOP", "(IS,00)"},
    {"ADD", "(IS,01)"},
    {"SUB", "(IS,02)"},
    {"MUL", "(IS,03)"},
    {"MOVER", "(IS,04)"},
    {"MOVEM", "(IS,05)"},
    {"COMP", "(IS,06)"},
    {"BC", "(IS,07)"},
    {"DIV", "(IS,08)"},
    {"READ", "(IS,09)"},
    {"PRINT", "(IS,10)"},
};

std::map<std::string, std::string> REG = {
    {"AREG", "(1)"},
    {"BREG", "(2)"},
    {"CREG", "(3)"},
    {"DREG", "(4)"},
};

std::map<std::string, std::string> CC = {
    {"LT", "(1)"},
    {"LE", "(2)"},
    {"EQ", "(3)"},
    {"GT", "(4)"},
    {"GE", "(5)"},
    {"ANY", "(6)"},
};

class AssemblerPass2
{
private:
    std::vector<std::string> icLines;
    std::map<int, std::string> symtab;
    std::map<int, std::string> littab;
    std::vector<int> pooltab;

    std::string generateMachineCode(const std::string &opcode, const std::vector<std::string> &operands)
    {
        std::string machineCode = opcode;
        for (const auto &operand : operands)
        {
            machineCode += " " + operand;
        }
        return machineCode;
    }

public:
    AssemblerPass2(const std::string &icFileName)
    {
        std::ifstream icFile(icFileName);
        if (!icFile.is_open())
        {
            std::cerr << "Error opening IC file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(icFile, line))
        {
            icLines.push_back(line);
        }
        icFile.close();

        std::ifstream symtabFile("Pass1_SYMTAB.txt");
        if (!symtabFile.is_open())
        {
            std::cerr << "Error opening SYMTAB file." << std::endl;
            return;
        }

        int index = 0;
        while (std::getline(symtabFile, line))
        {
            std::stringstream ss(line);
            std::string symbol, value;
            ss >> symbol >> value;
            symtab[index] = value;
            ++index;
        }
        symtabFile.close();

        std::ifstream littabFile("Pass1_LITTAB.txt");
        if (!littabFile.is_open())
        {
            std::cerr << "Error opening LITTAB file." << std::endl;
            return;
        }

        index = 0;
        while (std::getline(littabFile, line))
        {
            littab[index] = line;
            ++index;
        }
        littabFile.close();

        std::ifstream pooltabFile("Pass1_POOLTAB.txt");
        if (!pooltabFile.is_open())
        {
            std::cerr << "Error opening POOLTAB file." << std::endl;
            return;
        }

        while (std::getline(pooltabFile, line))
        {
            pooltab.push_back(std::stoi(line));
        }
        pooltabFile.close();
    }

    void process()
    {
        std::ofstream outputFile("Pass2_MachineCode.txt");
        if (!outputFile.is_open())
        {
            std::cerr << "Error opening output file." << std::endl;
            return;
        }

        int poolIndex = 0;
        for (const auto &icLine : icLines)
        {
            std::stringstream ss(icLine);
            std::string token, opcode;
            ss >> token; // First token

            if (token == "(AD,01)")
            {
                outputFile << "*\t(AD,01)" << std::endl;
                continue;
            }
            else if (token == "(AD,02)")
            {
                outputFile << "*\t(AD,02)" << std::endl;
                ++poolIndex;
                continue;
            }

            opcode = token; // OPCODE

            std::vector<std::string> operands;
            while (ss >> token)
            {
                if (token[0] == '(')
                {
                    operands.push_back(token);
                }
                else if (token[0] == 'S' || token[0] == 'L')
                {
                    int index = std::stoi(token.substr(2, token.length() - 3));
                    if (token[0] == 'S')
                    {
                        operands.push_back(symtab[index - 1]);
                    }
                    else
                    {
                        operands.push_back(littab[index - 1]);
                    }
                }
                else
                {
                    operands.push_back(token);
                }
            }

            outputFile << generateMachineCode(opcode, operands) << std::endl;
        }
        outputFile.close();
    }
};

int main()
{
    // AssemblerPass2 pass2("Pass1_IC.txt");
    AssemblerPass2 pass2("Pass1_IC.txt");
    pass2.process();
    return 0;
}
