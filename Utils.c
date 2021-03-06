#include "SharedHeaderFile.h"

/*A method to convert a short number to string of letters in the wierd four counting system*/
char* convertToWeirdFour(short wordShort)
{
	int i , wordLoc = 0;
	int num;
	char* weirdFourWord;

	weirdFourWord = (char*)malloc(sizeof(char)*6);
	if(!weirdFourWord)
		return NULL;
	wordLoc = (WORDLENGTH/2) - 1;
	for(i = 0; i < WORDLENGTH ; i += 2)
	{
		/*Calculate the number from two adjacent bit*/
		num = ((wordShort & (1  << i))>>i) + 2 * ((wordShort & (1  << (i+1)))>>(i+1));
		/*Fit the right number to the number according to the wierdFourCountNums enum*/
		switch(num)
		{
			case A : weirdFourWord[wordLoc] = 'a'; break;
			case B : weirdFourWord[wordLoc] = 'b'; break;
			case C : weirdFourWord[wordLoc] = 'c'; break;
			case D : weirdFourWord[wordLoc] = 'd'; break;
		}
		wordLoc--;
	}
	wordLoc = (WORDLENGTH/2);
	weirdFourWord[wordLoc] = 0;
	return weirdFourWord;
}

/*A function to add an error to last place in the error list*/
void addToErrorList(Errorptr *head, Errorptr *last, errorType err, int numLine)
{
	Errorptr temp,p;
	temp = (Errorptr) malloc(sizeof(error_node));/* allocate memory for a new Error in list*/
	if (!temp)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(0);

	}
	/*new item is put in a temporary node before entering the list*/
	temp->title = err;
	temp->lineNumber = numLine;
	temp->next = NULL;
	if (!(*head))
	{	
		/*insert to an empty list*/
		*last = temp;
		*head = temp;

	}
	else 
	{	
		/*insert to a non-empty list */
		p = *last;
		p->next = temp;
		*last = p->next;

	}		
}

/*gets a string version of enum value*/
const char *getError(errorType e)
{
	switch (e)
	{
		case NONE: return "NONE";
		case WRONG_COMMAND: return "WRONG_COMMAND";
		case WRONG_INPUT_IN_LABEL : return "WRONG_INPUT_IN_LABEL";
		case SYMBOL_ALREADY_IN_THE_TABLE : return "SYMBOL_ALREADY_IN_THE_TABLE"; 
		case LABEL_INPUT_TOO_LONG : return "LABEL_INPUT_TOO_LONG";		
		case WRONG_INPUT_VALUE : return "WRONG_INPUT_VALUE";
		case LABEL_INPUT_NOT_EXSIST: return "LABEL_INPUT_NOT_EXSIST";
		case WRONG_INSTRUCTION_NAME : return "WRONG_INSTRUCTION_NAME";
		case WRONG_PARAMETER_VALUE : return "WRONG_PARAMETER_VALUE";
		case NO_INPUT_DATA : return "NO_INPUT_DATA";
		case WRONG_MATRIX_SIZE : return "WRONG_MATRIX_SIZE";
		case NO_LABEL_FOR_MATRIX : return "NO_LABEL_FOR_MATRIX";
		case WRONG_MATRIX_INPUT : return "WRONG_MATRIX_INPUT";				
		case WRONG_OPERAND_INPUT : return "WRONG_OPERAND_INPUT";
		case TOO_MANY_OPERANDS : return "TOO_MANY_OPERANDS";
		case TOO_FEW_OPERANDS : return "TOO_FEW_OPERANDS";
		case NO_LABEL_FOR_EXTERN_INSTRUCTION : return "NO_LABEL_FOR_EXTERN_INSTRUCTION";
		case ERROR_IN_LABEL_FOR_EXTERN_INSTRUCTION : return "ERROR_IN_LABEL_FOR_EXTERN_INSTRUCTION";
		default: return NULL;	
	}
}

/*prints error trace stack*/ 
void printErrorList(Errorptr head)
{
	Errorptr p;
	p = head;
	while(p != NULL)
	{
		printf("%s, in line: %d\n",getError(p->title), p->lineNumber);				
		p=p->next;
	}
	printf("\n");
	return;	
}
/*free memory usage by ErrorList*/
void freeErrorList(Errorptr head){
	Errorptr p;
	while (head){
		p= head;
		head = p->next;
		free(p);	
	}
}
/*returns lower-case command if word is a command. Otherwise returs NULL*/
char *isOpCode(char *word)
{
	int i;

	for (i=0;i<16;i++)
	{
		if(strcmp(word,opcodesArray[i].opcodeName)==0)
		{

			return word;		

		}	
	}
	return NULL;
}
/*secure copy of string to a char pointer*/
char *strdup(char *s){
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL){
		strcpy(p, s);	
	}
	return p;
}
/*adds a symbol structure to the end of SymbolTable*/
void addToSymbolList(pSymbol *head,pSymbol *last, char *str, int counter,unsigned int isAct, unsigned int isExt, unsigned int isMat)  
{
	pSymbol temp,p;
	temp = (pSymbol) malloc(sizeof(symbol));/* allocate memory for a new Error in list*/
	if (!temp)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(0);
	}
	/*new item is put in a temporary node before entering the list*/
	temp->label = strdup(str);
	temp->address = counter;
	temp->action = isAct;
	temp->external = isExt;
	temp->matrix = isMat;
	temp->next = NULL;
	if (!(*head))
	{	
		/*insert to an empty list*/
		*last = temp;
		*head = temp;
	}
	else 
	{	
		/*insert to a non-empty list */
		p = *last;
		p->next = temp;
		*last = p->next;
	}		

}
/*returns a pointer to symbol 'x' there's an 'x' in SymbolTable that maintains 
 labal == x->label*/ 
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
/*prints Symbolslist from head to last*/
void printSymbolList(pSymbol head)
{
	pSymbol p;
	p = head;
	while(p != NULL)
	{
		printf("Label: %s, Address: %d, External: %d, Action: %d\n, Matrix: %d\n",p->label, p->address, p->external, p->action, p->matrix);				
		p=p->next;
	}
	printf("\n");
	return;	
}
/*free memory usage by SymbolList*/
void freeSymbolList(pSymbol head){
	pSymbol p;
	while (head){
		p=head;
		head = p->next;
		free(p);	
	}
}

unsigned int getNumOfParamsOfOpCode(char *word)
{
	int i;
	for (i=0;i<16;i++)
	{

		if(strcmp(word,opcodesArray[i].opcodeName)==0)
		{
			return opcodesArray[i].numOfParams;		
		}	
	}
	return (unsigned int)NULL;
}

unsigned int getNumOfOpCode(char *word)
{
	int i;
	for (i=0;i<16;i++)
	{

		if(strcmp(word,opcodesArray[i].opcodeName)==0)
		{
			return opcodesArray[i].opcodeNum;		
		}	
	}
	return (unsigned int)NULL;
}
/*returns 1 if str is consisted of whitespaces (of all kinds) and 0 if not*/
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


