#include "lexer_dat.h"

lex getNewlex(){
    lex new = (lex) malloc(sizeof(tokenInfo));
    return new;
}

link getNewNode(){
    link new = (link) malloc(sizeof(node));
    new->lex = getNewlex();
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
    for(i = 0; i < bufflen; i++)
        B[i] = '\0';

    if(fread(B, (size_t)bufflen, (size_t) 1, fp))
    {
        printf("read some text\n");
        return fp;
    }
    return NULL;
}

tokenInfo getNextToken(FILE *fp){
    // take in the advanced file pointer and call the function getStream to get
    // the filled buffer
    lex new = getNewlex();
    if()

    return *new;
}

void addNode(lexChain chain, link new){
    link first = chain->first;
    while(first->next != NULL)
        first = first->next;

    first->next= new;
    // next of tail is NULL
    first->next->next = NULL;
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

int isValidlexeme(char *lexeme){
    int i;
    for(i = 0; i < 24; i++){
        //strlwr(lexeme);
        if(strcmp(lexemes[i], lexeme))
            return i;
    }
    return -1;
}

int isAlpha(char c){
    if(c >= 97 && c <= 122)
        return 1;
    if(c >= 65 && c <= 90)
        return 1;
    return 0;
}

int isNum(char c){
    if(c >= 48 && c <= 57)
        return 1;
    return 0;
}

lexChain getTokens(File* fp){
    lexChain head1=(lexChain)malloc(sizeof(struct head));
    initializeChain(head1);
    link point = head->first;
    buffer B;
    FILE *fp = fopen("testcase1.txt", "r");
    int start = 0, end = 0;
    if(fp==NULL)
    {
        printf("File not found\n");
        return NULL;
    }
    state = 0;
    fp = getStream(fp, B, bufflen);
    char ch = B[start];
    while(1){
        switch(state)
        {
            printf("in switch\n");
            printf("case0 ch = %c\n", ch);
            case 0 :
                if(ch=='['){
                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_SQL");
                    strcpy(new->lex->value,"[");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                    state = 0;
                    break;
                }
                else if(ch==']')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_SQR");
                    strcpy(new->lex->value,"]");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch==';')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_SEM");
                    strcpy(new->lex->value,";");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch==':')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_COLON");
                    strcpy(new->lex->value,":");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='.')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_DOT");
                    strcpy(new->lex->value,".");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='(')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_OP");
                    strcpy(new->lex->value,"(");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch==')')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_CL");
                    strcpy(new->lex->value,")");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='+')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_PLUS");
                    strcpy(new->lex->value,"+");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='-')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_MINUS");
                    strcpy(new->lex->value,"-");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='*')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_MUL");
                    strcpy(new->lex->value,"*");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='/')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_DIV");
                    strcpy(new->lex->value,"/");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='%')
                {
                    printf("in %% \n");

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_COMMENT");
                    strcpy(new->lex->value,"%");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                    ch = B[++end];

                    while(ch!='\n')
                        ch=B[++end];
                    start = end;
                }
                else if(ch==',')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_COMMA");
                    strcpy(new->lex->value,",");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
                }
                else if(ch=='~')
                {

                    link new = getNewNode();
                    strcpy(new->lex->token,"TK_NEG");
                    strcpy(new->lex->value,"~");
                    new->lex->line = ++lineNo;
                    addNode(head1, new);
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
                    strcpy(t.value,"_");
                    state = 13;
                }
                else if(ch >='0' && ch <= '9'){
                    strcpy(t.value,"\0");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state = 20;
                }
                else if(ch=='b' || ch=='d'){
                    strcpy(t.value,"\0");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=24;
                }
                else if(ch=='c'){
                    ch=readCh();
                    strcpy(t.value,"c");
                    state=27;
                }
                else if((ch>= 'a' && ch<='z') && ch!='b'&& ch!='c' && ch!='d'){

                    strcpy(t.value,"\0");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=28;
                }
                else if(ch=='\n'){

                    lineNo++;
                    strcpy(t.value, "0");
                    return t;

                }
                else if(ch==' ' || ch=='\t'){
                    strcpy(t.value, "0");
                    return t;

                }

                else if(!isAllowed(ch)){
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"<");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR 2 - Unknowm symbol  %c at line number %d\n", ch,lineNo);
                }
                break;
            case 1:
                if (ch=='&')
                {
                    ch=readCh();
                    state=2;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"&");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 2:
                if (ch=='&')
                {
                    strcpy(t.token,"TK_AND");
                    strcpy(t.value,"&&&");
                    t.line =++lineNo;
                    return t;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"&&");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 3:
                if (ch=='@')    {
                    ch=readCh();
                    state=4;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"@");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 4:
                if (ch=='@')
                {
                    strcpy(t.token,"TK_OR");
                    strcpy(t.value,"@@@");
                    t.line =++lineNo;
                    return t;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"@@");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 5:
                if (ch=='=')
                {
                    strcpy(t.token,"TK_EQ");
                    strcpy(t.value,"==");
                    t.line =++lineNo;

                    return t;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"=");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 6:
                if (ch=='=')
                {
                    strcpy(t.token,"TK_GE");
                    strcpy(t.value,">=");
                    t.line =++lineNo;
                    return t;
                }
                else{
                    strcpy(t.token,"TK_GT");
                    strcpy(t.value,">");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 7:
                if (ch=='=')
                {
                    strcpy(t.token,"TK_LE");
                    strcpy(t.value,"<=");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='-'){
                    ch=readCh();
                    state=8;
                }
                else {
                    strcpy(t.token,"TK_LT");
                    strcpy(t.value,"<");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 8:
                if(ch=='-'){
                    ch=readCh();
                    state=9;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"<-");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                    ch=readCh();
                }
                break;
            case 9:
                if (ch=='-')
                {
                    strcpy(t.token,"TK_ASSIGNOP");
                    strcpy(t.value,"<---");
                    t.line =++lineNo;
                    return t;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"<--");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 10:
                if (ch=='=')
                {
                    strcpy(t.token,"TK_NE");
                    strcpy(t.value,"!=");
                    t.line =++lineNo;
                    return t;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"!");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s at lineNo %d\n", t.value,t.line);
                }
                break;
            case 11:
                if (ch>= 'a' && ch<='z')
                {
                    strcpy(t.value,"#");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=12;
                }
                else{
                    strcpy(t.token,"TK_ERROR");
                    strcpy(t.value,"#");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 12:
                if (ch>= 'a' && ch<='z')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=12;
                }
                else{
                    strcpy(t.token,"TK_RECORDID");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 13:
                if (((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))&& ch!='m')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    if(strlen(t.value)>20 )
                    {
                        strcpy(t.token,"TK_ERROR");
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    ch=readCh();
                    state=14;
                }
                else if (ch=='m')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=16;
                }
                else{
                    strcpy(t.value,"_");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 14:
                if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    if(strlen(t.value)>20 )
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);

                    }
                    ch=readCh();
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=15;
                }
                else{
                    strcpy(t.token,"TK_FUNID");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 15:
                if(ch >='0' && ch <= '9'){

                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    if(strlen(t.value)>20){
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);

                    }
                    ch=readCh();
                    state=15;
                }
                else{
                    strcpy(t.token,"TK_FUNID");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 16:
                if(ch =='a'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=17;
                }
                else if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z')&& ch!='a')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=15;
                }
                else{
                    strcpy(t.value,"_m");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 17:
                if(ch =='i'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=18;
                }
                else if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z')&& ch!='i')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=15;
                }
                else{
                    strcpy(t.value,"_ma");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 18:
                if(ch =='n'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=19;
                }
                else if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z')&& ch!='n')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=15;
                }
                else{
                    strcpy(t.value,"_mai");
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 19:
                if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))    {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=14;
                }
                else if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=15;
                }
                else{
                    strcpy(t.token,"TK_MAIN");
                    strcpy(t.value,"_main");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 20:
                if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=20;
                }
                else if(ch =='.' ){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=21;
                }
                else{
                    strcpy(t.token,"TK_NUM");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 21:
                if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=22;
                }
                else{
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 22:
                if(ch >='0' && ch <= '9'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=23;
                }
                else{
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 23:
                strcpy(t.token,"TK_RNUM");
                t.line =++lineNo;
                return t;
                    break;
            case 24:
                if(ch >='2' && ch <= '7'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=25;
                }
                else if (ch>= 'a' && ch<='z')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=28;
                }
                else{
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                    ch=readCh();
                }
                break;
            case 25:
                if(ch >='b' && ch <= 'd'){
                    if(strlen(t.value)>20 )
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    else{
                        t.value[strlen(t.value)+1]='\0';
                        t.value[strlen(t.value)]=ch;
                        t.line =++lineNo;
                    }
                    ch=readCh();
                    state=25;
                }
                else if (ch>= '2' && ch<='7')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    if(strlen(t.value)>20 )
                    {
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);

                    }
                    ch=readCh();
                    state=26;
                }
                else{
                    strcpy(t.token,"TK_ID");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 26:
                if (ch>= '2' && ch<='7')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    if((strlen(t.value)) > 20 ){
                        printf("ERROR_1 : Identifier at line %d is longer than the prescribed length of 20 characters\n", lineNo);
                    }
                    ch=readCh();
                    state=26;
                }
                else{
                    strcpy(t.token,"TK_ID");
                    t.line =++lineNo;
                    return t;
                }
                break;
            case 27:
                if(ch >='2' && ch <= '7'){
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line =++lineNo;
                    ch=readCh();
                    state=25;
                }
                else if (ch>= 'a' && ch<='z')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=28;
                }
                else{
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    t.line=++lineNo;
                    printf("ERROR_3: Unknown pattern %s\n", t.value);
                }
                break;
            case 28:
                if (ch>= 'a' && ch<='z')
                {
                    t.value[strlen(t.value)+1]='\0';
                    t.value[strlen(t.value)]=ch;
                    ch=readCh();
                    state=28;
                }
                else{
                    //call function for deciding keywords and fieldId
                    strcpy(t.token, keywordsFieldId(t.value));
                    t.line =++lineNo;
                    return t;
                }
                break;
                default : printf("Error file\n");
                break;
        }
}
}

int main(){
    FILE *fp = fopen("test", "r");
    char output[128];
    fp = getStream(fp, output, 20);
    //int i;
    //for(i = 0; i < )
    printf("%s", output);
    if(fp==NULL)
        printf("\nis null\n");
    return 0;
}
