#include "ast.hpp"

////////////////////////////////////////
// LessEqual
////////////////////////////////////////

LessEqual::LessEqual(ProgramPtr _left, ProgramPtr _right, int _pos,
                     int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  fprintf(stderr, "construct ExpOperator\n");
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

int LessEqual::evaluate(Binding *binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) <= right->evaluate(binding));
  } else {
    return (left->evaluate(binding) < right->evaluate(binding));
  }
}

int LessEqual::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// GreaterEqual
////////////////////////////////////////

GreaterEqual::GreaterEqual(ProgramPtr _left, ProgramPtr _right, int _pos,
                           int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  fprintf(stderr, "construct ExpOperator\n");
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

int GreaterEqual::evaluate(Binding *binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) >= right->evaluate(binding));
  } else {
    return (left->evaluate(binding) > right->evaluate(binding));
  }
}

int GreaterEqual::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// Equal
////////////////////////////////////////

Equal::Equal(ProgramPtr _left, ProgramPtr _right, int _pos, int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  fprintf(stderr, "construct ExpOperator\n");
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

int Equal::evaluate(Binding *binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) != right->evaluate(binding));
  } else {
    return (left->evaluate(binding) == right->evaluate(binding));
  }
}

int Equal::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// LogicalAnd
////////////////////////////////////////

LogicalAnd::LogicalAnd(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void LogicalAnd::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "&&";
  right->print(dst, indentation);
  dst << ")";
}

int LogicalAnd::evaluate(Binding *binding) const {
  return (left->evaluate(binding) && right->evaluate(binding));
}

int LogicalAnd::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// LogicalOr
////////////////////////////////////////

LogicalOr::LogicalOr(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ExpOperator\n");
}

void LogicalOr::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "||";
  right->print(dst, indentation);
  dst << ")";
}

int LogicalOr::evaluate(Binding *binding) const {
  return (left->evaluate(binding) || right->evaluate(binding));
}

int LogicalOr::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}
