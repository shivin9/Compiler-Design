
output: lexer.o parser.o driver.o
	gcc -w driver.o parser.o lexer.o -o stage1exe

lexer.o: lexerDef.h lexer.c 
	gcc -w -c -g lexer.c

parser.o: parserDef.h parser.c 
	gcc -w -c -g parser.c

driver.o: driver.c
	gcc -w -c -g driver.c
clean:
	rm *.o
