#include <fstream>

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

  std::ifstream source_file(arguments.source_file);
  char c = source_file.get();

  while (source_file.good()) {
    std::cout << c;
    c = source_file.get();
  }

  source_file.close();

  const Program *ast = parseAST();

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
