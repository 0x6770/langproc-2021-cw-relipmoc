#include "arg.hpp"
#include "ast.hpp"

extern FILE *yyin;

int main(int argc, char **argv) {
  char OUTPUT_FILE[] = "a.out";
  struct arguments arguments;

  // Default values for arguments
  arguments.source_file = 0;
  arguments.output_file = OUTPUT_FILE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  printf("SOURCE_FILE = %s\n", arguments.source_file);
  printf("OUTPUT_FILE = %s\n", arguments.output_file);
  printf("\n");

  FILE *source_file = fopen(arguments.source_file, "r");
  yyin = source_file;
  const Program *ast = parseAST(source_file);

  std::cout << "====================\n";
  std::cout << "formatted: \n";
  ast->print(std::cout);
  std::cout << std::endl;

  std::cout << "====================\n";
  std::cout << "exit status: ";
  std::cout << ast->evaluate();
  std::cout << std::endl;

  exit(0);
}
