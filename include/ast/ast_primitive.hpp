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
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

///////////////////////////////////////////
// Char
//////////////////////////////////////////

class Char : public Program {
 private:
  char value;

 public:
  Char(char _value);
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
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
  int codeGen(std::ofstream &dst, const Binding &_binding,
              int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  int getPos(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  std::string gettype(TypeBinding &_typebind) const;
  virtual std::string getVariableType() override;
};

#endif
