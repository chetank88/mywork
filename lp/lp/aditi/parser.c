#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void statement_list();
int statement();

char *ptr;//to get next token
FILE *fp1,*fp2;
char tok[50];
int lineno=0;//to see which line we are currently on
int ret;//return value from a function call
char* getToken()
{
 if(fp1!=EOF)
  {fscanf(fp1,"%s",tok);
  if(tok[0]=='#')
	  {
		lineno++;
		fscanf(fp1,"%s",tok);
	  }
  }
  return tok;
}

int checkSym(char *ptr)//check symbol table for an entry of the token
{
     if(ptr[0]=='i')
      {
        if(ptr[1]=='d')
          return 1; //matches id
      }
     else return 0;//not an id

}



void factor()//factor->id|num
{
   ptr=getToken();
   int c=checkSym(ptr);
   if(c==1 || isalnum(ptr[0]))
   {
     printf("\n%s ",ptr); //testing thos shit!!!
   }
   else
       { printf("\nidentifier or number expected on line no.%d",lineno);
       exit(-1); }
}

int mulop()//mulop->*|/|%
{
  ptr=getToken();
  if(ptr[0]=='*' || ptr[0]=='/' || ptr[0]=='%')
    return 1;
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
    return 1;
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

int compar_relop(char* ptr)//compares relationl operators
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
    return 1;
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
	if(c==1) //is an identifier
	{
          ptr=getToken();
	  if(strcmp(ptr,"=")==0)
          {

                expn();
	  }
          else
	  {
		printf("\n= expected on line no.%d",lineno);
		exit(-1);
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

  ptr=getToken();
  if(strcmp(ptr,"else")==0)
  {
   ptr=getToken();
   statement();
  }
}

int dec_stmt()//dec_stmt->if ( expn ) stmt dprime
{ printf("INSIDE DECC_STMT");
  if(strcmp(ptr,"if")==0)
  {
    printf("\n%s ",ptr);

    ptr=getToken();
    if(strcmp(ptr,"(")==0)
    {
      expn();
     if(strcmp(ptr,")")==0)
       {
        printf("\n%s ",ptr);
       }
      else
      {
        printf("\n) expected on line no.%d\n",lineno);exit(-1);
      }
         ptr=getToken();
         statement();
        //  if(ptr[0]==';')
//           printf("\n%s haha",ptr);
//          else
// 	  {
//             printf("\n ; expected (dec st) on line no.%d\n",lineno);exit(-1);
//           }
	  dprime();

     }
    else
    {
      printf("\n( expected on line no.%d\n",lineno);exit(-1);
    }
   return 1;
  }
  return  0;

}
void idlist()	//idlist->id|id,idlist
{


    ptr=getToken();
printf("\n hi%s ",ptr);
     int there=checkSym(ptr);
     printf("%d",there);
     if(there==1)
      {
          printf("\n%s ",ptr);//testing
          ptr=getToken();
           if(strcmp(ptr,",")==0) //if more than one identifiers have been declared
		{
		  idlist();
		}
      }
      else
      {
          printf("\n identifier comma expected on line no.%d\n",lineno);
          exit(-1);
      }

}
int statement()//statement->ass_stmt|decs_stmt|loop_stmt
{
  ret=ass_stmt();
  if(ret==0)
  {
     ret=dec_stmt();
  }
  return ret;
}

void statement_list()//statement_list->statement;statement_list|null
{
   ret=statement();
    if(ret==1)
	{printf("\n%s ",ptr);
	  if(strcmp(ptr,";")!=0)
		    {printf("\n; expected on line haha no.%d",lineno);
		    exit(-1);
   	   }
	ptr=getToken();
	statement_list();
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

void declarations()	//declarations->datatype idlist;declarations
{
	ret=datatype();

  if(ret==1)
  {
	//declarations->datatype idlist;declarations

      idlist();
      if(strcmp(ptr,";")==0)
        {
        }
      else
       { printf("\nidentifier expected");
       exit(-1);
        }

      declarations();
  }
}
void Program()
{
   ptr=getToken();
   if(strcmp(ptr,"int")==0)
   {
     ptr=getToken();
      printf("Hello world:%s",ptr);
     int there=checkSym(ptr);
     if(there==1)
      {
           ptr=getToken();
           there=checkSym(ptr);

            if(there==0 && strcmp(ptr,"(")==0) //not in symb table and is opening
              {
                   ptr=getToken();
                   there=checkSym(ptr);

                     if(there==0 && strcmp(ptr,")")==0) //not in symb & is closing
                      {
                             ptr=getToken();
                             there=checkSym(ptr);
			 if(there==0 && strcmp(ptr,"{")==0) //opening brace
                           {
				declarations();
				statement_list();

                                ptr=getToken();
                                there=checkSym(ptr);
				  if(there==0 && strcmp(ptr,"}")==0) //check for closing brace
                                  {
				    // printf("\n%s ",ptr);
				    return;
                                  }
                                  else
                                   {
				    printf("\n} expected on line no.%d\n",lineno);exit(-1);
			           }
                                //need to put the condition for ending }
			   }
			else
			  {
                             printf("\n{ expected on line no.%d\n",lineno);
                             exit(-1);
			  }
                      }
                     else
                       {
		                  printf("\n) expected on line no.%d\n",lineno);
		                  exit(-1);
                       }


              }
            else
              {
                 printf("\n( expected on line no.%d\n",lineno);
                 exit(-1);
              }

      }
     else
      {
        printf("\nmain required on line no.%d\n",lineno);
        exit(-1);
      }
   }
  else
  {
    printf("\no return type for main function on line no.%d\n",lineno);
    exit(-1);
  }
}


int main()
{
  fp1=fopen("op.txt","r");
  fp2=fopen("symb.txt","r");
  Program();
  fclose(fp1);
  fclose(fp2);
  return 0;
}
