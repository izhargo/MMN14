#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORDLENGTH 10

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

typedef struct
{
	unsigned int opcodeNum;
	char* opcodeName;
} opcodeStruct;

opcodeStruct opcodesArray[16] = 
{
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
typedef enum {Immediate = 0 , Direct = 1 , MarixAccess = 2 , DirectRegister = 3} eAddressingMethod;
typedef enum {A = 0 , B = 1 , C = 2 , D = 3} eWierdFourCountNums;

registers cpuRegisters[8];
memoryWord cpuFullMemory[256];

char* convertToWeirdFour(short);

int IC;
int DC;

typedef struct symbol* pSymbol; /*represent a pointer to a single symbol*/

typedef struct symbol{ /*a symbol in a linked list representing a symbol 								table*/ 

	char* label;

	int addresse;	

	unsigned int action:1;

	unsigned int external:1;

	pSymbol	next;

}symbol;

pSymbol SymbolTable;
pSymbol SymbolTableLast;

typedef enum errors {NONE, WRONG_COMMAND_LINE_INPUT ,WRONG_INSTRUCTION_NAME, WRONG_TYPE_OF_INPUT_SHOULD_INPUT_AN_INTEGER, WRONG_TYPE_OF_INPUT_SHOULD_INPUT_A_STRING, WRONG_OPERAND_SHOULD_INPUT_A_REGISTER_ADDRESS, WRONG_OPERAND_SHOULD_INPUT_A_MATRIX_REFERENCE, SYMBOL_ALREADY_IN_THE_TABLE} errorType;
  
typedef struct errorNode* Errorptr;

typedef struct errorNode{

	errorType description;

	int lineNumber;

	Errorptr next;

} error_node;

Errorptr errorList;
Errorptr errorListLast;

/*function adds an error to the linked list of errors in the assembly program*/ 
void addError (Errorptr *head, Errorptr *last, errorType err, int numLine);
void printErrorList(Errorptr head);
