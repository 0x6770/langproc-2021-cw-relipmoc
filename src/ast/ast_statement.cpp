#include "ast.hpp"

////////////////////////////////////////
// Statement
////////////////////////////////////////

Statement::Statement(ProgramPtr _expression) : expression(_expression) {
  logger->info("construct Statement\n");
}

void Statement::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  if (expression) expression->print(dst, indentation);
  dst << ";\n";
}

int Statement::evaluate(Binding *binding) const {
  if (node_type == 'R') return expression->evaluate(binding);
  return 0;
}

ProgramPtr Statement::getExpression() const { return expression; }

void Statement::bind(Binding *binding) const {}

int Statement::codeGen(Binding *binding, int reg) const {
  logger->info("generate code for statement\n");
  expression->codeGen(binding, reg);
  return 0;
}

////////////////////////////////////////
// Return
////////////////////////////////////////

Return::Return(ProgramPtr _expression) : Statement(_expression) {
  logger->info("construct Return\n");
  node_type = -1;
}

void Return::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "return ";
  expression->print(dst, indentation);
  dst << ";\n";
}

int Return::codeGen(Binding *binding, int reg) const {
  logger->info("generate code for Return\n");
  expression->codeGen(binding, 2);
  return 0;
}

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

VarDeclare::VarDeclare(std::string _var_type, std::string _name,
                       ProgramPtr _expression, int &_pos)
    : Statement(_expression), var_type(_var_type), name(_name) {
  node_type = 'v';
  pos = _pos;
  if (_var_type == "int") {
    size = 4;
    _pos += 4;
  }
}

void VarDeclare::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << var_type << " " << name;
  if (expression) {
    dst << " = ";
    expression->print(dst, indentation);
  }
  dst << ";\n";
}

void VarDeclare::bind(Binding *binding) const {
  if (binding->find(name) != binding->end()) {
    logger->error("Multiple declarations, \"%s\" has been declared\n",
                  name.c_str());
    exit(1);
  }
  binding->insert(std::pair<std::string, int>(name, pos));
}

int VarDeclare::codeGen(Binding *binding, int reg) const {
  logger->info("generate code for VarDeclare\n");
  assert(binding->find(name) != binding->end());

  if (expression) {
    expression->codeGen(binding, reg);
    printf("sw $2,%d($fp)\n", pos);
  }
  return 0;
}

////////////////////////////////////////
// VarAssign
////////////////////////////////////////

VarAssign::VarAssign(std::string _name, ProgramPtr _expression)
    : Statement(_expression), name(_name) {
  node_type = 'v';
}

void VarAssign::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << name << " = ";
  expression->print(dst, indentation);
  dst << ";\n";
}

void VarAssign::bind(Binding *binding) const {
  // if (binding->find(name) == binding->end()) {
  // fprintf(stdout, "Variable \"%s\" has not been declared in current scope\n",
  // name.c_str());
  //// this->print(std::cout, 0);
  // exit(1);
  //}
  // binding->at(name) = expression;
}

int VarAssign::codeGen(Binding *binding, int reg) const {
  logger->info("generate code for VarAssign\n");
  if (binding->find(name) == binding->end()) {
    logger->error("%s has not been declared\n", name.c_str());
  };
  expression->codeGen(binding, reg);
  printf("sw $2,%d($fp)\t# assign %s\n", pos, name.c_str());
  return 0;
}

////////////////////////////////////////
// StatementList
////////////////////////////////////////

StatementList::StatementList(ProgramPtr _statement) {
  addStatement(_statement);
}

void StatementList::addStatement(ProgramPtr _statement) {
  if (((Statement *)_statement)->getType() == 'v') {
    ((Statement *)_statement)->bind(&binding);
  }
  size += _statement->getSize();
  statements.push_back(_statement);
}

const Binding &StatementList::getBinding() const { return binding; }

void StatementList::mergeBinding(ProgramPtr _statement_list) {
  for (auto it : ((StatementList *)_statement_list)->getBinding()) {
    // keep existing variables in the current scope unchanged, add extra
    // variables from higher scope
    if (binding.find(it.first) == binding.end()) {
      binding.insert(std::make_pair(it.first, it.second));
    }
  }
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

int StatementList::codeGen(Binding *_binding, int reg) const {
  logger->info("generate code for StatementList\n");
  logger->info("Mapping of variables\n");
  logger->info("---------------------\n");
  logger->info("%10s|%10s\n", "name", "position");
  logger->info("---------------------\n");
  for (auto it : binding) {
    logger->info("%10s|%10d\n", it.first.c_str(), it.second);
  }
  for (auto it : statements) {
    it->codeGen((Binding *)&binding,
                2);  // generate mips assembly code using its own binding, and
                     // put result of sub operation into $2
    if (((Statement *)it)->getType() < 0) break;
  }
  return 0;
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
  printIndent(dst, indentation);
  dst << "if (";
  condition->print(dst, indentation);
  dst << ")";
  if (if_statement) {
    dst << " {\n";
    if_statement->print(dst, indentation);
    printIndent(dst, --indentation);
    dst << "}";
  }
  if (else_statement) {
    dst << " else {\n";
    else_statement->print(dst, indentation);
    printIndent(dst, --indentation);
    dst << "}";
  }
  dst << "\n";
}

int IfStatement::evaluate(Binding *_binding) const { return 0; }

int IfStatement::codeGen(Binding *binding, int reg) const { return 0; }

////////////////////////////////////////
// WhileLoop
////////////////////////////////////////

WhileLoop::WhileLoop(ProgramPtr _condition, ProgramPtr _statement)
    : condition(_condition), statement(_statement) {}

void WhileLoop::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "while (";
  condition->print(dst, indentation);
  dst << ")";
  if (statement) {
    dst << " {\n";
    statement->print(dst, indentation);
    printIndent(dst, --indentation);
    dst << "}";
  }
  dst << "\n";
}

int WhileLoop::evaluate(Binding *_binding) const { return 0; }

int WhileLoop::codeGen(Binding *binding, int reg) const { return 0; }
