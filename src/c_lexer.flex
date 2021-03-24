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
return                            { return T_RETURN;}
int                               {yylval.string=new std::string("int"); return T_INT;}
while                             { return T_WHILE;}
if                                {   return T_IF;}
else                              { return T_ELSE;}

 /* more keywords for intermediate features */ 
for                               {      return T_FOR;}
enum                              {  return T_ENUM;}
switch                            { return T_SWITCH;}
case                              {  return T_CASE;}
\:                                {           return yytext[0];}
default                           {   return T_DEFAULT;}
break                             { return T_BREAK;}
continue                          { return T_CONTINUE;}

 /* keyword \nused for advanced features */
double                            { yylval.string=new std::string("double"); return T_DOUBLE;}
float                             { yylval.string=new std::string("float"); return T_FLOAT;}
char                              {yylval.string=new std::string("char"); return T_CHAR;}
unsigned                          {yylval.string=new std::string("unsigned"); return T_UNSIGNED;}
struct                            {   return T_STRUCT;}
typedef                           {  return T_TYPEDEF;}
sizeof                            {   return T_SIZEOF;}
[\n\t\r ]                         {}


 /* different types of assignment */
 \+\=                             {  return T_ADDEQUAL;}
 \-\=                             {   return T_SUBEQUAL;}
 \*\=                             {   return T_MULEQUAL;}
 \/\=                             {   return T_DIVEQUAL;}
 \<\<\=                           { return T_SHIFTEQUAL_L;}
 \>\>\=                           { return T_SHIFTEQUAL_R;}
 \&\=                             {  return T_BITWISEEQUAL_AND;}
 \^\=                             {  return T_BITWISEEQUAL_XOR;}
 \|\=                             {   return T_BITWISEEQUAL_OR;}
 \%\=                             {return T_MODEQUAL;}

\,                                {return T_COMMA;}

 /* calculation */
\+\+                              {return T_INCREMENT;}
\-\-                              {return T_DECREMENT;}
\+                                {return yytext[0];}
\*                                {return yytext[0];}
\^                                {return yytext[0];}
\-                                {return yytext[0];}
\/                                {return yytext[0];}
\%                                {return yytext[0];}
\&                                {return yytext[0];}
\|                                {return yytext[0];}
\~                                {return yytext[0];}
\>                                { return T_GREATER;}
\<                                {return T_LESS;}
\=\=                              { return T_EQUAL;}
\>\=                              {return T_GREATER_E;}
\<\=                              {return T_LESS_E;}
\!\=                              {return T_NOT_EQUAL;}
\&\&                              {return T_AND_L;}
\|\|                              {return T_OR_L;}
\!                                {return yytext[0];}
\=                                {return yytext[0];}
\{                                {return yytext[0];}
\}                                {return yytext[0];}
\(                                { return yytext[0];}
\)                                {return yytext[0];}
\[                                {return yytext[0];}
\]                                {return yytext[0];}
\;                                {return yytext[0];}
\'                                {return T_CHAR_RE;}
\<\<                              {return T_SHIFT_L;}
\>\>                              {return T_SHIFT_R;}
[_a-zA-Z][0-9_a-zA-Z]*            {std::string *x=new std::string(yytext);  yylval.string=x; return T_NAME;}


 /* Number */
[0-9]+                            {int x=strtod(yytext, 0); yylval.integer=x; return T_INT_VALUE;}


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
