#ifndef log_hpp
#define log_hpp

#include <stdarg.h>

#include <cstring>
#include <string>

// ANSI escpae code (colors)
// foreground background
// black             30         40
// red               31         41
// green             32         42
// yellow            33         43
// blue              34         44
// magenta           35         45
// cyan              36         46
// white             37         47
// bright black      90         100
// bright red        91         101
// bright green      92         102
// bright yellow     93         103
// bright blue       94         104
// bright magenta    95         105
// bright cyan       96         106
// bright white      97         107

// 0 	Reset or normal
// 1 	Bold or increased intensity
// 2 	Faint, decreased intensity, or dim

enum levels { debug, info, warn, error };

char* convert_str(const std::string str);

class Log {
 private:
  int level;

 public:
  Log(levels _level) : level(_level){};
  void debug(const char* msg, ...) const;
  void info(const char* msg, ...) const;
  void warn(const char* msg, ...) const;
  void error(const char* msg, ...) const;
};

#endif
