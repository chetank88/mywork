#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char token[30][30];
FILE* fp,*fp1;
char ch;
int i=0,y=0;
void fromfile()
{
	fp=fopen("pr.java","r");
	fp1=fopen("tok","w");

	while((ch=fgetc(fp))!=EOF)
	{
		if(ch!=' '&&ch!='\n'&&ch!='{' && ch !='}' && ch!='(' && ch!=')' &&ch!=';')
		{
			
			token[i][y++]=ch;
			fputc(ch,fp1);
			
		}
		
		else if(ch=='(' || ch==')' || ch=='{' ||ch=='}'||ch==';')
		{
                        if(y>0)
			{
				token[i++][y]='\0';y=0;
				fputc(' ',fp1);
			}

                        token[i][y++]=ch;
			fputc(ch,fp1);                  
		}
                else
		{	
		  if(y>0)
		  {
                   i++;y=0;
		   fputc(' ',fp1); 	
		  }
		}
	
	}
  fclose(fp);
  fclose(fp1);
}
int main()
{
	fromfile();
	int j;
	for(j=0;j<i;j++)
		printf("%s\n",token[j]);
	return 0;
}
