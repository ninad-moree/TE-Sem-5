#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

struct MDTEntry
{
    char lab[10];
    char opc[10];
    char oper[10];
};

int main()
{
    char label[10], opcode[10], operand[10], newlabel[10], newoperand[10];
    char macroname[10];
    int i, lines;
    FILE *f1, *f2, *f3;
    f1 = fopen("Input.asm", "r");
    f2 = fopen("output.txt", "w");
    f3 = fopen("MDT.txt", "w");

    fscanf(f1, "%s %s %s", label, opcode, operand);

    while (strcmp(opcode, "END") != 0)
    {
        if (strcmp(opcode, "MACRO") == 0)
        {
            strcpy(macroname, label);
            fscanf(f1, "%s%s%s", label, opcode, operand);
            lines = 0;
            MDTEntry d[10];

            while (strcmp(opcode, "MEND") != 0)
            {
                fprintf(f3, "%s\t%s\t%s\n", label, opcode, operand);
                strcpy(d[lines].lab, label);
                strcpy(d[lines].opc, opcode);
                strcpy(d[lines].oper, operand);
                fscanf(f1, "%s %s %s", label, opcode, operand);
                lines++;
            }

            for (i = 0; i < lines; i++)
            {
                fprintf(f2, "%s\t%s\t%s\n", d[i].lab, d[i].opc, d[i].oper);
            }
        }
        else if (strcmp(opcode, macroname) == 0)
        {
            cout << "Macro Found" << endl;
        }
        else
        {
            fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);
        }
        fscanf(f1, "%s%s%s", label, opcode, operand);
    }
    fprintf(f2, "%s\t%s\t%s\n", label, opcode, operand);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    cout << "Finished" << endl;
    getch();
    return 0;
}
