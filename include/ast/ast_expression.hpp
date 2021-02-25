#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <cmath>

#include "ast_program.hpp"

class Integer : public Program {
 protected:
  int value;

 public:
  Integer(int _value) : value(_value) {
    fprintf(stderr, "construct Integer\n");
    node_type = 'i';
  }
  virtual void print(std::ostream &dst) const override { dst << value; }
  virtual int evaluate(Binding *binding) const override { return value; }
};

class Variable : public Program {
 private:
  std::string id;

 public:
  Variable(const std::string &_id) : id(_id) {
    fprintf(stderr, "construct Variable\n");
  }
  const std::string getId() const { return id; }
  virtual void print(std::ostream &dst) const override { dst << id; }
  virtual int evaluate(Binding *binding) const override {
    if (binding->find(id) == binding->end()) {
      fprintf(stdout, "%s has not been declared", id.c_str());
      exit(1);
    }
    return binding->at(id)->evaluate(binding);
  }
};

class Addition : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Addition(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct Addition\n");
    node_type = 'a';
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "+";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return left->evaluate(binding) + right->evaluate(binding);
  }
};

class SubOperator : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  SubOperator(ProgramPtr _left, ProgramPtr _right)
      : left(_left), right(_right) {
    fprintf(stderr, "construct subOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "-";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return left->evaluate(binding) - right->evaluate(binding);
  }
};

class MulOperator : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  MulOperator(ProgramPtr _left, ProgramPtr _right)
      : left(_left), right(_right) {
    fprintf(stderr, "construct MulOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "*";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return left->evaluate(binding) * right->evaluate(binding);
  }
};

class DivOperator : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  DivOperator(ProgramPtr _left, ProgramPtr _right)
      : left(_left), right(_right) {
    fprintf(stderr, "construct DivOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "/";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return left->evaluate(binding) / right->evaluate(binding);
  }
};

class ExpOperator : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  ExpOperator(ProgramPtr _left, ProgramPtr _right)
      : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "^";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (pow(left->evaluate(binding), right->evaluate(binding)));
  }
};

class Modulus : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Modulus(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "%";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) % right->evaluate(binding));
  }
};

#endif
