#include "ast.hpp"

////////////////////////////////////////
// Function
////////////////////////////////////////

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   int _pos)
    : type(_type), name(_name), statements(_statements) {
  int tmp_size = _pos + 8;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  //size = size + 16;
  logger->info("construct Function\n");
  node_type = 'F';
}

void Function::print(std::ostream &dst, int indentation) const {
  logger->info("====================\n");
  logger->info("formatted: \n");
  printIndent(dst, indentation);
  dst << type;
  dst << " ";
  dst << name;
  dst << "() {\n";
  statements->print(dst, indentation);
  dst << "}";
}

int Function::evaluate(const Binding &_binding) const {
  return statements->evaluate(binding);
}

int Function::codeGen(const Binding &_binding, int reg) const {
  logger->info("====================\n");
  logger->info("Build variable mapping in Function\n");
  ((StatementList *)statements)->bind(_binding);

  logger->info("====================\n");
  logger->info("generate code for Function\n");
  logger->info("size of stack frame: %d\n", getSize());
  printf(".globl\t%s\n", name.c_str());
  // printf(".ent\t%s\n", name.c_str());
  printf("\n");
  printf("%s:\n", name.c_str());
  // printf(".frame\t$fp,%d,$31\n", size);

  printf("addiu $sp,$sp,%d\n", -size);
  printf("sw $fp,%d($sp)\n", (size - 4));
  printf("move $fp,$sp\n");
  statements->codeGen(binding, 2);  // store  result result of to $2
  printf("move $sp,$fp\n");
  printf("lw $fp,%d($sp)\n", (size - 4));
  printf("addiu $sp,$sp,%d\n", size);
  printf("jr $31\n");
  printf("nop\n");
  printf("\n");

  // printf(".end\t%s\n", name.c_str());
  return 0;
}

void Function::bind(const Binding &_binding) {}
