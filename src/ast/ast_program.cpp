#include "ast.hpp"

////////////////////////////////////////
// Program
////////////////////////////////////////

int Program::getType() const { return node_type; };

int Program::getSize() const { return size; };

int Program::getPos(const Binding &_binding) const { return pos; };

void Program::printIndent(std::ostream &dst, int &indentation) const {
  std::string indent_space(indentation++ * N_SPACE, ' ');
  dst << indent_space;
}
