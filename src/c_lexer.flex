%option noyywrap
%option noinput 
%option nounput

%{

extern "C" int fileno(FILE *stream);
#include "c_parser.tab.hpp"

%}


%%

 /* keyword */
 /* used for basic requirements */
return                            {fprintf(stderr, "T_RETURN "); return T_RETURN;}
int                               {fprintf(stderr, "T_INT "); yylval.string=new std::string("int"); return T_INT;}
while                             {fprintf(stderr, "T_WHILE "); return T_WHILE;}
if                                {fprintf(stderr, "T_IF ");    return T_IF;}
else                              {fprintf(stderr, "T_ELSE ");  return T_ELSE;}

 /* more keywords for intermediate features */ 
for                               {fprintf(stderr, "T_FOR ");      return T_FOR;}
enum                              {fprintf(stderr, "T_ENUM ");     return T_ENUM;}
switch                            {fprintf(stderr, "T_SWITCH ");   return T_SWITCH;}
case                              {fprintf(stderr, "T_CASE");      return T_CASE;}
break                             {fprintf(stderr, "T_BREAK");     return T_BREAK;}
continue                          {fprintf(stderr, "T_CONTINUE");  return T_CONTINUE;}

 /* keyword \nused for advanced features */
double                            {fprintf(stderr, "T_DOUBLE "); yylval.string=new std::string("double"); return T_DOUBLE;}
float                             {fprintf(stderr, "T_FLOAT "); yylval.string=new std::string("float"); return T_FLOAT;}
char                              {fprintf(stderr, "T_CHAR "); yylval.string=new std::string("char"); return T_CHAR;}
unsigned                          {fprintf(stderr, "T_UNSIGNED "); yylval.string=new std::string("unsigned"); return T_UNSIGNED;}
struct                            {fprintf(stderr, "T_STRUCT ");   return T_STRUCT;}
typedef                           {fprintf(stderr, "T_TYPEDEF ");  return T_TYPEDEF;}
sizeof                            {fprintf(stderr, "T_SIZEOF ");   return T_SIZEOF;}
[\n\t\r ]                         {}


 /* different types of assignment */
 \+\=                             {fprintf(stderr, "+=");   return T_ADDEQUAL;}
 \-\=                             {fprintf(stderr, "-=");   return T_SUBEQUAL;}
 \*\=                             {fprintf(stderr, "*=");   return T_MULEQUAL;}
 \/\=                             {fprintf(stderr, "/=");   return T_DIVEQUAL;}
 \<\<\=                           {fprintf(stderr, "<<=");  return T_SHIFTEQUAL_L;}
 \>\>\=                           {fprintf(stderr, ">>=");  return T_SHIFTEQUAL_R;}
 \&\=                             {fprintf(stderr, "&=");   return T_BITWISEEQUAL_AND;}
 \^\=                             {fprintf(stderr, "^=");   return T_BITWISEEQUAL_XOR;}
 \|\=                             {fprintf(stderr, "|=");   return T_BITWISEEQUAL_OR;}
 \%\=                             {return T_MODEQUAL;}

\,                                {return T_COMMA;}

 /* calculation */
\+\+                              {fprintf(stderr, "++");   return T_INCREMENT;}
\-\-                              {fprintf(stderr, "--");   return T_DECREMENT;}
\+                                {fprintf(stderr, "+");    return yytext[0];}
\*                                {fprintf(stderr, "*");    return yytext[0];}
\^                                {fprintf(stderr, "^");    return yytext[0];}
\-                                {fprintf(stderr, "-");    return yytext[0];}
\/                                {fprintf(stderr, "/");    return yytext[0];}
\%                                {fprintf(stderr, "%%");   return yytext[0];}
\&                                {fprintf(stderr, "&");    return yytext[0];}
\|                                {fprintf(stderr, "|");    return yytext[0];}
\~                                {fprintf(stderr, "~");    return yytext[0];}
\>                                {fprintf(stderr, ">");    return T_GREATER;}
\<                                {fprintf(stderr, "<");    return T_LESS;}
\=\=                              {fprintf(stderr, "==");   return T_EQUAL;}
\>\=                              {fprintf(stderr, ">=");   return T_GREATER_E;}
\<\=                              {fprintf(stderr, "<=");   return T_LESS_E;}
\!\=                              {fprintf(stderr, "!=");   return T_NOT_EQUAL;}
\&\&                              {fprintf(stderr, "&&");   return T_AND_L;}
\|\|                              {fprintf(stderr, "||");   return T_OR_L;}
\!                                {fprintf(stderr, "!");    return yytext[0];}
\=                                {fprintf(stderr, "=");    return yytext[0];}
\{                                {fprintf(stderr, " {\n"); return yytext[0];}
\}                                {fprintf(stderr, "}\n");  return yytext[0];}
\(                                {fprintf(stderr, "(");    return yytext[0];}
\)                                {fprintf(stderr, ")");    return yytext[0];}
\[                                {fprintf(stderr, "[");    return yytext[0];}
\]                                {fprintf(stderr, "]");    return yytext[0];}
\;                                {fprintf(stderr, ";\n");  return yytext[0];}
\<\<                              {fprintf(stderr, "<<");   return T_SHIFT_L;}
\>\>                              {fprintf(stderr, ">>");   return T_SHIFT_R;}
[_a-zA-Z][0-9_a-zA-Z]*            {std::string *x=new std::string(yytext); fprintf(stderr, "%s", (*x).c_str()); yylval.string=x; return T_NAME;}


 /* Number */
[0-9]+                            {int x=strtod(yytext, 0); fprintf(stderr, "%d", x); yylval.integer=x; return T_INT_VALUE;}


.                                 {fprintf(stderr, "Not Implemented yet\n"); exit(1);}

%%

void yyerror (FILE *source_file, const char *msg)
{
  fprintf (stderr, "Parse error : %s\n", msg);
  fclose(source_file);
  exit(1);
}

int getPos(int size){
  pos+=size;
  return pos;
}
