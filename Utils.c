#include "SharedHeaderFile.h"



/*A method to convert a short number to string of letters in the wierd four counting system*/



char* convertToWeirdFour(short wordShort)

{

	int i , wordLoc = 0;

	short num;

	char* weirdFourWord;

	weirdFourWord = (char*)malloc(sizeof(char)*6);

	if(!weirdFourWord)

		return NULL;

	for(i = 0; i < WORDLENGTH; i += 2)

	{

		/*Calculate the number from two adjacent bit*/



		num = (wordShort & (1  << i)) + 2 * (wordShort & (1  << (i+1)));

		/*Fit the right number to the number according to the wierdFourCountNums enum*/



		switch(num)

		{

			case A : weirdFourWord[wordLoc] = 'a'; break;

			case B : weirdFourWord[wordLoc] = 'b'; break;

			case C : weirdFourWord[wordLoc] = 'c'; break;

			case D : weirdFourWord[wordLoc] = 'd'; break;

		}

		wordLoc++;

	}

	weirdFourWord[wordLoc] = 0;

	return weirdFourWord;

}



void addToErrorList(Errorptr *head, Errorptr *last, errorType err, int numLine){

	Errorptr temp,p;

	temp = (Errorptr) malloc(sizeof(error_node));/* allocate memory for a new 														Error in list*/

	if (!temp){

		fprintf(stderr, "Memory allocation failed\n");

		exit(0);

	}

	/*new item is put in a temporary node before entering the list*/

	temp->title = err;

	temp->lineNumber = numLine;

	temp->next = NULL;

	if (!(*head)){	/*insert to an empty list*/

		*last = temp;

		*head = temp;

	}

	else {	/*insert to a non-empty list */

		p = *last;

		p->next = temp;

		*last = p->next;

	}		

}

/*gets a string version of enum value*/

const char *getError(errorType e){

	switch (e){

		case NONE: return "NONE";

		case WRONG_INPUT_IN_LABEL : return "WRONG_INPUT_IN_LABEL";
		
		case SYMBOL_ALREADY_IN_THE_TABLE : return "SYMBOL_ALREADY_IN_THE_TABLE"; 

		case LABEL_INPUT_TOO_LONG : return "LABEL_INPUT_TOO_LONG";		
		
		case WRONG_INSTRUCTION_NAME : return "WRONG_INSTRUCTION_NAME";

		case WRONG_INPUT_VALUE : return "WRONG_INPUT_VALUE";

		case WRONG_OPERAND : return "WRONG_OPERAND";

		case TOO_MANY_OPERANDS : return "TOO_MANY_OPERANDS";

		default: return NULL;	

	}

}

/*prints error trace stack*/ 

void printErrorList(Errorptr head){

	Errorptr p;

	p = head;

	while(p != NULL){
		printf("%s, in line: %d\n",getError(p->title), p->lineNumber);				

		p=p->next;

	}

	printf("\n");

	return;	

}



char *isOpCode(char *word){

	int i;

	for (i=0;i<16;i++){

		if(strcmp(word,opcodesArray[i].opcodeName)==0){

			return word;		

		}	

	}

	return NULL;

}

void addToSymbolList(pSymbol *head,pSymbol *last, char *str, int counter,unsigned int isAct, unsigned int isExt)  {

	pSymbol temp,p;

	temp = (pSymbol) malloc(sizeof(symbol));/* allocate memory for a new 														Error in list*/

	if (!temp){

		fprintf(stderr, "Memory allocation failed\n");

		exit(0);

	}

	/*new item is put in a temporary node before entering the list*/

	temp->label = str;

	temp->address = counter;

	temp->action = isAct;

	temp->external = isExt;

	temp->next = NULL;

	if (!(*head)){	/*insert to an empty list*/

		*last = temp;

		*head = temp;

	}

	else {	/*insert to a non-empty list */

		p = *last;

		p->next = temp;

		*last = p->next;

	}		

}

pSymbol findSymbolByLabel(char *label)
{
	pSymbol currentSymbol = SymbolTable;
	while(currentSymbol)
	{
		if(strcmp(label,currentSymbol->label)==0)
		{
			return currentSymbol;
		}
		currentSymbol = currentSymbol->next;
	}
	return NULL;
}

void printSymbolList(pSymbol head){

	pSymbol p;

	p = head;

	while(p != NULL){
		printf("Label: %s, Address: %d, External: %d, Action: %d\n",p->label, p->address, p->external, p->action);				

		p=p->next;

	}

	printf("\n");

	return;	

}
