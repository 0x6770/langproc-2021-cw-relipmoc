#include "ast.hpp"

////////////////////////////////////////
// Operation
////////////////////////////////////////

Operation::Operation(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right) {
  logger->info("construct Operation\n");
  pos = _pos;
}

void Operation::print(std::ostream &dst, int indentation) const {}

int Operation::codeGen(const Binding &_binding, int reg) const { return 0; }

int Operation::evaluate(const Binding &_binding) const { return 0; }

void Operation::bind(const Binding &_binding) {
  if (left) ((Program *)left)->bind(_binding);
  if (right) ((Program *)right)->bind(_binding);
}
