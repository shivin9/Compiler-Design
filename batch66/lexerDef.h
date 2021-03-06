/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* buffer;
// buffer buffer1;
// buffer buffer2;
// buffer current;

int state;
//lex getNewlex();
struct tokenInfo{
    char* token;
    char* value;
    int line;
};

typedef struct tokenInfo tokenInfo;
typedef tokenInfo *lex;

typedef struct node *link;
typedef struct node node;

struct node{
    lex lex;
    link next;
};

struct head{
    int size;
    link first;
};

typedef struct head *lexChain;

static char* lexemes[24] = {"with", "parameters", "end", "while", "int",
                    "real", "type", "main", "global", "parameter",
                    "list", "input", "output", "endwhile", "if",
                    "then","endif", "read", "write", "return",
                    "call", "record", "endrecord", "else"};

static char* tokens[24] = {"TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_INT",
                    "TK_REAL", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER",
                    "TK_LIST", "TK_INPUT", "TK_OUTPUT", "TK_ENDWHILE", "TK_IF",
                    "TK_THEN","TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN",
                    "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE"};