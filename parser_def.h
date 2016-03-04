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
static int g[90][10];
static char* terms[110] = {     "program", "mainFunction", "otherFunctions", "function", "input_par", //5
                                "output_par", "parameter_list", "dataType", "primitiveDatatype", //9
                                "constructedDatatype", "remaining_list", "stmts", "typeDefinitions",//13
                                "typeDefinition", "fieldDefinitions", "fieldDefinition",//16
                                "moreFields", "declarations", "declaration", "global_or_not",//20
                                "otherStmts","stmt","assignmentStmt", "singleOrRecId","new_24",//25
                                "funCallStmt", "outputParameters","inputParameters", "iterativeStmt", //29
                                "conditionalStmt", "ioStmt","allVar","arithmeticExpression","expPrime",//34
                                "term", "termPrime", "factor", "highPrecedenceOperators",//38
                                "lowPrecedenceOperators","all", "temp", "booleanExpression",//42
                                "var", "logicalOp", "relationalOp", "returnStmt", //46
                                "optionalReturn", "idList", "more_ids",//49

                                "TK_ASSIGNOP","TK_COMMENT", "TK_FIELDID", "TK_ID", "TK_NUM", "TK_RNUM",//55
                                "TK_FUNID", "TK_WITH", "TK_PARAMETERS", "TK_END", "TK_WHILE", "TK_INT",//61
                                "TK_REAL", "TK_TYPE", "TK_MAIN", "TK_GLOBAL", "TK_PARAMETER",//66
                                "TK_LIST", "INPUT", "TK_OUTPUT", "TK_ENDWHILE", "TK_IF",//71
                                "TK_THEN","TK_ENDIF", "TK_READ", "TK_WRITE", "TK_RETURN",//76
                                "TK_CALL", "TK_RECORD", "TK_ENDRECORD", "TK_ELSE", "TK_SQL",//81
                                "TK_SQR", "TK_SEM", "TK_COLON", "TK_DOT", "TK_OP", "TK_CL", "TK_PLUS",//88
                                "TK_MINUS", "TK_MUL", "TK_DIV", "TK_COMMENT", "TK_COMMA", "TK_NEG",//94
                                "TK_AND", "TK_OR", "TK_EQ", "TK_GE", "TK_GT", "TK_LE", "TK_LT",//101
                                "TK_ASSIGNOP","TK_NE", "TK_RECORDID", "TK_FUNID", "TK_MAIN", "TK_NUM",//107
                                "TK_RNUM", "TK_ID", "eps"};//110