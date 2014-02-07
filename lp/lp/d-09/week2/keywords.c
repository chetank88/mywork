#include<stdio.h>
#include<string.h>
int substringe(char* sorc,char* dest,int i,int j)
{
int k=0;
while(i<=j)
{
dest[k++]=sorc[i++];
}
dest[k]='\0';
}
void main()
{
	FILE *pFile;
	FILE *in = fopen("test.c","w+");
	char buff[100];
	char pch[100];
	int lbegin=0;
	int forward=0;
	int read,lb,f,i=0,n=6,flag=0,tempf=0;
	char str[][6]={"for","if","else","while","void","int"};
  
	pFile = fopen ("harshas.c" , "r");
     
     
        while(fgets (buff , 100 , pFile)!= NULL )
	    {
               
		lb=0,f=0;
              if(strlen(buff)>0)
               {
               
    		while(f<strlen(buff))
			{       
                                flag=0;
				substringe(buff,pch,lb,f);
                                   //keywords
			      while(i<n)
					{
                                                
  						
                                             printf("%s==%s\n",str[i],pch);
						if(strcmp(pch,str[i])==0)
							{
                                                               
								 fprintf (in, "%s\n", pch);
                                                                 flag=1;
                                                                  lb=f+1;
                                                                   f++;
                                                                   
                                                                 break;
							}
						i++;
					}
                                 if(flag!=1)
                          		{
                                                 
						f++;
					}
                                        i=0;
                                  
			}
                      
                 }
     
    	   }
       fclose (pFile);
}

