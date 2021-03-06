#include "ast.hpp"

SizeOf::SizeOf(ProgramPtr _expression) {
  expression = _expression;
  is_type = 0;
}
SizeOf::SizeOf(std::string _type) {
  const_type = _type;
  is_type = 1;
}
int SizeOf::codeGen(std::ofstream &dst, const Binding &_binding,
                    int reg) const {
  std::string local_type;
  if (is_type == 1) {
    local_type = const_type;
  } else {
    // only support single variable now
    if (((Program *)expression)->getType() == 'x') {
      TypeBinding local_bind = typebind;
      local_type = ((Variable *)expression)->gettype(local_bind);
    } else {
      local_type = ((Program *)expression)->getVariableType();
    }
  }
  if (local_type == "int")
    dst << "\tli\t\t$" << reg << "," << 4 << "" << std::endl;
  if (local_type == "double")
    dst << "\tli\t\t$" << reg << "," << 8 << "" << std::endl;
  if (local_type == "char")
    dst << "\tli\t\t$" << reg << "," << 1 << "" << std::endl;
  if (local_type == "float")
    dst << "\tli\t\t$" << reg << "," << 4 << "" << std::endl;
  if (local_type == "unsigned")
    dst << "\tli\t\t$" << reg << "," << 4 << "" << std::endl;
  return 0;
}
void SizeOf::print(std::ostream &dst, int indentation) const {}
int SizeOf::evaluate(const Binding &_binding) const { return 0; }
void SizeOf::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  if (is_type == 0) {
    ((Program *)expression)->passFunctionName(_name, _pos);
  }
}
void SizeOf::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  if (is_type == 0) {
    ((Program *)expression)->passTypeBinding(_typebind);
  }
}

void SizeOf::bind(const Binding &_binding) {
  binding = _binding;
  if (is_type == 0) {
    ((Program *)expression)->bind(binding);
  }
}

std::string SizeOf::getVariableType() {
  if (is_type == 0) {
    return ((Program *)expression)->getVariableType();
  }
  return "can't recognize type";
}
