/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/
#include "parserDef.h"

// MAIN FUNCTIONS
parseTree parseInputSourceCode(parseTree head, FILE *fp, lexChain ch);
void createParseTable(int G[][10], tableLink tabl);
void printTree(parseTree head);


// SUPPORTING FUNCTIONS
nodeLink getNode();
tableLink initializeTable();
void addNewNode(tableLink tabl, int row, int col, int rule);
int findInTable(tableLink head1, int row, int col);
int find(char* term);
int epsInFirst(int alpha, int first[][11]);
int dollarInFollow(int A, int follow[][12]);
void printGrammar(int G[][10],int size);
void printTable(tableLink tabl);
parseTree create();
int push(int stack[],int top,int rule,int gra[][10]);
int pop(int stack[],int top);
parseTree search(parseTree start, int a);
void insert(parseTree temp, int rule,int gra[][10], lex lexem);
void printStack(int a[],int top);
