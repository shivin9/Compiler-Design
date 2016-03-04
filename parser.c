#include "parser_dat.h"

tableLink initializeTable(){
    tableLink new = (tableLink) malloc(sizeof(table));
    new -> size = 0;
    new -> head = NULL;
    return new;
}

nodeLink getNode(){
    nodeLink new = (nodeLink) malloc(sizeof(cell));
    new -> row = 0;
    new -> col = 0;
    new -> rule = 0;
    new -> next = NULL;
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
    for(i = 0; i <115; i++){
        if(!strcmp(terms[i], term))
            break;
    }
    return i;
}

// void clear(char* str){
//     int i;
//     for(i = 0; i < 30; i++)
//         str[i] = '\0';
// }

int epsInFirst(int alpha, int first[][11]){
    int i = 0;
    for(i; i < 11; i++){
        if(first[alpha][i] == 112)
            return 1;
    }
    return 0;
}

int dollarInFollow(int A, int follow[][15]){
    int i;
    for(i = 0; i < 15; i++){
        if(follow[A][i] == 113)
            return 1;
    }
    return 0;
}

void printGrammar(int G[][9],int size){
    int i, j;
    for(i = 0; i < size; i++){
        for(j = 0; j < 9; j++){
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

void printTable(tableLink tabl){
    nodeLink head1 = tabl->head;
    while(head1->next != NULL){
        printf("[%s, %s] -> %d\n", terms[head1->row], terms[head1->col + 50], head1->rule);
        head1 = head1->next;
    }
}

/*void printTable(int tabl[][75], int size){
  int i, j;
  for(i = 0; i < size; i++){
  for(j = 0; j < 75; j++){
  printf("%d ", tabl[i][j]);
  }
  printf("\n");
  }
  }*/

void createParseTable(int G[][9], tableLink tabl){
    int first[50][11] = {{112,56,64},
        {64},{112,56},
        {56},{68},{69,112},
        {61,62,78},{61,62,78},
        {61,62},{78},{93,112},
        {112,78,63,76,53,71,77,81,60,74,75},
        {112,78},{78},
        {63},{63},{112,63},
        {112,63},{63},
        {65,112},{112,53,71,77,81,60,74,75},
        {53,71,77,81,112,60,74,75},
        {53},{53},{85,112},{77,81,112},
        {81,112},{81},{60},
        {71},{80,73},{74,75},{104,53,54,55},
        {86,53,54,55,104},
        {112,88,89},{86,53,54,55,104},
        {112,90,91},{86,53,54,55,104},
        {90,91},{88,89},{53,54,55,104},
        {112,85},{86,109,53,54,55},
        {53,54,55},{95,96},{101,100,97,99,98,103},
        {76},{81,112},{53},{93,112}};

    int follow[50][15] = {{113},{113},{64},
        {56,64},{69},{83},{82},{84,53},
        {84,53},{84,53},{82},{59},{53,71,77,81,60,74,75,76,63},
        {78,53,71,77,81,60,74,75,76,63},
        {79},{63,79},{79},{53,71,77,81,60,74,75},
        {63,53,71,77,81,60,74,75},
        {83},{73,80,70,76},{53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {87,50},{87,50},{53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {77},{83},{53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {53,71,77,81,60,74,75,86,109,54,55,73,80,70,76},
        {87},{87,83},{87,83},{88,89,87,83},{88,89,87,83},{90,91,88,89,87,83},
        {86,53,54,55,104},{86,53,54,55,104},
        {90,91,88,89,87,83},{90,91,88,89,87,83},
        {87},{101,100,97,99,98,103,87},
        {86},{53,54,55},{59},{83},{82},{82}};

    int i, j;

    int rule, termfirst, right, alpha, foll, A, a, b, flag;
    //for each rule starting from 1st rule ie. G[0], right is terminal of non-terminal
    for(rule = 0; rule < 90; rule++){
        flag = 0;
        //for every prod. A->alpha of grammar
        A = G[rule][0];
        for(right = 0; right < 9; right++){
            alpha = G[rule][right];
            //printf("A = %s, alpha = %s\n", terms[A], terms[alpha]);
            for(termfirst = 0; termfirst < 11; termfirst++){
                a = first[alpha][termfirst];
                if (a >= 50){
                    //printf("printing...\n");
                    addNewNode(tabl, A, a-50, rule);
                    //printf("A = %s, a = %s\n", terms[A], terms[a]);
                }
            }

            if(!epsInFirst(alpha, first))
                break;

            if(epsInFirst(alpha, first))
                flag++;
        }
        // first(alpha) contains eps
        if(flag == 9){
            //printf("eps in first(alpha)\n");
            for(foll = 0; foll < 15; foll++){
                b = follow[A][foll];
                if(b >= 50){
                    //printf("inside...\n");
                    addNewNode(tabl, A, b - 50, rule);
                    //tabl[A][b - 50] = rule;
                }
            }
            if(dollarInFollow(A, follow)){
                printf("adding $\n");
                addNewNode(tabl, A, 113, rule);
                //tabl[A][113] = rule;
            }
        }
    }
    //int r = findInTable(tabl, 0, 60);
    //printTable(tabl);
    //printf("rule at 0,60 = %d", r);
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

//this used to create the head Node

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

int push(int stack[],int top,int rule,grammar gra)
{
    int *a=gra[rule],i=1,j;
    while(a[i]!=0&&i<10)
        i++;
    for(j=i-1;j>0;j--)
    {
        stack[top]=a[j];
        top++;
    }
    return top;
}
int pop(int stack[],int top)
{
    stack[top]=-1;
    return --top;
}

parseTree search(parseTree start, int a)
{
    parseTree temp;
    if(start==NULL)
        return NULL;
    else if((start->val==a)&&(start->visit==0))
        return start;
    else if((temp=search(start->down, a))!=0)
        return temp;
    else if((temp=search(start->left, a))!=0)
        return temp;
    else
        return NULL;
}

void insert(parseTree temp, int rule, grammar gra, lex lexem)
{
    int *a=gra[rule], i = 1;
    parseTree temp1,temp2,right;

    while(a[i]!=0&&i<10)
    {
        temp1=(parseTree)malloc(sizeof(Node));
        temp1->val=a[i];
        temp1->visit=0;
        temp1->left=NULL;
        temp1->down=NULL;
        temp1->up=temp;
        temp1->lexeme = lexem;
        if(temp->down==NULL)
            temp->down==temp1;
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

parseTree parseInputSourceCode(parseTree head, int stack[], int top, FILE *fp, tableLink tab, grammar gra, lexChain ch)
{
    char *tok;  // for storing token
    int t_val,curr=0;  // token value and incrementing pointer in the input file
    int rule;         // for storing rule number
    parseTree temp;       // for storing the pointer of the position where data has to be stored

    lex next;
    while(top!=0)                       //looping through whole file
    {

        next = getNextToken(fp, curr, ch);
        tok = next->token;
        t_val = find(tok);
        if(t_val==stack[top])
        {
            top=pop(stack,top);
            //curr++;
        }
        else
        {
            rule = findInTable(tab, stack[top], t_val - 50);
            if(head->down==NULL)
                insert(head,rule,gra, next);
            else
            {
                temp=search(head,stack[top]);
                if(temp==NULL)
                {
                    printf("Error\n");
                    break;
                }
                else
                {
                    temp->visit=1;
                    insert(temp,rule,gra,next);
                }
            }
            top=pop(stack,top);
            top=push(stack,top,rule,gra);

        }
        curr++;
    }
    return head;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

//parseTree  parseInputSourceCode(char *testcaseFile, table T);
//void printParseTree(parseTree  PT, char *outfile);

int main(){
    int gra[90][9] = {{0,2,1},
        {1,64,11,59},{2,3,2},{2,112},{3,56,4,5,83,11,59},
        {4,68,66,67,81,6,82},{5,69,66,67,81,6,82},
        {5,112},{6,7,53,10},{7,8},{7,9},{8,61},{8,62},
        {9,78,104},{10,93,6},{10,112},{11,12,17,20,46},
        {12,13,12},{12,112},{13,78,104,14,79,83},
        {14,15,15,16},{15,63,8,84,52,83},
        {16,15,16},{16,112},{17,18,17},{17,112},
        {18,63,7,84,53,84,53,19,83},
        {19,84,65},{19,112},{20,21,20},{20,112},
        {21,22},{21,28},{21,29},{21,31},
        {21,25},{22,23,50,33,83},{23,53,24},{24,85,52},
        {24,112},{25,26,77,56,57,58,27,83},
        {26,81,48,82,50},{26,112},{27,81,48,82},
        {28,60,86,42,87,21,20,70},
        {29,71,86,42,87,72,21,20,30},
        {30,80,21,20,73},{30,73},{31,74,86,23,87,83},
        {31,75,86,32,87,83},{32,43},{32,104,85,52},
        {33,35,34},{34,39,35,34},
        {34,112},{35,37,36},{36,38,37,36},
        {36,112},{37,86,33,87},{37,40},{38,90},
        {38,91},{39,88},{39,89},{40,53},
        {40,54},{40,55},{40,104,41},{41,112},{41,85,52},
        {42,86,42,87,44,86,42,87},{42,43,45,43},
        {42,109,42},{43,53},{43,54},{43,55},{44,95},
        {44,96},{45,101},{45,100},{45,97},
        {45,99},{45,98},{45,103},{46,76,47,83},
        {47,81,48,82},{47,112},{48,53,49},
        {49,93,48},{49,112}};

    parseTree headT;
    headT=create();

    FILE* fp = fopen("testcase1.txt", "r");
    if(fp==NULL)
    {
        printf("File not found\n");
        return NULL;
    }
    tableLink tabl = initializeTable();
    createParseTable(gra, tabl);

    lexChain ch = getAllTokens(fp);

    //printGrammar(gra,90);
    return 0;
}
