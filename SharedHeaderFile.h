#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#define MAXLINE	80
#define MAXLABEL 30
#define MAXWORD 30
#define opLength 4
#define numInstructions 5
#define numRegisters 8


#define WORDLENGTH 10
#define SIZEARRAY 100
#define ENTRY ".ENTRY"
#define EXTERN ".EXTERN"
#define DATA ".DATA"
#define STRING ".STRING"
#define MAT ".MAT"


typedef union commandBitField

{

	struct

	{

		unsigned int encodingType : 2;

		unsigned int destinationOperandAddressing : 2;

		unsigned int sourceOperandAddressing : 2;

		unsigned int opcode : 4;

		unsigned int unused : 4;

	} cBitField;

	short fullCommandInt;

} commandBitField;



typedef union registers

{

	struct

	{

		short reg : 10;

		short unused : 6;

	} r;

	short fullReg;

} registers;



typedef union registersParam

{

	struct

	{

		unsigned int encodingType : 2;

		unsigned int regDestination : 4;

		unsigned int regSource : 4;

		unsigned int unused : 6;

	} regParam;

	short fullRegParam;

} registersParam;

typedef union valueParam

{

	struct

	{

		unsigned int encodingType : 2;

		short numericValue : 8;

		unsigned int unused : 6;

	} valParam;

	short fullValueParam;

} valueParam;

typedef union symbolParam

{

	struct

	{

		unsigned int encodingType : 2;

		short addressValue : 8;

		unsigned int unused : 6;

	} symParam;

	short fullSymbolParam;

} symbolParam;

typedef union memoryWord

{

	struct

	{

		short word : 10;

		short unused : 6;

	} mw;

	short fullReg;

} memoryWord;

extern memoryWord dataArray[];



typedef struct

{

	unsigned int opcodeNum;

	char* opcodeName;

} opcodeStruct;



extern opcodeStruct opcodesArray[];



typedef enum
{

	r0,

	r1,

	r2,

	r3,

	r4,

	r5,

	r6,

	r7

} eCpuRegisters;

typedef enum {Absolute = 0 , External = 1 , Relocatable = 2} eEncodingType;

typedef enum {Immediate = 0 , Direct = 1 , MatrixAccess = 2 , DirectRegister = 3} eAddressingMethod;

typedef enum {A = 0 , B = 1 , C = 2 , D = 3} eWierdFourCountNums;



registers cpuRegisters[8];

memoryWord cpuFullMemory[256];



char* convertToWeirdFour(short);



extern int IC;

extern int DC;

FILE* currentExternFile;
FILE* currentEntryFile;



unsigned int getNumOfParamsOfOpCode(char *word);

typedef struct symbol* pSymbol; /*represent a pointer to a single symbol*/



typedef struct symbol{ /*a symbol in a linked list representing a symbol 								table*/ 



	char* label;



	int address;	

	


	unsigned int action:1;



	unsigned int external:1;


	
	

	pSymbol	next;

	


}symbol;




extern pSymbol SymbolTable;

extern pSymbol SymbolTableLast;


typedef enum errors {NONE,WRONG_INPUT_IN_LABEL,SYMBOL_ALREADY_IN_THE_TABLE,LABEL_INPUT_TOO_LONG,WRONG_INSTRUCTION_NAME, WRONG_PARAMETER_VALUE,WRONG_MATRIX_SIZE,WRONG_MATRIX_PARAMETER_VALUE,NO_LABEL_FOR_MATRIX, WRONG_OPERAND,TOO_MANY_OPERANDS,NO_LABEL_FOR_EXTERN_INSTRUCTION,ERROR_IN_LABEL_FOR_EXTERN_INSTRUCTION} errorType;

  

typedef struct errorNode* Errorptr;



typedef struct errorNode{



	errorType title;



	int lineNumber;



	Errorptr next;



} error_node;



extern Errorptr errorList;

extern Errorptr errorListLast;



/*function adds an error to the linked list of errors in the assembly program*/ 

void addToErrorList(Errorptr *head, Errorptr *last, errorType err, int numLine);
const char *getError(errorType e);
void printErrorList(Errorptr head);
char *isOpCode(char *word);
void addToSymbolList(pSymbol *head,pSymbol *last, char *str, int counter,unsigned int isAct, unsigned int isExt);
pSymbol findSymbolByLabel(char *label);
void printSymbolList(pSymbol head);
unsigned int getNumOfParamsOfOpCode(char *word);
