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
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
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
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// BitwiseXor
////////////////////////////////////////

BitwiseXor::BitwiseXor(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
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
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
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
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}
