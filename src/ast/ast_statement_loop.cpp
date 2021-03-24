#include "ast.hpp"

////////////////////////////////////////
// WhileLoop
////////////////////////////////////////

WhileLoop::WhileLoop(ProgramPtr _condition, ProgramPtr _statement_list,
                     int _label)
    : Statement(0), condition(_condition), statement_list(_statement_list) {
  label = _label;
  logger->info("construct WhileLoop\n");
  node_type = 'w';
  if (!condition) {
    logger->error("expected expression");
    exit(1);
  }
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
}

int WhileLoop::evaluate(const Binding &_binding) const { return 0; }

int WhileLoop::codeGen(std::ofstream &dst, const Binding &_binding,
                       int reg) const {
  int random_id = rand() % 10000;

  int label_condition = label * 2;
  int label_end = label * 2 + 1;

  dst << "\t\t\t\t# \u001b[38;5;" << random_id % 256 << "m";
  dst << "#### BEGIN WHILE LOOP ##### " << random_id << "\u001b[0m"
      << std::endl;

  print_map(binding, "WhileLoop");

  logger->info("generate code for WhileLoop\n");

  // condition for while loop
  dst << "$L" << label_condition << ":";
  dst << "\t\t\t\t# \033[1;36m[LABEL]\033[0m WHILE condition" << std::endl;
  condition->codeGen(dst, binding, reg);
  dst << "\tbeq\t\t$2,$0,$L" << label_end;
  dst << "\t# jump to end of WHILE" << std::endl;  // check condition again

  // body of while loop
  if (statement_list) statement_list->codeGen(dst, binding, reg);
  dst << "\tb\t$L" << label_condition;
  dst << "\t\t# jump to condition" << std::endl;  // check condition again
  dst << "\tnop" << std::endl;
  dst << std::endl;

  dst << "$L" << label_end << ":";
  dst << "\t\t\t\t# \033[1;36m[LABEL]\033[0m end of WHILE" << std::endl;

  dst << "\t\t\t\t# \u001b[38;5;" << random_id % 256 << "m";
  dst << "#### END   WHILE LOOP ##### " << random_id << "\u001b[0m"
      << std::endl;

  return 0;
}

void WhileLoop::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)condition)->bind(const_cast<Binding &>(binding));
  if (statement_list) ((Statement *)statement_list)->bind(binding);
}

void WhileLoop::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
  ((Program *)condition)->passFunctionName(_name, _pos);
  if (statement_list)
    ((Statement *)statement_list)->passFunctionName(_name, _pos);
}

void WhileLoop::passLabel(int _label) {
  if (statement_list) {
    ((Program *)statement_list)->passLabel(label);  // pass own label
  }
}

void WhileLoop::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)condition)->passTypeBinding(_typebind);
  if (statement_list) ((Statement *)statement_list)->passTypeBinding(_typebind);
}

std::string WhileLoop::getVariableType() { return "none for statements"; }

////////////////////////////////////////
// For Loop
// init_expr → test_expr → body
//            ↑ update_expr ↵
////////////////////////////////////////

ForLoop::ForLoop(ProgramPtr _init_expr, ProgramPtr _test_expr,
                 ProgramPtr _update_expr, ProgramPtr _statement_list,
                 int _label)
    : Statement(0),
      init_expr(_init_expr),
      test_expr(_test_expr),
      update_expr(_update_expr),
      statement_list(_statement_list) {
  label = _label;
  logger->info("construct For Loop\n");
};

int ForLoop::codeGen(std::ofstream &dst, const Binding &_binding,
                     int reg) const {
  int random_id = rand() % 10000;
  int label_test = label * 2;
  int label_end = label * 2 + 1;

  dst << "\t\t\t\t# \u001b[38;5;" << random_id % 256 << "m";
  dst << "#### BEGIN FOR LOOP ##### " << random_id << "\u001b[0m" << std::endl;

  if (init_expr) init_expr->codeGen(dst, binding, reg);

  dst << "$L" << label_test << ":";
  dst << "\t\t\t\t# \033[1;36m[LABEL]\033[0m FOR test expression" << std::endl;

  if (test_expr) {
    test_expr->codeGen(dst, binding, reg);
    dst << "\tbeq\t\t$2,$0,$L" << label_end;
    dst << "\t# jump to end of FOR" << std::endl;
    dst << "\tnop" << std::endl;
    dst << std::endl;
  }

  if (statement_list) statement_list->codeGen(dst, binding, reg);
  if (update_expr) update_expr->codeGen(dst, binding, reg);

  dst << "\tb\t$L" << label_test << "";
  dst << "\t\t# jump to start of FOR" << std::endl;
  dst << "\tnop" << std::endl;
  dst << std::endl;

  dst << "$L" << label_end << ":";
  dst << "\t\t\t\t# \033[1;36m[LABEL]\033[0m end of FOR" << std::endl;

  dst << "\t\t\t\t# \u001b[38;5;" << random_id % 256 << "m";
  dst << "#### END   FOR LOOP ##### " << random_id << "\u001b[0m" << std::endl;

  return 0;
}

void ForLoop::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "for (";
  if (init_expr) init_expr->print(dst, 0);
  dst << ";";
  if (test_expr) test_expr->print(dst, 0);
  dst << ";";
  if (update_expr) update_expr->print(dst, 0);
  dst << ")";
  if (statement_list) {
    dst << " {\n";
    statement_list->print(dst, indentation);
    printIndent(dst, --indentation);
    dst << "}";
  }
};

int ForLoop::evaluate(const Binding &_binding) const { return 0; };

void ForLoop::bind(const Binding &_binding) {
  binding = _binding;
  // std::cout << "entre bind for For loop" << std::endl;
  //  add variable declaration in initialization expression to binding
  if (init_expr && init_expr->getType() == 'd') {
    std::string id = ((VarDeclare *)init_expr)->getId();
    int pos = init_expr->getPos(binding);
    logger->info("find declaration for \"%s\" at %d\n", id.c_str(), pos);
    binding[id] = pos;
    print_map(binding, "for loop");
  }
  if (init_expr) ((Program *)init_expr)->bind(const_cast<Binding &>(binding));
  if (test_expr) ((Program *)test_expr)->bind(const_cast<Binding &>(binding));
  if (update_expr)
    ((Program *)update_expr)->bind(const_cast<Binding &>(binding));
  if (statement_list) ((Statement *)statement_list)->bind(binding);
  // std::cout << "finish binding for FOR " << std::endl;
};

void ForLoop::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
  if (statement_list)
    ((Statement *)statement_list)->passFunctionName(_name, _pos);
};

void ForLoop::passLabel(int _label) {
  if (statement_list) {
    ((Program *)statement_list)->passLabel(label);  // pass own label
  }
}

std::string ForLoop::getVariableType() { return "none for statements"; }
void ForLoop::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  if (init_expr) ((Program *)init_expr)->passTypeBinding(_typebind);
  if (test_expr) ((Program *)test_expr)->passTypeBinding(_typebind);
  if (update_expr) ((Program *)update_expr)->passTypeBinding(_typebind);
  if (statement_list) ((Statement *)statement_list)->passTypeBinding(_typebind);
}
