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

void Statement::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  ((Program *)expression)->passFunctionName(_name, _pos);
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
  std::string return_end = "end" + function_name;
  printf("\tb\t%s", return_end.c_str());
  printf(
      "\t\t# \033[1;33m[RETURN]\033[0m jump to end of "
      "function\n");
  printf("\tnop\n\n");
  return 0;
}

void Return::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)expression)->bind(binding);
}

void Return::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  // std::cout << _name << std::endl;
  ((Program *)expression)->passFunctionName(_name, _pos);
}

////////////////////////////////////////
// VarDeclare
////////////////////////////////////////

VarDeclare::VarDeclare(std::string _var_type, std::string _id,
                       ProgramPtr _expression, int _pos)
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
    printf("\tsw\t$2,%d($fp)\n", pos);
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

void VarDeclare::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
  if (expression) {
    ((Program *)expression)->passFunctionName(_name, _pos);
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
  printf("\tsw\t$2,%d($fp)\t# assign %s\n", pos_in_binding, name.c_str());
  return 0;
}

void VarAssign::bind(const Binding &_binding) {
  logger->info("binding...VarAssign\n");
  binding = _binding;
  print_map(binding, "VarAssign");
  ((Program *)expression)->bind(binding);
}

void VarAssign::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  if (expression) {
    ((Program *)expression)->passFunctionName(_name, _pos);
  }
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
  print_map(binding, "StatementList");
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
    if (it->getType() == 'A') {
      ((Array *)it)->add_bind(binding);
    }
    ((Statement *)it)->bind(binding);
  }
  print_map(binding, std::to_string(x));
}

void StatementList::passFunctionName(std::string _name, int _pos) {
  for (auto it : statements) {
    // std::cout << "entered pass name in statemetlist" << std::endl;
    ((Program *)it)->passFunctionName(_name, _pos);
  }
  function_name = _name;
  // std::cout << _name << std::endl;
}

////////////////////////////////////////
// IfStatement
////////////////////////////////////////

IfStatement::IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
                         ProgramPtr _else_statement, int _label)
    : Statement(0),
      condition(_condition),
      if_statement(_if_statement),
      else_statement(_else_statement),
      label(_label) {}

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

int IfStatement::codeGen(const Binding &_binding, int reg) const {
  int random_id = rand() % 10000;
  int label_end = label * 2;
  int label_else_statement = label * 2 + 1;
  std::string label_end_string =
      function_name + "_" + std::to_string(label_end);
  std::string label_else_string =
      function_name + "_" + std::to_string(label_else_statement);
  printf(
      "\t\t\t\t# \u001b[38;5;%dm#### BEGIN IF ELSE STATEMENT "
      "##### %d\u001b[0m\n",
      random_id % 256, random_id);

  condition->codeGen(binding, 2);

  if (else_statement) {
    printf("\tnop\n");
    printf(
        "\tbeq\t$2,$0,$L%s\t# jump to \"else "
        "statement\" if !condition\n",
        label_else_string.c_str());
    printf("\tnop\n\n");
    if_statement->codeGen(binding, 2);
    // TODO: use return to generate the label code;
    printf("\tnop\n");
    printf(
        "\tb\t$L%s\t\t# jump to \"next "
        "statement\"\n",
        label_end_string.c_str());
    printf("\tnop\n\n");
    printf("$L%s:\t\t\t\t# \033[1;36m[LABEL]\033[0m else statement\n",
           label_else_string.c_str());
    else_statement->codeGen(binding, 2);
  } else {
    printf("\tnop\n");
    printf("\tbeq\t$2,$0,$L%s\t# jump to \"end of IF ELSE\" if !condition\n",
           label_end_string.c_str());
    printf("\tnop\n\n");
    if_statement->codeGen(binding, 2);
  }

  printf("$L%s:\t\t\t\t# \033[1;36m[LABEL]\033[0m end of IF ELSE\n",
         label_end_string.c_str());  // next label

  printf(
      "\t\t\t\t# \u001b[38;5;%dm#### END   IF ELSE STATEMENT "
      "##### %d\u001b[0m\n",
      random_id % 256, random_id);

  return 0;
}

void IfStatement::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)condition)->bind(binding);
  ((Program *)if_statement)->bind(binding);
  if (else_statement) ((Program *)else_statement)->bind(binding);
}

void IfStatement::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
  ((Program *)condition)->passFunctionName(_name, _pos);
  ((Program *)if_statement)->passFunctionName(_name, _pos);
  if (else_statement)
    ((Program *)else_statement)->passFunctionName(_name, _pos);
}
