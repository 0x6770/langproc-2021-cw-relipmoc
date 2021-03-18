#include "ast.hpp"

///////////////////////
// Pointer
//////////////////////

Pointer::Pointer(std::string _name,std::string _type, int _pos){
    name = _name;
    type = _type;
    node_type = 'P';
    logger->info("Construct a Pointer\n");
}

Pointer::Pointer(std::string _name,int _pos){
    name = _name;
    node_type = 'P';
    logger->info("Construct a Pointer\n");
}

void Pointer::print(std::ostream &dst, int indentation) const{

}
int Pointer::codeGen(const Binding &_binding, int reg) const{
    printf("\tlw\t$%d,%d($fp)\t # Pointer %s Load\n",reg,binding.at(name),name.c_str());
    return 0;
}
int Pointer::evaluate(const Binding &_binding) const{
    return 0;
}
void Pointer::bind(const Binding &_binding){
    binding = _binding; 
}

void Pointer::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
}

void Pointer::passTypeBinding(TypeBinding &_typebind){
  
}


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