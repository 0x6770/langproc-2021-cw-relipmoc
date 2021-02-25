#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <map>

#include "ast_program.hpp"

class Statement;

class Statement : public Program {
 private:
  std::string type;
  std::string name;
  ProgramPtr expression;

 public:
  Statement(int _node_type, ProgramPtr _expression) : expression(_expression) {
    fprintf(stderr, "construct Statement\n");
    node_type = _node_type;
  }
  // for declaration
  Statement(int _node_type, std::string *_type, std::string *_name,
            ProgramPtr _expression)
      : type(*_type), name(*_name), expression(_expression) {
    fprintf(stderr, "construct D Statement\n");
    node_type = _node_type;
  }
  // for assignment
  Statement(int _node_type, std::string *_name, ProgramPtr _expression)
      : name(*_name), expression(_expression) {
    fprintf(stderr, "construct A Statement\n");
    node_type = _node_type;
  }
  virtual void print(std::ostream &dst, int indentation) const override {
    int matched = 1;
    print_indent(dst, indentation);
    switch (getType()) {
      case 'R':
        dst << "return ";
        expression->print(dst, indentation);
        break;
      case 'D':
        dst << type << " " << name;
        if (expression != 0) {
          dst << " = ";
          expression->print(dst, indentation);
        }
        break;
      case 'A':
        dst << name << " = ";
        expression->print(dst, indentation);
        break;
      default:
        matched = 0;
    }
    if (matched) dst << ";" << std::endl;
  }
  virtual int evaluate(Binding *binding) const override {
    if (node_type == 'R') return expression->evaluate(binding);
    return 0;
  }
  ProgramPtr getExpression() { return expression; }
  std::string getName() { return name; }
};

class StatementList : public Program {
 private:
  std::vector<Statement *> statements;
  Binding binding;

 public:
  StatementList(Statement *_statement) {
    addStatement(_statement);
    node_type = 'L';
  }
  std::vector<Statement *> addStatement(Statement *_statement) {
    std::string name = _statement->getName();
    ProgramPtr expr = _statement->getExpression();

    switch (_statement->getType()) {
      case 'D':
        if (binding.find(name) != binding.end()) {
          fprintf(stdout,
                  "Multiple declarations, variable %s has been declared\n",
                  name.c_str());
          exit(1);
        }
        binding.insert(std::pair<std::string, ProgramPtr>(name, expr));
        break;
      case 'A':
        if (binding.find(name) == binding.end()) {
          fprintf(stdout, "No delcaration, variable %s has not been declared\n",
                  name.c_str());
          _statement->print(std::cout, 0);
          exit(1);
        }
        binding.at(name) = expr;
        break;
      case 'E':
        break;
      case 'R':
        break;
      default:
        break;
    }

    statements.push_back(_statement);
    return statements;
  }
  virtual void print(std::ostream &dst, int indentation) const override {
    for (auto it : statements) {
      it->print(dst, indentation);
      if (it->getType() == 'R') break;
    }
  }
  virtual int evaluate(Binding *_binding) const override {
    int x;
    for (auto it : statements) {
      x = it->evaluate((Binding *)&binding);
      if (it->getType() == 'R') break;
    }
    return x;
  }
};

#endif
