#include "ast.hpp"

////////////////////////////////////////
// Addition Equal
////////////////////////////////////////

AddEqual::AddEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct +=\n");
}

void AddEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "+=";
  right->print(dst, indentation);
}

int AddEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) + right->evaluate(_binding);
}

int AddEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tadd\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  return 0;
}

void AddEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void AddEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string AddEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// Subtraction Equal
////////////////////////////////////////

SubEqual::SubEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct -=\n");
}

void SubEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "-=";
  right->print(dst, indentation);
}

int SubEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) - right->evaluate(_binding);
}

int SubEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tsub\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for sub equal" << std::endl;
  return 0;
}

void SubEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}
void SubEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string SubEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// Product assignment
////////////////////////////////////////

MulEqual::MulEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct *=\n");
}

void MulEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "*=";
  right->print(dst, indentation);
}

int MulEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) * right->evaluate(_binding);
}

int MulEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tmult\t$2,$3" << std::endl;
  dst << "\tmflo\t$2" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for mul equal" << std::endl;
  return 0;
}

void MulEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void MulEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string MulEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

QuoEqual::QuoEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct /=\n");
}

void QuoEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "/=";
  right->print(dst, indentation);
}

int QuoEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) / right->evaluate(_binding);
}

int QuoEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tdiv\t\t$2,$3" << std::endl;
  dst << "\tmflo\t$2" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for quo equal" << std::endl;
  return 0;
}

void QuoEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void QuoEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string QuoEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

ModEqual::ModEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct %%=\n");
}

void ModEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "%=";
  right->print(dst, indentation);
}

int ModEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) % right->evaluate(_binding);
}
int ModEqual::codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tdiv\t\t$2,$3" << std::endl;
  dst << "\tmfhi\t$2" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for modulus equal" << std::endl;
  return 0;
}

void ModEqual::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}
void ModEqual::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string ModEqual::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

ShiftEqual_L::ShiftEqual_L(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct <<=\n");
}

void ShiftEqual_L::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "<<=";
  right->print(dst, indentation);
}

int ShiftEqual_L::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) << right->evaluate(_binding);
}

int ShiftEqual_L::codeGen(std::ofstream &dst, const Binding &_binding,
                          int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tsll\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for shift left equal" << std::endl;
  return 0;
}

void ShiftEqual_L::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void ShiftEqual_L::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string ShiftEqual_L::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

ShiftEqual_R::ShiftEqual_R(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct >>=\n");
}

void ShiftEqual_R::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << ">>=";
  right->print(dst, indentation);
}

int ShiftEqual_R::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) >> right->evaluate(_binding);
}

int ShiftEqual_R::codeGen(std::ofstream &dst, const Binding &_binding,
                          int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tsra\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for shift right equal" << std::endl;
  return 0;
}
void ShiftEqual_R::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void ShiftEqual_R::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string ShiftEqual_R::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

BitwiseEqual_AND::BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right,
                                   int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct &=\n");
}

void BitwiseEqual_AND::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "&=";
  right->print(dst, indentation);
}

int BitwiseEqual_AND::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) & right->evaluate(_binding);
}

int BitwiseEqual_AND::codeGen(std::ofstream &dst, const Binding &_binding,
                              int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tand\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for bitwise and equal" << std::endl;
  return 0;
}

void BitwiseEqual_AND::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void BitwiseEqual_AND::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string BitwiseEqual_AND::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}
////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

BitwiseEqual_OR::BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct |=\n");
}

void BitwiseEqual_OR::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "|=";
  right->print(dst, indentation);
}

int BitwiseEqual_OR::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) | right->evaluate(_binding);
}

int BitwiseEqual_OR::codeGen(std::ofstream &dst, const Binding &_binding,
                             int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\tor\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for bitwise or equal" << std::endl;
  return 0;
}
void BitwiseEqual_OR::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void BitwiseEqual_OR::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string BitwiseEqual_OR::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

BitwiseEqual_XOR::BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right,
                                   int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct ^=\n");
}

void BitwiseEqual_XOR::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "^=";
  right->print(dst, indentation);
}

int BitwiseEqual_XOR::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) ^ right->evaluate(_binding);
}

int BitwiseEqual_XOR::codeGen(std::ofstream &dst, const Binding &_binding,
                              int reg) const {
  int right_type = right->getType();
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }

  right->codeGen(dst, binding, 3);
  left->codeGen(dst, binding, 2);
  if (!((right_type == 'i') | (right_type == 'x') || (right_type == 'a')))
    dst << "\tlw\t\t$3," << right->getPos(binding) << "($fp)" << std::endl;

  dst << "\txor\t\t$2,$2,$3" << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding) << "($fp)" << std::endl;
  // std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" <<
  // "#store the result for bitwise xor equal" << std::endl;
  return 0;
}
void BitwiseEqual_XOR::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

void BitwiseEqual_XOR::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  ((Program *)right)->passTypeBinding(typebind);
}

std::string BitwiseEqual_XOR::getVariableType() {
  std::string var_1 = ((Program *)left)->getVariableType();
  std::string var_2 = ((Program *)right)->getVariableType();
  if ((var_1 == "int") && (var_2 == "int")) {
    return "int";
  }
  return "no type";
}

////////////////////////////////////////
// Postfix increment
////////////////////////////////////////

Increment_Post::Increment_Post(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  logger->info("construct post increment\n");
  node_type = '1';
}

void Increment_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "++";
  dst << ")";
}

int Increment_Post::evaluate(const Binding &_binding) const {
  // int result = left->evaluate(_binding)+1;
  return left->evaluate(_binding);
}

int Increment_Post::codeGen(std::ofstream &dst, const Binding &_binding,
                            int reg) const {
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }
  left->codeGen(dst, binding, 2);

  TypeBinding temp = typebind;
  if (((Variable *)left)->gettype(temp) == "pointer") {
    dst << "\taddiu\t$3,$2,4\t#" << pos << std::endl;
  } else {
    dst << "\taddiu\t$3,$2,1\t#" << pos << std::endl;
  }

  dst << "\tsw\t\t$2," << pos << "($fp)\t# initial value x0" << std::endl;
  dst << "\tsw\t\t$3," << left->getPos(binding) << "($fp)\t# x0+1" << std::endl;
  return 0;
}
void Increment_Post::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
}

void Increment_Post::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
}

std::string Increment_Post::getVariableType() {
  std::string var_2 = ((Program *)left)->getVariableType();
  if ((var_2 == "int")) {
    return "int";
  } else if (var_2 == "pointer") {
    return "pointer";
  }
  return "no type";
}
////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Increment_Pre::Increment_Pre(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  logger->info("construct pre increment\n");
  node_type = '2';
}

void Increment_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "++";
  left->print(dst, indentation);
  dst << ")";
}

int Increment_Pre::evaluate(const Binding &_binding) const {
  return (left->evaluate(_binding) + 1);
}

int Increment_Pre::codeGen(std::ofstream &dst, const Binding &_binding,
                           int reg) const {
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }
  left->codeGen(dst, binding, 2);
  TypeBinding temp = typebind;
  if (((Variable *)left)->gettype(temp) == "pointer") {
    dst << "\taddiu\t$2,$2,4\t#" << pos << std::endl;
  } else {
    dst << "\taddiu\t$2,$2,1\t#" << pos << std::endl;
  }
  dst << "\tsw\t\t$2," << pos << "($fp)\t# store result of pre increment"
      << std::endl;
  dst << "\tsw\t\t$2," << left->getPos(binding)
      << "($fp)\t# store result of pre increment" << std::endl;
  return 0;
}
void Increment_Pre::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
}

void Increment_Pre::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
}

std::string Increment_Pre::getVariableType() {
  std::string var_2 = ((Program *)left)->getVariableType();
  if ((var_2 == "int")) {
    return "int";
  } else if (var_2 == "pointer") {
    return "pointer";
  }
  return "no type";
}
////////////////////////////////////////
// Postfix decrement
////////////////////////////////////////

Decrement_Post::Decrement_Post(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  logger->info("construct post increment\n");
  node_type = '3';
}

void Decrement_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "--";
  dst << ")";
}

int Decrement_Post::evaluate(const Binding &_binding) const {
  // int result = left->evaluate(_binding)-1;
  return left->evaluate(_binding);
}

int Decrement_Post::codeGen(std::ofstream &dst, const Binding &_binding,
                            int reg) const {
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }
  left->codeGen(dst, binding, 2);

  TypeBinding temp = typebind;
  if (((Variable *)left)->gettype(temp) == "pointer") {
    dst << "\taddiu\t$3,$2,-4\t#" << pos << "" << std::endl;
  } else {
    dst << "\taddiu\t$3,$2,-1\t# " << pos << "" << std::endl;
  }

  dst << "\tsw\t\t$2," << pos << "($fp)\t# initial value x0" << std::endl;
  dst << "\tsw\t\t$3," << left->getPos(binding) << "($fp)\t# x0-1" << std::endl;
  return 0;
}

void Decrement_Post::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
}

void Decrement_Post::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  //((Program*)right)->passTypeBinding(typebind);
}
std::string Decrement_Post::getVariableType() {
  std::string var_2 = ((Program *)left)->getVariableType();
  if ((var_2 == "int")) {
    return "int";
  } else if (var_2 == "pointer") {
    return "pointer";
  }
  return "no type";
}
////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Decrement_Pre::Decrement_Pre(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  logger->info("construct pre decrement\n");
  node_type = '3';
}

void Decrement_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "--";
  left->print(dst, indentation);
  dst << ")";
}

int Decrement_Pre::evaluate(const Binding &_binding) const {
  return (left->evaluate(_binding) - 1);
}

int Decrement_Pre::codeGen(std::ofstream &dst, const Binding &_binding,
                           int reg) const {
  int left_type = left->getType();
  if (left_type != 'x') {
    printf("ERROR: expression is not assignable\t");
    this->print(std::cout, 1);
    printf("\n");
    exit(1);
  }
  left->codeGen(dst, binding, 2);

  TypeBinding temp = typebind;
  if (((Variable *)left)->gettype(temp) == "pointer") {
    dst << "\taddiu\t$2,$2,-4\t# " << pos << std::endl;
  } else {
    dst << "\taddiu\t$2,$2,-1\t# " << pos << std::endl;
  }

  dst << "\tsw\t\t$2," << left->getPos(binding)
      << "($fp)\t# store result of pre decrement" << std::endl;
  dst << "\tsw\t\t$2," << pos << "($fp)\t# store result of pre decrement"
      << std::endl;
  return 0;
}
void Decrement_Pre::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
}

void Decrement_Pre::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)left)->passTypeBinding(typebind);
  //((Program*)right)->passTypeBinding(typebind);
}

std::string Decrement_Pre::getVariableType() {
  std::string var_2 = ((Program *)left)->getVariableType();
  if ((var_2 == "int")) {
    return "int";
  } else if (var_2 == "pointer") {
    return "pointer";
  }
  return "no type";
}
