#include "ast.hpp"

////////////////////////////////////////
// Program
////////////////////////////////////////

const int &Program::getType() const { return node_type; };

const int &Program::getSize() const { return size; };

const int &Program::getPos(const Binding &binding) const { return pos; };

void Program::printIndent(std::ostream &dst, int &indentation) const {
  std::string indent_space(indentation++ * N_SPACE, ' ');
  dst << indent_space;
}
