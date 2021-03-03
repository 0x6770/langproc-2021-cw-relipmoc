#include "ast.hpp"
#include <iterator>

////////////////////////////////////////
// Integer
////////////////////////////////////////

Integer::Integer(int _value) : value(_value) {
  logger->info("construct Integer\n");
  node_type = 'i';
}

void Integer::print(std::ostream &dst, int indentation) const { dst << value; }

int Integer::evaluate(const Binding &_binding) const { return value; }

int Integer::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for integer\n");
  printf("li $%d,%d\t\t# load %d\n", reg, value, value);
  return 0;
}

void Integer::bind(const Binding &_binding) {}

////////////////////////////////////////
// Variable
////////////////////////////////////////

Variable::Variable(const std::string &_id) : id(_id) {
  logger->info("construct Variable\n");
  node_type = 'x';
}

void Variable::print(std::ostream &dst, int indentation) const { dst << id; }

int Variable::evaluate(const Binding &_binding) const {
  if (_binding.find(id) == _binding.end()) {
    logger->error("%s has not been declared", id.c_str());
    exit(1);
  }
  // return binding.at(id)->evaluate(_binding);
  return 0;
}

int Variable::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for variable\n");
  if (binding.find(id) == binding.end()) {
    logger->error("\"%s\" has not been declared\n", id.c_str());
    exit(1);
  }
  printf("lw $%d,%d($fp)\t# load %s\n", reg, binding.at(id), id.c_str());
  return 0;
}

int Variable::getPos(const Binding &_binding) const {
  if (binding.find(id) == binding.end()) {
    logger->error("\"%s\" has not been declared\n", id.c_str());
    exit(1);
  }
  return binding.find(id)->second;
}

void Variable::bind(const Binding &_binding) {
  binding = _binding;
  logger->debug("binding...variable\n");
}
