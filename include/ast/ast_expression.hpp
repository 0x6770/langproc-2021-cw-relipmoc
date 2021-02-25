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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << value;
  }
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << id;
  }
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << "(";
    left->print(dst, indentation);
    dst << "+";
    right->print(dst, indentation);
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << "(";
    left->print(dst, indentation);
    dst << "-";
    right->print(dst, indentation);
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << "(";
    left->print(dst, indentation);
    dst << "*";
    right->print(dst, indentation);
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << "(";
    left->print(dst, indentation);
    dst << "/";
    right->print(dst, indentation);
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << "(";
    left->print(dst, indentation);
    dst << "^";
    right->print(dst, indentation);
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
  virtual void print(std::ostream &dst, int indentation) const override {
    dst << "(";
    left->print(dst, indentation);
    dst << "%";
    right->print(dst, indentation);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) % right->evaluate(binding));
  }
};

class Shift_left : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Shift_left(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "<<";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) << right->evaluate(binding));
  }
};

class Shift_right : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Shift_right(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << ">>";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) >> right->evaluate(binding));
  }
};

class Smaller_equal : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int is_equal;

 public:
  Smaller_equal(ProgramPtr _left, ProgramPtr _right,int _is_equal) : left(_left), right(_right),is_equal(_is_equal){
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    if(is_equal == 1){
      dst << "<=";
    }
    else{
      dst << "<";
    }
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    if(is_equal == 1){
      return (left->evaluate(binding) <= right->evaluate(binding));
    }
    else{
      return (left->evaluate(binding) < right->evaluate(binding));
    }
  }
};

class Larger_equal : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int is_equal;

 public:
  Larger_equal(ProgramPtr _left, ProgramPtr _right, int _is_equal) : left(_left), right(_right) ,is_equal(_is_equal) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    if(is_equal == 1){
      dst << ">=";
    }
    else{
      dst << ">";
    }
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    if(is_equal == 1){
      return (left->evaluate(binding) >= right->evaluate(binding));
    }
    else{
      return (left->evaluate(binding) > right->evaluate(binding));
    }
  }
};

class Equal : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;
  int is_equal;

 public:
  Equal(ProgramPtr _left, ProgramPtr _right, int _is_equal) : left(_left), right(_right) ,is_equal(_is_equal) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    if(is_equal == 1){
      dst << "!=";
    }
    else{
      dst << "==";
    }
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    if(is_equal == 1){
      return (left->evaluate(binding) != right->evaluate(binding));
    }
    else{
      return (left->evaluate(binding) == right->evaluate(binding));
    }
  }
};

class Bitwise_AND : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Bitwise_AND(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "&";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) & right->evaluate(binding));
  }
};

class Bitwise_OR : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Bitwise_OR(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "|";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) | right->evaluate(binding));
  }
};

class Logical_AND : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Logical_AND(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "&&";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) && right->evaluate(binding));
  }
};

class Logical_OR : public Program {
 protected:
  ProgramPtr left;
  ProgramPtr right;

 public:
  Logical_OR(ProgramPtr _left, ProgramPtr _right) : left(_left), right(_right) {
    fprintf(stderr, "construct ExpOperator\n");
  }
  virtual void print(std::ostream &dst) const override {
    dst << "(";
    left->print(dst);
    dst << "||";
    right->print(dst);
    dst << ")";
  }
  virtual int evaluate(Binding *binding) const override {
    return (left->evaluate(binding) || right->evaluate(binding));
  }
};

#endif
