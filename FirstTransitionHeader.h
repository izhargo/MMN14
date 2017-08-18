
extern char *instructions[];
extern char *registerNames[];
extern int flagLabel;
typedef struct binWord{
	short a : 10;
}binWord;
/*
typedef struct instructionHandle{
	char *inst;
	void (*func)(char *);
} instructionHandle;

extern instructionHandle instructions[];
*/
