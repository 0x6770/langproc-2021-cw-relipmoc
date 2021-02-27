#include "ast.hpp"

////////////////////////////////////////
// Addition
////////////////////////////////////////

Addition::Addition(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition\n");
  node_type = 'a';
}

void Addition::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "+";
  right->print(dst, indentation);
  dst << ")";
}

int Addition::evaluate(Binding *binding) const {
  return left->evaluate(binding) + right->evaluate(binding);
}

////////////////////////////////////////
// Subtraction
////////////////////////////////////////

Subtraction::Subtraction(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct subOperator\n");
}

void Subtraction::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "-";
  right->print(dst, indentation);
  dst << ")";
}

int Subtraction::evaluate(Binding *binding) const {
  return left->evaluate(binding) - right->evaluate(binding);
}

////////////////////////////////////////
// Multiplication
////////////////////////////////////////

Multiplication::Multiplication(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct MulOperator\n");
}

void Multiplication::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "*";
  right->print(dst, indentation);
  dst << ")";
}

int Multiplication::evaluate(Binding *binding) const {
  return left->evaluate(binding) * right->evaluate(binding);
}

////////////////////////////////////////
// Division
////////////////////////////////////////

Division::Division(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct DivOperator\n");
}

void Division::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "/";
  right->print(dst, indentation);
  dst << ")";
}

int Division::evaluate(Binding *binding) const {
  return left->evaluate(binding) / right->evaluate(binding);
}

////////////////////////////////////////
// Modulus
////////////////////////////////////////

Modulus::Modulus(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct ExpOperator\n");
}

void Modulus::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "%";
  right->print(dst, indentation);
  dst << ")";
}

int Modulus::evaluate(Binding *binding) const {
  return (left->evaluate(binding) % right->evaluate(binding));
}

////////////////////////////////////////
// Power
////////////////////////////////////////

Power::Power(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
  fprintf(stderr, "construct ExpOperator\n");
}

void Power::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "^";
  right->print(dst, indentation);
  dst << ")";
}

int Power::evaluate(Binding *binding) const {
  return (pow(left->evaluate(binding), right->evaluate(binding)));
}
