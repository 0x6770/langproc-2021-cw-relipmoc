#include "ast.hpp"

////////////////////////////////////////
// IfStatement
////////////////////////////////////////

IfStatement::IfStatement(ProgramPtr _condition, ProgramPtr _if_statement,
                         ProgramPtr _else_statement, int _label)
    : Statement(0),
      condition(_condition),
      if_statement(_if_statement),
      else_statement(_else_statement) {
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
}

int IfStatement::evaluate(const Binding &_binding) const { return 0; }

int IfStatement::codeGen(std::ofstream &dst, const Binding &_binding,
                         int reg) const {
  int random_id = rand() % 10000;
  int label_else = label * 2;
  int label_end = label * 2 + 1;

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### BEGIN IF ELSE STATEMENT ##### %d\u001b[0m\n", random_id);

  condition->codeGen(dst, binding, 2);

  if (else_statement) {
    dst << "\tnop" << std::endl;
    dst << "\tbeq\t\t\t$2,$0,$L" << label_else
        << "\t# jump to \"else statement\" if !condition" << std::endl;
    dst << "\tnop\n" << std::endl;
    if_statement->codeGen(dst, binding, 2);
    // TODO: use return to generate the label code;
    dst << "\tnop" << std::endl;
    dst << "\tb\t$L" << label_end << "\t\t# jump to \"next statement\""
        << std::endl;
    dst << "\tnop\n" << std::endl;
    dst << "$L" << label_else << ":";
    dst << "\t\t\t\t# \033[1;36m[LABEL]\033[0m else statement" << std::endl;
    else_statement->codeGen(dst, binding, 2);
  } else {
    dst << "\tnop" << std::endl;
    dst << "\tbeq\t\t\t$2,$0,$L" << label_end
        << "\t# jump to \"end of IF ELSE\" if !condition" << std::endl;
    dst << "\tnop\n" << std::endl;
    if_statement->codeGen(dst, binding, 2);
  }

  dst << "$L" << label_end << ":";  // next label
  dst << "\t\t\t\t# \033[1;36m[LABEL]\033[0m end of IF ELSE" << std::endl;

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

void IfStatement::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)condition)->passTypeBinding(_typebind);
  ((Program *)if_statement)->passTypeBinding(_typebind);
  if (else_statement) ((Program *)else_statement)->passTypeBinding(_typebind);
}

std::string IfStatement::getVariableType() { return "none for statements"; }

////////////////////////////////////////
// Case in Switch
////////////////////////////////////////

Case::Case(ProgramPtr _statements)
    : Statement(0), isDefault(1), statements(_statements) {
  node_type = 'C';
  logger->info("construct Case default\n");
};

Case::Case(int _constant, ProgramPtr _statements)
    : Statement(0), constant(_constant), statements(_statements) {
  node_type = 'C';
  logger->info("construct Case\n");
};

int Case::codeGen(std::ofstream &dst, const Binding &_binding, int reg) const {
  if (statements) {
    statements->codeGen(dst, binding, reg);
  }
  return 0;
};

void Case::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  if (isDefault) {
    dst << "default: {\n";
  } else {
    dst << "case " << constant << ": {\n";
  }
  if (statements) {
    statements->print(dst, indentation);
  }
  printIndent(dst, --indentation);
  dst << "}";
};

int Case::evaluate(const Binding &_binding) const { return 0; };

void Case::bind(const Binding &_binding) {
  binding = _binding;
  if (statements) {
    ((Program *)statements)->bind(binding);
  }
};

void Case::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  if (statements) {
    ((Program *)statements)->passFunctionName(_name, _pos);
  }
};

void Case::passLabel(int _label) {
  label = _label;
  if (statements) {
    ((Program *)statements)->passLabel(label);
  }
};

int Case::getConstant() const { return constant; }

int Case::getDefault() const { return isDefault; }

////////////////////////////////////////
// Cases in Switch
////////////////////////////////////////

Cases::Cases() : Statement(0) { logger->info("construct Cases\n"); };

void Cases::addCase(ProgramPtr _case) {
  int constant = ((Case *)_case)->getConstant();
  int isDefault = ((Case *)_case)->getDefault();

  // check multiple default labels
  if (isDefault) {
    if (hasDefault) {
      logger->error("multiple default labels in one switch\n");
      exit(1);
    } else {
      hasDefault++;
    }
  }

  // check duplicate cases
  if (constants.find(constant) != constants.end()) {
    logger->error("duplicate case value '%d'\n", constant);
    exit(1);
  }

  cases.push_back(_case);
};

int Cases::codeGen(std::ofstream &dst, const Binding &_binding, int reg) const {
  logger->error(
      "please use the Cases::codeGen overload below. \n"
      "int Cases::codeGen(std::ofstream &dst, const Binding &_binding, int "
      "reg, int switch_expr) "
      "const\n");
  return 0;
}

int Cases::codeGen(std::ofstream &dst, const Binding &_binding, int reg,
                   int switch_expr) const {
  int label_switch = label * 2;
  int label_default = -1;
  int index = 0;

  for (auto it : cases) {
    // skip default case
    if (!((Case *)it)->getDefault()) {
      dst << "\tlw\t\t\t$2," << switch_expr << "($fp)" << std::endl;
      dst << "\tli\t\t\t$3," << ((Case *)it)->getConstant() << "" << std::endl;
      dst << "\tbeq\t\t\t$2,$3,$L" << label_switch << "_" << index++ << ""
          << std::endl;
      dst << "\tnop" << std::endl;
      dst << std::endl;
    } else {
      label_default = index++;
    }
  }
  if (hasDefault) {
    if (label_default < 0) {
      logger->error("no label index for default case\n");
      exit(1);
    }
    dst << "\tb\t$L" << label_switch << "_" << label_default << "" << std::endl;
    dst << "\tnop" << std::endl;
    dst << std::endl;
  }

  index = 0;
  for (auto it : cases) {
    dst << "$L" << label_switch << "_" << index++ << ":" << std::endl;
    it->codeGen(dst, binding, reg);
  }

  return 0;
};

void Cases::print(std::ostream &dst, int indentation) const {
  for (auto it : cases) {
    it->print(dst, indentation);
    dst << "\n";
  }
};

int Cases::evaluate(const Binding &_binding) const { return 0; };

void Cases::bind(const Binding &_binding) {
  binding = _binding;
  for (auto it : cases) {
    ((Program *)it)->bind(binding);
  }
};

void Cases::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  for (auto it : cases) {
    ((Program *)it)->passFunctionName(_name, _pos);
  }
};

void Cases::passLabel(int _label) {
  label = _label;
  for (auto it : cases) {
    ((Program *)it)->passLabel(label);
  }
};

////////////////////////////////////////
// Switch
////////////////////////////////////////

Switch::Switch(ProgramPtr _expression, ProgramPtr _cases, int _label)
    : Statement(_expression), cases(_cases) {
  label = _label;
  logger->info("construct Switch\n");
};

int Switch::codeGen(std::ofstream &dst, const Binding &_binding,
                    int reg) const {
  int random_id = rand() % 10000;
  int label_switch_end = label * 2 + 1;

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### BEGIN SWITCH STATEMENT ##### %d\u001b[0m\n", random_id);

  expression->codeGen(dst, binding, reg);

  ((Cases *)cases)->codeGen(dst, binding, reg, expression->getPos(binding));

  dst << "$L" << label_switch_end << ":" << std::endl;

  printf("\t\t\t\t# \u001b[38;5;%dm", random_id % 256);
  printf("#### END   SWITCH STATEMENT ##### %d\u001b[0m\n", random_id);
  return 0;
};

void Switch::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "switch (";
  expression->print(dst, 0);
  dst << ") {\n";
  if (cases) {
    cases->print(dst, indentation);
    dst << "\n";
  }
  printIndent(dst, --indentation);
  dst << "}";
};

int Switch::evaluate(const Binding &_binding) const { return 0; };

void Switch::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)expression)->bind(const_cast<Binding &>(binding));
  if (cases) {
    ((Program *)cases)->bind(const_cast<Binding &>(binding));
  }
};

void Switch::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  ((Program *)expression)->passFunctionName(_name, _pos);
  if (cases) {
    ((Program *)cases)->passFunctionName(_name, _pos);
  }
};

void Switch::passLabel(int _label) {
  if (cases) {
    ((Program *)cases)->passLabel(label);
  }
};
