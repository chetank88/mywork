%{
int n=0;
int p=0;
%}

%%
[+]?[1-9][0-9]* p++;
[-]?[1-9][0-9]* n++;
%%
int main()
{
yylex();
if(n>0)
printf("number is negative");
else
printf("number is positive");
}
yywrap()
{
return 1;
}
