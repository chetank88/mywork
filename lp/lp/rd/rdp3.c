#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char str[40];
char* ptr=NULL;


void T();
void F()
{
  if(isalnum(*ptr))
  {
      ptr++;
      return;
  }
  else
  {
      printf("\nerror");
      exit(0);
  }
}

void T1()
{
    if(*ptr=='*')
    {
      ptr++;
      F();
      T1();
    }
    return;
}

void E1()
{
  if(*ptr=='+')
  {
      ptr++;
      T();
      E1();
  }

  return;

}
void T()
{
  F();
  T1();
}

void E()
{
    T();
    E1();
}

int main()
{

    while(1)
    {
    printf("\nenter the string:");
    scanf("%s",str);
    str[strlen(str)]='$';
    //printf("%s",str);
    ptr=str;

    E();
    if(*(ptr)=='$')
         {printf("accepted string");}
    else
    {
        printf("\nerror");exit(0);
    }
  }
    return 0;
}
