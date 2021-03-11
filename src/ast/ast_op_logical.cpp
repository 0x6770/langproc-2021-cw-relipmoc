#include "ast.hpp"

////////////////////////////////////////
// LessEqual
////////////////////////////////////////

LessEqual::LessEqual(ProgramPtr _left, ProgramPtr _right, int _pos,
                     int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  logger->info("construct LessEqual\n");
}

void LessEqual::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  if (is_equal == 1) {
    dst << "<=";
  } else {
    dst << "<";
  }
  right->print(dst, indentation);
  dst << ")";
}

int LessEqual::evaluate(const Binding &_binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) <= right->evaluate(binding));
  } else {
    return (left->evaluate(binding) < right->evaluate(binding));
  }
}

int LessEqual::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if(left_type == 'i' && right_type != 'i'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));
  

  if (is_equal == 1) {
    printf("slt $2,$3,$2\n");
    printf("xori $2,$2,0x1\n");
  }
  else{
    printf("slt $2,$2,$3\n");
  }
  printf("andi $2,$2,0x00ff\n");
  // TODO: there is also a line " andi $2,$2,0x00ff" in the online converter.
  printf("sw $2,%d($fp)\t# store result of logical less or less equal\n", pos);

  return 0;
}
void LessEqual::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}

////////////////////////////////////////
// GreaterEqual
////////////////////////////////////////

GreaterEqual::GreaterEqual(ProgramPtr _left, ProgramPtr _right, int _pos,
                           int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  logger->info("construct GreaterEqual\n");
}

void GreaterEqual::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  if (is_equal == 1) {
    dst << ">=";
  } else {
    dst << ">";
  }
  right->print(dst, indentation);
  dst << ")";
}

int GreaterEqual::evaluate(const Binding &_binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) >= right->evaluate(binding));
  } else {
    return (left->evaluate(binding) > right->evaluate(binding));
  }
}

int GreaterEqual::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if(left_type == 'i' && right_type != 'i'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));

  printf("slt $2,$3,$2\n");
  if (is_equal == 1) {
    printf("xori $2,$2,0x1\n");
  }
  printf("sw $2,%d($fp)\t# store result of logical greater or greater than\n",
         pos);

  return 0;
}

void GreaterEqual::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// Equal
////////////////////////////////////////

Equal::Equal(ProgramPtr _left, ProgramPtr _right, int _pos, int _is_equal)
    : Operation(_left, _right, _pos), is_equal(_is_equal) {
  logger->info("construct Equal\n");
}

void Equal::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  if (is_equal == 1) {
    dst << "!=";
  } else {
    dst << "==";
  }
  right->print(dst, indentation);
  dst << ")";
}

int Equal::evaluate(const Binding &_binding) const {
  if (is_equal == 1) {
    return (left->evaluate(binding) != right->evaluate(binding));
  } else {
    return (left->evaluate(binding) == right->evaluate(binding));
  }
}

int Equal::codeGen(const Binding &_binding, int reg) const {
  int left_type = left->getType();
  int right_type = right->getType();

  if(left_type == 'i' && right_type != 'i'){
        right->codeGen(binding, 3);
        left->codeGen(binding, 2);
  }
  else{
    left->codeGen(binding, 2);
    right->codeGen(binding, 3);
  }

  if (!((left_type == 'i') | (left_type == 'x')))
    printf("lw $2,%d($fp)\n", left->getPos(binding));
  if (!((right_type == 'i') | (right_type == 'x')))
    printf("lw $3,%d($fp)\n", right->getPos(binding));

  printf("xor $2,$2,$3\n");
  if (is_equal == 1) {
    printf("sltu $2,$0,$2\n");
  } else {
    printf("sltiu $2,$2,1\n");
  }
  printf(
      "sw $2,%d($fp)\t# store result of logical equal or logical not equal\n",
      pos);

  return 0;
}

void Equal::passFunctionName(std::string _name,int _pos){
    function_name = _name;
    pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}
////////////////////////////////////////
// LogicalAnd
////////////////////////////////////////

LogicalAnd::LogicalAnd(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct LogicalAnd\n");
}

void LogicalAnd::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "&&";
  right->print(dst, indentation);
  dst << ")";
}

int LogicalAnd::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) && right->evaluate(binding));
}

int LogicalAnd::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(binding, 2);
  std::string labelL2 = "F" + function_name + "_2a_"  + std::to_string(pos); 
  std::string labelL3 = "F" +  function_name + "_3a_"  + std::to_string(pos);
  printf("\tnop\n");
  // TODO： add counter to create unique label:
  //std::cout << "\tbeq $0,$2,"
  //          << labelL2 << std::endl;
  printf("\tbeq $0,$2,%s\n",labelL2.c_str());
  printf("\tnop\n");  // Add empty delay slot

  right->codeGen(binding, 2);
  printf("\tnop\n");
  // TODO： add counter to create unique label:
  //std::cout << "\tbeq $0,$2,"
  //          << labelL2 << std::endl;
  printf("\tbeq $0,$2,%s\n",labelL2.c_str());
  printf("\tnop\n");

  printf("\tli $2,1\n");
  printf("b %s\n",labelL3.c_str());  // TODO： add counter to create unique label:
  //std::cout << "\tb " << labelL3 << std::endl;
  printf("\tnop\n");   // Add empty delay slot
  printf("%s:\n",labelL2.c_str());
  //std::cout <<  "\t"<<labelL2 <<":" << std::endl;
  printf("\tmove $2,$0\n");
  printf("%s:\n",labelL3.c_str());
  //std::cout << "\t" <<labelL3 <<":" << std::endl;
  printf("\tsw $2,%d($fp)\t# store result of logical and\n", pos);
  printf("\tlw $2,%d($fp)\n", pos);

  return 0;
}

void LogicalAnd::passFunctionName(std::string _name,int _pos){
     function_name = _name;
     pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}

////////////////////////////////////////
// LogicalOr
////////////////////////////////////////

LogicalOr::LogicalOr(ProgramPtr _left, ProgramPtr _right, int _pos)
    : Operation(_left, _right, _pos) {
  logger->info("construct LogicalOr\n");
}

void LogicalOr::print(std::ostream &dst, int indentation) const {
  dst << "(";
  left->print(dst, indentation);
  dst << "||";
  right->print(dst, indentation);
  dst << ")";
}

int LogicalOr::evaluate(const Binding &_binding) const {
  return (left->evaluate(binding) || right->evaluate(binding));
}

int LogicalOr::codeGen(const Binding &_binding, int reg) const {
  left->codeGen(binding, 2);
  printf("nop\n");
  std::string labelL2 = "F" + function_name + "L2_or"  + std::to_string(pos); 
  std::string labelL3 = "F" + function_name + "L3_or"  + std::to_string(pos);
  std::string labelL4 = "F" + function_name + "L4_or"  + std::to_string(pos);
  // TODO： add counter to create unique label:
  //std::cout << "bne $2,$0,"
  //          << labelL2 << std::endl;
  printf("\tbne $2,$0,%s\n",labelL2.c_str());
  printf("nop\n");  // Add empty delay slot

  right->codeGen(binding, 2);
  printf("nop\n");
  // TODO： add counter to create unique label:
  //std::cout << "beq $2,$0,"
  //          << labelL3 << std::endl;
  printf("\tbeq $2,$0,%s\n",labelL3.c_str());
  printf("\tnop\n");

  printf("%s:\n",labelL2.c_str());
  //std::cout << labelL2 << ":" << std::endl;
  printf("li $2,1\n");
  printf("b %s\n",labelL4.c_str());  // TODO： add counter to create unique label:
  //std::cout << "b " << labelL4 << std::endl;
  printf("\tnop\n");
  printf("%s:\n",labelL3.c_str());
 // std::cout << labelL3 << ":" << std::endl;
  printf("\tmove $2,$0\n");
  printf("%s:\n",labelL4.c_str());
  //std::cout << labelL4 << ":" << std::endl;
  printf("\tsw $2,%d($fp)\t #store the value of logical or", pos);
  printf("\tlw $2,%d($fp)\n", pos);

  return 0;
}

void LogicalOr::passFunctionName(std::string _name,int _pos){
     function_name = _name;
     pos = pos + _pos;
    ((Program*)left)->passFunctionName(_name,_pos);
    ((Program*)right)->passFunctionName(_name,_pos);
}