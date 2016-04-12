output: lexer.o parser.o driver.o symTable.o
	gcc -w driver.o symTable.o parser.o lexer.o -o stage1exe

lexer.o: lexerDef.h lexer.c 
	gcc -w -c -g lexer.c

parser.o: parserDef.h parser.c 
	gcc -w -c -g parser.c

symTable.o: symData.h symTable.c 
	gcc -w -c -g symTable.c

driver.o: driver.c
	gcc -w -c -g driver.c
clean:
	rm *.o
