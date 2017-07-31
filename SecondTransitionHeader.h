
typedef struct parms
{
	registers* regSource;
	registers* regDestination;
	eCpuRegisters eRegSource;
	eCpuRegisters eRegDestination;
	short sourceNum;
} parms;

typedef struct
{
char *name;
void (*func)(parms);
} cmd;

void movTwoRegisterCmd(parms data);
void movRegisterValueCmd(parms data);
void cmpTwoRegisterCmd(parms data);
void cmpRegisterValueCmd(parms data);
void addTwoRegisterCmd(parms data);
void addRegisterValueCmd(parms data);
void subTwoRegisterCmd(parms data);
void subRegisterValueCmd(parms data);
void leaTwoRegisterCmd(parms data);
void leaRegisterValueCmd(parms data);
void notRegisterCmd(parms data);
void clrRegisterCmd(parms data);
void incRegisterCmd(parms data);
void decRegisterCmd(parms data);
void jmpRegisterCmd(parms data);
void bneRegisterCmd(parms data);
void redRegisterCmd(parms data);
void prnRegisterCmd(parms data);
void jsrRegisterCmd(parms data);
void rtsCmd(parms data);
void StopCmd(parms data);
