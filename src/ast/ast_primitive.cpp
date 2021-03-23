#include <iterator>

#include "ast.hpp"

////////////////////////////////////////
// Integer
////////////////////////////////////////

Integer::Integer(int _value) : value(_value) {
  logger->info("construct Integer\n");
  node_type = 'i';
}

void Integer::print(std::ostream &dst, int indentation) const { dst << value; }

int Integer::evaluate(const Binding &_binding) const { return value; }

int Integer::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for integer\n");
  printf("\tli\t$%d,%d\t\t# load %d\n", reg, value, value);
  return 0;
}

void Integer::bind(const Binding &_binding) {}
void Integer::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
}

void Integer::passTypeBinding(TypeBinding &_typebind){
  typebind = _typebind;
}

std::string Integer::getVariableType(){
  return "int";
}

////////////////////////////////////////
// Variable
////////////////////////////////////////

Variable::Variable(const std::string &_id) : id(_id) {
  logger->info("construct Variable\n");
  node_type = 'x';
}

void Variable::print(std::ostream &dst, int indentation) const { dst << id; }

int Variable::evaluate(const Binding &_binding) const {
  if (_binding.find(id) == _binding.end()) {
    logger->error("%s has not been declared", id.c_str());
    exit(1);
  }
  // return binding.at(id)->evaluate(_binding);
  return 0;
}

int Variable::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for variable\n");
  print_map(binding,"variable");
  if (binding.find(id) == binding.end()) {
    logger->error("\"%s\" has not been declared\n", id.c_str());
    exit(1);
  }
  TypeBinding temp = typebind;
  std::string var_type = temp[id];
  if(var_type == "float"){
    printf("\tlwc1\t$f%d,%d($fp)\n",reg,binding.at(id));
  }
  else{
    printf("\tlw\t$%d,%d($fp)\t# load %s\n", reg, binding.at(id), id.c_str());
  }
  return 0;
}

int Variable::getPos(const Binding &_binding) const {
  if (binding.find(id) == binding.end()) {
    logger->error("\"%s\" has not been declared\n", id.c_str());
    exit(1);
  }
  return binding.find(id)->second;
}

void Variable::bind(const Binding &_binding) {
  binding = _binding;
  logger->debug("binding...variable\n");
}

void Variable::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
}

void Variable::passTypeBinding(TypeBinding &_typebind){
  typebind = _typebind;
}

// get the variable type
std::string Variable::gettype(TypeBinding &_typebind) const{
  return _typebind[id];
}

std::string Variable::getVariableType(){
  return typebind[id];
 }


Char::Char(char _value){
  value = _value;
}

int Char::codeGen(const Binding &_binding, int reg) const{
  logger->info("generate code for char\n");
  printf("\tli\t$%d,%d\t\t# load %d\n", reg, int(value), value);
  return 0;
}
void Char::print(std::ostream &dst, int indentation) const{

}
int Char::evaluate(const Binding &_binding) const{
  return 0;
}
void Char::bind(const Binding &_binding){

}
void Char::passFunctionName(std::string _name, int _pos){
  function_name = _name;
  pos = pos + _pos;
}
void Char::passTypeBinding(TypeBinding &_typebind){

}
std::string Char::getVariableType(){
  return "char";
}