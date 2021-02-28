#include "ast.hpp"

////////////////////////////////////////
// Integer
////////////////////////////////////////

Integer::Integer(int _value) : value(_value) {
  logger->info("construct Integer\n");
  node_type = 'i';
}

void Integer::print(std::ostream &dst, int indentation) const { dst << value; }

int Integer::evaluate(Binding *binding) const { return value; }

int Integer::codeGen(Binding *binding, int reg) const {
  logger->info("generate code for integer\n");
  printf("li $%d,%d\t\t# load %d\n", reg, value, value);
  return 0;
}

////////////////////////////////////////
// Variable
////////////////////////////////////////

Variable::Variable(const std::string &_id) : id(_id) {
  logger->info("construct Variable\n");
  node_type = 'x';
}

void Variable::print(std::ostream &dst, int indentation) const { dst << id; }

int Variable::evaluate(Binding *binding) const {
  if (binding->find(id) == binding->end()) {
    logger->error("%s has not been declared", id.c_str());
    exit(1);
  }
  // return binding->at(id)->evaluate(binding);
  return 0;
}

int Variable::codeGen(Binding *binding, int reg) const {
  logger->info("generate code for variable\n");
  if (binding->find(id) == binding->end()) {
    logger->error("variable is not declared\n");
    exit(1);
  }
  printf("lw $%d,%d($fp)\t# load %s\n", reg, binding->at(id), id.c_str());
  return 0;
}

const int &Variable::getPos(const Binding &binding) const {
  assert(binding.find(id) != binding.end());
  return binding.find(id)->second;
}
