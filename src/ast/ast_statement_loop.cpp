#include "ast.hpp"

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

// TODO add support for return
int WhileLoop::codeGen(const Binding &_binding, int reg) const {
  int random_id = rand() % 10000;

  printf(
      "\t\t\t\t# \u001b[38;5;%dm#### BEGIN WHILE LOOP "
      "##### %d\u001b[0m\n",
      random_id % 256, random_id);

  print_map(binding, "WhileLoop");
  int label_condition = condition->getPos(binding) * 2;
  int label_end = condition->getPos(binding) * 2 + 1;
  std::string label_condition_string =
      function_name + "_" + std::to_string(label_condition);
  std::string label_end_string =
      function_name + "_" + std::to_string(label_end);
  logger->info("generate code for WhileLoop\n");

  // condition for while loop
  printf("$L%s:", label_condition_string.c_str());
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m WHILE condition\n");
  condition->codeGen(binding, reg);
  printf("\tbeq\t$2,$0,$L%s", label_end_string.c_str());
  printf("\t# jump to end of WHILE\n");  // check condition again

  // body of while loop
  statement_list->codeGen(binding, reg);
  printf("\tb\t$L%s", label_condition_string.c_str());
  printf("\t\t# jump to condition\n");  // check condition again
  printf("\tnop\n\n");

  printf("$L%s:", label_end_string.c_str());
  printf("\t\t\t\t# \033[1;36m[LABEL]\033[0m end of WHILE\n");

  printf(
      "\t\t\t\t# \u001b[38;5;%dm#### END   WHILE LOOP "
      "##### %d\u001b[0m\n",
      random_id % 256, random_id);

  return 0;
}

void WhileLoop::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)condition)->bind(const_cast<Binding &>(binding));
  ((Statement *)statement_list)->bind(binding);
}

void WhileLoop::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
  ((Program *)condition)->passFunctionName(_name, _pos);
  ((Statement *)statement_list)->passFunctionName(_name, _pos);
}

////////////////////////////////////////
// For Loop
// init_expr → test_expr → body
//            ↑ update_expr ↵
////////////////////////////////////////

ForLoop::ForLoop(ProgramPtr _init_expr, ProgramPtr _test_expr,
                 ProgramPtr _update_expr, ProgramPtr _statement_list)
    : Statement(0),
      init_expr(_init_expr),
      test_expr(_test_expr),
      update_expr(_update_expr),
      statement_list(_statement_list) {
  logger->info("construct For Loop\n");
};

int ForLoop::codeGen(const Binding &_binding, int reg) const { return 0; }

void ForLoop::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "for (";
  init_expr->print(dst, 0);
  test_expr->print(dst, 0);
  update_expr->print(dst, 0);
  dst << ")";
  if (statement_list) {
    dst << " {\n";
    statement_list->print(dst, indentation);
    printIndent(dst, --indentation);
    dst << "}";
  }
  dst << "\n";
};

int ForLoop::evaluate(const Binding &_binding) const { return 0; };

void ForLoop::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)init_expr)->bind(const_cast<Binding &>(binding));
  ((Program *)test_expr)->bind(const_cast<Binding &>(binding));
  ((Program *)update_expr)->bind(const_cast<Binding &>(binding));
  ((Statement *)statement_list)->bind(binding);
};

void ForLoop::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
  function_name = _name;
  ((Program *)init_expr)->passFunctionName(_name, _pos);
  ((Program *)test_expr)->passFunctionName(_name, _pos);
  ((Program *)update_expr)->passFunctionName(_name, _pos);
  ((Statement *)statement_list)->passFunctionName(_name, _pos);
};
