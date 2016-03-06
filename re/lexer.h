/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/

#include "lexerDef.h"
// MAIN FUNCTIONS
lex getNextToken(FILE *fp, int curr, lexChain chain);
FILE* getStream(FILE *fp, buffer B, int bufflen);


// SUPPORTING FUNCTIONS
lex getNewlex()
link getNewNode();
lexChain initializeChain();
void addNode(lexChain chain, link new);
int newLine(char* B, int curr);
void printNode(link l);
void printList(lexChain chain);
char* keywordsFieldId(char *lexeme);
int isAllowed(char c);
lexChain getAllTokens(FILE* fp);