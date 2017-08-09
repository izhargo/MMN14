#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

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

int main( int argc, char *argv[] ){
	int i;
	char *token;
	int DC = 0; 
	int IC = 100;
	
	FILE **files; /* a pointer to the files given as input from command-line*/ 
	errorType error; /* used for errorType enum*/ 
	
	/*First, check for command-line argument error. If An error is found, 			program stops immediately*/	
	printf("%d\n", argc);	
	printf("line 19\n");
	if (argc<2){
		printf("line 21\n");
		error = WRONG_COMMAND_LINE_INPUT;
		addError(&errorList, &errorListLast, error, 0);
		printErrorList(errorList);
		exit(0);
	}
	for (i=1;i<argc;i++){
		token = strtok(argv[i],".");
		token = strtok(NULL ,".");
		if (strcmp(token,"as") != 0){
			error = WRONG_COMMAND_LINE_INPUT;
			addError(&errorList, &errorListLast, error, 0);
			printErrorList(errorList);
			exit(0);
		}	
	}
	printf("Let's Start!\n"); /*just for debugging*/
	return 0;	
}

