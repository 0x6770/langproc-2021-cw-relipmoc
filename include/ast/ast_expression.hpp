#ifndef ast_expression_hpp
#define ast_expression_hpp

#include "ast_program.hpp"

class Integer : public Program {
 private:
  int value;

 public:
  Integer(int _value) : value(_value) {
    fprintf(stderr, "construct Integer\n");
  }
  virtual void print(std::ostream &dst) const override { dst << value; }
  virtual int evaluate() const override { return value; }
};

class Addition : public Program {
 private:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Addition(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct Addition\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "+";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate() const override {
    return left->evaluate() + right->evaluate();
  }
};

class division : public ProgramP{
  
}

#endif
