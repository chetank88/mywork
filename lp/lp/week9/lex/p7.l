%{
int k=0;
%}

%%
[0-9]?[2468]* k=0;
[[0-9]?[13579]* k=1;

%%

int main()
{
yylex();
if(k==0)
printf("even");
else
printf("odd");
}
yywrap()
{
return 1;
}

