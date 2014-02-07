#include<stdio.h>


intmain()
{
inti,j;
for(j=0;j<20;j++)
{
i=j%2;
if(i==0)
printf("HelloWorld\n");
else
printf("ByeWorld\n");
}
return0;
}
