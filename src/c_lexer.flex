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
return                            {fprintf(stderr, "T_RETURN\n"); return T_RETURN;}
int                               {fprintf(stderr, "T_INT\n"); yylval.string=new std::string("int"); return T_INT;}
while                             {fprintf(stderr, "T_WHILE\n"); return T_WHILE;}
if                                {fprintf(stderr, "T_IF\n"); return T_IF;}
else                              {fprintf(stderr, "T_ELSE\n"); return T_ELSE;}

 /* more keywords for intermediate features */ 
for                               {fprintf(stderr, "T_FOR\n");      return T_FOR;}
enum                              {fprintf(stderr, "T_ENUM\n");     return T_ENUM;}
switch                            {fprintf(stderr, "T_SWITCH\n");   return T_SWITCH;}
break                             {fprintf(stderr, "T_BREAK\n");    return T_BREAK;}
continue                          {fprintf(stderr, "T_CONTINUE\n"); return T_CONTINUE;}

 /* keyword \nused for advanced features */
double                            {fprintf(stderr, "T_DOUBLE\n");   return T_DOUBLE;}
float                             {fprintf(stderr, "T_FLOAT\n");    return T_FLOAT;}
char                              {fprintf(stderr, "T_CHAR\n");     return T_CHAR;}
unsigned                          {fprintf(stderr, "T_UNSIGNED\n"); return T_UNSIGNED;}
struct                            {fprintf(stderr, "T_STRUCT\n");   return T_STRUCT;}
typedef                           {fprintf(stderr, "T_TYPEDEF\n");  return T_TYPEDEF;}
sizeof                            {fprintf(stderr, "T_SIZEOF\n");   return T_SIZEOF;}
[\n\t\r ]                         {}


 /* calculation */
\+                                {fprintf(stderr, "+\n");    return yytext[0];}
\*                                {fprintf(stderr, "*\n");    return yytext[0];}
\^                                {fprintf(stderr, "^\n");    return yytext[0];}
\-                                {fprintf(stderr, "-\n");    return yytext[0];}
\/                                {fprintf(stderr, "/\n");    return yytext[0];}
\%                                {fprintf(stderr, "%%\n");   return yytext[0];}
\&                                {fprintf(stderr, "&\n");    return yytext[0];}
\|                                {fprintf(stderr, "|\n");    return yytext[0];}
\~                                {fprintf(stderr, "~\n");    return yytext[0];}
\>                                {fprintf(stderr, ">\n");    return T_GREATER;}
\<                                {fprintf(stderr, "<\n");    return T_LESS;}
\=\=                              {fprintf(stderr, "==\n");   return T_EQUAL;}
\>\=                              {fprintf(stderr, ">=\n");   return T_GREATER_E;}
\<\=                              {fprintf(stderr, "<=\n");   return T_LESS_E;}
\!\=                              {fprintf(stderr, "!=\n");   return T_NOT_EQUAL;}
\&\&                              {fprintf(stderr, "&&\n");   return T_AND_L;}
\|\|                              {fprintf(stderr, "||\n");   return T_OR_L;}
\!                                {fprintf(stderr, "!\n");    return yytext[0];}
\=                                {fprintf(stderr, "=\n");    return yytext[0];}
\{                                {fprintf(stderr, "{\n");    return yytext[0];}
\}                                {fprintf(stderr, "}\n");    return yytext[0];}
\(                                {fprintf(stderr, "(\n");    return yytext[0];}
\)                                {fprintf(stderr, ")\n");    return yytext[0];}
\[                                {fprintf(stderr, "[\n");    return yytext[0];}
\]                                {fprintf(stderr, "]\n");    return yytext[0];}
\;                                {fprintf(stderr, ";\n");    return yytext[0];}
\<\<                              {fprintf(stderr, "<<\n");   return T_SHIFT_L;}
\>\>                              {fprintf(stderr, ">>\n");   return T_SHIFT_R;}
[_a-zA-Z][0-9_a-zA-Z]*            {fprintf(stderr, "T_NAME\n"); std::string *x=new std::string(yytext); yylval.string=x; return T_NAME;}


 /* Number */
[0-9]+                            {int x=strtod(yytext, 0); fprintf(stderr, "%d\n", x); yylval.integer=x; return T_INT_VALUE;}


.                                 {fprintf(stderr, "Not Implemented yet\n"); exit(1);}

%%

void yyerror (FILE *source_file, const char *msg)
{
  fprintf (stderr, "Parse error : %s\n", msg);
  fclose(source_file);
  exit(1);
}
