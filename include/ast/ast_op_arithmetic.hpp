#ifndef ast_op_arithmetic_hpp
#define ast_op_arithmetic_hpp

#include "ast_program.hpp"

////////////////////////////////////////
// Addition
////////////////////////////////////////

class Addition : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Addition(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Subtraction
////////////////////////////////////////

class Subtraction : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Subtraction(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Multiplication
////////////////////////////////////////

class Multiplication : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Multiplication(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Division
////////////////////////////////////////

class Division : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Division(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Power
////////////////////////////////////////

class Power : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Power(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Modulus
////////////////////////////////////////

class Modulus : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Modulus(ProgramPtr _left, ProgramPtr _right);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif
