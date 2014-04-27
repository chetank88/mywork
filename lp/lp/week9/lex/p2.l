%{
int l=0;
int w=0;
int sp=0;
int c=0;
%}
character [a-zA-Z]
%%
[\n] l++;
[ ] sp++,w=sp+1;
{character} c++;
%%

int main()
{
yylex();
printf("lines %d ;; spaces %d ;; words %d ;; charcters %d ",l,sp,w,c);
}
int yywrap()
{
return 1;
}
