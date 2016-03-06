/*
    BATCH NUMBER - 66
    SHIVIN SRIVASTAVA - 2013A7PS073P
    UPADHYAY GAURAV ARVIND - 2013A7PS030P
*/


#include "parser_dat.h"

typedef struct set set;
typedef struct set *links;
typedef struct shead shead;
typedef struct shead *sheadl;
struct shead{
  links head;
};
struct set{
  int val;
  links next;
};

sheadl initializeSet(){
    sheadl new = (sheadl) malloc(sizeof(shead));
    return new;
}

void addSet(sheadl S, int val){
    links head = S->head;
    if(head == NULL){
        S->head = (links) malloc(sizeof(set));
        S->head->val = val;
        return;
    }
    if(head->next == NULL){
        head->next = (links) malloc(sizeof(set));
        if(head->val != val)
            head->next->val = val;
        return;
    }
    while(head->next != NULL){
        if(head->val == val){
            return;
          }
        head = head->next;
    }
    if(head->val == val){
        return;
    }
    head->next = (links) malloc(sizeof(set));
    head->next->val = val;
}

void printSet(sheadl S){
    links head = S->head;
    while(head != NULL){
        printf("val = %s\n", terms[head->val]);
        head = head->next;
    }
}

int createfirst(int gra[][10], sheadl S, int A){
    int alpha, rule, right;
    for(rule = 0; rule < 85; rule++){
        // for rule A->alpha...
        printf("rule = %d\n", rule);
        if(gra[rule][0] == A){
            if(gra[rule][1] == 110 && gra[rule][2] == -1){
                addSet(S, 110);
                return 110;
            }
            for(right = 1; right < 10; right++){
              alpha = gra[rule][right];
              if(alpha >= 48 && alpha != 110){
                  addSet(S, alpha);
                  return alpha;
              }
              else if(alpha == 110){
                  //addSet(S, 110);
                  addSet(S, createfirst(gra, S, gra[rule][right+1]));
                  return 110;
              }
              else{
                  addSet(S, createfirst(gra, S, alpha));
                  return;
              }
          }
        }
    }
}

int main(){
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

    sheadl S = initializeSet();
    createfirst(gra, S, 0);
    printSet(S);
    return 0;
}
