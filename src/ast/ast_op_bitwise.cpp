#include "ast.hpp"

////////////////////////////////////////
// BitwiseAnd
////////////////////////////////////////

BitwiseAnd::BitwiseAnd(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct BitwiseAnd\n");
}

void BitwiseAnd::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "&";
  right->print(dst, indentation);
  dst << ")";
}

int BitwiseAnd::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) & right->evaluate(binding));
}

int BitwiseAnd::codeGen(std::ofstream &dst, const Binding &_binding,
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

  dst << "\tand\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t\t# store result of and bitwise operation" << std::endl;

  return 0;
}

void BitwiseAnd::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void BitwiseAnd::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string BitwiseAnd::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// BitwiseOr
////////////////////////////////////////

BitwiseOr::BitwiseOr(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct BitwiseOr\n");
}

void BitwiseOr::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "|";
  right->print(dst, indentation);
  dst << ")";
}

int BitwiseOr::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) | right->evaluate(binding));
}

int BitwiseOr::codeGen(std::ofstream &dst, const Binding &_binding,
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

  dst << "\tor\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t\t# store result of or bitwise operation" << std::endl;

  return 0;
}
void BitwiseOr::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}
void BitwiseOr::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string BitwiseOr::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// BitwiseXor
////////////////////////////////////////

BitwiseXor::BitwiseXor(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct BitwiseXor\n");
}

void BitwiseXor::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "^";
  right->print(dst, indentation);
  dst << ")";
}

int BitwiseXor::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) ^ right->evaluate(binding));
}

int BitwiseXor::codeGen(std::ofstream &dst, const Binding &_binding,
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

  dst << "\txor\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t\t# store result of xor bitwise operation" << std::endl;
  return 0;
}

void BitwiseXor::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void BitwiseXor::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string BitwiseXor::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// ShiftLeft
////////////////////////////////////////

ShiftLeft::ShiftLeft(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct ShiftLeft\n");
}

void ShiftLeft::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "<<";
  right->print(dst, indentation);
  dst << ")";
}

int ShiftLeft::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) << right->evaluate(binding));
}

int ShiftLeft::codeGen(std::ofstream &dst, const Binding &_binding,
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

  dst << "\tsll\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t\t# store result of left shift operation" << std::endl;

  return 0;
}

void ShiftLeft::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void ShiftLeft::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string ShiftLeft::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// ShiftRight
////////////////////////////////////////

ShiftRight::ShiftRight(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct ShiftRight\n");
}

void ShiftRight::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << ">>";
  right->print(dst, indentation);
  dst << ")";
}

int ShiftRight::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) >> right->evaluate(binding));
}

int ShiftRight::codeGen(std::ofstream &dst, const Binding &_binding,
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

  dst << "\tsra\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << pos
      << "($fp)\t\t# store result of right shift operation" << std::endl;

  return 0;
}

void ShiftRight::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void ShiftRight::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string ShiftRight::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
