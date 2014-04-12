#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char str[40];
char* ptr=NULL;

void S();

void T1()
{
    if(*ptr==',')
    {
        ptr++;
        S();
        T1();
    }
    return;
}

void T()
{
    S();
    T1();
}

void S()
{
    if(*ptr=='a')
    {
        ptr++;
        return;
        //printf("%c",*ptr);
    }
    else if(*ptr=='(')
    {
        ptr++;
        T();
        if(*ptr==')')
        {
            ptr++;
            return ;
        }
        else{
            printf("\nerror");exit(0);
        }
    }
    else
    {
     printf("\nerror");exit(0);
    }

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

    S();
    if(*(ptr)=='$')
         {printf("accepted string");}
    else
    {
        printf("\nerror");
    }
  }
    return 0;
}

