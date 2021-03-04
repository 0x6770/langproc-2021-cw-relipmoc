#include "ast.hpp"

////////////////////////////////////////
// Statement
////////////////////////////////////////

Statement::Statement(ProgramPtr _expression) : expression(_expression) {}

void Statement::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  if (expression) expression->print(dst, indentation);
  dst << ";\n";
}

int Statement::evaluate(const Binding &_binding) const {
  if (node_type == 'r') return expression->evaluate(binding);
  return 0;
}

ProgramPtr Statement::getExpression() const { return expression; }

int Statement::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for statement\n");
  if (expression) expression->codeGen(binding, reg);
  return 0;
}

void Statement::bind(const Binding &_binding) {
  binding = _binding;
  logger->info("binding...%c\n", node_type);
}

////////////////////////////////////////
// Return
////////////////////////////////////////

Return::Return(ProgramPtr _expression) : Statement(_expression) {
  logger->info("construct Return\n");
  node_type = 'r';
}

void Return::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "return ";
  expression->print(dst, 0);
  dst << ";\n";
}

int Return::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for Return\n");
  expression->codeGen(binding, 2);
  return 0;
}

void Return::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)expression)->bind(binding);
}

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

VarDeclare::VarDeclare(std::string _var_type, std::string _id,
                       ProgramPtr _expression, int &_pos)
    : Statement(_expression), var_type(_var_type), id(_id) {
  logger->info("construct VarDeclare\n");
  node_type = 'd';
  pos = _pos;
  if (_var_type == "int") {
    size = 4;
    _pos += 4;
  }
}

void VarDeclare::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << var_type << " " << id;
  if (expression) {
    dst << " = ";
    expression->print(dst, 0);
  }
  dst << ";\n";
}

int VarDeclare::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for VarDeclare\n");

  if (expression) {
    expression->codeGen(binding, reg);
    printf("sw $2,%d($fp)\n", pos);
  }
  return 0;
}

std::string VarDeclare::getId() const { return id; }

void VarDeclare::bind(const Binding &_binding) {
  logger->info("binding...VarAssign\n");
  binding = _binding;
  print_map(binding, "VarDeclare");
  if (expression) {
    ((Program *)expression)->bind(binding);
  }
}

////////////////////////////////////////
// VarAssign
////////////////////////////////////////

VarAssign::VarAssign(std::string _name, ProgramPtr _expression)
    : Statement(_expression), name(_name) {}

void VarAssign::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << name << " = ";
  expression->print(dst, 0);
  dst << ";\n";
}

int VarAssign::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for VarAssign\n");
  print_map(binding, "VarAssign");
  if (binding.find(name) == binding.end()) {
    logger->error("%s has not been declared\n", name.c_str());
    exit(1);
  };
  int pos_in_binding = binding.at(name);
  expression->codeGen(binding, reg);
  printf("sw $2,%d($fp)\t# assign %s\n", pos_in_binding, name.c_str());
  return 0;
}

void VarAssign::bind(const Binding &_binding) {
  logger->info("binding...VarAssign\n");
  binding = _binding;
  print_map(binding, "VarAssign");
  ((Program *)expression)->bind(binding);
}

////////////////////////////////////////
// StatementList
////////////////////////////////////////

StatementList::StatementList() : Statement(0) {
  node_type = 'l';
  logger->info("construct StatementList\n");
}

void StatementList::addStatement(ProgramPtr _statement) {
  size += _statement->getSize();
  statements.push_back(_statement);
}

void StatementList::print(std::ostream &dst, int indentation) const {
  for (auto it : statements) {
    it->print(dst, indentation);
    if (((Statement *)it)->getType() == 'r') break;
  }
}

int StatementList::evaluate(const Binding &_binding) const {
  int x;
  for (auto it : statements) {
    x = it->evaluate(binding);
    if (((Statement *)it)->getType() == 'r') break;
  }
  return x;
}

int StatementList::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for StatementList\n");
  logger->info("Mapping of variables\n");
  logger->info("---------------------\n");
  logger->info("%10s|%10s\n", "name", "position");
  logger->info("---------------------\n");
  for (auto it : binding) {
    logger->info("%10s|%10d\n", it.first.c_str(), it.second);
  }
  for (auto it : statements) {
    it->codeGen(binding, 2);
    // generate mips assembly code using its own binding, and
    // put result into $2
    if (((Statement *)it)->getType() == 'r') break;
  }
  return 0;
}

void StatementList::bind(const Binding &_binding) {
  int x = rand() % 1000;
  logger->info("binding...StatementList %d\n", x);
  binding = _binding;
  // all variables defined in current scope and outer scopes
  Binding local_binding;

  print_map(binding, std::to_string(x));
  for (auto it : statements) {
    if (it->getType() == 'd') {
      std::string id = ((VarDeclare *)it)->getId();
      int pos = it->getPos(binding);
      if (local_binding.find(id) != local_binding.end()) {
        logger->error("Multiple declaration for \"%s\"\n", id.c_str());
        exit(1);
      }
      logger->info("find declaration for \"%s\" at %d\n", id.c_str(), pos);
      local_binding[id] = pos;
      binding[id] = pos;
      print_map(local_binding, std::to_string(x));
      print_map(binding, std::to_string(x));
    }
    ((Statement *)it)->bind(binding);
  }
  print_map(binding, std::to_string(x));
}

////////////////////////////////////////
// IfStatement
////////////////////////////////////////

IfStatement::IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
                         ProgramPtr _else_statement)
    : Statement(0),
      condition(_condition),
      if_statement(_if_statement),
      else_statement(_else_statement) {}

void IfStatement::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "if (";
  condition->print(dst, 0);
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

int IfStatement::evaluate(const Binding &_binding) const { return 0; }

int IfStatement::codeGen(const Binding &_binding, int reg) const { return 0; }

////////////////////////////////////////
// WhileLoop
////////////////////////////////////////

WhileLoop::WhileLoop(ProgramPtr _condition, ProgramPtr _statement_list)
    : Statement(0), condition(_condition), statement_list(_statement_list) {
  logger->info("construct WhileLoop\n");
  node_type = 'w';
}

void WhileLoop::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "while (";
  condition->print(dst, 0);
  dst << ")";
  if (statement_list) {
    dst << " {\n";
    statement_list->print(dst, indentation);
    printIndent(dst, --indentation);
    dst << "}";
  }
  dst << "\n";
}

int WhileLoop::evaluate(const Binding &_binding) const { return 0; }

// two labels: $L(2n) and $L(2n+1) if
int WhileLoop::codeGen(const Binding &_binding, int reg) const {
  print_map(binding, "WhileLoop");
  int label_statement = condition->getPos(binding) * 2;
  int label_condition = condition->getPos(binding) * 2 + 1;
  logger->info("generate code for WhileLoop\n");
  // start while loop
  printf("b $L%d\t\t# jump to WHILE condition\n", label_condition);
  printf("nop\n\n");
  // body of while loop
  printf("$L%d:\t\t# label for WHILE statement\n", label_statement);
  condition->codeGen(binding, reg);
  // condition for while loop
  printf("$L%d:\t\t# label for WHILE condition\n", label_condition);
  statement_list->codeGen(binding, reg);
  printf("bne $2,$0,$L%d\n",
         label_statement);  // run statement if result of condition is not 0
  printf("nop\n\n");
  return 0;
}

void WhileLoop::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)condition)->bind(const_cast<Binding &>(binding));
  ((Statement *)statement_list)->bind(binding);
}
