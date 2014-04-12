%{
int p=0;
int s=0;
%}
%%
[p][r][i][n][t][f] {p++;fprintf(yyout,"write");}
[s][c][a][n][f] {s++;fprintf(yyout,"read");}
%%
int main()
{
yyin=fopen("a.txt","r");
yyout=fopen("b.txt","w");
yylex();
printf("number of printfs%d",p);
printf("number of scanfs%d:",s);
}
yywrap()
{
return 1;
}
