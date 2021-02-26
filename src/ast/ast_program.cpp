#include "ast.hpp"

////////////////////////////////////////
// Program
////////////////////////////////////////

int Program::getType() const { return node_type; };

void Program::print_indent(std::ostream &dst, int &indentation) const {
  std::string indent_space(indentation++ * N_SPACE, ' ');
  dst << indent_space;
}
