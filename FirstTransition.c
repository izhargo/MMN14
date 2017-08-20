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

int isInteger(char *str);
int isParam(char *str);
int strcmpci(char *a, char *b);
char *isRegister(char *str);
char *isInstruction(char *str);
void addError(errorType e, int lineNumber);
void numToBin(int num);
void numToNeg(int num);
void addToDataArray(int num);
int isBlank(char *str);
void matFunc(char *str,int lineNumber);		
void stringFunc(char *str,int lineNumber);		
void dataFunc(char *str,int lineNumber);		
void externFunc(char *str,int lineNumber);
char *isLabel(char *word, int lineNumber);
int calcOneOperand0123(char *str, int lineNum);	
int calcOneOperand123(char *str, int lineNum);
int calcOneOperand12(char *str, int lineNum);
int oneOperandFunc(char *line,int opCode, int lineNum);
int twoOperandFunc(char *line ,int opCode, int lineNum);
void noOperand (char *line, int lineNum);
void analizeLine(char *line, int lineNum);
/*A function to move over file and analize each line in the file*/
void moveOverFileOne(FILE* currentFile);


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
	free(token);
	free(tokenInner);
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
			for (i=0;i<strlen(param);i++){
				data = param[i];
				addToDataArray(data);			
			}		
		}   
	}
	free(token);
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
	free(token);	
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
			addToSymbolList(&SymbolTable, &SymbolTableLast, exLabel, 0, 0, 1, 0);
		}
	}
	free(token);
	free(exLabel);	
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

int calcOneOperand0123(char *str, int lineNum){	
	char *token;
	char reg1[MAXWORD], reg2[MAXWORD];	
	int result = 0;
	if (str[0]=='#'){/*immediate address (0)*/
		if (isParam(str+1)){
			result++;
		}
		else{
			addError(WRONG_OPERAND_INPUT,lineNum);			
			return 0;
		}
	}
	else if (isParam(str)){
		addError(WRONG_OPERAND_INPUT,lineNum);			
		return 0;	
	}
	else if (isRegister(str)){ /*register address (3)*/
		result++;
	}
	else if (strchr(str,'[') != NULL) { /*matrix address (2)*/			
		token = strtok(str,"[");
		token = strtok(NULL,"]");
		strcpy(reg1,token);
		token = strtok(NULL,"]");
		strcpy(reg2,token);
		if ((isRegister(reg1)) && (isRegister(reg2+1))){
			result+=2;
		}
		else{
			addError(WRONG_OPERAND_INPUT,lineNum);			
			return 0;		
		}	
	}
	else{ /*direct address, cannot validate in first transition*/
		result++;
	}

	return result;
}

int calcOneOperand123(char *str, int lineNum){	
	char *token;	
	char reg1[MAXWORD], reg2[MAXWORD];	
	int result = 0;	
	if (str[0]=='#'){/*immediate address (0) not allowed*/
		addError(WRONG_OPERAND_INPUT,lineNum);			
		return 0;	
	}
	else if (isParam(str)){
		addError(WRONG_OPERAND_INPUT,lineNum);			
		return 0;	
	}
	else if (isRegister(str)){ /*register address (3)*/
		result++;
	}
	else if (strchr(str,'[') != NULL) { /*matrix address (2)*/			
		token = strtok(str,"[");
		token = strtok(NULL,"]");
		strcpy(reg1,token);
		token = strtok(NULL,"]");
		strcpy(reg2,token);
		if ((isRegister(reg1)) && (isRegister(reg2+1))){
			result+=2;
		}
		else{
			addError(WRONG_OPERAND_INPUT,lineNum);			
			return 0;		
		}	
	}
	else{/*direct address, cannot validate in first transition*/
		result++;
	}
	return result;
}

int calcOneOperand12(char *str, int lineNum){
	char *token;	
	char reg1[MAXWORD], reg2[MAXWORD];	
	int result = 0;	
	if (str[0]=='#'){/*immediate address (0), not allowed*/
		addError(WRONG_OPERAND_INPUT,lineNum);			
		return 0;	
	}
	else if (isParam(str)){
		addError(WRONG_OPERAND_INPUT,lineNum);			
		return 0;	
	}
	else if (isRegister(str)){ /*register address (3), not allowed*/
		addError(WRONG_OPERAND_INPUT,lineNum);			
		return 0;
	}
	else if (strchr(str,'[') != NULL) { /*matrix address (2)*/			
		token = strtok(str,"[");
		token = strtok(NULL,"]");
		strcpy(reg1,token);
		token = strtok(NULL,"]");
		strcpy(reg2,token);
		if ((isRegister(reg1)) && (isRegister(reg2+1))){
			result+=2;
		}
		else{
			addError(WRONG_OPERAND_INPUT,lineNum);			
			return 0;		
		}	
	}
	else{/*direct address, cannot validate in first transition*/
		result++;
	}
	return result;
}

int oneOperandFunc(char *line,int opCode, int lineNum){
	char *token;	
	char op1[MAXWORD];
	int result = 0;
	token = strtok(line," ");
	if ((token = strtok(NULL,",")) != NULL){
		sscanf(token, "%s", op1);
	}
	else{
		addError(TOO_FEW_OPERANDS,lineNum);			
		return 0;
	}
	if ((token = strtok(NULL," ")) != NULL){
		addError(TOO_MANY_OPERANDS,lineNum);			
		return 0;
	}
	else{
		if (opCode == 12){
			result = calcOneOperand0123(op1,lineNum);
		}
		else{
			result = calcOneOperand123(op1,lineNum);
		}
	}
	free(token);
	return result;
}

int twoOperandFunc(char *line ,int opCode, int lineNum){
	char *token;		
	char op1[MAXWORD], op2[MAXWORD];
	int opVal1,opVal2;	
	int result = 0; 
	token = strtok(line," ");
	if ((token = strtok(NULL,",")) != NULL){
		sscanf(token, "%s", op1);
	}
	else{
		addError(TOO_FEW_OPERANDS,lineNum);			
		return 0;		
	}		
	if ((token = strtok(NULL,",")) != NULL){
		sscanf(token, "%s", op2); 
	}
	else{
		addError(TOO_FEW_OPERANDS,lineNum);			
		return 0;	
	}
	if ((token = strtok (NULL,",")) == NULL){
		if (opCode == 1){
			opVal1 = calcOneOperand0123(op1,lineNum);
			opVal2 = calcOneOperand0123(op2,lineNum);		
		}
		else if ((opCode == 0) || (opCode == 2) || (opCode == 3)){			
			opVal1 = calcOneOperand0123(op1,lineNum);
			opVal2 = calcOneOperand123(op2,lineNum);
		}
		else if (opCode == 6){
			opVal1 = calcOneOperand12(op1,lineNum);
			opVal2 = calcOneOperand123(op2,lineNum);		
		}
		result = opVal1 + opVal2;
	}
	else{
		addError(TOO_MANY_OPERANDS,lineNum);			
		return 0;
	}	
	/* a special check for two registers*/
	if ((isRegister(op1)) && (isRegister(op2)) && (opCode !=6)){
		result += 1;	
	}
	free(token);
	return result;
}

void noOperand (char *line, int lineNum){
	char *token;	
	token = strtok(line," ");
	if ((token = strtok(NULL," ")) == NULL){
		return;	
	}
    else{ /*we have a kind of an operand - and we shouldn't*/
		addError(TOO_MANY_OPERANDS,lineNum);			
		return;
	}
	free(token);
	return;
}

void analizeLine(char *line, int lineNum){
	char *label,*word1,*checker,*restOfLine;	
	char token[MAXWORD];
	int opCode, result;
	if ((isBlank(line)) || (line[0] == ';' )){
		return;	
	}
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
			if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0, 0);				

			dataFunc(restOfLine,lineNum);
		}
		else if (strcmp(instructions[1],isInstruction(token+1)) == 0){		
			if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0, 0);				
			stringFunc(restOfLine,lineNum);
		}
		else if (strcmp(instructions[2],isInstruction(token+1)) == 0){		
			if (flagLabel) {
			addToSymbolList(&SymbolTable, &SymbolTableLast, label, DC, 0, 0, 1);
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
	else if (isOpCode(token) != NULL){
		if (flagLabel) addToSymbolList(&SymbolTable, &SymbolTableLast, label, IC, 1, 0, 0);	
		opCode = getNumOfOpCode(token);
		if (((opCode>=0) && (opCode<=3)) || (opCode==6)) {
			result = twoOperandFunc(restOfLine,opCode,lineNum);
			IC+=result+1;
		}
		else if (((opCode>=7) && (opCode<=13)) || (opCode==4) || (opCode==5)){ 
			result = oneOperandFunc(restOfLine,opCode,lineNum);
			IC+=result+1;
		}
		else{
			noOperand(restOfLine,lineNum);			
			IC++;
		}
	}
	else{
		addError(WRONG_COMMAND,lineNum);						
		return;
	}
}

/*A function to move over file and analize each line in the file*/
void moveOverFileOne(FILE* currentFile)
{
	int lineNum = 1;
	char* startLine;
	int fileChar; 
	int ind = 0;

	startLine = (char*)(malloc(sizeof(char)*MAXLINE));
	ind = 0;
	while((fileChar = fgetc(currentFile)))
	{
			
		if(fileChar == '\n')
		{
			startLine[ind] = '\0';
			analizeLine(startLine , lineNum);
			ind = 0;
			lineNum++;
			continue;
		}
		if (fileChar == EOF)
		{
			if(ind > 0)
			{
				startLine[ind] = '\0';
				analizeLine(startLine , lineNum);
				ind = 0;
				lineNum++;
			}
			break;
		}
		else
            		startLine[ind++] = (char)fileChar;
	}
	free(startLine);
}

