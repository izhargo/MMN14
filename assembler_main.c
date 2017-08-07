#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

int main( int argc, char *argv[] ){
	extern Errorptr errorList;
	extern Errorptr errorListLast;	
	extern int DC; 
	extern int IC;
	int i;
	char *token;
	FILE **files; /* a pointer to the files given as input from command-line*/ 
	errorType error; /* used for errorType enum*/ 
	DC = 0;
	IC = 100;
	errorList = NULL;
	errorListLast = NULL;
	/*First, check for command-line argument error. If An error is found, 			program stops immediately*/	
	printf("line 23\n");
	if (argc==1){
		printf("line 25\n");
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

