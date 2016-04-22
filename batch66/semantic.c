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
        lex temp = getType(tab, otherStmts->lexeme->value, funcName);
        if(temp == NULL){
            printf("line %d: variable <%s> is undeclared in function %s\n", otherStmts->lexeme->line, otherStmts->lexeme->value, funcName);
        }
    }
    else{
        r2(tab, otherStmts->down, funcName);
        r2(tab, otherStmts->left, funcName);
    }
}

parseTree getFunc(parseTree ast, char* funcName){
    if(ast->down->down == NULL)
        return NULL;
    else{
        parseTree tempfunc = ast->down->down;
        while(strcmp(tempfunc->lexeme->value, funcName))
            tempfunc = tempfunc->left;
        return tempfunc;
    }
}

void compareFunc(symLink tab, parseTree ori, parseTree new, char* currFunc){
    int cnt1 = 0, cnt2 = 0;
    parseTree tempori = ori->down, n1 = new;
    n1 = n1->down;
    while(tempori != NULL){
        cnt1++;
        // printf("inside tempori\n");
        // printTreeNode(tempori);
        tempori = tempori->left;
    }

    //printTreeNode(n1->down);

    while(1){
        // printf("inside funcallstmt\n");
        // printTreeNode(n1);
        if(n1->val == 51){
            cnt2++;
            n1 = n1->left;
        }
        else if(n1->down == NULL)
            break;
        else
            n1 = n1->down->down;
    }
    // printf("undeccnt1 = %d, cnt2 = %d\n", cnt1, cnt2);
    if(cnt1 != cnt2){
        printf("line %d: number of parameters passed to the function %s doesnt match it's signature\n", ori->line, ori->up->lexeme->value);
        return;
    }

    tempori = ori->down, n1 = new;
    n1 = n1->down;
    lex t1, t2;

    // now checking that the types match
    while(tempori != NULL){
        cnt1++;
        // printf("inside tempori\n");
        t1 = tempori->down->lexeme;
        // printLex(t1);

        if(n1->val == 51){
            cnt2++;
            t2 = getType(tab, n1->lexeme->value, currFunc);

            if(strcmp(t1->token, t2->token)){
                printf("line %d:  The type <%s> of variable <%s> returned does not match with the type <%s> of the formal output parameter <%s>", ori->line, t1->value, tempori->lexeme->value, t2->value, n1->lexeme->value);

            n1 = n1->left;
            }
        }
        else if(n1->down == NULL)
            break;
        else
            n1 = n1->down->down;
        tempori = tempori->left;
    }
}

// ast is the root of ast
// funId is name of function
void r4(symLink tab, parseTree funId, parseTree ast, char* currFunc){
    if(funId == NULL)
        return;
    else if(funId->val == 25){

        parseTree out = funId->down->down;
        parseTree func = funId->down->left;
        parseTree inp = funId->down->left->left;

        parseTree signa = getFunc(ast, func->lexeme->value);
        //printTreeNode(signa);
        compareFunc(tab, signa->down, inp, currFunc);
        // signa->down->left is output
        compareFunc(tab, signa->down->left, out, currFunc);

    }
    else{
        r4(tab, funId->down, ast, currFunc);
        r4(tab, funId->left, ast, currFunc);
    }
}

void funcLoad(symLink tab)
{
   int i=0,j;
   while(tab->func[i]->lexeme!=NULL){
      j=0;
      while(tab->func[j]->lexeme!=NULL){
         if(i==j)
            j++;
         else{

            if(!strcmp(tab->func[j]->lexeme->value,tab->func[i]->lexeme->value)){
                printf("Function %s is overloaded\n", tab->func[j]->lexeme->value);
                exit(0);
            }
         }
         j++;

      }
      i++;
   }
}

void recurse(char *ch, parseTree temp){
    if(temp == NULL)
        return;
    else if(!strcmp(temp->lexeme->value,ch) && temp->up->val == 25){
        printf("recursive definition of function %s\n", ch);
    }
    else{
        //printTreeNode(temp);
        recurse(ch,temp->down);
        recurse(ch,temp->left);
    }

}

void funcRecur(parseTree othFunc){
  parseTree temp1,temp=othFunc->down;
  while(temp!=NULL)
  {
    char *ch = (char*) malloc(30*sizeof(char));
    strcpy(ch, temp->lexeme->value);
    // printf("recursive definition of function %s\n", temp->lexeme->value);
    temp1=temp->down;
    recurse(ch,temp->down);
    //recurse(ch,temp->left);
    free(ch);
    temp=temp->left;
  }
}


void testRules(symLink tab, parseTree ast){
    parseTree temp = ast, otherstmts;

    //temp has function name
    temp = temp->down->down;
    // printTreeNode(temp);
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

    temp = ast->down->down;
    while(temp != NULL){
        r4(tab, temp, ast, temp->lexeme->value);
        temp = temp->left;
    }
    // f4 for _main
    r4(tab, ast->down->left, ast, "_main");

    funcRecur(ast->down);
    funcLoad(tab);
}

// todo check if undeclared function is being used