#include "symData.h"

parseTree getAssignOp(parseTree ast){
    if(ast->val == 48)
        return ast;
    else{
        getAssignOp(ast->down);
        getAssignOp(ast->left);
    }
}

int checkAssign(parseTree funId){

    lex fId = funId->lexeme;
    parseTree ast = getAssignOp(funId);
    lex type = getType(symLink tab, char* name, fId->lexeme->value);

}