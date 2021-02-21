#ifndef arg_hpp
#define arg_hpp

#include <argp.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "log.hpp"

const char *argp_program_version = "c2mips-compiler 0.1.0";

// Program documentation.
static char doc[] =
    "ELEC50010 Coursework -- a compiler from C to MIPS assembly";

// struct argp_option {
//   const char *name,
//   int key,
//   const char *arg,
//   int flags,
//   const char *doc,
//   int group)
// }
// https://www.gnu.org/software/libc/manual/html_node/Argp-Option-Vectors.html
static struct argp_option options[] = {
    {"level", 'l', "[0-3]", 1, "Set output level", 0},
    {"source", 'S', "FILE", 0, "Path to source file", 0},
    {"output", 'o', "FILE", 0, "Path to output file, 'a.out' by default", 0},
    {0, 0, 0, 0, 0, 0}};

struct arguments {
  levels level;
  char *source_file = NULL;
  char *output_file = NULL;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  // Get the input argument from argp_parse
  struct arguments *arguments = (struct arguments *)state->input;

  switch (key) {
    case 'l':
      if (arg) {
        int level = atoi(arg);
        if (level < 4 && level >= 0) {
          arguments->level = (levels)level;
        } else {
          fprintf(stderr, "Wrong value specified for output level, %d\n",
                  level);
          argp_usage(state);
        }
      }
      break;

    case 'S':
      arguments->source_file = arg;
      break;

    case 'o':
      arguments->output_file = arg;
      break;

    case ARGP_KEY_END:
      if (!arguments->source_file) {
        fprintf(stdout, "[ERROR] ⚠️  Source file not specified\n");
        argp_usage(state);
      }
      break;

    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

// argp_parse(
//   const struct argp_option *options,
//   argp_parser_t parser,
//   const char *args_doc,
//   const char *doc,
//   const struct argp_child *children,
//   char *(*help_filter)(int key, const char *text, void *input),
//   const char *argp_domain
// )
// https://www.gnu.org/software/libc/manual/html_node/Argp-Parsers.html
static struct argp argp = {options, parse_opt, 0, doc, 0, 0, 0};

#endif
