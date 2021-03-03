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
    return (left->evaluate(_binding) <= right->evaluate(_binding));
  } else {
    return (left->evaluate(_binding) < right->evaluate(_binding));
  }
}

int LessEqual::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
    return (left->evaluate(_binding) >= right->evaluate(_binding));
  } else {
    return (left->evaluate(_binding) > right->evaluate(_binding));
  }
}

int GreaterEqual::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
    return (left->evaluate(_binding) != right->evaluate(_binding));
  } else {
    return (left->evaluate(_binding) == right->evaluate(_binding));
  }
}

int Equal::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
  return (left->evaluate(_binding) && right->evaluate(_binding));
}

int LogicalAnd::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
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
  return (left->evaluate(_binding) || right->evaluate(_binding));
}

int LogicalOr::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(_binding, 2);
  right->codeGen(_binding, 2);
  return 0;
}
