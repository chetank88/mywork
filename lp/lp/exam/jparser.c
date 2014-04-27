#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char tok[30];
FILE* fp;
int flag=0;

void  gettoken()
{

  int x=fscanf(fp,"%s",tok);
  if(x!=EOF)
  return;
  else
  {
   printf("\n end of file reached");
   exit(-1);
  }
}

void ClassDec()
{
 gettoken();
  if(isalpha(tok[0]))
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n identifer expected");
 }
 gettoken();

  if(tok[0]=='(')
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n ( expected");
 }
 
 gettoken();
 
  if(tok[0]==')')
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n ) expected");
 }
 
  gettoken();
 
  if(tok[0]==';')
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n ; expected");
 }

 gettoken();
  
  if(tok[0]=='}')
 {
  printf("\n%s",tok);
  printf("\nString parsed");
 }
 else
 {
  flag=-1;printf("\n } expected");
 }
 
}


void ClassBody()
{
   gettoken();
 if(strcmp(tok,"void")==0)
 {
  printf("\n%s",tok);
 }
 else if(strcmp(tok,"}")==0)
 {
  printf("\n%s",tok);
  printf("\n string parsed");
  exit(0);
 }
 else
  {
   flag=-1;
   printf("\n void expected");
 }
 ClassDec();

}

void Interface()
{
  gettoken();
   if(isalpha(tok[0]))
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n identifer expected");
 }
  gettoken();
 
 if(strcmp(tok,"{")==0)
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n { expected");
 }
 ClassBody();

}

void Super()
{
  gettoken();
  if(isalpha(tok[0]))
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n identifer expected");
 }
 gettoken();

 if(strcmp(tok,"implements")==0)
 {
  printf("\n%s",tok);
 }
 else
 {
  flag=-1;printf("\n implements expected");
 }

 Interface();
}

void Modifer()
{
  gettoken();
 if(strcmp(tok,"class")==0)
  printf("\n%s",tok);
 else
{ flag=-1; printf("\n class expected");}
 gettoken();
 if(isalpha(tok[0]))
 printf("\n%s",tok);
 else
{ flag=-1;printf("\n identifer expected");}
 
 gettoken();

if(strcmp(tok,"extends")==0)
{
  flag=-1;
 printf("\n%s",tok);
}
else
{
 printf("\n extends expected");
}
Super();

}


int main()
{
  fp=fopen("tok","r");
  gettoken();
 if(strcmp(tok,"public")==0 || strcmp(tok,"private")==0 || strcmp(tok,"protected")==0)
 printf("\n%s",tok);
 else
  {flag=-1;printf("\n pri or pub or pro expected");}

 Modifer();
}
