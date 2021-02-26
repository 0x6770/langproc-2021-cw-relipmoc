#include "ast.hpp"

////////////////////////////////////////
// Statement
////////////////////////////////////////

Statement::Statement(int _node_type, ProgramPtr _expression)
    : expression(_expression) {
  fprintf(stderr, "construct Statement\n");
  node_type = _node_type;
}

// for declaration
Statement::Statement(int _node_type, std::string *_type, std::string *_name,
                     ProgramPtr _expression)
    : type(*_type), name(*_name), expression(_expression) {
  fprintf(stderr, "construct D Statement\n");
  node_type = _node_type;
}

// for assignment
Statement::Statement(int _node_type, std::string *_name, ProgramPtr _expression)
    : name(*_name), expression(_expression) {
  fprintf(stderr, "construct A Statement\n");
  node_type = _node_type;
}

void Statement::print(std::ostream &dst, int indentation) const {
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
    case 'E':
      expression->print(dst, indentation);
      break;
    default:
      matched = 0;
      dst << "/* do nothing */\n";
  }
  if (matched) dst << ";" << std::endl;
}

int Statement::evaluate(Binding *binding) const {
  if (node_type == 'R') return expression->evaluate(binding);
  return 0;
}

ProgramPtr Statement::getExpression() { return expression; }

std::string Statement::getName() { return name; }

////////////////////////////////////////
// StatementList
////////////////////////////////////////

StatementList::StatementList(ProgramPtr _statement) {
  addStatement(_statement);
  node_type = 'L';
}

std::vector<ProgramPtr> StatementList::addStatement(ProgramPtr _statement) {
  std::string name = ((Statement *)_statement)->getName();
  ProgramPtr expr = ((Statement *)_statement)->getExpression();

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

void StatementList::print(std::ostream &dst, int indentation) const {
  for (auto it : statements) {
    it->print(dst, indentation);
    if (it->getType() == 'R') break;
  }
}

int StatementList::evaluate(Binding *_binding) const {
  int x;
  for (auto it : statements) {
    x = it->evaluate((Binding *)&binding);
    if (it->getType() == 'R') break;
  }
  return x;
}

IfStatement::IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
                         ProgramPtr _else_statement)
    : condition(_condition),
      if_statement(_if_statement),
      else_statement(_else_statement) {}

void IfStatement::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  dst << "if (";
  condition->print(dst, indentation);
  dst << ")";
  if (if_statement) {
    dst << " {\n";
    if_statement->print(dst, indentation);
    print_indent(dst, --indentation);
    dst << "}";
  }
  if (else_statement) {
    dst << " else {\n";
    else_statement->print(dst, indentation);
    print_indent(dst, --indentation);
    dst << "}";
  }
  dst << "\n";
}

int IfStatement::evaluate(Binding *_binding) const { return 0; }

WhileLoop::WhileLoop(ProgramPtr _condition, ProgramPtr _statement)
    : condition(_condition), statement(_statement) {}

void WhileLoop::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  dst << "while (";
  condition->print(dst, indentation);
  dst << ")";
  if (statement) {
    dst << " {\n";
    statement->print(dst, indentation);
    print_indent(dst, --indentation);
    dst << "}";
  }
  dst << "\n";
}

int WhileLoop::evaluate(Binding *_binding) const { return 0; }
