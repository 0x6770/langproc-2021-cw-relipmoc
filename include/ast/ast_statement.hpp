#ifndef ast_statement_hpp
#define ast_statement_hpp

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
  virtual void passFunctionName(std::string _name, int _pos) override;
  virtual void passLabel(int _label) override;
  virtual void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
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
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Continue
////////////////////////////////////////

class Continue : public Statement {
 public:
  Continue();
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// Break
////////////////////////////////////////

class Break : public Statement {
 public:
  Break();
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

class VarDeclare : public Statement {
 private:
  std::string var_type;
  std::string id;
  ProgramPtr left;
  int is_pointer;

 public:
  VarDeclare(std::string _var_type, std::string _id, ProgramPtr _expression,
             int _pos);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  std::string getId() const;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// VarAssign
////////////////////////////////////////

class VarAssign : public Statement {
 private:
  std::string name;
  ProgramPtr assign_left;
  int with_left;

 public:
  VarAssign(std::string _name, ProgramPtr _expression);
  VarAssign(ProgramPtr _left, ProgramPtr _expression);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
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
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// IfStatement
////////////////////////////////////////

class IfStatement : public Statement {
 private:
  ProgramPtr condition;
  ProgramPtr if_statement;
  ProgramPtr else_statement;

 public:
  IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
              ProgramPtr _else_statement, int _label);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// WhileLoop
////////////////////////////////////////

class WhileLoop : public Statement {
 private:
  ProgramPtr condition;
  ProgramPtr statement_list;

 public:
  WhileLoop(ProgramPtr _condition, ProgramPtr _statement_list, int _label);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  std::string getVariableType() override;
};

////////////////////////////////////////
// For Loop
// init_expr → test_expr → body
//            ↑ update_expr ↵
////////////////////////////////////////

class ForLoop : public Statement {
 private:
  ProgramPtr init_expr;
  ProgramPtr test_expr;
  ProgramPtr update_expr;
  ProgramPtr statement_list;

 public:
  ForLoop(ProgramPtr _init_expr, ProgramPtr _test_expr, ProgramPtr _update_expr,
          ProgramPtr _statement_list, int _label);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  void passTypeBinding(TypeBinding &_typebind) override;
  virtual std::string getVariableType() override;
};

////////////////////////////////////////
// Switch
////////////////////////////////////////

class Switch : public Statement {
 private:
  ProgramPtr cases;

 public:
  Switch(ProgramPtr _expression, ProgramPtr _cases, int _label);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
};

////////////////////////////////////////
// Case in Switch
////////////////////////////////////////

class Case : public Statement {
 private:
  int constant;
  int isDefault = 0;
  ProgramPtr statements;

 public:
  Case(ProgramPtr _statements);
  Case(int _constant, ProgramPtr _statements);
  int codeGen(const Binding &_binding, int reg) const override;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
  int getConstant() const;
  int getDefault() const;
};

////////////////////////////////////////
// Cases in Switch
////////////////////////////////////////

class Cases : public Statement {
 private:
  int hasDefault = 0;
  std::set<int> constants;
  std::vector<ProgramPtr> cases;

 public:
  Cases();
  void addCase(ProgramPtr _cases);
  int codeGen(const Binding &_binding, int reg) const override;
  int codeGen(const Binding &_binding, int reg, int switch_expr_res) const;
  void print(std::ostream &dst, int indentation) const override;
  int evaluate(const Binding &_binding) const override;
  void bind(const Binding &_binding) override;
  void passFunctionName(std::string _name, int _pos) override;
  void passLabel(int _label) override;
};

#endif
