#include "ast.hpp"

///////////////////////
// Pointer
///////////////////  
// delete pointer class -- no use for now


AddressOf::AddressOf(ProgramPtr _expression, int _pos){
      left = _expression;
      pos = _pos;
  }
void AddressOf::print(std::ostream &dst, int indentation) const{
        dst << "-";
        dst << "(";
        left->print(dst, indentation);
        dst << ")";
  }
int AddressOf::codeGen(const Binding &_binding, int reg) const{
      //std::cout << "enter addressof " << std::endl;
      printf("\taddiu\t$%d,$fp,%d\n",reg,((Variable*)left)->getPos(binding));
      return 0;
  }
int AddressOf::evaluate(const Binding &_binding) const {
      return 0;
  }
void AddressOf::bind(const Binding &_binding) {
      binding = _binding;
      ((Program*)left)->bind(binding);
  }
void AddressOf::passFunctionName(std::string _name, int _pos){
  pos = pos + _pos;
  function_name = _name;
  }

  void AddressOf::passTypeBinding(TypeBinding &_typebind){
  typebind = _typebind;
  ((Program*)left)->passTypeBinding(_typebind);
}

std::string AddressOf::getVariableType(){
  std::string var_1 = ((Program*)left)->getVariableType();
  if((var_1 == "int")){
    return "int";
  }
  return "no type";
}


  Dereference::Dereference(ProgramPtr _expression, int _pos){
      left = _expression;
      pos = _pos;
      is_write = 0;
      node_type = '*';
      
  }
  void Dereference::print(std::ostream &dst, int indentation) const{

  }
  int Dereference::codeGen(const Binding &_binding, int reg) const{
      //std::cout << "entered here"  << "dereference " << std::endl;
      print_map(binding,"dereference");
      left->codeGen(binding,2);
      printf("\tnop\n");
      printf("\tsw\t$2,%d($fp) # store the value of dereference\n",pos);
      if(is_write == 0){
      printf("\tlw\t$%d,0($2)\n",reg);
      }
      return 0;
  }
  int Dereference::evaluate(const Binding &_binding) const {
      return 0;
  }
  void Dereference::bind(const Binding &_binding) {
      binding = _binding;
      ((Program*)left)->bind(binding);
  }
  void Dereference::passFunctionName(std::string _name, int _pos){
  pos = pos + _pos;
  function_name = _name;
  }
  void Dereference::passTypeBinding(TypeBinding &_typebind){
  typebind = _typebind;
  ((Program*)left)->passTypeBinding(_typebind);
}

void Dereference::read(int _read){
    is_write = _read;
}

std::string Dereference::getVariableType(){
  std::string var_1 = ((Program*)left)->getVariableType();
  if((var_1 == "int")){
    return "int";
  }
  return "no type";
}