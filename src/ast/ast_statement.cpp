#include "ast.hpp"

////////////////////////////////////////
// Statement
////////////////////////////////////////

Statement::Statement(ProgramPtr _expression) : expression(_expression) {
  fprintf(stderr, "construct Statement\n");
}

void Statement::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  if (expression) expression->print(dst, indentation);
  dst << ";\n";
}

int Statement::evaluate(Binding *binding) const {
  if (node_type == 'R') return expression->evaluate(binding);
  return 0;
}

ProgramPtr Statement::getExpression() const { return expression; }

void Statement::bind(Binding *binding) const {}

////////////////////////////////////////
// Return
////////////////////////////////////////

Return::Return(ProgramPtr _expression) : Statement(_expression) {
  node_type = -1;
}

void Return::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  dst << "return ";
  expression->print(dst, indentation);
  dst << ";\n";
}

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

VarDeclare::VarDeclare(std::string _var_type, std::string _name,
                       ProgramPtr _expression)
    : Statement(_expression), var_type(_var_type), name(_name) {
  node_type = 'v';
}

void VarDeclare::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  dst << var_type << " " << name;
  if (expression) {
    dst << " = ";
    expression->print(dst, indentation);
  }
  dst << ";\n";
}

void VarDeclare::bind(Binding *binding) const {
  if (binding->find(name) != binding->end()) {
    fprintf(stdout, "Multiple declarations, variable %s has been declared\n",
            name.c_str());
    exit(1);
  }
  binding->insert(std::pair<std::string, ProgramPtr>(name, expression));
}

////////////////////////////////////////
// VarAssign
////////////////////////////////////////

VarAssign::VarAssign(std::string _name, ProgramPtr _expression)
    : Statement(_expression), name(_name) {
  node_type = 'v';
}

void VarAssign::print(std::ostream &dst, int indentation) const {
  print_indent(dst, indentation);
  dst << name << " = ";
  expression->print(dst, indentation);
  dst << ";\n";
}

void VarAssign::bind(Binding *binding) const {
  if (binding->find(name) == binding->end()) {
    fprintf(stdout, "Variable \"%s\" has not been declared in current scope\n",
            name.c_str());
    // this->print(std::cout, 0);
    exit(1);
  }
  binding->at(name) = expression;
}

////////////////////////////////////////
// StatementList
////////////////////////////////////////

StatementList::StatementList(ProgramPtr _statement) {
  addStatement(_statement);
}

std::vector<ProgramPtr> StatementList::addStatement(ProgramPtr _statement) {
  if (((Statement *)_statement)->getType() == 'v') {
    ((Statement *)_statement)->bind(&binding);
  }
  statements.push_back(_statement);
  return statements;
}

void StatementList::print(std::ostream &dst, int indentation) const {
  for (auto it : statements) {
    it->print(dst, indentation);
    if (((Statement *)it)->getType() < 0) break;
  }
}

int StatementList::evaluate(Binding *_binding) const {
  int x;
  for (auto it : statements) {
    x = it->evaluate((Binding *)&binding);
    if (((Statement *)it)->getType() < 0) break;
  }
  return x;
}

////////////////////////////////////////
// IfStatement
////////////////////////////////////////

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

////////////////////////////////////////
// WhileLoop
////////////////////////////////////////

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
