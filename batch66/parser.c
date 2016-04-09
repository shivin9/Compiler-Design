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

// returns the pointer to the required node
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

void insert(parseTree temp, int rule, int gra[][10], lex lexem)
{
    int *a = gra[rule], i = 1;
    parseTree temp1,temp2,right;

    // for all terminals and non-terminals in the rule
    while(a[i]!=-1 && i<10)
    {
        // new node to be inserted
        temp1 = (parseTree) malloc(sizeof(Node));
        temp1->lexeme = (lex) malloc(sizeof(tokenInfo));
        temp1->val = a[i];

        // to tell if the node is a leaf or not
        if(a[i]>48)
            temp1->visit = 1;
        else
            temp1->visit = 0;

        temp1->left = NULL;
        temp1->down = NULL;
        temp1->prev = NULL;
        //printf("token = %s, value = %s, line = %d \n", lexem->token, lexem->value, lexem->line);

        // new node is definitely the child of temp
        temp1->up = temp;
        //if(!strcmp(terms[a[i]], lexem->token)){
        temp1->lexeme = lexem;
        //}

        // else{
        //     lex new = getNewlex();
        //     printf("copied to value %s\n", terms[a[i]]);
        //     if(new == NULL){
        //         printf("new lex is null\n");
        //     }
        //     strcpy(new->value, terms[a[i]]);
        //     printf("copied to value %s\n", terms[a[i]]);
        //     strcpy(new->token, keywordsFieldId(terms[a[i]]));
        //     temp1->lexeme = new;
        // }

        temp1->line = lexem->line;

        // insert at temp only
        if(temp->down==NULL)
            temp->down = temp1;

        // finding a child which has no down pointer by traversing through the list of children
        else
        {
            temp2=temp->down;
            while(temp2!=NULL)
            {
                right = temp2;
                temp2 = temp2->left;
            }
            // set the left child to temp1
            right->left = temp1;
            temp1->prev = right;
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
    lex next;

    do  //looping through whole file
    {
        next = getNextToken(fp, curr, ch);

        if(next==NULL)
            break;

        tok = next->token;
        while(!strcmp(tok,"TK_COMMENT")){
            curr++;
            next = getNextToken(fp, curr, ch);
            tok = next->token;
        }
        t_val = find(tok);
        if(!strcmp(terms[stack[top]], tok))
        {
            curr++;
            top=pop(stack,top);
        }
        else
        {
            rule = findInTable(tab, stack[top], t_val - 48);
            if(rule==-1 && stack[top] >= 48){
                printf("error in line %d, wrong term '%s'\n", next->line, terms[t_val]);
                top = pop(stack, top);
                if(top == -1){
                    printf("remove the specified errors and compile again... exiting\n");
                    exit(0);
                }
                flag = 1;
            }

            else if(head->down==NULL)
                insert(head, rule, gra, next);

            else
            {
                if(stack[top] < 48)
                {
                    // modifies temp to the requires node
                    temp = search(head, stack[top]);
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
    if((head==NULL)||(head->val==110)){
        //printf("head = NULL\n");
        return;
    }

    char* up = (char*) malloc(30*sizeof(char));
    char* prev = (char*) malloc(30*sizeof(char));
    char* lexcurrnode = (char*) malloc(30*sizeof(char));
    char* numval = (char*) malloc(30*sizeof(char));
    char* isleaf = (char*) malloc(30*sizeof(char));
    char* symbol = (char*) malloc(30*sizeof(char));
    char* tok = (char*) malloc(30*sizeof(char));

    strcpy(tok, terms[head->val]);
    if(head->up != NULL)
        strcpy(up, terms[head->up->val]);
    else
        strcpy(up, "root");

    if(head->val >= 48){
        strcpy(lexcurrnode, head->lexeme->value);
        //printf("%d", head->val);
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

    if(head->prev == NULL)
        strcpy(prev, "NULL");
    else
        strcpy(prev, terms[head->prev->val]);

    //int line = head->lexeme->line;
    //printf("copied everything... line= %d\n", line);

    printf("%s, %d, %s, %s, %s, %s, %s, p = %s\n",lexcurrnode, head->line, tok, numval, up, isleaf, symbol, prev);
    free(tok);
    free(symbol);
    free(lexcurrnode);
    free(numval);
    free(isleaf);
    free(up);

    printTree(head->down);
    printTree(head->left);
}

parseTree createAst(parseTree pTree){
    parseTree ast;
    ast = pTree;
    //printTree(ast);
    removePunc(ast, NULL);
    verifyPrev(ast, NULL);
    pullUpSingle(ast, NULL);
    verifyPrev(ast, NULL);
    fixFunId(ast);
    verifyPrev(ast, NULL);
    //printTree(ast);
    firstUp(ast);
    // terminals now have children
    return ast;
}

void verifyPrev(parseTree ast, parseTree prev){
    if(ast == NULL)
        return;
    else{
            ast->prev = prev;
            verifyPrev(ast->left, ast);
            verifyPrev(ast->down, NULL);
    }
}

void removePunc(parseTree ast, parseTree prev){
    if(ast == NULL)
        return;

    int tok_value = ast->val;
    if (tok_value < 48 && ast->down == NULL){
        printf("inside EPS rule\n");
        if(prev != NULL){
            prev->left = ast->left;
            ast->left->prev = prev;
            removePunc(ast->left, prev);
            free(ast);
        }
        else{
            if(ast->up != NULL)
                ast->up->down = ast->down;
            removePunc(ast->left, NULL);
        }
    }
    else if
       (tok_value == 55 || tok_value == 56 || tok_value == 57 || tok_value == 61 || tok_value == 64 ||
        tok_value == 65 || tok_value == 68 || tok_value == 71 || tok_value == 75 || tok_value == 76 ||
        tok_value == 77 || tok_value == 79 || tok_value == 80 || tok_value == 81 || tok_value == 82 ||
        tok_value == 83 || tok_value == 84 || tok_value == 85 || tok_value == 91){
        // ast is the left most child
        if(prev != NULL){
            prev->left = ast->left;
            if(ast->left != NULL)
                ast->left->prev = prev;
            free(ast);
            removePunc(ast->left, prev);
        }
        else{
            ast->up->down = ast->left;
            if(ast->left != NULL)
                ast->left->prev = prev;
            //ast->left->down = ast->down;
            removePunc(ast->left, NULL);
            free(ast);
        }
    }
    else{
            removePunc(ast->down, NULL);
            removePunc(ast->left, ast);
    }
}

// clean rules of type <stmt> ===> <assignmentStmt>
void pullUpSingle(parseTree ast, parseTree prev){
    if(ast == NULL)
        return;
    int tok_value = ast->val;

    if (tok_value == 7  || tok_value == 8  || tok_value == 9  || tok_value == 19 || tok_value == 21 || tok_value == 24 ||
        tok_value == 27 || tok_value == 32 || tok_value == 37 || tok_value == 38 || tok_value == 39 || tok_value == 41 ||
        tok_value == 42 || tok_value == 43 || tok_value == 44 || tok_value == 45 || tok_value == 46 || tok_value == 47){
        if(prev == NULL){
            ast->up->down = ast->down;
            ast->down->left = ast->left;
            ast->down->up = ast->up;
            if(ast->left != NULL)
                ast->left->prev = prev;
            pullUpSingle(ast->down, NULL);
            //pullUpSingle(ast->left, ast);
            free(ast);
        }
        else{
            prev->left = ast->down;
            ast->down->left = ast->left;
            ast->down->up = ast->up;
            if(ast->left != NULL)
                ast->left->prev = prev;
            //pullUpSingle(ast->down, NULL);
            pullUpSingle(ast->left, ast);
            free(ast);
        }
    }
    else{
            pullUpSingle(ast->down, NULL);
            pullUpSingle(ast->left, ast);
    }
}

/* fix rules of type

<input_par> ===> TK_INPUT TK_PARAMETER TK_LIST TK_SQL <parameter_list> TK_SQR
{<input_par>.ptr = newNode([makeLeaf("TK_INPUT", "input"), <parameter_list>.ptr])}

*/
void firstUp(parseTree ast){
    if (ast == NULL)
        return;
    int tok_value = ast->val;
    // all terminals... so ast->down == NULL
    // for rule <singleOrRecId> ===> TK_ID <new_24> involving TK_ID
    if ((tok_value == 51 && (ast->up->val == 23 || ast->up->val == 46)) || /*tok_value == 54 || tok_value == 58 ||*/
        (tok_value == 66 && ast->down == NULL) ||
        (tok_value == 67 && ast->down == NULL) /*|| tok_value == 69 || tok_value == 72 || tok_value == 73 ||
        tok_value == 74 || tok_value == 78 || tok_value == 92 || tok_value == 102*/){

        // ast->up is the left most child
        printf("firstup ast = %s\n", terms[ast->val]);
        if(ast->up->prev == NULL){
            printf("ast->up = %s\n", terms[ast->up->val]);

            if(ast->up->up != NULL)
                ast->up->up->down = ast;

            ast->down = ast->left;

            if(ast->down != NULL)
                ast->down->prev = NULL;

            ast->left = ast->up->left;

            if(ast->left != NULL)
                ast->left->prev = ast;

            parseTree tempUp = ast->up->up;
            free(ast->up);
            ast->up = tempUp;
            printf("firstUp ast->up = %s\n", terms[ast->up->val]);

            // change the up pointer of all the leaves
            parseTree temp = ast->down;
            while(temp != NULL){
                temp->up = ast;
                temp = temp->left;
            }
            printf("firstup ast->left = %s\n", terms[ast->left->val]);
            printf("firstup ast->down = %s\n", terms[ast->down->val]);

            firstUp(ast->left);
            firstUp(ast->down);
        }
        // ast->up lies somewhere in between
        else{
            printf("up in between ast = %s\n", terms[ast->up->val]);
            printf("prev in between ast = %s\n", terms[ast->up->prev->val]);

            ast->down = ast->left;
            if(ast->down != NULL)
                ast->down->prev = NULL;
            ast->left = ast->up->left;
            ast->prev = ast->up->prev;
            if(ast->left != NULL)
                ast->left->prev = ast;
            ast->up->prev->left = ast;
            parseTree tempUp = ast->up->up;
            free(ast->up);
            ast->up = tempUp;
            parseTree temp = ast->down;
            while(temp != NULL){
                temp->up = ast;
                temp = temp->left;
            }
            firstUp(ast->left);
        }
    }
    else{
        //printf("firstup else ast->down = %s\n", terms[ast->down->val]);
        //printf("firstup else ast->left = %s\n", terms[ast->left->val]);

        firstUp(ast->down);
        firstUp(ast->left);
    }
}

// void removeCondi(parseTree ast){
//     if (ast == NULL)
//         return;
//     int tok_value = ast->val;
//     // all terminals... so ast->down == NULL
//     if(/*tok_value == 54 ||*/ tok_value == 58 || /*tok_value == 66 || tok_value == 67 ||*/ tok_value == 69 || tok_value == 72 ||
//        tok_value == 73 || tok_value == 78 || tok_value == 92 || tok_value == 102){
//         printf("ast = %s\n", terms[ast->val]);
//         if(ast->up->prev == NULL){
//             ast->down = ast->left;
//             ast->left = ast->up->left;
//             if(ast->down != NULL)
//                 ast->down->prev = NULL;
//             ast->up->up->down = ast;
//             parseTree temp = ast->down;
//             ast->up = ast->up->up;
//             while(temp != NULL){
//                 temp->up = ast;
//                 temp = temp->left;
//             }
//             removeCondi(ast->left);
//             removeCondi(ast->down);
//         }
//         else{
//             ast->down = ast->left;
//             if(ast->down != NULL)
//                 ast->down->prev = NULL;
//             ast->left = ast->up->left;
//             ast->up->prev->left = ast;
//             ast->up = ast->up->up;
//             parseTree temp = ast->down;
//             while(temp != NULL){
//                 temp->up = ast;
//                 temp = temp->left;
//             }
//             removeCondi(ast->left);
//             removeCondi(ast->down);
//         }
//     }

//     else{
//             removeCondi(ast->down);
//             removeCondi(ast->left);
//         }
// }

void removeID(parseTree ast){
    if (ast == NULL)
        return;
    int tok_value = ast->val;
    // all terminals... so ast->down == NULL
    if(tok_value == 51 /*|| tok_value == 58 || /*tok_value == 66 || tok_value == 67 || tok_value == 69 || tok_value == 72 ||
       tok_value == 73 || tok_value == 78 ||  tok_value == 86 */|| tok_value == 48){
        printf("ast = %s\n", terms[ast->val]);
        // here ast->prev is never NULL, 46 because of idList rule, an  26 for funcallstmt
        if(ast->up->prev == NULL && ast->up->val != 23 && ast->up->val != 26 /*&& ast->up->val != 46*/){
            /*printf("up = %s, right = %s\n", terms[ast->up->val], terms[ast->left->val]);
            printf("curr = %s\n", terms[ast->val]);*/

            parseTree templ = ast->prev;
            parseTree tempr = ast->left;

            // removing TK_ID from the middle
            if(ast->prev != NULL){
                ast->prev->left = ast->left;
                //printf("ast->prev->left = %s\n", terms[ast->prev->left->val]);
            }

            // removing ast->up
            if(ast->up->up != NULL)
                ast->up->up->down = ast;

            if(ast->left != NULL)
                ast->left->prev = ast->prev;

            // to chenge the UP node of left and right nodes of ast
            //printf("templ = %s, ", terms[templ->val]);
            //printf("tempr = %s\n", terms[tempr->val]);

            while(templ != NULL){
                templ->up = ast;
                ast->down = templ;
                templ = templ->prev;
            }
            while(tempr != NULL){
                tempr->up = ast;
                tempr = tempr->left;
            }

            ast->prev = NULL;
            ast->left = ast->up->left;
            removeID(ast->down);
            removeID(ast->left);
            //free(ast->up);
        }

        else if(ast->up->prev != NULL && ast->up->val != 23 && ast->up->val != 26 /*&& ast->up->val != 46*/){
            // removing TK_ID from the middle
            printf("inside tok_value else\n");

            if(ast->prev != NULL)
                ast->prev->left = ast->left;

            ast->up->prev->left = ast;
            // to chenge the UP node of left and right nodes of ast
            parseTree templ = ast->prev;
            parseTree tempr = ast->left;
            while(templ != NULL){
                templ->up = ast;
                ast->down = templ;
                templ = templ->prev;
            }
            while(tempr != NULL){
                tempr->up = ast;
                tempr = tempr->left;
            }
            // setting pointers of ast's new neighbours
            if(ast->up->left != NULL)
                ast->up->left->prev = ast;
            // setting pointers of UP
            ast->left = ast->up->left;
            ast->prev = ast->up->prev;

            removeID(ast->down);
            //free(ast->up);
        }
    }
    else{
            removeID(ast->down);
            removeID(ast->left);
    }
}

void fixFunId(parseTree ast){
    if (ast == NULL)
        return;
    int tok_value = ast->val;

    if(tok_value == 54 || tok_value == 62){
        if(ast->up->prev == NULL && ast->up->val != 25){
            //printf("ast = %s\n", terms[ast->val]);
            //printf("ast->up->up = %s\n", terms[ast->up->up->val]);
            ast->up->up->down = ast;
            ast->down = ast->left;
            //printf("ast->down = %s\n", terms[ast->down->val]);

            if(ast->up->left != NULL)
                ast->up->left->prev = ast;

            parseTree pleft = ast->left;
            while(pleft != NULL){
                pleft->up = ast;
                pleft = pleft->left;
            }

            //printf("ast->left = %s\n", terms[ast->left->val]);

            ast->left->prev = ast;
            ast->up = ast->up->up;
            fixFunId(ast->left);
        }
        else if (ast->up->prev != NULL && ast->up->val != 25){
            //printf("ast in else = %s\n", terms[ast->val]);
            //printf("ast->up in else = %s\n", terms[ast->up->val]);

            // fix the pointers of ast's new neighbours
            ast->up->prev->left = ast;
            if(ast->up->left != NULL)
                ast->up->left->prev = ast;
            // fix ast's old neighbours
            if(ast->prev != NULL)
                ast->prev->left = ast->left;

            parseTree pleft = ast->left;
            while(pleft != NULL){
                pleft->up = ast;
                pleft = pleft->left;
            }

            if(ast->left != NULL)
                ast->left->prev = ast->prev;
            // fix ast
            ast->down = ast->left;
            ast->left = ast->up->left;
            ast->prev = ast->up->prev;
            ast->up = ast->up->up;

        }
    }
    else{
        fixFunId(ast->down);
        fixFunId(ast->left);
    }
}