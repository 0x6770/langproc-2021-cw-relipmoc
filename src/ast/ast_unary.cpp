#include "ast.hpp"


  SizeOf::SizeOf(ProgramPtr _expression){
      expression = _expression;
      is_type = 0;
  }
  SizeOf::SizeOf(std::string _type){
      const_type = _type;
      is_type = 1;
  }
  int SizeOf::codeGen(const Binding &_binding, int reg) const{
      if(is_type == 1){
          if(const_type == "int") 
          printf("\tli\t$%d,%d\n",reg,4);
          if(const_type == "double") 
          printf("\tli\t$%d,%d\n",reg,8);
          if(const_type == "char") 
          printf("\tli\t$%d,%d\n",reg,1);
          if(const_type == "float") 
          printf("\tli\t$%d,%d\n",reg,4);
          if(const_type == "unsigned") 
          printf("\tli\t$%d,%d\n",reg,4);
      }
      return 0;
  }
  void SizeOf::print(std::ostream &dst, int indentation) const{

  }
  int SizeOf::evaluate(const Binding &_binding) const{
      return 0;
  }
  void SizeOf::passFunctionName(std::string _name, int _pos) {
      function_name = _name;
      pos = pos + _pos;
      if(is_type == 0){
          ((Program*)expression)->passFunctionName(_name,_pos);
      }
  }
  void SizeOf::passTypeBinding(TypeBinding &_typebind){
      typebind = _typebind;
      if(is_type == 0){
          ((Program*)expression)->passTypeBinding(_typebind);
      }
  }

  void SizeOf::bind(const Binding &_binding){
      binding = _binding;
      if(is_type == 0){
          ((Program*)expression)->bind(binding);
      }
  }

