#include "ast.hpp"

////////////////////////////////////////
// Function
////////////////////////////////////////

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   int _pos, int _call, int _arg_size)
    : type(_type), name(_name), statements(_statements) {
  int tmp_size = _pos + 8;
  tmp_size = tmp_size + (_arg_size)*4 + 4;
  // free space for the number of arguments;
  if (_call == 1) tmp_size = tmp_size + 4;
  // add 4 for store the value in $ra when there is function call in the
  // function;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  // size = size + 16;
  logger->info("construct Function with no arguments\n");
  node_type = 'F';
  passFunctionName(_name, _arg_size * 4);
  with_function_call = _call;
  arg_size = _arg_size;
  // std::cout << _arg_size << std::endl;
  // if(_statements == 0){is_define = 1;}
}

Function::Function(std::string _type, std::string _name, ProgramPtr _statements,
                   ProgramPtr _arguments, int _pos, int _call, int _arg_size) {
  type = _type;
  statements = _statements;
  arguments = _arguments;
  int tmp_size = _pos + 8;
  tmp_size = tmp_size + (_arg_size)*4 + 4;
  if (_call == 1) tmp_size = tmp_size + 4;
  size = (tmp_size % 8) ? tmp_size + 4 : tmp_size;
  // ADD spaces for four parameters:
  // size = size + 16;
  logger->info("construct Function with arguments\n");
  node_type = 'F';
  with_param = 1;
  // std::string function_name = _name + "_" +
  // ((Paramlist*)arguments)->get_type_string();
  name = _name;
  passFunctionName(_name, _arg_size * 4);
  with_function_call = _call;
  arg_size = _arg_size;
  // if(_statements == 0){is_define = 1;}
  // std::cout << _arg_size << std::endl;
}

void Function::print(std::ostream &dst, int indentation) const {
  logger->info("====================\n");
  logger->info("formatted: \n");
  printIndent(dst, indentation);
  dst << type;
  dst << " ";
  dst << name;
  dst << "(";
  if (with_param == 1) {
    arguments->print(dst, indentation);
  }
  dst << ") {\n";

  statements->print(dst, indentation);
  dst << "}";
}

int Function::evaluate(const Binding &_binding) const {
  return statements->evaluate(binding);
  return 0;
}

int Function::codeGen(const Binding &_binding, int reg) const {
  logger->info("====================\n");
  logger->info("Build variable mapping in Function\n");
  Binding container;
  Binding temp;
  TypeBinding variable_bind;
  // when the function has arguments up-to four
  if (with_param == 1) {
    temp = ((Paramlist *)arguments)->return_bind(container, size);
    ((StatementList *)statements)->bind(temp);
    ((Paramlist *)arguments)->passTypeBinding(variable_bind);
  } else {
    ((StatementList *)statements)->bind(binding);
  }

  ((Program *)statements)->passTypeBinding(variable_bind);
  // set labels for key words: `continue` and `break`
  ((StatementList *)statements)->passLabel(label);

  // make unique end label:
  std::string function_end = "end" + name;
  logger->info("====================\n");
  logger->info("generate code for Function\n");
  logger->info("size of stack frame: %d\n", getSize());
  printf(".global\t%s\n", name.c_str());
  printf("\n");
  printf("%s:\n", name.c_str());
  printf("\taddiu\t$sp,$sp,%d\n", -size);
  if (with_function_call == 1) {
    printf("\tsw\t$31,%d($sp)\n", (size - 4));
    printf("\tsw\t$fp,%d($sp)\n", (size - 8));
  } else {
    printf("\tsw\t$fp,%d($sp)\n", (size - 4));
  }
  printf("\tmove\t$fp,$sp\n");
  // store the values in the register a0-a3 in the stack.
  if (with_param == 1) {
    arguments->codeGen(temp, 2);
  }
  statements->codeGen(binding, 2);  // store  result result of to $2
  printf("%s", function_end.c_str());
  printf(":\t\t\t\t# \033[1;036m[LABEL]\033[0m end of function\n");
  // TODO: return statement to determine the label part
  printf("\tmove\t$sp,$fp\n");
  if (with_function_call == 1) {
    printf("\tlw\t$31,%d($sp)\n", (size - 4));
    printf("\tlw\t$fp,%d($sp)\n", (size - 8));
  } else {
    printf("\tlw\t$fp,%d($sp)\n", (size - 4));
  }
  printf("\taddiu\t$sp,$sp,%d\n", size);
  printf("\tjr\t$31\n");
  printf("\tnop\n");
  printf("\n");

  return 0;
}

void Function::bind(const Binding &_binding) {}

void Function::passFunctionName(std::string _name, int _pos) {
  ((Program *)statements)->passFunctionName(_name, _pos);
}

void Function::passTypeBinding(TypeBinding &_typebind) {
  //((Program *)statements)->passTypeBinding(_typebind);
}

////////////////////////////////////////
// MultiFunction
////////////////////////////////////////

MultiFunction::MultiFunction(ProgramPtr _function) {
  logger->info("construct one function");
  functions.push_back(_function);
}

void MultiFunction::add_function(ProgramPtr _function) {
  logger->info("construct more functions");
  functions.push_back(_function);
}

void MultiFunction::print(std::ostream &dst, int indentation) const {
  for (auto function : this->functions) {
    function->print(dst, indentation);
  }
}
int MultiFunction::codeGen(const Binding &_binding, int reg) const {
  for (auto it : functions) {
    ((Program *)it)->codeGen(binding, 2);
  }
  return 0;
}
int MultiFunction::evaluate(const Binding &_binding) const { return 0; }

void MultiFunction::bind(const Binding &_binding) {}

void MultiFunction::passFunctionName(std::string _name, int _pos) {}

void MultiFunction::passTypeBinding(TypeBinding &_typebind) {
  typebind = _typebind;
}

////////////////////////////////////////
// Param
////////////////////////////////////////

Param::Param(std::string _type, std::string _name) {
  logger->info("construct one parameter\n");
  type = _type;
  name = _name;
  is_pointer = 0;
}

void Param::print(std::ostream &dst, int indentation) const {
  dst << type << " " << name;
}
Param::Param(std::string _type, std::string _name, int _is_pointer) {
  logger->info("construct one parameter [Pointer]\n");
  type = _type;
  name = _name;
  is_pointer = _is_pointer;
}
int Param::codeGen(const Binding &_binding, int reg) const {
  Binding temp = binding;
  std::string variable_name = name;
  printf("\tsw\t$%d,%d($fp)\n", reg, temp[variable_name]);
  return 0;
}

int Param::evaluate(const Binding &_binding) const { return 0; }

void Param::bind(const Binding &_binding) {}

void Param::passFunctionName(std::string _name, int _pos) {}

std::string Param::getName() { return name; }

Binding Param::return_bind(Binding &_binding, int pos) {
  // std::string p_name;
  if (is_pointer == 1) {
    // p_name = "*" + name;
    _binding[name] = pos;
  } else {
    _binding[name] = pos;
  }
  binding = _binding;
  return _binding;
}

std::string Param::getType() { return type; }

void Param::passTypeBinding(TypeBinding &_typebind) {
  _typebind[name] = type;
  typebind = _typebind;
}

////////////////////////////////////////
// Param List
////////////////////////////////////////

Paramlist::Paramlist() {
  // do nothing;
  logger->info("Build an empty parameter list\n");
}

Paramlist::Paramlist(ProgramPtr argument) {
  parameters.push_back(argument);
  logger->info("construct paramlist with on param\n");
}

void Paramlist::add_argument(ProgramPtr argument) {
  parameters.push_back(argument);
}

void Paramlist::print(std::ostream &dst, int indentation) const {
  for (auto it : parameters) {
    ((Param *)it)->print(dst, indentation);
  }
}

int Paramlist::codeGen(const Binding &_binding, int reg) const {
  std::string key;
  int regtemp = 4;

  int count = 1;

  for (auto it : parameters) {
    if (count <= 4) {
      ((Param *)it)->codeGen(binding, regtemp);
      regtemp = regtemp + 1;
      count = count + 1;
    }
  }

  return 0;
}

int Paramlist::evaluate(const Binding &_binding) const { return 0; }

void Paramlist::bind(const Binding &_binding) {}

Binding Paramlist::return_bind(const Binding &_binding, int _pos) {
  // _pos is the size of stack in the function:
  Binding result;
  Binding temp;
  int n = _pos;
  int counter = 1;
  std::string tmp_string;
  for (auto it : parameters) {
    if (counter <= 4) {
      result = ((Param *)it)->return_bind(temp, n);
      n = n + 4;
      counter = counter + 1;
    } else {
      tmp_string = ((Param *)it)->getName();
      result[tmp_string] = n;
      n = n + 4;
    }
  }
  binding = result;
  return result;
}

std::string Paramlist::get_type_string() {
  std::string name = ((Param *)parameters[0])->getType();
  int n = parameters.size();
  name = name + "_" + std::to_string(n);
  return name;
}

void Paramlist::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
}

void Paramlist::passTypeBinding(TypeBinding &_typebind) {
  for (auto it : parameters) {
    ((Param *)it)->passTypeBinding(_typebind);
  }
  typebind = _typebind;
  /*for(auto it: _typebind ){
    std::cout << it.first << " " << it.second << std::endl;
  }
    for(auto it: typebind ){
    std::cout << it.first << " " << it.second << std::endl;
  }*/
}

////////////////////////////////////////
// FunctionCall
////////////////////////////////////////

FunctionCall::FunctionCall(std::string _name, int _pos) {
  name = _name;
  pos = _pos;
  logger->info("construct function NO arguments");
  with_argument = 0;
}

FunctionCall::FunctionCall(std::string _name, ProgramPtr _argument, int _pos) {
  logger->info("construct function call with arguments");
  name = _name;
  pos = _pos;
  arguments = _argument;
  with_argument = 1;
}

void FunctionCall::add_argument(ProgramPtr _argument) {
  // arguments.push_back(_Argument);
}

void FunctionCall::print(std::ostream &dst, int indentation) const {
  printIndent(dst, indentation);
  dst << name << "(";
  if (arguments) {
    arguments->print(dst, --indentation);
  }
  dst << ")";
}

// assuming all variable types are int for now
int FunctionCall::codeGen(const Binding &_binding, int reg) const {
  // int pos = 20;
  if (with_argument == 1) {
    ((Program *)arguments)->codeGen(binding, 2);
  }
  printf("\t.option\tpic0\n");
  printf("\tjal\t%s\n", name.c_str());
  printf("\tnop\n");
  printf("\t.option\tpic2\n");
  printf("\tsw\t$2,%d($fp)\t# store the value after function call\n", pos);
  return 0;
}

int FunctionCall::evaluate(const Binding &_binding) const { return 0; }

void FunctionCall::bind(const Binding &_binding) {
  binding = _binding;
  if (with_argument == 1) {
    ((Program *)arguments)->bind(binding);
  }
}

void FunctionCall::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
}

void FunctionCall::passTypeBinding(TypeBinding &_typebind) {}

ExpressionList::ExpressionList(ProgramPtr _argument) {
  logger->info("Build expression list\n");
  arguments.push_back(_argument);
}

void ExpressionList::add_argument_expression(ProgramPtr _expr) {
  logger->info("add more expr\n");
  arguments.push_back(_expr);
}

void ExpressionList::print(std::ostream &dst, int indentation) const {
  for (auto it : arguments) {
    it->print(dst, indentation);
  }
}

int ExpressionList::codeGen(const Binding &_binding, int reg) const {
  int reg_temp = 4;
  int temp_location = 16;

  if (arguments.size() > 4) {
    for (unsigned int j = 4; j < arguments.size(); j++) {
      ((Program *)arguments[j])->codeGen(binding, 2);
      printf("\tsw\t$2,%d($fp)\n", temp_location);
      temp_location = temp_location + 4;
    }
  }

  for (unsigned int i = 0; i < 4; i++) {
    if (i < arguments.size()) {
      ((Program *)arguments[i])->codeGen(binding, 2);
      printf("\tmove\t$%d,$2\n", reg_temp);
      reg_temp = reg_temp + 1;
    }
  }
  return 0;
}

int ExpressionList::evaluate(const Binding &_binding) const { return 0; }

void ExpressionList::bind(const Binding &_binding) {
  binding = _binding;
  for (auto it : arguments) {
    ((Program *)it)->bind(binding);
  }
}

void ExpressionList::passFunctionName(std::string _name, int _pos) {
  pos = pos + _pos;
}

void ExpressionList::passTypeBinding(TypeBinding &_typebind) {}

FunctionDeclare::FunctionDeclare(std::string _name) { name = _name; }

FunctionDeclare::FunctionDeclare(std::string _name, ProgramPtr _param_list) {
  name = _name;
  parameters = _param_list;
}

void FunctionDeclare::print(std::ostream &dst, int indentation) const {}

int FunctionDeclare::codeGen(const Binding &_binding, int reg) const {
  return 0;
}

int FunctionDeclare::evaluate(const Binding &_binding) const { return 0; }

void FunctionDeclare::bind(const Binding &_binding) {}

void FunctionDeclare::passFunctionName(std::string _name, int _pos) {}

void FunctionDeclare::passTypeBinding(TypeBinding &_typebind) {}
