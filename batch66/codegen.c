/*
   BATCH NUMBER - 66
   SHIVIN SRIVASTAVA - 2013A7PS073P
   UPADHYAY GAURAV ARVIND - 2013A7PS030P
   */

#include "symData.h"

void generateCode(parseTree ast, FILE* fp){

        fprintf(fp, "global main\n");
        fprintf(fp, "extern printf, scanf\n");
        fprintf(fp, "section .symDataformat:db %d, 0 \n");
}
