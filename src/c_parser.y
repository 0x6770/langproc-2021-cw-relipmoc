%code requires{
  #include "ast.hpp"
  #include "string"
  #include <cassert>

  int yylex(void);
  void yyerror(const char *);
}

%union{
  int integer;
  std::string *string;
}

%token T_NAME T_RETURN 
%token T_INT T_FLOAT T_DOUBLE 
%token T_CHAR T_STRING
%token T_UNSIGNED T_STRUCT T_TYPEDEF T_SIZEOF T_ENUM
%token T_INT_VALUE T_FLOAT_VALUE T_DOUBLE_VALUE T_CHAR_VALUE 
%token T_ADD T_SUB T_MUL T_DIV T_MOD T_EXP 
%token T_AND T_OR T_NOT T_GREATER T_LESS T_EQUAL T_GE T_LE T_NE 
%token T_LAND T_LOR T_LNOT 
%token T_WHILE T_FOR T_SWITCH T_IF T_ELSE T_ELSEIF T_BREAK T_CONTINUE
%token T_ASSIGN T_LB T_RB T_LBC T_RBC T_LBS T_RBS T_SEMI

/*%type <expr> expr */
/*%type <integer> T_INT */

%left T_GREATER T_LESS T_LE T_GE T_NE 
%left T_ADD T_SUB 
%left T_MUL T_DIV T_MOD 
%right T_POW 

%start progam  

%%

type : T_INT 
     ;

progam : function  
       ;

function : type T_NAME T_LB T_RB T_LBC statement T_RBC 
         ;

statement : T_RETURN expr T_SEMI
          ;

number : T_INT_VALUE
       | T_FLOAT_VALUE 
       | T_DOUBLE_VALUE 
       ;

expr : T_LB expr T_RB
     | expr T_ADD expr 
     | expr T_SUB expr 
     | expr T_MUL expr 
     | expr T_DIV expr 
     | expr T_MOD expr 
     | expr T_EXP expr 
     | number 
     ;

%%

const Program *root;

const Program *parseAST() {
 root = 0;
 yyparse();
 return root;
}
