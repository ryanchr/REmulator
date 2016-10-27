/**********************************************************************************
-----------------------------------------------------------------------------------
    @File:    main.cpp
    @Author:  Ren Chen, CNASIC, <diyer.renchen@gmail.com>
    @Version: 1.0, 
    @Time:    2010-06-21, 15:29
    
    @section LICENSE
    @
    @section DESCRIPTION:
    This file mainly implements class definition of system controller module.
-----------------------------------------------------------------------------------
**********************************************************************************/

#include <systemc.h>
#include <sys/stat.h>
#include "./topsys/topsystem.h"
#include "./tools/system_def.h"
#include "./regfile/regs_vg.h"
#include "./regfile/regs_sg.h"
#include "./regfile/regs_if.h"
#include "./regfile/regs_d.h"
#include "./regfile/regs.h"
#include "./config/reconfigure_if.h"
#include "./rcore/rcore.h"
#include "./rcore/rca.h"
#include "./rcore/rc.h"
#include "./parameter/parameter_arch.h"
#include "./rcore/mux.h"
#include "./config/config_rcore.h"
#include "./config/config_rca.h"
#include "./config/config_rc.h"
#include "./config/config_mux.h"
#include "./config/config_alu.h"
#include "./rcore/alu.h"
#include "./parser/parser.h"

#if DEBUG_ENABLE_MAT_ENGINE
	#include "engine.h"
#endif
//#include "vld.h"

void config_parse(String);    //parse function in lex&yacc tool

TopSystem *topsystem;
ContextParser *parser_;

int sc_main(int argc, char* argv[])
{
	
	sc_report_handler::set_actions(SC_WARNING, SC_DO_NOTHING);
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	sc_clock clk("SystemClock", 1, SC_NS);

	parser_ = new ContextParser;

	String conf_file = "../../test_bench/test.cfg";
	config_parse( conf_file );
	#if DEBUG_ONLY_PARSE
		return 1;
	#endif
	
	topsystem = new TopSystem("Topsystem",parser_);
	topsystem->clk_in_(clk);	

	sc_start();
	
	if(parser_) {
		delete parser_; 
		parser_ = NULL;
	}
	if(topsystem){
		delete topsystem;
		topsystem = NULL;
	}
	return 1;
}
