%code requires{
  #include <string>
  #include <cassert>
  #include <map>

  #include "ast.hpp"

  extern const Program *root;
  int yylex(void);
  void yyerror(FILE *source_file, const char *msg);
}

%parse-param {FILE *source_file}

%union{
  int integer;
  std::string *string;
  ProgramPtr program;
}

%token T_ADDEQUAL T_SUBEQUAL T_MULEQUAL T_DIVEQUAL T_MODEQUAL 
%token T_SHIFTEQUAL_L T_SHIFTEQUAL_R
%token T_BITWISEEQUAL_AND T_BITWISEEQUAL_OR T_BITWISEEQUAL_XOR
%token T_INCREMENT T_DECREMENT
%token T_SHIFT_L T_SHIFT_R T_GREATER_E T_LESS_E T_GREATER T_LESS T_EQUAL T_NOT_EQUAL
%token T_NAME T_RETURN T_AND_L T_OR_L
%token T_INT T_FLOAT T_DOUBLE 
%token T_CHAR T_STRING
%token T_UNSIGNED T_STRUCT T_TYPEDEF T_SIZEOF T_ENUM
%token T_INT_VALUE T_FLOAT_VALUE T_DOUBLE_VALUE T_CHAR_VALUE 
%token T_WHILE T_FOR T_SWITCH T_IF T_ELSE T_BREAK T_CONTINUE
 
%type <program> program function term unary factor expr add_sub shift_operator relational 
%type <program> relational_equal bitwise_and bitwise_xor bitwise_or logical_and
%type <program> stmt stmt_list stmt_closed stmt_open loop complex_assignment scope param_list param
%type <program> unary_postfix unary_prefix
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

function : type T_NAME '(' ')' scope  { $$ = new Function(*$1, *$2, $5, pos); } 
         | type T_NAME '(' param_list ')' scope  { $$ = new Function(*$1, *$2, $6, pos); } 
         ;

 /* TODO: Implicit param e.g. int f(a, b); */
param_list : param                 { }
           | param_list ',' param  {  }
           ;

param : type T_NAME  { }
        ;
scope : '{' stmt_list '}'  { $$ = $2; }
      ;

stmt_list : %empty                    { $$ = new StatementList(); }
          | stmt_list stmt   { ((StatementList *)$1)->addStatement($2); $$ = $1; }
          | stmt_list scope  { ((StatementList *)$1)->addStatement($2); ((StatementList *)$2)->mergeBinding($1); $$ = $1; }
          ;

stmt : stmt_open    { $$ = $1; }
     | stmt_closed  { $$ = $1; }
     ;

stmt_open : T_IF '(' expr ')' stmt                          { $$ = new IfStatement($3, $5, 0); }
          | T_IF '(' expr ')' stmt_closed T_ELSE stmt_open  { $$ = new IfStatement($3, $5, $7); }
          ;

stmt_closed : T_IF '(' expr ')' stmt_closed T_ELSE stmt_closed  { $$ = new IfStatement($3, $5, $7); }
            | complex_assignment ';'                            { $$ = $1; }
            | type T_NAME                                       { $$ = new VarDeclare(*$1, *$2, 0, pos); }
            | T_RETURN expr ';'                                 { $$ = new Return($2); }
            | loop                                              { $$ = $1; }
            /*| ';'                                               { $$ = new Statement(0); }*/
            ; 

loop : T_WHILE '(' complex_assignment ')' scope          { $$ = new WhileLoop($3, $5); }
     | T_FOR '(' stmt stmt stmt ')' scope  { $$ = new WhileLoop($7, $5); }
     ;

complex_assignment : expr                                          { $$ = $1; }
                   | type T_NAME '=' complex_assignment            { $$ = new VarDeclare(*$1, *$2, $4, pos); }
                   | T_NAME '=' complex_assignment                 { $$ = new VarAssign(*$1, $3); }
                   | factor T_ADDEQUAL complex_assignment          { $$ = new AddEqual($1, $3, pos); }
                   | factor T_SUBEQUAL complex_assignment          { $$ = new SubEqual($1, $3,pos); }
                   | factor T_MULEQUAL complex_assignment          { $$ = new MulEqual($1, $3,pos); }
                   | factor T_DIVEQUAL complex_assignment          { $$ = new QuoEqual($1, $3,pos); }
                   | factor T_MODEQUAL complex_assignment          { $$ = new ModEqual($1, $3,pos); }
                   | factor T_SHIFTEQUAL_L complex_assignment      { $$ = new ShiftEqual_L($1, $3,pos); }
                   | factor T_SHIFTEQUAL_R complex_assignment      { $$ = new ShiftEqual_R($1, $3,pos); }
                   | factor T_BITWISEEQUAL_AND complex_assignment  { $$ = new BitwiseEqual_AND($1, $3,pos); }
                   | factor T_BITWISEEQUAL_OR complex_assignment   { $$ = new BitwiseEqual_OR($1, $3,pos); }
                   | factor T_BITWISEEQUAL_XOR complex_assignment  { $$ = new BitwiseEqual_XOR($1,$3,pos); }
                   ;

expr : logical_and              { $$ = $1; }
     | expr T_OR_L logical_and  { $$ = new LogicalOr($1, $3, pos); pos+=4; }
     ; 

logical_and : bitwise_or                      { $$ = $1; }
            | logical_and T_AND_L bitwise_or  { $$ = new LogicalAnd($1, $3, pos); pos+=4; }
            ;


bitwise_or : bitwise_xor                 { $$ = $1; }
           | bitwise_or '|' bitwise_and  { $$ = new BitwiseOr($1, $3, pos); pos+=4; }
           ;

bitwise_xor : bitwise_and                 { $$ = $1; }
            | bitwise_xor '^' bitwise_and { $$ = new BitwiseXor($1,$3,pos); pos+=4;} 

bitwise_and : relational_equal                  { $$ = $1;}
            | bitwise_and '&' relational_equal  { $$ = new BitwiseAnd($1, $3, pos); pos+=4;}
            ;

relational_equal : relational                                   { $$ = $1;}
                 | relational_equal T_EQUAL shift_operator      { $$ = new Equal($1, $3, 0, pos); pos+=4; }
                 | relational_equal T_NOT_EQUAL shift_operator  { $$ = new Equal($1, $3, 1, pos); pos+=4; }
                 ;

relational : shift_operator                             { $$ = $1;}
           | shift_operator T_LESS_E shift_operator     { $$ = new LessEqual($1, $3, 1, pos); pos+=4; }
           | shift_operator T_LESS shift_operator       { $$ = new LessEqual($1, $3, 0, pos); pos+=4; }
           | shift_operator T_GREATER_E shift_operator  { $$ = new GreaterEqual($1, $3, 1, pos); pos+=4; }
           | shift_operator T_GREATER shift_operator    { $$ = new GreaterEqual($1, $3, 0, pos); pos+=4; }
           ;

shift_operator : add_sub                           { $$ = $1;}   
               | shift_operator T_SHIFT_L add_sub  { $$ = new ShiftLeft($1, $3, pos); pos+=4; }
               | shift_operator T_SHIFT_R add_sub  { $$ = new ShiftRight($1, $3, pos); pos+=4; }
               ;

add_sub : term              { $$ = $1; }
        | add_sub '+' term  { $$ = new Addition($1, $3, pos); pos+=4; }
        | add_sub '-' term  { $$ = new Subtraction($1, $3, pos); pos+=4; }
        ;

term : unary                { $$ = $1; }
     | term '*' unary       { $$ = new Multiplication($1, $3, pos); pos+=4; }
     | term '/' unary       { $$ = new Division($1, $3, pos); pos+=4; }
     | term '%' unary       { $$ = new Modulus($1, $3, pos); pos+=4; }
     ;

unary : unary_prefix              { $$ = $1;}
      | '-' unary_prefix          { $$ = $2;}    
      ;   

unary_prefix : unary_postfix                   { $$ = $1;}
             | T_INCREMENT unary_prefix        { $$ = new Increment_Pre($2); }
             | T_DECREMENT unary_prefix        { $$ = new Decrement_Pre($2); }

unary_postfix : factor                         { $$ = $1;}
              | unary_postfix T_INCREMENT      { $$ = new Increment_Post($1);}
              | unary_postfix T_DECREMENT      { $$ = new Decrement_Post($1);}

factor : T_INT_VALUE        { $$ = new Integer($1); }
       | '(' expr ')'       { $$ = $2;}
       | T_NAME             { $$ = new Variable(*$1);}
       ;

%%

const Program *root;

const Program *parseAST(FILE *source_file) {
  root = 0;
  yyparse(source_file);
  return root;
}

int pos = 0;
