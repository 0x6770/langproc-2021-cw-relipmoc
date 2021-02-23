#include "arg.hpp"
#include "ast.hpp"

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

  const Program *ast = parseAST();
  ast->print(std::cout);

  exit(0);
}
