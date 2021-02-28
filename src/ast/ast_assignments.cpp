#include "ast/ast_assignments.hpp"

////////////////////////////////////////
// Addition Equal
////////////////////////////////////////

AddEqual::AddEqual(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void AddEqual::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "+=";
  right->print(dst, indentation);
  dst << ";\n";
}

int AddEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding)+right->evaluate(binding);
}


////////////////////////////////////////
// Subtraction Equal
////////////////////////////////////////

SubEqual::SubEqual(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void SubEqual::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "-=";
  right->print(dst, indentation);
  dst << ";\n";
}

int SubEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) - right->evaluate(binding);
}

////////////////////////////////////////
// Product assignment
////////////////////////////////////////

MulEqual::MulEqual(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void MulEqual::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "*=";
  right->print(dst, indentation);
  dst << ";\n";
}

int MulEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) * right->evaluate(binding);
}

////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

QuoEqual::QuoEqual(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void QuoEqual::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "/=";
  right->print(dst, indentation);
  dst << ";\n";
  
}

int QuoEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) / right->evaluate(binding);
}

////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

ModEqual::ModEqual(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void ModEqual::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "%=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ModEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) % right->evaluate(binding);
}

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

ShiftEqual_L::ShiftEqual_L(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void ShiftEqual_L::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "<<=";
  right->print(dst, indentation);
  dst << ";\n";
  
}

int ShiftEqual_L::evaluate(Binding *binding) const {
  return left->evaluate(binding) << right->evaluate(binding);
}

////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

ShiftEqual_R::ShiftEqual_R(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void ShiftEqual_R::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << ">>=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ShiftEqual_R::evaluate(Binding *binding) const {
  return left->evaluate(binding) >> right->evaluate(binding);
}

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

BitwiseEqual_AND::BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void BitwiseEqual_AND::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "&=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_AND::evaluate(Binding *binding) const {
  return left->evaluate(binding) & right->evaluate(binding);
}

////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

BitwiseEqual_OR::BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void BitwiseEqual_OR::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "|=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_OR::evaluate(Binding *binding) const {
  return left->evaluate(binding) | right->evaluate(binding);
}

////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

BitwiseEqual_XOR::BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right)
    : left(_left), right(_right) {
  fprintf(stderr, "construct Addition assigment\n");
}

void BitwiseEqual_XOR::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  left->print(dst, indentation);
  dst << "^=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_XOR::evaluate(Binding *binding) const {
  return left->evaluate(binding) ^ right->evaluate(binding);
}

