#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

std::map<std::string, std::string> OPTAB = {
    {"STOP", "00"},
    {"ADD", "01"},
    {"SUB", "02"},
    {"MUL", "03"},
    {"MOVER", "04"},
    {"MOVEM", "05"},
    {"COMP", "06"},
    {"BC", "07"},
    {"DIV", "08"},
    {"READ", "09"},
    {"PRINT", "10"},

    {"AREG", "01"},
    {"BREG", "02"},
    {"CREG", "03"},
    {"DREG", "04"},

    {"LT", "1"},
    {"LE", "2"},
    {"EQ", "3"},
    {"GT", "4"},
    {"GE", "5"},
    {"ANY", "6"},
};

std::map<std::string, std::string> CC = {
    {"LT", "(1)"},
    {"LE", "(2)"},
    {"EQ", "(3)"},
    {"GT", "(4)"},
    {"GE", "(5)"},
    {"ANY", "(6)"},
};

class AssemblerPass2 {
private:
    std::vector<std::string> icLines;

    std::string generateMachineCode(const std::string &opcode, const std::vector<std::string> &operands) {
        std::string machineCode = opcode;
        for (const auto &operand : operands) {
            machineCode += " " + operand;
        }
        return machineCode;
    }

public:
    AssemblerPass2(const std::string &icFileName) {
        std::ifstream icFile(icFileName);
        if (!icFile.is_open()) {
            std::cerr << "Error opening IC file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(icFile, line)) {
            icLines.push_back(line);
        }
        icFile.close();
    }

    void process() {
        std::ofstream outputFile("output.txt");
        if (!outputFile.is_open()) {
            std::cerr << "Error opening output file." << std::endl;
            return;
        }

        for (const auto &icLine : icLines) {
            std::stringstream ss(icLine);
            std::string token, opcode;
            ss >> opcode; // First token is opcode

            std::vector<std::string> operands;
            while (ss >> token) {
                if (token[0] == '(') {
                    token.erase(std::remove(token.begin(), token.end(), '('), token.end());
                    token.erase(std::remove(token.begin(), token.end(), ')'), token.end());
                    operands.push_back(token);
                } else {
                    operands.push_back(token);
                }
            }

            std::string machineCode = generateMachineCode(OPTAB[opcode], operands);
            outputFile << machineCode << std::endl;
        }
        outputFile.close();
    }
};

int main() {
    AssemblerPass2 pass2("intermediate_code.txt");
    pass2.process();
    return 0;
}