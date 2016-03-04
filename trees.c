struct Node;                     // individual Node in the tree
typedef struct Node Node;
typedef struct Node *Link;      //Link is a pointer to the Node

struct Node                       // Node data structure
{
 Link up;
 int val;
 int visit;      // whether Node has been visited earlier or not
 Link left;
 Link down
};

//this used to create the head Node

Link create(){
   Link head=(Link)malloc(sizeof(Node));
   head->up=NULL;
   head->val=0;
   head->visit=0;
   head->left=NULL;
   head->down=NULL;
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

Link search(Link start,int a)
{
   Link temp;
   if(start==NULL)
    return NULL;
   else if((start->val==a)&&(start->visit==0))
    return start;
   else if((temp=search(start->down))!=0)
     return temp;
    else if((temp=search(start->left))!=0)
      return temp;
    else
      return NULL;
}
void insert(Link temp,int rule,grammar gra)
{
  int *a=grammar[gra],i=1;
  Link temp1,temp2,right;

  while(a[i]!=0&&i<10)
  {
     temp1=(Link)malloc(sizeof(Node));
     temp1->val=a[i];
     temp1->visit=0;
     temp1->left=NULL;
     temp1->down=NULL;
     temp1->up=temp;
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

Link ruleFunc(Link head,int stack[],int top,FILE *fp,table tab,grammar gra)
{
  char *tok;  // for storing token
  int t_val,curr=0;  // token value and incrementing pointer in the input file
  int rule;         // for storing rule number
  Link temp;       // for storing the pointer of the position where data has to be stored
  while(top!=0)                       //looping through whole file
  {
    tok=getNextToken(fp,curr);
    t_val=find(tok);
    if(t_val==stack[top])
    {
      top=pop(stack,top);
      //curr++;
    }
    else
    {
      rule=tab[stack[top]][tok];
      if(head->down==NULL)
        insert(head,rule,gra);
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
              insert(temp,rule,gra);
         }
      }
      top=pop(stack,top);
      top=push(stack,top,rule,gra);

    }
    curr++;
  }
}