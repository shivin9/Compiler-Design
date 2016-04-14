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
void getDec(symLink tab, parseTree declarations,int nFunc)
{
    parseTree dec = declarations;
    while(dec != NULL){
        printf("inside getDec\n");
        dLink d = createData();

        cpyLex(d->lexName,dec->lexeme);
        cpyLex(d->lexType,dec->down->lexeme);

        if((dec->down->left)!=NULL)
        {
            dLink g = tab->glo;
            if(tab->glo == NULL)
                tab->glo=d;
            else
            {
                while(g->next != NULL)
                    g=g->next;
                g->next=d;
            }
        }
        else
        {
            if(tab->func[nFunc]->var==NULL)
                tab->func[nFunc]->var=d;
            else{
                while(tab->func[nFunc]->var->next!=NULL)
                    tab->func[nFunc]->var=tab->func[nFunc]->var->next;
                tab->func[nFunc]->var->next=d;
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
        printf("\nlex: ");
        printLex(flink->lexeme);
        printf("\ninp: ");
        printDNode(flink->inp);
        printf("\nout: ");
        printDNode(flink->out);
        printf("\nvar: ");
        printDNode(flink->var);
    }
}

void printSymTable(symLink tab){
    printf("nFuncs = %d\n", tab->nFunc);
    int i = 0;
    for(i; i < tab->nFunc; i++){
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

    funId = ast->down->down;

    cpyLex(tab->func[nFunc]->lexeme, funId->lexeme);

    tempIn = funId->down->down;
    tempOut = funId->down->left->down;
    tempVar = funId->down->left->left;


    printTreeNode(tempIn);

    // filling inputs
    while(tempIn!=NULL)
    {
        dLink dinp = createData();

        cpyLex(dinp->lexName, tempIn->lexeme);
        printf("printing tempin\n");
        printTreeNode(tempIn);
        cpyLex(dinp->lexType, tempIn->down->lexeme);
        printTreeNode(tempIn->down);

        printf("printing tempin->down\n");
        printLex(tempIn->down->lexeme);


        if(tab->func[nFunc]->inp == NULL){
            tab->func[nFunc]->inp = dinp;
            //printf("inserting...\n");
            //printDNode(dinp);
        }

        else{
            while(tab->func[nFunc]->inp->next != NULL)
                tab->func[nFunc]->inp = tab->func[nFunc]->inp->next;

            //printf("inserting...\n");
            //printDNode(dinp);

            tab->func[nFunc]->inp->next = dinp;
        }
        tempIn=tempIn->left;
    }

    printSymTable(tab);


    while(tempOut!=NULL)
    {
        dLink outVars = createData();

        cpyLex(outVars->lexName,tempOut->lexeme);
        cpyLex(outVars->lexType,tempOut->down->lexeme);

        if(tab->func[nFunc]->out==NULL)
            tab->func[nFunc]->out=outVars;

        else
        {
            while(tab->func[nFunc]->out->next!=NULL)
                tab->func[nFunc]->out=tab->func[nFunc]->out->next;
            tab->func[nFunc]->out->next=outVars;
        }
        tempOut=tempOut->left;
    }
    //printSymTable(tab);
    getStmt(tab,tempVar,nFunc);
}

void getSymtable(symLink s, parseTree ast)
{
    printf("inside get table!\n");
    parseTree temp = ast;
    temp = temp->down->down;
    // for functions
    while(temp != NULL){
        insertFunc(s, ast);
        s->nFunc++;
        temp = temp->left;
    }
    // for main function
    //insertFunc(s, ast->down->left);
}
