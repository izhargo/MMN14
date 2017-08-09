
typedef struct parms
{
	registers* regSource;
	registers* regDestination;
	eCpuRegisters eRegSource;
	eCpuRegisters eRegDestination;
	pSymbol symbolSource;
	pSymbol symbolDestination;
	pSymbol matrixSource;
	eCpuRegisters eMatrixRegRowSource;
	eCpuRegisters eMatrixRegColumnSource;
	pSymbol matrixDestination;
	eCpuRegisters eMatrixRegRowDestination;
	eCpuRegisters eMatrixRegColumnDestination;
	short sourceNum;
} parms;

typedef struct
{
char *name;
void (*func)(parms);
} cmd;

void readdressSymbolTable();

/*mov commands*/
void movTwoRegisterCmd(parms data);
void movRegisterSymbolCmd(parms data);
void movSymbolRegisterCmd(parms data);
void movSymbolSymbolCmd(parms data);
void movValueRegisterCmd(parms data);
void movValueSymbolCmd(parms data);

/*cmp commands*/
void cmpTwoRegisterCmd(parms data);
void cmpRegisterSymbolCmd(parms data);
void cmpSymbolRegisterCmd(parms data);
void cmpSymbolSymbolCmd(parms data);
void cmpValueRegisterCmd(parms data);
void cmpValueSymbolCmd(parms data);

/*add commands*/
void addTwoRegisterCmd(parms data);
void addRegisterSymbolCmd(parms data);
void addSymbolRegisterCmd(parms data);
void addSymbolSymbolCmd(parms data);
void addValueRegisterCmd(parms data);
void addValueSymbolCmd(parms data);

/*sub commands*/
void subTwoRegisterCmd(parms data);
void subRegisterSymbolCmd(parms data);
void subRegisterMatrixCmd(parms data);
void subSymbolRegisterCmd(parms data);
void subMatrixRegisterCmd(parms data);
void suMatrixMatrixCmd(parms data);
void subSymbolSymbolCmd(parms data);
void suMatrixSymbolCmd(parms data);
void subSymbolMatrixCmd(parms data);
void subValueRegisterCmd(parms data);
void subValueSymbolCmd(parms data);
void subValueMatrixCmd(parms data);

/*lea commands*/
void leaTwoRegisterCmd(parms data);
void leaRegisterSymbolCmd(parms data);
void leaMatrixSymbolCmd(parms data);
void leaRegisterMatrixCmd(parms data);
void leaSymbolRegisterCmd(parms data);
void leaMatrixRegisterCmd(parms data);
void leaSymbolSymbolCmd(parms data);
void leaSymbolMatrixCmd(parms data);
void leaMatrixMatrixCmd(parms data);
void leaValueRegisterCmd(parms data);
void leaValueSymbolCmd(parms data);
void leaValueMatrixCmd(parms data);

/*not commands*/
void notRegisterCmd(parms data);
void notSymbolCmd(parms data);
void notMatrixCmd(parms data);

/*clr commands*/
void clrRegisterCmd(parms data);
void clrSymbolCmd(parms data);
void clrMatrixCmd(parms data);

/*inc commands*/
void incRegisterCmd(parms data);
void incSymbolCmd(parms data);
void incMatrixCmd(parms data);

/*dec commands*/
void decRegisterCmd(parms data);
void decSymbolCmd(parms data);
void decMatrixCmd(parms data);

/*jmp commands*/
void jmpRegisterCmd(parms data);
void jmpSymbolCmd(parms data);
void jmpMatrixCmd(parms data);

/*bne commands*/
void bneRegisterCmd(parms data);
void bneSymbolCmd(parms data);
void bneMatrixCmd(parms data);

/*red commands*/
void redRegisterCmd(parms data);
void redSymbolCmd(parms data);
void redMatrixCmd(parms data);

/*prn commands*/
void prnRegisterCmd(parms data);
void prnSymbolCmd(parms data);
void prnMatrixCmd(parms data);

/*jsr commands*/
void jsrRegisterCmd(parms data);
void jsrSymbolCmd(parms data);
void jsrMatrixCmd(parms data);

/*rts command*/
void rtsCmd(parms data);

/*stop command*/
void StopCmd(parms data);
