#include<stdio.h>
// This is a single line comment  
  /* *****This is a 
  ****** Multiline Comment  *****/ 

int main()
{
int i,j;
for( j=0;j<20;j++)
{
i=j%2;
if(i==0)
printf("Hello World\n");
else
printf("Bye World\n");
}
 return 0;
}
