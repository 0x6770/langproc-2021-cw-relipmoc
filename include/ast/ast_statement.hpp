#ifndef ast_statement_hpp
#define ast_statement_hpp

#include "ast_program.hpp"

class Statement;

class Statement : public Program {
 private:
  ProgramPtr expression;
  int is_return;

 public:
  Statement(ProgramPtr _expression, int _is_return)
      : expression(_expression), is_return(_is_return) {
    fprintf(stderr, "construct Statement\n");
  }
  virtual void print(std::ostream &dst) const override {
    if (is_return) dst << "return ";
    expression->print(dst);
    dst << ";\n";
  }
  virtual int evaluate() const override { return expression->evaluate(); }
  int has_return() const {
    if (is_return) return 1;
    return 0;
  }
};

class StatementList : public Program {
 private:
  std::vector<Statement *> statements;

 public:
  StatementList(Statement *_statement) {
    std::vector<Statement *> _statements{_statement};
    statements = _statements;
  }
  std::vector<Statement *> addStatement(Statement *_statement) {
    statements.push_back(_statement);
    return statements;
  }
  virtual void print(std::ostream &dst) const override {
    for (auto it : statements) {
      it->print(dst);
      if (it->has_return()) break;
    }
  }
  virtual int evaluate() const override {
    int x;
    for (auto it : statements) {
      x = it->evaluate();
      if (it->has_return()) break;
    }
    return x;
  }
};

#endif
