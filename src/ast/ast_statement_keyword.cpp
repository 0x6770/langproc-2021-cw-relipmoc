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
  dst << ";";
}

int Return::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for Return\n");
  expression->codeGen(binding, 2);
  std::string return_end = "end" + function_name;
  printf("\tb\t%s", return_end.c_str());
  printf("\t\t# \033[1;33m[RETURN]\033[0m jump to end of function\n");
  printf("\tnop\n\n");
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

void Return::passTypeBinding(TypeBinding &_typebind){
  typebind = _typebind;
  ((Program *)expression)->passTypeBinding(_typebind);
}

////////////////////////////////////////
// Continue
////////////////////////////////////////

Continue::Continue() : Statement(0) {
  logger->info("construct Continue\n");
  node_type = 'c';
}

void Continue::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "continue;";
}

int Continue::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for Continue\n");
  std::string loop_start =
      "$L" + function_name + "_" + std::to_string(label * 2);
  printf("\tb\t%s", loop_start.c_str());
  printf("\t\t# \033[1;33m[CONTINUE]\033[0m jump to the start\n");
  printf("\tnop\n\n");
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

void Continue::passTypeBinding(TypeBinding &_typebind){
  
}
////////////////////////////////////////
// Break
////////////////////////////////////////

Break::Break() : Statement(0) {
  logger->info("construct Break\n");
  node_type = 'b';
}

void Break::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << "break;";
}

int Break::codeGen(const Binding &_binding, int reg) const {
  logger->info("generate code for Break\n");
  std::string loop_end =
      "$L" + function_name + "_" + std::to_string(label * 2 + 1);
  printf("\tb\t%s", loop_end.c_str());
  printf("\t\t# \033[1;33m[BREAK]\033[0m jump to the end\n");
  printf("\tnop\n\n");
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

void Break::passTypeBinding(TypeBinding &_typebind){
  
}