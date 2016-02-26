lex getNewlex();
link getNewNode();
lexChain initializeChain();
FILE* getStream(FILE *fp, buffer B, int bufflen);
tokenInfo getNextToken(FILE *fp);
void addlex(lexChain chain, lex lexeme);
void printNode(link l);
void printList(lexChain chain);
int isValidlexeme(char *lexeme);
int isAlpha(char c);
int isNum(char c);
// uses: buffer
___ dfa(buffer B, int start, int end, );
