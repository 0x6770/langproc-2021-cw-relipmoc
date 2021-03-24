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

int Statement::codeGen(std::ofstream &dst, const Binding &_binding,
                       int reg) const {
  logger->info("generate code for statement\n");
  if (expression) expression->codeGen(dst, binding, reg);
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

std::string Statement::getVariableType() { return "none for statements"; }

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

int VarDeclare::codeGen(std::ofstream &dst, const Binding &_binding,
                        int reg) const {
  logger->info("generate code for VarDeclare\n");

  if (expression) {
    expression->codeGen(dst, binding, reg);
    dst << "\tsw\t\t$2," << pos << "($fp)" << std::endl;
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

std::string VarDeclare::getVariableType() { return "none for statements"; }
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

int VarAssign::codeGen(std::ofstream &dst, const Binding &_binding,
                       int reg) const {
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
    expression->codeGen(dst, binding, reg);
    dst << "\tsw\t\t$2," << pos_in_binding << "($fp)\t\t\t# assign "
        << name.c_str() << "" << std::endl;
  }
  if (with_left == 1) {
    ((Dereference *)assign_left)->read(1);
    assign_left->codeGen(dst, binding, 2);
    expression->codeGen(dst, binding, 3);
    if (((Program *)expression)->getType() != 'i') {
      dst << "\tlw\t\t$" << 3 << "," << expression->getPos(binding) << "($fp)"
          << std::endl;
    }
    dst << "\tlw\t\t$2," << assign_left->getPos(binding) << "($fp)"
        << std::endl;
    dst << "\tsw\t\t$3," << 0 << "($" << 2 << ")" << std::endl;
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

std::string VarAssign::getVariableType() { return "none for statements"; }

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

int StatementList::codeGen(std::ofstream &dst, const Binding &_binding,
                           int reg) const {
  print_map(binding, "StatementList");
  for (auto it : statements) {
    it->codeGen(dst, binding, 2);
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

std::string StatementList::getVariableType() { return "none for statements"; }
