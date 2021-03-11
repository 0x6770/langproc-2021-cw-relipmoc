#include "ast.hpp"

////////////////////////////////////////
// Addition Equal
////////////////////////////////////////

AddEqual::AddEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct +=\n");
}

void AddEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "+=";
  right->print(dst, indentation);
  dst << ";\n";
}

int AddEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) + right->evaluate(_binding);
}

int AddEqual::codeGen(const Binding &_binding, int reg) const { 
  int right_type = right->getType();
  right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("add $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  return 0;
}

void AddEqual::passFunctionName(std::string _name,int _pos){
      function_name = _name;
      pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}

////////////////////////////////////////
// Subtraction Equal
////////////////////////////////////////

SubEqual::SubEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct -=\n");
}

void SubEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "-=";
  right->print(dst, indentation);
  dst << ";\n";
}

int SubEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) - right->evaluate(_binding);
}

int SubEqual::codeGen(const Binding &_binding, int reg) const { 
  int right_type = right->getType();
  right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("sub $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for sub equal" << std::endl;
  return 0;
}


void SubEqual::passFunctionName(std::string _name,int _pos){
      function_name = _name;
      pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// Product assignment
////////////////////////////////////////

MulEqual::MulEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct *=\n");
}

void MulEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "*=";
  right->print(dst, indentation);
  dst << ";\n";
}

int MulEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) * right->evaluate(_binding);
}

int MulEqual::codeGen(const Binding &_binding, int reg) const {
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("mult $2,$3\n");
  printf("mflo $2\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for mul equal" << std::endl;
  return 0;
 }

void MulEqual::passFunctionName(std::string _name,int _pos){
      function_name = _name;
      pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// Quotient assignment
////////////////////////////////////////

QuoEqual::QuoEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct /=\n");
}

void QuoEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "/=";
  right->print(dst, indentation);
  dst << ";\n";
}

int QuoEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) / right->evaluate(_binding);
}

int QuoEqual::codeGen(const Binding &_binding, int reg) const {
int right_type = right->getType();
 right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("div $2,$3\n");
  printf("mflo $2\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for quo equal" << std::endl;
  return 0;

 }

void QuoEqual::passFunctionName(std::string _name,int _pos){
      function_name = _name;
      pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// Modulus assignment
////////////////////////////////////////

ModEqual::ModEqual(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct %%=\n");
}

void ModEqual::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "%=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ModEqual::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) % right->evaluate(_binding);
}
int ModEqual::codeGen(const Binding &_binding, int reg) const {
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("div $2,$3\n");
  printf("mfhi $2\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for modulus equal" << std::endl;
  return 0;

 }

 void ModEqual::passFunctionName(std::string _name,int _pos){
       function_name = _name;
       pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}

////////////////////////////////////////
// shift left assignment
////////////////////////////////////////

ShiftEqual_L::ShiftEqual_L(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct <<=\n");
}

void ShiftEqual_L::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "<<=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ShiftEqual_L::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) << right->evaluate(_binding);
}

int ShiftEqual_L::codeGen(const Binding &_binding, int reg) const { 
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("sll $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for shift left equal" << std::endl;
  return 0;
}

void ShiftEqual_L::passFunctionName(std::string _name,int _pos){
      function_name = _name;
      pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// shift right assignment
////////////////////////////////////////

ShiftEqual_R::ShiftEqual_R(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct >>=\n");
}

void ShiftEqual_R::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << ">>=";
  right->print(dst, indentation);
  dst << ";\n";
}

int ShiftEqual_R::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) >> right->evaluate(_binding);
}

int ShiftEqual_R::codeGen(const Binding &_binding, int reg) const {
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
  printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("sra $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for shift right equal" << std::endl;
  return 0;
 }
void ShiftEqual_R::passFunctionName(std::string _name,int _pos){
      function_name = _name;
      pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}

////////////////////////////////////////
// bitwise AND assignment
////////////////////////////////////////

BitwiseEqual_AND::BitwiseEqual_AND(ProgramPtr _left, ProgramPtr _right,
                                   int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct &=\n");
}

void BitwiseEqual_AND::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "&=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_AND::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) & right->evaluate(_binding);
}

int BitwiseEqual_AND::codeGen(const Binding &_binding, int reg) const {
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("and $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for bitwise and equal" << std::endl;
  return 0;
}

void BitwiseEqual_AND::passFunctionName(std::string _name,int _pos){
      function_name = _name;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// bitwise OR assignment
////////////////////////////////////////

BitwiseEqual_OR::BitwiseEqual_OR(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct |=\n");
}

void BitwiseEqual_OR::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "|=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_OR::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) | right->evaluate(_binding);
}

int BitwiseEqual_OR::codeGen(const Binding &_binding, int reg) const {
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("or $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for bitwise or equal" << std::endl;
  return 0;
}
void BitwiseEqual_OR::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// bitwise XOR assignment
////////////////////////////////////////

BitwiseEqual_XOR::BitwiseEqual_XOR(ProgramPtr _left, ProgramPtr _right,
                                   int _pos)
    : Operation(_left, _right, _pos) {
  fprintf(stderr, "construct ^=\n");
}

void BitwiseEqual_XOR::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  left->print(dst, indentation);
  dst << "^=";
  right->print(dst, indentation);
  dst << ";\n";
}

int BitwiseEqual_XOR::evaluate(const Binding &_binding) const {
  return left->evaluate(_binding) ^ right->evaluate(_binding);
}

int BitwiseEqual_XOR::codeGen(const Binding &_binding, int reg) const {
  int right_type = right->getType();
   right->codeGen(binding,3);
  left->codeGen(binding,2);
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  printf("xor $2,$2,$3\n");
  printf("sw $2,%d($fp)\n",left->getPos(binding));
  //std::cout << "sw $2,"  << left->getPos(binding) << "($fp)"<< "\t" << "#store the result for bitwise xor equal" << std::endl;
  return 0;
}
void BitwiseEqual_XOR::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// Postfix increment
////////////////////////////////////////

Increment_Post::Increment_Post(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {   
  fprintf(stderr, "construct increment prefix\n");
}

void Increment_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "++";
  dst << ")";
}

int Increment_Post::evaluate(const Binding &_binding) const {
  // int result = left->evaluate(_binding)+1;
  return left->evaluate(_binding);
}

int Increment_Post::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  left->codeGen(binding, 2);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));

  printf("addiu $3,$2,1\n");
  printf("sw $2,%d($fp)\t# store result of post_decrement\n", pos);
  printf("sw $3,%d($fp)\t# store result of post_decrement\n", left->getPos(binding));
  return 0;
}
void Increment_Post::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
}

////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Increment_Pre::Increment_Pre(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  fprintf(stderr, "construct increment prefix\n");
}

void Increment_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "++";
  left->print(dst, indentation);
  dst << ")";
}

int Increment_Pre::evaluate(const Binding &_binding) const {
  return (left->evaluate(_binding) + 1);
}

int Increment_Pre::codeGen(const Binding &_binding, int reg) const { 
  int left_type = left->getType();
  left->codeGen(binding, 2);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  printf("addiu $2,$2,1 # %d\n",pos);
  printf("sw $2,%d($fp)\t# store result of pre_increment\n",pos);
  printf("sw $2,%d($fp)\t# store result of pre_increment\n",left->getPos(binding));
  return 0; }
void Increment_Pre::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// Postfix decrement
////////////////////////////////////////

Decrement_Post::Decrement_Post(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  fprintf(stderr, "construct decrement postfix\n");
}

void Decrement_Post::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "--";
  dst << ")";
}

int Decrement_Post::evaluate(const Binding &_binding) const {
  // int result = left->evaluate(_binding)-1;
  return left->evaluate(_binding);
}

int Decrement_Post::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  left->codeGen(binding, 2);

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));

  printf("addiu $3,$2,-1\n");
  printf("sw $2,%d($fp)\t# store result of post_decrement\n", pos);
  printf("sw $3,%d($fp)\t# store result of post_decrement\n", left->getPos(binding));
  return 0;
}

void Decrement_Post::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// prefix increment
////////////////////////////////////////

Decrement_Pre::Decrement_Pre(ProgramPtr _left, int _pos)
    : Operation(_left, 0, _pos) {
  fprintf(stderr, "construct decrement prefix\n");
}

void Decrement_Pre::print(std::ostream &dst, int indentation) const {
  dst << "(";
  dst << "--";
  left->print(dst, indentation);
  dst << ")";
}

int Decrement_Pre::evaluate(const Binding &_binding) const {
  return (left->evaluate(_binding) - 1);
}

int Decrement_Pre::codeGen(const Binding &_binding, int reg) const { 
  int left_type = left->getType();
  left->codeGen(binding, 2);
  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));

  printf("addiu $2,$2,-1\n");
  printf("sw $2,%d($fp)\t# store result of pre_decrement\n", left->getPos(binding));
  printf("sw $2,%d($fp)\t# store result of pre_decrement\n", pos);
  return 0; }
void Decrement_Pre::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
}