%option noyywrap

%{

extern "C" int fileno(FILE *stream);
#include "c_parser.tab.hpp"

%}


%%

 /* keyword */
 /* used for basic requirements */
return                            {printf("T_RETURN\n"); return T_RETURN;}
int                               {printf("T_INT\n"); yylval.type=c_type::c_int; return T_INT;}
while                             {printf("T_WHILE\n"); return T_WHILE;}
if                                {printf("T_IF\n"); return T_IF;}
else                              {printf("T_ELSE\n"); return T_ELSE;}
else[ ]if                         {printf("T_ELSEIF\n"); return T_ELSEIF;}

 /* more keywords for intermediate features */ 
for                               {printf("T_FOR\n");      return T_FOR;}
enum                              {printf("T_ENUM\n");     return T_ENUM;}
switch                            {printf("T_SWITCH\n");   return T_SWITCH;}
break                             {printf("T_BREAK\n");    return T_BREAK;}
continue                          {printf("T_CONTINUE\n"); return T_CONTINUE;}

 /* keyword \nused for advanced features */
double                            {printf("T_DOUBLE\n");   return T_DOUBLE;}
float                             {printf("T_FLOAT\n");    return T_FLOAT;}
char                              {printf("T_CHAR\n");     return T_CHAR;}
unsigned                          {printf("T_UNSIGNED\n"); return T_UNSIGNED;}
struct                            {printf("T_STRUCT\n");   return T_STRUCT;}
typedef                           {printf("T_TYPEDEF\n");  return T_TYPEDEF;}
sizeof                            {printf("T_SIZEOF\n");   return T_SIZEOF;}
[\n\t\r ]                         {}


 /* calculation */
\+                                {printf("+\n");    return yytext[0];}
\*                                {printf("*\n");    return yytext[0];}
\^                                {printf("^\n");    return yytext[0];}
\-                                {printf("-\n");    return yytext[0];}
\/                                {printf("/\n");    return yytext[0];}
\%                                {printf("%%\n");   return yytext[0];}
\&                                {printf("&\n");    return yytext[0];}
\|                                {printf("|\n");    return yytext[0];}
\~                                {printf("~\n");    return yytext[0];}
\>                                {printf(">\n");    return yytext[0];}
\<                                {printf("<\n");    return yytext[0];}
\=\=                              {printf("==\n");   return yytext[0];}
\>\=                              {printf(">=\n");   return yytext[0];}
\<\=                              {printf("<=\n");   return yytext[0];}
\!\=                              {printf("!=\n");   return yytext[0];}
\&\&                              {printf("&&\n");   return yytext[0];}
\|\|                              {printf("||\n");   return yytext[0];}
\!                                {printf("!\n");    return yytext[0];}
\=                                {printf("=\n");    return yytext[0];}
\{                                {printf("{\n");    return yytext[0];}
\}                                {printf("}\n");    return yytext[0];}
\(                                {printf("(\n");    return yytext[0];}
\)                                {printf(")\n");    return yytext[0];}
\[                                {printf("[\n");    return yytext[0];}
\]                                {printf("]\n");    return yytext[0];}
\;                                {printf(";\n");    return yytext[0];}
[_a-zA-Z][0-9_a-zA-Z]*            {printf("T_NAME\n"); std::string *x=new std::string(yytext); yylval.string=x; return T_NAME;}


 /* Number */
[0-9]+                            {int x=strtod(yytext, 0); printf("%d\n", x); yylval.integer=x; return T_INT_VALUE;}


.                                 {fprintf(stderr, "Not Implemented yet\n"); exit(1);}

%%

void yyerror (char const*s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
