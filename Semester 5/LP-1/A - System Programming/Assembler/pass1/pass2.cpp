#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream symbolIn("symbol_table.txt", ios::in);
    ifstream literalIn("literal_table.txt", ios::in);
    ifstream intemediateIn("intermediate_code.txt", ios::in);
    fstream machineOut("machineCode.txt", ios::out);
    
    string line, word;
    vector<pair<string, int>> symtab;
    vector<pair<string, int>> littab;

    while (!symbolIn.eof())
    {
        string line;
        getline(symbolIn, line);
        string symbol = "", address = "";
        int i = 0;
        for (; i < line.length(); i++)
        {
            if (line[i] == ',')
                break;
            symbol += line[i];
        }
        i++;
        for (; i < line.length(); i++)
        {
            address += line[i];
        }
        symtab.push_back({symbol, stoi(address)});
    }
    symbolIn.close();

    while (!literalIn.eof())
    {
        string line;
        getline(literalIn, line);
        string symbol = "", address = "";
        int i = 0;
        for (; i < line.length(); i++)
        {
            if (line[i] == ',')
                break;
            symbol += line[i];
        }
        i++;
        for (; i < line.length(); i++)
        {
            address += line[i];
        }
        littab.push_back({symbol, stoi(address)});
    }
    literalIn.close();

    while (!intemediateIn.eof())
    {
        string line;
        getline(intemediateIn, line);
        string cls = "", mnemonic = "", op1 = "", op2 = "";
        int index = line.find('(');
        int i = 1;
        for (; i < line.length(); i++)
        {
            if (line[i] == ',')
                break;
            cls += line[i];
        }
        i++;
        for (; i < line.length(); i++)
        {
            if (line[i] == ')')
                break;
            mnemonic += line[i];
        }
        i += 3;

        if (cls == "AD")
        {
            machineOut << "+" << endl;
        }
        else if (cls == "IS")
        {
            machineOut << "+" << "\t";
            machineOut << mnemonic << "\t";

            if (mnemonic == "0")
            {
                machineOut << "0\t000" << endl;
                continue;
            }
            machineOut << line[i] << "\t";

            i += 4;
            if (line[i] == 'S')
            {
                int ind = line[i + 2] - '0';
                machineOut << setw(3) << setfill('0') << symtab[ind - 1].second << endl;
            }
            else
            {
                cout<<op2<<endl;
                machineOut << setw(3) << setfill('0') << line[line.size()-3] << endl;
            }
        }
        else if (cls == "DL")
        {
            if (mnemonic == "2")
            {
                machineOut << "+" << endl;
            }
            else
            {
                machineOut << "+" << "\t";
                for (int j = line.length() - 2; j >= 0; j--)
                {
                    if (line[j] == ',')
                        break;
                    op2 += line[j];
                }
                reverse(op2.begin(), op2.end());
                if(op2.back() == ')') op2.pop_back();
                machineOut << 0 << "\t" << 00 << "\t" << setw(3) << setfill('0') << op2 << endl;
            }
        }
    }

    machineOut.close();
    intemediateIn.close();
    cout << "\nProgram Executed\n";

    return 0;
}