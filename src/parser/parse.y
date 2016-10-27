/**********************************************************************************
----------------------------------------------------------------------------------
    @File:    configyacc.y
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0
    @Time:    2011/4/4 22:24
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements syntactical analysis of config file .
-----------------------------------------------------------------------------------
**********************************************************************************/

%{

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
// #include <dlfcn.h>
#include <stdarg.h>
#include <vector>
using namespace std;

#include "parser.h"
#include "../parameter/parameter_arch.h"

unsigned int idx_cfg_parse,idx_data_cfg_parse;
unsigned int idx_jump_modular = 0;
int * int_array_temp;
vector<unsigned int> int_vec_temp;
char ** string_array_temp;
vector<string> string_vec_temp;

int  yylex( void );
void yyerror ( char const * );

extern FILE*   yyin;

extern ContextParser *parser_;

%}

%union {
        unsigned int        uival;
        int                 ival;
        char *              char_ptr;  
        int *               int_vec;
        char **             char_vec;
}

%token TK_NUM_CONTEXT
%token TK_CONTEXT 

%token TK_FLAG_PIPELINE 
%token TK_NUM_GOLABAL_VAR_IN 
%token TK_NUM_GOLABAL_VAR_OUT 
%token TK_PORT_INDEX_GOLABAL_IN 
%token TK_NAME_GLOABAL_IN 
%token TK_NAME_GLOABAL_OUT 

%token TK_DATA_SOURCE_ROW 
%token TK_OP_ROW 
%token TK_DATA_DES_ROW 
%token TK_JUMP_MODULAR_SOURCE 
%token TK_JUMP_MODULAR_OP 
%token TK_JUMP_MODULAR_DES
     
%token TK_NUM_DATA_CONFIG
%token TK_DATA_CONFIG 

%token TK_READ_VGRF_CFG
%token TK_WRITE_VGRF_CFG
%token TK_DATA_ADDR_IN_ROW   
%token TK_DATA_ADDR_OUT_ROW 
%token TK_JUMP_MODULAR_ADDR_IN 
%token TK_JUMP_MODULAR_ADDR_OUT
%token TK_JUMP_MODULAR_MODE

%token TK_DATA_INPUT

%token TK_DIGIT
%token TK_CHAR

%type  <uival>    TK_DIGIT 
%type  <char_ptr> TK_CHAR

%type  <char_ptr> chars 

%%
/////////////////// A Whole Definition: Contexts //////////////////////////////
////////////          $1                $2
contexts :        num_context         context
{
#if DEBUG_YACC
	cout<<"yyparse >> ************** Context["<<idx_cfg_parse<<"] Parse End **************"<<endl;
#endif
}
		|		    contexts            context
{
#if DEBUG_YACC
	cout<<"yyparse >> ************** Context["<<idx_cfg_parse<<"] Parse End **************"<<endl;
#endif
}
;
/////////////////////// Part I of "Contexts": NUM_CONTEXT /////////////////////////////////
////////////           $1          $2        $3
num_context :    TK_NUM_CONTEXT    '='    TK_DIGIT 
{
#if DEBUG_YACC
	cerr <<endl;
	cerr << "yyparse >> ******************* Start Context Parse ******************* "<<endl;
	cerr << "yyparse >> The Number of Contexts is "<<$3<< endl;
#endif
	parser_->setNumOfContext($3);
}
; 
/////////////////////// Part II of "Contexts" : CONTEXT /////////////////////////////////
////////////    $1               $2             $3          
context :   head_context    route_context     data_context
{
#if DEBUG_YACC
#endif
}
;

/////////////////////// Part I of "context" : Context Head /////////////////////////////////
//////        	   $1               $2               $3                $4        
head_context :  index_context   flag_pipeline     num_gvar_in      num_gvar_out    
//////        	   $5             $6              $7             							
								index_port   name_port_in    name_port_out   
{ 
#if DEBUG_YACC
	cerr << "yyparse >> Head Context Parse End."<< endl<<endl;
	cerr << "yyparse >> Route Context Parse Start"<<endl;
#endif
//TODO
} 
;
//////        	   $1            $2        $3        $4        
index_context :  TK_CONTEXT      '['     TK_DIGIT    ']' 
{ 
#if DEBUG_YACC
	cerr << endl;
	cerr << "yyparse >> ************** Start Context"<<"["<<$3<<"] Parse **************"<< endl;
#endif
  idx_cfg_parse = $3;
} 
;
//////               $1                  $3 
flag_pipeline : TK_FLAG_PIPELINE  '='  TK_DIGIT
{
#if DEBUG_YACC
	cerr << "yyparse >> Flag of Pipeline :"<<" "<<$3<<" "<< endl;
#endif
	parser_->setFlagPipeline($3,idx_cfg_parse);
};
//////                 $1                        $3     
num_gvar_in :  TK_NUM_GOLABAL_VAR_IN   '='    TK_DIGIT 
{
#if DEBUG_YACC
	cerr << "yyparse >> The Number of Input Golabal Variables is "<< $3 << endl;
#endif
//TODO
	parser_->setNumOfGlobalIn($3,idx_cfg_parse);
} 
;                
//////                $1                         $3          
num_gvar_out : TK_NUM_GOLABAL_VAR_OUT   '='    TK_DIGIT
{
#if DEBUG_YACC
	cerr << "yyparse >> The number of Output Golabal Variables is " << $3 << endl;
#endif
//TODO
	parser_->setNumOfGlobalOut($3,idx_cfg_parse);
} 
;
//////                 $1                        $3    
index_port :         index          
		|                index_port              index
{
#if DEBUG_YACC
	cerr << "yyparse >> The Numbers of Port Indices are "<< endl;
#endif
//TODO
}
;
//////                 $1                       $3                          $6   
index :    TK_PORT_INDEX_GOLABAL_IN   '['     TK_DIGIT    ']'     '='    int_array		   
{
#if DEBUG_YACC
	cerr << "yyparse >> The Numbers of Port Indices are "<< endl;
#endif
//TODO
	parser_->setIndexOfGlobalPort($3, int_vec_temp, idx_cfg_parse);
}
;
//////                 $1                     $3    
name_port_in :       port_in         
			|            name_port_in          port_in
{
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Input Ports are " << endl;
#endif
//TODO
}
;
//////            $1                   $3                     $6
port_in : TK_NAME_GLOABAL_IN  '['   TK_DIGIT   ']'  '='   string_array
{
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Input Ports are " << endl;
#endif
//TODO
	parser_->setNameOfGlobalIn($3, string_vec_temp, idx_cfg_parse);
}
;
//////                 $1                           $3    
name_port_out :     port_out        
			|					  name_port_out         port_out
{
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Output Ports are "<< endl;
#endif
//TODO
}
;
//////            $1                           $3    
port_out : TK_NAME_GLOABAL_OUT    '['       TK_DIGIT     ']'    '='   string_array
{
#if DEBUG_YACC
	cerr << "yyparse >> The Names of Output Ports are "<< endl;
#endif
//TODO
		parser_->setNameOfGlobalOut($3, string_vec_temp, idx_cfg_parse);
}
;


///////////////////////// Part II of "context": Route Config /////////////////////////////// 
//////                 $1                 $2           
route_context :  rca_route_config   multi_jump_cfg
{
}
;
//////                    $1                     $2            $3       
rca_route_config :  route_cofing_row    
		 |		    rca_route_config      route_cofing_row 
{
#if DEBUG_YACC
#endif
}
;
//////                     $1             $2          $3       
route_cofing_row :  data_source_row     op_row    data_des_row  
{
#if DEBUG_YACC
#endif
}
;
//////                     $1             $2       $3        $4                  $7
data_source_row : TK_DATA_SOURCE_ROW  TK_DIGIT   '['     TK_DIGIT  ']'  '='  string_array				
{
#if DEBUG_YACC
	cerr << "yyparse >> row "<<$2<<" data source : num = "<<$4<< endl;
#endif
	parser_->setDataSource($4, string_vec_temp, idx_cfg_parse);	
}
;
////////   $1            $2       $3 
op_row:	TK_OP_ROW    TK_DIGIT    '['  TK_DIGIT  ']'  '='  string_array	
{
#if DEBUG_YACC
	cerr << "yyparse >> op_row"<<$2<<endl;
#endif
	parser_->setOpcode($4, string_vec_temp, idx_cfg_parse);	
}
;
///////////           $1            $2       $3 
data_des_row : TK_DATA_DES_ROW   TK_DIGIT   '['  TK_DIGIT  ']'  '='  string_array	  						
{
#if DEBUG_YACC
	cerr << "yyparse >> row "<<$2<<" data des : "<< endl;
#endif
	parser_->setDataDes($4, string_vec_temp, idx_cfg_parse);	
}
;  
//////                 $1             
multi_jump_cfg : jump_modular_cfg 
       |          multi_jump_cfg    jump_modular_cfg
{
}
;
//////                      $1               $2               $3
jump_modular_cfg : jump_modular_source   jump_modular_op  jump_modular_des
{
}
;
//////                       $1                $2       $3        $4                  $7
jump_modular_source : TK_JUMP_MODULAR_SOURCE   '['     TK_DIGIT  ']'  '='  string_array				
{
#if DEBUG_YACC
	cerr<<"yyparse >> jump modular "<<" source : num = "<<$3<<endl;
#endif
//TODO
	parser_->setDataSource($3, string_vec_temp, idx_cfg_parse);	
}
;
////////              $1             $2      $3 
jump_modular_op:	TK_JUMP_MODULAR_OP   '['   TK_DIGIT  ']'  '='  string_array	
{
#if DEBUG_YACC
	cerr<<"yyparse >> jump modular "<<" op : num = "<<$3<<endl;
#endif
//TODO
	parser_->setOpcode($3, string_vec_temp, idx_cfg_parse);	
}
;
///////////               $1             $2       $3 
jump_modular_des : TK_JUMP_MODULAR_DES    '['   TK_DIGIT  ']'  '='  string_array	  						
{
#if DEBUG_YACC
	cerr<<"yyparse >> jump modular "<<" des : num = "<<$3<<endl;
#endif
//TODO
	parser_->setDataDes($3, string_vec_temp, idx_cfg_parse);	
}
;

/////////////////////////// Part III of "context" : data config /////////////////////////////
//////    		    $1                  $2            
data_context :  num_data_cfg    multi_data_config   
{
#if DEBUG_YACC	
	cerr << "yyparse >> Data Context Parse End." << endl<<endl;
#endif
}
;
//////    		    $1                 $2       $3     
num_data_cfg : TK_NUM_DATA_CONFIG      '='    TK_DIGIT
{
#if DEBUG_YACC
	cerr <<endl;
	cerr << "yyparse >> Data Context Parse Start. "<< endl;
	cerr << "yyparse >> Num of Data Context is "<<$3<< endl;
#endif
	parser_->setDataCfgNum($3,idx_cfg_parse);
}
;
//////                  $1           
multi_data_config :  data_config   
{
#if DEBUG_YACC
#endif
}
		 |		  multi_data_config	    data_config
{
}
;

//////             $1           $2                $3                   $4                   $5
data_config : head_data_cfg  vgrf_cfg    multi_data_addr_in    multi_data_addr_out   multi_jump_data_cfg
{
#if DEBUG_YACC
#endif
    idx_jump_modular = 0;
}
;
//////    	           $1            $2     
head_data_cfg :  TK_DATA_CONFIG   TK_DIGIT    
{
#if DEBUG_YACC
	cerr << "yyparse >> Data Config Head : Index of Data Config = " <<$2<< endl;
#endif
	idx_data_cfg_parse = $2;;
}
;
//////             $1               $2           
vgrf_cfg :    read_vgrf_cfg    write_vgrf_cfg   
{
};
/////                   $1              $2        #3                         $5   
read_vgrf_cfg :   TK_READ_VGRF_CFG     '['     TK_DIGIT     ']'    '='   int_array
{
#if DEBUG_YACC
	cerr << "yyparse >> Here is Read Vgrf Config in Data Context "<<idx_data_cfg_parse<<endl;
#endif
	parser_->setReadVgrfCfg(idx_data_cfg_parse, $3, idx_cfg_parse, int_vec_temp);
};
/////                  $1              $2                                      $5
write_vgrf_cfg : TK_WRITE_VGRF_CFG     '['   TK_DIGIT     ']'    '='   int_array
{
#if DEBUG_YACC
	cerr << "yyparse >> Here is Write Vgrf Config in Data Context "<<idx_data_cfg_parse<<endl;
#endif
	parser_->setWriteVgrfCfg(idx_data_cfg_parse,  $3, idx_cfg_parse, int_vec_temp);
};
//////    		     	 $1        		   $2     
multi_data_addr_in :    data_addr_in_row       									     
		 |		       multi_data_addr_in	    data_addr_in_row		
{
#if DEBUG_YACC
#endif
}
;
//////    			          $1                 $2                $4
data_addr_in_row :     TK_DATA_ADDR_IN_ROW    TK_DIGIT    '['   TK_DIGIT   ']'   '='   int_array	
{
#if DEBUG_YACC
	cerr << "yyparse >> Read Data Addr in Row "<<$2<<endl;
#endif
	parser_->setDataAddrIn($4,idx_data_cfg_parse,idx_cfg_parse,int_vec_temp);
}
;
//////    			           $1        			     
multi_data_addr_out :    data_addr_out_row   		
	   |			    multi_data_addr_out     data_addr_out_row										 
{
#if DEBUG_YACC
#endif
}
;
//////    					$1        			    $2              $4
data_addr_out_row :  TK_DATA_ADDR_OUT_ROW   	 TK_DIGIT   '['  TK_DIGIT  ']'  '='  int_array	 
{
#if DEBUG_YACC
	 cerr << "yyparse >> Read Data Addr Out Row "<<$2<<endl;
#endif
//TODO
	parser_->setDataAddrOut($4,idx_data_cfg_parse,idx_cfg_parse,int_vec_temp);
}
;
//////    					  $1              
multi_jump_data_cfg :	jump_data_cfg 
{
	idx_jump_modular++;
}
         |            multi_jump_data_cfg   jump_data_cfg
{
    idx_jump_modular++;
}
;
//////    			  $1                $2                $3
jump_data_cfg :	 modular_addr_in   modular_addr_out    modular_mode
{
}
;
//////    					$1                   $2             $4
modular_addr_in :   TK_JUMP_MODULAR_ADDR_IN     '['  TK_DIGIT  ']'  '='  int_array	 
{
#if DEBUG_YACC
	 cerr << "yyparse >> Jump modular Config, Num of Addr in:"<<$3<< endl;
#endif
	parser_->setJumpDataIn($3,idx_data_cfg_parse,idx_cfg_parse,int_vec_temp,idx_jump_modular);
}
;
//////    				$1                     $2              $4
modular_addr_out :TK_JUMP_MODULAR_ADDR_OUT     '['  TK_DIGIT  ']'  '='  int_array	 
{
#if DEBUG_YACC
	 cerr << "yyparse >> Jump modular 2 Config, Num of Addr Out:"<<$3<< endl;
#endif
	parser_->setJumpDataOut($3,idx_data_cfg_parse,idx_cfg_parse,int_vec_temp,idx_jump_modular);
}
;
//////    			      $1               $2              $4
modular_mode :   TK_JUMP_MODULAR_MODE     '['  TK_DIGIT  ']'  '='  int_array	 
{
#if DEBUG_YACC
	 cerr << "yyparse >> Jump Module 2 Config, Num of Mode:"<<$3<< endl;
#endif
	parser_->setJumpMode($3,idx_data_cfg_parse,idx_cfg_parse,int_vec_temp,idx_jump_modular);
}
;

/////////////////////// Part V: Data Txt Parser /////////////////////////////////
//////  	      $1            $2		       $3     
data_txt :   TK_DATA_INPUT     '='          int_array       
{
#if DEBUG_YACC
	//cerr << "yyparse >> read data input txt!!! " << endl;
#endif
	parser_->readDataInputTxt(int_vec_temp);
}
;

/////////////////////// Part VI: Parser tools /////////////////////////////////
//////  	    $1         $2		       $3     
int_array :   '{'   	    digits       '}'
		|	  '{'                     '}'
{
#if DEBUG_YACC
	//cerr << "yyparse >> read an integer array!!! " << endl;
#endif
}
;
//////  	      $1          $2		       $3     
string_array :  '{'   	      '}'
		|	    '{'      strings               '}'
{
#if DEBUG_YACC
	//cerr << "yyparse >> read an string array!!! " << endl;
#endif
}
;
//////  	       $1        			
digits :      TK_DIGIT                    
{ 
	int_vec_temp.clear();  int_vec_temp.push_back($1);  
	//cerr <<"yyparse >> read a digit "<<endl;
}       						    							      
	   | 	    digits    ','   TK_DIGIT    
{    
	int_vec_temp.push_back($3);  
#if DEBUG_YACC
	//cerr <<"yyparse >> read a digit "<<endl;
#endif
}       
;
//////  	      $1        			
strings  :     chars			              
{  
	string_vec_temp.clear();   
	string_vec_temp.push_back($1); 
}     							       
	     |     strings  ','   chars     
{  string_vec_temp.push_back($3);  }     
;
//////  	  $1    $2     $3 			
chars  :   '"'   TK_CHAR  '"'           
{
#if DEBUG_YACC
	//cerr <<"yyparse >> read a string "<<endl;
#endif
	$$ = $2;
}
;

%%

void yyerror( char const *s )
{
	fprintf(stderr,"%s\n",s);
}

void config_parse( string name )
{
	yyin = fopen( name.c_str(), "r" ); 

	yyparse();

	return;
}


