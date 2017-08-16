
#define MAXNUMBERSIZE 20

typedef struct parms
{
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
	short destinationNum;
} parms;

typedef struct
{
	eParametersType paramFunc;
	void (*func)(parms);
} cmd;

char* tabArray = "/t";
typedef enum 
{
	VALUE_VALUE,
	REGISTER_VALUE,
	SYMBOL_VALUE,
	MATRIX_VALUE,
	TWO_REGISTER,
	REGISTER_SYMBOL,
	REGISTER_MATRIX,
	MATRIX_REGISTER,
	SYMBOL_REGISTER,
	SYMBOL_MATRIX,
	MATRIX_SYMBOL,
	SYMBOL_SYMBOL,
	MATRIX_MATRIX,
	VALUE_REGISTER,
	VALUE_SYMBOL,
	VALUE_MATRIX,
	ONE_VALUE,
	ONE_REGISTER,
	ONE_SYMBOL,
	ONE_MATRIX,
	NONE_PARAMETERS
} eParametersType;

cmd movs[] = 
{
	{TWO_REGISTER,movTwoRegisterCmd},
	{REGISTER_SYMBOL,movRegisterSymbolCmd},
	{REGISTER_MATRIX,movRegisterMatrixCmd},
	{MATRIX_REGISTER,movMatrixRegisterCmd},
	{SYMBOL_REGISTER,movSymbolRegisterCmd},
	{SYMBOL_MATRIX,movSymbolMatrixCmd},
	{MATRIX_SYMBOL,movMatrixSymbolCmd},
	{SYMBOL_SYMBOL,movSymbolSymbolCmd},
	{MATRIX_MATRIX,movMatrixMatrixCmd},
	{VALUE_REGISTER,movValueRegisterCmd},
	{VALUE_SYMBOL,movValueSymbolCmd},
	{VALUE_MATRIX,movValueMatrixCmd}
};

cmd cmps[] = 
{
	{TWO_REGISTER,cmpTwoRegisterCmd},
	{REGISTER_SYMBOL,cmpRegisterSymbolCmd},
	{REGISTER_MATRIX,cmpRegisterMatrixCmd},
	{MATRIX_REGISTER,cmpMatrixRegisterCmd},
	{SYMBOL_REGISTER,cmpSymbolRegisterCmd},
	{SYMBOL_MATRIX,cmpSymbolMatrixCmd},
	{MATRIX_SYMBOL,cmpMatrixSymbolCmd},
	{SYMBOL_SYMBOL,cmpSymbolSymbolCmd},
	{MATRIX_MATRIX,cmpMatrixMatrixCmd},
	{VALUE_REGISTER,cmpValueRegisterCmd},
	{VALUE_SYMBOL,cmpValueSymbolCmd},
	{VALUE_MATRIX,cmpValueMatrixCmd}
};

cmd adds[] = 
{
	{TWO_REGISTER,addTwoRegisterCmd},
	{REGISTER_SYMBOL,addRegisterSymbolCmd},
	{REGISTER_MATRIX,addRegisterMatrixCmd},
	{MATRIX_REGISTER,addMatrixRegisterCmd},
	{SYMBOL_REGISTER,addSymbolRegisterCmd},
	{SYMBOL_MATRIX,addSymbolMatrixCmd},
	{MATRIX_SYMBOL,addMatrixSymbolCmd},
	{SYMBOL_SYMBOL,addSymbolSymbolCmd},
	{MATRIX_MATRIX,addMatrixMatrixCmd},
	{VALUE_REGISTER,addValueRegisterCmd},
	{VALUE_SYMBOL,addValueSymbolCmd},
	{VALUE_MATRIX,addValueMatrixCmd}
};

cmd subs[] = 
{
	{TWO_REGISTER,subTwoRegisterCmd},
	{REGISTER_SYMBOL,subRegisterSymbolCmd},
	{REGISTER_MATRIX,subRegisterMatrixCmd},
	{MATRIX_REGISTER,subMatrixRegisterCmd},
	{SYMBOL_REGISTER,subSymbolRegisterCmd},
	{SYMBOL_MATRIX,subSymbolMatrixCmd},
	{MATRIX_SYMBOL,subMatrixSymbolCmd},
	{SYMBOL_SYMBOL,subSymbolSymbolCmd},
	{MATRIX_MATRIX,subMatrixMatrixCmd},
	{VALUE_REGISTER,subValueRegisterCmd},
	{VALUE_SYMBOL,subValueSymbolCmd},
	{VALUE_MATRIX,subValueMatrixCmd}
};

cmd leas[] = 
{
	{TWO_REGISTER,leaTwoRegisterCmd},
	{REGISTER_SYMBOL,leaRegisterSymbolCmd},
	{REGISTER_MATRIX,leaRegisterMatrixCmd},
	{MATRIX_REGISTER,leaMatrixRegisterCmd},
	{SYMBOL_REGISTER,leaSymbolRegisterCmd},
	{SYMBOL_MATRIX,leaSymbolMatrixCmd},
	{MATRIX_SYMBOL,leaMatrixSymbolCmd},
	{SYMBOL_SYMBOL,leaSymbolSymbolCmd},
	{MATRIX_MATRIX,leaMatrixMatrixCmd},
	{VALUE_REGISTER,leaValueRegisterCmd},
	{VALUE_SYMBOL,leaValueSymbolCmd},
	{VALUE_MATRIX,leaValueMatrixCmd}
};

cmd nots[] =
{
	{ONE_REGISTER,notRegisterCmd},
	{ONE_SYMBOL,notSymbolCmd},
	{ONE_MATRIX,notMatrixCmd}
};

cmd clrs[] =
{
	{ONE_REGISTER,clrRegisterCmd},
	{ONE_SYMBOL,clrSymbolCmd},
	{ONE_MATRIX,clrMatrixCmd}
};

cmd incs[] =
{
	{ONE_REGISTER,incRegisterCmd},
	{ONE_SYMBOL,incSymbolCmd},
	{ONE_MATRIX,incMatrixCmd}
};

cmd decs[] =
{
	{ONE_REGISTER,decRegisterCmd},
	{ONE_SYMBOL,decSymbolCmd},
	{ONE_MATRIX,decMatrixCmd}
};

cmd jmps[] =
{
	{ONE_REGISTER,jmpRegisterCmd},
	{ONE_SYMBOL,jmpSymbolCmd},
	{ONE_MATRIX,jmpMatrixCmd}
};

cmd bnes[] =
{
	{ONE_REGISTER,bneRegisterCmd},
	{ONE_SYMBOL,bneSymbolCmd},
	{ONE_MATRIX,bneMatrixCmd}
};

cmd reds[] =
{
	{ONE_REGISTER,redRegisterCmd},
	{ONE_SYMBOL,redSymbolCmd},
	{ONE_MATRIX,redMatrixCmd}
};

cmd prns[] =
{
	{ONE_REGISTER,prnRegisterCmd},
	{ONE_SYMBOL,prnSymbolCmd},
	{ONE_MATRIX,prnMatrixCmd}
};

cmd jsrs[] =
{
	{ONE_REGISTER,jsrRegisterCmd},
	{ONE_SYMBOL,jsrSymbolCmd},
	{ONE_MATRIX,jsrMatrixCmd}
};

cmd rtss[] =
{
	{NONE_PARAMETERS,rtsCmd}
};

cmd stops[] =
{
	{NONE_PARAMETERS,StopCmd}
};


void readdressSymbolTable();
int analizeLineSecTransition(char *line);
cmd getCmdToPreform(char* cmdName , eParametersType funcParametersType);
void addToExternFile(pSymbol externSymbol);
void addToEntryFile(pSymbol entrySymbol);
eParametersType assignTwoCommandParametersType(eAddressingMethod firstParam , eAddressingMethod secondParam);
void writeObjectFile();

/*mov commands*/
void movTwoRegisterCmd(parms data);
void movRegisterSymbolCmd(parms data);
void movRegisterMatrixCmd(parms data);
void movMatrixRegisterCmd(parms data);
void movSymbolRegisterCmd(parms data);
void movSymbolMatrixCmd(parms data);
void movMatrixSymbolCmd(parms data);
void movSymbolSymbolCmd(parms data);
void movMatrixMatrixCmd(parms data);
void movValueRegisterCmd(parms data);
void movValueSymbolCmd(parms data);
void movValueMatrixCmd(parms data);

/*cmp commands*/ /*Add cmp with value as destination and value-value*/
void cmpValueValueCmd(parms data);
void cmpRegisterValueCmd(parms data);
void cmpSymbolValueCmd(parms data);
void cmpMatrixValueCmd(parms data);
void cmpTwoRegisterCmd(parms data);
void cmpRegisterSymbolCmd(parms data);
void cmpRegisterMatrixCmd(parms data);
void cmpSymbolRegisterCmd(parms data);
void cmpMatrixRegisterCmd(parms data);
void cmpSymbolMatrixCmd(parms data);
void cmpMatrixSymbolCmd(parms data);
void cmpSymbolSymbolCmd(parms data);
void cmpMatrixMatrixCmd(parms data);
void cmpValueRegisterCmd(parms data);
void cmpValueSymbolCmd(parms data);
void cmpValueMatrixCmd(parms data);

/*add commands*/
void addTwoRegisterCmd(parms data);
void addRegisterSymbolCmd(parms data);
void addRegisterMatrixCmd(parms data);
void addMatrixRegisterCmd(parms data);
void addSymbolRegisterCmd(parms data);
void addMatrixSymbolCmd(parms data);
void addSymbolSymbolCmd(parms data);
void addSymbolMatrixCmd(parms data);
void addMatrixMatrixCmd(parms data);
void addValueRegisterCmd(parms data);
void addValueSymbolCmd(parms data);
void addValueMatrixCmd(parms data);

/*sub commands*/
void subTwoRegisterCmd(parms data);
void subRegisterSymbolCmd(parms data);
void subRegisterMatrixCmd(parms data);
void subSymbolRegisterCmd(parms data);
void subMatrixRegisterCmd(parms data);
void subMatrixMatrixCmd(parms data);
void subSymbolSymbolCmd(parms data);
void subMatrixSymbolCmd(parms data);
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
void prnValueCmd(parms data);
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
