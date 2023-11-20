import json
import re as regex

symboltable=json.load(open('D:\Coding\PICT College\TE Lab Work\Semester 5\Python\Assembler\Pass-1\output\symbols.json','r'))
literaltable=json.load(open('D:\Coding\PICT College\TE Lab Work\Semester 5\Python\Assembler\Pass-1\output\literals.json','r'))
icfile=open('D:\Coding\PICT College\TE Lab Work\Semester 5\Python\Assembler\Pass-1\output\ic.txt','r')
opfile2=open('Pass2.txt','a')
opcode=op1code=op2code=""
lc=""
cnt=-1
pattern=r'\s+'


for line in icfile:
    opcode=op1code=op2code=""
    if line=='\n':
        continue
    
    line=line.strip()
    print(line)
    ipwords=regex.split(pattern,line.rstrip())
    print(ipwords)
    


    if len(ipwords) == 4:
        lc=ipwords[0]
        opcode=ipwords[1].split(',')[1].replace(')',"")
        op1code=ipwords[2].replace('(',"")
        op1code=op1code.replace(')',"")
        cnt=ipwords[3].split(',')[1].replace(')',"")
        
        
        if 'S' in ipwords[3]:
            for symbol,[stcnt,symb,value] in symboltable.items():
                if stcnt==int(cnt):
                    op2code=value 
        elif 'L' in ipwords[3]:
            for literal,[ltcnt,literal,value] in literaltable.items():
                if ltcnt==int(cnt):
                    op2code=value
                    
    elif len(ipwords)==3:
        print(ipwords)
        lc=ipwords[0]
        opcode=ipwords[1].split(',')[1].replace(')',"")
        cnt=ipwords[2].split(',')[1].replace(')',"")
        
        if 'C' in ipwords[2]:
            op1code=ipwords[2].split(',')[1].replace(')',"")
        elif 'S' in ipwords[2]:
            for symbol,[stcnt,symb,value] in symboltable.items():
                if stcnt==int(cnt):
                    op1code=value
        op2code=""
        
    elif len(ipwords)==2:
        if 'IS' in ipwords[1]:
            lc=ipwords[0]
            opcode=opcode=ipwords[1].split(',')[1].replace(')',"")
            op1code=""
            op2code=""
        else:
            continue
        
    else:
        continue
        
    opfile2.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")