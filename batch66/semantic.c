/*
   BATCH NUMBER - 66
   SHIVIN SRIVASTAVA - 2013A7PS073P
   UPADHYAY GAURAV ARVIND - 2013A7PS030P
   */

#include "symData.h"

int gflag=0;

void r2(symLink tab, parseTree otherStmts, char* funcName){
    if(otherStmts == NULL)
        return;
    else if(otherStmts->val == 51){
        lex temp = getType(tab, otherStmts->lexeme->value, funcName);
        if(temp == NULL){
            gflag=1;
            printf("line %d: variable <%s> is undeclared in function <%s>\n", otherStmts->lexeme->line, otherStmts->lexeme->value, funcName);
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

void compareFunc(symLink tab, parseTree ori, parseTree new, char* currFunc, int flag){
    int cnt1 = 0, cnt2 = 0;
    parseTree tempori = ori->down, n1 = new;
    n1 = n1->down;
    //printf("n1 = \n");
    //printTreeNode(n1);
    while(tempori != NULL){
        cnt1++;
        if(tempori->left == NULL){
            tempori = tempori->down->left;
        }
        else
            tempori = tempori->left;
    }

    while(1){
        if(n1->val == 51){
            cnt2++;
            n1 = n1->left;
        }
        else if(n1->down == NULL)
            break;
        else
            n1 = n1->down->down;
    }

    //printf("cnt1 = %d, cnt2 = %d for function %s in function %s\n", cnt1, cnt2, ori->up->up->lexeme->value, currFunc);

    if(cnt1 != cnt2){
        if(flag == 0)
        {
            gflag=1;
            printf("line %d: number of parameters passed to the function <%s> in the function <%s> doesnt match it's signature\n", new->line, ori->up->lexeme->value, currFunc);
}
        if(flag == 1)
        {
            gflag=1;
            printf("line %d: number of output parameters passed to the function <%s> in the function <%s> doesnt match parameters passed in return\n", new->line, ori->up->lexeme->value, currFunc);
}
        return;
    }

    tempori = ori->down, n1 = new;
    n1 = n1->down;
    lex t1, t2;
    // now checking that the types match
    while(tempori != NULL){

        t1 = getType(tab, tempori->lexeme->value, ori->up->lexeme->value);
        // different for output and input parameters

        if(t1 == NULL)


        if(n1->val == 51){
            printTreeNode(n1);
            t2 = getType(tab, n1->lexeme->value, currFunc);
            if(t2 == NULL){
                gflag=1;
                printf("line %d: %s doesnt exist in scope\n", n1->line, n1->lexeme->value);
            }
            else if(strcmp(t1->token, t2->token)){
                if(flag == 0)
                {
                    gflag=1;
                    printf("line %d:  The type <%s> of variable <%s> returned does not match with the type <%s> of the formal output parameter <%s>", ori->line, t1->value, tempori->lexeme->value, t2->value, n1->lexeme->value);
 }

                if(flag == 1)
                {
                    gflag=1;
                    printf("line %d:  The type <%s> of variable <%s> in output list of function <%s> returned does not match with the type <%s> of the returned output parameter <%s>", ori->line, t1->value, tempori->lexeme->value, ori->up->lexeme->value, t2->value, n1->lexeme->value);
            }}

            n1 = n1->left;
            if(n1->down == NULL)
                break;
            else{
                n1 = n1->down->down;
            }
        }


        if(tempori->left == NULL && tempori->up->val != 66){
            //printTreeNode(tempori);
            tempori = tempori->down->left;
        }
        else
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
        compareFunc(tab, signa->down, inp, currFunc, 0);
        // signa->down->left is output
        compareFunc(tab, signa->down->left, out, currFunc, 0);
        r4(tab, funId->left, ast, currFunc);

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
                    gflag=1;
                    printf("Function <%s> is overloaded\n", tab->func[j]->lexeme->value);

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
        gflag=1;
        printf("line %d: recursive definition of function <%s>\n", temp->line, ch);
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

// todo check if undeclared function is being used


void checkFun(symLink tab, char *ch, parseTree temp, char* funName)
{
    int j=0, mark = 0, flag = 0;
    while(!strcmp(tab->func[j++]->lexeme->value,funName))
        mark++;

    j = 0;
    while(j <= mark){
        if(!strcmp(tab->func[j]->lexeme->value, ch)){
            flag = 1;
            break;
        }
        j++;
    }

    if(j == mark){
        gflag=1;
        printf("line %d: Undefined Function <%s> is being used\n", temp->line, ch);
    }
}

void inFunCheck(symLink tab,parseTree temp,char* funName)
{
    if(temp == NULL)
        return;
    else if(temp!=NULL)    {
        char *ch=(char *)malloc(30*sizeof(char));
        if(temp->val == 25){
            strcpy(ch, temp->down->left->lexeme->value);
            checkFun(tab,ch, temp, funName);
            inFunCheck(tab, temp->left, funName);
        }
        else
        {
            inFunCheck(tab,temp->down,funName);
            inFunCheck(tab,temp->left,funName);
        }

    }
}


void othFunCheck(symLink tab,parseTree otherFun)
{
    // otherFun has other functions
    parseTree temp=otherFun->down;

    while(temp!=NULL)              // rest of the functions
    {
        char funName[30];
        //printTreeNode(temp);
        strcpy(funName,temp->lexeme->value);
        inFunCheck(tab,temp->down,funName);
        temp=temp->left;
    }
    // temp=otherFun->left;   // for main function
    // inFunCheck(tab,temp);
}

void r5(symLink tab, parseTree ast){
    parseTree funId = ast->down->down;
    while(funId != NULL){
        parseTree opret = funId->down->left->left->down;

        while(opret->left != NULL)
            opret = opret->left;

        parseTree out = funId->down->left;
        //opret->down has idList
        compareFunc(tab, out, opret->down, funId->lexeme->value, 1);
        funId = funId->left;
    }
}

void dowhile(symLink tab, parseTree ast){
    parseTree funId = ast->down->down;
    while(funId != NULL){
        parseTree opret = funId->down->left->left->down;


        parseTree out = funId->down->left;
        //opret->down has idList
        compareFunc(tab, out, opret->down, funId->lexeme->value, 1);
        funId = funId->left;
    }
}

int testRules(symLink tab, parseTree ast){
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
    // temp has funId
    while(temp != NULL){
        //printf("currfunc = %s\n", temp->lexeme->value);
        r4(tab, temp, ast, temp->lexeme->value);

        temp = temp->left;
    }
    // f4 for _main
    r4(tab, ast->down->left, ast, "_main");
    r5(tab, ast);
    funcRecur(ast->down);
    funcLoad(tab);
    othFunCheck(tab, ast->down);
    return gflag;
}
