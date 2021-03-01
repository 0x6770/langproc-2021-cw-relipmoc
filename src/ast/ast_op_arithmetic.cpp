#include "ast.hpp"

////////////////////////////////////////
// Addition
////////////////////////////////////////

Addition::Addition(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct Addition\n");
  node_type = 'a';
}

void Addition::print(std::ostream &dst, int indentation) const {
  int indent = indentation;
  printIndent(dst, indentation);
  dst << "(";
  left->print(dst, 0);
  dst << "+";
  right->print(dst, 0);
  dst << ")";
  if (indent) {
    dst << "\n";
  }
}

int Addition::evaluate(Binding *binding) const {
  return left->evaluate(binding) + right->evaluate(binding);
}

int Addition::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));

  printf("add $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of addition\n", pos);

  return 0;
}

////////////////////////////////////////
// Subtraction
////////////////////////////////////////

Subtraction::Subtraction(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct subOperator\n");
}

void Subtraction::print(std::ostream &dst, int indentation) const {
  int indent = indentation;
  printIndent(dst, indentation);
  dst << "(";
  left->print(dst, 0);
  dst << "-";
  right->print(dst, 0);
  dst << ")";
  if (indent) {
    dst << "\n";
  }
}

int Subtraction::evaluate(Binding *binding) const {
  return left->evaluate(binding) - right->evaluate(binding);
}

int Subtraction::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  left->codeGen(binding, 2);
  right->codeGen(binding, 3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));

  printf("sub $2,$2,$3\n");
  printf("sw $2,%d($fp)\t# store result of addition\n", pos);

  return 0;
}

////////////////////////////////////////
// Multiplication
////////////////////////////////////////

Multiplication::Multiplication(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct MulOperator\n");
}

void Multiplication::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "*";
  right->print(dst, indentation);
  dst << ")";
}

int Multiplication::evaluate(Binding *binding) const {
  return left->evaluate(binding) * right->evaluate(binding);
}

int Multiplication::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// Division
////////////////////////////////////////

Division::Division(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct DivOperator\n");
}

void Division::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "/";
  right->print(dst, indentation);
  dst << ")";
}

int Division::evaluate(Binding *binding) const {
  return left->evaluate(binding) / right->evaluate(binding);
}

int Division::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// Modulus
////////////////////////////////////////

Modulus::Modulus(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ModOperator\n");
}

void Modulus::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "%";
  right->print(dst, indentation);
  dst << ")";
}

int Modulus::evaluate(Binding *binding) const {
  return (left->evaluate(binding) % right->evaluate(binding));
}

int Modulus::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
  return 0;
}
////////////////////////////////////////
// Postfix increment
////////////////////////////////////////

Increment_Post::Increment_Post(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct increment prefix\n");
}

void Increment_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "++";
  dst << ")";
}

int Increment_Post::evaluate(Binding *binding) const {
  // int result = left->evaluate(binding)+1;
  return left->evaluate(binding);
}

int Increment_Post::codeGen(Binding *binding, int reg) const { return 0; }

////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Increment_Pre::Increment_Pre(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct increment prefix\n");
}

void Increment_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "++";
  left->print(dst, indentation);
  dst << ")";
}

int Increment_Pre::evaluate(Binding *binding) const {
  return (left->evaluate(binding) + 1);
}

int Increment_Pre::codeGen(Binding *binding, int reg) const { return 0; }

////////////////////////////////////////
// Postfix decrement
////////////////////////////////////////

Decrement_Post::Decrement_Post(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct decrement postfix\n");
}

void Decrement_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "--";
  dst << ")";
}

int Decrement_Post::evaluate(Binding *binding) const {
  // int result = left->evaluate(binding)-1;
  return left->evaluate(binding);
}

int Decrement_Post::codeGen(Binding *binding, int reg) const { return 0; }

////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Decrement_Pre::Decrement_Pre(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct decrement prefix\n");
}

void Decrement_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "--";
  left->print(dst, indentation);
  dst << ")";
}

int Decrement_Pre::evaluate(Binding *binding) const {
  return (left->evaluate(binding) - 1);
}

int Decrement_Pre::codeGen(Binding *binding, int reg) const { return 0; }
