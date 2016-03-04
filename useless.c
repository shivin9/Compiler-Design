#include "parser_dat.h"

int find(char* term){
    int i;
    for(i = 0; i <115; i++){
        if(!strcmp(terms[i], term))
            break;
    }
    return i;
}

int main(){
char* inp[276] = {"$","*","$","*","TK_MAIN","*","TK_FUNID","TK_MAIN","*","TK_OUTPUT","*","TK_SEM","*","TK_SQR","*","TK_COLON","TK_ID","*","TK_COLON","TK_ID","*","TK_COLON","TK_ID","*","TK_SQR","*","TK_END","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_RETURN","TK_TYPE","*","TK_RECORD","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_RETURN","TK_TYPE","*","TK_ENDRECORD","*","TK_TYPE","TK_ENDRECORD","*","TK_ENDRECORD","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","*","TK_TYPE","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","*","TK_SEM","*","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_CL","TK_ASSIGNOP","*","TK_CL","TK_ASSIGNOP","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_CALL","*", "TK_SEM","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_ID","TK_IF","TK_CALL","TK_SQL","TK_WHILE","TK_READ","TK_WRITE","TK_OP","TK_NOT","TK_NUM","TK_RNUM","TK_ENDIF","TK_ELSE","TK_ENDWHILE","TK_RETURN","*","TK_CL","*","TK_CL","TK_SEM","*","TK_CL","TK_SEM","*","TK_PLUS","TK_MINUS","TK_CL","TK_SEM","*","TK_PLUS","TK_MINUS","TK_CL","TK_SEM","*","TK_MUL","TK_DIV","TK_PLUS","TK_MINUS","TK_CL","TK_SEM","*","TK_OP","TK_ID","TK_NUM","TK_RNUM","TK_RECORDID","*","TK_OP","TK_ID","TK_NUM","TK_RNUM","TK_RECORDID","*","TK_MUL","TK_DIV","TK_PLUS","TK_MINUS","TK_CL","TK_SEM","*","TK_MUL","TK_DIV","TK_PLUS","TK_MINUS","TK_CL","TK_SEM","*","TK_CL","*","TK_LT","TK_LE","TK_EQ","TK_GT","TK_GE","TK_NE","TK_CL","*","TK_OP","*","TK_ID","TK_NUM","TK_RNUM","*","TK_END","*","TK_SEM","*","TK_SQR","*","TK_SQR"};
    int i = 0;
    while(i<276){
        //printf("enter string \n");
        //scanf("%s", inp);
        printf("%d\n", find(inp[i++]));
    }
    return 0;
}