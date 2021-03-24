#include <ast.hpp>

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
}

int Return::codeGen(std::ofstream &dst, const Binding &_binding,
                    int reg) const {
  logger->info("generate code for Return\n");
  expression->codeGen(dst, binding, 2);
  std::string return_end = "end" + function_name;
  dst << "\tb\t" << return_end.c_str();
  dst << "\t\t# \033[1;33m[RETURN]\033[0m jump to end of function" << std::endl;
  dst << "\tnop\n" << std::endl;
  return 0;
}

void Return::bind(const Binding &_binding) {
  binding = _binding;
  ((Program *)expression)->bind(binding);
}

void Return::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
  ((Program *)expression)->passFunctionName(_name, _pos);
}

void Return::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
  ((Program *)expression)->passTypeBinding(_typebind);
}

std::string Return::getVariableType() { return "none for statements"; }

////////////////////////////////////////
// Continue
////////////////////////////////////////

Continue::Continue() : Statement(0) {
  logger->info("construct Continue\n");
  node_type = 'c';
}

void Continue::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "continue";
}

int Continue::codeGen(std::ofstream &dst, const Binding &_binding,
                      int reg) const {
  logger->info("generate code for Continue\n");
  int loop_start = label * 2;
  dst << "\tb\t$L" << loop_start;
  dst << "\t\t# \033[1;33m[CONTINUE]\033[0m jump to the start" << std::endl;
  dst << "\tnop\n" << std::endl;
  return 0;
}

void Continue::bind(const Binding &_binding) {}

void Continue::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
}

void Continue::passLabel(int _label) {
  if (_label < 0) {
    logger->error("'continue' statement not in loop statement\n");
    exit(1);
  }
  label = _label;
}

void Continue::passTypeBinding(TypeBinding &_typebind) {}

std::string Continue::getVariableType() { return "none for statements"; }
////////////////////////////////////////
// Break
////////////////////////////////////////

Break::Break() : Statement(0) {
  logger->info("construct Break\n");
  node_type = 'b';
}

void Break::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "break";
}

int Break::codeGen(std::ofstream &dst, const Binding &_binding, int reg) const {
  logger->info("generate code for Break\n");
  int loop_end = label * 2 + 1;
  dst << "\tb\t$L" << loop_end;
  dst << "\t\t# \033[1;33m[BREAK]\033[0m jump to the end" << std::endl;
  dst << "\tnop\n" << std::endl;
  return 0;
}

void Break::bind(const Binding &_binding) {}

void Break::passFunctionName(std::string _name, int _pos) {
  function_name = _name;
}

void Break::passLabel(int _label) {
  if (_label < 0) {
    logger->error("'break' statement not in loop or switch statement\n");
    exit(1);
  }
  label = _label;
}

void Break::passTypeBinding(TypeBinding &_typebind) {}

std::string Break::getVariableType() { return "none for statements"; }
