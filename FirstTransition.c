#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

binWord bin;

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

int isInteger(char *str){
	int i;
	if (strlen(str)==0)	return 0;
	for (i=0;i<strlen(str);i++){ 		
		if (isdigit(str[i]) == 0){
			return 0;
		}
	}
	return 1;
}	

int isParam(char *str){
	char num[MAXWORD];
	int result = 0;
	sscanf(str,"%s",num);	
	/*validating input as integers only*/
	if ((num[0] == '+') || (num[0] == '-')){
		memmove(num, num+1, strlen(num));
	}
	if (isInteger(num) == 1){
		result = 1;			
	} 
	return result;
}

int strcmpci(char *a, char *b){
    int i;
    int result = 0;
    if (strlen(a) != strlen(b)){
        return -1;
    }
	else{
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

int isBlank(char *str){
	int i;	
	int result = 1;
	for (i=0;i<strlen(str);i++){
		if (!isspace(str[i])){
			result = 0;
			break;
		}	
	}
	return result;
}

void matFunc(char *str,int lineNumber){		
	char *token, *tokenInner;
	char size1[MAXWORD];
	char size2[MAXWORD];
	int i,row,col,data,checker,matSize; 
	token = strtok (str," ");
    token = strtok (NULL," "); 
	checker = sscanf(token,"[%99[^]]]" "[%99[^]]]",size1,size2);
	if (checker<=1){
		addError(WRONG_MATRIX_SIZE,lineNumber); 
		return; 	
	}
	else if ((isInteger(size1) == 0) || (isInteger(size2) == 0)){
		addError(WRONG_MATRIX_SIZE,lineNumber); 
		return;
	}
	else{
		row = atoi(size1);
		col = atoi(size2);
		matSize = col*row;
		if (((token = strtok (NULL,"\n")) == NULL) || (isBlank(token))){
			for (i=0;i<matSize;i++){
				addToDataArray(0);
			}
			return;		
		}	
		else{
			tokenInner = strtok(token, ",");
			for (i=0;i<matSize;i++){
				if ((tokenInner != NULL) && (isParam(tokenInner) == 1)){
					data = atoi(tokenInner);
					addToDataArray(data);
				}
				else{
					addError(WRONG_MATRIX_PARAMETER_VALUE,lineNumber);        
					return;
				}
				tokenInner = strtok(NULL, ",");
			}
			if (tokenInner){
				addError(WRONG_MATRIX_PARAMETER_VALUE,lineNumber);        
				return;			
			}
		}
	}
}
		
void stringFunc(char *str,int lineNumber){		
	char *token;
	char param[MAXWORD];
	int i,checker,data;   
	token = strtok (str," ");
	token = strtok(NULL, "\n");
	if (token == NULL){
		addError(WRONG_PARAMETER_VALUE,lineNumber);        
		return;	
	}
	else{
		checker = sscanf(token," \"%[^\"]",param);
		if (checker<=0){		
			addError(WRONG_PARAMETER_VALUE,lineNumber);        
			return;
		}
		else{
			printf("%d\n",param[strlen(param)-1]);
			for (i=0;i<strlen(param);i++){
				data = param[i];
				addToDataArray(data);			
			}		
		}   
	}
}		
	
void dataFunc(char *str,int lineNumber){		
	char *token;
	int data;
	token = strtok (str," ");
    while((token = strtok (NULL,",")) != NULL){			
		if (isParam(token) == 1){
			data = atoi(token);
			addToDataArray(data);
		}
		else{
			addError(WRONG_PARAMETER_VALUE,lineNumber);        
			return;
		}
	}	
}
/*function makes a special label validation, different from the one in isLabel, due to requirements*/
void externFunc(char *str,int lineNumber){
	char *token, *exLabel;
	int i = 0;	
	token = strtok(str," ");
	token = strtok(NULL," ");
	exLabel = (char *) malloc(sizeof(char));
	if (!exLabel){
		fprintf(stderr, "Memory Allocation Failure\n");	
		exit(0);	
	}
	if (token == NULL){
		addError(NO_LABEL_FOR_EXTERN_INSTRUCTION,lineNumber);
		return;
	}
	else{
		sscanf(token, "%s", exLabel);
		if ((isalpha(exLabel[0]) == 0) || (isOpCode(exLabel) != NULL)|| 
		(isRegister(exLabel) != NULL) || (isInstruction(exLabel) != NULL) ||
		(strlen(exLabel) > MAXLABEL)){
			addError(ERROR_IN_LABEL_FOR_EXTERN_INSTRUCTION,lineNumber);
			return;
		}
		else{
			while (exLabel[i]){
				if (isalnum(exLabel[i]) == 0){
					addError(ERROR_IN_LABEL_FOR_EXTERN_INSTRUCTION,lineNumber);
					return;		
				} 
				else{
					i++;
				}
			}
			if ((token = strtok(NULL," ")) != NULL){
				addError(ERROR_IN_LABEL_FOR_EXTERN_INSTRUCTION,lineNumber);
				return;
			}
			addToSymbolList(&SymbolTable, &SymbolTableLast, exLabel, 0, 0, 1);
		}
	}	
}

char *isLabel(char *word, int lineNumber){
	int i = 1;	
	if ((isalpha(word[0]) == 0) || (isOpCode(word) != NULL)|| 
		(isRegister(word) != NULL) || (isInstruction(word) != NULL)){
		addError(WRONG_INPUT_IN_LABEL,lineNumber);  		
		flagLabel = 0;
		return NULL;       	
	}
	else if (findSymbolByLabel(word) != NULL){ 
		addError(SYMBOL_ALREADY_IN_THE_TABLE,lineNumber);		     
		flagLabel = 0;
		return NULL;
	}
	else if (strlen(word) > MAXLABEL){
		addError(LABEL_INPUT_TOO_LONG,lineNumber);		    
		flagLabel = 0;
		return NULL;
	}	 
	else{
		while (word[i]){
			if (isalnum(word[i]) == 0){
				addError(WRONG_INPUT_IN_LABEL,lineNumber);			
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
	char *label;	
	char *word1;
    char *checker;
    char *restOfLine;
	char token[MAXWORD];
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
		flagLabel = 0;
	}
	sscanf(restOfLine, "%s",token);
	/*Decide whether word is an Order (Must be in lower case charachters) or an Instraction (Could be in lower/upper case) or an input error.*/
	if (token[0] == '.'){ /*word should be an instruction*/ 					
		if (isInstruction(token+1) == NULL){
			addError(WRONG_INSTRUCTION_NAME,lineNum);						
			return;
		}
		else if (strcmp(instructions[0],isInstruction(token+1)) == 0){		
			if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0);				
			dataFunc(restOfLine,lineNum);
		}
		else if (strcmp(instructions[1],isInstruction(token+1)) == 0){		
			if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0);				
			stringFunc(restOfLine,lineNum);
		}
		else if (strcmp(instructions[2],isInstruction(token+1)) == 0){		
			if (flagLabel) {
			addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0);
			}
			else{
				addError(NO_LABEL_FOR_MATRIX,lineNum);			
				return;
			}									
			matFunc(restOfLine,lineNum);
		}
		else if (strcmp(instructions[3],isInstruction(token+1)) == 0){		
			return;
		}
		else if (strcmp(instructions[4],isInstruction(token+1)) == 0){		
			externFunc(restOfLine,lineNum);
		}			
	}
}


int main(){
	int i;
	char line1[80] = {"MAIN:    .data 2,1   "};
	char line2[80] = {"m34:    .mat [2][2]   "};

	
	char line3[80] = {"m35:    .mat [2][2]"};	
	/*
	char line4[80] = {"MAIN    .mat [2][2]"}; 

	   
	*/
	analizeLine(line1, 1);	
	analizeLine(line2, 2);
	analizeLine(line3, 3);
	for (i=0;i<DC;i++){
		printf("%d , %s\n",dataArray[i].mw.word,convertToWeirdFour(dataArray[i].mw.word));
	}
	printSymbolList(SymbolTable);
	printErrorList(errorList);	
	
	return 0;
}

