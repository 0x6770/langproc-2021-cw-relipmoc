#include "ast.hpp"

void print_map(const Binding &_binding, std::string _name) {
  logger->info("Print mapping of variables for %s\n", _name.c_str());
  logger->info("---------------------\n");
  logger->info("%10s|%10s\n", "name", "position");
  logger->info("---------------------\n");
  for (auto it : _binding) {
    logger->info("%10s|%10d\n", it.first.c_str(), it.second);
  }
}

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

void Program::passLabel(int _label) {}

std::string getVariableType() { return "default int"; }
