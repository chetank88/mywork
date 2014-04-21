#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void statment_list();
int statment();

char *ptr;//to get next token
FILE *fp,*fp2;
char tok[32];
int ret;//return value from a function call

char* getToken()
{

  fscanf(fp,"%s",tok);

  return tok;

}

int checkSym(char *ptr)//check symbol table for an entry of the token
{
   int x=strlen(ptr);

   if(x<2)return 0;
   else
   {
     if(ptr[0]=='i')
      {
        if(ptr[1]=='d')
          return 1;
        else
          return 0;
      }
     else return 0;
   }

}
int datatype()
{
   //datatype->int|char

    ptr=getToken();
    if(strcmp(ptr,"int")==0 || strcmp(ptr,"char")==0)
    {
        printf("\n%s ",ptr);
        return 1;
    }
    return 0;
}

void idlist()
{
  //idlist->id|id,idlist

    ptr=getToken();

     int c=checkSym(ptr);
     if(c==1)
      {
          printf("\n%s ",ptr);

          ptr=getToken();
           if(strcmp(ptr,",")==0)
		{
		  printf("\n%s ",ptr);
		  idlist();
		}
      }
      else
      {
          printf("\n identifier expected");exit(-1);
      }

}

void declarations()
{
  ret=datatype();

  if(ret==1)
  {
	//declarations->datatype idlist;declarations

      idlist();
      if(strcmp(ptr,";")==0)
        {printf("\n%s ",ptr);}
      else
       { printf("\nidentifier expected or ; expected");exit(-1); }

      declarations();
  }

}

void factor()//factor->id|num
{
   ptr=getToken();
   int c=checkSym(ptr);
   if(c==1 || isalnum(ptr[0]))
   {
     printf("\n%s ",ptr);
   }
   else
       { printf("\nidentifier or number expected");exit(-1); }
}

int mulop()//mulop->*|/|%
{
  ptr=getToken();
  if(ptr[0]=='*' || ptr[0]=='/' || ptr[0]=='%')
  {
    printf("\n%s ",ptr);
    return 1;
  }
  return 0;
}

void tprime()//tprime->mulop factor tprime|null
{
  ret=mulop();
  if(ret==1)
  {
    factor();
    tprime();
  }

}

void term()//term->factor tprime
{
  factor();
  tprime();
}

int addop()//addop->+|-
{
  if(ptr[0]=='+' || ptr[0]=='-')
  {
    printf("\n%s ",ptr);
    return 1;
  }

  return 0;
}

void seprime()//seprime->addop term seprime|null
{
  ret=addop();
  if(ret==1)
  {
     term();
     seprime();
  }
}
void simple_exp()//simple_exp->term seprime
{
  term();
  seprime();
}

int compar_relop(char* ptr)//compares realationl operators
{
 if(strcmp(ptr,"==")==0 || strcmp(ptr,"!=")==0 ||strcmp(ptr,"<=")==0 ||strcmp(ptr,">=")==0 || strcmp(ptr,">")==0 || strcmp(ptr,"<")==0)
 {
   return 1;
 }
 return 0;

}
int relop()//relop->==|!=|<=|>=|<|>
{

  if(compar_relop(ptr)==1)
  {
    printf("\n%s ",ptr);
    return 1;
  }
  return 0;
}

void eprime()//eprime->relopsimple_exp|null
{

  ret=relop();
  if(ret==1)
  {
   simple_exp();
  }
}

void expn()//expn->simple_expn eprime
{
  simple_exp();
  eprime();
}

int ass_stmt()//ass_stmt->id=expn;
{
   int c=checkSym(ptr);
	if(c==1)
	{
          printf("\n%s ",ptr);
          ptr=getToken();
	  if(strcmp(ptr,"=")==0)
      {
		printf("\n%s ",ptr);
                expn();
        if(strcmp(ptr,";")==0)
          {
    		printf("\n%s ",ptr);
          }
          else
          {
		    printf("\n; expected but found %s",ptr);exit(-1);
   	      }
	  }
          else
	  {
		printf("\n= expected");exit(-1);
	  }

	}
        else
	{
		return 0;
	}
     return 1;
}

void dprime()//dprime->else stmt_list|null
{
  if(strcmp(ptr,"else")==0)
  {
   printf("\n%s ",ptr);
   ptr=getToken();
   statment_list();
   //printf("\n%s ",ptr);
  }
}

int dec_stmt()//dec_stmt->if ( expn ) stmt_list dprime
{
  if(strcmp(ptr,"if")==0)
  {
    printf("\n%s ",ptr);

    ptr=getToken();
    if(strcmp(ptr,"(")==0)
    {
      printf("\n%s ",ptr);
      expn();
     if(strcmp(ptr,")")==0)
       {
        printf("\n%s ",ptr);
       }
      else
      {
        printf("\n) expected");exit(-1);
      }
         ptr=getToken();
         statment_list();
	 dprime();

     }
    else
    {
      printf("\n( expected");exit(-1);
    }
   return 1;
  }
  return  0;

}

int statment()//statment->ass_stmt|decs_stmt|loop_stmt
{
  ret=ass_stmt();

  if(ret==0)
  {
     //printf("\n%s",ptr);
     ret=dec_stmt();
  }
  /*if(strcmp(ptr,";")==0)
          {
    		printf("\n%s ",ptr);
          }
          else
          {
		    printf("\n; expected you know %s",ptr);exit(-1);
   	      }*/
  return ret;

}

void statment_list()//statment_list->statment;statment_list|null
{

   ret=statment();

    if(ret==1)
	{

	  /*if(strcmp(ptr,";")==0)
          {
    		printf("\n%s ",ptr);
          }
          else
           {
		    printf("\n; expected");exit(-1);
   	   }*/
          ptr=getToken();
	  statment_list();
	}
}

void Program()
{
   ptr=getToken();

   if(strcmp(ptr,"int")==0)
   {
     printf("\n%s ",ptr);
     ptr=getToken();
     int c=checkSym(ptr);
     if(c==1)
      {
           printf("\n%s ",ptr);
           ptr=getToken();
           c=checkSym(ptr);

            if(c==0 && strcmp(ptr,"(")==0)
              {
                   printf("\n%s ",ptr);
                   ptr=getToken();
                   c=checkSym(ptr);

                     if(c==0 && strcmp(ptr,")")==0)
                      {
                            printf("\n%s ",ptr);
                             ptr=getToken();
                             c=checkSym(ptr);
			 if(c==0 && strcmp(ptr,"{")==0)
                           {
				declarations();
				statment_list();

                                ptr=getToken();
                                c=checkSym(ptr);
				  if(c==0 && strcmp(ptr,"}")==0)
                                  {
				    printf("\n%s \nString parsed",ptr);
				    return;
                                  }
                                  else
                                   {
				    printf("\n} expected");exit(-1);
			           }
                                //need to put the condition for ending }
			   }
			else
			  {
                             printf("\n{ expected");exit(-1);
			  }
                      }
                     else
                       {
		                  printf("\n) expected");exit(-1);
                       }


              }
            else
              {
                 printf("\n( expected");exit(-1);
              }

      }
     else
      {
        printf("\nmain required");exit(-1);
      }
   }
  else
  {
    printf("\ninvalid type");exit(-1);
  }
}

int checkFullSymbolTable()
{
   char token[32],buffer[25][32];
   int count=0,flag=0,i=0,k=0,l=0;

   while(fscanf(fp2,"%s",token)!=EOF)
   {
     //printf("%s\n",token);
      count++;
      if(count == 2)
        {if(strcmp(token,"void")==0)
           {flag=1;}
        }
      if(count ==3)
	   { if(flag==1)
         printf("Undeclared variable %s\n",token);
         strcpy(buffer[i++],token);
         count=0;
         flag=0;
       }
   }

   while(k<i)
   {
       l=k+1;
     while(l<i)
     {
         if(strcmp(buffer[k],buffer[l])==0)
            printf(" Multiple declaration of %s\n",buffer[k]);
         l++;
     }
      k++;
   }

    return 1;
}


int main()
{
  fp=fopen("tok.txt","r");
  fp2=fopen("sym","r");
  checkFullSymbolTable();
  Program();

  fclose(fp);
  fclose(fp2);
  return 0;
}
