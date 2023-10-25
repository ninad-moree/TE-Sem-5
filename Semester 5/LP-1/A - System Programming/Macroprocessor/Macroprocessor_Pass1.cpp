#include <bits/stdc++.h>
using namespace std;

void processMacroPass1(const std::string &inputFile)
{
    std::ifstream infile(inputFile);
    if (!infile)
    {
        std::cerr << "Failed to open input file: " << inputFile << std::endl;
        return;
    }

    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream pnt("pntab.txt");
    ofstream ir("intermediate.txt");

    unordered_map<std::string, int> pntab;

    string line;
    string macroName;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(infile, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            if (word == "MACRO")
            {
                flag = 1;
                getline(infile, line);
                istringstream iss(line);
                pp = kp = 0;
                mdtp = 1;
                paramNo = 1;
                pntab.clear();

                while (iss >> word)
                {
                    if (word == ",")
                        continue;

                    if (word.find('=') != std::string::npos)
                    {
                        kp++;
                        istringstream keywordParam(word);
                        string key, value;
                        getline(keywordParam, key, '=');
                        getline(keywordParam, value);

                        pntab[key] = paramNo++;
                        kpdt << key << "\t" << value << "\n";
                    }
                    else
                    {
                        pntab[word] = paramNo++;
                        pp++;
                    }
                }

                mnt << macroName << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << endl;
                kpdtp += kp;
            }
            else if (word == "MEND")
            {
                mdt << line << "\n";
                flag = kp = pp = 0;
                mdtp++;
                paramNo = 1;
                pnt << macroName << ":\t";

                for (const auto &entry : pntab)
                {
                    pnt << entry.first << "\t";
                }
                pnt << "\n";
                pntab.clear();
            }
            else if (flag == 1)
            {
                if (word.find('&') != std::string::npos)
                {
                    // word.erase(std::remove(word.begin(), word.end(), '&'), word.end());
                    mdt << "(P," << pntab[word] << ")\t";
                }
                else
                {
                    mdt << word << "\t";
                }
            }
            else
            {
                ir << line << "\n";
            }
        }
    }

    infile.close();
    mdt.close();
    mnt.close();
    ir.close();
    pnt.close();
    kpdt.close();
    std::cout << "Macro Pass 1 processing done. :)\n";
}

int main()
{
    processMacroPass1("Input.asm");
    return 0;
}