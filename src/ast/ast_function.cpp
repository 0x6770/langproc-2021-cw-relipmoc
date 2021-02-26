#include "ast.hpp"

////////////////////////////////////////
// Function
////////////////////////////////////////

Function::Function(std::string *_type, std::string *_name,
                   ProgramPtr _statements)
    : type(_type), name(_name), statements(_statements) {
  fprintf(stderr, "construct Function\n");
  node_type = 'F';
}

void Function::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  dst << *type;
  dst << " ";
  dst << *name;
  dst << "() {\n";
  statements->print(dst, indentation);
  dst << "}";
}

int Function::evaluate(Binding *binding) const {
  return statements->evaluate(binding);
}
