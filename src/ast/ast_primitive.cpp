#include "ast.hpp"

////////////////////////////////////////
// Integer
////////////////////////////////////////

Integer::Integer(int _value) : value(_value) {
  fprintf(stderr, "construct Integer\n");
  node_type = 'i';
}
void Integer::print(std::ostream &dst, int indentation) const { dst << value; }
int Integer::evaluate(Binding *binding) const { return value; }

////////////////////////////////////////
// Variable
////////////////////////////////////////

Variable::Variable(const std::string &_id) : id(_id) {
  fprintf(stderr, "construct Variable\n");
}

void Variable::print(std::ostream &dst, int indentation) const { dst << id; }
int Variable::evaluate(Binding *binding) const {
  if (binding->find(id) == binding->end()) {
    fprintf(stdout, "%s has not been declared", id.c_str());
    exit(1);
  }
  return binding->at(id)->evaluate(binding);
}
