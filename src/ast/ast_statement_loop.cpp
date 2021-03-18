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

int WhileLoop::codeGen(const Binding &_binding, int reg) const {
  int random_id = rand() % 10000;

  int label_condition = label * 2;
  int label_end = label * 2 + 1;

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### BEGIN WHILE LOOP ##### %d\u001b[0m\n", random_id);

  print_map(binding, "WhileLoop");

  logger->info("generate code for WhileLoop\n");

  // condition for while loop
  printf("$L%d:", label_condition);
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m WHILE condition\n");
  condition->codeGen(binding, reg);
  printf("\tbeq\t$2,$0,$L%d", label_end);
  printf("\t# jump to end of WHILE\n");  // check condition again

  // body of while loop
  if (statement_list) statement_list->codeGen(binding, reg);
  printf("\tb\t$L%d", label_condition);
  printf("\t\t# jump to condition\n");  // check condition again
  printf("\tnop\n\n");

  printf("$L%d:", label_end);
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m end of WHILE\n");

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### END   WHILE LOOP ##### %d\u001b[0m\n", random_id);

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

int ForLoop::codeGen(const Binding &_binding, int reg) const {
  int random_id = rand() % 10000;
  int label_test = label * 2;
  int label_end = label * 2 + 1;

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### BEGIN FOR LOOP ##### %d\u001b[0m\n", random_id);

  if (init_expr) init_expr->codeGen(binding, reg);

  printf("$L%d:", label_test);
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m FOR test expression\n");

  if (test_expr) {
    test_expr->codeGen(binding, reg);
    printf("\tbeq\t$2,$0,$L%d", label_end);
    printf("\t# jump to end of FOR\n");
    printf("\tnop\n\n");
  }

  if (statement_list) statement_list->codeGen(binding, reg);
  if (update_expr) update_expr->codeGen(binding, reg);

  printf("\tb\t$L%d", label_test);
  printf("\t\t# jump to start of FOR\n");
  printf("\tnop\n\n");

  printf("$L%d:", label_end);
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m end of FOR\n");

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### END   FOR LOOP ##### %d\u001b[0m\n", random_id);

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

void ForLoop::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  if (init_expr) ((Program *)init_expr)->passTypeBinding(_typebind);
  if (test_expr) ((Program *)test_expr)->passTypeBinding(_typebind);
  if (update_expr) ((Program *)update_expr)->passTypeBinding(_typebind);
  if (statement_list) ((Statement *)statement_list)->passTypeBinding(_typebind);
}
