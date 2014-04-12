#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char key[][10]={"short","int","long","float","double","char","if","else","for","while","do","switch","case","break"};
char datatypes[][10]={"short","int","long","float","double","char"};
char op[][10]={"+","-","/","*","%","<",">","!","&","|","?",":","=","^"};
int noOfKeyWords=14;
int noOfOperators=14;
int count[14]={0};
int countop=0;
char tok[1500][300];
char attr[2][30];
int sl=1;//serial no

FILE* fp;

int check(char sc)
{
  switch(sc)
  {
   case '+':
   case '-':
   case '/':
   case '%':
   case '*':
   case '=':
   case '>':
   case '<':
   case '!':
   case '&':
   case '|':
   case '^':
   case ' ':
   case '\n':
   case '\t':
   case '(':
   case ')':
   case ',':
   case ':':
   case ';':
   case ']':
   case '[':
   case '@':
   case '}':
   case '{':
   case '#':
   case '\\':
   case '.':
   case '"':
   case '?':return 1;
  }
  return 0;
}

int token(FILE* fp)
{
  char sc;
  int x=0,y=0,eof;
  while(eof!=EOF)
      {
        while((eof=fscanf(fp,"%c",&sc))!=EOF)
        {
           if(sc=='"')
            {
               while((eof=fscanf(fp,"%c",&sc))!=EOF)
                 {
                         if(sc=='"')break;
                 }
            }

           if(check(sc))break;

            tok[x][y++]=sc;
        }
         if(y!=0)
            {
                tok[x][y]='\0';x++;y=0;
                if(sc!=' ' && sc!='\n' && sc!='"' && sc!='\t' )
                    {
                        tok[x][y++]=sc;tok[x][y]='\0';x++;y=0;
                    }
          }
          else
          {

              if(sc!=' ' && sc!='\n' && sc!='"' && sc!='\t' )
              {
                tok[x][y++]=sc;
                tok[x][y]='\0';x++;y=0;
              }
          }

     }

   return x-1;

}


typedef struct node
{
  int slno;
  char name[30];
  char type[30];
  char value[30];
}node;


typedef struct list

{

  node tok;
  struct list* next;
  struct list* prev;
}list;

  list head,tail;


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

int checkId(list* head,list* tail,char name[30])
{
 list *temp=(struct list*)malloc(sizeof(struct list));
 temp=head->next;

  while(temp!=tail)
  {
     if(strcmp(temp->tok.name,name)==0)
       return temp->tok.slno;
     temp=temp->next;
  }
  return 0;

}

void createSymbolTable(int sl,char attr[][30],list* head,list* tail)
{
 node l1;
 list *ul=(struct list*)malloc(sizeof(struct list));
 l1.slno=sl;
 strcpy(l1.name,attr[0]);
 strcpy(l1.type,attr[1]);
 ul->tok=l1;
 insert(ul,head,tail);
}

void display(list* head,list* tail)
{
    printf("\n\nSymbol Table :\n");
  list *temp=(struct list*)malloc(sizeof(struct list));

  temp=head->next;

   while(temp!=tail)
    {
      printf("\n%d %s %s",temp->tok.slno,temp->tok.type,temp->tok.name);
      temp=temp->next;
    }

}

void keyWordCount(int x)
{
    int i,j;
   for(i=0;i<=x;i++)
   for(j=0;j<noOfKeyWords;j++)
    {
       if(strcmp(key[j],tok[i])==0)
          {
            count[j]++;
          }
       else if(strcmp(op[j],tok[i])==0)
          {
               countop++;
          }
    }
   printf("\nkeyword\tcount\n");
   for(i=0;i<noOfKeyWords;i++)
    {
        printf("%s\t%d\n",key[i],count[i]);
    }

}

void printToken(char tok[])
{
    char tokGen[30]="";

               strcat(tokGen,"<");
               strcat(tokGen,tok);
               strcat(tokGen,">");
               strcat(tokGen,"\0");
               printf("%s ",tokGen);
               strcpy(tokGen,"");
}

void opCount(int x)
{
    int i,j,k,flag=0;
    char type[30];
    char tokGen[30]="";
    char ita[10];
    printf("\n\noperators:%d\n",countop);


    for(i=0;i<x;i++)
    {
      int c=checkId(&head,&tail,tok[i]);
        if(c==0)
         {
            for(j=0;j<noOfOperators;j++)
            {
              if(strcmp(op[j],tok[i])==0)
               {
                 for(k=0;k<noOfOperators;k++)
                   if(strcmp(op[k],tok[i+1])==0)
                   {
                       strcat(tokGen,op[j]);
                       strcat(tokGen,op[k]);
                       printToken(tokGen);
                       strcpy(tokGen,"");
                        flag==1;
                        i+=2;
                        break;
                   }

             }
            }
            if(flag==0)
              printToken(tok[i]);
         }
         else
         {
                         strcat(tokGen,"id,");
                        //strcat(tokGen,itoa(c,ita,10));
                         snprintf(ita,10,"%d",c);
                         strcat(tokGen,ita);
                         //strcat(tokGen,snprintf(ita,"%d",c));
                         printToken(tokGen);
                         strcpy(tokGen,"");
         }
      for(j=0;j<noOfKeyWords;j++)
        if(strcmp(key[j],tok[i])==0 && strcmp(tok[i+2],"(")!=0 && strcmp("if",tok[i])!=0)
         {
           if(strcmp(tok[i+2],";")==0 || strcmp(tok[i],"else")==0)
           {
                //printf("\n%s %s",tok[i],tok[i+1]);
                int c=checkId(&head,&tail,tok[i+1]);
                  if(c==0)
                      {

                         strcpy(attr[0],tok[i+1]);
                         strcpy(attr[1],tok[i]);
                         createSymbolTable(sl++,attr,&head,&tail);
                         strcat(tokGen,"id,");
                         //strcat(tokGen,itoa(sl-1,ita,10));
                         snprintf(ita,10,"%d",sl-1);
                         strcat(tokGen,ita);
                         printToken(tokGen);
                         strcpy(tokGen,"");

                      }
           }
          else
          {
             strcpy(type,tok[i]);
             while(strcmp(tok[++i],";")!=0)
	       {
             if(strcmp(tok[i],"=")==0)
              {
                 // printf("\n%s %s",type,tok[i-1]);
                  int c=checkId(&head,&tail,tok[i-1]);
                  if(c==0)
                      {
                         strcpy(attr[0],tok[i-1]);
                         strcpy(attr[1],type);
                         createSymbolTable(sl++,attr,&head,&tail);
                         strcat(tokGen,"id,");
                         //strcat(tokGen,itoa(sl-1,ita,10));
                         snprintf(ita,10,"%d",sl-1);
                         strcat(tokGen,ita);
                         printToken(tokGen);
                         strcpy(tokGen,"");
                      }

              }
             else if(strcmp(tok[i],",")==0)
               {
                   //printf("\n%s %s",type,tok[i-1]);

                   int c=checkId(&head,&tail,tok[i-1]);
                  if(c==0)
                      {

                         strcpy(attr[0],tok[i-1]);
                         strcpy(attr[1],type);
                         createSymbolTable(sl++,attr,&head,&tail);
                            //strcat(tokGen,"<");
                         strcat(tokGen,"id,");
                         //strcat(tokGen,itoa(sl-1,ita,10));
                         snprintf(ita,10,"%d",sl-1);
                         strcat(tokGen,ita);
                         //strcat(tokGen,">");
                         //strcat(tokGen,"\0");
                         //printf("%s ",tokGen);
                         printToken(tokGen);
                         strcpy(tokGen,"");

                      }
                   strcat(tokGen,",");
                   printToken(tokGen);
                   strcpy(tokGen,"");

               }
	     }
          
           if(strcmp(tok[i-2],"=")!=0)
               {
                 //printf("\n%s %s",type,tok[i-1]);
                  int c=checkId(&head,&tail,tok[i-1]);
                  if(c==0)
                      {
                         strcpy(attr[0],tok[i-1]);
                         strcpy(attr[1],type);
                         createSymbolTable(sl++,attr,&head,&tail);
                         strcat(tokGen,"id,");
                         //strcat(tokGen,itoa(sl-1,ita,10));
                         snprintf(ita,10,"%d",sl-1);
                         strcat(tokGen,ita);
                         printToken(tokGen);
                         strcpy(tokGen,"");
                      }

               }
           i--;
          }
        }
        else if(strcmp(key[j],tok[i])==0 && strcmp(tok[i+2],"(")==0 && strcmp("if",tok[i])!=0)
         {
               //printf("\n%s %s",tok[i],tok[i+1]);
                  int c=checkId(&head,&tail,tok[i+1]);
                  if(c==0)
                      {
                         strcpy(attr[0],tok[i+1]);
                         strcpy(attr[1],tok[i]);
                         createSymbolTable(sl++,attr,&head,&tail);
                         strcat(tokGen,"id,");
                         //strcat(tokGen,itoa(sl-1,ita,10));
                         snprintf(ita,10,"%d",sl-1);
                         strcat(tokGen,ita);
                         printToken(tokGen);
                         strcpy(tokGen,"");
                         i++;
                      }

         }

    }


}



int main()
{
  head.next=&tail;
  tail.prev=&head;


fp=fopen("pr1.txt","r");
if(fp!=NULL)
{
  int x= token(fp);


    keyWordCount(x);
    opCount(x);

   display(&head,&tail);
   printf("\n");
}
else
{
   printf("\nerror opening the file");
}

return 0;
}
