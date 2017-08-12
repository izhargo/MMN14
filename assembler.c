#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"

void validateFileName(char *token);
FILE *handleFileName(char *filename);
int main(int argc, char *argv[]){
	FILE *fd;	
	char *suffix;
	char *fileName;
	int argumentIndex = 1;
	/*First, check for command-line argument error. If An error is found, 			program stops immediately*/	
	if (argc<2){
		printf("No File Reference in Command-Line Input\n");
		exit(0);
	}
	printf("line 19\n");
	while (argumentIndex<argc){
		printf("%d\n", argumentIndex);		
		fileName = (char*) malloc(sizeof(char)*maxFileName);
		if (!fileName){
			fprintf(stderr, "Memory allocation for file name failed\n");
			exit(0);
		}
		strcpy(fileName,argv[argumentIndex]);	
		suffix = strtok(argv[argumentIndex],".");
		suffix = strtok(NULL,".");
		validateFileName(suffix);		
		fd = handleFileName(fileName);
		/*fileFirstTransition(fd);*/
		printf("Let's Start!\n"); /*just for debugging*/
		argumentIndex++;
	}
	
	return 0;	
}

void validateFileName(char *token){
	if ((token == NULL) || (strcmp(token,inputFileSuffix)!=0)){
		fprintf(stderr, "Wrong File Type as Argument\n");
		exit(0);
	}
}

FILE *handleFileName(char *filename){
	FILE *f;	
	if (!(f = fopen(filename,"r")))
	{
		fprintf(stderr,"cannot open file\n");
		exit(0);
	} else {
		return f;
	}
}
