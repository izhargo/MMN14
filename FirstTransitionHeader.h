

extern char *instructions[];
extern char *registerNames[];
extern int flagLabel;
/*helps with handling dataArray*/
typedef struct binWord{
	unsigned int a : 10;
}binWord;

void analizeLine(char *line, int lineNum);
void moveOverFileOne(FILE* currentFile);

