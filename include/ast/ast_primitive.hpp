#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <cmath>

#include "ast_program.hpp"

////////////////////////////////////////
// Integer
////////////////////////////////////////

class Integer : public Program {
 private:
  int value;

 public:
  Integer(int _value);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
};

////////////////////////////////////////
// Variable
////////////////////////////////////////

class Variable : public Program {
 private:
  std::string id;
  unsigned int index;

 public:
  Variable(const std::string &_id);
  const std::string getId() const;
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *binding) const override;
  const int &getPos(const Binding &binding) const override;
};

#endif
