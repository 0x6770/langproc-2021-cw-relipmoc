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

 public:
  Statement(ProgramPtr _expression);
  virtual int codeGen(Binding *binding, int reg) const override;
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  virtual void bind(Binding *_binding) const;
  ProgramPtr getExpression() const;
};

////////////////////////////////////////
// Return
////////////////////////////////////////

class Return : public Statement {
 public:
  Return(ProgramPtr _expression);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
};

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

class VarDeclare : public Statement {
 private:
  std::string var_type;
  std::string name;

 public:
  VarDeclare(std::string _var_type, std::string _name, ProgramPtr _expression,
             int &_pos);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(Binding *_binding) const override;
};

////////////////////////////////////////
// VarAssign
////////////////////////////////////////

class VarAssign : public Statement {
 private:
  std::string name;

 public:
  VarAssign(std::string _name, ProgramPtr _expression);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(Binding *_binding) const override;
};

////////////////////////////////////////
// StatementList
////////////////////////////////////////

class StatementList : public Program {
 private:
  std::vector<ProgramPtr> statements;
  Binding binding;

 public:
  StatementList();
  void addStatement(ProgramPtr _statement);
  void mergeBinding(ProgramPtr _statement_list);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *_binding) const override;
  const Binding &getBinding() const;
};

class IfStatement : public Program {
 private:
  ProgramPtr condition;
  ProgramPtr if_statement;
  ProgramPtr else_statement;

 public:
  IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
              ProgramPtr _else_statement);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *_binding) const override;
};

class WhileLoop : public Program {
 private:
  ProgramPtr condition;
  ProgramPtr statement;

 public:
  WhileLoop(ProgramPtr _condition, ProgramPtr _statement);
  int codeGen(Binding *binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(Binding *_binding) const override;
};

#endif
