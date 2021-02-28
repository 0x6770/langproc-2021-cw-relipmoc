#include "log.hpp"

void Log::debug(const char* msg, ...) const {
  // normal light-cyan text
  if (this->level <= levels::debug) {
    fprintf(stdout, "\033[0;96m[DEBUG]\033[0;96m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    va_end(args);
    fprintf(stdout, "\033[0m");
  }
}

void Log::info(const char* msg, ...) const {
  // bold blue text
  if (this->level <= levels::info) {
    fprintf(stdout, "\033[0;34m[INFO]\033[1;34m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    va_end(args);
    fprintf(stdout, "\033[0m");
  }
}

void Log::warn(const char* msg, ...) const {
  // bold yellow text
  if (this->level <= levels::warn) {
    fprintf(stdout, "\033[0;33m[WARN]\033[1;33m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    va_end(args);
    fprintf(stdout, "\033[0m");
  }
}

void Log::error(const char* msg, ...) const {
  // bold red text
  if (this->level <= levels::error) {
    fprintf(stdout, "\033[0;31m[ERROR]\033[1;31m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stdout, msg, args);
    va_end(args);
    fprintf(stdout, "\033[0m");
  }
}
