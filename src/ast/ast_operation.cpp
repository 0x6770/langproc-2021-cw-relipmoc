#include "ast.hpp"

////////////////////////////////////////
// Operation
////////////////////////////////////////

Operation::Operation(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right) {
  logger->info("construct Operation\n");
  pos = _pos;
}

void Operation::print(std::ostream &dst, int indentation) const {}

int Operation::codeGen(const Binding &_binding, int reg) const { return 0; }

int Operation::evaluate(const Binding &_binding) const { return 0; }

void Operation::bind(const Binding &_binding) {
  if (left) ((Program *)left)->bind(_binding);
  if (right) ((Program *)right)->bind(_binding);
}

void Operation::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void Operation::passTypeBinding(TypeBinding &_typebind){
    typebind = _typebind;
  ((Program*)left)->passTypeBinding(typebind); 
  ((Program*)right)->passTypeBinding(typebind); 
}

std::string Operation::getVariableType(){
  std::string var_1 = ((Program*)left)->getVariableType();
  std::string var_2 = ((Program*)right)->getVariableType();
  if((var_1 == "int")&& (var_2 == "int")){
    return "int";
  }
  return "none";
}