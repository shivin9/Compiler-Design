/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/

//#include "parserDef.h"
#include "symData.h"

#include <fcntl.h>
int main(int argc, char* argv[]){
    if(argc == 1){
        printf("****enter the name of file****\n");
        exit(0);
    }

    else if(argc > 2){
        printf("****wrong format****\n");
        exit(0);
    }
    printf("*********************************************************************************\n");
    printf("Level 3: Symbol table/type Checking/ Semantic Rules modules work \n");
    printf("*********************************************************************************\n");

    int  toklist, parse, asTree,pA,sT,semE,code;
    printf("press 1 for YES and 0 for NO\n");

    printf("do you want to see token list?\n");
    scanf("%d", &toklist);

    printf("do you want verify syntactic correctness of the code?\n");
    scanf("%d", &parse);
   
    printf("Do you want to print the ast tree?\n");
    scanf("%d",&asTree);

    printf("Allocated memory and number of nodes to each of parse tree 	and abstract syntax tree for the test case used.\n");
    scanf("%d",&pA);

    printf("do you want to print Symbol Table?\n");
    scanf("%d",&sT);

    printf("Semantic errors?\n");
    scanf("%d",&semE);

    printf("Assembly Code\n");
    scanf("%d",&code);
   
    parseTree headT;
    headT=create();

    FILE* fp1 = fopen(argv[1], "a");
    fprintf(fp1,"%c",'$');
    fclose(fp1);
    FILE* fp = fopen(argv[1], "r");

    if(fp==NULL)
    {
        printf("File not found\n");
        return 0;
    }

    lexChain ch;
    ch = getAllTokens(fp);

   
    if(toklist)
    {
      
        printList(ch);
    }
   

    if(parse){
      
        parseInputSourceCode(headT, fp, ch);
        fixTree(headT, ch);
        printf("\nlexemeCurrentNode     lineno   token   valueIfNumber   parentNodeSymbol   isLeafNode(yes/no)    NodeSymbol\n");
        printTree(headT);
        
    }
    
    int ntree =sizeofTree(headT);
    int stree =sizeof(Node)*ntree;
   
     parseTree ast = createAst(headT);
    
     int nast= sizeofTree(ast);
     int sast =sizeof(Node)*nast;
     
    float comp=(((float)(stree-sast))/stree)*100;
     
    if(asTree)
    {      
        printTree(ast);
    } 
    if(pA)
    {   
      
      printf("Parse tree Number of nodes= %d  Allocated Memory  = %d\n",ntree,stree);
      printf("AST        Number of nodes= %d  Allocated Memory  = %d\n",nast,sast);
      printf("Compression percentage = %f\n",comp);
    }
    symLink stab = createSym();
    getSymtable(stab, ast);
    
    if(sT)
    {
      
       printf("Lexeme(identifier)    type   scope(name of the function/global)       offset  \n");
       printSymTable(stab);
    }
    if(semE)
    {
      
       testRules(stab, ast);
    }

    if(code)
    {
	FILE* fpcode = fopen(argv[2], "w");
	generateCode(ast, fpcode);
    }
    free(headT);
    free(ch);
    return 0;
}
