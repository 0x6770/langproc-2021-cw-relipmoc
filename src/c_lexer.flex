%option noyywrap

%{

extern "C" int fileno(FILE *stream);
#include "C_parser.tab.hpp"

%}


%%


[_a-zA-z]+([0-9]|[_a-zA-Z])*      {return T_NAME;}
(return)                          {return T_RETURN;}
(int)                             {return T_INT;}
(while)                           {return T_WHILE;}
(if)                              {return T_IF;}
(else)                            {return T_ELSE;}
(else if)                         {return T_ELSEIF;}

[\+]                              {return T_ADD;}
[\*]                              {return T_MULT;}
[\^]                              {return T_EXP;}
[-]                               {return T_MINUS;}
[/]                               {return T_DIVIDE;}
[%]                               {return T_MODE;}
[&]                               {return T_AND;}
[\|]                              {return T_OR;}
[~]                               {return T_NOT;}
[>]                               {return T_GRATER;}
[\<]                              {return T_LESS;}
[==]                              {return T_EQUAL;}
(>=)                              {return T_GE;}
(\<=)                             {return T_LS;}
(!=)                              {return T_NE;}
(&&)                              {return T_LAND;}
(\|\|)                            {return T_LOR;}
[!]                               {return T_LNOT;}
[=]                               {return T_ASSIGN;}
[\{]                              {return T_LB;}
[}]                               {return T_RB;}
[\(]                              {return T_LBC;}
[)]                               {return T_RBC;}
[\[]                              {return T_LBS;}
[]]                               {return T_RBS;}  


/* Number */
[0-9]+                            {return T_INT;}


%%