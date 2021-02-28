#include "ast.hpp"

////////////////////////////////////////
// Operation
////////////////////////////////////////

Operation::Operation(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right) {
  pos = _pos;
  fprintf(stderr, "construct Operation\n");
}

void Operation::print(std::ostream &dst, int indentation) const {}

int Operation::codeGen(Binding *binding, int reg) const { return 0; }

int Operation::evaluate(Binding *binding) const { return 0; }
