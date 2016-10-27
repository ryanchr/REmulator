/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    configlex.lex
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0
    @Time:    2011/4/4 20:57
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements lexical analysis of config file .
-----------------------------------------------------------------------------------
**********************************************************************************/
%option noyywrap
%{

#include <stdlib.h>
#include "parse.tab.hpp"
#include <iostream>
using std::cout;
using std::endl;

char*  errpos;
int line_num = 0;

%}

DIGIT    [0-9]
HEXDIGIT [0-9a-fA-F]
STRING   \"[^"]*\"
COMMENT "#"[^#]*"#"
%%

[ \t]+           ;
\n             { line_num++;  }

"}"              {       return yytext[0];            }
"{"              {       return yytext[0];            }
":"              {       return yytext[0];            }
","              {       return yytext[0];            }
"["              {       return yytext[0];            }
"]"              {       return yytext[0];            }
"="				 {       return yytext[0];            }
\"   			 {       return yytext[0];            }

#[^\n]*               ;

NUM_CONTEXT					{ return TK_NUM_CONTEXT;  }
CONTEXT                     { return TK_CONTEXT;  }

FLAG_PIPELINE               { return TK_FLAG_PIPELINE; }
NUM_GOLABAL_VAR_IN          { return TK_NUM_GOLABAL_VAR_IN; } 
NUM_GOLABAL_VAR_OUT         { return TK_NUM_GOLABAL_VAR_OUT; }
PORT_INDEX_GOLABAL_IN 		{ return TK_PORT_INDEX_GOLABAL_IN; }
NAME_GLOABAL_IN 			{ return TK_NAME_GLOABAL_IN; }
NAME_GLOABAL_OUT			{ return TK_NAME_GLOABAL_OUT; }

DATA_SOURCE_ROW_ 			{ return TK_DATA_SOURCE_ROW; }					
OP_ROW_				 	 	{ return TK_OP_ROW; }		
DATA_DES_ROW_     		 	{ return TK_DATA_DES_ROW; }		
JUMP_MODULAR_SOURCE		    { return TK_JUMP_MODULAR_SOURCE; }
JUMP_MODULAR_OP			    { return TK_JUMP_MODULAR_OP; }
JUMP_MODULAR_DES		    { return TK_JUMP_MODULAR_DES; } 		    

NUM_DATA_CONFIG        		{ return TK_NUM_DATA_CONFIG; } 
DATA_CONFIG_				{ return TK_DATA_CONFIG;   }

READ_VGRF_CFG				{ return TK_READ_VGRF_CFG; }
WRITE_VGRF_CFG         		{ return TK_WRITE_VGRF_CFG; }
DATA_ADDR_IN_ROW_			{ return TK_DATA_ADDR_IN_ROW;   }
DATA_ADDR_OUT_ROW_	   		{ return TK_DATA_ADDR_OUT_ROW; }
JUMP_MODULAR_ADDR_IN		{ return TK_JUMP_MODULAR_ADDR_IN; }
JUMP_MODULAR_ADDR_OUT		{ return TK_JUMP_MODULAR_ADDR_OUT; }
JUMP_MODULAR_MODE			{ return TK_JUMP_MODULAR_MODE; }
	
DATA_INPUT                  { return TK_DATA_INPUT; }

-?{DIGIT}+         |
0x{HEXDIGIT}+    |
0X{HEXDIGIT}+    {        
                      yylval.uival = strtoul( yytext, &errpos, 0 );
 
                      return TK_DIGIT;
                 }

[a-zA-Z0-9\/\.-]+  {       
                       yylval.char_ptr = strdup(yytext);
					   //cout<<yytext<<"!!!!"<<endl;
                       return TK_CHAR;
                   }

.             ECHO; //{ printf(" syntax error occur at ");  printf("at line %d\n", line_num ); };
%%

int yyerror( char* msg )
{
	printf("Error: %s	encountered at line number:%d\n", msg);	
	return 0;
}


