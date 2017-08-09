#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SharedHeaderFile.h"
#include "FirstTransitionHeader.h"

errorType error;
extern int flagLabel;

void fileTransition(FILE *fd){}

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
}

