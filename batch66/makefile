output: lexer.o parser.o driver.o symTable.o typeChecker.o
	gcc -w driver.o symTable.o parser.o lexer.o typeChecker.o -o stage1exe

lexer.o: lexerDef.h lexer.c 
	gcc -w -c -g lexer.c

parser.o: parserDef.h parser.c 
	gcc -w -c -g parser.c

symTable.o: symData.h symTable.c 
	gcc -w -c -g symTable.c

typeChecker.o: typeChecker.c
	gcc -w -c -g typeChecker.c

driver.o: driver.c
	gcc -w -c -g driver.c
clean:
	rm *.o
