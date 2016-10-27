#include <iostream>
#include <fstream>
#include <systemc.h>
#include "../tools/system_def.h"
#include "../parameter/parameter_arch.h"
#include "topsystem.h"
#include "../parser/parser.h"

using namespace TopSysParameter;
void config_parse( String );    //parse function in lex&yacc tool

void TopSystem::readInputContext()
{
	//Vector<RcoreContext> context = init_->getRcoreContext();
	//rcore_context_.reserve(context.size());
	//for(Uint32 i=0; i<context.size(); i++)
	//	rcore_context_.push_back(context[i]);
	rcore_context_ = init_->getRcoreContext();
}

void TopSystem::mainAction()
{	
	wait();
	Uint32 size_input;

#if DEBUG_USE_MAT_INPUT
	Uint8 * addr_input = init_->initialOfMatInput();
	size_input = 400*600;
	//Uint32 data_in_vgrf1[256];
	//rcore_[0]->port_to_vgregs_[0]->multiRead(data_in_vgrf1,0,256);
	/* initialize data in vgregs */
	//cout<<"----------Start initialize for VGRF by Matlab Engine---------"<<endl;
	for(Uint32 i = 0; i<NUM_VGRF; i++) {
		vgregs_[i]->initialize(addr_input, size_input);
		//wait();
	}
#endif

#if DEBUG_USE_TXT_INPUT
  Uint32 * addr_input;
  config_parse("../../test_bench/test.data");
	Vector<Uint32> data_in = init_->returnDataInputTxt();
	size_input = data_in.size();
	addr_input = new Uint32 [size_input];
	for(Uint32 i=0; i<size_input; i++)
		addr_input[i] = data_in[i];
  for(Uint32 i = 0; i<NUM_VGRF; i++) {
		vgregs_[i]->initialize(addr_input, size_input);
		//wait();
	}
	delete[] addr_input;
#endif

	//cout<<"----------End initialize for VGRF---------"<<endl;
	
	/* print simulating information */
	cout<<"************************ Start Simulation ************************"<<endl;
	#if DEBUG_PRINT_VGRF
	ofstream file1;
	file1.open("vgregs_start.txt");
	cout<<"*Event: print 'VGRF' value"<<endl;
	for(Uint32 i = 0; i<NUM_VGRF; i++) {
		file1<<"DATA IN VGRFS ["<<i<<"]: "<<endl;
		vgregs_[i]->print(file1);
		file1<<endl<<endl;
		//wait();
	}
	file1.close();
	#endif
	
	/* Read all system contexts  */
	readInputContext();	
	wait();
	
	/* start  simulation datacontext by datacontext 
	   NOTE: Now there is no task allocation between multi-cores */	 
	for( Uint32 i = 0; i<(Uint32)rcore_context_.size(); i++ ){	
		cout<<"<<<<< Time: "<<sc_time_stamp()<<", ";
		cout<<"Start RcoreContext[ "<<i<<" ] "<< " Simulation"<<endl;
		rcore_[0]->runOneContext(rcore_context_[i]);		

		wait();
		cout<<"<<<<< Time: "<<sc_time_stamp()<<","
		    <<" End RcoreContext[ "<<i<<" ] "<< " Simulation "<<endl<<endl;
	}
	
	cout<<endl<<"************************ End Simulation ************************"<<endl;

	#if DEBUG_PRINT_VGRF
	ofstream file2;
	file2.open("vgregs_end.txt");
	cout<<"*Event: print 'VGRF' value"<<endl;
	for(Uint32 i = 0; i<NUM_VGRF; i++) {
		file2<<"DATA IN VGRFS ["<<i<<"]: "<<endl;
		vgregs_[i]->print(file2);
		file2<<endl<<endl;
		//wait();
	}
	file2.close();
	#endif

	//while(true) wait();
	//wait();

	//cout<<"----------Start Output data to Matlab Engine---------"<<endl;
  #if DEBUG_USE_MAT_OUTPUT
	Uint32 data_in_vgrf[256];
	Uint32 data_in_sgrf[256];
	//rcore_[0]->printSGRF(data_in_sgrf);
	rcore_[0]->port_to_vgregs_[0]->multiRead(data_in_vgrf,0,256);
	init_->initialOfMatOutput(data_in_vgrf);
	#endif

	sc_stop();
		//wait();
}