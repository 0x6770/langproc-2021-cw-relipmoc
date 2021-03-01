#include "ast.hpp"

////////////////////////////////////////
// BitwiseAnd
////////////////////////////////////////

BitwiseAnd::BitwiseAnd(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void BitwiseAnd::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "&";
  right->print(dst, indentation);
  dst << ")";
}

int BitwiseAnd::evaluate(Binding *binding) const {
  return (left->evaluate(binding) & right->evaluate(binding));
}

int BitwiseAnd::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("and $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of and bitwise operation\n", pos);
  return 0;
}

////////////////////////////////////////
// BitwiseOr
////////////////////////////////////////

BitwiseOr::BitwiseOr(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void BitwiseOr::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "|";
  right->print(dst, indentation);
  dst << ")";
}

int BitwiseOr::evaluate(Binding *binding) const {
  return (left->evaluate(binding) | right->evaluate(binding));
}

int BitwiseOr::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("or $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of or bitwise operation\n", pos);
  return 0;
}

////////////////////////////////////////
// BitwiseXor
////////////////////////////////////////

BitwiseXor::BitwiseXor(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void BitwiseXor::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "^";
  right->print(dst, indentation);
  dst << ")";
}

int BitwiseXor::evaluate(Binding *binding) const {
  return (left->evaluate(binding) ^ right->evaluate(binding));
}

int BitwiseXor::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("xor $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of xor bitwise operation\n", pos);
  return 0; }

////////////////////////////////////////
// ShiftLeft
////////////////////////////////////////

ShiftLeft::ShiftLeft(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void ShiftLeft::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "<<";
  right->print(dst, indentation);
  dst << ")";
}

int ShiftLeft::evaluate(Binding *binding) const {
  return (left->evaluate(binding) << right->evaluate(binding));
}

int ShiftLeft::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("sll $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of left shift operation\n", pos);
  return 0;
}

////////////////////////////////////////
// ShiftRight
////////////////////////////////////////

ShiftRight::ShiftRight(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void ShiftRight::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << ">>";
  right->print(dst, indentation);
  dst << ")";
}

int ShiftRight::evaluate(Binding *binding) const {
  return (left->evaluate(binding) >> right->evaluate(binding));
}

int ShiftRight::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));

  printf("slr $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of right shift operation\n", pos);

  return 0;
}
