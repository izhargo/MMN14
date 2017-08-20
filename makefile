assembler: utils.o firstTransition.o assembler.o secondTransition.o
	gcc -ansi -Wall -pedantic utils.o firstTransition.o secondTransition.o assembler.o -o assembler
assembler.o: assembler.c assembler.h FirstTransitionHeader.h SecondTransitionHeader.h SharedHeaderFile.h
	gcc -c -ansi -Wall -pedantic assembler.c -o assembler.o
secondTransition.o: SecondTransition.c SharedHeaderFile.h SecondTransitionHeader.h
	gcc -c -ansi -Wall -pedantic SecondTransition.c -o secondTransition.o
firstTransition.o: FirstTransition.c SharedHeaderFile.h FirstTransitionHeader.h
	gcc -c -ansi -Wall -pedantic FirstTransition.c -o firstTransition.o
utils.o: Utils.c SharedHeaderFile.h
	gcc -c -ansi -Wall -pedantic Utils.c -o utils.o
