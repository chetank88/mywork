#include <stdio.h>
#include <string.h>

void strc(char *sorc,char *dest,int i,int j)
{
	int k=0;
	while(i<=j)
	{
		dest[k++]=sorc[i++];
	}
	dest[k]='\0';
}

int main ()
{
	
 	FILE *fout=fopen("hellof.c","r");
 
  char str[100];
  char pch[100];
  int i=0;
  int j=0;
  while(!feof(fout))
  {
	  i=0,j=0;
	  
	
    //printf("%s",pch);
	  fgets(str,100,fout);
  while (i<strlen(str))
  {
    strc(str,pch,i,j);
    //printf("%s",pch);
    
		if(strcmp(pch,"for")==0)
		{
		printf("FOR\n");
		i=j+1;
		j=i;
		//printf("%d\n%d",i,j);
	   }
		else if(strcmp(pch,"if")==0)
		{
		printf("IF\n");
		  	i=j+1;
		j=i;
	    }
		else if(strcmp(pch,"else")==0)
		{
		printf("ELSE\n");
			i=j+1;
		j=i;
		
	    }
		else if(strcmp(pch,"int")==0)
		{
		printf("INT\n");
		 	i=j+1;
		j=i;
	    }
	    else if(strcmp(pch,"return")==0)
		{
		printf("RETURN\n");
		 	i=j+1;
		j=i;
	    }
		else
		{
			j++;
		//printf("<ID>");
	
	    }
   }
}
  
  return 0;
}
