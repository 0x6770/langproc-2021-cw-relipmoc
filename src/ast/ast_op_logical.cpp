#include "ast.hpp"

////////////////////////////////////////
// LessEqual
////////////////////////////////////////

LessEqual::LessEqual(ProgramPtr _left, ProgramPtr _right, int _is_equal)
    : left(_left), right(_right), is_equal(_is_equal) {
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

////////////////////////////////////////
// GreaterEqual
////////////////////////////////////////

GreaterEqual::GreaterEqual(ProgramPtr _left, ProgramPtr _right, int _is_equal)
    : left(_left), right(_right), is_equal(_is_equal) {
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

////////////////////////////////////////
// Equal
////////////////////////////////////////

Equal::Equal(ProgramPtr _left, ProgramPtr _right, int _is_equal)
    : left(_left), right(_right), is_equal(_is_equal) {
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

////////////////////////////////////////
// LogicalAnd
////////////////////////////////////////

LogicalAnd::LogicalAnd(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
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

////////////////////////////////////////
// LogicalOr
////////////////////////////////////////

LogicalOr::LogicalOr(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
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
