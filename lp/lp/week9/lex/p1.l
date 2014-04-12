%{
int v=0;
%}
vowel [aeiouAEIOU]
%%
{vowel} { v++;}
%%

int main()
{
yylex();
printf("no of vowels : %d",v);
}
int yywrap()
{
return 1;
}

