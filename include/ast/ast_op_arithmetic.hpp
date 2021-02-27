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

////////////////////////////////////////
// Suffix/postfix increment
////////////////////////////////////////

class Increment_Post : public Program {
 protected:
  ProgramPtr left;

 public:
  Increment_Post(ProgramPtr _left);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};


////////////////////////////////////////
// Prefix increment
////////////////////////////////////////

class Increment_Pre : public Program {
 protected:
  ProgramPtr left;

 public:
  Increment_Pre(ProgramPtr _left);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Suffix/postfix decrement
////////////////////////////////////////

class Decrement_Post : public Program {
 protected:
  ProgramPtr left;

 public:
  Decrement_Post(ProgramPtr _left);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};


////////////////////////////////////////
// Prefix decrement
////////////////////////////////////////

class Decrement_Pre : public Program {
 protected:
  ProgramPtr left;

 public:
  Decrement_Pre(ProgramPtr _left);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif
