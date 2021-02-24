#ifndef ast_statement_hpp
#define ast_statement_hpp

#include "ast_program.hpp"

class Statement;

class Statement : public Program {
 private:
  ProgramPtr expression;

 public:
  Statement(int _node_type, ProgramPtr _expression) : expression(_expression) {
    fprintf(stderr, "construct Statement\n");
    node_type = _node_type;
  }
  virtual void print(std::ostream &dst) const override {
    if (getType() == 'R') dst << "return ";
    expression->print(dst);
    dst << ";\n";
  }
  virtual int evaluate() const override { return expression->evaluate(); }
};

class StatementList : public Program {
 private:
  std::vector<Statement *> statements;

 public:
  StatementList(Statement *_statement) {
    std::vector<Statement *> _statements{_statement};
    statements = _statements;
    node_type = 'L';
  }
  std::vector<Statement *> addStatement(Statement *_statement) {
    statements.push_back(_statement);
    return statements;
  }
  virtual void print(std::ostream &dst) const override {
    for (auto it : statements) {
      it->print(dst);
      if (it->getType() == 'R') break;
    }
  }
  virtual int evaluate() const override {
    int x;
    for (auto it : statements) {
      x = it->evaluate();
      if (it->getType() == 'R') break;
    }
    return x;
  }
};

#endif
