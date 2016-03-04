#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer_dat.h"

// rows are left
// columns are rights
//int table[33][];

// table of non-terminals
//typedef int** grammar;

//grammar array
//typedef int** table;
typedef int** grammar;

typedef struct table table;
typedef struct table* tableLink;
typedef struct cell cell;
typedef struct cell* nodeLink;

struct Node;                     // individual Node in the tree
typedef struct Node Node;
typedef struct Node *parseTree;      //parseTree is a pointer to the Node

struct Node                       // Node data structure
{
 parseTree up;
 int val;
 int visit;      // whether Node has been visited earlier or not
 parseTree left;
 lex lexeme;
 parseTree down;
};

struct cell{
        int row;
        int col;
        int rule;
        nodeLink next;
};

struct table{
        nodeLink head;
        int size;
};



static int g[90][10];
static char* terms[115] = {     "program", "mainFunction", "otherFunctions", "function", "input_par", //5
                                "output_par", "parameter_list", "dataType", "primitiveDatatype", //9
                                "constructedDatatype", "remaining_list", "stmts", "typeDefinitions",//13
                                "typeDefinition", "fieldDefinitions", "fieldDefinition",//16
                                "moreFields", "declarations", "declaration", "global_or_not",//20
                                "otherStmts","stmt","assignmentStmt", "singleOrRecId","new_24",//25
                                "funCallStmt", "outputParameters","inputParameters", "iterativeStmt", //29
                                "conditionalStmt","elsePart","ioStmt","allVar","arithmeticExpression",//34
                                "expPrime",//35
                                "term", "termPrime", "factor", "highPrecedenceOperators",//39
                                "lowPrecedenceOperators","all", "temp", "booleanExpression",//43
                                "var", "logicalOp", "relationalOp", "returnStmt", //47
                                "optionalReturn", "idList", "more_ids",//50

                                "TK_ASSIGNOP","TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM",//56
                                "TK_FUNID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_INT",//62
                                "TK_REAL", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER",//67
                                "TK_LIST", "TK_INPUT", "TK_OUTPUT", "TK_ENDWHILE", "TK_IF",//72
                                "TK_THEN","TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN",//77
                                "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_SQL",//82
                                "TK_SQR", "TK_SEM", "TK_COLON", "TK_DOT", "TK_OP", "TK_CL", "TK_PLUS",//89
                                "TK_MINUS", "TK_MUL", "TK_DIV", "TK_COMMENT", "TK_COMMA", "TK_NEG",//95
                                "TK_AND", "TK_OR", "TK_EQ", "TK_GE", "TK_GT", "TK_LE", "TK_LT",//102
                                "TK_ASSIGNOP","TK_NE", "TK_RECORDID", "TK_FUNID", "TK_MAIN", "TK_NUM",//108
                                "TK_RNUM", "TK_NOT", "TK_ADD", "TK_SUB", "eps", "$", "*"};//115
