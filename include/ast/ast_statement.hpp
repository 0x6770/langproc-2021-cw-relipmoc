#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <map>

#include "ast_program.hpp"

class Statement : public Program {
 private:
  std::string type;
  std::string name;
  ProgramPtr expression;

 public:
  Statement(int _node_type, ProgramPtr _expression);
  // for declaration
  Statement(int _node_type, std::string *_type, std::string *_name,
            ProgramPtr _expression);
  // for assignment
  Statement(int _node_type, std::string *_name, ProgramPtr _expression);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *binding) const override;
  ProgramPtr getExpression();
  std::string getName();
};

class StatementList : public Program {
 private:
  std::vector<ProgramPtr> statements;
  Binding binding;

 public:
  StatementList(ProgramPtr _statement);
  std::vector<ProgramPtr> addStatement(ProgramPtr _statement);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *_binding) const override;
};

class IfStatement : public Program {
 private:
  ProgramPtr condition;
  ProgramPtr if_statement;
  ProgramPtr else_statement;

 public:
  IfStatement(ProgramPtr condition, ProgramPtr _if_statement,
              ProgramPtr _else_statement);
  virtual void print(std::ostream &dst, int indentation) const override;
  virtual int evaluate(Binding *_binding) const override;
};

#endif
