#include "ast/ast_assignments.hpp"

////////////////////////////////////////
// Addition Equal
////////////////////////////////////////

AddEqual::AddEqual(ProgramPtr _left, ProgramPtr _right,int _pos)
    : left(_left), right(_right),pos(_pos) {
  fprintf(stderr, "construct Addition assigment\n");
}

void AddEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "+=";
  right->print(dst, indentation);
  dst << ";\n";
}

int AddEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding)+right->evaluate(binding);
}

int AddEqual::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("add $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
}



////////////////////////////////////////
// Subtraction Equal
////////////////////////////////////////

SubEqual::SubEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos) {
  fprintf(stderr, "construct Addition assigment\n");
}

void SubEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "-=";
  right->print(dst, indentation);
  dst << ";\n";
}

int SubEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) - right->evaluate(binding);
}

int SubEqual::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("sub $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
  return 0; }

////////////////////////////////////////
// Product assignment
////////////////////////////////////////

MulEqual::MulEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos){
  fprintf(stderr, "construct Addition assigment\n");
}

void MulEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "*=";
  right->print(dst, indentation);
  dst << ";\n";
}

int MulEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) * right->evaluate(binding);
}

int MulEqual::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("mult $2,$3\n");
  printf("mflo $2\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  return 0; }

////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

QuoEqual::QuoEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos){
  fprintf(stderr, "construct Addition assigment\n");
}

void QuoEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "/=";
  right->print(dst, indentation);
  dst << ";\n";
  
}

int QuoEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) / right->evaluate(binding);
}

int QuoEqual::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("div $2,$3\n");
  printf("mflo $2\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
 }

////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

ModEqual::ModEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos) {
  fprintf(stderr, "construct Addition assigment\n");
}

void ModEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "%=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ModEqual::evaluate(Binding *binding) const {
  return left->evaluate(binding) % right->evaluate(binding);
}
int ModEqual::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("div $2,$3\n");
  printf("mfhi $2\n");

  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
 }

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

ShiftEqual_L::ShiftEqual_L(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right) ,pos(_pos){
  fprintf(stderr, "construct Addition assigment\n");
}

void ShiftEqual_L::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "<<=";
  right->print(dst, indentation);
  dst << ";\n";
  
}

int ShiftEqual_L::evaluate(Binding *binding) const {
  return left->evaluate(binding) << right->evaluate(binding);
}

int ShiftEqual_L::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("sll $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
 }

////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

ShiftEqual_R::ShiftEqual_R(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos) {
  fprintf(stderr, "construct Addition assigment\n");
}

void ShiftEqual_R::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << ">>=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ShiftEqual_R::evaluate(Binding *binding) const {
  return left->evaluate(binding) >> right->evaluate(binding);
}

int ShiftEqual_R::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("slr $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
}

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

BitwiseEqual_AND::BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos) {
  fprintf(stderr, "construct Addition assigment\n");
}

void BitwiseEqual_AND::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "&=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_AND::evaluate(Binding *binding) const {
  return left->evaluate(binding) & right->evaluate(binding);
}

int BitwiseEqual_AND::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("and $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
 }

////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

BitwiseEqual_OR::BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right, int _pos)
    : left(_left), right(_right), pos(_pos){
  fprintf(stderr, "construct Addition assigment\n");
}

void BitwiseEqual_OR::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "|=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_OR::evaluate(Binding *binding) const {
  return left->evaluate(binding) | right->evaluate(binding);
}

int BitwiseEqual_OR::codeGen(Binding *binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("or $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
 }

////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

BitwiseEqual_XOR::BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right,int _pos)
    : left(_left), right(_right),pos(_pos) {
  fprintf(stderr, "construct Addition assigment\n");
}

void BitwiseEqual_XOR::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "^=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_XOR::evaluate(Binding *binding) const {
  return left->evaluate(binding) ^ right->evaluate(binding);
}

int BitwiseEqual_XOR::codeGen(Binding *binding, int reg) const { 
  int left_type = left->getType();
  int right_type = right->getType();
  right->codeGen(binding,2);
  left->codeGen(binding,3);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(*binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(*binding));
  printf("xor $2,$2,$3\n");
  std::cout << "sw $2,"  << left->getPos(*binding) << "($fp)"<< "\t" << "store the result for add equal" << std::endl;
  
  return 0;
 }

