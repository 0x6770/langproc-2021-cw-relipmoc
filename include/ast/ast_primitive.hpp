#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <cmath>

#include "ast_program.hpp"

////////////////////////////////////////
// Integer
////////////////////////////////////////

class Integer : public Program {
 protected:
  int value;

 public:
  Integer(int _value);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Variable
////////////////////////////////////////

class Variable : public Program {
 private:
  std::string id;

 public:
  Variable(const std::string &_id);
  const std::string getId() const;
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
};

#endif
