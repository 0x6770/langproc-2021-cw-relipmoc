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
  return (left->evaluate(_binding) & right->evaluate(_binding));
}

int BitwiseAnd::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
  return (left->evaluate(_binding) | right->evaluate(_binding));
}

int BitwiseOr::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
  return (left->evaluate(_binding) ^ right->evaluate(_binding));
}

int BitwiseXor::codeGen(const Binding &_binding, int reg) const { return 0; }

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
  return (left->evaluate(_binding) << right->evaluate(_binding));
}

int ShiftLeft::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
  return (left->evaluate(_binding) >> right->evaluate(_binding));
}

int ShiftRight::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
}
