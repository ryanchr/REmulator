/*
*  parser.cpp
*
*  ContextParser Implementation
*
*  Copyright (C) 2010  Chen Ren
*
*  2011/4/9 15:34  Created.
*
*  Description: The ContextParser init the module through the cfgfile. 
*/
#include "parser.h"
#include <assert.h>
#include "../parameter/parameter_arch.h"
#include "../config/config_alu.h"
#include "../tools/system_def.h"
#include "../topsys/topsystem.h"

using namespace RcoreParameter;

ContextParser::ContextParser()
{
	mat_engine = new MatEngine("MatEngine");
	/* Initial for op_map_ */
	op_map_["OPNULL"] = OPNULL;
	op_map_["BYPASS0"] = BYPASS0;
	op_map_["ADD"] = ADD;
	op_map_["SUB"] = SUB;
	op_map_["MUL"] = MUL;
	op_map_["NOT0"] = NOT0;
	op_map_["AND"] = AND;
	op_map_["NAND"] = NAND;
	op_map_["OR"] = OR;
	op_map_["NOR"] = NOR;
	op_map_["XOR"] = XOR;
	op_map_["XNOR"] = XNOR;
	op_map_["LSL"] = LSL;
	op_map_["LSR"] = LSR;
	op_map_["ASR"] = ASR;
	op_map_["ROL"] = ROL;
	op_map_["ROR"] = ROR;
	op_map_["ASUB"] = ASUB;
	op_map_["LT"] = LT;

	op_map_["OPDEFAULT"] = OPNULL;

	/* Initial for rc_input_map_ */
 	rc_input_map_ = rc_input_cfg.input_cfg_;

	/* Initial for rc_input_map_ */
	rc_output_map_["NoOutput"] = NoOutput;
	rc_output_map_["ToRc"] = ToRc;
	rc_output_map_["ToRf"] = ToRf;
	rc_output_map_["ToGlobal"] = ToGlobal;

	rc_output_map_["Default"] = RcOutDefault;

 	num_context_ = 0;
}

void ContextParser::setNumOfContext(Uint32 num)
{	
	num_context_ = num;	
	init_rcore_context_.reserve(num);
	RcoreContext * context;
	context = new RcoreContext[num];
	for(Uint32 i=0; i<num; i++)
		init_rcore_context_.push_back(context[i]);
  delete []	context;
	context = NULL;
	#if DEBUG_CFG_PARSE
	cout<<"************************** Start Config File Initialization ************************"<<endl;
	cout<<"<<<<<<<<<<<<<<< Start Read Context Head"<<endl;
	cout<<"Initialzation : Num of RcoreContext is "<<num_context_<<endl;
	#endif
}

void ContextParser::setFlagPipeline(Uint32 flag, Uint32 index)
{
	assert(index<num_context_ && index>=0);
	init_rcore_context_[index].debugInfo_.flag_pipeline = flag;
	
	#if DEBUG_CFG_PARSE
	
	cout<<endl<<"Initialzation : "<<"Context["<<index<<"] Start Parse"<<endl;
	cout<<"Initialzation : "<<"Context["<<index<<"] "
	 											  <<"Flag of Pipeline is "<<flag<<endl;
	#endif
}

void ContextParser::setNumOfGlobalIn(Uint32 num, Uint32 index)
{
	assert(index<num_context_ && index>=0);
	init_rcore_context_[index].debugInfo_.num_global_data_in_ = num;
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "
	 											  <<"Num of Global Input is "<<num<<endl;
	#endif
}

void ContextParser::setNumOfGlobalOut(Uint32 num, Uint32 index)
{
	assert(index<num_context_ && index>=0);
	init_rcore_context_[index].debugInfo_.num_global_data_out_ = num;
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "
	 											  <<"Num of Global Output is "<<num<<endl;	
	#endif
}

void ContextParser::setIndexOfGlobalPort( Uint32 size, Vector<Uint32> vec_int, Uint32 index)
{
	assert(index<num_context_ && index>=0);
	
	Uint32 size_indices = init_rcore_context_[index].debugInfo_.indices_global_port_in.size();
	init_rcore_context_[index].debugInfo_.indices_global_port_in.reserve(size_indices + size);
	
	for(Uint32 i =0; i<size; i++)
		init_rcore_context_[index].debugInfo_.indices_global_port_in.push_back(vec_int[i]) ;
		
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "<<"Index of Global Output: ";

	for( Uint32 i=0; i< init_rcore_context_[index].debugInfo_.indices_global_port_in.size(); i++)
		cout<<init_rcore_context_[index].debugInfo_.indices_global_port_in[i]<<" ";
	cout<<endl;
	#endif
}

void ContextParser::setNameOfGlobalIn( Uint32 size, Vector<String> vec_string, Uint32 index)
{
	assert(index<num_context_ && index>=0);
	
	init_rcore_context_[index].debugInfo_.name_global_data_in_.reserve(size);
	init_rcore_context_[index].debugInfo_.name_global_data_in_ = vec_string;
	
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "<<"Name of Global Inputs: ";
	for( Uint32 i=0; i< init_rcore_context_[index].debugInfo_.name_global_data_in_.size(); i++)
		cout<<init_rcore_context_[index].debugInfo_.name_global_data_in_[i]<<" ";
	cout<<endl;
	#endif
}

void ContextParser::setNameOfGlobalOut( Uint32 size, Vector<String> vec_string, Uint32 index)
{
	assert(index<num_context_ && index>=0);
	
	//init_rcore_context_[index].debugInfo_.name_global_data_out_.reserve(size);
	init_rcore_context_[index].debugInfo_.name_global_data_out_ = vec_string;
	
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "<<"Name of Global Outputs: ";
	for( Uint32 i=0; i< init_rcore_context_[index].debugInfo_.name_global_data_out_.size(); i++)
		cout<<init_rcore_context_[index].debugInfo_.name_global_data_out_[i]<<" ";
	cout<<endl;	
	cout<<"<<<<<<<<<<<<<<< Start Read Route Context"<<endl;
	#endif

}

void ContextParser::setDataSource( Uint32 size, Vector<String> vec_string, Uint32 index )
{
	assert(index<num_context_ && index>=0);
	assert((vec_string.size() == NUM_RC_COL*NUM_ALU_INPUT)||(vec_string.size() == 3));

	Vector<Uint32> rc_in_temp;
	//TODO : this code will change with different RC Connection topology
	rc_in_temp.reserve(size);
	
	for (Uint32 i = 0; i<vec_string.size(); i++ ){
		Uint32 rc_in_code = (rc_input_map_.find(vec_string[i]))->second;
		rc_in_temp.push_back(rc_in_code);
	}
	init_rcore_context_[index].route_context.data_source_.reserve(NUM_RC_ROW);
	init_rcore_context_[index].route_context.data_source_.push_back(rc_in_temp);

	Uint32 cfg_size = (Uint32)init_rcore_context_[index].route_context.data_source_.size();
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "
	    <<"Row "<<cfg_size<<" Data Source: ";
	for ( Uint32 i=0; i< size; i++ ){
		cout<<vec_string[i]<<" ";
	}
	cout<<endl;
	#endif
}

void ContextParser::setOpcode( Uint32 size, Vector<String> vec_string, Uint32 index )
{
	assert(index<num_context_ && index>=0);
	assert((vec_string.size() == NUM_RC_COL)||(vec_string.size() == 2));
	
	Vector<Uint32> vec_op; 	
	vec_op.reserve(size);
	
	for(Uint32 i=0; i<(Uint32)vec_string.size(); i++ ){
		Uint32 opcode = (op_map_.find(vec_string[i]))->second;
			vec_op.push_back(opcode);
	}
	
	init_rcore_context_[index].route_context.op_rc_.push_back(vec_op);
	  
	Uint32 cfg_size = (Uint32)init_rcore_context_[index].route_context.op_rc_.size();
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "
	    <<"Row "<<cfg_size<<" Opcode: ";
	for ( Uint32 i=0; i< size; i++ )
	  	 cout<<vec_string[i]<<"   ";	  	
	cout<<endl;
	#endif
}

void ContextParser::setDataDes( Uint32 size, Vector<String> vec_string, Uint32 index ) 
{
	assert(index<num_context_ && index>=0);
	assert((vec_string.size() == NUM_RC_COL*NUM_ALU_OUTPUT)||(vec_string.size() == 2));
	
	Vector<Uint32> vec_out_temp; 	
	vec_out_temp.reserve(size);
	
	for(Uint32 i=0; i<(Uint32)vec_string.size(); i++){
		Uint32 outcode = (rc_output_map_.find(vec_string[i]))->second;
			vec_out_temp.push_back(outcode);
	}
	
	init_rcore_context_[index].route_context.data_des_.reserve(NUM_RC_COL);
	init_rcore_context_[index].route_context.data_des_.push_back(vec_out_temp);
	  
	Uint32 cfg_size = (Uint32)init_rcore_context_[index].route_context.data_des_.size();
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<index<<"] "
	    <<"Row "<<cfg_size<<" Data Des: ";
	for ( Uint32 i=0; i< size; i++ ){
	  	cout<<vec_string[i]<<"  ";
	}
	cout<<endl;
	#endif
}

void ContextParser::setDataCfgNum(Uint32 num, Uint32 index)
{
	assert(num>=0);
	JumpModularDataCfg jump_data_cfg;
	init_rcore_context_[index].num_data_context = num;
	init_rcore_context_[index].data_context_group.creatDataContext(num);
	/* initial for jump data context */
	init_rcore_context_[index].jump_of_data_cfg.assign(num,jump_data_cfg);
	init_rcore_context_[index].jump_read_vgrf_cfg.assign(num,jump_data_cfg);
	init_rcore_context_[index].jump_write_vgrf_cfg.assign(num,jump_data_cfg);
	
	#if DEBUG_CFG_PARSE
	  cout<<"<<<<<<<<<<<<<<< Start Read Data Context"<<endl;
	  cout<<"Initialzation : "<<"Context["<<index<<"] "
	      <<"Num of Data Context is: "<<num<<"  ";
	  cout<<endl;
	#endif
}

void ContextParser::setDataAddrIn(Uint32 size, Uint32 loopindex, Uint32 cfgindex, Vector<Uint32> vec_int)
{
	assert(size == NUM_RC_COL*NUM_ALU_INPUT);

	init_rcore_context_[cfgindex].data_context_group.data_context[loopindex]->addr_data_in.push_back(vec_int);
	Uint32 cfg_size = (Uint32)init_rcore_context_[cfgindex].data_context_group.data_context[loopindex]->addr_data_in.size();
	#if DEBUG_CFG_PARSE
	  cout<<"Initialzation : "<<"Context["<<cfgindex<<"] "
	      <<"DataCfg"<<loopindex<<" ";
		cout<<"Row "<<cfg_size<<" Data Addr In: ";
		for(Uint32 i=0; i<size; i++)
			cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}

void ContextParser::setDataAddrOut(Uint32 size, Uint32 loopindex, Uint32 cfgindex, Vector<Uint32> vec_int)
{
	assert(size == NUM_RC_COL*NUM_ALU_OUTPUT);

	init_rcore_context_[cfgindex].data_context_group.data_context[loopindex]->addr_data_out.push_back(vec_int);
	Uint32 cfg_size = (Uint32)init_rcore_context_[cfgindex].data_context_group.data_context[loopindex]->addr_data_out.size();
	#if DEBUG_CFG_PARSE
	  cout<<"Initialzation : "<<"Context["<<cfgindex<<"] "
	      <<"DataCfg"<<loopindex<<" ";
		cout<<"Row "<<cfg_size<<" Data Addr Out: ";
		for(Uint32 i=0; i<size; i++)
			cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}

void ContextParser::setReadVgrfCfg(Uint32 idx_data_cfg, Uint32 size, Uint32 cfgindex, Vector<Uint32> vec_int)
{
	vec_int.insert(vec_int.begin(), idx_data_cfg);
	init_rcore_context_[cfgindex].read_vgrf_context.push_back(vec_int);
	
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<cfgindex<<"] "<<"Read Vgrf Cfg: ";
		for(Uint32 i=0; i<(Uint32)vec_int.size(); i++)
	  	cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}

void ContextParser::setWriteVgrfCfg(Uint32 idx_data_cfg, Uint32 size, Uint32 cfgindex, Vector<Uint32> vec_int)
{
	vec_int.insert(vec_int.begin(), idx_data_cfg);
	init_rcore_context_[cfgindex].write_vgrf_context.push_back(vec_int);
	
	#if DEBUG_CFG_PARSE
	cout<<"Initialzation : "<<"Context["<<cfgindex<<"] "<<"Write Vgrf Cfg: ";
	  for(Uint32 i=0; i<(Uint32)vec_int.size(); i++)
	  	cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}

void ContextParser::setJumpDataIn(Uint32 size, Uint32 idx_data_cfg, Uint32 idx_cfg, Vector<Uint32> vec_int, Uint32 idx_jump_modular)
{	
	switch(idx_jump_modular)
	{
		case 0: init_rcore_context_[idx_cfg].jump_of_data_cfg[idx_data_cfg].data_in = vec_int;
			      break;
		case 1: init_rcore_context_[idx_cfg].jump_read_vgrf_cfg[idx_data_cfg].data_in = vec_int;
						break;
		case 2: init_rcore_context_[idx_cfg].jump_write_vgrf_cfg[idx_data_cfg].data_in = vec_int;
						break;
	}
	#if DEBUG_CFG_PARSE
	  cout<<"Initialzation : "<<"Context["<<idx_cfg<<"] ";
		cout<<"Set Jump Module"<<idx_jump_modular<<" Data In Cfg: ";
		for(Uint32 i=0; i<size; i++)
			cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}


void ContextParser::setJumpDataOut(Uint32 size, Uint32 idx_data_cfg, Uint32 idx_cfg, Vector<Uint32> vec_int, Uint32 idx_jump_modular)
{	
	switch(idx_jump_modular)
	{
		case 0: init_rcore_context_[idx_cfg].jump_of_data_cfg[idx_data_cfg].data_out = vec_int;
			      break;
		case 1: init_rcore_context_[idx_cfg].jump_read_vgrf_cfg[idx_data_cfg].data_out = vec_int;
						break;
		case 2: init_rcore_context_[idx_cfg].jump_write_vgrf_cfg[idx_data_cfg].data_out = vec_int;
						break;
	}
	#if DEBUG_CFG_PARSE
	  cout<<"Initialzation : "<<"Context["<<idx_cfg<<"] ";
		cout<<"Set Jump Module"<<idx_jump_modular<<" Data Out Cfg: ";
		for(Uint32 i=0; i<size; i++)
			cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}


void ContextParser::setJumpMode(Uint32 size, Uint32 idx_data_cfg, Uint32 idx_cfg, Vector<Uint32> vec_int, Uint32 idx_jump_modular)
{	
	switch(idx_jump_modular)
	{
		case 0: init_rcore_context_[idx_cfg].jump_of_data_cfg[idx_data_cfg].mode = vec_int;
			      break;
		case 1: init_rcore_context_[idx_cfg].jump_read_vgrf_cfg[idx_data_cfg].mode = vec_int;
						break;
		case 2: init_rcore_context_[idx_cfg].jump_write_vgrf_cfg[idx_data_cfg].mode = vec_int;
						break;
	}
	#if DEBUG_CFG_PARSE
	  cout<<"Initialzation : "<<"Context["<<idx_cfg<<"] ";
		cout<<"Set Jump Module"<<idx_jump_modular<<" Modular Mode Cfg: ";
		for(Uint32 i=0; i<size; i++)
			cout<<"0x"<<hex<<vec_int[i]<<" ";
	  cout<<endl;
	#endif
}

Vector<RcoreContext> ContextParser::getRcoreContext(void)
{
	return init_rcore_context_;
}

Uint8 * ContextParser::initialOfMatInput()
{
	mat_engine->inputEngine();
	return mat_engine->returnDataPr();
}

void ContextParser::initialOfMatOutput(Uint32 *output)
{
	mat_engine->outputEngine(output);
	return ;
}

void ContextParser::readDataInputTxt(Vector<Uint32> vec_int)
{
  data_txt_in = vec_int;
	return;
}

Vector<Uint32> ContextParser::returnDataInputTxt(void) const
{
	return data_txt_in;
}
	