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
    {"PRINT", "(IS,10)"}};

std::map<std::string, std::string> REG = {
    {"AREG", "(1)"},
    {"BREG", "(2)"},
    {"CREG", "(3)"},
    {"DREG", "(4)"}};

std::map<std::string, std::string> CC = {
    {"LT", "(1)"},
    {"LE", "(2)"},
    {"EQ", "(3)"},
    {"GT", "(4)"},
    {"GE", "(5)"},
    {"ANY", "(6)"}};

class AssemblerPass1
{
private:
    std::vector<std::vector<std::string>> symtab;
    std::vector<std::vector<std::string>> littab;
    std::string ic;
    std::vector<int> pooltab;
    int lc;
    std::vector<int> lctab;
    int litIndex;
    int poolIndex;

public:
    AssemblerPass1()
    {
        lc = 0;
        litIndex = 0;
        poolIndex = 0;
    }

    void UpdateSymtab(std::vector<std::string> pair)
    {
        for (auto &entry : symtab)
        {
            if (entry[0] == pair[0])
            {
                entry[1] = pair[1];
                return;
            }
        }
        symtab.push_back(pair);
    }

    int LCSymtab(std::string &word)
    {
        for (const auto &entry : symtab)
        {
            if (entry[0] == word)
            {
                return std::stoi(entry[1]);
            }
        }
        return -1;
    }

    int PosSymtab(std::string &word)
    {
        for (size_t pos = 0; pos < symtab.size(); ++pos)
        {
            if (symtab[pos][0] == word)
            {
                return static_cast<int>(pos);
            }
        }
        return -1;
    }

    void process()
    {
        std::ifstream file("TestCase.txt");
        if (!file.is_open())
        {
            std::cerr << "Error opening file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string word;
            std::vector<std::string> words;
            while (std::getline(ss, word, '\t'))
            {
                words.push_back(word);
            }

            if (!words.empty())
            {
                std::vector<std::string> pair = {words[0], std::to_string(lc)};
                UpdateSymtab(pair);
            }

            if (words[1] == "START")
            {
                lc = std::stoi(words[2]);
                lctab.push_back(lc);
                ic += "(AD,01)\t(C," + std::to_string(lc) + ")\n";
            }

            if (words[1] == "LTORG")
            {
                for (int i = poolIndex; i < litIndex; ++i)
                {
                    littab[i][1] = lc;
                    ++lc;
                    lctab.push_back(lc);

                    std::string value = littab[i][0];
                    value.erase(std::remove(value.begin(), value.end(), '='), value.end());
                    ic += "(DL,01)\t(C," + value + ")\n";
                }

                pooltab.push_back(poolIndex);
                poolIndex = litIndex;
            }
            else if (words[1] == "END")
            {
                for (int i = poolIndex; i < litIndex; ++i)
                {
                    littab[i][1] = lc;
                    ++lc;
                    lctab.push_back(lc);

                    std::string value = littab[i][0];
                    value.erase(std::remove(value.begin(), value.end(), '='), value.end());
                    ic += "(DL,01)\t(C," + value + ")\n";
                }

                pooltab.push_back(poolIndex);
                poolIndex = litIndex;

                ic += "(AD,02)\n";
            }
            else if (words[1] == "DC")
            {
                ic += "(DL,01)\t(C," + words[2] + ")\n";
                ++lc;
                lctab.push_back(lc);
            }
            else if (words[1] == "DS")
            {
                ic += "(DL,02)\t(C," + words[2] + ")\n";
                lc += std::stoi(words[2]);
                lctab.push_back(lc);
            }
            else if (words[1] == "ORIGIN")
            {
                std::string locationWord = words[2].substr(0, words[2].find('+'));
                int location = LCSymtab(locationWord);
                int addition = std::stoi(words[2].substr(words[2].find('+') + 1));
                ic += "(AD,03)\t(S," + std::to_string(PosSymtab(locationWord) + 1) + ")+" + std::to_string(addition) + "\n";
                lc = location + addition;
                lctab.push_back(lc);
            }
            else if (words[1] == "EQU")
            {
                std::string locationWord = words[2].substr(0, words[2].find('+'));
                int location = LCSymtab(locationWord);
                int addition = std::stoi(words[2].substr(words[2].find('+') + 1));
                ic += "(AD,04)\t(S," + std::to_string(PosSymtab(locationWord) + 1) + ")+" + std::to_string(addition) + "\n";
                UpdateSymtab({words[0], std::to_string(location + addition)});
            }
            else if (OPTAB.find(words[1]) != OPTAB.end())
            {
                ic += OPTAB[words[1]] + " ";

                for (size_t i = 2; i < words.size(); ++i)
                {
                    if (CC.find(words[i]) != CC.end())
                    {
                        ic += CC[words[i]] + " ";
                    }
                    else if (REG.find(words[i]) != REG.end())
                    {
                        ic += REG[words[i]] + " ";
                    }
                    else if (words[i].find('=') == std::string::npos)
                    {
                        int symbolLocation = LCSymtab(words[i]);
                        if (symbolLocation == -1)
                        {
                            UpdateSymtab({words[i], std::to_string(lc)});
                        }

                        int index = PosSymtab(words[i]);
                        ic += "(S," + std::to_string(index + 1) + ")\t";
                    }
                    else
                    {
                        littab.push_back({words[i], "-1"});
                        ++litIndex;
                        ic += "(L," + std::to_string(litIndex) + ")\t";
                    }
                }

                ++lc;
                lctab.push_back(lc);
                ic += "\n";
            }
            else
            {
                // continue;
            }
        }
        file.close();

        std::ofstream ICFile("Pass1_IC.txt");
        ICFile << ic;
        ICFile.close();

        std::ofstream SYMTABFile("Pass1_SYMTAB.txt");
        for (const auto &entry : symtab)
        {
            for (const auto &val : entry)
            {
                SYMTABFile << val << "\t";
            }
            SYMTABFile << "\n";
        }
        SYMTABFile.close();

        std::ofstream LITTABFile("Pass1_LITTAB.txt");
        for (const auto &entry : littab)
        {
            for (const auto &val : entry)
            {
                LITTABFile << val << " ";
            }
            LITTABFile << "\n";
        }
        LITTABFile.close();

        std::ofstream POOLTABFile("Pass1_POOLTAB.txt");
        for (const auto &val : pooltab)
        {
            POOLTABFile << val << "\n";
        }
        POOLTABFile.close();
    }
};

int main()
{
    AssemblerPass1 test;
    test.process();
    return 0;
}
