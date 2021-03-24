#include "ast.hpp"

Array::Array(std::string _variable_type, uint32_t _size, std::string _name,
             int _pos) {
  size = _size;
  name = _name;
  variable_type = _variable_type;
  node_type = 'A';
  pos = _pos;
}

void Array::print(std::ostream &dst, int indentation) const {
  dst << variable_type << " " << name << "[" << size << "]" << std::endl;
}

int Array::codeGen(std::ofstream &dst, const Binding &_binding, int reg) const {
  // do nothing
  return 0;
}

int Array::evaluate(const Binding &_binding) const { return 0; }

void Array::bind(const Binding &_binding) { binding = _binding; }

void Array::add_bind(Binding &_binding) {
  int n = 0;
  int pos_temp = pos;
  std::string key = name + "_" + std::to_string(n);
  for (uint32_t i = 0; i < size; i++) {
    key = name + "_" + std::to_string(i);
    _binding[key] = pos_temp;
    pos_temp = pos_temp + 4;
  }
}

void Array::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
}

uint32_t Array::getSize() { return size * 4; }

std::string Array::getName() { return name; }

void Array::passTypeBinding(TypeBinding &_typebind) {
  _typebind[name] = "array";
  typebind = _typebind;
}

std::string Array::getVariableType() { return "array"; }

ArrayElement::ArrayElement(ProgramPtr _left, std::string _name) {
  left = _left;
  name = _name;
  node_type = 'a';
}

ArrayElement::ArrayElement(ProgramPtr _left, ProgramPtr _right,
                           std::string _name) {
  left = _left;
  right = _right;
  name = _name;
  node_type = 'a';
}

void ArrayElement::array_assignment(ProgramPtr _right) {
  right = _right;
  call = 1;
  logger->info("construct array_elment");
}

void ArrayElement::print(std::ostream &dst, int indentation) const {}
int ArrayElement::codeGen(std::ofstream &dst, const Binding &_binding,
                          int reg) const {
  std::string temp = name + "_" + std::to_string(0);
  // int start_location = 0;
  /*for (auto it : binding) {
    if (it.first == temp) {
      start_location = it.second;
    }
  }*/
  TypeBinding var_binding = typebind;
  Binding pos_bind = binding;
  std::string variable_type = var_binding[name];
  if (variable_type == "array") {
    left->codeGen(dst, binding, 2);
    dst << "\tsll\t$2,$2,2" << std::endl;
    dst << "\taddiu\t$3,$fp,8" << std::endl;
    dst << "\taddu\t$2,$3,$2" << std::endl;
    if (call == 1) {
      right->codeGen(dst, binding, 3);
      dst << "\tnop" << std::endl;
      ;
      dst << "\tsw\t\t$3," << 4 << "($2)\t\t# store an element in an array"
          << std::endl;
    } else {
      dst << "\tnop" << std::endl;
      ;
      dst << "\tlw\t\t$" << reg << "," << 4
          << "($2)\t\t# load an element in an array" << std::endl;
    }
  }
  if (variable_type == "pointer") {
    left->codeGen(dst, binding, 2);
    dst << "\tsll\t$2,$2,2" << std::endl;
    dst << "\tlw\t\t$3," << pos_bind[name] << "($fp)" << std::endl;
    dst << "\tnop" << std::endl;
    dst << "\taddu\t$2,$2,$3" << std::endl;
    dst << "\tlw\t\t$" << reg << ",0($2)" << std::endl;
  }

  return 0;
}
int ArrayElement::evaluate(const Binding &_binding) const { return 0; }

void ArrayElement::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)left)->bind(binding);
  if (call == 1) {
    ((Program *)right)->bind(binding);
  }
}

void ArrayElement::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  ((Program *)left)->passFunctionName(_name, _pos);
  if (call == 1) {
    ((Program *)right)->passFunctionName(_name, _pos);
  }
}

void ArrayElement::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(_typebind);
  if (call == 1) {
    ((Program *)right)->passTypeBinding(_typebind);
  }
}

std::string ArrayElement::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2;
  if (call == 1) var_2 = ((Program *)right)->getVariableType();
  if (call == 1) {
    if (var_1 == "int" && var_2 == "int") return "int";
  } else {
    if (var_1 == "int") return "int";
  }
  return "no type";
}
