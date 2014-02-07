#include<stdio.h>

void main()
{
FILE *out=fopen("harsha.c","r");
FILE *in =fopen("harshas.c","w");
char buff;
if(out==NULL)
{
perror("harsha.c");
}
	while(out!=NULL&&buff!=EOF)
	{
           
                buff=getc(out);
                
                       
		if(buff=='/')
		{   buff=getc(out);
                
                      if(buff=='/')
                       {
                           while(buff!='\n')
                              {
                                  buff=getc(out);
                                    
                               }
                              
                       }

                       else if(buff=='*')
                           {  
                              buff=getc(out);
                                 
                                 while(buff!='*')
                                   {
                                    buff=getc(out);
                                    
                                   
                                   }
                                  while(buff!='/')
                                      {
                                          buff=getc(out);
                                          
                                       }
                             continue;      
                       
                           } 
                       }
                  
                    
                    else  if(buff==' '||buff=='\t')
                     {  
                        buff=getc(out);
                          printf("%cspace",buff);
                        while(buff==' '|| buff=='\t')
                         {    
                               buff=getc(out);
                         }
                           printf("%cspace",buff);
                     }        
                
                       putc(buff,in);
                         

                                             
                  
                  
		
	}
fclose(out);
fclose(in);

return;
}
