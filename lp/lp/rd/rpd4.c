#include<stdio.h>
#include<stdlib.h>

char str[40];
char* ptr=NULL;

void B()
{
  if(*ptr=='d')
  {
	  ptr++;
  }
}


void A1()
{
 if(*ptr=='b')
 {
	 ptr++;
	 A1();
 }
}

void A()
{
  if(*ptr=='b')
  {
    ptr++;	  
    A1();
  }
}


void S()
{
  if(*ptr=='a')
  {
   ptr++;	  
   A();
   if(*ptr=='c')
   {
    ptr++;	   
    B();
    ptr++;
     if(*ptr=='e')
	  {  ptr++;
	     return;
          }
     }
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
        printf("\nerror");exit(0);
    }
  }
    return 0;
	     

		        
}
