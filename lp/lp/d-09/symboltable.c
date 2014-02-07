#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include "symboltable.h"

struct node1
{
int h;
char *name;
char *type;
node  left;
node  right;
};

struct list1
{
node head;
node tail;
}l1;

int nosymbol(list li,char *name)
{
node st=li->head;

	while(st!=NULL)
	{
		if(strcmp(st->name,name)==0)
		{
		  return 0;
		}
		st=st->left;
		
	}
	return 1;

}
display(list dli)
{
node h=dli->head;
	while(h!=NULL)
	{
		printf("%d\t",h->h);
		printf("%s\t",h->name);
		printf("%s\t",h->type);
		printf("\n");
		h=h->right;
	  
	}
}
void addnode(node a,list li)
{
	node st=li->head;

	if(st==NULL)
	{
		li->head=a;
		li->tail=a;
				   
	}
	else
	{
	
	        li->tail->right=a;
		a->left=li->tail;
		li->tail=a;
				

	}
}
int add(list li,char *name,char *type,int i)
{
	if(nosymbol(li,name))
	{
           node a=(node)malloc(sizeof(struct node1));
           a->name=name;
           a->type=type;
           a->h=i;
           a->left=NULL;
           a->right=NULL;
           addnode(a,li);
           return 1;
	}
	else
	{
	 return 2;
	}
}


