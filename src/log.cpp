#include "log.hpp"

void Log::debug(const char* msg, ...) {
  // normal light-cyan text
  if (this->level <= levels::debug) {
    fprintf(stderr, "\033[0;96m[DEBUG]\033[0;96m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }
}

void Log::info(const char* msg, ...) {
  // bold blue text
  if (this->level <= levels::info) {
    fprintf(stderr, "\033[0;34m[INFO]\033[1;34m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }
}

void Log::warn(const char* msg, ...) {
  // bold yellow text
  if (this->level <= levels::warn) {
    fprintf(stderr, "\033[0;33m[WARN]\033[1;33m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }
}

void Log::error(const char* msg, ...) {
  // bold red text
  if (this->level <= levels::error) {
    fprintf(stderr, "\033[0;31m[ERROR]\033[1;31m\t");
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }
}
