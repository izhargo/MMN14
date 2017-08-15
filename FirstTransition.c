#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

errorType error = NONE;

int flagLabel = 0;

opcodeStruct opcodesArray[16]={
	{0 , "mov"},
	{1 , "cmp"},
	{2 , "add"},
	{3 , "sub"},
	{4 , "not"},
	{5 , "clr"},
	{6 , "lea"},
	{7 , "inc"},
	{8 , "dec"},
	{9 , "jmp"},
	{10 , "bne"},
	{11 , "red"},
	{12 , "prn"},
	{13 , "jsr"},
	{14 , "rts"},
	{15 , "stop"},
};
instructionHandle instructions[numInstructions]= {
	{"data", dataFunc},
	{"string", stringFunc},
	{"mat", matFunc},
	{"entry", entryFunc},
	{"extern", externFunc},
};
Errorptr errorList = NULL;
Errorptr errorListLast = NULL;	
int DC = 0; 
int IC = 100;

void dataFunc(char *str){
	char token[30];
	sscanf(str, "%s" 
};
void stringFunc(char *){
};
void matFunc(char *){
};
void entryFunc(char *){
};
void externFunc(char *){
};
stringFunc(char *)
/*void fileFirstTransition(FILE *fd){}*/

int strcmpci(char *a, char *b){
    int i;
    int result = 0;
    if (strlen(a) != strlen(b)){
        return -1;
    }else
    {
    for (i=0;i<strlen(a);i++){
        if ((result =tolower(a[i])-tolower(b[i])) != 0){
            return result;
        }
    }
    }
    return result;
}

char *isLabel(char *word, int lineNumber){
	int i = 1;	
	if ((isalpha(word[0]) == 0) || (isOpCode(word)==NULL)){
		error = WRONG_INPUT_IN_LABEL;				
		addError(&errorList, &errorListLast, error,lineNumber);        
		flagLabel = 0;
		return NULL;
	} else{
		while (word[i]){
			if (isalnum(word[i]) == 0){
				error = WRONG_INPUT_IN_LABEL;				
				addError(&errorList, &errorListLast, error, 				 								lineNumber);				
				flagLabel = 0;
				return NULL;			
			} else {
				i++;
			}
		}
		flagLabel = 1;		
		return word;
	}
}

void analizeLine(char *line, int lineNum){
	char *word1;
	char *op;
    char *checker;
    char *restOfLine;
    char *label;
	char token[30];
	int i = 0;	
    checker = strchr(line,':');
	if (checker != NULL){ /* ":" appears in line*/
        word1 = strtok(line, ":");
        label = isLabel(word1, lineNum);
		if (label == NULL){
			return;		
		}else
		{
        restOfLine = strtok(NULL,":");
		}
	} else{ /* ":" doesn't appear in line"*/
        restOfLine = line;
	}
	sscanf(restOfLine, "%s",token);
	/*Decide whether word is an Order (Must be in lower case charachters) or an Instraction (Could be in lower/upper case) or an input error.*/

	if (token[0] == "."){ /*word should be an instruction*/ 
		while (i<numInstructions){/*validate word is indeed an instruction*/
			if (strcmpci(token+1,instructions[i].inst)==0){
				break;			
			}  	
			else{
				i++;			
			}
		}
		if (i==numInstructions){
			error = WRONG_INSTRUCTION_NAME;				
			addError(&errorList, &errorListLast, error,lineNumber);
			return;
		}
		else{
			(*(instructions[i].func))(restOfLine);	
		}
	}   
}

