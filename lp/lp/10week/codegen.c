#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main()
{
   char str[30];
   int m1,m2;
   printf("\n Enter the Postfix expression (end with $):");
   gets(str);
   int i=0,c,stack[20],count=-1;
   while(str[i]!='$')
   {
       c=str[i];
       if(isdigit(str[i]))
       {
          stack[++count]=c-48;
          printf("\n STACK[%d]=%d",count,stack[count]);
       }
       if(c=='+' ||c=='-'|| c=='*' || c=='/')
       {
           int d2=stack[count];
               m2=count;
           int d1=stack[--count];
               m1=count;

           int d3=0;
           char op[10];

           if(c=='+')
           {
                d3=d1+d2;
                strcpy(op,"add");
           }
            else if(c=='-')
           {
                d3=d1-d2;
                strcpy(op,"sub");

           }
            else if(c=='*')
           {

                d3=d1*d2;
                strcpy(op,"mul");

           }
           else if(c=='/')
           {

                d3=d1/d2;
                strcpy(op,"div");

           }

              stack[count]=d3;
                printf("\n ----------------------------------");
                printf("\n STACK[%d]=%d ,STACK[%d]=%d",m1,d1,m2,d2);
                printf("\n STACK[%d]=STACK[%d]%cSTACK[%d]=%d",m1,m1,c,m2,d3);
                printf("\n -----------");
               printf("\n mov R%d,%d",m2,d2);
               printf("\n mov R%d,%d",m1,d1);
               printf("\n %s R%d,R%d",op,m1,m2);
               printf("\n-----------------------------------");

       }
            i++;
   }
    printf("\n Calulated value of Expression = %d",stack[0]);
    printf("\n ----------------------------------");
    printf("\n store STACK[%d],R%d",m1,m1);
    printf("\n ----------------------------------");
   return 0;
}
