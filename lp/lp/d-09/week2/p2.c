#include<stdio.h>

int main()
{
	FILE *outc=fopen("hello.c","r");
    FILE *outf=fopen("hellof.c","w");
   
	char c=getc(outc);
	char temp;
	while(c!=EOF)
	{
		
			if(c=='/')
			{
				 
					temp=getc(outc);
					if(temp=='/')
						{  
							c=getc(outc);
							while(getc(outc)!='\n');
			
			
					     }
			//printf("%c",c);	
					else if(temp=='*')
						 {
						    while(c!='*'&&c!=EOF)
						  {   
						    c=getc(outc);
						
						   }
                                                    while(c!='/'&&c!=EOF)
						     c=getc(outc);
     c=getc(outc);
						 }
					     
			
                                           else
					       {
					          putc(c,outf);
							printf("%c",c);
							 c=getc(outc);
					       }
	 
                           } 
			     else if(c==' ')
			     {
			printf("%c",c);	
					  c=getc(outc);
					  
					 while(c==' ')
					 { 
			
						  c=getc(outc);
			
					 }
				 }
				 else
				 {
					 putc(c,outf);
					//printf("%c",c);
					 c=getc(outc);
				 }
   }
	return 0;
}
