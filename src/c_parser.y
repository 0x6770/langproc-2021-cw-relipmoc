%code requires{
  #include "ast.hpp"
  #include "string"
  #include <cassert>

  extern const Program *root;
  int yylex(void);
  void yyerror(const char *);
}

%union{
  int integer;
  std::string *string;
  Program *program;
  c_type type;
}

%token T_NAME T_RETURN 
%token T_INT T_FLOAT T_DOUBLE 
%token T_CHAR T_STRING
%token T_UNSIGNED T_STRUCT T_TYPEDEF T_SIZEOF T_ENUM
%token T_INT_VALUE T_FLOAT_VALUE T_DOUBLE_VALUE T_CHAR_VALUE 
%token T_WHILE T_FOR T_SWITCH T_IF T_ELSE T_ELSEIF T_BREAK T_CONTINUE
 
%type <program> program function statement expr type
%type <type> T_INT
%type <integer> T_INT_VALUE number
%type <string> T_NAME 

%left '<' '>' "<=" ">=" "!="
%left '+' '-'
%left '*' '/' '%'
%right '^'

%start program  

%%

type : T_INT { $$ = new Type($1); }
     ;

program : function  { root = $1; }
       ;

function : type T_NAME '(' ')' '{' statement '}' { $$ = new Function($1, $2, $6); } 
         ;

statement : T_RETURN expr ';' { $$ = new Statement($2); }
          ;

number : T_INT_VALUE  { $$ = $1; }
       ;

expr : '(' expr ')'   { $$ = $2; }
     | expr '+' expr  { $$ = $1; }
     | expr '-' expr  { $$ = $1; }
     | expr '*' expr  { $$ = $1; }
     | expr '/' expr  { $$ = $1; }
     | expr '%' expr  { $$ = $1; }
     | expr '^' expr  { $$ = $1; }
     | number         { $$ = new Expression($1); }
     ;

%%

const Program *root;

const Program *parseAST() {
  root = 0;
  yyparse();
  return root;
}
