#define inputFileSuffix "as"
#define maxFileName 30

void validateFileName(char *token);
FILE *handleFileName(char *filename);

typedef struct nameFile{
	char *name;
	char *suffix;
}nameFile;
