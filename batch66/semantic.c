/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/

#include "symData.h"

void r2(symLink tab, parseTree otherStmts, char* funcName){
    if(otherStmts == NULL)
        return;
    else if(otherStmts->val == 51){
        //printLex(otherStmts->lexeme);
        lex temp = getType(tab, otherStmts->lexeme->value, funcName);
        if(temp == NULL){
            printf("variable %s is undeclared in function %s\n", otherStmts->lexeme->value, funcName);
        }
    }
    else{
        r2(tab, otherStmts->down, funcName);
        r2(tab, otherStmts->left, funcName);
    }
}

void testRules(symLink tab, parseTree ast){
    parseTree temp = ast, otherstmts;
    //temp has function name
    temp = temp->down->down;

    // for r2
    while(temp != NULL){
        //stmts has typedef or declaration
        otherstmts = temp->down->left->left->down;
        // to find out otherStmts
        while(otherstmts->val != 20)
            otherstmts = otherstmts->left;
        //printTreeNode(temp);
        r2(tab, otherstmts, temp->lexeme->value);
        temp = temp->left;
    }
    // inserting main function
    otherstmts = ast->down->left->down->down;

    while(otherstmts->val != 20)
            otherstmts = otherstmts->left;

    r2(tab, otherstmts, "_main");
}