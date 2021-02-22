%option noyywrap

%{

extern "C" int fileno(FILE *stream);
#include "c_parser.tab.hpp"

%}


%%

 /* keyword */
 /* used for basic requirements */
return                            {printf("T_RETURN\n"); return T_RETURN;}
int                               {printf("T_INT\n"); return T_INT;}
while                             {printf("T_WHILE\n"); return T_WHILE;}
if                                {printf("T_IF\n"); return T_IF;}
else                              {printf("T_ELSE\n"); return T_ELSE;}
else[ ]if                         {printf("T_ELSEIF\n"); return T_ELSEIF;}

 /* more keywords for intermediate features */ 
for                               {printf("T_FOR\n"); return T_FOR;}
enum                              {printf("T_ENUM\n"); return T_ENUM;}
switch                            {printf("T_SWITCH\n"); return T_SWITCH;}
break                             {printf("T_BREAK\n"); return T_BREAK;}
continue                          {printf("T_CONTINUE\n"); return T_CONTINUE;}

 /* keyword used for advanced features */
double                            {printf("T_DOUBLE\n"); return T_DOUBLE;}
float                             {printf("T_FLOAT\n"); return T_FLOAT;}
char                              {printf("T_CHAR\n"); return T_CHAR;}
unsigned                          {printf("T_UNSIGNED\n"); return T_UNSIGNED;}
struct                            {printf("T_STRUCT\n"); return T_STRUCT;}
typedef                           {printf("T_TYPEDEF\n"); return T_TYPEDEF;}
sizeof                            {printf("T_SIZEOF\n"); return T_SIZEOF;}
[\n\t\r ]                         {}


 /* calculation */
\+                                {printf("T_ADD\n"); return T_ADD;}
\*                                {printf("T_MUL\n"); return T_MUL;}
\^                                {printf("T_POW\n"); return T_POW;}
\-                                {printf("T_SUB\n"); return T_SUB;}
\/                                {printf("T_DIV\n"); return T_DIV;}
\%                                {printf("T_MOD\n"); return T_MOD;}
\&                                {printf("T_AND\n"); return T_AND;}
\|                                {printf("T_OR\n"); return T_OR;}
\~                                {printf("T_NOT\n"); return T_NOT;}
\>                                {printf("T_GREATER\n"); return T_GREATER;}
\<                                {printf("T_LESS\n"); return T_LESS;}
\=\=                              {printf("T_EQUAL\n"); return T_EQUAL;}
\>\=                              {printf("T_GE\n"); return T_GE;}
\<\=                              {printf("T_LE\n"); return T_LE;}
\!\=                              {printf("T_NE\n"); return T_NE;}
\&\&                              {printf("T_LAND\n"); return T_LAND;}
\|\|                              {printf("T_LOR\n"); return T_LOR;}
\!                                {printf("T_LNOT\n"); return T_LNOT;}
\=                                {printf("T_ASSIGN\n"); return T_ASSIGN;}
\{                                {printf("T_LB\n"); return T_LBC;}
\}                                {printf("T_RB\n"); return T_RBC;}
\(                                {printf("T_LBC\n"); return T_LB;}
\)                                {printf("T_RBC\n"); return T_RB;}
\[                                {printf("T_LBS\n"); return T_LBS;}
\]                                {printf("T_RBS\n"); return T_RBS;}  
\;                                {printf("T_SEMI\n"); return T_SEMI;}  
[_a-zA-Z][0-9_a-zA-Z]*            {printf("T_NAME\n"); return T_NAME;}


 /* Number */
[0-9]+                            {int x=strtod(yytext, 0); printf("%d\n", x); yylval.integer=x; return T_INT_VALUE;}


.                                 {fprintf(stderr, "Not Implemented yet\n"); exit(1);}

%%

void yyerror (char const*s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
