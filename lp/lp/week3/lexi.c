#include<stdio.h>
#include<string.h>



int check(char sc)
{
  switch(sc)
  {
   case ' ':
   case '\n':
   case '(':
   case ')':
   case ',':
   case ':':
   case ';':
   case '=':
   case '"':return 1;
  }
  return 0;
}

int token(FILE* fp,char tok[][30])
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
         if(y!=0) { tok[x][y]='\0';  printf("\n%s",tok[x]);x++;y=0; }
        
       
     }
   
   return x-1;
    
}

int main()
{

char key[][10]={"short","int","long","float","double","char","if","else","for","while","do","switch","case","break"};
int noOfKeyWords=14;
int count[14]={0};
char tok[1000][300];

FILE* fp;
fp=fopen("pr1.txt","r");
if(fp!=NULL)
{
  int x= token(fp,tok);
  int i,j;
  for(i=0;i<=x;i++)
   for(j=0;j<noOfKeyWords;j++)
    {
       if(strcmp(key[j],tok[i])==0)
          {
            count[j]++;
          }
    }
   printf("\nkeyword\tcount\n");
   for(i=0;i<noOfKeyWords;i++)
    {
        printf("%s\t%d\n",key[i],count[i]);
    }
      
}
else
{
   printf("\nerror opening the file");
}

return 0;
}
