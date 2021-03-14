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

int Addition::evaluate(const Binding &_binding) const {
  return left->evaluate(binding) + right->evaluate(binding);
}

int Addition::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();
  if ((left_type == 'i' && right_type != 'i') ||
      (left_type == 'x' && right_type != 'x')) {
    right->codeGen(binding, 3);
    left->codeGen(binding, 2);
  } else {
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("\tlw\t$2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("\tlw\t$3,%d($fp)\n", right->getPos(binding));

  printf("\tadd\t$2,$2,$3\n");
  printf("\tsw\t$2,%d($fp)\t# store result of addition\n", pos);

  return 0;
}

void Addition::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
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

int Subtraction::evaluate(const Binding &_binding) const {
  return left->evaluate(binding) - right->evaluate(binding);
}

int Subtraction::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if ((left_type == 'i' && right_type != 'i') ||
      (left_type == 'x' && right_type != 'x')) {
    right->codeGen(binding, 3);
    left->codeGen(binding, 2);
  } else {
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("\tlw\t$2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("\tlw\t$3,%d($fp)\n", right->getPos(binding));

  printf("\tsub\t$2,$2,$3\n");
  printf("\tsw\t$2,%d($fp)\t# store result of subtraction\n", pos);

  return 0;
}

void Subtraction::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
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

int Multiplication::evaluate(const Binding &_binding) const {
  return left->evaluate(binding) * right->evaluate(binding);
}

int Multiplication::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if ((left_type == 'i' && right_type != 'i') ||
      (left_type == 'x' && right_type != 'x')) {
    right->codeGen(binding, 3);
    left->codeGen(binding, 2);
  } else {
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("\tlw\t$2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("\tlw\t$3,%d($fp)\n", right->getPos(binding));

  printf("\tmult\t$2,$3\n");
  printf("\tmflo\t$2\n");
  printf("\tsw\t$2,%d($fp)\t# store result of multiplication\n", pos);

  return 0;
}

void Multiplication::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
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

int Division::evaluate(const Binding &_binding) const {
  return left->evaluate(binding) / right->evaluate(binding);
}

int Division::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if ((left_type == 'i' && right_type != 'i') ||
      (left_type == 'x' && right_type != 'x')) {
    right->codeGen(binding, 3);
    left->codeGen(binding, 2);
  } else {
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("\tlw\t$2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("\tlw\t$3,%d($fp)\n", right->getPos(binding));

  printf("\tdiv\t$2,$3\n");
  printf("\tmflo\t$2\n");
  printf("\tsw\t$2,%d($fp)\t# store result of division\n", pos);

  return 0;
}

void Division::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
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

int Modulus::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) % right->evaluate(binding));
}

int Modulus::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if ((left_type == 'i' && right_type != 'i') ||
      (left_type == 'x' && right_type != 'x')) {
    right->codeGen(binding, 3);
    left->codeGen(binding, 2);
  } else {
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("\tlw\t$2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("\tlw\t$3,%d($fp)\n", right->getPos(binding));

  printf("\tdiv\t$2,$3\n");
  printf("\tmfhi\t$2\n");
  printf("\tsw\t$2,%d($fp)\t# store result of modulus\n", pos);

  return 0;
}

void Modulus::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  ((Program *)left)->passFunctionName(_name, _pos);
  ((Program *)right)->passFunctionName(_name, _pos);
}

////////////////////////////////////////
// Negation
////////////////////////////////////////

Negation::Negation(ProgramPtr _right, int _pos) : Operation(0, _right, _pos) {
  fprintf(stderr, "construct Negation\n");
}

void Negation::print(std::ostream &dst, int indentation) const {
  dst << "-";
  dst << "(";
  right->print(dst, indentation);
  dst << ")";
}

int Negation::evaluate(const Binding &_binding) const {
  return -(right->evaluate(binding));
}

int Negation::codeGen(const Binding &_binding, int reg) const {
  right->codeGen(binding, 2);
  printf("\tsub\t$2,$0,$2\n");
  printf("\tsw\t$2,%d($fp)\t# store result of Negation\n", pos);

  return 0;
}

void Negation::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  pos = pos + _pos;
  //((Program*)left)->passFunctionName(_name);
  ((Program *)right)->passFunctionName(_name, _pos);
}
