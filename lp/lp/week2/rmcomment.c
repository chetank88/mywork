#include<stdio.h>
#include<string.h>
#include<stdlib.h>


FILE* openFile(char name[20],char mode[2])
{
  FILE* fp=fopen(name,mode);
   if(fp!=NULL)
   {
     return fp;
   }
   printf("\nerror opening the file");
  exit(0);
  
}

void readFile(FILE *fp)
{
    char ch,chp='\n';
    FILE* fp1=openFile("pr1cpy.txt","w");
   while(fscanf(fp,"%c",&ch)!=EOF)
   {
     if(ch=='/')
      {
        fscanf(fp,"%c",&ch);
         if(ch=='/')
          {
              while(fscanf(fp,"%c",&ch))
                {
                     if(ch=='\n')
                       break;
                }
          }
         else if(ch=='*')
         {
             while(fscanf(fp,"%c",&ch))
              {
                 if(ch=='*')
                    {
                       fscanf(fp,"%c",&ch);
			 if(ch=='/')
                           { break;}
		    }
              }
         }
         else
          {
              fprintf(fp1,"%c",ch);
          }
          
      }
     else
     {
           fprintf(fp1,"%c",ch);

     }
   }
    fclose(fp);
    fclose(fp1);
    
}

void removeSpaces()
{
  FILE* fp=openFile("pr1cpy.txt","r");
  FILE* fp1=openFile("pr1cpy2.txt","w");
  char ch;
  while(fscanf(fp,"%c",&ch)!=EOF)
   {
       if(ch==' ')
        { fprintf(fp1,"%c",ch);
            while(fscanf(fp,"%c",&ch))
              if(ch!=' ' && ch!='\n')
               {fprintf(fp1,"%c",ch);break;}
        }
        else
        {      if(ch=='\n')
                 ch=' ';
               fprintf(fp1,"%c",ch);
        } 
   }
}

int main()
{
    FILE* fp=openFile("pr1.txt","r");
    readFile(fp);
    removeSpaces();
   
   return 0;
}

