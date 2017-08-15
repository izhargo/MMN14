#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

extern int flagLabel;

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
Errorptr errorList = NULL;
Errorptr errorListLast = NULL;	
int DC = 0; 
int IC = 100;

errorType error;

void fileFirstTransition(FILE *fd){}

char *isOrderOrInstruction(char *word){
	char *op;
	op = (char*) malloc (sizeof(char)*opLength);
	if (!op){
		fprintf(stderr, "Memory allocation failed\n");
		exit(0);	
	}	
	if (word[0] == "."){ /*word could be an instruction*/
		if (op = isOpCode(word+1)!=NULL){
					
		}
	}
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
	char orderType;    
	char *word1;
    char *checker;
    char *restOfLine;
    char *label;
    checker = strchr(line,':');
	if (checker != NULL){ /* ":" appears in line*/
        word1 = strtok(line, ":");
        label = isLabel(word1, lineNum);
        restOfLine = strtok(NULL,":");
	} else{ /* ":" doesn't appear in line"*/
        restOfLine = line;
	}
	token = strtok(restOfLine," ");
	orderType = isOrderOrInstruction(token); 
	   
}

