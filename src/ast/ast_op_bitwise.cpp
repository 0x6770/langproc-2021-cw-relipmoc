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

int BitwiseAnd::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("and $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of and bitwise operation\n", pos);

  return 0;
}

void BitwiseAnd::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
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

int BitwiseOr::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("or $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of or bitwise operation\n", pos);

  return 0;
}
void BitwiseOr::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
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

int BitwiseXor::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("xor $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of xor bitwise operation\n", pos);
  return 0;
}

void BitwiseXor::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
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

int ShiftLeft::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if (left_type == 'i' || left_type == 'x'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("sll $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of left shift operation\n", pos);

  return 0;
}

void ShiftLeft::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
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

int ShiftRight::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

 if (left_type == 'i' || left_type == 'x'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));

  printf("sra $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of right shift operation\n", pos);

  return 0;
}

void ShiftRight::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}