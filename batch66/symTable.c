#include "symData.h"

dLink createData()
{
    dLink tab=(dLink)malloc(sizeof(dNode));
    tab->lexName=getNewlex();
    tab->lexType=getNewlex();
    tab->rec=0;
    tab->offset=0;
    tab->down=NULL;
    tab->next=NULL;
    return tab;
}

//creating function Table

funcLink createFunc()
{
    funcLink tab=(funcLink)malloc(sizeof(funcBox));
    tab->lexeme=NULL;
    tab->inp=NULL;
    tab->out=NULL;
    tab->var=NULL;
    return tab;
}

//  creating symbol table
symLink createSym()
{
    int i;
    symLink tab=(symLink)malloc(sizeof(symBox));
    for(i=0;i<10;i++){
        tab->func[i]=createFunc();
    }
    tab->glo=NULL;
    tab->nFunc=0;
    printf("returning tab!\n");
    return tab;
}

void cpyLex(lex d,lex l)
{
    if(d == NULL)
        printf("d in cpylex is null\n");
    strcpy(d->token,l->token);
    strcpy(d->value,l->value);
    d->line=l->line;
}


// linked list of dLinks
// void getTypeDef(symLink tab,parseTree typeDef,int nFunc)
// {


// }

// linked list of int/real
void getDec(symLink tab, parseTree declarations, int nFunc)
{
    parseTree dec = declarations->down;
    while(dec != NULL){
        dLink dvar = createData();
        cpyLex(dvar->lexName,dec->lexeme);

        if(dec->down != NULL)
            cpyLex(dvar->lexType,dec->down->lexeme);

        if((dec->down->left)!=NULL)
        {
            dLink g = tab->glo;
            printf("\ninserting in global: ");
            // print(de);
            if(tab->glo == NULL)
                tab->glo=dvar;
            else
            {
                while(g->next != NULL)
                    g=g->next;
                g->next=dvar;
            }
        }
        else
        {
            if(tab->func[nFunc]->var==NULL)
                tab->func[nFunc]->var=dvar;
            else{
                dLink temp = tab->func[nFunc]->var;

                while(temp->next != NULL)
                    temp = temp->next;

                temp->next = dvar;
            }
        }
        dec=dec->left;
    }
}

void printDNode(dLink dlk){
    if(dlk == NULL)
        return;
    else{
        printf("lexName: ");
        printLex(dlk->lexName);
        printf("\nlexType: ");
        printLex(dlk->lexType);

        printf("\ndlk->down: ");
        printDNode(dlk->down);

        printf("\ndlk->next: ");
        printDNode(dlk->next);
    }
}

void printFunBox(funcLink flink){
    if(flink == NULL)
        return;
    else{
        printf("\nFunction Details: ");
        printLex(flink->lexeme);
        printf("\ninp: ");
        printDNode(flink->inp);
        printf("\nout: ");
        printDNode(flink->out);
        printf("\nvar: ");
        printDNode(flink->var);
        printf("\n");
    }
}

void printSymTable(symLink tab){
    printf("nFuncs = %d\n", tab->nFunc);
    int i;
    for(i = 0; i < tab->nFunc + 1; i++){
        printFunBox(tab->func[i]);
    }
    printf("glo = \n");
    printDNode(tab->glo);
}

// returns the final dlinks under stmts
void getStmt(symLink tab,parseTree stmts,int nFunc){
    //getTypeDef(tab,stmts->down,nFunc);
    getDec(tab,stmts->down->left,nFunc);

}

// filling function in symbol table
void insertFunc(symLink tab, parseTree ast)
{
    int nFunc = tab->nFunc;

    // initialize lexeme of func
    tab->func[nFunc]->lexeme = getNewlex();

    parseTree tempIn,tempOut,tempVar, funId;
    funId = ast;

    cpyLex(tab->func[nFunc]->lexeme, funId->lexeme);

    // special initialization for TK_MAIN
    if(funId->val != 62){
        tempIn = funId->down->down;
        tempOut = funId->down->left->down;
        tempVar = funId->down->left->left;
    }
    else{
        tempIn = NULL;
        tempOut = NULL;
        tempVar = funId->down;
    }

    // filling inputs
    while(tempIn!=NULL)
    {
        dLink dinp = createData();

        cpyLex(dinp->lexName, tempIn->lexeme);
        // printf("printing tempin\n");
        printTreeNode(tempIn);
        cpyLex(dinp->lexType, tempIn->down->lexeme);

        // printf("printing tempin->down\n");
        printTreeNode(tempIn->down);
        //printLex(tempIn->down->lexeme);

        // handling the first case separately
        if(tab->func[nFunc]->inp == NULL){
            tab->func[nFunc]->inp = dinp;
            // printf("inserting...\n");
            printDNode(dinp);
        }

        else{
            dLink temp = tab->func[nFunc]->inp;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = dinp;
        }
        tempIn=tempIn->left;
    }

    //printSymTable(tab);
    //printf("**********************************\nFunc");
    while(tempOut!=NULL)
    {
        dLink outVars = createData();

        cpyLex(outVars->lexName,tempOut->lexeme);
        cpyLex(outVars->lexType,tempOut->down->lexeme);

        if(tab->func[nFunc]->out==NULL)
            tab->func[nFunc]->out=outVars;

        else{
            dLink temp = tab->func[nFunc]->out;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = outVars;
        }
        tempOut=tempOut->left;
    }
    //("**********************************\n");
    //printSymTafunId->down->left->downble(tab);
    getStmt(tab,tempVar,nFunc);
}

void getSymtable(symLink s, parseTree ast)
{
    parseTree temp = ast;
    temp = temp->down->down;
    // for functions
    while(temp != NULL){
        // printf("\nnode = ");
        // printTreeNode(temp);
        insertFunc(s, temp);
        s->nFunc++;
        temp = temp->left;
    }
    // inserting main function
    insertFunc(s, ast->down->left);
}

// to search a variable in the symbol table
int searchTable(symLink tab, char* name, char* type, char* func){
    int i = 0;

    // find the corresponding entry for that function
    while(strcmp(tab->func[i]->lexeme->value, func)){
        i++;
        if(i > tab->nFunc){
            return -1;
        }
    }

    // variable we're searching is record type
    //if(!strcmp(type->token, "TK_RECORDID")){

    //}
    dLink function = tab->func[i]->var;
    dLink glob = tab->glo;
    int pres = 0;
    // variable is int/float type
    //else{
        // only when both are 1, loop will terminate
        while(function != NULL && (strcmp(function->lexName->value, name) || strcmp(function->lexType->value, type))){
            function = function->next;
            if(function == NULL){
                pres = 0;
                break;
            }
        }
        if(!pres){
            while(strcmp(glob->lexName->value, name) || strcmp(glob->lexType->value, type)){
                glob = glob->next;
                if(glob == NULL){
                    return 0;
                }
            }
        }
        return 1;
}

// ge the type of variable given the name
lex getType(symLink tab, char* name, char* func){
    int i = 0;

    // find the corresponding entry for that function
    while(strcmp(tab->func[i]->lexeme->value, func)){
        i++;
        if(i > tab->nFunc){
            return NULL;
        }
    }

    // variable we're searching is record type
    //if(!strcmp(type->token, "TK_RECORDID")){

    //}
    dLink function = tab->func[i]->var;
    dLink glob = tab->glo;
    int pres = 1;
    // variable is int/float type
    //else{
        // only when both are 1, loop will terminate
        while(function != NULL && (strcmp(function->lexName->value, name))){
            function = function->next;
            if(function == NULL){
                pres = 0;
                break;
            }
        }
        if(pres)
            return function->lexType;

        if(!pres){
            while(strcmp(glob->lexName->value, name)){
                glob = glob->next;
                if(glob == NULL){
                    return NULL;
                }
            }
        }
    return glob->lexType;
}