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

%token T_SHIFT_L T_SHIFT_R T_GREATER_E T_LESS_E T_GREATER T_LESS T_EQUAL T_NOT_EQUAL
%token T_NAME T_RETURN T_AND_L T_OR_L
%token T_INT T_FLOAT T_DOUBLE 
%token T_CHAR T_STRING
%token T_UNSIGNED T_STRUCT T_TYPEDEF T_SIZEOF T_ENUM
%token T_INT_VALUE T_FLOAT_VALUE T_DOUBLE_VALUE T_CHAR_VALUE 
%token T_WHILE T_FOR T_SWITCH T_IF T_ELSE T_ELSEIF T_BREAK T_CONTINUE
 
%type <program> program function term unary factor expr add_sub shift_operator relational
%type <program> relational_equal bitwise_and bitwise_or logical_and
%type <statement> statement
%type <statements> statement_list
%type <integer> T_INT_VALUE 
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
               | statement_list statement  { $1->addStatement($2); $$ = $1; }
               ;

statement : T_RETURN expr ';'         { $$ = new Statement('R', $2); }
          | type T_NAME '=' expr ';'  { $$ = new Statement('D', $1, $2, $4); }
          | type T_NAME ';'           { $$ = new Statement('D', $1, $2, 0); }
          | T_NAME '=' expr ';'       { $$ = new Statement('A', $1, $3); }
          | expr ';'                  { $$ = new Statement('E', $1); }
          ;


expr : logical_and              { $$ = $1;}
     | expr T_OR_L logical_and  { $$ = new LogicalOr($1, $3);}
     ; 

logical_and : bitwise_or                      { $$ = $1;}
            | logical_and T_AND_L bitwise_or  { $$ = new LogicalAnd($1, $3);}
            ;

bitwise_or : bitwise_and                 { $$ = $1;}
           | bitwise_or '|' bitwise_and  { $$ = new BitwiseOr($1, $3);}
           ;

bitwise_and : relational_equal                  { $$ = $1;}
            | bitwise_and '&' relational_equal  { $$ = new BitwiseAnd($1, $3);}
            ;

relational_equal : relational                                   { $$ = $1;}
                 | relational_equal T_EQUAL shift_operator      { $$ = new Equal($1, $3, 0); }
                 | relational_equal T_NOT_EQUAL shift_operator  { $$ = new Equal($1, $3, 1); }
                 ;

relational : shift_operator                             { $$ = $1;}
           | shift_operator T_LESS_E shift_operator     { $$ = new LessEqual($1, $3, 1); }
           | shift_operator T_LESS shift_operator       { $$ = new LessEqual($1, $3, 0); }
           | shift_operator T_GREATER_E shift_operator  { $$ = new GreaterEqual($1, $3, 1); }
           | shift_operator T_GREATER shift_operator    { $$ = new GreaterEqual($1, $3, 0); }
           ;

shift_operator : add_sub                           { $$ = $1;}   
               | shift_operator T_SHIFT_L add_sub  { $$ = new ShiftLeft($1, $3); }
               | shift_operator T_SHIFT_R add_sub  { $$ = new ShiftRight($1, $3); }
               ;

add_sub : term              { $$ = $1;}
        | add_sub '+' term  { $$ = new Addition($1, $3); }
        | add_sub '-' term  { $$ = new Subtraction($1, $3); }
        ;

term : unary                { $$ = $1;}
     | term '*' unary       { $$ = new Multiplication($1, $3);}
     | term '/' unary       { $$ = new Division($1, $3);}
     | term '%' unary       { $$ = new Modulus($1, $3);}
     ;

unary : factor              { $$ = $1;}
      | '-' factor          { $$ = $2;}    
      ;   

factor : T_INT_VALUE        { $$ = new Integer($1); }
       | '(' expr ')'       { $$ = $2;}
       | T_NAME             { $$ = new Variable(*$1);}
       | factor '^' unary   { $$ = new Power($1, $3);}
       ;

%%

const Program *root;

const Program *parseAST(FILE *source_file) {
  root = 0;
  yyparse(source_file);
  return root;
}
