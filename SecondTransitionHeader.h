
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
