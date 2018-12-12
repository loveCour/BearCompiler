%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[0-9]+    { yylval.ival = atoi(yytext); return(CONSTANT); }
[a-zA-Z_][a-zA-Z_0-9]*  { yylval.sval = strdup(yytext); return(ID); }
"else"		{ return (ELSE); }
"if"			{ return(IF); }
"int"			{ return(INT); }
"return"	{ return(RETURN); }
"list"		{ return(LIST); }
"void"		{ return(VOID); }
"while"		{ return(WHILE); }
"<="		{ return(LE_OP); }
">="		{ return(GE_OP); }
"=="		{ return(EQ_OP); }
"!="		{ return(NE_OP); }
";"			{ return(';'); }
"{"		  { return('{'); }
"}" 	  { return('}'); }
","			{ return(','); }
"="			{ return('='); }
"("			{ return('('); }
")"			{ return(')'); }
("[")		{ return('['); }
("]")		{ return(']'); }
"-"			{ return('-'); }
"+"			{ return('+'); }
"*"			{ return('*'); }
"/"			{ return('/'); }
"<"			{ return('<'); }
">"			{ return('>'); }
"^"			{ return('^'); }

[ \t\v\n\f]		{ ; }
.			{ /* ignore bad characters */ }

%%

yywrap()
{
	return(1);
}
