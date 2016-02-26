#include "lexer_dat.h"

buff buff1;
buff buff2;

void initializeChain(lexChain new)
{
    new->size = 0;
    new->first = NULL;
}

void initializebuff()
{
    buff1.count=0;
}

FILE* getStream(FILE *fp, buffer B, int bufflen)
{
	int i;

	for(i = 0; i < bufflen; i++)
        B[i] = '\0';

    if(fread(B, (size_t)bufflen, (size_t) 1, fp))
    {
        printf("read some text\n");
        return fp;
    }
    return NULL;
}

void printToken(lexChain head1)
{
    link point;
    point=head1->first;
    while(point!=NULL){
        printf("%s",(point->l.token));
        point=point->next;
    }
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

char* keywordsFieldId(char *lexeme){
    int i;
    for(i = 0; i < 24; i++){
        //strlwr(lexeme);
        if(strcmp(lexemes[i], lexeme))
            break;
    }
    return tokens[i];
}

static int lineNo=0;
int flag=0;

char readCh()
{
    char ch;
    int count1;
    printf("in readCh\n");
    if(flag==0)
    {
        ch=buff1.ch[end++];
        ++buff1.count;
        count1=buff1.count;
        if(count1>BSIZE)
        {
            flag=1;
            end=0;
            buff1.count=BSIZE;
        }
    }
    else
    {
        ch=buff2.ch[end];
        end++;
        ++buff2.count;
        count1=buff2.count;
        if(count1>BSIZE)
        {
            flag=0;
            end=0;
            buff2.count=BSIZE;
        }
    }
    return ch;
}
tokenInfo getNextToken()
{
	printf("hello?\n");
    tokenInfo t;
    int i;
    for(i = 0; i < BSIZE; i++){
        printf("i=%d", i);
        t.token[i] = '\0';
        t.value[i] = '\0';
    }
    int state = 0;
    char ch=readCh();
	printf("hello3?\n");
    while(1){
        switch(state)
        {
        	printf("in switch\n");
        	printf("case0 ch = %c\n", ch);
            case 0 :
                if(ch=='['){
                    strcpy(t.token,"TK_SQL");
                    strcpy(t.value,"[");
                    t.line=++lineNo;
                    return t;
                }
                else if(ch==']')
                {
                    strcpy(t.token,"TK_SQR");
                    strcpy(t.value,"]");
                    t.line=++lineNo;
                    return t;
                }
                else if(ch==';')
                {
                    strcpy(t.token,"TK_SEM");
                    strcpy(t.value,";");
                    t.line=++lineNo;
                    return t;

                }
                else if(ch==':')
                {
                    strcpy(t.token,"TK_COLON");
                    strcpy(t.value,":");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='.')
                {
                    strcpy(t.token,"TK_DOT");
                    strcpy(t.value,".");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='(')
                {
                    strcpy(t.token,"TK_OP");
                    strcpy(t.value,"(");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch==')')
                {
                    strcpy(t.token,"TK_CL");
                    strcpy(t.value,")");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='+')
                {
                    strcpy(t.token,"TK_PLUS");
                    strcpy(t.value,"+");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='-')
                {
                    strcpy(t.token,"TK_MINUS");
                    strcpy(t.value,"-");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='*')
                {
                    strcpy(t.token,"TK_MUL");
                    strcpy(t.value,"*");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='/')
                {
                    strcpy(t.token,"TK_DIV");
                    strcpy(t.value,"/");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='%')
                {
					printf("in %% \n");
                    strcpy(t.token,"TK_COMMENT");
        			printf("done partial stuff\n");
                    strcpy(t.value,"%");
                    t.line =++lineNo;
        			printf("done stuff\n");
                    ch=readCh();
                    while(ch!='\n')
                        ch=readCh();
                    printf("c = %c\n", ch);
                    return t;
                }
                else if(ch==',')
                {
                    strcpy(t.token,"TK_COMMA");
                    strcpy(t.value,",");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='~')
                {
                    strcpy(t.token,"TK_NOT");
                    strcpy(t.value,"~");
                    t.line =++lineNo;
                    return t;
                }
                else if(ch=='&')
                {
                    ch=readCh();
                    state=1;
                }
                else if(ch=='@')
                {
                    ch=readCh();
                    state = 3;
                }
                else if(ch=='='){
                    ch=readCh();
                    state = 5;
                }
                else if(ch=='>'){
                    ch=readCh();
                    state = 6;
                }
                else if(ch=='<'){
                    ch=readCh();
                    state = 7;
                }
                else if(ch=='!'){
                    ch=readCh();
                    state = 10;
                }
                else if(ch=='#'){
                    ch=readCh();
                    state = 11;
                }
                else if(ch=='_'){
                    ch=readCh();
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
                if (ch=='@')	{
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
                if ((ch>= 'a' && ch<='z')||(ch>='A' && ch<='Z'))	{
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

lexChain getAllTokens()
{
    lexChain head1=(lexChain)malloc(sizeof(struct head));
    initializeChain(head1);
    link point,prev,prev1;
    buffer B;
    tokenInfo t;
    FILE *fp = fopen("testcase1.txt", "r");
    if(fp==NULL)
    {
        printf("File not found\n");
        return NULL;
    }

    initializebuff();

    start=0;
    end=0;
    fp=getStream(fp,B,BSIZE);
    strcpy(buff1.ch, B);
    fp=getStream(fp,B,BSIZE);
    strcpy(buff2.ch, B);

    printf("buff1 = %s\n", buff1.ch);
    printf("buff2 = %s\n", buff2.ch);
    while(1)
    {
        t=getNextToken();
        if(t.value=="0")
            continue;
        point=head1->first;
        if(point!=NULL)
        {
            prev=point;
            point=point->next;
        }
        prev1=(link)malloc(sizeof(node));
        prev1->l=t;
        prev1->next=NULL;
        prev->next=prev1;
        start=end;
        if(feof(fp))
            break;
        if(buff1.count==BSIZE){
            fp=getStream(fp,B,BSIZE);
            strcpy(buff1.ch, B);
        }
        if(buff2.count==BSIZE){
            fp=getStream(fp,B,BSIZE);
            strcpy(buff2.ch, B);
        }
    }


    fclose(fp);

    return head1;
}

int main()
{
    lexChain head1=(lexChain)malloc(sizeof(struct head));
    initializeChain(head1);
    head1=getAllTokens();
    printToken(head1);
    return 0;
}
