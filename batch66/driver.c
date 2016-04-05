/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/

#include "parserDef.h"
#include <fcntl.h>
int main(int argc, char* argv[]){
    if(argc == 1){
        printf("****enter the name of file****\n");
        exit(0);
    }
    if(argc == 2){
        printf("****enter the name of file for printing the parse tree****\n");
        exit(0);
    }
    else if(argc > 3){
        printf("****wrong format****\n");
        exit(0);
    }
    printf("********* both lexer and syntax analysis modules developed **********************\n");
    printf("************************ both modules compile ***********************************\n");
    printf("******************** work with testcases 1, 3, 4 ********************************\n");
    printf("******* error recovery in both lexer and parser implemented *********************\n");

    int comm, toklist, parse, tree;
    printf("press 1 for YES and 0 for NO\n");

    printf("do you want to see comment free code?\n");
    scanf("%d", &comm);

    printf("do you want to see token list?\n");
    scanf("%d", &toklist);

    printf("do you want verify syntactic correctness of the code?\n");
    scanf("%d", &parse);

    printf("do you want to print the parse tree?\n");
    scanf("%d", &tree);

    parseTree headT;
    headT=create();

    FILE* fp = fopen(argv[1], "r");
    //FILE* fp1 = fopen(argv[2], "w");

    if(fp==NULL)
    {
        printf("File not found\n");
        return 0;
    }

    lexChain ch;
    ch = getAllTokens(fp);

    if(comm){
        rewind(fp);
        int curr = 0;
        char B[4096];
        fread(B, (size_t)4096, (size_t) 1, fp);
        while(B[curr] != '$'){
            if(B[curr] == '%'){
                while(B[curr] != '\n')
                    curr++;
            }
            printf("%c", B[curr++]);
         }
    }

    if(toklist)
        printList(ch);

    if(parse == 0 && tree == 1){
        printf("can't print tree without checking the syntactic correctness of the code!\n");
        exit(0);
    }

    if(parse)
        parseInputSourceCode(headT, fp, ch);

    if(tree){
        int back, new;
        fflush(stdout);
        back = dup(1);
        new = open(argv[2], O_WRONLY);
        dup2(new, 1);
        close(new);

        printf("\nlexemeCurrentNode     lineno   token   valueIfNumber   parentNodeSymbol   isLeafNode(yes/no)    NodeSymbol\n");
        printTree(headT);

        fflush(stdout);
        dup2(back, 1);
        close(back);
    }
    //printTree(headT);
    parseTree ast = createAst(headT);
    printTree(ast);

    //free(ast);
    free(headT);
    free(ch);
    return 0;
}
