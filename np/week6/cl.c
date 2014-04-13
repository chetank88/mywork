#include <stdio.h>
#include <string.h>

int main()
{
   char buff[]={"my name is khan"};
  int i=0,k=0;
  int r=strlen(buff);
         for(i=r-1;i>=r/2;i--)
           {
               char temp=buff[k];
                buff[k]=buff[i];
                buff[i]=temp; 
                printf("%c ",buff[k]);
                printf("%c\n",buff[i]);
                //fflush(stdout);
           		k++;  
           }
           printf("\n%s",buff);
    return 0;
}
