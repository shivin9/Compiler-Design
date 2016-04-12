#include "symData.h"

dLink createData()
{
    dLink tab=(dLink)malloc(sizeof(dNode));
    tab->lexName=(char*) malloc(30*sizeof(char));
    tab->lexType=(char*) malloc(30*sizeof(char));
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
    printf("in create sym\n");
    int i;
    symLink tab=(symLink)malloc(sizeof(symBox));
    for(i=0;i<10;i++){
        printf("in loop\n");
        tab->func[i]=createFunc();
    }
    tab->glo=NULL;
    tab->nFunc=0;
    printf("returning tab!\n");
    return tab;
}

void cpyLex(lex d,lex l)
{
    strcpy(d->token,l->token);
    strcpy(d->value,l->value);
    d->line=l->line;
}


// linked list of dLinks
// void getTypeDef(symLink tab,parseTree typeDef,int nFunc)
// {


// }

// linked list of int/real
void getDec(symLink tab,parseTree declarations,int nFunc)
{
    parseTree dec=declarations;
    while(dec!=NULL)
    {
        dLink d=(dLink)malloc(sizeof(dNode));
        cpyLex(d->lexName,dec->lexeme);
        cpyLex(d->lexType,dec->down->lexeme);
        if((dec->down->left)!=NULL)
        {
            dLink g=tab->glo;
            if(tab->glo==NULL)
                tab->glo=d;
            else
            {
                while(g->next!=NULL)
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

// returns the final dlinks under stmts
void getStmt(symLink tab,parseTree stmts,int nFunc){
    //getTypeDef(tab,stmts->down,nFunc);
    getDec(tab,stmts->down->left,nFunc);

}

// filling function in symbol table
void insertFunc(symLink tab,parseTree funId)
{
    int nFunc = tab->nFunc;
    tab->func[nFunc]->lexeme=(lex)malloc(sizeof(tokenInfo));
    tab->func[nFunc]->lexeme->token = (char*) malloc(30*sizeof(char));
    tab->func[nFunc]->lexeme->value = (char*) malloc(30*sizeof(char));
    strcpy(tab->func[nFunc]->lexeme->token, funId->lexeme->token);
    strcpy(tab->func[nFunc]->lexeme->value, funId->lexeme->value);
    tab->func[nFunc]->lexeme->line = funId->lexeme->line;

    printf("inside insertFunc\n");
    parseTree tempIn,tempOut,tempVar;
    tempIn=funId->down;
    tempOut=tempIn->left;
    // tempVar = stmts
    tempVar=tempOut->left;
    while(tempIn!=NULL)
    {
        dLink d=(dLink)malloc(sizeof(dNode));
        cpyLex(d->lexName,tempIn->lexeme);
        cpyLex(d->lexType,tempIn->down->lexeme);
        if(tab->func[nFunc]->inp==NULL)
            tab->func[nFunc]->inp=d;
        else{
            while(tab->func[nFunc]->inp->next!=NULL)
                tab->func[nFunc]->inp=tab->func[nFunc]->inp->next;
            tab->func[nFunc]->inp->next=d;
        }
        tempIn=tempIn->left;

    }
    while(tempOut!=NULL)
    {
        dLink outVars=(dLink)malloc(sizeof(dNode));
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

    getStmt(tab,tempVar,nFunc);
}

void getSymtable(symLink s, parseTree ast)
{
    printf("inside get table!\n");
    parseTree temp = ast;
    temp = temp->down->down;
    while(temp != NULL){
        insertFunc(s, temp);
        temp = temp->left;
    }
    insertFunc(s, ast->down->left);
}
