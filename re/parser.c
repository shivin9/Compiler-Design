/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/


#include "parserDef.h"
#include <string.h>

//----------------------------------------SUPPORT FUNCTIONS----------------------------------------
nodeLink getNode(){
    nodeLink new = (nodeLink) malloc(sizeof(cell));
    new -> row = 0;
    new -> col = 0;
    new -> rule = 0;
    new -> next = NULL;
    return new;
}

tableLink initializeTable(){
    tableLink new = (tableLink) malloc(sizeof(table));
    new -> size = 0;
    new -> head = getNode();
    return new;
}

void addNewNode(tableLink tabl, int row, int col, int rule){
    nodeLink head = tabl->head;
    tabl->size++;
    if(head == NULL){
        tabl -> head = getNode();
        tabl -> head -> row = row;
        tabl -> head -> col = col;
        tabl -> head -> rule = rule;
        return;
    }
    if(findInTable(tabl, row, col) != -1)
        return;
    while(head -> next != NULL){
        head = head->next;
    }
    head -> next = getNode();
    head -> row = row;
    head -> col = col;
    head -> rule = rule;
}

int findInTable(tableLink head1, int row, int col){
    nodeLink head = head1->head;
    while(head->next != NULL){
        if(head->row == row && head->col == col)
            return head->rule;
        head = head->next;
    }
    if(head->row == row && head->col == col)
        return head->rule;
    return -1;
}

int find(char* term){
    int i;
    for(i = 0; i <113; i++){
        if(!strcmp(terms[i], term))
            break;
    }
    return i;
}

int epsInFirst(int alpha, int first[][11]){
    int i = 0;
    for(i; i < 11; i++){
        if(first[alpha][i] == 110)
            return 1;
    }
    return 0;
}

int dollarInFollow(int A, int follow[][12]){
    int i;
    for(i = 0; i < 12; i++){
        if(follow[A][i] == 111)
            return 1;
    }
    return 0;
}

void printGrammar(int G[][10],int size){
    int i, j;
    for(i = 0; i < size; i++){
        for(j = 0; j < 10; j++){
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

void printTable(tableLink tabl){
    nodeLink head1 = tabl->head;
    while(head1->next != NULL){
        printf("[%s, %s] -> %d\n", terms[head1->row], terms[head1->col + 48], head1->rule);
        head1 = head1->next;
    }
}

//--------------------------------------PARSE TREE AND STACK FUNCTIONS----------------------------

parseTree create(){
    parseTree head=(parseTree)malloc(sizeof(Node));
    head->up=NULL;
    head->val=0;
    head->visit=0;
    head->left=NULL;
    head->down=NULL;
    lex lexeme = NULL;
    return head;
}

int push(int stack[],int top,int rule,int gra[][10])
{
    int *a=gra[rule],i=1,j;
    while(a[i]!=-1 && i<9)
        i++;
    //printf("before push: %s\n",terms[stack[top]]);
    if(a[i-1]==110)
        return top;
    for(j=i-1;j>0;j--)
    {
        top++;
        stack[top]=a[j];

    }
    //printf("after push: %s\n",terms[stack[top]]);
    return top;
}
int pop(int stack[],int top)
{
    //printf("popping : %s\n",terms[stack[top]]);
    stack[top]=-1;
    --top;
    //printf("new top %s\n",terms[stack[top]]);
    return top;
}

parseTree search(parseTree start, int a)
{
    parseTree temp;
    if(start==NULL)
        return NULL;
    else if((start->val==a)&&(start->visit==0))
        return start;
    else if((temp=search(start->down, a))!=NULL)
        return temp;
    else if((temp=search(start->left, a))!=NULL)
        return temp;
    else
        return NULL;
}

void insert(parseTree temp, int rule,int gra[][10], lex lexem)
{
    int *a=gra[rule], i = 1;
    parseTree temp1,temp2,right;

    while(a[i]!=-1 && i<10)
    {
        temp1 = (parseTree) malloc(sizeof(Node));
        temp1->lexeme = (lex) malloc(sizeof(tokenInfo));
        temp1->val=a[i];
        if(a[i]>48)
            temp1->visit=1;
        else
            temp1->visit=0;
        temp1->left=NULL;
        temp1->down=NULL;
        temp1->up=temp;
        temp1->lexeme = lexem;
        if(temp->down==NULL)
        {
            temp->down=temp1;
        }
        else
        {

            temp2=temp->down;
            while(temp2!=NULL)
            {
                right=temp2;
                temp2=temp2->left;
            }
            right->left=temp1;
        }
        i++;
    }
}

void printStack(int a[],int top)
{
    int i=top;
    printf("***************\n");
    for(i;i>=0;i--)
        printf("%s\n",terms[a[i]]);
    printf("***************\n");

}

//-------------------------------------------MAIN FUNCTIONS--------------------------------------

parseTree parseInputSourceCode(parseTree head, FILE *fp, lexChain ch)
{
    int stack[256],top=1,i=2;
    stack[0]=111;
    stack[1]=0;
    for(i;i<256;i++)
        stack[i]=-1;

    int gra[85][10] = {{0,2,1,-1},{1,62,11,57,-1},
        {2,3,2,-1},{2,110,-1},{3,54,4,5,81,11,57,-1},
        {4,66,64,65,79,6,80,-1},{5,67,64,65,79,6,80,-1},
        {5,110,-1},{6,7,51,10,-1},{7,8,-1},{7,9,-1},{8,59,-1},{8,60,-1},{9,76,102,-1},
        {10,91,6,-1},{10,110,-1},{11,12,17,20,44,-1},{12,13,12,-1},
        {12,110,-1},{13,76,102,14,77,81,-1},
        {14,15,15,16,-1},{15,61,8,82,50,81,-1},
        {16,15,16,-1},{16,110,-1},{17,18,17,-1},
        {17,110,-1},{18,61,7,82,51,19,81,-1},
        {19,82,63,-1},{19,110,-1},{20,21,20,-1},{20,110,-1},
        {21,22,-1},{21,28,-1},{21,29,-1},{21,31,-1},
        {21,25,-1},{22,23,48,33,81,-1},
        {23,51,24,-1},{24,83,50,-1},{24,110,-1},{25,26,75,54,55,56,27,81,-1},
        {26,79,46,80,48,-1},{26,110,-1},{27,79,46,80,-1},
        {28,58,84,40,85,21,20,68,-1},{29,69,84,40,85,70,21,20,30,-1},
        {30,78,21,20,71,-1},{30,71,-1},{31,72,84,23,85,81,-1},
        {31,73,84,32,85,81,-1},{32,23,-1},{32,52,-1},
        {32,53,-1},{33,35,34,-1},{34,39,35,34,-1},{34,110,-1},{35,37,36,-1},
        {36,38,37,36,-1},{36,110,-1},{37,84,33,85,-1},
        {37,32,-1},{38,88,-1},{38,89,-1},{39,86,-1},
        {39,87,-1},{40,84,40,85,42,84,40,85,-1},
        {40,41,43,41,-1},{40,92,84,40,85,-1},
        {41,51,-1},{41,52,-1},{41,53,-1},{42,93,-1},
        {42,94,-1},{43,99,-1},{43,98,-1},{43,95,-1},
        {43,97,-1},{43,96,-1},{43,101,-1},{44,74,45,81,-1},
        {45,79,46,80,-1},{45,110,-1},{46,51,47,-1},
        {47,91,46,-1},{47,110,-1}};

    tableLink tab = initializeTable();
    createParseTable(gra, tab);


    char *tok;  // for storing token
    int t_val,curr=0;  // token value and incrementing pointer in the input file
    int rule, flag = 0;         // for storing rule number
    parseTree temp;       // for storing the pointer of the position where data has to be stored
    // printf("1\n");
    lex next;
    do  //looping through whole file
    {
        next = getNextToken(fp, curr, ch);
        if(next==NULL)
            break;
        tok = next->token;
        //printf("%s\n",tok);
        while(!strcmp(tok,"TK_COMMENT"))
        {
            curr++;
            next = getNextToken(fp, curr, ch);
            tok = next->token;
            // printf("%s\n",tok);
        }
        t_val = find(tok);
        if(!strcmp(terms[stack[top]],tok))
        {
            curr++;
            top=pop(stack,top);
        }
        else
        {
            //printf("1\n");
            rule = findInTable(tab, stack[top], t_val - 48);
            //printf("rule :%d\n",rule);
            if(rule==-1 && stack[top] >= 48){
                printf("error in line %d, wrong term '%s'\n", next->line, terms[t_val]);
                top = pop(stack, top);
                if(top == -1){
                    printf("beyond repair code... exiting\n");
                    exit(0);
                }
                flag = 1;
            }
            else if(head->down==NULL)
            {
                insert(head,rule,gra, next);
            }
            else
            {
                if(stack[top]<48)
                {
                    // printf("Stack top: %d\n",stack[top]);
                    temp=search(head,stack[top]);
                    // printf("temp value : %d\n",temp->val);
                    if(temp==NULL)
                    {
                        printf("Error\n") ;
                        flag = 1;
                        break;
                    }
                    else
                    {
                        temp->visit=1;
                        insert(temp,rule,gra,next);
                    }
                }
            }
            top=pop(stack,top);
            top=push(stack,top,rule,gra);
        }

    }while(top != 111);
    if(flag)
        printf("CODE IS SYNTACTICALLY INCORRECTLY\n");

    else
        printf("CODE IS SYNTACTICALLY CORRECT\n\n");
    return head;
}

void createParseTable(int G[][10], tableLink tabl){
    int first[48][11] = {{54,62,-1},{62,-1},{54,110,-1},{54,-1},
        {66,-1},{67,110,-1},{59,60,76,-1},{59,60,76,-1},
        {59,60,-1},{76,-1},{91,110,-1},
        {76,61,51,58,69,72,73,79,75,74,-1},
        {76,110,-1},{76,-1},{61,-1},{61,-1},{61,110,-1},
        {61,110,-1},{61,-1},{82,110,-1},
        {51,58,69,72,73,79,75,110,-1},
        {51,58,69,72,73,79,75,-1},
        {51,-1},{51,-1},{83,110,-1},
        {79,75,-1},{79,110,-1},
        {79,-1},{58,-1},{69,-1},{78,71,-1},
        {72,73,-1},{51,52,53,-1},
        {84,51,52,53,-1},{86,87,110,-1},
        {84,51,52,53,-1},{88,89,110,-1},
        {84,51,52,53,-1},{88,89,-1},
        {86,87,-1},{84,51,52,53,107,-1},
        {51,52,53,-1},{93,94,-1},
        {99,98,95,97,96,101,-1},
        {74,-1},{79,110,-1},{51,-1},{91,110}};

    int follow[48][12] = {{111,-1},{111,-1},{62,-1},{54,62,-1},
        {67,81,-1},{81,-1},{80,-1},{51,82,-1},{51,82,-1},
        {51,82,-1},{80,-1},{57,-1},{61,51,58,69,72,73,79,75,74,-1},
        {76,61,51,58,69,72,73,79,75,74,-1},
        {77,-1},{61,77,-1},{77,-1},{51,58,69,72,73,79,75,74,-1},
        {61,51,58,69,72,73,79,75,74,-1},{81,-1},{74,68,78,71,-1},
        {51,58,69,72,73,79,75,74,68,78,71,-1},
        {51,58,69,72,73,79,75,74,68,78,71,-1},
        {48,85,88,89,86,87,81,-1},{48,85,88,89,86,87,81,-1},
        {51,58,69,72,73,79,75,74,68,78,71,-1},
        {75,-1},{81,-1},{51,58,69,72,73,79,75,74,68,78,71,-1},
        {51,58,69,72,73,79,75,74,68,78,71,-1},
        {51,58,69,72,73,79,75,74,68,78,71,-1},
        {51,58,69,72,73,79,75,74,68,78,71,-1},
        {85,88,89,86,87,81,-1},{81,85,-1},{81,85,-1},{86,87,81,85,-1},
        {86,87,81,85,-1},{88,89,86,87,81,85,-1},
        {84,51,52,53,-1},{84,51,52,53,-1},{85,-1},{99,98,95,97,96,101,-1},
        {84,-1},{51,52,53,-1},{57,-1},{81,-1},{80,-1},{80}};

    int i, j;
    int rule, termfirst, right, alpha, foll, A, a, b, flag, zero;
    //for each rule starting from 1st rule ie. G[0], right is terminal of non-terminal
    for(rule = 0; rule < 85; rule++){
        flag = 0;
        //for every prod. A->alpha of grammar
        A = G[rule][0];

        for(right = 1; right < 10; right++){
            alpha = G[rule][right];
            //printf("alpha == %d", alpha);
            if(alpha == 110){
                //printf("first if A = %s, a = %s\n", terms[A], terms[a]);
                flag = 1;
                break;
            }

            if(alpha >= 48){
                addNewNode(tabl, A, alpha-48, rule);
                break;
            }
            for(termfirst = 0; termfirst < 11; termfirst++){
                a = first[alpha][termfirst];
                if (a >= 48 && alpha != 0 && a!=110){
                    addNewNode(tabl, A, a - 48, rule);
                    //printf("A = %s, a = %s\n", terms[A], terms[a]);
                }
            }
            //printf("eps in first(alpha) G[rule][right+1] = %d\n", G[rule][right+1]);

            if(!epsInFirst(alpha, first))
                break;
            else if(epsInFirst(alpha, first))
                printf(" ");
            else if(epsInFirst(alpha, first) && G[rule][right+1] == -1){
                flag = 1;
                break;
            }
        }
        // first(alpha) contains eps
        if(flag == 1){
            //printf("eps in first(alpha)\n");
            for(foll = 0; foll < 12; foll++){
                b = follow[A][foll];
                if(b>=48){
                    //printf("A = %s, b = %s\n", terms[A], terms[b]);
                    addNewNode(tabl, A, b - 48, rule);
                }
            }
            if(dollarInFollow(A, follow)){
                //printf("adding $\n");
                addNewNode(tabl, A, 111 - 48, rule);
                //tabl[A][113] = rule;
            }
        }
    }
}

void printTree(parseTree head)
{
    if((head==NULL)||(head->val==110))
        return;

    char* up = (char*) malloc(30*sizeof(char));
    char* lexcurrnode = (char*) malloc(30*sizeof(char));
    char* numval = (char*) malloc(30*sizeof(char));
    char* isleaf = (char*) malloc(30*sizeof(char));
    char* symbol = (char*) malloc(30*sizeof(char));
    char* tok = (char*) malloc(30*sizeof(char));

    strcpy(tok, terms[head->val]);
    //printf("inside print!\n");
    if(head->up != NULL)
        strcpy(up, terms[head->up->val]);
    else
        strcpy(up, "root");

    if(head->val >= 48){
        strcpy(lexcurrnode, head->lexeme->value);
        strcpy(isleaf, "yes");
        strcpy(symbol, "-----");
    }
    else{
        strcpy(lexcurrnode, "-----");
        strcpy(isleaf, "no");
        strcpy(symbol, terms[head->val]);
    }

    if(head->val == 105 || head->val == 106)
        strcpy(numval, terms[head->val]);
    else
        strcpy(numval, "-----");

    //int line = head->lexeme->line;
    //printf("copied everything... line= %d\n", line);

    printf("%s, %d, %s, %s, %s, %s, %s\n",lexcurrnode, -1, tok, numval, up, isleaf, symbol);
    printTree(head->down);
    printTree(head->left);
}