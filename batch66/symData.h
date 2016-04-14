#include "parserDef.h"

// node for data type storage and other information
typedef struct dNode dNode;
typedef struct dNode *dLink;

// function box

typedef struct funcBox funcBox;
typedef struct funcBox *funcLink;

// Symbol Table box
typedef struct symBox symBox;
typedef struct symBox *symLink;

// information about types
struct dNode{
    lex lexName;
    lex lexType;
    int rec; // to tell whether it is a constructed or primitive datatype
    int offset;
    dLink down;
    dLink next;
};

// information about function. Each function is directly pointed from symbol table
struct funcBox
{
    lex lexeme;
    dLink inp;
    dLink out;
    dLink var;
};

// symbol table data structure
struct symBox
{
    funcLink func[10];
    dLink glo;
    int nFunc;
};