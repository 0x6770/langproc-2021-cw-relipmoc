#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <map>

#include "ast_program.hpp"

////////////////////////////////////////
// Statement
////////////////////////////////////////

class Statement : public Program {
 protected:
  ProgramPtr expression;
  Binding binding;

 public:
  Statement(ProgramPtr _expression);
  virtual int codeGen(const Binding &_binding, int reg) const override;
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(const Binding &_binding) const override;
  virtual void bind(const Binding &_binding) override;
  ProgramPtr getExpression() const;
  virtual void passFunctionName(std::string _name,int _pos) override;
};

////////////////////////////////////////
// Return
////////////////////////////////////////

class Return : public Statement {
 public:
  Return(ProgramPtr _expression);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name,int _pos) override;
};

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

class VarDeclare : public Statement {
 private:
  std::string var_type;
  std::string id;

 public:
  VarDeclare(std::string _var_type, std::string _id, ProgramPtr _expression,
             int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  std::string getId() const;
  void passFunctionName(std::string _name,int _pos) override;
};

////////////////////////////////////////
// VarAssign
////////////////////////////////////////

class VarAssign : public Statement {
 private:
  std::string name;

 public:
  VarAssign(std::string _name, ProgramPtr _expression);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name,int _pos) override;
};

////////////////////////////////////////
// StatementList
////////////////////////////////////////

class StatementList : public Statement {
 private:
  std::vector<ProgramPtr> statements;
  Binding binding;

 public:
  StatementList();
  void addStatement(ProgramPtr _statement);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name,int _pos);
};

////////////////////////////////////////
// IfStatement
////////////////////////////////////////

class IfStatement : public Statement {
 private:
  ProgramPtr condition;
  ProgramPtr if_statement;
  ProgramPtr else_statement;
  int label;

 public:
  IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
              ProgramPtr _else_statement, int _label);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name,int _pos);
};

////////////////////////////////////////
// WhileLoop
////////////////////////////////////////

class WhileLoop : public Statement {
 private:
  ProgramPtr condition;
  ProgramPtr statement_list;

 public:
  WhileLoop(ProgramPtr _condition, ProgramPtr _statement_list);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name,int _pos);
};

#endif
