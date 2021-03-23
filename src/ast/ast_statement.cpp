#include "ast.hpp"

////////////////////////////////////////
// Statement
////////////////////////////////////////

Statement::Statement(ProgramPtr _expression) : expression(_expression) {}

void Statement::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  if (expression) expression->print(dst, indentation);
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
  logger->info("passing function name...%c\n", node_type);
  ((Program *)expression)->passFunctionName(_name, _pos);
}

void Statement::passLabel(int _label) {}

void Statement::passTypeBinding(TypeBinding &_typebind) {
  ((Program *)expression)->passTypeBinding(_typebind);
}

std::string Statement::getVariableType(){
  return "none for statements";
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
  // is_pointer = _is_pointer;
}

void VarDeclare::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << var_type << " " << id;
  if (expression) {
    dst << " = ";
    expression->print(dst, 0);
  }
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

void VarDeclare::passTypeBinding(TypeBinding &_typebind) {
  _typebind[id] = var_type;
  if (expression) {
    ((Program *)expression)->passTypeBinding(_typebind);
  }
}

std::string VarDeclare::getVariableType(){
  return "none for statements";
}
////////////////////////////////////////
// VarAssign
////////////////////////////////////////

VarAssign::VarAssign(std::string _name, ProgramPtr _expression)
    : Statement(_expression), name(_name) {
  with_left = 0;
}

VarAssign::VarAssign(ProgramPtr _left, ProgramPtr _expression)
    : Statement(_expression) {
  logger->info("construct VarAssign with dereference\n");
  assign_left = _left;
  with_left = 1;
  expression = _expression;
}

void VarAssign::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << name << " = ";
  expression->print(dst, 0);
}

int VarAssign::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for VarAssign\n");
  // std::cout << "entered here"  << " " << with_left<< std::endl;
  print_map(binding, "VarAssign");
  // std::cout << "entered here"  << " " << with_left<< std::endl;
  if (with_left == 0) {
    // std::cout << "entered here" << std::endl;
    if (binding.find(name) == binding.end()) {
      logger->error("%s has not been declared\n", name.c_str());
      exit(1);
    };
    int pos_in_binding = binding.at(name);
    expression->codeGen(binding, reg);
    printf("\tsw\t$2,%d($fp)\t# assign %s\n", pos_in_binding, name.c_str());
  }
  if (with_left == 1) {
    ((Dereference *)assign_left)->read(1);
    assign_left->codeGen(binding, 2);
    expression->codeGen(binding, 3);
    if (((Program *)expression)->getType() != 'i') {
      printf("\tlw\t$%d,%d($fp)\n", 3, expression->getPos(binding));
    }
    printf("\tlw\t$2,%d($fp)\n", assign_left->getPos(binding));
    printf("\tsw\t$3,%d($%d)\n", 0, 2);
  }
  return 0;
}

void VarAssign::bind(const Binding &_binding) {
  logger->info("binding...VarAssign\n");
  binding = _binding;
  print_map(binding, "VarAssign");
  ((Program *)expression)->bind(binding);
  if (with_left == 1) {
    ((Program *)assign_left)->bind(binding);
  }
}

void VarAssign::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  if (expression) {
    ((Program *)expression)->passFunctionName(_name, _pos);
  }
  if (with_left == 1) {
    ((Program *)assign_left)->passFunctionName(_name, _pos);
  }
}

void VarAssign::passTypeBinding(TypeBinding &_typebind) {
  // print_map(binding, "VarAssign type");
  typebind = _typebind;
  if (expression) {
    ((Program *)expression)->passTypeBinding(_typebind);
  }
  if (with_left == 1) {
    ((Program *)assign_left)->passTypeBinding(_typebind);
  }
  // std::cout << "finish assign variable" << std::endl;
}

std::string VarAssign::getVariableType(){
  return "none for statements";
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
    dst << ";\n";
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
    // std::cout << "entered here"  << " statements bind"<< std::endl;
  }
  print_map(binding, std::to_string(x));
}

void StatementList::passFunctionName(std::string _name, int _pos) {
  for (auto it : statements) {
    ((Program *)it)->passFunctionName(_name, _pos);
  }
  function_name = _name;
}

void StatementList::passLabel(int _label) {
  for (auto it : statements) {
    ((Program *)it)->passLabel(_label);  // pass give label to children
  }
};

void StatementList::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  for (auto it : statements) {
    ((Program *)it)->passTypeBinding(_typebind);
  }
  // std::cout << "the type finding for statemetnlist " << std::endl;
  // for(auto it: _typebind ){
  //  std::cout << it.first << " " << it.second << std::endl;
  //}
}


std::string StatementList::getVariableType(){
  return "none for statements";
}

////////////////////////////////////////
// IfStatement
////////////////////////////////////////
/*
IfStatement::IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
                         ProgramPtr _else_statement, int _label)
    : Statement(0),
      condition(_condition),
      if_statement(_if_statement),
      else_statement(_else_statement) {
  //setLabel(_label);
  label = _label;
  if (!condition) {
    logger->error("expected expression\t");
    print(std::cerr, 1);
    exit(1);
  }
}

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
  dst << "";
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

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### BEGIN IF ELSE STATEMENT ##### %d\u001b[0m\n", random_id);

  condition->codeGen(binding, 2);

  if (else_statement) {
    printf("\tnop\n");
    printf("\tbeq\t$2,$0,$L%s\t# jump to \"else statement\" if !condition\n",
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
    printf("$L%s:", label_else_string.c_str());
    printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m else statement\n");
    else_statement->codeGen(binding, 2);
  } else {
    printf("\tnop\n");
    printf("\tbeq\t$2,$0,$L%s\t# jump to \"end of IF ELSE\" if !condition\n",
           label_end_string.c_str());
    printf("\tnop\n\n");
    if_statement->codeGen(binding, 2);
  }

  printf("$L%s:", label_end_string.c_str());  // next label
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m end of IF ELSE\n");

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### END   IF ELSE STATEMENT ##### %d\u001b[0m\n", random_id);

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

void IfStatement::passLabel(int _label) {
  // pass give label to children
  if (if_statement) {
    ((Program *)if_statement)->passLabel(_label);
  }
  if (else_statement) {
    ((Program *)else_statement)->passLabel(_label);
  }
};


void IfStatement::passTypeBinding(TypeBinding &_typebind){
  typebind = _typebind;
    ((Program *)condition)->passTypeBinding(_typebind);
  ((Program *)if_statement)->passTypeBinding(_typebind);
  if (else_statement)
    ((Program *)else_statement)->passTypeBinding(_typebind);
}

std::string IfStatement::getVariableType(){
  return "none for statements";
}
*/