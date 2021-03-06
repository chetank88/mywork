#include<stdio.h>
#include<string.h>
#include "symboltable.h"

#define MAXTOKENLEN 40
#define BUFLEN 256
#define MAXRESERVED 9
#define true 1
#define FALSE 0

typedef enum
{
  START,INASSINGN,INSCOMMENT,INSCOMMENT1,INDCOMMENT,INDCOMMENT1,INNUM,INID,DONE
}statetype;
typedef enum
{
ENDFILE,ERROR,
IF,THEN,ELSE,WHILE,FOR,DO,INT,FLOAT,CHAR,
ID,NUM,
ASSIGN,EQ,LT,PLUS,MINUS,MULTIP,OVER,LPAREN,RPAREN,SEMI
}TokenType;
FILE *source;
FILE *listing;
char tokenstring[MAXTOKENLEN+1];
static char lineBuf[BUFLEN];
static int linepos=0;
static int bufsize=0;
static int lineno;
char tokenstring[MAXTOKENLEN+1];
int Echosource=true;
int Tracescan=true;
/*list sybtab=(list)malloc(sizeof(l1));
 sybtab->head=NULL;
 sybtab->tail=NULL;*/
static char getNextChar(void)
{
 if(!(linepos<bufsize))
   {
   lineno++;
      if(fgets(lineBuf,BUFLEN-1,source))
	   {
		   if(Echosource)
		   fprintf(listing,"%4d:%s",lineno,lineBuf);
	           bufsize=strlen(lineBuf);
	           linepos=0;
	           return lineBuf[linepos++];
	   }
	   else return EOF;
    }
    else
    return lineBuf[linepos++];
}
void printToken(TokenType token,const char* tokenString)
{
switch(token)
{
case IF:
case THEN:
case ELSE:
case WHILE:
case FOR:
case DO:
case INT:
case FLOAT:
case CHAR:
fprintf(listing,"reserved word:%s\n",tokenString);
default:
fprintf(listing,"token:%s\n",tokenString);

}
}
static void ungetNextChar(void)
{
   linepos--;
}
static struct
{
	char *str;
	TokenType tok;
} reservedWords[MAXRESERVED]={{"if",IF},{"then",THEN},{"else",ELSE},{"for",FOR},{"while",WHILE},{"do",DO},{"int",INT},{"float",FLOAT},{"char",CHAR}};

static TokenType reservedLookup(char *s)
{
	int i;
	for(i=0;i<MAXRESERVED;i++)
	{
		if(!(strcmp(s,reservedWords[i].str)==0))
		return reservedWords[i].tok;
        }
	return ID;
}
TokenType getToken(void)
{
   int tokenstringindex=0;
   TokenType currentToken;
   statetype state=START;
   int save;
  
   while(state!=DONE)
   {
	   char c=getNextChar();
	      
	   save=true;
	   switch(state)
	   {
	      case START:
		    if(isdigit(c))
		     state=INNUM;
		     else if(isalpha(c))
		     state=INID;
		     else if(c=='=')
		     state=INASSINGN;
		     else if((c==' ')||(c=='\t')||(c=='\n'))
		       save=FALSE;
		     else if(c=='/')
		     { save=FALSE;
		     state=INSCOMMENT;
		     }
		     else
		     {
		     state=DONE;
		     switch(c)
		     {
		       case EOF:
		           save=FALSE;
		           currentToken=ENDFILE;
		           break;
		       case '<':
		            currentToken=LT;
		            break;
		       case '+':
		            currentToken=PLUS;
		            break;
		       case '-':
		            currentToken=MINUS;
		            break;
		       case '*':
		            currentToken=MULTIP;
		            break;
		       case '/':
		            currentToken=OVER;
		            break;
		       case '(':
		            currentToken=LPAREN; 
		            break;
		       case ')':
		             currentToken=RPAREN;
		             break;
		       case ';':  
		             currentToken=SEMI;
		             break;
		       default:
		             currentToken=ERROR;
		             break;                       
		       
		     }
                    }    
                    break;
              case INSCOMMENT:
                 save=FALSE;
                 if(c=='/') state=INSCOMMENT1;
                 else if(c=='*')
                 { 
                   state=INDCOMMENT;
                 }
                 break;
              case INSCOMMENT1:
                  save=FALSE;
                  if(c=='\n') state=START;
                  break;
              case INDCOMMENT:
                   save=FALSE;
                   if(c=='*')
                    state=INDCOMMENT1;
                    break;
              case INDCOMMENT1:
                    save=FALSE;
                     if(c=='/')
                     state=START;
                     break; 
               case INASSINGN:
               state=DONE;
               if(c=='=')
               currentToken=EQ;
               else
               {
               ungetNextChar();
		 currentToken=ASSIGN;
		
               }
                 break;
               case  INNUM:
                  if(!isdigit(c))
                  {
                     ungetNextChar();
                     save=FALSE;
                     state=DONE;
                     currentToken=NUM;
                  }  
                   break;
               case INID:
                   if(!isalpha(c))
                   {
                   ungetNextChar();
                   save=FALSE;
                   state=DONE;
                   currentToken=ID;
                   }
                   break;
                case DONE:
                default:
                   fprintf(listing,"Scanner Bug: state=%d\n",state);
                   state=DONE;
                   currentToken=ERROR;
                   break;         
                 if((save)&&(tokenstringindex<=MAXTOKENLEN))
                 {
                 tokenstring[tokenstringindex++]=c;
             
                 }
                 if(state==DONE)
                 {
                  tokenstring[tokenstringindex]='\0';
                  if(currentToken==ID)
                  {
                    currentToken=reservedLookup(tokenstring);
                  }
                  if(currentToken==ID)
                  {
                   //add(sybtab,tokenstring,"datatype" ,1)
                  }
                 }              
                         
          }
       
   }
      if(Tracescan)
          {
           fprintf(listing,"\t%d:",lineno);
        
            printToken(currentToken,tokenstring);
          }
          
 return currentToken;  
}
void main()
{
 source = fopen("la.c","r+");

 listing = stdout;
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
  getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
  getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
  getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
 getToken();
}
