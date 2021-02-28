#ifndef ast_op_arithmetic_hpp
#define ast_op_arithmetic_hpp

#include "ast_operation.hpp"

////////////////////////////////////////
// Addition
////////////////////////////////////////

class Addition : public Operation {
 public:
  Addition(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Subtraction
////////////////////////////////////////

class Subtraction : public Operation {
 public:
  Subtraction(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Multiplication
////////////////////////////////////////

class Multiplication : public Operation {
 public:
  Multiplication(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Division
////////////////////////////////////////

class Division : public Operation {
 public:
  Division(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};


////////////////////////////////////////
// Modulus
////////////////////////////////////////


class Power : public Operation {
 public:
  Power(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Suffix/postfix increment
////////////////////////////////////////

class Modulus : public Operation {
 public:
  Modulus(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
 };

class Increment_Post : public Operation {
  Power(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};


////////////////////////////////////////
// Prefix increment
////////////////////////////////////////

class Increment_Pre : public Operation {
  Power(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Suffix/postfix decrement
////////////////////////////////////////

class Decrement_Post : public Operation {
  Power(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};


////////////////////////////////////////
// Prefix decrement
////////////////////////////////////////

class Decrement_Pre : public Operation {
  Power(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

#endif
