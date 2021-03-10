%code requires{
  #include <string>
  #include <cassert>
  #include <map>

  #include "ast.hpp"

  extern const Program *root;
  int yylex(void);
  void yyerror(FILE *source_file, const char *msg);
  int getPos(int size);
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
%token T_COMMA
 
%type <program> program function term unary factor expr add_sub shift_operator relational 
%type <program> relational_equal bitwise_and bitwise_xor bitwise_or logical_and param_list param
%type <program> stmt stmt_list loop assignment control_flow_if multiple_function
%type <program> unary_postfix unary_prefix array_declare expression_list function_call function_define
%type <integer> T_INT_VALUE 
%type <string> type T_NAME T_INT

%start program  

%%

type : T_INT  { $$ = $1; }
     ;

program : multiple_function  { root = $1; }
        ;

multiple_function : function     { $$ = new MultiFunction($1); pos = 0;}
                  | multiple_function function { ((MultiFunction*)$$)->add_function($2); pos=0; }

function : type T_NAME '(' ')' stmt             { $$ = new Function(*$1, *$2, $5, pos, call,number_argu);  call = 0;} 
         | type T_NAME '(' param_list ')' stmt  { $$ = new Function(*$1, *$2, $6, $4, pos, call,number_argu); call = 0;} 
         | function_define                      { $$ = $1;}
         ;

function_define : type T_NAME '(' param_list ')' ';' { $$ = new FunctionDeclare(*$2,$4); }
                | type T_NAME '(' ')' ';'               { $$ = new FunctionDeclare(*$2); }

 /* TODO: Implicit param e.g. int f(a, b); */
param_list : param            { 
             $$ = new Paramlist($1);
          } 
          | param_list T_COMMA type T_NAME   {
             Param* temp = new Param("int",*$4);
             ((Paramlist*)$$)->add_argument(temp);
          }
          
          ;



param : type T_NAME  { $$ = new Param("int",*$2); }
      ;

/*scope : '{' stmt_list '}'  { $$ = $2; }*/
      /*;*/

stmt_list : %empty              { $$ = new StatementList(); }
          | stmt_list stmt      { ((StatementList *)$1)->addStatement($2); $$ = $1; }
          ;
stmt : control_flow_if                     { $$ = $1; }
     | assignment ';'                      { $$ = $1; }
     | type T_NAME ';'                     { $$ = new VarDeclare(*$1, *$2, 0, getPos(4)); delete $1; delete $2; }
     | type T_NAME '=' assignment ';'      { $$ = new VarDeclare(*$1, *$2, $4, getPos(4)); delete $1; delete $2;}
     | T_RETURN expr ';'                   { $$ = new Return($2); }
     | loop                                { $$ = $1; }
     | '{' stmt_list '}'                   { $$ = $2; }
     | array_declare                       { $$ = $1; }
     //| function_call                       { $$ = $1; }
     ; 


array_declare : type T_NAME '[' T_INT_VALUE ']' ';'  { $$ = new Array(*$1,$4,*$2, getPos(4)); pos+=(4*$4);delete $1; delete $2;}

loop : T_WHILE '(' assignment ')' stmt { $$ = new WhileLoop($3, $5); }
     /*| T_FOR '(' stmt stmt stmt ')' scope        { $$ = new WhileLoop($7, $5); }*/
     ;

control_flow_if : T_IF '(' expr ')' stmt              { $$ = new IfStatement($3, $5, 0, label++); }
                | T_IF '(' expr ')' stmt T_ELSE stmt  { $$ = new IfStatement($3, $5, $7, label++); }
                ;

assignment : expr                                  { $$ = $1; }
           | T_NAME '=' assignment                 { $$ = new VarAssign(*$1, $3); }
           | unary_postfix '=' assignment          { ((ArrayElement*)$1)->array_assignment($3); $$ = $1;}
           | factor T_ADDEQUAL assignment          { $$ = new AddEqual($1, $3, getPos(4)); }
           | factor T_SUBEQUAL assignment          { $$ = new SubEqual($1, $3, getPos(4)); }
           | factor T_MULEQUAL assignment          { $$ = new MulEqual($1, $3, getPos(4)); }
           | factor T_DIVEQUAL assignment          { $$ = new QuoEqual($1, $3, getPos(4)); }
           | factor T_MODEQUAL assignment          { $$ = new ModEqual($1, $3, getPos(4)); }
           | factor T_SHIFTEQUAL_L assignment      { $$ = new ShiftEqual_L($1, $3, getPos(4)); }
           | factor T_SHIFTEQUAL_R assignment      { $$ = new ShiftEqual_R($1, $3, getPos(4)); }
           | factor T_BITWISEEQUAL_AND assignment  { $$ = new BitwiseEqual_AND($1, $3, getPos(4)); }
           | factor T_BITWISEEQUAL_OR assignment   { $$ = new BitwiseEqual_OR($1, $3, getPos(4)); }
           | factor T_BITWISEEQUAL_XOR assignment  { $$ = new BitwiseEqual_XOR($1, $3, getPos(4)); }
           ;


expr : logical_and              { $$ = $1; }
     | expr T_OR_L logical_and  { $$ = new LogicalOr($1, $3, getPos(4)); }
     ; 

logical_and : bitwise_or                      { $$ = $1; }
            | logical_and T_AND_L bitwise_or  { $$ = new LogicalAnd($1, $3, getPos(4)); }
            ;


bitwise_or : bitwise_xor                 { $$ = $1; }
           | bitwise_or '|' bitwise_and  { $$ = new BitwiseOr($1, $3, getPos(4)); }
           ;

bitwise_xor : bitwise_and                 { $$ = $1; }
            | bitwise_xor '^' bitwise_and { $$ = new BitwiseXor($1, $3, getPos(4)); } 

bitwise_and : relational_equal                  { $$ = $1;}
            | bitwise_and '&' relational_equal  { $$ = new BitwiseAnd($1, $3, getPos(4)); }
            ;

relational_equal : relational                                   { $$ = $1;}
                 | relational_equal T_EQUAL shift_operator      { $$ = new Equal($1, $3, getPos(4), 0); }
                 | relational_equal T_NOT_EQUAL shift_operator  { $$ = new Equal($1, $3, getPos(4), 1); }
                 ;

relational : shift_operator                             { $$ = $1;}
           | shift_operator T_LESS_E shift_operator     { $$ = new LessEqual($1, $3, getPos(4), 1); }
           | shift_operator T_LESS shift_operator       { $$ = new LessEqual($1, $3, getPos(4), 0); }
           | shift_operator T_GREATER_E shift_operator  { $$ = new GreaterEqual($1, $3, getPos(4), 1); }
           | shift_operator T_GREATER shift_operator    { $$ = new GreaterEqual($1, $3, getPos(4), 0); }
           ;

shift_operator : add_sub                           { $$ = $1;}   
               | shift_operator T_SHIFT_L add_sub  { $$ = new ShiftLeft($1, $3, getPos(4)); }
               | shift_operator T_SHIFT_R add_sub  { $$ = new ShiftRight($1, $3, getPos(4)); }
               ;

add_sub : term              { $$ = $1; }
        | add_sub '+' term  { $$ = new Addition($1, $3, getPos(4)); }
        | add_sub '-' term  { $$ = new Subtraction($1, $3, getPos(4)); }
        ;

term : unary                { $$ = $1; }
     | term '*' unary       { $$ = new Multiplication($1, $3, getPos(4)); }
     | term '/' unary       { $$ = new Division($1, $3, getPos(4)); }
     | term '%' unary       { $$ = new Modulus($1, $3, getPos(4)); }
     ;

unary : unary_prefix      { $$ = $1; }
      | '-' unary_prefix  { $$ = new Negation($2, getPos(4)); }
      ;

unary_prefix : unary_postfix                   { $$ = $1;}
             | T_INCREMENT unary_prefix        { $$ = new Increment_Pre($2, getPos(4)); }
             | T_DECREMENT unary_prefix        { $$ = new Decrement_Pre($2, getPos(4)); }


unary_postfix : factor                         { $$ = $1;}
              | unary_postfix T_INCREMENT      { $$ = new Increment_Post($1, getPos(4)); }
              | unary_postfix T_DECREMENT      { $$ = new Decrement_Post($1, getPos(4)); }

factor : T_INT_VALUE        { $$ = new Integer($1); }
       | '(' expr ')'       { $$ = $2;}
       | T_NAME             { $$ = new Variable(*$1);}
       | T_NAME '[' expr ']'         { $$ = new ArrayElement($3,*$1);}
       | function_call      { $$ = $1; }
       ;

function_call :  T_NAME '(' expression_list ')'    { $$ = new FunctionCall(*$1,$3,getPos(4)); call =1;}
              | T_NAME  '(' ')'                    { $$ = new FunctionCall(*$1,getPos(4)); call = 1;
                                                     number_argu = 0;
                                                    }

expression_list : expr                             { $$ = new ExpressionList($1); number_argu = number_argu +1;}
                | expression_list T_COMMA expr     { //ExpressionList* temp = new ExpressionList($1);
                                                   ((ExpressionList*)$1)->add_argument_expression($3); $$ = $1;
                                                     number_argu = number_argu +1;
                                                    }


%%

const Program *root;

const Program *parseAST(FILE *source_file) {
  root = 0;
  yyparse(source_file);
  return root;
}

int pos = 0;
int label = 0;
int call = 0;
int number_argu = 0;
