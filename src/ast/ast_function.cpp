#include "ast.hpp"

////////////////////////////////////////
// Function
////////////////////////////////////////

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   int _pos)
    : type(_type), name(_name), statements(_statements) {
  int tmp_size = _pos + 8;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  // size = size + 16;
  logger->info("construct Function\n");
  node_type = 'F';
  passFunctionName(_name);
}

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   ProgramPtr _Arguments, int _pos) {
  type = _type;
  statements = _statements;
  Arguments = _Arguments;
  int tmp_size = _pos + 8;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  //size = size + 16;
  logger->info("construct Function with arguments\n");
  node_type = 'F';
  with_param = 1;
  // std::string function_name = _name + "_" + ((Paramlist*)Arguments)->get_type_string();
  name = _name;
  //std::cout << name << std::endl;
  passFunctionName(_name);
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
  printf(".globl\t%s\n", name.c_str());
  // printf(".ent\t%s\n", name.c_str());
  printf("\n");
  printf("%s:\n", name.c_str());
  // printf(".frame\t$fp,%d,$31\n", size);
  printf("\taddiu\t$sp,$sp,%d\n", -size);
  printf("\tsw\t$fp,%d($sp)\n", (size - 4));
  printf("\tmove\t$fp,$sp\n");
  // store the values in the register a0-a3 in the stack.
  if (with_param == 1) {
    Arguments->codeGen(temp, 2);
  }
  statements->codeGen(binding, 2);  // store  result result of to $2
  std::cout << function_end;
  printf(":\t\t\t\t# \033[1;036m[LABEL]\033[0m end of function\n");
  // TODO: return statement to determine the label part
  printf("\tmove\t$sp,$fp\n");
  printf("\tlw\t$fp,%d($sp)\n", (size - 4));
  printf("\taddiu\t$sp,$sp,%d\n", size);
  printf("\tjr\t$31\n");
  printf("\tnop\n");
  printf("\n");

  // printf(".end\t%s\n", name.c_str());
  return 0;
}

void Function::bind(const Binding &_binding) {}

void Function::passFunctionName(std::string _name){
  ((Program*)statements)->passFunctionName(_name);
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
    ((Function*)it)->codeGen(binding,2);
  }
  return 0;
}
int MultiFunction::evaluate(const Binding &_binding) const {
  return 0;
}

void MultiFunction::bind(const Binding &_binding){

}

void MultiFunction::passFunctionName(std::string _name){

}

Param::Param(std::string _type, std::string _name) {
  type = _type;
  name = _name;
  // std::cout << "construct Param" << std::endl;
}

void Param::print(std::ostream &dst, int indentation) const {
  dst << type << " " << name << " ";
}

int Param::codeGen(const Binding &_binding, int reg) const { return 0; }

int Param::evaluate(const Binding &_binding) const { return 0; }

void Param::bind(const Binding &_binding) {}

void Param::passFunctionName(std::string _name){}

Binding Param::return_bind(Binding &_binding, int pos) {
  _binding[name] = pos;
  return _binding;
}

std::string Param::getType(){
  return type;
}

Paramlist::Paramlist() {
  // do nothing;
}

Paramlist::Paramlist(ProgramPtr argument) {
  parameters.push_back(argument);
  // std::cout << "only one argument" << std::endl;
}

void Paramlist::add_argument(ProgramPtr argument) {
  parameters.push_back(argument);
  // std::cout << "add one more argument" << std::endl;
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
  for (auto it : _binding) {
    key = it.first;
    value = it.second;
    printf("sw $%d,%d($fp)\n", regtemp, value);
    regtemp = regtemp + 1;
  }
  return 0;
}

int Paramlist::evaluate(const Binding &_binding) const { return 0; }

void Paramlist::bind(const Binding &_binding) {}

Binding Paramlist::return_bind(const Binding &_binding, int pos) {
  Binding result;
  Binding temp;
  int n = pos;
  for (auto it : parameters) {
    result = ((Param *)it)->return_bind(temp, n);
    n = n + 4;
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

void Paramlist::passFunctionName(std::string _name){}

FunctionCall::FunctionCall(std::string _name, ProgramPtr _argument){
  logger->info("construct function call");
  name = _name;
}
void FunctionCall::add_Arguments(ProgramPtr _Argument){
  //arguments.push_back(_Argument);

} 
void FunctionCall::print(std::ostream &dst, int indentation) const{

}

// assuming all variable types are int for now
int FunctionCall::codeGen(const Binding &_binding, int reg) const {
  return 0;
}
int FunctionCall::evaluate(const Binding &_binding) const {
  return 0;
}
void FunctionCall::bind(const Binding &_binding) {

}

void FunctionCall::passFunctionName(std::string _name){}

ExpressionList::ExpressionList(ProgramPtr _argument){
  arguments.push_back(_argument);
}
void ExpressionList::add_argument_expression(ProgramPtr _expr){
  arguments.push_back(_expr);
}
void ExpressionList::print(std::ostream &dst, int indentation) const{
  for(auto it: arguments){
    it->print(dst,indentation);
  }
}
int ExpressionList::codeGen(const Binding &_binding, int reg) const{
  return 0;
}
int ExpressionList::evaluate(const Binding &_binding) const {
  return 0;
}
void ExpressionList::bind(const Binding &_binding) {

}

void ExpressionList::passFunctionName(std::string _name){}
