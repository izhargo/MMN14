#include "SharedHeaderFile.h"

/*A method to convert a short number to string of letters in the wierd four counting system*/
char* convertToWeirdFour(short wordShort)
{
	int i , wordLoc = 0;
	short num;
	char* weirdFourWord;
	weirdFourWord = (char*)malloc(sizeof(char)*6);
	if(!weirdFourWord)
		return NULL;
	for(i = 0; i < WORDLENGTH; i += 2)
	{
		/*Calculate the number from two adjacent bit*/
		num = (wordShort & (1  << i)) + 2 * (wordShort & (1  << (i+1)));
		/*Fit the right number to the number according to the wierdFourCountNums enum*/
		switch(num)
		{
			case A : weirdFourWord[wordLoc] = 'a'; break;
			case B : weirdFourWord[wordLoc] = 'b'; break;
			case C : weirdFourWord[wordLoc] = 'c'; break;
			case D : weirdFourWord[wordLoc] = 'd'; break;
		}
		wordLoc++;
	}
	weirdFourWord[wordLoc] = 0;
	return weirdFourWord;
}