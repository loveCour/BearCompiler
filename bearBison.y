%{
    #include stdio.h
    #include "ast.h"
    int yyerror(const char *msg), yylex();
%}
%union {
    int* pval;
    int ival;

    int* opval;
    int* sval;
}
/***********************************************************
%type  <pval>  Begin
%type  <pval>  Def DParams
%type  <pval>  Statelist State
%type  <pval>  Decl Initdecl
%type  <pval>  Assign
%type  <pval>  Listelem Initlist
%type  <pval>  Brackets
%type  <pval>  Fact
%type  <pval>  ArithMD ArithAM
%type  <pval>  CompE CompG
%type  <pval>  Params
%type  <pval>  Unary
********************************************************/

%token ELSE IF INT RETURN VOID WHILE
%token LE_OP GE_OP EQ_OP NE_OP
%token <sval>  ID
%token <ival>  CONSTANT
%token LIST

%%

Begin : Begin Initdecl
      | Begin Def
      | Initdecl
      | Def
      ;

Def :  INT ID  '(' DParams ')' '{' State RETURN Assign ';' '}'
     | LIST ID  '(' DParams  ')' '{' State RETURN Assign ';' '}'
     | VOID ID  '(' DParams  ')' '{' State '}'
     | INT ID  '(' ')' '{' State RETURN Assign ';' '}'
     | LIST ID  '(' ')' '{' State RETURN Assign ';' '}'
     | VOID ID  '(' ')' '{' State '}'
     ;

DParams : DParams ',' INT ID
        | DParams ',' LIST ID
        | INT ID
        | LIST ID
        ;

State : IF '('  Assign  ')' State
      | IF '('  Assign  ')' State  ELSE State
      | WHILE '('  Assign  ')' State
      | '{' Statelist '}'
      | Assign ';'
      | '^' Listelem ';'
      | Initdecl ';'
      | ';'
      ;

Statelist : Statelist  State
          | State
          ;

Initdecl : Decl  '=' Init
         | Decl
         ;

Decl : INT ID
     | LIST ID
     | INT ID  Brackets
     | LIST ID  Brackets
     ;


Init  : '{' Initlist  '}'
      | '{' Initlist  ','  '}'
      | Assign
      ;

Initlist  : Initlist  ',' Init
          | Init
          ;

Brackets  : Brackets '[' CONSTANT  ']'
          | '[' CONSTANT  ']'
          ;

Assign  : Assign  '=' CompG
        | CompG
        ;

Listelem  : ID  Brackets
          ;

CompG : CompG  '>'  CompE
      | CompG  '<'  CompE
      | CompG  GE_OP CompE
      | CompG  LE_OP CompE
      | CompE
      ;

CompE : CompE NE_OP ArithAM
      | CompE EQ_OP ArithAM
      | ArithAM
      ;

ArithAM : ArithAM  '+' ArithMD
        | ArithAM  '-' ArithMD
        | ArithMD
        ;

ArithMD : ArithMD  '*' Unary
        | ArithMD  '/' Unary
        | Unary
        ;

Unary : '-' Fact
      | Fact
      ;

Fact  : CONSTANT
      | ID
      | Listelem
      | ID  '(' Params  ')'
      | ID  '(' ')'
      | '(' Assign ')'
      ;

Params  : Params ',' Unary
        | Unary
        ;


%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg) { fputs(msg, stderr); }
