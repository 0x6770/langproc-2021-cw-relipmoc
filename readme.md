## Token defination

%union{
  const Function *func;
  const Expression *expr;
  int integer;
}

%token T_NAME T_RETURN 
%token T_INT T_INT_VALUE 
%token T_ADD T_MULT T_DIVIDE T_MODE T_EXP 
%token T_AND T_OR T_NOT T_GREATER T_LESS T_EQUAL T_GE T_LE T_NE 
%token T_LAND T_LOR T_LNOT 
%token T_WHILE T_IF T_ELSE T_ELSEIF 
%token T_ASSIGN T_LB T_RB T_LBC T_RBC T_LBS T_RBS 

int main(){}

int a = 10;
double b = 20;

T_INT T_NAME T_ASSIGN T_INT_VALUE
new integer($4)

T_DOUBLE T_NAME T_ASSIGN T_DOUBLE_VALUE
new double($4)
