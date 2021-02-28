#include "ast.hpp"

////////////////////////////////////////
// Function
////////////////////////////////////////

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   int _pos)
    : type(_type), name(_name), statements(_statements) {
  int tmp_size = _pos + 8;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  fprintf(stderr, "construct Function\n");
  node_type = 'F';
}

void Function::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << type;
  dst << " ";
  dst << name;
  dst << "() {\n";
  statements->print(dst, indentation);
  dst << "}";
}

int Function::evaluate(Binding *binding) const {
  return statements->evaluate(binding);
}

int Function::codeGen(Binding *binding, int reg) const {
  fprintf(stderr, "generate code for function\n");
  printf("addiu $sp,$sp,%d\n", -size);
  printf("sw $fp,(%d)$sp\n", (size - 4));
  printf("move $fp,$sp\n");
  statements->codeGen(binding, 2);  // store  result result of to $2
  printf("move $sp,$fp\n");
  printf("lw $fp,(%d)$sp\n", (size - 4));
  printf("addiu $sp,$sp,%d\n", size);
  printf("jr $31\n");
  printf("nop\n");
  return 0;
}
