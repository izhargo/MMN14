

extern char *instructions[];
extern char *registerNames[];
extern int flagLabel;
typedef struct binWord{
	short a : 10;
}binWord;

void analizeLine(char *line, int lineNum);
void moveOverFileOne(FILE* currentFile);

