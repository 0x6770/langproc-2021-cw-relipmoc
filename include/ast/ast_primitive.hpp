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
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
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
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int getPos(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
};

#endif
