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
  dst << "(";
  left->print(dst, indentation);
  dst << "+";
  right->print(dst, indentation);
  dst << ")";
}

int Addition::evaluate(Binding *binding) const {
  return left->evaluate(binding) + right->evaluate(binding);
}

int Addition::codeGen(Binding *binding, int reg) const {
  // left can be int, var, expr;
  // right also can be int, var, expr;
  // so there are 9 possible combinations in total
  int left_type = left->getType();
  int right_type = right->getType();

  switch (left_type) {
    case 'i': {  // left is integer
      switch (right_type) {
        case 'i': {  // right is integer
          int res = evaluate(binding);
          printf("li $2,%d\n", res);
          break;
        }
        case 'x': {  // right is variable
          printf("lw $2,%d($fp)\n", right->getPos(*binding));
          printf("addiu $2,$2,%d\n", left->evaluate(binding));
          break;
        }
        default: {  // right is expression
          right->codeGen(binding, reg);
          printf("addiu $2,$2,%d\n", left->evaluate(binding));
          break;
        }
      }
      break;
    }
    case 'x': {  // left is variable
      switch (right_type) {
        case 'i': {  // right is integer
          printf("lw $2,%d($fp)\t# from var\n", left->getPos(*binding));
          printf("addiu $2,$2,%d\n", right->evaluate(binding));
          break;
        }
        case 'x': {  // right is variable
          printf("lw $2,%d($fp)\t# from var\n", left->getPos(*binding));
          printf("lw $3,%d($fp)\t# from var\n", right->getPos(*binding));
          printf("addu $2,$3,$2\n");
          break;
        }
        default: {  // right is expression
          right->codeGen(binding, reg);
          printf("lw $2,%d($fp)\t# from var\n", left->getPos(*binding));
          printf("lw $3,%d($fp)\t# from expr\n", right->getPos(*binding));
          printf("addu $2,$3,$2\n");
          break;
        }
      }
      break;
    }
    default: {  // left is expression
      switch (right_type) {
        case 'i': {  // right is integer
          left->codeGen(binding, reg);
          printf("lw $2,%d($fp)\t# from expr\n", left->getPos(*binding));
          printf("addiu $2,$2,%d\n", right->evaluate(binding));
          break;
        }
        case 'x': {  // right is variable
          left->codeGen(binding, reg);
          printf("lw $2,%d($fp)\t# from expr\n", left->getPos(*binding));
          printf("lw $3,%d($fp)\t# from var\n", right->getPos(*binding));
          printf("addu $2,$3,$2\n");
          break;
        }
        default: {  // right is expression
          left->codeGen(binding, reg);
          right->codeGen(binding, reg);
          printf("lw $2,%d($fp)\t# from expr\n", left->getPos(*binding));
          printf("lw $3,%d($fp)\t# from expr\n", right->getPos(*binding));
          printf("addu $2,$3,$2\n");
          break;
        }
      }
      break;
    }
  }
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
  dst << "(";
  left->print(dst, indentation);
  dst << "-";
  right->print(dst, indentation);
  dst << ")";
}

int Subtraction::evaluate(Binding *binding) const {
  return left->evaluate(binding) - right->evaluate(binding);
}

int Subtraction::codeGen(Binding *binding, int reg) const {
  left->codeGen(binding, 2);
  right->codeGen(binding, 2);
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
  fprintf(stderr, "construct ExpOperator\n");
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

////////////////////////////////////////
// Postfix increment
////////////////////////////////////////

Increment_Post::Increment_Post(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct postfix increment\n");
}

void Increment_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "++";
  dst << ")";
}

int Increment_Post::evaluate(Binding *binding) const {
  //int result = left->evaluate(binding)+1;
  return left->evaluate(binding);
}

////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Increment_Pre::Increment_Pre(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct prefix increment\n");
}

void Increment_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "++";
  left->print(dst, indentation);
  dst << ")";
}

int Increment_Pre::evaluate(Binding *binding) const {
  return (left->evaluate(binding)+1);
}

////////////////////////////////////////
// Postfix decrement
////////////////////////////////////////

Decrement_Post::Decrement_Post(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct postfix increment\n");
}

void Decrement_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "--";
  dst << ")";
}

int Decrement_Post::evaluate(Binding *binding) const {
  //int result = left->evaluate(binding)-1;
  return left->evaluate(binding);
}

////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Decrement_Pre::Decrement_Pre(ProgramPtr _left) : left(_left) {
  fprintf(stderr, "construct prefix increment\n");
}

void Decrement_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "--";
  left->print(dst, indentation);
  dst << ")";
}

int Decrement_Pre::evaluate(Binding *binding) const {
  return (left->evaluate(binding)-1);
}



