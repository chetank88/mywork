%{
int c=0;
%}

%%
[a-z][a-z]*[ ]([a][n][d])|([o][r])[ ][[a-z][a-z]*]+ c=1;
%%
int main()
{
yylex();
if(c==1)
printf("compound statement");
else
printf("not compound");
}
yywrap()
{
return 1;
}

