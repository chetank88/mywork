#include<stdio.h>
#include<string.h>

typedef struct node
{
  int slno;
  char *name;
  char *type;
  char *value;
}node;


typedef struct list

{

  node tok;
  struct list* next; 
  struct list* prev; 
}list;


void insert(list* l,list* head,list* tail)
{
   list *temp=(struct list*)malloc(sizeof(struct list));

   temp=head;
   while(temp->next!=tail)
  {
    temp=temp->next;
  }
  temp->next=l;
  l->prev=temp;
  l->next=tail;
  tail->prev=l;
  
}

int check(list* head,list* tail,char name[30])
{
 list *temp=(struct list*)malloc(sizeof(struct list));
 temp=head->next;
  printf("\n%s %s",name,temp->tok.name);
  while(temp!=tail)
  {
     if(strcmp(temp->tok.name,name)==0)
       return 1;
     temp=temp->next;
  }
  return 0;
  
}

void display(list* head,list* tail)
{
  list *temp=(struct list*)malloc(sizeof(struct list));

  temp=head->next;

   while(temp!=tail)
    {
      printf("\n%d %s",temp->tok.slno,temp->tok.name);
      temp=temp->next;
    }
  
}


int main()
{
  
  list head,tail;
  head.next=&tail; 
  tail.prev=&head;
  
   node l1,l2;
   list *lis=(struct list*)malloc(sizeof(struct list));

   l1.slno=1;
   l1.name="abc";
   lis->tok=l1;
   insert(lis,&head,&tail);

   l1.slno=2;
   l1.name="pqr";
   lis->tok=l1; 
  insert(lis,&head,&tail);
  display(&head,&tail);

 // int c=check(&head,&tail,"abc");

   //printf("%d\n",c);
  //printf("%d",l1.slno);
  //printf("%s",l1.name);
}
