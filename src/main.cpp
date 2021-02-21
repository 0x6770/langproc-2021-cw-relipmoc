#include "arg.hpp"
#include "log.hpp"

int main(int argc, char **argv) {
  char OUTPUT_FILE[] = "a.out";
  struct arguments arguments;

  // Default values.
  arguments.level = debug;
  arguments.source_file = 0;
  arguments.output_file = OUTPUT_FILE;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  fprintf(stdout, "SOURCE_FILE = %s\n", arguments.source_file);
  fprintf(stdout, "OUTPUT_FILE = %s\n", arguments.output_file);
  fprintf(stdout, "OUTPUT_LEVEL= %d\n", arguments.level);

  Log *new_log = new Log(arguments.level);
  new_log->debug("debuging %0.2f\n", 1.0);
  new_log->info("aaa\n");
  new_log->warn("warn %s\n", "abc");
  new_log->error("error\n");

  exit(0);
}
