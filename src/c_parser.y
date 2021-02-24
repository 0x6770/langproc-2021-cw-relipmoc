%code requires{
  #include "ast.hpp"
  #include "string"
  #include <cassert>
  #include <map>

  extern const Program *root;
  int yylex(void);
  void yyerror(FILE *source_file, const char *msg);
}

%parse-param { FILE *source_file}

%union{
  int integer;
  std::string *string;
  Statement *statement;
  StatementList *statements;
  ProgramPtr program;
}

%token T_NAME T_RETURN 
%token T_INT T_FLOAT T_DOUBLE 
%token T_CHAR T_STRING
%token T_UNSIGNED T_STRUCT T_TYPEDEF T_SIZEOF T_ENUM
%token T_INT_VALUE T_FLOAT_VALUE T_DOUBLE_VALUE T_CHAR_VALUE 
%token T_WHILE T_FOR T_SWITCH T_IF T_ELSE T_ELSEIF T_BREAK T_CONTINUE
 
%type <program> program function term unary factor expr
%type <statement> statement
%type <statements> statement_list
%type <integer> T_INT_VALUE number
%type <string> type T_NAME T_INT

%left '<' '>' "<=" ">=" "!="
%left '+' '-'
%left '*' '/' '%'
%right '^'

%start program  

%%

type : T_INT  { $$ = $1; }
     ;

program : function  { root = $1; }
        ;

function : type T_NAME '(' ')' '{' statement_list '}'  { $$ = new Function($1, $2, $6); } 
         ;

statement_list : statement                 { $$ = new StatementList($1); }
               | statement_list statement  { if ($2) $1->addStatement($2); $$ = $1; }
               ;

statement : T_RETURN expr ';'         { $$ = new Statement('R', $2); }
          | type T_NAME '=' expr ';'  { }
          | type T_NAME ';'           { $$ = new Statement('A', 0); }
          | T_NAME '=' expr ';'       { }
          | expr ';'                  { $$ = new Statement('E', $1); }
          ;

expr : term          { $$ = $1;}
     | expr '+' term  { $$ = new Addition($1, $3); }
     | expr '-' term  { $$ = new SubOperator($1,$3); }
     ;


term : unary             { $$ = $1;}
    | term '*' unary    { $$ = new MulOperator($1,$3);}
    | term '/' unary    { $$ = new DivOperator($1,$3);}
    | term '%' unary    { $$ = new Modulus($1,$3);}
    ;

unary : factor         { $$ = $1;}
      | '-' factor     { $$ = $2;}    
      ;   

factor : T_INT_VALUE     { $$ = new Integer($1); }
     | '(' expr ')'     { $$ = $2;}
     | T_NAME           { $$ = new Variable(*$1);}
     | factor '^' unary { $$ = new ExpOperator($1,$3);}
     ;

%%

const Program *root;

const Program *parseAST(FILE *source_file) {
  root = 0;
  yyparse(source_file);
  return root;
}
