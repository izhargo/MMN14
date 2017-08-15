#define MAXLINE	80
#define MAXLABEL 30
#define opLength 4
#define numInstructions 5;

extern int flagLabel;

typedef struct instructionHandle{
	char *inst;
	void (*func)(char *);
} instructionHandle;

extern instructionHandle instructions[];
