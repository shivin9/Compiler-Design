/*
   BATCH NUMBER - 66
   SHIVIN SRIVASTAVA - 2013A7PS073P
   UPADHYAY GAURAV ARVIND - 2013A7PS030P
   */

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

// to search a variable in the symbol table
int searchTable(symLink tab, char* name, char* func){
    int i = 0;

    // find the corresponding entry for that function
    while(strcmp(tab->func[i]->lexeme->value, func)){
        i++;
        if(i > tab->nFunc){
            return -1;
        }
    }

    dLink function = tab->func[i]->var;
    dLink glob = tab->glo;
    int pres = 0;

    // only when both are 1, loop will terminate
    while(function != NULL && strcmp(function->lexName-> value, name)){
        function = function->next;
        if(function == NULL){
            pres = 0;
            break;
        }
    }
    if(!pres){
        if(glob == NULL)
            return 0;
        while(strcmp(glob->lexName->value, name)){
            glob = glob->next;
            if(glob == NULL){
                return 0;
            }
        }
    }
    return 1;
}

// gets the type of variable given the name
lex getType(symLink tab, char* name, char* func){
    int i = 0;

    // find the corresponding entry for that function
    while(strcmp(tab->func[i]->lexeme->value, func)){
        i++;
        if(i > tab->nFunc){
            return NULL;
        }
    }

    dLink glob = tab->glo;
    dLink varlist = tab->func[i]->var;
    int pres, cnt = 0;
    // no var in function

    while(cnt < 3){
        pres = 1;
        if(cnt == 1)
            varlist = tab->func[i]->inp;

        else if(cnt == 2)
            varlist = tab->func[i]->out;

        if(varlist == NULL)
            pres = 0;

        // variable is int/float type
        // only when both are 1, loop will terminate

        while(varlist != NULL && (strcmp(varlist->lexName->value, name))){
            varlist = varlist->next;
            if(varlist == NULL){
                pres = 0;
                break;
            }
        }
        if(pres)
            return varlist->lexType;
        cnt++;
    }

    if(!pres){

        if(glob == NULL)
            return NULL;

        while(strcmp(glob->lexName->value, name)){
            glob = glob->next;
            if(glob == NULL){
                return NULL;
            }
        }
    }
    return glob->lexType;
}

int isPresent(symLink tab, char* name){
    int i = 0;

    // NULL ==> variable is not present in the table
    while(getType(tab, name, tab->func[i]->lexeme->value) == NULL){
        if(tab->func[i]->lexeme == NULL || i == tab->nFunc)
            return 0;
        i++;
    }
    if(i == tab->nFunc+1)
        // variable is present in the table
        return 1;
}

int isGlobal(symLink tab, char* name){
    dLink glob = tab->glo;
    if(glob == NULL)
        return 0;

    while(strcmp(glob->lexName->value, name)){
        glob = glob->next;
        if(glob == NULL){
            return 0;
        }
    }
    return 1;
}

// linked list of int/real
void getDec(symLink tab, parseTree declarations, int nFunc)
{
    parseTree dec = declarations->down;
    while(dec != NULL){
        dLink dvar = createData();
        cpyLex(dvar->lexName,dec->lexeme);

        if(dec->down != NULL)
            cpyLex(dvar->lexType,dec->down->lexeme);

        lex type1 = getType(tab, dvar->lexName->value,tab->func[nFunc]->lexeme->value);
        // to check whether a variable is being reinitialized
        //printLex();
        if(type1 != NULL){
            printf("line %d: variable <%s> of type <%s> already declared\n", dec->line, dvar->lexName->value, dvar->lexType->value);
        }

        else if((dec->down->left)!=NULL)
        {
            dLink g = tab->glo;
            if(tab->glo == NULL)
                tab->glo=dvar;
            else
            {
                while(g->next != NULL){
                    if(!isGlobal(tab, dvar->lexName->value)){
                        g=g->next;
                        g->next=dvar;
                    }
                    else
                        g = g->next;
                }
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

void printDNode(dLink dlk, char* funcName){
    if(dlk == NULL)
        return;
    else{
        if(dlk->down == NULL){
            printf("%s                  ", dlk->lexName->value);
            printf("%s                  ", dlk->lexType->value);
            printf("%s                  ", funcName);
            printf("%d\n", dlk->offset);

        }
        //printDNode(dlk->down, funcName);
        printDNode(dlk->next, funcName);
    }
}

void printFunBox(funcLink flink){
    if(flink == NULL)
        return;
    else{
        printDNode(flink->inp, flink->lexeme->value);
        printDNode(flink->var, flink->lexeme->value);
        printDNode(flink->out, flink->lexeme->value);
    }
}

void printSymTable(symLink tab){
    printf("\n\nLexeme              type                scope                offset\n");
    int i;
    for(i = 0; i < tab->nFunc + 1; i++){
        printFunBox(tab->func[i]);
    }
    printDNode(tab->glo, "global");
}

void insertDown(dLink rec, dLink recSub)
{
    dLink temp,prev;
    temp=rec;
    prev=temp;
    if(temp->down==NULL)
        temp->down = recSub;
    else{
        while(temp!=NULL)
        {

            if(!strcmp(temp->lexName,recSub->lexName))
            {
                printf("line %d: Same Variable Name <%s> in Record\n", temp->lexName->line, temp->lexName->value);
            }
            prev=temp;
            temp=temp->down;
        }
        prev->down=recSub;
    }
}

void insertGlo(symLink tab,dLink dRec)
{
    dLink prev,temp=tab->glo;

    prev=temp;
    if(temp==NULL)
        tab->glo=dRec;
    else{
        while(temp!=NULL)
        {
            if(!strcmp(temp->lexName,dRec->lexName))
            {
                printf("Same Record or global Name <%s> in the global variable\n", temp->lexName->value);
            }
            prev=temp;
            temp=temp->next;
        }
        prev->next=dRec;
    }
}
void getTypeDef(symLink tab, parseTree typed)
{
    parseTree tempRec=typed;
    if(typed==NULL);
    else
    {
        tempRec=tempRec->down;
        dLink dRec= createData();
        dRec->rec=1;
        //printf("tempRec = ");
        //printTreeNode(tempRec);
        cpyLex(dRec->lexName,tempRec->lexeme);
        strcpy(dRec->lexType->value, dRec->lexType->value);
        tempRec=tempRec->left->down;
        //printLex(tempRec->lexeme);
        int i=0;
        while(tempRec != NULL)
        {
            //printLex(tempRec->lexeme);
            dLink dRecSub= createData();
            cpyLex(dRecSub->lexType,tempRec->down->lexeme);
            cpyLex(dRecSub->lexName,tempRec->down->left->lexeme);
            //printf("tempRec->down = ");
            // printLex(tempRec->down->lexeme);
            // printLex(tempRec->down->left->lexeme);
            insertDown(dRec,dRecSub);
            tempRec=tempRec->left;
            //printLex(tempRec->lexeme);
            i++;
            if(i>=2)
            {
                tempRec=tempRec->down;
                //  printf("Checking inside if\n");
                // printLex(tempRec->lexeme);
            }
        }
        insertGlo(tab,dRec);
        getTypeDef(tab,typed->left->down);
    }
}

void getStmt(symLink tab, parseTree stmts,int nFunc){
    getDec(tab,stmts->down->left,nFunc);

    //printLex(stmts->down->left);
    getTypeDef(tab,stmts->down->down);
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
        cpyLex(dinp->lexType, tempIn->down->lexeme);

        // handling the first case separately
        if(tab->func[nFunc]->inp == NULL){
            tab->func[nFunc]->inp = dinp;
        }

        else{
            dLink temp = tab->func[nFunc]->inp;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = dinp;
        }
        tempIn=tempIn->left;
    }

    while(tempOut!=NULL)
    {
        dLink outVars = createData();

        cpyLex(outVars->lexName,tempOut->lexeme);
        cpyLex(outVars->lexType,tempOut->down->lexeme);
        if(tab->func[nFunc]->out==NULL){
            tab->func[nFunc]->out=outVars;
        }

        else{
            dLink temp = tab->func[nFunc]->out;

            while(temp->next != NULL)
                temp = temp->next;

            temp->next = outVars;
        }
        tempOut=tempOut->down->left;
    }
    getStmt(tab,tempVar,nFunc);
}

void getSymtable(symLink s, parseTree ast)
{
    parseTree temp = ast;
    temp = temp->down->down;

    // for functions
    while(temp != NULL){
        insertFunc(s, temp);
        s->nFunc++;
        temp = temp->left;
    }
    // inserting main function
    insertFunc(s, ast->down->left);
}
