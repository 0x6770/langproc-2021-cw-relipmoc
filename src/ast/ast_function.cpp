#include "ast.hpp"

////////////////////////////////////////
// Function
////////////////////////////////////////

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   int _pos, int _call , int _argu_number)
    : type(_type), name(_name), statements(_statements) {
  int tmp_size = _pos + 8;
  tmp_size = tmp_size + (_argu_number)*4 + 4;
  // free space for the number of arguments;
  if(_call == 1)  tmp_size = tmp_size+4;
  // add 4 for store the value in $ra when there is function call in the function;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  // size = size + 16;
  logger->info("construct Function with no arguments\n");
  node_type = 'F';
  passFunctionName(_name,_argu_number*4);
  with_function_call = _call;
  argu_size = _argu_number;
  //std::cout << _argu_number << std::endl;
  //if(_statements == 0){is_define = 1;}
}

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   ProgramPtr _Arguments, int _pos, int _call,int _argu_number) {
  type = _type;
  statements = _statements;
  Arguments = _Arguments;
  int tmp_size = _pos + 8;
  tmp_size = tmp_size + (_argu_number)*4 + 4;
  if(_call == 1)  tmp_size = tmp_size+4;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  //size = size + 16;
  logger->info("construct Function with arguments\n");
  node_type = 'F';
  with_param = 1;
  // std::string function_name = _name + "_" + ((Paramlist*)Arguments)->get_type_string();
  name = _name;
  passFunctionName(_name,_argu_number*4);
  with_function_call = _call;
  argu_size = _argu_number;
  //if(_statements == 0){is_define = 1;}
  //std::cout << _argu_number << std::endl;
}

void Function::print(std::ostream &dst, int indentation) const {
  logger->info("====================\n");
  logger->info("formatted: \n");
  printIndent(dst, indentation);
  dst << type;
  dst << " ";
  dst << name;
  dst << "(";
  if (with_param == 1) {
    Arguments->print(dst, indentation);
  }
  dst << ") {\n";
  
  statements->print(dst, indentation);
  dst << "}";
}

int Function::evaluate(const Binding &_binding) const {
  return statements->evaluate(binding);
  return 0;
}

int Function::codeGen(const Binding &_binding, int reg) const {

  logger->info("====================\n");
  logger->info("Build variable mapping in Function\n");
  Binding container;
  Binding temp;
  // when the function has arguments up-to four
  if (with_param == 1) {
    temp = ((Paramlist *)Arguments)->return_bind(container, size);
    ((StatementList *)statements)->bind(temp);
  } else {
    ((StatementList *)statements)->bind(binding);
  }
  // make unique end label:

  std::string function_end = "end" + name;
  logger->info("====================\n");
  logger->info("generate code for Function\n");
  logger->info("size of stack frame: %d\n", getSize());
  //printf(".text\n");
  //printf(".align\t2\n");
  //printf(".set\tnomips16\n");
  //printf(".set\tnomicromips\n");
  //printf(".cpload $25\n");
  //printf(".ent\t%s\n",name.c_str());
  //printf(".cprestore %d\n",argu_size*4+4);
  printf(".global\t%s\n", name.c_str());
  //printf(".ent\t%s\n", name.c_str());
  printf("\n");
  printf("%s:\n", name.c_str());
  //printf("\t.cprestore %d\n",argu_size*4+4);
  //printf("\t.frame $fp,%d,$31\n",size);
  //printf("\t.mask 0xc0000000,-4\n");
  //printf("\t.fmask 0x00000000,0\n");
  //printf(".set\tnomacro\n");
  //printf(".set\tnoreoder\n");
  // printf(".frame\t$fp,%d,$31\n", size);
  printf("\taddiu\t$sp,$sp,%d\n", -size);
  if(with_function_call == 1){
  printf("\tsw\t$31,%d($sp)\n", (size - 4));
  printf("\tsw\t$fp,%d($sp)\n", (size - 8));
  }
  else{
    printf("\tsw\t$fp,%d($sp)\n", (size - 4));
  }
  printf("\tmove\t$fp,$sp\n");
  // store the values in the register a0-a3 in the stack.
  if (with_param == 1) {
    Arguments->codeGen(temp, 2);
  }
  statements->codeGen(binding, 2);  // store  result result of to $2
  printf("%s",function_end.c_str());
  printf(":\t\t\t\t# \033[1;036m[LABEL]\033[0m end of function\n");
  // TODO: return statement to determine the label part
  printf("\tmove\t$sp,$fp\n");
  if(with_function_call==1){
  printf("\tlw\t$31,%d($sp)\n", (size - 4));
  printf("\tlw\t$fp,%d($sp)\n", (size - 8));
  }
  else{
    printf("\tlw\t$fp,%d($sp)\n", (size - 4));
  }
  printf("\taddiu\t$sp,$sp,%d\n", size);
  printf("\tjr\t$31\n");
  printf("\tnop\n");
  printf("\n");
  
  //printf(".set\tmacro\n");
 // printf(".set\treorder\n");
  //printf(".end\t%s\n",name.c_str());
  // printf(".end\t%s\n", name.c_str());
  return 0;
}

void Function::bind(const Binding &_binding) {}

void Function::passFunctionName(std::string _name,int _pos){
  ((Program*)statements)->passFunctionName(_name,_pos);
}

MultiFunction::MultiFunction(ProgramPtr _function){
  logger->info("construct one function");
  functoins.push_back(_function);
}

void MultiFunction::add_function(ProgramPtr _function){
  logger->info("construct more functions");
  functoins.push_back(_function);
}

void MultiFunction::print(std::ostream &dst, int indentation) const {

}
int MultiFunction::codeGen(const Binding &_binding, int reg) const {
  for(auto it:functoins){
    ((Program*)it)->codeGen(binding,2);
  }
  return 0;
}
int MultiFunction::evaluate(const Binding &_binding) const {
  return 0;
}

void MultiFunction::bind(const Binding &_binding){

}

void MultiFunction::passFunctionName(std::string _name,int _pos){

}

Param::Param(std::string _type, std::string _name) {
  logger->info("construct one parameter\n");
  type = _type;
  name = _name;
}

void Param::print(std::ostream &dst, int indentation) const {
  dst << type << " " << name << " ";
}

int Param::codeGen(const Binding &_binding, int reg) const { return 0; }

int Param::evaluate(const Binding &_binding) const { return 0; }

void Param::bind(const Binding &_binding) {}

void Param::passFunctionName(std::string _name,int _pos){}

std::string Param::getName(){
  return name;
}

Binding Param::return_bind(Binding &_binding, int pos) {
  _binding[name] = pos;
  return _binding;
}

std::string Param::getType(){
  return type;
}

Paramlist::Paramlist() {
  // do nothing;
  logger->info("Build an empty parameter list\n");
}

Paramlist::Paramlist(ProgramPtr argument) {
  parameters.push_back(argument);
  logger->info("construct paramlist with on param\n");
}

void Paramlist::add_argument(ProgramPtr argument) {
  parameters.push_back(argument);
}

void Paramlist::print(std::ostream &dst, int indentation) const {
  for (auto it : parameters) {
    ((Param *)it)->print(dst, indentation);
  }
}

int Paramlist::codeGen(const Binding &_binding, int reg) const {
  std::string key;
  int value = 0;
  int regtemp = 4;
  
  int count = 1;
  for (auto it : _binding) {
    if(count<=4){
    key = it.first;
    value = it.second;
    printf("\tsw \t$%d,%d($fp)\n", regtemp, value);
    regtemp = regtemp + 1;
    count = count + 1;
    }
  }

  return 0;
}

int Paramlist::evaluate(const Binding &_binding) const { return 0; }

void Paramlist::bind(const Binding &_binding) {}

Binding Paramlist::return_bind(const Binding &_binding, int _pos) {
  Binding result;
  Binding temp;
  int n = _pos;
  int counter = 1;
  std::string tmp_string;
  for (auto it : parameters) {
    if(counter <= 4){
    result = ((Param *)it)->return_bind(temp, n);
    n = n + 4;
    counter = counter + 1;}
    else{
      tmp_string = ((Param*)it)->getName();
      result[tmp_string] = n;
      n = n + 4;
    }
  }
  binding = result;
  return result;
}


std::string Paramlist::get_type_string(){
  std::string name = ((Param*)parameters[0])->getType();
  int n = parameters.size();
  name = name + "_"+ std::to_string(n);
  return name;
}

void Paramlist::passFunctionName(std::string _name,int _pos){
  pos = pos + _pos;
}

FunctionCall::FunctionCall(std::string _name,int _pos){
  name = _name;
  pos = _pos;
  logger->info("construct function NO arguments");
  with_argument = 0;
}


FunctionCall::FunctionCall(std::string _name, ProgramPtr _argument,int _pos){
  logger->info("construct function call with arguments");
  name = _name;
  pos = _pos;
  expression_list = _argument;
  with_argument = 1;
}
void FunctionCall::add_Arguments(ProgramPtr _Argument){
  //arguments.push_back(_Argument);

} 
void FunctionCall::print(std::ostream &dst, int indentation) const{
  
}

// assuming all variable types are int for now
int FunctionCall::codeGen(const Binding &_binding, int reg) const {
  //int pos = 20;
  if(with_argument == 1){
  ((Program*)expression_list)->codeGen(binding,2);}
 // printf("\t.cprestore 20\n");
  printf("\t jal %s\n",name.c_str());
  printf("\tnop\n");
  printf("\tsw\t$2,%d($fp)    # store the value after function call\n",pos);  
  return 0;
}
int FunctionCall::evaluate(const Binding &_binding) const {
  return 0;
}
void FunctionCall::bind(const Binding &_binding) {
  binding = _binding;
   if(with_argument == 1){
  ((Program*)expression_list)->bind(binding);}
}

void FunctionCall::passFunctionName(std::string _name,int _pos){
  pos = pos + _pos;
}

ExpressionList::ExpressionList(ProgramPtr _argument){
  logger->info("Build expression list\n");
  arguments.push_back(_argument);
}
void ExpressionList::add_argument_expression(ProgramPtr _expr){
  logger->info("add more expr\n");
  arguments.push_back(_expr);
}
void ExpressionList::print(std::ostream &dst, int indentation) const{
  for(auto it: arguments){
    it->print(dst,indentation);
  }
}
int ExpressionList::codeGen(const Binding &_binding, int reg) const{
  int reg_temp = 4;
  int temp_location = 16;

  if(arguments.size()>4){
    for(unsigned int j = 4; j < arguments.size();j++){
      ((Program*)arguments[j])->codeGen(binding,2);
      printf("\t sw $2,%d($fp)\n",temp_location);
      temp_location = temp_location + 4;
    }
  }

  for(unsigned int i = 0; i< 4; i++){
    if(i < arguments.size()){
    ((Program*)arguments[i])->codeGen(binding,2);
    printf("\t move $%d,$2\n",reg_temp);
    reg_temp = reg_temp + 1;}
  }
  return 0;
}
int ExpressionList::evaluate(const Binding &_binding) const {
  return 0;
}
void ExpressionList::bind(const Binding &_binding) {
  binding = _binding;
  for(auto it: arguments){
    ((Program*)it)->bind(binding);
  }
}

void ExpressionList::passFunctionName(std::string _name,int _pos){
  pos = pos + _pos;
}

FunctionDeclare::FunctionDeclare(std::string _name){
  name = _name;
}

FunctionDeclare::FunctionDeclare(std::string _name,ProgramPtr _param_list){
  name = _name;
  parameters = _param_list;
}
void FunctionDeclare::print(std::ostream &dst, int indentation) const{

}
int FunctionDeclare::codeGen(const Binding &_binding, int reg) const{
  return 0;
}
int FunctionDeclare::evaluate(const Binding &_binding) const{
  return 0;
}
void FunctionDeclare::bind(const Binding &_binding) {

}


void FunctionDeclare::passFunctionName(std::string _name,int _pos){}