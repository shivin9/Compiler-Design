#include "lexer_dat.h"
static int lineNo=1;
//int bufflen = 4096;

lex getNewlex(){
    lex new = (lex) malloc(sizeof(tokenInfo));
    return new;
}

void clear(char* str){
    int i;
    for(i = 0; i < 30; i++)
        str[i] = '\0';
}

link getNewNode(){
    link new = (link) malloc(sizeof(node));
    new->lex = getNewlex();
    new->lex->token = (char*) malloc(30*sizeof(char));
    new->lex->value = (char*) malloc(30*sizeof(char));
    int i;
    for(i = 0; i < 30; i++){
        new->lex->value[i] = '\0';
        new->lex->token[i] = '\0';
    }
    new->next = NULL;
    return new;
}

lexChain initializeChain(){
    lexChain new = (lexChain) malloc(sizeof(struct head));
    new->size = 0;
    new->first = NULL;
    return new;
}

FILE* getStream(FILE *fp, buffer B, int bufflen){
    // return the file pointer which has been advanced to further position
    int i;

    if(fp == NULL){
        printf("invalid file name...\n");
        exit(0);
    }

    //clearing the buffer
    // for(i = 0; i < bufflen; i++)
    //     B[i] = '\0';

    if(fread(B, (size_t)bufflen, (size_t) 1, fp))
    {
        return fp;
    }
    printf("%s\n", B);
    return NULL;
}

lex getNextToken(FILE *fp, int curr, lexChain chain){
    // take in the advanced file pointer and call the function getStream to get
    // the filled buffer
    int i;
    lex ret;
    link first = chain->first;
    for(i = 0; i < curr; i++){
        first = first->next;
    }
    return first -> lex;
}

void addNode(lexChain chain, link new){
    link first = chain->first;
    if(first == NULL){
        chain->first = new;
        return;
    }

    while(first->next != NULL)
        first = first->next;
    first->next = new;
    // next of tail is NULL
    first->next->next = NULL;
}

int newLine(char* B, int curr){
    while(B[curr] != '\n')
        curr++;
    curr++;
    lineNo++;
    return curr;
}

void printNode(link l){
    printf("token = %s, value = %s, line = %d", l->lex->token, l->lex->value,
            l->lex->line);
}

void printList(lexChain chain){
    link first = chain->first;
    while(first != NULL){
        printNode(first);
        printf("\n");
        first = first->next;
    }
}

char* keywordsFieldId(char *lexeme){
    int i;
    for(i = 0; i < 24; i++){
        //strlwr(lexeme);
        if(!strcmp(lexemes[i], lexeme))
            break;
    }
    return tokens[i];
}

int isAllowed(char c){
    if(c >= 97 && c <= 122)
        return 1;
    else if(c >= 65 && c <= 90)
        return 1;
    else if(c >= 48 && c <= 57)
        return 1;
    return 0;
}

lexChain getAllTokens(FILE* fp){
    lexChain head1=(lexChain)malloc(sizeof(struct head));
    initializeChain(head1);
    link point = head1->first;
    bufflen = 4096;
    char B[bufflen];

    FILE* temp = fopen("testcase4.txt", "a");
    fprintf(temp,"%c",'$');
    fclose(temp);

    static int start = 0, end = 0;

    state = 0;
    int len = 0;
    fp = getStream(fp, B, bufflen);
    char ch = B[end];
    char* tok = (char*) malloc(30*sizeof(char));
    char* val = (char*) malloc(30*sizeof(char));
    link new;

    while(ch != '$'){
        ch = B[end];
        printf("state = %d\n", state);
        switch(state)
        {
            case 0 :
                if(ch=='['){
                    strcpy(tok,"TK_SQL");
                    strcpy(val,"[");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);


                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else if(ch==']')
                {
                    strcpy(tok,"TK_SQR");
                    strcpy(val,"]");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);


                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else if(ch==';')
                {
                    strcpy(tok,"TK_SEM");
                    strcpy(val,";");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch==':')
                {
                    strcpy(tok,"TK_COLON");
                    strcpy(val,":");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='.')
                {
                    strcpy(tok,"TK_DOT");
                    strcpy(val,".");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='(')
                {
                    strcpy(tok,"TK_OP");
                    strcpy(val,"(");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch==')')
                {
                    strcpy(tok,"TK_CL");
                    strcpy(val,")");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='+')
                {
                    strcpy(tok,"TK_PLUS");
                    strcpy(val,"+");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='-')
                {
                    strcpy(tok,"TK_MINUS");
                    strcpy(val,"-");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='*')
                {
                    strcpy(tok,"TK_MUL");
                    strcpy(val,"*");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='/')
                {
                    strcpy(tok,"TK_DIV");
                    strcpy(val,"/");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='%')
                {
                    strcpy(tok,"TK_COMMENT");
                    //printf("tok = %s", tok);
                    strcpy(val,"comment");

                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);


                    new = getNewNode();

                    state = 0;

                    while(ch!='\n')
                        ch=B[++end];
                    start = end;
                    state = 0;
                    break;
                }
                else if(ch==',')
                {
                    strcpy(tok,"TK_COMMA");
                    strcpy(val,",");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='~')
                {
                    strcpy(tok,"TK_NEG");
                    strcpy(val,"~");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    break;
                }
                else if(ch=='&')
                {
                    ch = B[++end];
                    state=1;
                }
                else if(ch=='@')
                {
                    ch = B[++end];
                    state = 3;
                }
                else if(ch=='='){
                    ch = B[++end];
                    state = 5;
                }
                else if(ch=='>'){
                    ch = B[++end];
                    state = 6;
                }
                else if(ch=='<'){
                    ch = B[++end];
                    state = 7;
                }
                else if(ch=='!'){
                    ch = B[++end];
                    state = 10;
                }
                else if(ch=='#'){
                    ch = B[++end];
                    state = 11;
                }
                else if(ch=='_'){
                    ch = B[++end];
                    strcpy(val,"_");
                    state = 13;
                }
                else if(ch >='0' && ch <= '9'){
                    val[len]=ch;
                    len++;
                    ch=B[++end];
                    state = 20;
                }
                else if(ch=='b' || ch=='d'){
                    //strcpy(val,"\0");
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=24;
                }
                else if(ch=='c'){
                    val[len] = ch;
                    len++;
                    ch=B[++end];
                    state=27;
                }
                else if((ch>= 'a' && ch<='z') && ch!='b'&& ch!='c' && ch!='d'){
                    //strcpy(val,"\0");
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=28;
                }
                else if(ch=='\n'){
                    end = newLine(B, end);
                    break;
                }
                else if(ch==' ' || ch=='\t'){
                    state = 0;
                    end++;
                    ch = B[end];
                    start = end;
                    break;
                }

                else {
                    strcpy(tok,"TK_ERROR");
                    val[len]=ch;

                    //new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    //addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);
                    end = newLine(B, end);
                    state=0;
                    //printf("ERROR 2 - Unknowm symbol  %c at line number %d\n", ch,lineNo);
                }
                break;
            case 1:
                if (ch=='&')
                {
                    ch = B[++end];
                    state=2;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"&");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 2:
                if (ch=='&')
                {
                    strcpy(tok,"TK_AND");
                    strcpy(val,"&&&");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"&&");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 3:
                if (ch=='@')    {
                    ch = B[++end];
                    state=4;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"@");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 4:
                if (ch=='@')
                {
                    strcpy(tok,"TK_OR");
                    strcpy(val,"@@@");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"@@");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 5:
                if (ch=='=')
                {
                    strcpy(tok,"TK_EQ");
                    strcpy(val,"==");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"=");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 6:
                if (ch=='=')
                {
                    strcpy(tok,"TK_GE");
                    strcpy(val,">=");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else{
                    strcpy(tok,"TK_GT");
                    strcpy(val,">");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 7:
                if (ch=='=')
                {
                    strcpy(tok,"TK_LE");
                    strcpy(val,"<=");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else if(ch=='-'){
                    ch = B[++end];
                    state=8;
                }
                else {
                    strcpy(tok,"TK_LT");
                    strcpy(val,"<");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 8:
                if(ch=='-'){
                    ch = B[++end];
                    state=9;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"<-");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                    ch = B[++end];
                }
                break;
            case 9:
                if (ch=='-')
                {
                    strcpy(tok,"TK_ASSIGNOP");
                    strcpy(val,"<---");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"<--");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 10:
                if (ch=='=')
                {
                    strcpy(tok,"TK_NE");
                    strcpy(val,"!=");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"!");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", val, lineNo);
                }
                break;
            case 11:
                if (ch>= 'a' && ch<='z')
                {
                    strcpy(val,"#");
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=12;
                }
                else{
                    strcpy(tok,"TK_ERROR");
                    strcpy(val,"#");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 12:
                if (ch>= 'a' && ch<='z')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=12;
                }
                else{
                    strcpy(tok,"TK_RECORDID");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 13:
                if (((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))&& ch!='m')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    if(len>20 )
                    {
                        strcpy(tok,"TK_ERROR");
                        end = newLine(B, end);
                        state=0;
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    ch = B[++end];
                    state=14;
                }
                else if (ch=='m')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    printf("ch=m %s", val);
                    ch = B[++end];
                    state=16;
                }
                else{
                    strcpy(val,"_");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 14:
                if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    if(len>20)
                    {
                        end = newLine(B, end);
                        state=0;
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);

                    }
                    ch = B[++end];
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=15;
                }
                else{
                    strcpy(tok,"TK_FUNID");

                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 15:
                if(ch >='0' && ch <= '9'){

                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    if(len>20){
                        end = newLine(B, end);
                        state=0;
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    ch = B[++end];
                    state=15;
                }
                else{
                    strcpy(tok,"TK_FUNID");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 16:
                if(ch =='a'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=17;
                }
                else if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z')&& ch!='a')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=15;
                }
                else{
                    strcpy(val,"_m");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 17:
                if(ch =='i'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=18;
                }
                else if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z')&& ch!='i')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=15;
                }
                else{
                    strcpy(val,"_ma");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 18:
                if(ch =='n'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=19;
                }
                else if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z')&& ch!='n')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=15;
                }
                else{
                    strcpy(val,"_mai");
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 19:
                if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))    {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=15;
                }
                else{
                    strcpy(tok,"TK_MAIN");
                    strcpy(val,"_main");
                    printf("printed main\n");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 20:
                if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=20;
                }
                else if(ch =='.' ){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=21;
                }
                else{
                    strcpy(tok,"TK_NUM");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 21:
                if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=22;
                }
                else{
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 22:
                if(ch >='0' && ch <= '9'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=23;
                }
                else{
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 23:
                strcpy(tok,"TK_RNUM");
                new->lex->line =++lineNo;
                addNode(head1, new);


                state = 0;
                end++;
                start = end;
                break;
                break;
            case 24:
                if(ch >='2' && ch <= '7'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=25;
                }
                else if (ch>= 'a' && ch<='z')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=28;
                }
                else{
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                    ch = B[++end];
                }
                break;
            case 25:
                if(ch >='b' && ch <= 'd'){
                    if(len>20 )
                    {
                        end = newLine(B, end);
                        state=0;
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    else{
                        //val[len+1]='\0';
                        val[len]=ch;
                        len++;
                    }
                    ch = B[++end];
                    state=25;
                }
                else if (ch>= '2' && ch<='7')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    if(len>20 )
                    {
                        end = newLine(B, end);
                        state=0;
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);

                    }
                    ch = B[++end];
                    state=26;
                }
                else{
                    strcpy(tok,"TK_ID");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    state = 0;
                    //end++;
                    start = end;
                    break;
                }
                break;
            case 26:
                if (ch>= '2' && ch<='7')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    if((len) > 20 ){
                        end = newLine(B, end);
                        state=0;
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    ch = B[++end];
                    state=26;
                }
                else{
                    strcpy(tok,"TK_ID");
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);



                    state = 0;
                    end++;
                    start = end;
                    break;
                }
                break;
            case 27:
                if(ch >='2' && ch <= '7'){
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=25;
                }
                else if (ch>= 'a' && ch<='z')
                {
                    //val[len+1]='\0';
                    val[len]=ch;
                    len++;
                    ch = B[++end];
                    state=28;
                }
                else{
                    //val[len+1]='\0';
                    val[len]=ch;
                    new = getNewNode();
                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);
                    len=0;
                    clear(val);
                    clear(tok);

                    end = newLine(B, end);
                    state=0;
                    printf("ERROR_3: Unknown pattern %s\n", val);
                }
                break;
            case 28:
                if (ch>= 'a' && ch<='z')
                {
                    val[len] = ch;
                    len++;
                    ch = B[++end];
                    state=28;
                }
                else{
                    //call function for deciding keywords and fieldId
                    //printf("hello in kef");
                    strcpy(tok, keywordsFieldId(val));
                    new = getNewNode();

                    strcpy(new->lex->value, val);
                    strcpy(new->lex->token, tok);
                    new->lex->line = lineNo;
                    addNode(head1, new);

                    len=0;
                    clear(val);
                    clear(tok);

                    state = 0;
                    //end++;
                    start = end;
                    break;
                }
                break;
            default : end = newLine(B, end);
                      state=0;
                      printf("ERROR file\n");
                      break;
        }
    }
    return head1;
}

/*int main(){
    lexChain head1;
    FILE* fp1;
    head1=getAllTokens(fp1);
    printList(head1);
    return 0;
}*/
