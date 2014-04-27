%{
int c=0;
%}
%%
[a-z][a-z]*[0-9]*[+-/*][a-z][a-z]*[0-9]* c++;
%%
int main()
{
yylex();
if(c>0)
printf("valid arithemetic statement");
else
printf("not valid");
}
yywrap()
{
return 1;
}

