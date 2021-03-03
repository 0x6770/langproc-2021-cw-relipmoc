#include "arg.hpp"
#include "ast.hpp"

Log *logger;

int main(int argc, char **argv) {
  struct arguments arguments;
  Binding binding;

  // Default values for arguments
  arguments.source_file = 0;
  arguments.output_file = (char *)"a.out";
  arguments.level = warn;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  logger = new Log(arguments.level);
  logger->info("SOURCE_FILE = %s\n", arguments.source_file);
  logger->info("OUTPUT_FILE = %s\n", arguments.output_file);

  FILE *source_file = fopen(arguments.source_file, "r");
  yyin = source_file;
  const Program *ast = parseAST(source_file);
  fclose(source_file);

  ast->codeGen(binding, 2);

  // std::cout << "====================\n";
  // std::cout << "exit status: ";
  // std::cout << ast->evaluate(0);
  // std::cout << std::endl;

  std::cerr << std::endl;
  ast->print(std::cerr, 0);
  std::cerr << std::endl;

  exit(0);
}
