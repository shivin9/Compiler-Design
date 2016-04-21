/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/

#include "symData.h"

void checkTree(parseTree ast, symLink tab, char* func, lex type){
    if(ast == NULL)
        return;
    if(ast != NULL && (ast->val == 51 || ast->val == 52 || ast->val == 53)){
        lex typeId = getNewlex();
        // ast is a number
        if(ast->val == 52 || ast->val == 53){
            // +7 to convert tk_num to tk_int
            // printf("ast is number = %s\n", terms[ast->val+7]);
            strcpy(typeId->token, terms[ast->val+7]);
        }

        else{
            // getType fetches the type of ID
            //printTreeNode(ast);
            typeId = getType(tab, ast->lexeme->value, func);
            if(typeId == NULL){
                printf("ast = %s has not been initialized!!\n", ast->lexeme->value);
                return;
            }
        }
        //type of ID and ast dont match
        if(strcmp(typeId->token, type->token)){
            //printf("type of variable is %s \n", type->token);
            //printf("typeId of left is %s \n", typeId->token);
            printf("error!! types dont match %s is of type %s not %s \n", ast->lexeme->value, typeId->token, type->token);
            return;
        }
    }
    else{
        checkTree(ast->down, tab, func, type);
        checkTree(ast->left, tab, func, type);
    }
}

// ast is a funId
int checkAssign(symLink tab, parseTree ast, parseTree funcNode){
    if(ast == NULL)
        return;

    else if(ast != NULL && ast->val == 48 && ast->up->val != 26){
        // get the type of x in x <--- y
        lex type = getType(tab, ast->down->lexeme->value, funcNode->lexeme->value);
        if(type == NULL){
            printf("%s has not been initialized\n", ast->down->lexeme->value);
            checkAssign(tab, ast->left, funcNode);
        }
        else{
            // pass the ast, symbol table, name of function and type of x
            checkTree(ast->down->left, tab, funcNode->lexeme->value, type);
            checkAssign(tab, ast->left, funcNode);
        }
    }

    else{
        checkAssign(tab, ast->down, funcNode);
        checkAssign(tab, ast->left, funcNode);
    }
}