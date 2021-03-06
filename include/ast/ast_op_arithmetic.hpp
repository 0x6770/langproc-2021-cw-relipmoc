#ifndef ast_op_arithmetic_hpp
#define ast_op_arithmetic_hpp

#include "ast_operation.hpp"

////////////////////////////////////////
// Addition
////////////////////////////////////////

class Addition : public Operation {
 public:
  Addition(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
};

////////////////////////////////////////
// Subtraction
////////////////////////////////////////

class Subtraction : public Operation {
 public:
  Subtraction(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
};

////////////////////////////////////////
// Multiplication
////////////////////////////////////////

class Multiplication : public Operation {
 public:
  Multiplication(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
};

////////////////////////////////////////
// Division
////////////////////////////////////////

class Division : public Operation {
 public:
  Division(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
};

////////////////////////////////////////
// Modulus
////////////////////////////////////////

class Modulus : public Operation {
 public:
  Modulus(ProgramPtr _left, ProgramPtr _right, int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
};

////////////////////////////////////////
// Negation
////////////////////////////////////////

class Negation : public Operation {
 public:
  Negation(ProgramPtr _right, int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
};

#endif
