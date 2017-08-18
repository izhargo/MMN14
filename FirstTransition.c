#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

binWord bin;

char *label;

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

char *instructions[numInstructions] = {"data", "string", "mat", "entry", "extern"};

char *registerNames[numRegisters] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

pSymbol SymbolTable = NULL;
pSymbol SymbolTableLast = NULL;
Errorptr errorList = NULL;
Errorptr errorListLast = NULL;
memoryWord dataArray[SIZEARRAY];	
int DC = 0; 
int IC = 100;

	
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


char *isRegister(char *str){
	int i;	
	for (i=0;i<numRegisters;i++){
		if (strcmp(str,registerNames[i]) == 0){ /*str is a register name*/
			return registerNames[i];		
		}
	}
	return NULL;
}

char *isInstruction(char *str){
	int i;	
	for (i=0;i<numInstructions;i++){
		if (strcmpci(str,instructions[i]) == 0){ /*str is an instructions name*/
			return instructions[i];		
		}
	}
	return NULL;
}

void addError(errorType e, int lineNumber){
	error = e;	
	addToErrorList(&errorList, &errorListLast,e,lineNumber);
}

void numToBin(int num){
	int i;
	int mask = 0x01;
	bin.a = 0;
	for (i=0;i<WORDLENGTH && num != 0;i++){
        bin.a = (num % 2) ? (bin.a | mask) : bin.a;
        num /= 2;
        mask <<= 1;
    }
	dataArray[DC].mw.word = bin.a;	
}

void numToNeg(int num){
	int m=1;	
	numToBin(num);
	bin.a = (~bin.a);
	
	/* Flip all the set bits until we find a 0 */
	while(bin.a & m){
		bin.a = bin.a^m;
		m <<= 1;
	}
	/* flip the rightmost 0 bit */
	bin.a = bin.a^m;
	dataArray[DC].mw.word = bin.a;
}

void addToDataArray(int num){
	dataArray[DC].fullReg = 0;
	if (num>0){
		numToBin(num);
	}
	else if (num<0){
		numToNeg(num);
	}
	DC++;
}

void dataFunc(char *str,int lineNumber){		
	char *token;
	char num[30];
	int i;    
	int data;
	token = strtok (str," ");
    while((token = strtok (NULL,",")) != NULL){		
		sscanf(token,"%s",num);
		/*validating input as integers only*/
		if ((num[0] == '+') || (num[0] == '-') || (isdigit(num[0]) !=0 )){
			for (i=1;i<strlen(num);i++){  			
				if (isdigit(num[i]) == 0){
					addError(WRONG_INPUT_VALUE,lineNumber);        
					return;
				}
			}
		}
		else{
			addError(WRONG_INPUT_VALUE,lineNumber);        
			return;
		}
		/*input is validated*/
		data = atoi(num);
		addToDataArray(data);
	}
}		
/*
void stringFunc(char *){
};
void matFunc(char *){
};
void entryFunc(char *){
};
void externFunc(char *){
};
stringFunc(char *)
void fileFirstTransition(FILE *fd);
*/ 

char *isLabel(char *word, int lineNumber){
	int i = 1;	
	if ((isalpha(word[0]) == 0) || (isOpCode(word) != NULL)|| 
		(isRegister(word) != NULL) || (isInstruction(word) != NULL)){
		error = WRONG_INPUT_IN_LABEL;
		addToErrorList(&errorList, &errorListLast, error,lineNumber);
		flagLabel = 0;
		return NULL;       	
	}
	else if (findSymbolByLabel(word) != NULL){ 
		error = SYMBOL_ALREADY_IN_THE_TABLE;				
		addToErrorList(&errorList, &errorListLast, error,lineNumber);        
		flagLabel = 0;
		return NULL;
	}
	else if (strlen(word) > MAXLABEL){
		error = LABEL_INPUT_TOO_LONG;				
		addToErrorList(&errorList, &errorListLast, error,lineNumber);        
		flagLabel = 0;
		return NULL;
	}	 
	else{
		while (word[i]){
			if (isalnum(word[i]) == 0){
				error = WRONG_INPUT_IN_LABEL;				
				addToErrorList(&errorList, &errorListLast, error, 				 								lineNumber);				
				flagLabel = 0;
				return NULL;			
			} 
			else{
				i++;
			}
		}
		flagLabel = 1;		
		return word;
	}
}

void analizeLine(char *line, int lineNum){
	char *word1;
    char *checker;
    char *restOfLine;
	char token[30];
    checker = strchr(line,':');
	if (checker != NULL){ /* ":" appears in line*/           
		word1 = strtok(line, ":");
        label = isLabel(word1, lineNum);  
		if (label == NULL){
			return;		
		}
		restOfLine = strtok(NULL,":");
	}
	else{ /* ":" doesn't appear in line"*/        
		restOfLine = line;
	}
	sscanf(restOfLine, "%s",token);
	/*Decide whether word is an Order (Must be in lower case charachters) or an Instraction (Could be in lower/upper case) or an input error.*/

	if (token[0] == '.'){ /*word should be an instruction*/ 					
		if (isInstruction(token+1) == NULL){
			error = WRONG_INSTRUCTION_NAME;				
			addToErrorList(&errorList, &errorListLast, error,lineNum);
			return;
		}
		else if (strcmp(instructions[0],isInstruction(token+1)) == 0){		
				if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0);				
				dataFunc(restOfLine,lineNum);
		}
		else if (strcmp(instructions[1],isInstruction(token+1)) == 0){		
				if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0);				
				dataFunc(restOfLine,lineNum);
	}
}

/*
int main(){
	int i;
	char line1[80] = {"MAIN:    .data   +8,   105 , -8 , -89    "};
	char line2[80] = {"MAN:    .data +7,   -5a76   , *178,1+9"};
	
	char line3[80] = {"MAIN:    .data +7,   -57   , 17,9"};	
	char line4[80] = {"MAIN    .mat [2][2]"}; 
	analizeLine(line3, 3);   

	analizeLine(line1, 1);	
	analizeLine(line2, 2);
	for (i=0;i<DC;i++){
		printf("%d , %s\n",dataArray[i].mw.word,convertToWeirdFour(dataArray[i].mw.word));
	}
	printSymbolList(SymbolTable);
	printErrorList(errorList);	
	return 0;
}
*/
