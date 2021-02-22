## Token defination

Defined tokens

/* keyword */
/* used for basic requirements */
return                            T_RETURN\
int                               T_INT\
while                             T_WHILE\
if                                T_IF\
else                              {yylval.string=new std::string(yytext);   return T_ELSE;}
else[ ]if                         {yylval.string=new std::string(yytext);   return T_ELSEIF;}

/* more keywords for intermediate features */ 
for                               {yylval.string=new std::string(yytext);   return T_FOR;}
enum                              {yylval.string=new std::string(yytext);   return T_ENUM;}
switch                            {yylval.string=new std::string(yytext);   return T_SWITCH;}
break                             {yylval.string=new std::string(yytext);   return T_BREAK;}
continue                          {yylval.string=new std::string(yytext);   return T_CONTINUE;}

/* keyword used for afvanced features */
double                            {yylval.string=new std::string(yytext);   return T_DOUBLE;}
float                             {yylval.string=new std::string(yytext);   return T_FLOAT;}
char                              {yylval.string=new std::string(yytext);   return T_CHAR;}
unsigned                          {yylval.string=new std::string(yytext);   return T_UNSIGNED;}
struct                            {yylval.string=new std::string(yytext);   return T_STRUCT;}
typedef                           {yylval.string=new std::string(yytext);   return T_TYPEDEF;}
sizeof                            {yylval.string=new std::string(yytext);   return T_SIZEOF;}
\n


/* calculation */
\+                                {return T_ADD;}
\*                                {return T_MULT;}
\^                                {return T_EXP;}
\-                                {return T_MINUS;}
\/                                {return T_DIVIDE;}
\%                                {return T_MODE;}
\&                                {return T_AND;}
\|                                {return T_OR;}
\~                                {return T_NOT;}
\>                                {return T_GRATER;}
\<                                {return T_LESS;}
\=\=                              {return T_EQUAL;}
\>\=                              {return T_GE;}
\<\=                              {return T_LE;}
\!\=                              {return T_NE;}
\&\&                              {return T_LAND;}
\|\|                              {return T_LOR;}
\!                                {return T_LNOT;}
\=                                {return T_ASSIGN;}
\{                                {return T_LB;}
\}                                {return T_RB;}
\(                                {return T_LBC;}
\)                                {return T_RBC;}
\[                                {return T_LBS;}
\]                                {return T_RBS;}  
[_a-zA-z]+([0-9]|[_a-zA-Z])*      {return T_NAME;}


/* Number */
[0-9]+                            {yylval.number=strtod(yytext, 0);  return T_INT;}
[a-zA-Z]+                         {yylval.string=new std::string(yytext);  return T_STRING;}
