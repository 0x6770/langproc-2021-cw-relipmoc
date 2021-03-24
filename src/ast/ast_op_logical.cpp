#include "ast.hpp"

////////////////////////////////////////
// LessEqual
////////////////////////////////////////

LessEqual::LessEqual(ProgramPtr _left, ProgramPtr _right, int _pos,
                     int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  logger->info("construct LessEqual\n");
}

void LessEqual::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  if (is_equal == 1) {
    dst << "<=";
  } else {
    dst << "<";
  }
  right->print(dst, indentation);
  dst << ")";
}

int LessEqual::evaluate(const Binding &_binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) <= right->evaluate(binding));
  } else {
    return (left->evaluate(binding) < right->evaluate(binding));
  }
}

int LessEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                       int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x' || left_type == 'a') {
    right->codeGen(dst, binding, 3);
    left->codeGen(dst, binding, 2);
  } else {
    left->codeGen(dst, binding, 2);
    right->codeGen(dst, binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x') || (left_type == 'a')))
    dst << "\tlw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  if (is_equal == 1) {
    dst << "\tslt\t\t$2,$3,$2" << std::endl;
    dst << "\txori\t$2,$2,0x1" << std::endl;
  } else {
    dst << "\tslt\t\t$2,$2,$3" << std::endl;
  }
  dst << "\tandi\t$2,$2,0x00ff" << std::endl;
  //  TODO: there is also a line " andi $2,$2,0x00ff" in the online converter.
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t# store result of logical less or less equal" << std::endl;

  return 0;
}
void LessEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void LessEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string LessEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// GreaterEqual
////////////////////////////////////////

GreaterEqual::GreaterEqual(ProgramPtr _left, ProgramPtr _right, int _pos,
                           int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  logger->info("construct GreaterEqual\n");
}

void GreaterEqual::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  if (is_equal == 1) {
    dst << ">=";
  } else {
    dst << ">";
  }
  right->print(dst, indentation);
  dst << ")";
}

int GreaterEqual::evaluate(const Binding &_binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) >= right->evaluate(binding));
  } else {
    return (left->evaluate(binding) > right->evaluate(binding));
  }
}

int GreaterEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                          int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x' || left_type == 'a') {
    right->codeGen(dst, binding, 3);
    left->codeGen(dst, binding, 2);
  } else {
    left->codeGen(dst, binding, 2);
    right->codeGen(dst, binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x') || (left_type == 'a')))
    dst << "\tlw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tslt\t\t$2,$3,$2" << std::endl;
  if (is_equal == 1) {
    dst << "\txori\t$2,$2,0x1" << std::endl;
  }
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t# store result of logical greater or greater than"
      << std::endl;

  return 0;
}

void GreaterEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void GreaterEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string GreaterEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// Equal
////////////////////////////////////////

Equal::Equal(ProgramPtr _left, ProgramPtr _right, int _pos, int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  logger->info("construct Equal\n");
}

void Equal::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  if (is_equal == 1) {
    dst << "!=";
  } else {
    dst << "==";
  }
  right->print(dst, indentation);
  dst << ")";
}

int Equal::evaluate(const Binding &_binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) != right->evaluate(binding));
  } else {
    return (left->evaluate(binding) == right->evaluate(binding));
  }
}

int Equal::codeGen(std::ofstream &dst, const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x' || left_type == 'a') {
    right->codeGen(dst, binding, 3);
    left->codeGen(dst, binding, 2);
  } else {
    left->codeGen(dst, binding, 2);
    right->codeGen(dst, binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x') || (left_type == 'a')))
    dst << "\tlw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\txor\t\t$2,$2,$3" << std::endl;
  if (is_equal == 1) {
    dst << "\tsltu\t$2,$0,$2" << std::endl;
  } else {
    dst << "\tsltiu\t$2,$2,1" << std::endl;
  }
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t# store result of logical equal or logical not equal"
      << std::endl;

  return 0;
}

void Equal::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void Equal::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string Equal::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// LogicalAnd
////////////////////////////////////////

LogicalAnd::LogicalAnd(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct LogicalAnd\n");
}

void LogicalAnd::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "&&";
  right->print(dst, indentation);
  dst << ")";
}

int LogicalAnd::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) && right->evaluate(binding));
}

int LogicalAnd::codeGen(std::ofstream &dst, const Binding &_binding,
                        int reg) const {
  left->codeGen(dst, binding, 2);
  std::string labelL2 = "F" + function_name + "_2a_" + std::to_string(pos);
  std::string labelL3 = "F" + function_name + "_3a_" + std::to_string(pos);
  dst << "\tnop" << std::endl;
  // TODO： add counter to create unique label:
  // std::cout << "\tbeq $0,$2,"
  //          << labelL2 << std::endl;
  dst << "\tbeq\t\t$0,$2," << labelL2.c_str() << std::endl;
  dst << "\tnop" << std::endl;  // Add empty delay slot

  right->codeGen(dst, binding, 2);
  dst << "\tnop" << std::endl;
  // TODO： add counter to create unique label:
  // std::cout << "\tbeq $0,$2,"
  //          << labelL2 << std::endl;
  dst << "\tbeq\t\t$0,$2," << labelL2.c_str() << std::endl;
  dst << "\tnop" << std::endl;

  dst << "\tli\t\t$2,1" << std::endl;
  dst << "b " << labelL3.c_str() << ""
      << std::endl;  // TODO： add counter to create unique label:
  // std::cout << "\tb " << labelL3 << std::endl;
  dst << "\tnop" << std::endl;  // Add empty delay slot
  dst << "" << labelL2.c_str() << ":" << std::endl;
  // std::cout <<  "\t"<<labelL2 <<":" << std::endl;
  dst << "\tmove\t$2,$0" << std::endl;
  dst << "" << labelL3.c_str() << ":" << std::endl;
  // std::cout << "\t" <<labelL3 <<":" << std::endl;
  dst << "\tsw\t\t$2," << pos << "($fp)\t# store result of logical and"
      << std::endl;
  dst << "\tlw\t\t$2," << pos << "($fp)" << std::endl;

  return 0;
}

void LogicalAnd::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}
void LogicalAnd::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string LogicalAnd::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// LogicalOr
////////////////////////////////////////

LogicalOr::LogicalOr(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct LogicalOr\n");
}

void LogicalOr::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "||";
  right->print(dst, indentation);
  dst << ")";
}

int LogicalOr::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) || right->evaluate(binding));
}

int LogicalOr::codeGen(std::ofstream &dst, const Binding &_binding,
                       int reg) const {
  left->codeGen(dst, binding, 2);
  dst << "nop" << std::endl;
  std::string labelL2 = "F" + function_name + "L2_or" + std::to_string(pos);
  std::string labelL3 = "F" + function_name + "L3_or" + std::to_string(pos);
  std::string labelL4 = "F" + function_name + "L4_or" + std::to_string(pos);
  // TODO： add counter to create unique label:
  // std::cout << "bne $2,$0,"
  //          << labelL2 << std::endl;
  dst << "\tbne\t\t$2,$0," << labelL2.c_str() << std::endl;
  dst << "\tnop" << std::endl;  // Add empty delay slot

  right->codeGen(dst, binding, 2);
  dst << "\tnop" << std::endl;
  // TODO： add counter to create unique label:
  // std::cout << "beq $2,$0,"
  //          << labelL3 << std::endl;
  dst << "\tbeq\t\t$2,$0," << labelL3.c_str() << std::endl;
  dst << "\tnop" << std::endl;

  dst << "" << labelL2.c_str() << ":" << std::endl;
  // std::cout << labelL2 << ":" << std::endl;
  dst << "\tli\t\t$2,1" << std::endl;
  dst << "\tb\t" << labelL4.c_str() << ""
      << std::endl;  // TODO： add counter to create unique label:
  // std::cout << "b " << labelL4 << std::endl;
  dst << "\tnop" << std::endl;
  dst << "" << labelL3.c_str() << ":" << std::endl;
  // std::cout << labelL3 << ":" << std::endl;
  dst << "\tmove\t$2,$0" << std::endl;
  dst << "" << labelL4.c_str() << ":" << std::endl;
  // std::cout << labelL4 << ":" << std::endl;
  dst << "\tsw\t\t$2," << pos << "($fp)\t #store the value of logical or"
      << std::endl;
  dst << "\tlw\t\t$2," << pos << "($fp)" << std::endl;

  return 0;
}

void LogicalOr::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void LogicalOr::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string LogicalOr::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
