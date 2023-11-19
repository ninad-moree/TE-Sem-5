import re as regex
import itertools
import json
import os

os.system('cls' if os.name == 'nt' else 'clear')

def get_key(val: str, dict: dict) -> any:
    for key, value in dict.items():
        if val == value:
            return key

with open("Macro-Assembler/Pass-1/output/mdt.asm",'w') as file:
    pass
file.close()

inputFile = open('Macro-Assembler/Pass-1/input/program.asm', 'r')

# Output File(s)
mdtFile = open('Macro-Assembler/Pass-1/output/mdt.asm', 'a')

pattern = r'\s+'


mSign = False
mDef = False

mnt = {}
pntab = {}
kpdtab = {}

macroName = ""
kpdtabIndex = 1
kpdtabLoc = 1
mntIndex = 1
mdtLoc = 1


for line in inputFile:
    if line == '\n': continue
    line = line.strip()

    cmd = regex.split(pattern, line.rstrip())

    if len(cmd) == 1 and cmd[0] == 'MACRO':
        mSign = True
        continue

    if mSign:
        macroName = cmd.pop(0)
        pntab[macroName] = {}
        paramCnt = 0  
        pp = 0
        kp = 0

        for parameter in cmd:
            if ',' in parameter:
                parameter = parameter.replace(',','')

            if '&' in parameter and '=' not in parameter:
                paramCnt += 1
                pp += 1
                
                paramName = parameter[1::]

                pntab[macroName][paramCnt] = paramName
                
            elif '&' in parameter and '=' in parameter:
                paramCnt += 1

                if kp == 0:
                    kpdtabLoc = kpdtabIndex

                kp += 1
                
                # Get the index of the '=' sign and 
                eqIndex = parameter.index('=')
                
                paramName = parameter[1:eqIndex:]
                paramDefValue = parameter[eqIndex + 1::]

                pntab[macroName][paramCnt] = paramName
                
                kpdtab[kpdtabIndex] = {
                    'index' : kpdtabIndex, 
                    'name' : paramName, 
                    'value' : paramDefValue if paramDefValue else '---',
                }
                
                kpdtabIndex += 1
                
            else:
                pass
                
        mSign = False
        mDef = True
        mnt[mntIndex] = {
            'index' : mntIndex,
            'name' : macroName,
            'pp' : pp,
            'kp' : kp,
            'mdtp' : mdtLoc,
            'kpdtp' : kpdtabLoc if kp else '---',
        }
        mntIndex += 1
        continue
    
    if mDef:
        mdtLoc += 1
        callLine = ""
        
        for command in cmd:
            if ',' in command:
                command = command.replace(',','')
            if '&' in command:
                replParamValue = f'(P,{get_key(command[1::], pntab[macroName])})'
                callLine += replParamValue + " "
            else:
                callLine += command + " "    
                
        mdtFile.write(callLine + '\n')
        continue
    
    if len(cmd) == 1 and cmd[0] == 'MEND':
        mdtLoc += 1
        mDef = False
        mdtFile.write('MEND\n')
        continue
    
with open('Macro-Assembler/Pass-1/output/mnt.json', 'w') as json_file:
    json.dump(mnt, json_file, indent=4)
json_file.close()

with open('Macro-Assembler/Pass-1/output/pntab.json', 'w') as json_file:
    json.dump(pntab, json_file, indent=4)
json_file.close()

with open('Macro-Assembler/Pass-1/output/kpdtab.json', 'w') as json_file:
    json.dump(kpdtab, json_file, indent=4)
json_file.close()