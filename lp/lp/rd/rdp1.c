#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char str[40];
char* ptr=NULL;

void T()
{
  if(*ptr=='*')
  {
      ptr++;
       if(isdigit(*ptr))
       {
          ptr++;
           T();
       }
  }

  if(*ptr!='$')
  {
      printf("\nerror");
      exit(0);
  }
  return;
}

void E()
{
    if(isdigit(*ptr))
    {
        ptr++;
        T();
        printf("\nacceptable string");
        //printf("%c",*ptr);
    }
    else{
        printf("\nerror");
        exit(0);
    }

}

int main()
{
    printf("\nenter the string:");
    scanf("%s",str);
    str[strlen(str)]='$';
    //printf("%s",str);
    ptr=str;

    E();
    return 0;
}
